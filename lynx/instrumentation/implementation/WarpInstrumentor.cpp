/*! \file WarpInstrumentor.cpp
	\date Monday July 30, 2011
	\author Naila Farooqui <naila@cc.gatech.edu>
	\brief The source file for the WarpInstrumentor class.
*/

#ifndef WARP_REDUCTION_INSTRUMENTOR_CPP_INCLUDED
#define WARP_REDUCTION_INSTRUMENTOR_CPP_INCLUDED

#include <lynx/instrumentation/interface/WarpInstrumentor.h>
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

#ifdef REPORT_BASE
#undef REPORT_BASE
#endif

// whether debugging messages are printed
#define REPORT_BASE 0

using namespace hydrazine;

namespace instrumentation
{

    bool WarpInstrumentor::validate() {
        return true;
    }

    void WarpInstrumentor::analyze(ir::Module &module) {

       for (ir::Module::KernelMap::const_iterator kernel = module.kernels().begin(); 
	        kernel != module.kernels().end(); ++kernel) 
       {
	        
            //std::cout << "kernel: " << kernel->first << std::endl;        

            ir::ControlFlowGraph::BlockPointerVector sequence =
                    kernel->second->cfg()->reverse_topological_sequence();
            for(ir::ControlFlowGraph::BlockPointerVector::iterator block = sequence.begin();
                            block != sequence.end(); ++block)
            {
                if(!(*block)->instructions.size()) continue;

                for(ir::ControlFlowGraph::BasicBlock::InstructionList::reverse_iterator 
                    instruction = (*block)->instructions.rbegin(); instruction != 
                    (*block)->instructions.rend(); ++instruction)
                {
                    ir::PTXInstruction *ptxInstruction = ((ir::PTXInstruction *)*instruction);
                    //std::cout << ptxInstruction->toString() << std::endl;
                    if(ptxInstruction->addressSpace == ir::PTXInstruction::Global 
                        && ptxInstruction->opcode == ir::PTXInstruction::Ld)
                    {
                        
                        std::set<std::string> registerSet;
                        registerSet.insert(ptxInstruction->a.toString());
                        flowMap.insert(std::make_pair(ptxInstruction->toString(), registerSet));
                    }
                    else if(ptxInstruction->addressSpace == ir::PTXInstruction::Global 
                        && ptxInstruction->opcode == ir::PTXInstruction::St)
                    {
                        std::set<std::string> registerSet;
                        registerSet.insert(ptxInstruction->d.toString());
                        flowMap.insert(std::make_pair(ptxInstruction->toString(), registerSet));
                    }
                    else
                    {
                        //iterate through registerSets in flowMap
                        for(InformationFlowMap::iterator globalMemOp = flowMap.begin();
                            globalMemOp != flowMap.end(); ++globalMemOp)
                        {
                            std::set<std::string>::iterator toErase = globalMemOp->second.end();
                            for(std::set<std::string>::iterator reg = globalMemOp->second.begin();
                                reg != globalMemOp->second.end(); ++reg)
                            {  
                                if(ptxInstruction->d.toString().compare(*reg) == 0) {
                                    toErase = reg;
        
                                    if(ptxInstruction->addressSpace == ir::PTXInstruction::Param 
                                        && ptxInstruction->opcode == ir::PTXInstruction::Ld) {
                                        globalMemOp->second.insert(ptxInstruction->a.toString());
                                    }
                                    else {     

                                        if(ptxInstruction->a.addressMode == ir::PTXOperand::Register)
                                            globalMemOp->second.insert(ptxInstruction->a.toString());
                                        if(ptxInstruction->b.addressMode == ir::PTXOperand::Register)
                                            globalMemOp->second.insert(ptxInstruction->b.toString());
                                        if(ptxInstruction->c.addressMode == ir::PTXOperand::Register) 
                                            globalMemOp->second.insert(ptxInstruction->a.toString()); 
                                    }                                                                      
                                }
                            }
                            
                            if(toErase != globalMemOp->second.end())
                                globalMemOp->second.erase(toErase);
                        }
                        
                    }
                }
            }
        }

        /*
        for(InformationFlowMap::iterator globalMemOp = flowMap.begin();
            globalMemOp != flowMap.end(); ++globalMemOp)
        {
            std::cout << globalMemOp->first << ":" << std::endl;
            for(std::set<std::string>::iterator reg = globalMemOp->second.begin();
                reg != globalMemOp->second.end(); ++reg)
                std::cout << *reg << "\t";
            std::cout << std::endl;
        }
        */
    }


    void WarpInstrumentor::initialize() {
        
        counter = 0;

        warpCount = (threads * threadBlocks)/32;
        
        if(warpCount == 0)
            warpCount = 1;

        unsigned long size = entries * warpCount;
        
        if(cudaMalloc((void **) &counter, size * sizeof(size_t)) != cudaSuccess){
            throw hydrazine::Exception(
            "Could not allocate sufficient memory on device (cudaMalloc failed)");
        }
        if(cudaMemset( counter, 0, size * sizeof(size_t)) != cudaSuccess){
            throw hydrazine::Exception( "cudaMemset failed!" );
        }
        
        if(cudaMemcpyToSymbol(symbol.c_str(), &counter, sizeof(size_t *), 0, 
            cudaMemcpyHostToDevice) != cudaSuccess) {
            throw hydrazine::Exception( "cudaMemcpyToSymbol failed!");
        }
    }

