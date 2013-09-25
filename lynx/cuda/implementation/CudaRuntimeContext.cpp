/*! \file CudaRuntimeContext.cpp
	\date Friday June 22, 2012
	\author Naila Farooqui <naila@cc.gatech.edu>
	\brief The source file for the CUDA runtime context
*/

#include <lynx/cuda/interface/CudaRuntimeContext.h>
#include <lynx/cuda/interface/CudaRuntimeInterface.h>
#include <lynx/cuda/interface/CudaContext.h>

#include <cuda.h>

#include <boost/lexical_cast.hpp>
#include <boost/thread/locks.hpp>

#include <signal.h>
#include <stdio.h>
#include <iostream>

// Hydrazine includes
#include <hydrazine/interface/Exception.h>
#include <hydrazine/interface/string.h>
#include <hydrazine/interface/debug.h>

#ifdef REPORT_BASE
#undef REPORT_BASE
#endif

////////////////////////////////////////////////////////////////////////////////

// whether CUDA runtime catches exceptions thrown by Ocelot
#define CATCH_RUNTIME_EXCEPTIONS 0

// whether verbose error messages are printed
#define CUDA_VERBOSE 1

// whether debugging messages are printed
#define REPORT_BASE 0

// report all ptx modules
#define REPORT_ALL_PTX 0

////////////////////////////////////////////////////////////////////////////////

namespace cuda {

    static CudaRuntimeContext _instance;
    CudaRuntimeContext & CudaRuntimeContext::instance() {
        return _instance;
    }

    CudaContext & CudaRuntimeContext::context() {

        const unsigned device = currentDevice();
        boost::unique_lock<boost::mutex> lock(_mutex);

        assert(device < _deviceCount);
        CudaContext * context = _deviceContexts[device];
        HostThread * current = _threads.get();
        assert(current);

        if (!(context)) {
            context = cudaContextFactory(static_cast<int>(device), _deviceFlags);
            _deviceContexts[device] = context;
        } 
        else if (!(current->contextSetOnThread)) {
            CUresult ret = cuCtxSetCurrent(context->_cuContext);
            assert(ret == CUDA_SUCCESS);
            current->contextSetOnThread = true;
        }

        return *context;
    }

    const CudaContext & CudaRuntimeContext::context() const {
        const unsigned device = currentDevice();
        boost::unique_lock<boost::mutex> lock(_mutex);

        assert(device < _deviceCount);

        CudaContext * context = _deviceContexts[device];
        HostThread * current = _threads.get();
        assert(current);
        
        if (!(context)) {
            context = cudaContextFactory(static_cast<int>(device), _deviceFlags);
            _deviceContexts[device] = context;
        } 
        else if (!(current->contextSetOnThread)) {
            CUresult ret = cuCtxSetCurrent(context->_cuContext);
            assert(ret == CUDA_SUCCESS);
            current->contextSetOnThread = true;
        }

        return *context;
    }

    CudaRuntimeContext::~CudaRuntimeContext() {

        for(unsigned int i = 0; i < _deviceCount; i++)
        {
            CudaContext *ctx = _deviceContexts[i];
            if(ctx)
                delete ctx;
        }

        _deviceContexts.clear();
        _modules.clear();
        _kernels.clear();
        _textures.clear();
        _globals.clear();
    }

    CudaRuntimeContext::CudaRuntimeContext() {
        cuInit(0);

        int tmp;
        assert(cuDeviceGetCount(&tmp) == CUDA_SUCCESS && tmp >= 0);
        _deviceCount = static_cast<unsigned>(tmp);
        
        _deviceContexts.resize(_deviceCount, NULL);
        _deviceFlags = 0;
    }

    CudaRuntimeContext::HostThread::HostThread() : device(0),
        contextSetOnThread(false) { }

    CudaRuntimeContext::HostThread * CudaRuntimeContext::currentThread() {
        HostThread * current = _threads.get();
        if (!(current)) {
            current = new HostThread();
            _threads.reset(current);
        }

        return current;
    }

