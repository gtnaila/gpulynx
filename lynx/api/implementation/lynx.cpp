/*! \file lynx.cpp
	\date Sunday October 14, 2012
	\author Naila Farooqui <naila@cc.gatech.edu>
	\brief The source file for the Lynx API.
*/

#ifndef LYNX_CPP_INCLUDED
#define LYNX_CPP_INCLUDED

#include <lynx/api/interface/lynx.h>
#include <lynx/instrumentation/interface/InstrumentationRuntime.h>
#include <lynx/instrumentation/interface/InstrumentationContext.h>

#include <boost/thread/thread.hpp>

#include <map>

#ifdef REPORT_BASE
#undef REPORT_BASE
#endif

#define REPORT_BASE 0

namespace lynx
{

    static instrumentation::InstrumentationRuntime::InstrumentationContextMap::iterator get() {
		instrumentation::InstrumentationRuntime::InstrumentationContextMap::iterator context = 
		    instrumentation::InstrumentationRuntime::Singleton.instrumentationContexts.find(
		boost::this_thread::get_id());
	
		assert(context != instrumentation::InstrumentationRuntime::Singleton.instrumentationContexts.end());

	    return context;    		    
	}

    void initialize()
    {
        instrumentation::InstrumentationRuntime::InstrumentationContextMap::iterator context = 
		    instrumentation::InstrumentationRuntime::Singleton.instrumentationContexts.find(
		boost::this_thread::get_id());
		
		if(context == instrumentation::InstrumentationRuntime::Singleton.instrumentationContexts.end())
        {
            instrumentation::InstrumentationRuntime::Singleton.instrumentationContexts.
                insert(std::make_pair(boost::this_thread::get_id(), instrumentation::InstrumentationContext()));
        }    
        
        if(instrumentation::InstrumentationRuntime::Singleton.instrumentors.size() > 0)
        {
            get()->second.setActiveInstrumentor(
                *(instrumentation::InstrumentationRuntime::Singleton.instrumentors.begin()));  
        }
        
    }

    void clearInstrumentors()
    {
        instrumentation::InstrumentationRuntime::Singleton.instrumentors.clear();
	}
    
    void finalize()
    {
    }

    void addInstrumentor( instrumentation::PTXInstrumentor * instrumentor)
	{
	    report("adding instrumentor ...");
	    instrumentation::InstrumentationRuntime::Singleton.instrumentors.push_back(instrumentor);
    }
    
	PTXInstrumentorVector *getConfiguredInstrumentors()
	{
	    return &instrumentation::InstrumentationRuntime::Singleton.instrumentors;
	}
	
	instrumentation::PTXInstrumentor *getInstrumentor()
	{
	    return get()->second.getActiveInstrumentor();
	}
	
	void resetInstrumentor(instrumentation::PTXInstrumentor *instrumentor)
	{
	    get()->second.setActiveInstrumentor(instrumentor);
	}
	
	bool validateInstrumentor(std::string moduleName, std::string kernelName)
	{
        bool passed = false;
        
	    instrumentation::PTXInstrumentor *instrumentor = getInstrumentor();
	
	    if(!instrumentor)
	        return passed;

	    instrumentor->kernelName = kernelName;
	    
	    if(instrumentor->conditionsMet())
	    {
	        if(!instrumentor->on)
                get()->second.toggled = true;	            
    	        
            instrumentor->on = true;
	        passed = true;
	    }
	    else
	    {
	        if(instrumentor->on)
            {
                instrumentor->on = false;
                get()->second.toggled = true;     
            }
	    }
	    
	    resetInstrumentor(instrumentor);
	    report("validation passed: " << passed);
	    return passed;
	}
	
    bool getInstrumentorSwitch()
    {
        return get()->second.toggled;
    }
    
    void setInstrumentorSwitch(bool toggled)
    {
        get()->second.toggled = toggled;
    }
    
    void instrument(ir::Module & module) 
    {
        instrumentation::PTXInstrumentor *activeInstrumentor = getInstrumentor();
        
        report("instrument: checking if active ...");
        if(activeInstrumentor && activeInstrumentor->on)
        {
            report("analyzing and instrumenting module ...");
            activeInstrumentor->analyze(module);
            activeInstrumentor->instrument(module);       
        }        
    }
    
    void initializeKernelLaunch(std::string kernelName, unsigned int threads, unsigned int threadBlocks)
    {
        report("initializing kernel launch ...");
        instrumentation::PTXInstrumentor *instrumentor = getInstrumentor();
        if(instrumentor && instrumentor->on)
        {
            instrumentor->kernelName = kernelName;
            instrumentor->threads = threads;
            instrumentor->threadBlocks = threadBlocks;         
            instrumentor->initialize();
        }    
    }
    
    void finalizeKernelLaunch()
    {
        instrumentation::PTXInstrumentor *instrumentor = getInstrumentor();
        
        if(instrumentor && instrumentor->on)
            instrumentor->finalize();
    }

    trace::Profiler *getProfiler()
    {
        return &(instrumentation::InstrumentationRuntime::Singleton.profiler);
    }
    
    trace::Profiler::KernelProfiler *getKernelProfiler(std::string kernelName)
    {
        trace::Profiler::KernelProfilerMap::iterator found = 
            instrumentation::InstrumentationRuntime::Singleton.profiler.
                kernelProfilers.find(kernelName);
    
        if(found == instrumentation::InstrumentationRuntime::Singleton.profiler.
            kernelProfilers.end())
            instrumentation::InstrumentationRuntime::Singleton.profiler.
                kernelProfilers.insert(std::make_pair(
                kernelName, trace::Profiler::KernelProfiler()));
    
        return &(instrumentation::InstrumentationRuntime::Singleton.
            profiler.kernelProfilers[kernelName]);
    }

}

#endif
