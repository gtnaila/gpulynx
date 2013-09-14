/*! \file   InstrumentationRuntime.cpp
	\author Naila Farooqui <naila@cc.gatech.edu>
	\date   Tuesday November 22, 2011
	\brief  The source file for the InstrumentationRuntime class.
*/

#ifndef INSTRUMENTATION_RUNTIME_CPP_INCLUDED
#define INSTRUMENTATION_RUNTIME_CPP_INCLUDED

// Instrumentation includes
#include <lynx/instrumentation/interface/InstrumentationRuntime.h>
#include <lynx/api/interface/lynx.h>
#include <lynx/instrumentation/interface/kernel_profile.h>

#include <lynx/instrumentation/interface/BasicBlockInstrumentor.h>
#include <lynx/instrumentation/interface/ClockCycleCountInstrumentor.h>
#include <lynx/instrumentation/interface/WarpInstrumentor.h>

// Hydrazine includes
#include <hydrazine/interface/Exception.h>
#include <hydrazine/interface/debug.h>
#include <hydrazine/interface/json.h>

#include <errno.h>

#ifdef REPORT_BASE
#undef REPORT_BASE
#endif

#define REPORT_BASE 0

namespace instrumentation
{

    InstrumentationRuntime InstrumentationRuntime::Singleton;

    InstrumentationRuntime::InstrumentationRuntime() : toggledActiveInstrumentor(false)
    {
        report("InstrumentationRuntime Constructor");
        
        // Open a message queue for writing (sending data)
        messageQueue = mq_open (MSG_QUEUE, O_RDWR | O_NONBLOCK);
        if(messageQueue < 0)
        {
            report( "Failed to open message queue for writing" );       
            if(errno == EACCES)
                report("invalid permissions");
            if(errno == ENOENT)
                report("no queue with this name exists");
            if(errno == EEXIST)
                report("queue with this name already exists");
            if(errno == EINVAL)
                report("invalid attribute properties");
        }
        
        if(configuration.clockCycleCount)
	    {
		    report( "Creating clock cycle count instrumentor" );
		    lynx::addInstrumentor(new ClockCycleCountInstrumentor());			
	    }
	
	    if(configuration.memoryEfficiency)
	    {
	        report( "Creating memory efficiency instrumentor" );
	        lynx::addInstrumentor(new WarpInstrumentor(
	        instrumentation::WarpInstrumentor::memoryEfficiency));
	    }
	
	    if(configuration.branchDivergence)
	    {
	        report( "Creating branch divergence instrumentor" );
	        lynx::addInstrumentor(new WarpInstrumentor(
	        instrumentation::WarpInstrumentor::branchDivergence));
	    }
	    
	    if(configuration.activityFactor)
	    {
	        report( "Creating activity factor instrumentor" );
	        lynx::addInstrumentor(new WarpInstrumentor(
	        instrumentation::WarpInstrumentor::activityFactor));
	    }
	
	    if(configuration.warpInstructionCount)
	    {
	        report( "Creating warp instruction count instrumentor" );
	        lynx::addInstrumentor(new WarpInstrumentor(
	        instrumentation::WarpInstrumentor::instructionCount));
	    }
	    if(configuration.barrierCount)
	    {
	        report( "Creating barrier count instrumentor" );
	        lynx::addInstrumentor(new WarpInstrumentor(
	        instrumentation::WarpInstrumentor::barrierCount));
	    }
	
	    if(configuration.threadInstructionCount)
	    {
	        report( "Creating thread instruction count instrumentor" );
	        lynx::addInstrumentor(new BasicBlockInstrumentor(
	        instrumentation::BasicBlockInstrumentor::instructionCount));
	    }
	
	    if(configuration.basicBlockExecutionCount)
	    {
	        report( "Creating basic block execution count instrumentor" );
	        lynx::addInstrumentor(new BasicBlockInstrumentor(
	        instrumentation::BasicBlockInstrumentor::executionCount));
	    }
	    
	    for(PTXInstrumentorVector::iterator instrumentor = instrumentors.begin();
	        instrumentor != instrumentors.end(); ++instrumentor)
	    {
	        (*instrumentor)->iterations = configuration.iterations;
	        
	        for(PTXInstrumentor::KernelVector::const_iterator kernel = 
	            configuration.kernelsToInstrument.begin(); 
	            kernel != configuration.kernelsToInstrument.end();
	            ++kernel)
	        {
	            (*instrumentor)->kernelsToInstrument.push_back(*kernel);
	        }     
	    }    
    }

    InstrumentationRuntime::InstrumentationConfiguration::InstrumentationConfiguration()
    : 
    clockCycleCount(false),
    memoryEfficiency(false),
    branchDivergence(false),
    activityFactor(false),
    threadInstructionCount(false),
    warpInstructionCount(false),
    barrierCount(false),
    basicBlockExecutionCount(false)
    {
    
        std::ifstream stream("configure.lynx");
        hydrazine::json::Parser parser;
	    hydrazine::json::Object* object = 0;
   
		try {
		        
	        object = parser.parse_object(stream);

	        hydrazine::json::Visitor mainConfig(object);
	        hydrazine::json::Visitor instrumentConfig = mainConfig["instrument"];
	        

	        if(!instrumentConfig.is_null())
	        {
	        
	            log = instrumentConfig.parse<bool>("log", false);   
	            logfile = instrumentConfig.parse<std::string>("logfile", "");   
	            logKernelInfo = instrumentConfig.parse<bool>("logKernelInfo", false);   

                hydrazine::json::Visitor kernels = instrumentConfig["kernels"];

                if (!kernels.is_null()) {
	                hydrazine::json::Array *array = 
		                static_cast<hydrazine::json::Array *>(kernels.value);
	
	                for (hydrazine::json::Array::ValueVector::iterator it = array->begin();
		                it != array->end(); ++it) {
		                hydrazine::json::Visitor k(*it);
		                kernelsToInstrument.push_back((std::string)k);
	                }
                }
        
                iterations = instrumentConfig.parse<int>("iterations", -1);   

                clockCycleCount = instrumentConfig.parse<bool>("clockCycleCount", false);
                memoryEfficiency = instrumentConfig.parse<bool>("memoryEfficiency", false);
                branchDivergence = instrumentConfig.parse<bool>("branchDivergence", false);
		        activityFactor = instrumentConfig.parse<bool>("activityFactor", false);
		        warpInstructionCount = instrumentConfig.parse<bool>("warpInstructionCount", false);
		        barrierCount = instrumentConfig.parse<bool>("barrierCount", false);
		        threadInstructionCount = instrumentConfig.parse<bool>("threadInstructionCount", false);
		        basicBlockExecutionCount = instrumentConfig.parse<bool>("basicBlockExecutionCount", false);
		
	        }
	    } catch (std::exception exp) {
	        std::cerr << "==LYNX== WARNING: Could not parse config file 'configure.lynx'.\n" << std::endl;
        }          

	    delete object;
    }

    InstrumentationRuntime::~InstrumentationRuntime()
    {
        int err = mq_close(messageQueue);
        if(err < 0)
            report( "Failed to close message queue" );
            
        lynx::clearInstrumentors();
        instrumentationContexts.clear();       
    }

}

#endif

