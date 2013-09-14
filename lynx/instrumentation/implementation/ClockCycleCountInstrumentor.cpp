/*! \file ClockCycleCountInstrumentor.cpp
	\date Monday November 15, 2010
	\author Naila Farooqui <naila@cc.gatech.edu>
	\brief The source file for the ClockCycleCountInstrumentor class.
*/

#ifndef CLOCK_CYCLE_COUNT_INSTRUMENTOR_CPP_INCLUDED
#define CLOCK_CYCLE_COUNT_INSTRUMENTOR_CPP_INCLUDED

#include <lynx/instrumentation/interface/ClockCycleCountInstrumentor.h>
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
#include <hydrazine/interface/json.h>

#include <mqueue.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <fstream>

#ifdef REPORT_BASE
#undef REPORT_BASE
#endif

#define REPORT_BASE 0

using namespace hydrazine;

namespace instrumentation
{

    bool ClockCycleCountInstrumentor::validate() {
        return true;
    }

    void ClockCycleCountInstrumentor::analyze(ir::Module &module) {
        /* No static analysis necessary for this instrumentation */
    }

    void ClockCycleCountInstrumentor::initialize() {

        clock_sm_info = 0;
        report("threadBlocks: " << threadBlocks);

        cudaMalloc((void **) &clock_sm_info, 2 * threadBlocks * sizeof(size_t));
        cudaMemset( clock_sm_info, 0, 2 * threadBlocks * sizeof( size_t ));
        cudaMemcpyToSymbol(symbol.c_str(), &clock_sm_info, sizeof(size_t *), 0, 
            cudaMemcpyHostToDevice);
    }            
    
    std::string ClockCycleCountInstrumentor::specificationPath() 
    {
        return "resources/clockCycleCount.c";
    }

    void ClockCycleCountInstrumentor::extractResults(std::ostream *out) {
            
        size_t *info = new size_t[2 * threadBlocks];
        
        if(clock_sm_info) {
            cudaMemcpy(info, clock_sm_info, 2 * threadBlocks * sizeof( size_t ), 
                cudaMemcpyDeviceToHost);      
            cudaFree(clock_sm_info);
        }

        struct cudaDeviceProp properties;
        cudaGetDeviceProperties(&properties, 0);

        std::vector<size_t> threadBlockInfo;
        threadBlockInfo.resize(2, 0);

        size_t smid = 0;
        lynx::getKernelProfiler(kernelName)->processorToThreadBlockCount.clear();
        lynx::getKernelProfiler(kernelName)->threadBlockToProcessor.clear();
        lynx::getKernelProfiler(kernelName)->processorToClockCycles.clear();
        
        for(size_t i = 0; i < threadBlocks; i++) {
            smid = info[i*2+1];
            threadBlockInfo[0] = info[i*2];
            threadBlockInfo[1] = smid;
            lynx::getKernelProfiler(kernelName)->processorToThreadBlockCount[smid]++;
            lynx::getKernelProfiler(kernelName)->processorToClockCycles[smid] += info[i*2];
            lynx::getKernelProfiler(kernelName)->threadBlockToProcessor[i] = threadBlockInfo;        
        } 

        std::vector<double> clockCyclesPerSM;
        clockCyclesPerSM.clear();

        for(trace::Profiler::KernelProfiler::ProcessorToClockCyclesMap::
            const_iterator it = lynx::getKernelProfiler(kernelName)->processorToClockCycles.begin();
            it != lynx::getKernelProfiler(kernelName)->processorToClockCycles.end(); ++it) {
            clockCyclesPerSM.push_back(it->second);
        }

        lynx::getKernelProfiler(kernelName)->runtime = 
            *(std::max_element(clockCyclesPerSM.begin(), 
                clockCyclesPerSM.end()))/properties.clockRate;
        
        _profile.type = KERNEL_RUNTIME;
        _profile.data.kernel_runtime = lynx::getKernelProfiler(kernelName)->runtime;
        
        int err = sendKernelProfile(InstrumentationRuntime::Singleton.messageQueue);
        if(err < 0)
            report("Unable to send kernel profile");
    
        if(info)
            delete[] info;
     
    }

    ClockCycleCountInstrumentor::ClockCycleCountInstrumentor() {
        description = "Clock Cycles and SM (Processor) ID";
    }

}

#endif
