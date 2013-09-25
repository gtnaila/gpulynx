/*! \file PTXInstrumentor.cpp
	\date Saturday November 13, 2010
	\author Naila Farooqui <naila@cc.gatech.edu>
	\brief The source file for the PTXInstrumentor class.
*/

#ifndef PTX_INSTRUMENTOR_CPP_INCLUDED
#define PTX_INSTRUMENTOR_CPP_INCLUDED

#include <lynx/instrumentation/interface/PTXInstrumentor.h>
#include <lynx/transforms/interface/CToPTXModulePass.h>
#include <lynx/transforms/interface/CToPTXInstrumentationPass.h>
#include <lynx/translator/interface/CToPTXTranslator.h>

#include <cuda_runtime.h>

#include <ocelot/transforms/interface/PassManager.h>
#include <ocelot/ir/interface/Module.h>

#include <hydrazine/interface/Exception.h>
#include <hydrazine/interface/json.h>

#include <fstream>
#include <cstring>
#include <unistd.h>

#define MQ_DFT_PRIO 0

#ifdef REPORT_BASE
#undef REPORT_BASE
#endif

// whether debugging messages are printed
#define REPORT_BASE 0

namespace instrumentation
{

    void PTXInstrumentor::createPasses(std::string resource) 
    {
        translator::CToPTXData translation = 
            translator::CToPTXTranslator::translator().generate(resource);
        transforms::CToPTXInstrumentationPass *pass = 
            new transforms::CToPTXInstrumentationPass(translation);
        
        std::string function;
        
        for(ir::PTXKernel::PTXStatementVector::const_iterator statement = 
            translation.statements.begin(); 
            statement != translation.statements.end();
            ++statement)
        {
            if((statement->toString()).find(UNIQUE_ELEMENT_COUNT) 
                != std::string::npos)
            {
                function = UNIQUE_ELEMENT_COUNT;
                break;
            }
        }    
        
        transforms::CToPTXModulePass *modulePass = 
            new transforms::CToPTXModulePass(function, translation.globals);
        modulePass->parameterMap = pass->parameterMap;
        
        passes[0] = pass;
        passes[1] = modulePass; 
    }


    void PTXInstrumentor::instrument(ir::Module& module) {

        transforms::PassManager manager( &module );
        
        createPasses(specificationPath());
        for(PassMap::iterator pass = passes.begin(); pass != passes.end(); ++pass)
        {
            if(pass->second != NULL)
                manager.addPass( pass->second ); 
        }
	    manager.runOnModule();
        manager.releasePasses();  
    }

    void PTXInstrumentor::finalize() {

        if(out == NULL) {
            if(!output.empty()){
                out = new std::ofstream(output.c_str(), std::fstream::app);
		    }
            else {
			       out = &std::cout;
		    }
        }

        extractResults(out);
    }

    void PTXInstrumentor::jsonEmitter(std::string metric, hydrazine::json::Object *stats) {
   
		std::ofstream outFile;

		std::string tmp = "." + metric;
		int i = 1;
		bool alreadyExists = true;
		do {
			outFile.open((kernelName + tmp + ".json").c_str(), std::ios::in);	
			if( outFile.is_open() )
			{
				std::stringstream out;
				out << "." << metric << "." << i;
				tmp = out.str();
				i++;
			} else {
				alreadyExists = false;
			}
            outFile.close();
		} while(alreadyExists);
	
		outFile.open((kernelName + tmp + ".json").c_str());
		hydrazine::json::Emitter emitter;
		emitter.use_tabs = false;
		emitter.emit_pretty(outFile, stats, 2);
        outFile.close();

    }