    const CudaRuntimeContext::HostThread * CudaRuntimeContext::currentThread() const {
        HostThread * current = _threads.get();
        if (!(current)) {
            current = new HostThread();
            _threads.reset(current);
        }

        return current;
    }

    unsigned CudaRuntimeContext::currentDevice() const {
        return currentThread()->device;
    }

    CudaContext * CudaRuntimeContext::cudaContextFactory(int device,
            unsigned int flags) const {
        return new CudaContext(const_cast<CudaRuntimeContext *>(this), device, flags);
    }

    
    void** CudaRuntimeContext::cudaRegisterFatBinary(void *fatCubin) 
    {
        size_t handle = 0;        
        boost::unique_lock<boost::mutex> lock(_mutex);
            
        handle = _fatBinaries.size();
	
	    FatBinaryMap::const_iterator fatbin = _fatBinaries.insert(std::make_pair(
		    handle,	FatBinaryContext(fatCubin))).first;
	
	    for (FatBinaryMap::const_iterator it = _fatBinaries.begin();
		    it != _fatBinaries.end(); ++it) {
		    if(fatbin == it) continue;
		
		    if (std::string(it->second.name()) == fatbin->second.name()) {
			    assert(0 && "binary already exists");		
			    return 0;
		    }	
	    }

	    // register associated PTX
	    ModuleMap::iterator module = _modules.insert(
		    std::make_pair(fatbin->second.name(), ir::Module())).first;
	    module->second.lazyLoad(fatbin->second.ptx(), fatbin->second.name());
	
	    report("Loading module (fatbin) - " << module->first);
	    reportE(REPORT_ALL_PTX, " with PTX\n" << fatbin->second.ptx());

        return (void **)handle;
    }

    void CudaRuntimeContext::cudaRegisterFunction(void **fatCubinHandle,
            const char *hostFun, char *deviceFun, const char *deviceName,
            int thread_limit, uint3 *tid, uint3 *bid, dim3 *bDim, dim3 *gDim,
            int *wSize) {
        boost::unique_lock<boost::mutex> lock(_mutex);

        size_t handle = (size_t)fatCubinHandle;

	        void *symbol = (void *)hostFun;
	        std::string kernelName = deviceFun;
	        std::string moduleName = _fatBinaries[handle].name();
	        
	        report("Registered kernel - " << kernelName 
		        << " in module '" << moduleName << "'"); 
	        _kernels[symbol] = RegisteredKernel(handle, moduleName, kernelName);
    }

    void CudaRuntimeContext::cudaRegisterTexture(void **fatCubinHandle,
            const struct textureReference *hostVar, const void **deviceAddress,
            const char *deviceName, int dim, int norm, int ext) {
       
            boost::unique_lock<boost::mutex> lock(_mutex);
        
            size_t handle = (size_t)fatCubinHandle;
            std::string moduleName = _fatBinaries[handle].name();
	        
	        report("cudaRegisterTexture('" << deviceName << ", dim: " << dim 
		        << ", norm: " << norm << ", ext: " << ext);
            
	        _textures[(void*)hostVar] = RegisteredTexture(moduleName, deviceName, norm);
        
    }

    void CudaRuntimeContext::cudaRegisterVar(void **fatCubinHandle,char *hostVar,
            char *deviceAddress, const char *deviceName, int ext, int size,
            int constant, int global) {

            boost::unique_lock<boost::mutex> lock(_mutex);

            
            report("cuda::CudaRuntimeContext::cudaRegisterVar() - host var: "
		    << (void *)hostVar << ", deviceName: " << deviceName << ", size: "
		    << size << " bytes," << (constant ? " constant" : " ")
		    << (global ? " global" : " "));
            
	        size_t handle = (size_t)fatCubinHandle;

	        std::string moduleName = _fatBinaries[handle].name();
	
	        _globals[(void *)hostVar] = RegisteredGlobal(moduleName, deviceName);
       
    }

