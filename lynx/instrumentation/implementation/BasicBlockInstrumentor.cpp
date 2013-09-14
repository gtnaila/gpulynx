/*! \file BasicBlockInstrumentor.cpp
	\date Monday November 15, 2010
	\author Naila Farooqui <naila@cc.gatech.edu>
	\brief The source file for the BasicBlockInstrumentor class.
*/

#ifndef BASIC_BLOCK_INSTRUMENTOR_CPP_INCLUDED
#define BASIC_BLOCK_INSTRUMENTOR_CPP_INCLUDED

#include <lynx/instrumentation/interface/BasicBlockInstrumentor.h>
#include <lynx/instrumentation/interface/InstrumentationRuntime.h>

#include <lynx/transforms/interface/CToPTXInstrumentationPass.h>
#include <lynx/transforms/interface/CToPTXModulePass.h>
#include <lynx/translator/interface/CToPTXTranslator.h>
#include <lynx/api/interface/lynx.h>

#include <cuda_runtime.h>
#include <ocelot/ir/interface/Module.h>

#include <hydrazine/interface/ArgumentParser.h>
#include <hydrazine/interface/string.h>
#include <hydrazine/interface/debug.h>
#include <hydrazine/interface/Exception.h>

#include <fstream>

using namespace hydrazine;

namespace instrumentation
{

    bool BasicBlockInstrumentor::validate() {
        return true;
    }

    void BasicBlockInstrumentor::analyze(ir::Module &module) {
        
        for (ir::Module::KernelMap::const_iterator kernel = module.kernels().begin(); 
	        kernel != module.kernels().end(); ++kernel) {
	        kernelDataMap[kernel->first] = kernel->second->cfg()->size() - 2;
        
            for( ir::ControlFlowGraph::const_iterator block = kernel->second->cfg()->begin(); 
			block != kernel->second->cfg()->end(); ++block ) {
                if(block->label() == "entry" || block->label() == "exit")
                    continue;
                kernelLabelsMap[kernel->first].push_back(block->label());
            }
        }
        
    }

    void BasicBlockInstrumentor::initialize() {
        
        counter = 0;

        if(cudaMalloc((void **) &counter, 
            (entries * kernelDataMap[kernelName] * threadBlocks * threads) 
                * sizeof(size_t)) != cudaSuccess){
            throw hydrazine::Exception( 
            "Could not allocate sufficient memory on device (cudaMalloc failed)!" );
        }
        if(cudaMemset( counter, 0, 
            (entries * kernelDataMap[kernelName] * threadBlocks * threads) * 
            sizeof( size_t )) != cudaSuccess){
            throw hydrazine::Exception( "cudaMemset failed!" );
        }
        
        if(cudaMemcpyToSymbol(symbol.c_str(), &counter, sizeof(size_t *), 0, 
            cudaMemcpyHostToDevice) != cudaSuccess) {
            throw hydrazine::Exception( "cudaMemcpyToSymbol failed!");
        }
    }

    std::string BasicBlockInstrumentor::specificationPath() {
        
        entries = 1;
        std::string resource;
        
        switch(type) {
            case executionCount:
            {
                resource = "resources/basicBlockExecutionCount.c";
                _profile.type = EXECUTION_COUNT;
                break;
            }
            case instructionCount:
            {
                resource = "resources/threadInstructionCount.c";
                _profile.type = INST_COUNT;
                break;
            }
            default:
                throw hydrazine::Exception( "No basic block instrumentation pass specified!" );
        }
        
        return resource;
    }

    void BasicBlockInstrumentor::extractResults(std::ostream *out) {

        size_t *info = new size_t[(entries * kernelDataMap[kernelName] * 
            threadBlocks * threads)];
        if(counter) {
            cudaMemcpy(info, counter, (entries * kernelDataMap[kernelName] * 
                threadBlocks * threads) * sizeof( size_t ), cudaMemcpyDeviceToHost);
            cudaFree(counter);
        }

        unsigned long instructionCount = 0;
        
        size_t j = 0;
        for(j = 0; j < kernelDataMap[kernelName] * threads * threadBlocks; j++) {
            instructionCount += info[j];
        }

        _profile.data.instruction_count = instructionCount;
        
        sendKernelProfile(InstrumentationRuntime::Singleton.messageQueue);

        if(info)
            delete[] info;
            
    }

    BasicBlockInstrumentor::BasicBlockInstrumentor(){
        description = "Basic Block Execution Count Per Thread";        
    }

    BasicBlockInstrumentor::BasicBlockInstrumentor(BasicBlockInstrumentationType type)
    : type(type) {
        description = "Basic Block Execution Count Per Thread";        
    }    

}

#endif
