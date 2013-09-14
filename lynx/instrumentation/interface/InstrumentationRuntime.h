/*! \file   InstrumentationRuntime.h
	\author Naila Farooqui <naila@cc.gatech.edu>
	\date   Tuesday November 22, 2011
	\brief  The header file for the InstrumentationRuntime class.
*/

#ifndef INSTRUMENTATION_RUNTIME_H_INCLUDED
#define INSTRUMENTATION_RUNTIME_H_INCLUDED

#include <lynx/instrumentation/interface/InstrumentationContext.h>
#include <lynx/instrumentation/interface/PTXInstrumentor.h>

#include <lynx/trace/interface/Profiler.h>

#include <boost/thread/thread.hpp>

#include <mqueue.h>

namespace instrumentation
{
	/*! \brief A singleton used to create/manage instances of instrumentors */
	class InstrumentationRuntime
	{
	
	class InstrumentationConfiguration
	{
	
	    public:
		    
	        bool clockCycleCount;
		    bool memoryEfficiency;
		    bool branchDivergence;
		    bool activityFactor;
		    bool threadInstructionCount;
		    bool warpInstructionCount;
		    bool barrierCount;
		    bool basicBlockExecutionCount;
	
	    public:
		    InstrumentationConfiguration();

		    //! \brief name of log file for instrumentation data
            std::string logfile;
            bool log;
            bool logKernelInfo;
			
			int iterations;
			instrumentation::PTXInstrumentor::KernelVector kernelsToInstrument;        
    };
    		
	public:
	    static InstrumentationRuntime Singleton;
		InstrumentationConfiguration configuration;

	public:
    
        InstrumentationRuntime();
        ~InstrumentationRuntime();
    
        typedef std::map<boost::thread::id, InstrumentationContext> InstrumentationContextMap;
    
        //! instrumentation context map
        InstrumentationContextMap instrumentationContexts;
        //! set of instrumentors to be inserted into kernels 
        PTXInstrumentorVector instrumentors;
        //! check if active instrumentor has been toggled (if so, we need to reload module)
        bool toggledActiveInstrumentor;
        //! associated profiler
        trace::Profiler profiler;
    
        //! \brief message queue descriptor
        mqd_t messageQueue;    
	};
}

#endif