    void PTXInstrumentor::deviceInfo(std::ostream *out) {

        if(out == NULL) {
            return;
        }

        struct cudaDeviceProp properties;
        cudaGetDeviceProperties(&properties, 0);
    
        *out << "DEVICE INFO:\n\n";
        *out << "Multiprocessor Count: " << properties.multiProcessorCount << "\n"; 
        
        *out << "Total amount of global memory: " << properties.totalGlobalMem << "\n";
        
        *out << "Total amount of constant memory: " << properties.totalConstMem << "\n";
        *out << "Total amount of shared memory per block: " << properties.sharedMemPerBlock << "\n";
        *out << "Total number of registers available per block: " << properties.regsPerBlock << "\n";
        
        *out << "Warp size: " << properties.warpSize << "\n";
        *out << "Maximum number of threads per block: " << properties.maxThreadsPerBlock << "\n";
        *out << "Maximum sizes of each dimension of a block: " << properties.maxThreadsDim[0] << " x " << properties.maxThreadsDim[1] << " x " << 
                properties.maxThreadsDim[2] << "\n";     
        *out << "Maximum sizes of each dimension of a grid: " << properties.maxGridSize[0] << " x " << properties.maxGridSize[1] << " x " << 
                properties.maxGridSize[2] << "\n";     
        
        *out << "Clock rate: " << properties.clockRate * 1e-6f << " GHz\n";

        *out << "\n\n";

    }
    
    int PTXInstrumentor::sendKernelProfile(mqd_t messageQueue) {
    
        int err = 0;
        
        _profile.pid = getpid();
       
	cudaGetDevice(&_profile.device);
 
        int len = kernelName.size() > MAX_KERNEL_NAME_SIZE - 1 
            ? MAX_KERNEL_NAME_SIZE - 1 : kernelName.size();
        
        std::strncpy(_profile.name, kernelName.data(), len);
        _profile.name[len] = '\0';
        
        do {
            err = mq_send(messageQueue, (char *)&_profile, sizeof(kernel_profile), MQ_DFT_PRIO);
            
            if(err == 0)
                break;
            else {
                /* if O_NONBLOCK is set and the message queue is full, EAGAIN is returned. In this
                case, we do nothing so that if the messages we send are not consumed by anyone, 
                we still function normally */
                if(errno == EAGAIN)
                    break;
            
            }
        } 
        /* keep sending message while a signal interrupted call */
        while(errno == EINTR);
        
        return err;
    }
    
    bool PTXInstrumentor::conditionsMet()
    {
        bool conditionsMet = false;
    
        report("kernelsToInstrument: " << kernelsToInstrument.size());
        if(kernelsToInstrument.size() == 0)
        {
            /* instrument all kernels */    
            conditionsMet = true;
        }
        
        for(KernelVector::const_iterator kernel = kernelsToInstrument.begin();
            kernel != kernelsToInstrument.end(); ++kernel)
        {
            if(kernelName.find(*kernel) != std::string::npos)
            {
                conditionsMet = true;
                break;
            }
        }

        

        if(conditionsMet)
        {
            report("kernelName: " << kernelName << ", iterations: " << iterations );
            if(iterations == 0) {
                conditionsMet = false;
            }
            else if(iterations > 0 && !kernelName.empty()){
                KernelDataMap::iterator kernelData = kernelDataMap.find(kernelName);
                if(kernelData == kernelDataMap.end())
                {
                    kernelDataMap.insert(std::make_pair(kernelName, 0));
                }
                else if(kernelData->second >= iterations){
                    report("iterations condition failed");
                    conditionsMet = false;
                }
                (kernelDataMap.find(kernelName)->second)++;
            }
        }
       
        if(conditionsMet)
            return validate();

        return false;
    }

    PTXInstrumentor::PTXInstrumentor() : description(""),
        symbol(GLOBAL_MEM_BASE_ADDRESS), on(false), fmt(text), 
        deviceInfoWritten(false), sharedMemSize(0), iterations(-1)
    {
        out = NULL;
    }

    PTXInstrumentor::~PTXInstrumentor() {
        if(out != &std::cout && out != NULL){
            delete out;
        }
    }

}

#endif
