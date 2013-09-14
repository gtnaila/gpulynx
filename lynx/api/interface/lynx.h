/*! \file   lynx.h
	\author Naila Farooqui <naila@cc.gatech.edu>
	\date   Sunday October 14, 2012
	\brief  The header file for the Lynx API functions.
*/

#ifndef LYNX_H_INCLUDED
#define LYNX_H_INCLUDED

#include <string>
#include <vector>

#include <lynx/trace/interface/Profiler.h>

//Forward Declarations
namespace instrumentation
{
    class PTXInstrumentor;
    class KernelProfile;
}

namespace ir
{
    class Module;
}

namespace lynx
{
    typedef std::vector< instrumentation::PTXInstrumentor *> PTXInstrumentorVector;

    void initialize();
    void finalize();

    void addInstrumentor(instrumentation::PTXInstrumentor * instrumentor);
    void clearInstrumentors();
    PTXInstrumentorVector *getConfiguredInstrumentors();
    bool instrumentorsConfigured();
    
    void instrument(ir::Module & module);
    
    void initializeKernelLaunch(std::string kernelName, unsigned int threads, unsigned int threadBlocks);
    void finalizeKernelLaunch();
    
    instrumentation::PTXInstrumentor *getInstrumentor();
    void resetInstrumentor(instrumentation::PTXInstrumentor *instrumentor);
    
    bool validateInstrumentor(std::string moduleName, std::string kernelName = "");
    
    bool getInstrumentorSwitch();
    void setInstrumentorSwitch(bool toggled);
    
    trace::Profiler *getProfiler();
    trace::Profiler::KernelProfiler *getKernelProfiler(std::string kernelName);
    
}

#endif
