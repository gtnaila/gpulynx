/*!
	\file Profiler.h
	\author Naila Farooqui <naila@cc.gatech.edu>
	\date November 9, 2012
	\brief accumulates performance/measurement "counters" for various events, 
	    such as time spent in data movement, kernel execution, etc
*/

#ifndef TRACE_PROFILER_H_INCLUDED
#define TRACE_PROFILER_H_INCLUDED

// Hydrazine includes
#include <hydrazine/interface/Timer.h>

#include <map>
#include <ostream>
#include <vector>

namespace trace {
	class Profiler {
	
	public:
	
	    class KernelProfiler {
	    
	        public:
	       
	            enum CounterType {
	                BRANCHES,
	                DIVERGENT_BRANCHES,
	                GLOBAL_MEM_TRANSACTIONS,
	                DYNAMIC_HALF_WARPS_EXEC_MEM_TRANSACTIONS,
	                BARRIERS,
	                INST_COUNT,
	                MAX_THREADS,
	                ACTIVE_THREADS,
	                WARPS
	            };
	       
	            /*! \brief Maps CTA->SM */
                typedef std::map<size_t, std::vector<size_t>> ThreadBlockToProcessorMap;

                /*! \brief Maps number of CTAs executed on each SM */
                typedef std::map<size_t, size_t> ProcessorToThreadBlockCountMap;
            
                /*! \brief Maps SM ID to total number of clock cycles */
                typedef std::map<size_t, size_t> ProcessorToClockCyclesMap;

                /*! \brief Maps Basic Block ID to total number of basic block execution */
                typedef std::map<size_t, size_t> BasicBlockToExecCountMap;
	       
	            
	            double kernelExecute;
	            double runtime;
	            
	            unsigned long instructionCount;
	            unsigned long branches;
	            unsigned long divergentBranches;
	            unsigned long globalMemTransactions;
	            unsigned long dynamicHalfWarpsExecutingMemTransactions;
	            unsigned long barriers;
	            unsigned long maxThreads;
	            unsigned long activeThreads;
	            unsigned long warps;
	            
	            ThreadBlockToProcessorMap threadBlockToProcessor;
	            ProcessorToThreadBlockCountMap processorToThreadBlockCount;
	            ProcessorToClockCyclesMap processorToClockCycles;
	            BasicBlockToExecCountMap basicBlockToExecCount;
	            
	            KernelProfiler(): 
	                kernelExecute(0),
	                runtime(0),
	                instructionCount(0),
	                branches(0),
	                divergentBranches(0),
	                globalMemTransactions(0),
	                dynamicHalfWarpsExecutingMemTransactions(0),
	                barriers(0),
	                maxThreads(0),
	                activeThreads(0),
	                warps(0)
	            { }
	            
	            void updateCounter(CounterType type, unsigned long counter);
	            void updateRuntime(double r);
	            void write(std::ostream *out);
	    };
	
	    typedef std::map<std::string, KernelProfiler> KernelProfilerMap;
	
		Profiler();
		~Profiler();
		
		//! starts a timer
		void startTimer();
		void startAppTimer();
		
		//! stops the timer and adds time to a selected accumulator
		void stopTimer(double Profiler::* accumulator);
		void stopAppTimer(double Profiler::* appTime);
		void stopKernelTimer(double Profiler::* accumulator, std::string kernelName = "");
		
		void updateCounter(std::string kernelName, 
		    KernelProfiler::CounterType type, unsigned long counter);
		void updateRuntime(std::string kernelName, double r);    
	
	private:
		hydrazine::Timer timer;
		hydrazine::Timer appTimer;
		
	public:
		//! accumulates time spent moving data from host to device and back
		double dataMove;
		
		//! size (in bytes) of data transferred to/from device
		unsigned long dataMoveSize;
		
		//! captures total application execution time
		double appExecute;
		//! accumulates time spent executing PTX kernels
		double kernelsExecute;
		double runtime;
		
		//! counters
		unsigned long branches;
		unsigned long divergentBranches;
		unsigned long globalMemTransactions;
		unsigned long dynamicHalfWarpsExecutingMemTransactions;
		unsigned long barriers;
		unsigned long instructionCount;
		unsigned long maxThreads;
		unsigned long activeThreads;
		 unsigned long warps;
		
		//! maintain per-kernel counter information
		KernelProfilerMap kernelProfilers;
	};

}
#endif