    std::string WarpInstrumentor::specificationPath() {
        
        passes.clear();
        std::string resource;

        switch(type){
            case memoryEfficiency:
            {
                resource = "resources/memoryEfficiency.c";
                _profile.type = MEM_EFFICIENCY;
               
                entries = 2;
            }
            break;
            case branchDivergence:
            {
                resource = "resources/branchDivergence.c";
                _profile.type = BRANCH_DIVERGENCE;
                
                entries = 2;
            }
            break;
            case activityFactor:
            {
                resource = "resources/activityFactor.c";
                entries = 2;
            }   
            break;
            case instructionCount:
            {
                entries = 1;
                resource = "resources/warpInstructionCount.c";
                _profile.type = INST_COUNT;
            }
            break;
            case barrierCount:
            {
                entries = 1;
                resource = "resources/barrierCount.c";
                _profile.type = INST_COUNT;
            }
            break;
            default:
            {
                throw hydrazine::Exception("No instrumentation type specified!");
            }    
            break;
        }

        return resource;
    }

    void WarpInstrumentor::extractResults(std::ostream *out) {

        unsigned long size = entries * warpCount;
        
        size_t *info = new size_t[size];
        if(counter) {
            cudaMemcpy(info, counter, size * sizeof( size_t ), 
                cudaMemcpyDeviceToHost);
            cudaFree(counter);
        }

        switch(type)
        {
        
            case memoryEfficiency:
            {
            
                unsigned int dynamicWarps = 0;
                unsigned int memTransactions = 0;
                
                for(unsigned int i = 0; i < warpCount; i++)
                {
                    memTransactions += info[i * entries];
                    dynamicWarps += info[i * entries + 1];
                }

                unsigned int dynamicHalfWarps = dynamicWarps * 2;
                
                lynx::getProfiler()->updateCounter(kernelName, 
                    trace::Profiler::KernelProfiler::GLOBAL_MEM_TRANSACTIONS,
                    memTransactions);
                    
                lynx::getProfiler()->updateCounter(kernelName, 
                    trace::Profiler::KernelProfiler::DYNAMIC_HALF_WARPS_EXEC_MEM_TRANSACTIONS,
                    dynamicWarps); 
                
                _profile.data.memory_efficiency = ((double)dynamicHalfWarps/
                    (double)memTransactions) * 100 ;
              
            }
            break;
            case branchDivergence:
            {
                unsigned int divergentBranches = 0;
                unsigned int totalBranches = 0;
                
                for(unsigned int i = 0; i < warpCount; i++)
                {
                    divergentBranches += info[i * entries];
                    totalBranches += info[i * entries + 1];
                }
            
                lynx::getProfiler()->updateCounter(kernelName, 
                    trace::Profiler::KernelProfiler::BRANCHES, 
                    totalBranches);
                lynx::getProfiler()->updateCounter(kernelName, 
                    trace::Profiler::KernelProfiler::DIVERGENT_BRANCHES, 
                    divergentBranches);
            
                _profile.data.branch_divergence = ((double)divergentBranches/
                    (double)totalBranches) * 100;
            }
            break;
            case activityFactor:
            {
                unsigned int maximumThreads = 0; 
                unsigned int activeThreads = 0;
                
                unsigned int threadsPerWarp = 32;
                if(threads < threadsPerWarp) threadsPerWarp = threads;
                
                for(unsigned int i = 0; i < warpCount; i++)
                {
                    activeThreads += info[i * 2];
                    maximumThreads += info[(i * 2) + 1];
                }
                
                report("activeThreads: " << activeThreads << 
                    ", maxThreads: " << maximumThreads);
                
                lynx::getProfiler()->updateCounter(kernelName, 
                    trace::Profiler::KernelProfiler::MAX_THREADS,
                        maximumThreads);
            
                lynx::getProfiler()->updateCounter(kernelName, 
                    trace::Profiler::KernelProfiler::ACTIVE_THREADS,
                        activeThreads);            
            }
            break;
            case instructionCount:
            {
                unsigned int instructionCount = 0;
                for(unsigned int i = 0; i < warpCount; i++)
                    instructionCount += info[i];
                
                lynx::getProfiler()->updateCounter(kernelName, 
                    trace::Profiler::KernelProfiler::INST_COUNT, 
                    instructionCount);
                
                _profile.data.instruction_count = instructionCount;
            }                    
            break;
            case barrierCount: 
            {
                unsigned int instructionCount = 0;
                for(unsigned int i = 0; i < warpCount; i++)
                    instructionCount += info[i];
                
                lynx::getProfiler()->updateCounter(kernelName, 
                    trace::Profiler::KernelProfiler::BARRIERS, 
                    instructionCount);
            
            }
            break;
        }

        sendKernelProfile(InstrumentationRuntime::Singleton.messageQueue);

        if(info)
            delete[] info;
            
    }

    WarpInstrumentor::WarpInstrumentor() : entries(2)
    {
        description = "Warp Instrumentor";
    }
    
    WarpInstrumentor::WarpInstrumentor(InstrumentationType type) 
    : type(type), entries(2)
    {
        description = "Warp Instrumentor";
    }

}

#endif
