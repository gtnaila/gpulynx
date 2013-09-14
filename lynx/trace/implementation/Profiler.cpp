/*!
	\file Profiler.cpp
	\author Naila Farooqui <naila@cc.gatech.edu>
	\date November 9, 2012
	\brief accumulates performance/measurement "counters" for various events, 
	    such as time spent in data movement, kernel execution, etc
*/

#include <lynx/trace/interface/Profiler.h>
#include <lynx/instrumentation/interface/InstrumentationRuntime.h>

#include <iostream>
#include <fstream>
#include <ostream>

#ifdef REPORT_BASE
#undef REPORT_BASE
#endif

#define REPORT_BASE 0

namespace trace {

void Profiler::KernelProfiler::updateCounter(
    Profiler::KernelProfiler::CounterType type, 
    unsigned long counter) {
 
    switch(type) {
        case BRANCHES:
        {
            this->branches = counter;
        }
        break;
        case DIVERGENT_BRANCHES:
        {
            this->divergentBranches = counter;
        }
        break;
        case GLOBAL_MEM_TRANSACTIONS:
        {
            this->globalMemTransactions = counter;
        }
        break;
        case DYNAMIC_HALF_WARPS_EXEC_MEM_TRANSACTIONS:
        {
            this->dynamicHalfWarpsExecutingMemTransactions = (counter * 2);
        }
        break;
        case BARRIERS:
        {
            this->barriers = counter;
        }
        break;
        case INST_COUNT:
        {
            this->instructionCount = counter;
        }
        break;
        case MAX_THREADS:
        {
            this->maxThreads = counter;
        }
        break;
        case ACTIVE_THREADS:
        {
            this->activeThreads = counter;
        }
        break;
        case WARPS:
        {
            this->warps = counter;
        }
        break;
        default:
        break;   
    }       
}    

void Profiler::KernelProfiler::updateRuntime(double r)
{   
    runtime = r;
}

void Profiler::KernelProfiler::write(std::ostream *out) {

    struct {
	    const char *name;
	    unsigned long *ptr;
    } kernelProfilerMembers[] = {
	    { "branches", &branches },
		{ "divergentBranches", &divergentBranches},
		{ "globalMemTransactions", &globalMemTransactions},
		{ "dynamicHalfWarpsExecutingMemTransactions", &dynamicHalfWarpsExecutingMemTransactions},
		{ "barriers", &barriers},
		{ "activeThreads", &activeThreads},
		{ "maxThreads", &maxThreads},
		{ "warps", &warps},
		{ 0, 0 }  
	};

    *out << "\"kernelExecute\": " << kernelExecute << ", ";

    for (int i = 0; kernelProfilerMembers[i].ptr; ++i) {
        *out << "\"" << kernelProfilerMembers[i].name << "\"" << ":" << 
            *(kernelProfilerMembers[i].ptr);
        if(kernelProfilerMembers[i+1].ptr)
             *out << ", ";       
     }
}

Profiler::Profiler(): 
	dataMove(0), dataMoveSize(0), appExecute(0), kernelsExecute(0), runtime(0), 
	branches(0), divergentBranches(0), globalMemTransactions(0), 
	dynamicHalfWarpsExecutingMemTransactions(0),
	barriers(0), instructionCount(0), maxThreads(0), activeThreads(0),
	warps(0) {
}

Profiler::~Profiler() {
	
	struct {
		const char *name;
		double *ptr;
	} profilerMembers[] = {
		{ "dataMove", &dataMove },
		{ "appExecute", &appExecute},
		{ "kernelsExecute", &kernelsExecute},
		{ "runtime", &runtime},
		{ 0, 0 }
	};
	
	struct {
	    const char *name;
	    unsigned long *ptr;
    } counters[] = {
        { "dataMoveSize", &dataMoveSize },
        { "branches", &branches },
		{ "divergentBranches", &divergentBranches},
		{ "globalMemTransactions", &globalMemTransactions},
		{ "dynamicHalfWarpsExecutingMemTransactions", &dynamicHalfWarpsExecutingMemTransactions},
		{ "barriers", &barriers},
		{ "instructionCount", &instructionCount},
		{ "activeThreads", &activeThreads},
		{ "maxThreads", &maxThreads},
		{ "warps", &warps},
		{ 0, 0 }
    };	    
	
	report("log: " << instrumentation::InstrumentationRuntime::Singleton.configuration.log);
	report("appExecute: " << appExecute);
	if(instrumentation::InstrumentationRuntime::Singleton.configuration.log)
	{
	
	    std::ostream *out = NULL;
	    
	    if(instrumentation::InstrumentationRuntime::Singleton.configuration.logfile.empty())
	    {
	        out = &std::cout;
	    }
	    else 
	    {
	        out = new std::ofstream(
	            instrumentation::InstrumentationRuntime::Singleton.configuration.logfile, 
	            std::fstream::app);
	    }       
	    
	    *out << "{ ";
	
	    for(KernelProfilerMap::iterator kernelProfiler = kernelProfilers.begin();
	        kernelProfiler != kernelProfilers.end(); ++kernelProfiler)
        {
            branches += kernelProfiler->second.branches;
            divergentBranches += kernelProfiler->second.divergentBranches;
            globalMemTransactions += kernelProfiler->second.globalMemTransactions;
            dynamicHalfWarpsExecutingMemTransactions += 
                kernelProfiler->second.dynamicHalfWarpsExecutingMemTransactions;
            barriers += kernelProfiler->second.barriers; 
            instructionCount += kernelProfiler->second.instructionCount;
            activeThreads += kernelProfiler->second.activeThreads;
            maxThreads += kernelProfiler->second.maxThreads;
            warps += kernelProfiler->second.warps;
            runtime += kernelProfiler->second.runtime;
        
            if(instrumentation::InstrumentationRuntime::Singleton.configuration.logKernelInfo)
            {
                *out << "\"" << kernelProfiler->first << "\": {";
                kernelProfiler->second.write(out);
                *out << "}, ";
            }        
        }

        for (int i = 0; profilerMembers[i].ptr; ++i) {
	        *out << "\"" << profilerMembers[i].name << "\"" << ":" << 
	            *(profilerMembers[i].ptr) << ", ";
	    }
	
	    for (int i = 0; counters[i].ptr; ++i) {
	        *out << "\"" << counters[i].name << "\"" << ":" << *(counters[i].ptr);
	        if(counters[i+1].ptr)
	             *out << ", ";     
	    }
	
	    *out << "}\n";
	    
	    if(out != &std::cout && out != NULL)
	        delete(out);
	}
	
	kernelProfilers.clear();
	
}

//! starts a timer
void Profiler::startTimer() {
	timer.start();
}

void Profiler::startAppTimer() {
	appTimer.start();
}

void Profiler::stopAppTimer(double Profiler::* appTime) {
	appTimer.stop();
	this->*appTime = appTimer.seconds();
}

//! stops the timer and adds time to a selected accumulator
void Profiler::stopTimer(double Profiler::* accumulator) {
	timer.stop();
	this->*accumulator += timer.seconds();
}

//! stops the timer and adds time to a selected accumulator
void Profiler::stopKernelTimer(double Profiler::* accumulator,
    std::string kernelName) {
	timer.stop();

    KernelProfilerMap::iterator kernelProfiler = kernelProfilers.find(kernelName);
    if(kernelProfiler == kernelProfilers.end())
    {
        KernelProfiler newProfiler;
        newProfiler.kernelExecute = timer.seconds();
        kernelProfilers.insert(std::make_pair(kernelName, newProfiler));
    }
    else 
    {
        kernelProfiler->second.kernelExecute = timer.seconds();
    }

	this->*accumulator += timer.seconds();
}

void Profiler::updateCounter(std::string kernelName, KernelProfiler::CounterType type, 
    unsigned long counter) {
    
    KernelProfilerMap::iterator kernelProfiler = kernelProfilers.find(kernelName);
    if(kernelProfiler == kernelProfilers.end())
    {
        KernelProfiler newProfiler;
        newProfiler.updateCounter(type, counter);
        kernelProfilers.insert(std::make_pair(kernelName, newProfiler));
    }
    else 
    {
        kernelProfiler->second.updateCounter(type, counter);
    }    

}

void Profiler::updateRuntime(std::string kernelName, double r)
{
    KernelProfilerMap::iterator kernelProfiler = kernelProfilers.find(kernelName);
    if(kernelProfiler == kernelProfilers.end())
    {
        KernelProfiler newProfiler;
        newProfiler.updateRuntime(r);
        kernelProfilers.insert(std::make_pair(kernelName, newProfiler));
    }
    else 
    {
        kernelProfiler->second.updateRuntime(r);
    }    
}

}