    void CudaRuntimeContext::cudaUnregisterFatBinary(void **fatCubinHandle) {

    }

    cudaError_t CudaRuntimeContext::cudaDeviceReset() {

        boost::unique_lock<boost::mutex> lock(_mutex);

        const unsigned device = currentDevice();
        assert(device < _deviceCount);
        CudaContext *context = _deviceContexts[device];
        if(context)
        {
            delete context;
            _deviceContexts[device] = NULL;    
        }
        return CudaRuntimeInterface::cudaDeviceReset();
    }

    cudaError_t CudaRuntimeContext::cudaGetDevice(int *device) const {
        boost::unique_lock<boost::mutex> lock(_mutex);
        
        *device = static_cast<int>(currentDevice());
        return cudaSuccess;
    }

    cudaError_t CudaRuntimeContext::cudaGetDeviceCount(int *count) const {
        boost::unique_lock<boost::mutex> lock(_mutex);

        *count = static_cast<int>(_deviceCount);
        return cudaSuccess;
    }

    cudaError_t CudaRuntimeContext::cudaSetDevice(int device) {
        boost::unique_lock<boost::mutex> lock(_mutex);

        const unsigned udevice = static_cast<unsigned>(device);

        if (udevice >= _deviceCount) {
            return cudaErrorInvalidDevice;
        }
       
        HostThread * current = currentThread();
        current->device = udevice;

        if (current->contextSetOnThread) {
            CudaContext * ctx = _deviceContexts[udevice];
            if (ctx) {
                assert(cuCtxSetCurrent(ctx->_cuContext) == CUDA_SUCCESS);
            } 
            else {
                current->contextSetOnThread = false;
            }
        } 
        
        return cudaSuccess;
    }

    cudaError_t CudaRuntimeContext::cudaSetValidDevices(int *device_arr, int len)
    {
        cudaError_t ret = cudaErrorInvalidValue;
        
        if(len < 0 || device_arr == NULL)
            return ret;
        
        for(int i = 0; i < len; i++)
        {
            if((ret = cudaSetDevice(device_arr[i])) == cudaSuccess)
            {
                break;
            } 
        }
        
        return ret;    
    }

    cudaError_t CudaRuntimeContext::cudaSetDeviceFlags(unsigned int flags) {
        cudaError_t result = cudaErrorSetOnActiveProcess;

        boost::unique_lock<boost::mutex> lock(_mutex);
        
        const unsigned device = currentThread()->device;
        assert(device < _deviceCount);
        CudaContext  * context = _deviceContexts[device];

        if (!context) {
            _deviceFlags = flags;
            result = cudaSuccess;
        }
        
        return result;
    }

    cudaError_t CudaRuntimeContext::cudaThreadExit(void) {
        return cudaDeviceReset();
    }

    cudaError_t CudaRuntimeContext::cudaDeviceCanAccessPeer(int *canAccessPeer, int
            device, int peerDevice) {
        (void) canAccessPeer;
        (void) device;
        (void) peerDevice;
        return cudaErrorNotYetImplemented;
    }

    cudaError_t CudaRuntimeContext::cudaDeviceDisablePeerAccess(int peerDevice) {
        (void) peerDevice;
        return cudaErrorNotYetImplemented;
    }

    cudaError_t CudaRuntimeContext::cudaDeviceEnablePeerAccess(int peerDevice, unsigned
            int flags) {
        (void) peerDevice;
        (void) flags;
        return cudaErrorNotYetImplemented;
    }

    cudaError_t CudaRuntimeContext::cudaDeviceGetByPCIBusId(int *device,
            char *pciBusId) {
        (void) device;
        (void) pciBusId;
        return cudaErrorNotYetImplemented;
    }

    cudaError_t CudaRuntimeContext::cudaDeviceGetPCIBusId(
            char *pciBusId, int len, int device) {
        (void) pciBusId;
        (void) len;
        (void) device;
        return cudaErrorNotYetImplemented;
    }


}

