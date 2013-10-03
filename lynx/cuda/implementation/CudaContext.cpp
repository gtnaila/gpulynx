/*! \file CudaContext.cpp
	\date Friday June 22, 2012
	\author Naila Farooqui <naila@cc.gatech.edu>
	\brief The source file for the CUDA context 
*/

#include <lynx/api/interface/lynx.h>
#include <lynx/cuda/interface/CudaContext.h>
#include <lynx/cuda/interface/CudaRuntimeContext.h>
#include <lynx/cuda/interface/CudaRuntimeInterface.h>

#include <ocelot/transforms/interface/PassManager.h>
#include <ocelot/ir/interface/Module.h>

#include <boost/lexical_cast.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/thread/locks.hpp>
#include <boost/utility.hpp>

#include <cstdio>
#include <cstring>
#include <signal.h>
#include <sstream>

#include <cuda.h>

#include <hydrazine/interface/Exception.h>
#include <hydrazine/interface/string.h>
#include <hydrazine/interface/debug.h>

#include <lynx/api/interface/lynx.h>

#ifdef REPORT_BASE
#undef REPORT_BASE
#endif

// whether debugging messages are printed
#define REPORT_BASE 0

#define REPORT_INSTRUMENTED_PTX 1

namespace cuda {

    typedef CudaRuntimeContext _cudaRuntime;

    /* Utility method for loading CUDA modules and kernels on the device
        eagerly. No need to call this method if loading lazily, as is the
        default case.
    */
    void CudaContext::loadDevice() {
    
        for (CudaRuntimeContext::ModuleMap::iterator 
		        module = cudaRuntime()->_modules.begin(); 
		        module != cudaRuntime()->_modules.end();
		        ++module) 
            {
                if(!module->second.loaded()) 
                {
                    module->second.loadNow();
                }
    
                
                if(!_device->moduleLoaded(module->first)) 
                {
                    report("loading module on device");
                    _device->loadModule(&module->second);
                }

        }
        
        for (CudaRuntimeContext::RegisteredKernelMap::const_iterator 
		        kernel = cudaRuntime()->_kernels.begin(); 
		        kernel != cudaRuntime()->_kernels.end();
		        ++kernel) 
            {
                report("loading kernel - " << kernel->second.kernel << " - on device");
                if(!_device->kernelLoaded(kernel->second.kernel))
                    _device->loadKernel(kernel->second.kernel, kernel->second.module);
            }
    
    }

    CudaContext::CudaContext(CudaRuntimeContext * ctx, int deviceId,
            unsigned int flags) : _deviceId(deviceId),
            _cudaRuntime(ctx), _error(cudaSuccess)
        {

        report("creating CUDA context ...");
        assert(cuCtxCreate(&_cuContext, flags, deviceId) == CUDA_SUCCESS);
        report("getting CUDA Runtime Version ...");
        assert(CudaRuntimeInterface::cudaRuntimeGetVersion(&_runtimeVersion)
            == cudaSuccess);
            
        report("initializing CUDA device ...");
        _device = new CudaDevice(deviceId);              

        report("initializing lynx ...");    
        lynx::initialize();
        report("getting instrumentors ...");
        instrumentors = lynx::getConfiguredInstrumentors();
    }

    CudaContext::~CudaContext() {
        lynx::finalize();
        delete _device;
        (void) cuCtxDestroy(_cuContext);
    }

    cudaError_t CudaContext::cudaConfigureCall(dim3 gridDim, dim3 blockDim,
            size_t sharedMem, cudaStream_t stream) {
        boost::unique_lock<boost::mutex> lock(_mutex);
        cudaError_t result = cudaErrorInvalidConfiguration;
	
        KernelLaunchConfiguration launch(gridDim, blockDim, sharedMem, stream);
        launchConfigurations.push_back(launch);

        result = cudaSuccess;

        return setLastError(result);
    }

    void CudaContext::registerModule(ir::Module & module)
    {
        report("REGISTER-MODULE");
        if(module.loaded()) return;    
    
        report("loading module now");
        module.loadNow();
        report("instrumenting module");
        lynx::instrument(module);

        #if REPORT_BASE && REPORT_INSTRUMENTED_PTX 
        module.writeIR(std::cout);
        #endif

        report("loading module on device ...");
        _device->loadModule(&module);

        report("loading kernels on device ...");
        for (CudaRuntimeContext::RegisteredKernelMap::const_iterator 
		        kernel = cudaRuntime()->_kernels.begin(); 
		        kernel != cudaRuntime()->_kernels.end();
		        ++kernel) 
        {
            if(kernel->second.module == module.path())
            {
                report("loading kernel - " << kernel->second.kernel << " - on device");
                _device->loadKernel(kernel->second.kernel, kernel->second.module);
            }
        }

        for (CudaRuntimeContext::RegisteredTextureMap::iterator 
		        texture = cudaRuntime()->_textures.begin(); 
		        texture != cudaRuntime()->_textures.end();
		        ++texture) 
        {
            if(texture->second.module == module.path())
            {                
                ir::Texture* tex = module.getTexture(texture->second.texture);
		        assert(tex != 0);
		        tex->normalizedFloat = texture->second.norm; 

                report("loading texture - " << texture->second.texture << " - on device");
                _device->loadTexture(texture->second.texture);
            }
        }
    }
    
    void CudaContext::registerAllModules() {
	for(CudaRuntimeContext::ModuleMap::iterator module = cudaRuntime()->_modules.begin(); 
		module != cudaRuntime()->_modules.end(); ++module) {
		lynx::validateInstrumentor(module->first);
		registerModule(module->second);
	}
}

    cudaError_t CudaContext::launchKernel(CUfunction kernelHandle, 
        KernelLaunchConfiguration launch) 
    {

        report("launchKernel ...");

        size_t paramSize = 0;
        for (size_t i = 0; i < launch.args.size(); i++) {
            paramSize = std::max(paramSize, launch.args[i]->size +
                launch.args[i]->offset);
        }

        char paramBlock[4096];
        if (paramSize > sizeof(paramBlock)) {
            return cudaErrorInvalidValue;
        }

        for (size_t i = 0; i < launch.args.size(); i++) {
            memcpy(paramBlock + launch.args[i]->offset,
                launch.args[i]->param, launch.args[i]->size);
        }

        void * paramConfig[] = {
            CU_LAUNCH_PARAM_BUFFER_POINTER, paramBlock,
            CU_LAUNCH_PARAM_BUFFER_SIZE,    &paramSize,
            CU_LAUNCH_PARAM_END};

        if (launch.blockDim.x * launch.blockDim.y * launch.blockDim.z == 0) {
            return cudaErrorInvalidConfiguration;
        }
        report("launch shared memory: " << launch.sharedMemory);
        
        CUresult ret = cuLaunchKernel(kernelHandle, launch.gridDim.x, launch.gridDim.y,
                launch.gridDim.z, launch.blockDim.x, launch.blockDim.y, launch.blockDim.z,
                launch.sharedMemory, launch.stream, NULL, paramConfig);

        report("kernel launch ret = " << ret);

        cudaError_t _ret = cudaSuccess;

        switch (ret) {
            case CUDA_SUCCESS:
                _ret = cudaSuccess;
                break;
            case CUDA_ERROR_DEINITIALIZED:
            case CUDA_ERROR_NOT_INITIALIZED:
            case CUDA_ERROR_INVALID_CONTEXT:
            case CUDA_ERROR_INVALID_VALUE:
                _ret = cudaErrorInvalidConfiguration;
                break;
            case CUDA_ERROR_LAUNCH_FAILED:
                _ret = cudaErrorLaunchFailure;
                break;
            case CUDA_ERROR_LAUNCH_OUT_OF_RESOURCES:
                _ret = cudaErrorLaunchOutOfResources;
                break;
            case CUDA_ERROR_LAUNCH_TIMEOUT:
                _ret = cudaErrorLaunchTimeout;
                break;
            case CUDA_ERROR_SHARED_OBJECT_INIT_FAILED:
                _ret = cudaErrorSharedObjectInitFailed;
                break;
            case CUDA_ERROR_LAUNCH_INCOMPATIBLE_TEXTURING:
            default:
                _ret = cudaErrorUnknown;
                break;
        }

        return _ret;
    }


    cudaError_t CudaContext::cudaLaunch(const void *entry) {
        boost::unique_lock<boost::mutex> lock(_mutex);

        report("cudaLaunch ...");

        cudaError_t result = cudaErrorLaunchFailure;

        CudaRuntimeContext::RegisteredKernelMap::iterator kernel = 
            _cudaRuntime->_kernels.find((void *)entry);
        assert(kernel != _cudaRuntime->_kernels.end());
        std::string moduleName = kernel->second.module;
        std::string kernelName = kernel->second.kernel;
    
        report("module: " << moduleName << ", kernel: " << kernelName);
       
        CudaRuntimeContext::ModuleMap::iterator module = 
            _cudaRuntime->_modules.find(moduleName);
        assert(module != _cudaRuntime->_modules.end());

        assert(launchConfigurations.size());

        KernelLaunchConfiguration launch(launchConfigurations.back());
        launchConfigurations.pop_back();
        
        instrumentation::PTXInstrumentorVector *instrumentors = 
            lynx::getConfiguredInstrumentors();
        
        if(instrumentors->size() == 0)
        {
            registerModule(module->second);
                
            assert(_device->kernels.find(kernelName) != _device->kernels.end());
            CUfunction kernelHandle = _device->kernels.find(kernelName)->second;
            assert(kernelHandle);

            report("launching non-instrumented kernel ...");
            
            lynx::getProfiler()->startTimer();   
            
            result = launchKernel(kernelHandle, launch);
            
            lynx::getProfiler()->stopKernelTimer(
		    & trace::Profiler::kernelsExecute, kernelName); 
        }

        report("instrumentors size: " << instrumentors->size());
        
        for(instrumentation::PTXInstrumentorVector::iterator instrumentor = 
            instrumentors->begin();
            instrumentor != instrumentors->end(); ++instrumentor)
        {
            report((*instrumentor)->description);
            lynx::resetInstrumentor(*instrumentor);

            if(lynx::validateInstrumentor(moduleName, kernelName))
            {
                registerModule(module->second);
                
                lynx::initializeKernelLaunch(kernelName, 
                    launch.blockDim.x * launch.blockDim.y * launch.blockDim.z,
                    launch.gridDim.x * launch.gridDim.y * launch.gridDim.z);

                assert(_device->kernels.find(kernelName) != _device->kernels.end());
                CUfunction kernelHandle = _device->kernels.find(kernelName)->second;
                assert(kernelHandle);
                report("launching instrumented kernel ...");
                
                lynx::getProfiler()->startTimer();   
                
                result = launchKernel(kernelHandle, launch);
                
                lynx::getProfiler()->stopKernelTimer(
		            & trace::Profiler::kernelsExecute, kernelName);           
        
                lynx::finalizeKernelLaunch();
            }
            else
            {
                report("Instrumentor validation failed ...");
                registerModule(module->second);
                
                assert(_device->kernels.find(kernelName) != _device->kernels.end());
                CUfunction kernelHandle = _device->kernels.find(kernelName)->second;
                assert(kernelHandle);
                report("launching non-instrumented kernel ...");
                
                lynx::getProfiler()->startTimer();   
                
                result = launchKernel(kernelHandle, launch);
                
                lynx::getProfiler()->stopKernelTimer(
		            & trace::Profiler::kernelsExecute, kernelName); 

            }
        }
      
        return setLastError(result);
    }

    cudaError_t CudaContext::cudaSetupArgument(const void *arg, size_t size,
            size_t offset) {
        boost::unique_lock<boost::mutex> lock(_mutex);

        cudaError_t result = cudaErrorMissingConfiguration;
        if(launchConfigurations.size() > 0)
        {
            KernelLaunchConfiguration launch(launchConfigurations.back());
	        
            Parameter * copy = new Parameter(arg, size, offset);
            launch.args.push_back(copy);
            launchConfigurations.pop_back();
            launchConfigurations.push_back(launch);

            result = cudaSuccess;
        }

        return setLastError(result);
    }

    cudaError_t CudaContext::cudaThreadGetCacheConfig(
            enum cudaFuncCache *pCacheConfig) {
        return CudaRuntimeInterface::cudaThreadGetCacheConfig(pCacheConfig);
    }

    cudaError_t CudaContext::cudaThreadGetLimit(size_t *pValue,
            enum cudaLimit limit) {
        return CudaRuntimeInterface::cudaThreadGetLimit(pValue, limit);
    }

    cudaError_t CudaContext::cudaThreadSetCacheConfig(
            enum cudaFuncCache cacheConfig) {
        return CudaRuntimeInterface::cudaThreadSetCacheConfig(cacheConfig);
    }

    cudaError_t CudaContext::cudaThreadSetLimit(enum cudaLimit limit,
            size_t value) {
        return CudaRuntimeInterface::cudaThreadSetLimit(limit, value);
    }

    cudaError_t CudaContext::cudaThreadSynchronize() {
        return cudaDeviceSynchronize();
    }

    cudaError_t CudaContext::cudaBindSurfaceToArray(
            const struct surfaceReference *surfref, const struct cudaArray *array,
            const struct cudaChannelFormatDesc *desc) {
        return CudaRuntimeInterface::cudaBindSurfaceToArray(surfref, array, desc);
    }

    cudaError_t CudaContext::locateTexture(
        const struct textureReference *texref,
        CUtexref & texHandle, 
        CudaRuntimeContext::RegisteredTextureMap::iterator & texture)
    {
        texture = cudaRuntime()->_textures.find((void*)texref);
	    if(texture == cudaRuntime()->_textures.end()) {
            report("Unable to find texture in RegisteredTextureMap");
            return setLastError(cudaErrorInvalidValue);
        }

        CudaRuntimeContext::ModuleMap::iterator module = 
            cudaRuntime()->_modules.find(texture->second.module);
        if(module != cudaRuntime()->_modules.end()) {  
            report("registering module");
            lynx::validateInstrumentor(module->first);
            registerModule(module->second);
        }   
        else {
            report("Texture not associated with module!");
            return setLastError(cudaErrorInvalidValue);
        }   

        report("locating texture handle");
        texHandle = _device->textures.find(texture->second.texture)->second;
        assert(texHandle);

        return cudaSuccess;

    }

    cudaError_t CudaContext::cudaBindTexture(size_t *offset,
            const struct textureReference *texref, const void *devPtr,
            const struct cudaChannelFormatDesc *desc, size_t size) {
        
        boost::unique_lock<boost::mutex> lock(_mutex);
        
        if (!(devPtr)) {
            return setLastError(cudaErrorUnknown);
        }

        CUtexref texHandle = NULL;
        CudaRuntimeContext::RegisteredTextureMap::iterator texture;
        cudaError_t result = locateTexture(texref, texHandle, texture);
        if(result != cudaSuccess)
            return setLastError(result);

        //set texture address and format
        size_t internalOffset;
        report("setting texture reference address");
        CUresult ret = cuTexRefSetAddress(&internalOffset, texHandle, 
            (CUdeviceptr) devPtr, size);

        switch(ret) {
            case CUDA_SUCCESS:
            break;
            case CUDA_ERROR_INVALID_VALUE:
                return cudaErrorInvalidValue;
            case CUDA_ERROR_DEINITIALIZED:
            case CUDA_ERROR_NOT_INITIALIZED:
            case CUDA_ERROR_INVALID_CONTEXT:
            default:
                /* TODO */
            return setLastError(cudaErrorNotYetImplemented);
        }

        if (internalOffset != 0 && !(offset)) {
            return setLastError(cudaErrorInvalidValue);
        } 
        else if (offset) {
            *offset = internalOffset;
        }

        CUarray_format format = CU_AD_FORMAT_SIGNED_INT32;

        switch (desc->f) {
            case cudaChannelFormatKindSigned:
                format = CU_AD_FORMAT_SIGNED_INT32;
                break;
            case cudaChannelFormatKindUnsigned:
                format = CU_AD_FORMAT_UNSIGNED_INT32;
                break;
            case cudaChannelFormatKindFloat:
                format = CU_AD_FORMAT_FLOAT;
                break;
            case cudaChannelFormatKindNone:
                /* TODO */
                return setLastError(cudaErrorInvalidValue);
        }
        report("setting texture reference format");
        ret = cuTexRefSetFormat(texHandle, format,
            (desc->x + desc->y + desc->z + desc->w + 31) / 32);
        switch (ret) {
            case CUDA_SUCCESS:
                break;
            case CUDA_ERROR_INVALID_VALUE:
                return setLastError(cudaErrorInvalidValue);
            case CUDA_ERROR_DEINITIALIZED:
            case CUDA_ERROR_NOT_INITIALIZED:
            case CUDA_ERROR_INVALID_CONTEXT:
            default:
                /* TODO */
                return setLastError(cudaErrorNotYetImplemented);
            
        }    

        report("cudaBindTexture(ref = " << texref 
	    << ", devPtr = " << devPtr << ", size = " << size << ")");

        texture->second.bound = true;
        if(offset)
            texture->second.offset = *offset;

        return setLastError(cudaSuccess);
    }

    cudaError_t CudaContext::cudaBindTexture2D(size_t *offset, const struct
            textureReference *texref, const void *devPtr, const struct
            cudaChannelFormatDesc *desc, size_t width, size_t height, size_t
            pitch) {
        return CudaRuntimeInterface::cudaBindTexture2D(offset, texref, devPtr, desc, width,
            height, pitch);
    }

    cudaError_t CudaContext::cudaBindTextureToArray(
            const struct textureReference *texref, const struct cudaArray *array,
            const struct cudaChannelFormatDesc *desc) {
        
        boost::unique_lock<boost::mutex> lock(_mutex);
  
        report("cudaBindTextureToArray() - texref = '" << texref << "', array = " 
		<< (void *)array << " - format: " << desc->f << " (" << desc->x 
		<< ", " << desc->y << ", " << desc->z << ", " << desc->w << ")");

        if (!(desc)) {
            /* CUDA SIGSEGV's here */
            raise(SIGSEGV);
            return setLastError(cudaErrorInvalidValue);
         }

        if (!(array)) {
            return setLastError(cudaErrorInvalidResourceHandle);
        }

        CUtexref texHandle = NULL;
        CudaRuntimeContext::RegisteredTextureMap::iterator texture;

        report("locating texture ...");
        cudaError_t result = locateTexture(texref, texHandle, texture);
        if(result != cudaSuccess)
            return setLastError(result);        

        report("setting texture reference array");
        CUresult ret = cuTexRefSetArray(texHandle, (CUarray) array,
        CU_TRSA_OVERRIDE_FORMAT);
        report("ret = " << ret);

        switch (ret) {
            case CUDA_SUCCESS:
                break;
            case CUDA_ERROR_INVALID_VALUE:
                return setLastError(cudaErrorInvalidValue);
            case CUDA_ERROR_DEINITIALIZED:
            case CUDA_ERROR_NOT_INITIALIZED:
            case CUDA_ERROR_INVALID_CONTEXT:
            default:
                /* TODO */
                return setLastError(cudaErrorInvalidResourceHandle);
        }

        report("setting texture bound to true and offset to zero");
        texture->second.bound = true;
        texture->second.offset = 0;

        return setLastError(cudaSuccess);
    }

    cudaError_t CudaContext::cudaChooseDevice(int *deviceId,
            const struct cudaDeviceProp *prop) {
        return CudaRuntimeInterface::cudaChooseDevice(deviceId, prop);
    }

    cudaChannelFormatDesc CudaContext::cudaCreateChannelDesc(int x, int y, int z,
            int w, enum cudaChannelFormatKind f) {
        return CudaRuntimeInterface::cudaCreateChannelDesc(x, y, z, w, f);
    }

    cudaError_t CudaContext::cudaDeviceGetCacheConfig(
            enum cudaFuncCache *pCacheConfig) {
        return CudaRuntimeInterface::cudaDeviceGetCacheConfig(pCacheConfig);
    }

    cudaError_t CudaContext::cudaDeviceGetLimit(size_t *pValue,
            enum cudaLimit limit) {
        return CudaRuntimeInterface::cudaDeviceGetLimit(pValue, limit);
    }

    cudaError_t CudaContext::cudaDeviceSetCacheConfig(
            enum cudaFuncCache cacheConfig) {
        return CudaRuntimeInterface::cudaDeviceSetCacheConfig(cacheConfig);
    }

    cudaError_t CudaContext::cudaDeviceSetLimit(enum cudaLimit limit,
            size_t value) {
        return CudaRuntimeInterface::cudaDeviceSetLimit(limit, value);
    }

    cudaError_t CudaContext::cudaDeviceSynchronize() {
        cudaError_t ret = CudaRuntimeInterface::cudaDeviceSynchronize();
        return setLastError(ret);
    }

    cudaError_t CudaContext::cudaDriverGetVersion(int *driverVersion) {
        cudaError_t ret = CudaRuntimeInterface::cudaDriverGetVersion(driverVersion);
       
        return ret;
    }

    cudaError_t CudaContext::cudaEventCreate(cudaEvent_t *event) {
        return CudaRuntimeInterface::cudaEventCreate(event);
    }

    cudaError_t CudaContext::cudaEventCreateWithFlags(cudaEvent_t *event,
            unsigned int flags) {
        return CudaRuntimeInterface::cudaEventCreateWithFlags(event, flags);
    }

    cudaError_t CudaContext::cudaEventDestroy(cudaEvent_t event) {
        return CudaRuntimeInterface::cudaEventDestroy(event);
    }

    cudaError_t CudaContext::cudaEventElapsedTime(float *ms, cudaEvent_t start,
            cudaEvent_t end) {
        return CudaRuntimeInterface::cudaEventElapsedTime(ms, start, end);
    }

    cudaError_t CudaContext::cudaEventQuery(cudaEvent_t event) {
        return CudaRuntimeInterface::cudaEventQuery(event);
    }

    cudaError_t CudaContext::cudaEventRecord(cudaEvent_t event,
            cudaStream_t stream) {
        return CudaRuntimeInterface::cudaEventRecord(event, stream);
    }

    cudaError_t CudaContext::cudaEventSynchronize(cudaEvent_t event) {
        return CudaRuntimeInterface::cudaEventSynchronize(event);
    }

    cudaError_t CudaContext::cudaFree(void *devPtr) {
        return setLastError(CudaRuntimeInterface::cudaFree(devPtr));
    }

    cudaError_t CudaContext::cudaFreeArray(struct cudaArray *array) {
        return CudaRuntimeInterface::cudaFreeArray(array);
    }

    cudaError_t CudaContext::cudaFreeHost(void *ptr) {
        return CudaRuntimeInterface::cudaFreeHost(ptr);
    }

    cudaError_t CudaContext::cudaFuncGetAttributes(
            struct cudaFuncAttributes *attr, const void *func) {
        return CudaRuntimeInterface::cudaFuncGetAttributes(attr, func);
    }

    cudaError_t CudaContext::cudaFuncSetCacheConfig(const void *func,
            enum cudaFuncCache cacheConfig) {
       return CudaRuntimeInterface::cudaFuncSetCacheConfig(func, cacheConfig);
    }

    cudaError_t CudaContext::cudaGetChannelDesc(
            struct cudaChannelFormatDesc *desc, const struct cudaArray *array) {
        report("cudaGetChannelDesc");
        return CudaRuntimeInterface::cudaGetChannelDesc(desc, array);
    }

    cudaError_t CudaContext::cudaGetDeviceProperties(struct cudaDeviceProp *prop,
            int deviceId) {
        return CudaRuntimeInterface::cudaGetDeviceProperties(prop, deviceId);
    }

    cudaError_t CudaContext::cudaGetExportTable(const void **ppExportTable,
            const cudaUUID_t *pExportTableId) {
        return CudaRuntimeInterface::cudaGetExportTable(ppExportTable, pExportTableId);
    }

    cudaError_t CudaContext::cudaGetSurfaceReference(
            const struct surfaceReference **surfRef, const char *symbol) {
        return CudaRuntimeInterface::cudaGetSurfaceReference(surfRef, symbol);
    }

    cudaError_t CudaContext::cudaGetLastError() {
        cudaError_t ret = _error;
        _error = cudaSuccess;
        return ret;
    }

    void CudaContext::findSymbol(const void *symbol, std::string & name, std::string & moduleName) 
    {
        CudaRuntimeContext::RegisteredGlobalMap::iterator global = 
        cudaRuntime()->_globals.find((void*)symbol);

        report("findSymbol -- " << (void *)symbol);
        
        if(global != cudaRuntime()->_globals.end())
        {
            name = global->second.global;
		    moduleName = global->second.module;
		    report("found global: " << name);
        }
        else
        {
            name = (char *)symbol;
            // register all modules -- this ensures that all global variables
            // added via instrumentation have been incorporated into the modules
            report("registering all modules ...");
            registerAllModules();
            // try a brute force search over all modules
			for(CudaRuntimeContext::ModuleMap::iterator module = cudaRuntime()->_modules.begin(); 
				module != cudaRuntime()->_modules.end(); ++module)
			{
                report("searching module - " << module->second.path());
				ir::Module::GlobalMap::const_iterator g = 
					module->second.globals().find((char *)symbol);
				if(g != module->second.globals().end())
				{
					moduleName = module->second.path();
                    break;
				}
			}

        }
    }

    cudaError_t CudaContext::cudaGetSymbolAddress(void **devPtr,
            const void *symbol) {

        report("cudaGetSymbolAddress - symbol: " << (void *)symbol);

        if (!(devPtr)) {
            return setLastError(cudaErrorInvalidValue);
        }
        
        std::string name;
        std::string moduleName;

        findSymbol(symbol, name, moduleName);

        report("name: " << name << ", module: " << moduleName);

        if(_device->modules.find(moduleName) == _device->modules.end())
        {
            CudaRuntimeContext::ModuleMap::iterator moduleToLoad = 
                cudaRuntime()->_modules.find(moduleName);
            assert(moduleToLoad != cudaRuntime()->_modules.end());
            registerModule(moduleToLoad->second);
        }

        CUmodule moduleHandle = _device->modules.find(moduleName)->second;
        assert(moduleHandle);

        size_t bytes;
        CUdeviceptr tmp;

        report("retrieving symbol address ...");
        assert(cuModuleGetGlobal(&tmp, &bytes, moduleHandle, name.c_str()) == CUDA_SUCCESS);
        *devPtr = (char *)tmp;
        report("devPtr = " << *devPtr);

        return setLastError(cudaSuccess);
    }

    cudaError_t CudaContext::cudaGetSymbolSize(size_t *size, const void *symbol) {
        
        if (!(size)) {
            return setLastError(cudaErrorInvalidValue);
        }

        std::string name;
        std::string moduleName;

        findSymbol(symbol, name, moduleName);

        report("name: " << name << ", module: " << moduleName);

        if(_device->modules.find(moduleName) == _device->modules.end())
        {
            CudaRuntimeContext::ModuleMap::iterator moduleToLoad = 
                cudaRuntime()->_modules.find(moduleName);
            assert(moduleToLoad != cudaRuntime()->_modules.end());
            registerModule(moduleToLoad->second);
        }

        CUmodule moduleHandle = _device->modules.find(moduleName)->second;
        assert(moduleHandle);

        CUdeviceptr devPtr;
        report("retrieving symbol size ..");
        assert(cuModuleGetGlobal(&devPtr, size, moduleHandle, name.c_str()) == CUDA_SUCCESS);
        report("size: " << *size);

        return setLastError(cudaSuccess);
    }

    cudaError_t CudaContext::cudaGetTextureAlignmentOffset(size_t *offset,
            const struct textureReference *texref) {
        boost::unique_lock<boost::mutex> lock(_mutex);

        CUtexref texHandle = NULL;
        CudaRuntimeContext::RegisteredTextureMap::iterator texture;
        cudaError_t result = locateTexture(texref, texHandle, texture);
        if(result != cudaSuccess)
            return setLastError(result);

        *offset = texture->second.offset;        

        return setLastError(cudaSuccess);
    }

    cudaError_t CudaContext::cudaGetTextureReference(
            const struct textureReference **texref, const char *symbol) {

        std::string name = symbol;
	    CudaRuntimeContext::RegisteredTextureMap::iterator matchedTexture = 
            cudaRuntime()->_textures.end();
	
	    for(CudaRuntimeContext::RegisteredTextureMap::iterator 
            texture = cudaRuntime()->_textures.begin(); 
		    texture != cudaRuntime()->_textures.end(); ++texture) {
		    if(texture->second.texture == name) {
			    if(matchedTexture != cudaRuntime()->_textures.end()) {
				   
				    throw hydrazine::Exception(
                    "Ambiguous texture declared in at least two modules");
			    }
			    matchedTexture = texture;
		    }
	    }
	
	    if(matchedTexture != cudaRuntime()->_textures.end()) {
		    *texref = (const struct textureReference*)matchedTexture->first;
	    }

        return cudaSuccess;
    }

    cudaError_t CudaContext::cudaGraphicsMapResources(int count,
            cudaGraphicsResource_t *resources, cudaStream_t stream) {
        return CudaRuntimeInterface::cudaGraphicsMapResources(count, resources, stream);
    }

    cudaError_t CudaContext::cudaGraphicsResourceGetMappedPointer(void **devPtr,
            size_t *size, cudaGraphicsResource_t resource) {
        return CudaRuntimeInterface::cudaGraphicsResourceGetMappedPointer(devPtr, size,
            resource);
    }

    cudaError_t CudaContext::cudaGraphicsResourceSetMapFlags(
            cudaGraphicsResource_t resource, unsigned int flags) {
        return CudaRuntimeInterface::cudaGraphicsResourceSetMapFlags(resource, flags);
    }

    cudaError_t CudaContext::cudaGraphicsSubResourceGetMappedArray(
            struct cudaArray **array, cudaGraphicsResource_t resource,
            unsigned int arrayIndex, unsigned int mipLevel) {
        return CudaRuntimeInterface::cudaGraphicsSubResourceGetMappedArray(array, resource,
            arrayIndex, mipLevel);
    }

    cudaError_t CudaContext::cudaGraphicsUnmapResources(int count,
            cudaGraphicsResource_t *resources, cudaStream_t stream) {
        return CudaRuntimeInterface::cudaGraphicsUnmapResources(count, resources, stream);
    }

    cudaError_t CudaContext::cudaGraphicsUnregisterResource(
            cudaGraphicsResource_t resource) {
        return CudaRuntimeInterface::cudaGraphicsUnregisterResource(resource);
    }

    cudaError_t CudaContext::cudaHostAlloc(void **pHost, size_t size,
            unsigned int flags) {
        return CudaRuntimeInterface::cudaHostAlloc(pHost, size, flags);
    }

    cudaError_t CudaContext::cudaHostGetDevicePointer(void **pdeviceId, void *pHost,
            unsigned int flags) {
        return CudaRuntimeInterface::cudaHostGetDevicePointer(pdeviceId, pHost, flags);
    }

    cudaError_t CudaContext::cudaHostGetFlags(unsigned int *pFlags, void *pHost) {
        return CudaRuntimeInterface::cudaHostGetFlags(pFlags, pHost);
    }

    cudaError_t CudaContext::cudaHostRegister(void *ptr, size_t size,
            unsigned int flags) {
        return CudaRuntimeInterface::cudaHostRegister(ptr, size, flags);
    }

    cudaError_t CudaContext::cudaHostUnregister(void *ptr) {
        return CudaRuntimeInterface::cudaHostUnregister(ptr);
    }

#if CUDA_VERSION >= 4010 /* cudaIpc* calls added from CUDA 4.1 onwards */ 
    cudaError_t CudaContext::cudaIpcGetEventHandle(cudaIpcEventHandle_t *handle,
            cudaEvent_t event) {
        return CudaRuntimeInterface::cudaIpcGetEventHandle(handle, event);
    }

    cudaError_t CudaContext::cudaIpcOpenEventHandle(cudaEvent_t *event,
            cudaIpcEventHandle_t handle) {
        return CudaRuntimeInterface::cudaIpcOpenEventHandle(event, handle);
    }

    cudaError_t CudaContext::cudaIpcGetMemHandle(cudaIpcMemHandle_t *handle,
            void *devPtr) {
        return CudaRuntimeInterface::cudaIpcGetMemHandle(handle, devPtr);
    }

    cudaError_t CudaContext::cudaIpcOpenMemHandle(void **devPtr,
            cudaIpcMemHandle_t handle, unsigned int flags) {
        return CudaRuntimeInterface::cudaIpcOpenMemHandle(devPtr, handle, flags);
    }

    cudaError_t CudaContext::cudaIpcCloseMemHandle(void *devPtr) {
        return CudaRuntimeInterface::cudaIpcCloseMemHandle(devPtr);
    }
#endif

    cudaError_t CudaContext::cudaMalloc(void **devPtr, size_t size) {
        report("cudaMalloc( *devPtr = " << (void *)*devPtr 
	            << ", size = " << size << ")");
        return setLastError(CudaRuntimeInterface::cudaMalloc(devPtr, size));
    }

    cudaError_t CudaContext::cudaMalloc3D(struct cudaPitchedPtr *pitchedDevPtr,
            struct cudaExtent extent) {
        return setLastError(CudaRuntimeInterface::cudaMalloc3D(pitchedDevPtr, extent));
    }

    cudaError_t CudaContext::cudaMalloc3DArray(struct cudaArray** array,
            const struct cudaChannelFormatDesc *desc, struct cudaExtent extent,
            unsigned int flags) {
        return CudaRuntimeInterface::cudaMalloc3DArray(array, desc, extent, flags);
    }

    cudaError_t CudaContext::cudaMallocArray(struct cudaArray **array,
            const struct cudaChannelFormatDesc *desc, size_t width, size_t height,
            unsigned int flags) {
        return CudaRuntimeInterface::cudaMallocArray(array, desc, width, height, flags);
    }

    cudaError_t CudaContext::cudaMallocHost(void **ptr, size_t size) {
        return CudaRuntimeInterface::cudaMallocHost(ptr, size);
    }

    cudaError_t CudaContext::cudaMallocPitch(void **devPtr, size_t *pitch,
            size_t width, size_t height) {
        return CudaRuntimeInterface::cudaMallocPitch(devPtr, pitch, width, height);
    }

    cudaError_t CudaContext::cudaMemcpy(void *dst, const void *src, size_t size,
            enum cudaMemcpyKind kind) {
        return CudaRuntimeInterface::cudaMemcpy(dst, src, size, kind);
    }

    cudaError_t CudaContext::cudaMemcpy2D(void *dst, size_t dpitch,
            const void *src, size_t pitch, size_t width, size_t height,
            enum cudaMemcpyKind kind) {
        return CudaRuntimeInterface::cudaMemcpy2D(dst, dpitch, src, pitch, width, height, kind);
    }

    cudaError_t CudaContext::cudaMemcpy2DAsync(void *dst, size_t dpitch,
            const void *src, size_t spitch, size_t width, size_t height,
            enum cudaMemcpyKind kind, cudaStream_t stream) {
        return CudaRuntimeInterface::cudaMemcpy2DAsync(dst, dpitch, src, spitch, width, height,
            kind, stream);
    }

    cudaError_t CudaContext::cudaMemcpy2DArrayToArray(struct cudaArray *dst,
            size_t wOffsetDst, size_t hOffsetDst, const struct cudaArray *src,
            size_t wOffsetSrc, size_t hOffsetSrc, size_t width, size_t height,
            enum cudaMemcpyKind kind) {
        return CudaRuntimeInterface::cudaMemcpy2DArrayToArray(dst, wOffsetDst, hOffsetDst, src,
            wOffsetSrc, hOffsetSrc, width, height, kind);
    }

    cudaError_t CudaContext::cudaMemcpy2DFromArray(void *dst, size_t dpitch,
            const struct cudaArray *src, size_t wOffset, size_t hOffset,
            size_t width, size_t height, enum cudaMemcpyKind kind) {
        return CudaRuntimeInterface::cudaMemcpy2DFromArray(dst, dpitch, src, wOffset, hOffset,
            width, height, kind);
    }

    cudaError_t CudaContext::cudaMemcpy2DFromArrayAsync(void *dst, size_t dpitch,
            const struct cudaArray *src, size_t wOffset, size_t hOffset,
            size_t width, size_t height, enum cudaMemcpyKind kind,
            cudaStream_t stream) {
        return CudaRuntimeInterface::cudaMemcpy2DFromArrayAsync(dst, dpitch, src, wOffset,
            hOffset, width, height, kind, stream);
    }

    cudaError_t CudaContext::cudaMemcpy2DToArray(struct cudaArray *dst,
            size_t wOffset, size_t hOffset, const void *src, size_t spitch,
            size_t width, size_t height, enum cudaMemcpyKind kind) {
        return CudaRuntimeInterface::cudaMemcpy2DToArray(dst, wOffset, hOffset, src, spitch,
            width, height, kind);
    }

    cudaError_t CudaContext::cudaMemcpy2DToArrayAsync(struct cudaArray *dst,
            size_t wOffset, size_t hOffset, const void *src, size_t spitch,
            size_t width, size_t height, enum cudaMemcpyKind kind,
            cudaStream_t stream) {
        return CudaRuntimeInterface::cudaMemcpy2DToArrayAsync(dst, wOffset, hOffset, src,
            spitch, width, height, kind, stream);
    }

    cudaError_t CudaContext::cudaMemcpy3D(const struct cudaMemcpy3DParms *p) {
        return CudaRuntimeInterface::cudaMemcpy3D(p);
    }

    cudaError_t CudaContext::cudaMemcpy3DAsync(const struct cudaMemcpy3DParms *p,
            cudaStream_t stream) {
        return CudaRuntimeInterface::cudaMemcpy3DAsync(p, stream);
    }

    cudaError_t CudaContext::cudaMemcpy3DPeer(
            const struct cudaMemcpy3DPeerParms *p) {
        return CudaRuntimeInterface::cudaMemcpy3DPeer(p);
    }

    cudaError_t CudaContext::cudaMemcpy3DPeerAsync(
            const struct cudaMemcpy3DPeerParms *p, cudaStream_t stream) {
        return CudaRuntimeInterface::cudaMemcpy3DPeerAsync(p, stream);
    }

    cudaError_t CudaContext::cudaMemcpyArrayToArray(struct cudaArray *dst,
            size_t wOffsetDst, size_t hOffsetDst, const struct cudaArray *src,
            size_t wOffsetSrc, size_t hOffsetSrc, size_t count,
            enum cudaMemcpyKind kind) {
        return CudaRuntimeInterface::cudaMemcpyArrayToArray(dst, wOffsetDst, hOffsetDst, src,
            wOffsetSrc, hOffsetSrc, count, kind);
    }

    cudaError_t CudaContext::cudaMemcpyAsync(void *dst, const void *src,
            size_t count, enum cudaMemcpyKind kind, cudaStream_t stream) {
        return CudaRuntimeInterface::cudaMemcpyAsync(dst, src, count, kind, stream);
    }

    cudaError_t CudaContext::cudaMemcpyFromArray(void *dst,
            const struct cudaArray *src, size_t wOffset, size_t hOffset,
            size_t count, enum cudaMemcpyKind kind) {
        return CudaRuntimeInterface::cudaMemcpyFromArray(dst, src, wOffset, hOffset,
            count, kind);
    }

    cudaError_t CudaContext::cudaMemcpyFromArrayAsync(void *dst,
            const struct cudaArray *src, size_t wOffset, size_t hOffset,
            size_t count, enum cudaMemcpyKind kind, cudaStream_t stream) {
        return CudaRuntimeInterface::cudaMemcpyFromArrayAsync(dst, src, wOffset, hOffset,
            count, kind, stream);
    }

    cudaError_t CudaContext::cudaMemcpyFromSymbol(void *dst,
            const void *symbol, size_t count, size_t offset,
            enum cudaMemcpyKind kind) {

        uint8_t * symbolPtr;
        cudaError_t ret = CudaContext::cudaGetSymbolAddress((void **) &symbolPtr, symbol);
        if (ret != cudaSuccess) {
            return ret;
        }

        size_t symbolSize;
        ret = CudaContext::cudaGetSymbolSize(&symbolSize, symbol);
        if (ret != cudaSuccess) {
            return ret;
        }

        if (symbolSize < count + offset) {
            return cudaErrorInvalidValue;
        }

        switch (kind) {
            case cudaMemcpyDefault:
                raise(SIGSEGV);

                /* Fall through */
            case cudaMemcpyDeviceToDevice:
            case cudaMemcpyHostToDevice:
            default:
                return cudaErrorInvalidMemcpyDirection;
            case cudaMemcpyDeviceToHost:
            case cudaMemcpyHostToHost:
                break;
        }

        return cudaMemcpy(dst, symbolPtr + offset, count, kind);
    }

    cudaError_t CudaContext::cudaMemcpyFromSymbolAsync(void *dst,
            const void *symbol, size_t count, size_t offset,
            enum cudaMemcpyKind kind, cudaStream_t stream) {

        uint8_t * symbolPtr;
        cudaError_t ret = CudaContext::cudaGetSymbolAddress((void **) &symbolPtr, symbol);
        if (ret != cudaSuccess) {
            return ret;
        }

        size_t symbolSize;
        ret = CudaContext::cudaGetSymbolSize(&symbolSize, symbol);
        if (ret != cudaSuccess) {
            return ret;
        }

        if (symbolSize < count + offset) {
            return cudaErrorInvalidValue;
        }

        switch (kind) {
            case cudaMemcpyDefault:
                raise(SIGSEGV);

                /* Fall through */
            case cudaMemcpyDeviceToDevice:
            case cudaMemcpyHostToDevice:
            default:
                return cudaErrorInvalidMemcpyDirection;
            case cudaMemcpyDeviceToHost:
            case cudaMemcpyHostToHost:
                break;
        }

        return cudaMemcpyAsync(dst, symbolPtr + offset, count, kind, stream);
    }

    cudaError_t CudaContext::cudaMemcpyPeer(void *dst, int dstdeviceId,
            const void *src, int srcdeviceId, size_t count) {
        return CudaRuntimeInterface::cudaMemcpyPeer(dst, dstdeviceId, src, srcdeviceId, count);
    }

    cudaError_t CudaContext::cudaMemcpyPeerAsync(void *dst, int dstdeviceId,
            const void *src, int srcdeviceId, size_t count, cudaStream_t stream) {
        return CudaRuntimeInterface::cudaMemcpyPeerAsync(dst, dstdeviceId, src, srcdeviceId,
            count, stream);
    }

    cudaError_t CudaContext::cudaMemcpyToArray(struct cudaArray *dst,
            size_t wOffset, size_t hOffset, const void *src, size_t count,
            enum cudaMemcpyKind kind) {
        report("cudaMemcpyToArray("<< dst << ", " << src << ", " << wOffset 
		<< ", " << hOffset << ", " << count << ")");
        return CudaRuntimeInterface::cudaMemcpyToArray(dst, wOffset, hOffset, src, count, kind);
    }

    cudaError_t CudaContext::cudaMemcpyToArrayAsync(struct cudaArray *dst,
            size_t wOffset, size_t hOffset, const void *src, size_t count,
            enum cudaMemcpyKind kind, cudaStream_t stream) {
        return CudaRuntimeInterface::cudaMemcpyToArrayAsync(dst, wOffset, hOffset, src, count,
            kind, stream);
    }

    cudaError_t CudaContext::cudaMemcpyToSymbol(const void *symbol,
            const void *src, size_t count, size_t offset,
            enum cudaMemcpyKind kind) {
        
        report("cudaMemcpyToSymbol - symbol: " << (void *)symbol);
        uint8_t * symbolPtr;
        cudaError_t ret = CudaContext::cudaGetSymbolAddress((void **) &symbolPtr, symbol);
        if (ret != cudaSuccess) {
            return ret;
        }

        size_t symbolSize;
        ret = CudaContext::cudaGetSymbolSize(&symbolSize, symbol);
        if (ret != cudaSuccess) {
            return ret;
        }

        if (symbolSize < count + offset) {
            return cudaErrorInvalidValue;
        }

        switch (kind) {
            case cudaMemcpyDefault:
                raise(SIGSEGV);

                /* Fall through */
            case cudaMemcpyDeviceToHost:
            case cudaMemcpyHostToHost:
            default:
                return cudaErrorInvalidMemcpyDirection;
            case cudaMemcpyDeviceToDevice:
            case cudaMemcpyHostToDevice:
                break;
        }

        return cudaMemcpy(symbolPtr + offset, src, count, kind);
    }

    cudaError_t CudaContext::cudaMemcpyToSymbolAsync(const void *symbol,
            const void *src, size_t count, size_t offset,
            enum cudaMemcpyKind kind, cudaStream_t stream) {

        uint8_t * symbolPtr;
        cudaError_t ret = CudaContext::cudaGetSymbolAddress((void **) &symbolPtr, symbol);
        if (ret != cudaSuccess) {
            return ret;
        }

        size_t symbolSize;
        ret = CudaContext::cudaGetSymbolSize(&symbolSize, symbol);
        if (ret != cudaSuccess) {
            return ret;
        }

        if (symbolSize < count + offset) {
            return cudaErrorInvalidValue;
        }

        switch (kind) {
            case cudaMemcpyDefault:
                raise(SIGSEGV);

                /* Fall through */
            case cudaMemcpyDeviceToHost:
            case cudaMemcpyHostToHost:
            default:
                return cudaErrorInvalidMemcpyDirection;
            case cudaMemcpyDeviceToDevice:
            case cudaMemcpyHostToDevice:
                break;
        }

        return cudaMemcpyAsync(symbolPtr + offset, src, count, kind, stream);
    }

    cudaError_t CudaContext::cudaMemGetInfo(size_t *free, size_t *total) {
        return CudaRuntimeInterface::cudaMemGetInfo(free, total);
    }

    cudaError_t CudaContext::cudaMemset(void *devPtr, int value, size_t count) {
        return setLastError(CudaRuntimeInterface::cudaMemset(devPtr, value, count));
    }

    cudaError_t CudaContext::cudaMemset2D(void *devPtr, size_t pitch, int value,
            size_t width, size_t height) {
        return CudaRuntimeInterface::cudaMemset2D(devPtr, pitch, value, width, height);
    }

    cudaError_t CudaContext::cudaMemset2DAsync(void *devPtr, size_t pitch,
            int value, size_t width, size_t height, cudaStream_t stream) {
        return CudaRuntimeInterface::cudaMemset2DAsync(devPtr, pitch, value, width, height,
            stream);
    }

    cudaError_t CudaContext::cudaMemset3D(struct cudaPitchedPtr pitchedDevPtr,
            int value, struct cudaExtent extent) {
        return CudaRuntimeInterface::cudaMemset3D(pitchedDevPtr, value, extent);
    }

    cudaError_t CudaContext::cudaMemset3DAsync(
            struct cudaPitchedPtr pitchedDevPtr, int value,
            struct cudaExtent extent, cudaStream_t stream) {
        return CudaRuntimeInterface::cudaMemset3DAsync(pitchedDevPtr, value, extent, stream);
    }

    cudaError_t CudaContext::cudaMemsetAsync(void *devPtr, int value,
            size_t count, cudaStream_t stream) {
        return CudaRuntimeInterface::cudaMemsetAsync(devPtr, value, count, stream);
    }

    cudaError_t CudaContext::cudaPeekAtLastError() {
        return _error;
    }

    cudaError_t CudaContext::cudaPointerGetAttributes(struct
            cudaPointerAttributes *attributes, const void *ptr) {
        
        return CudaRuntimeInterface::cudaPointerGetAttributes(attributes, (void *)ptr);
    }

    cudaError_t CudaContext::cudaRuntimeGetVersion(int *runtimeVersion) {
        if (runtimeVersion) {
            *runtimeVersion = _runtimeVersion;
            return cudaSuccess;
        } else {
            return cudaErrorInvalidValue;
        }
    }

    cudaError_t CudaContext::cudaSetDoubleForDevice(double *d) {
        return CudaRuntimeInterface::cudaSetDoubleForDevice(d);
    }

    cudaError_t CudaContext::cudaSetDoubleForHost(double *d) {
        return CudaRuntimeInterface::cudaSetDoubleForHost(d);
    }

    cudaError_t CudaContext::cudaStreamCreate(cudaStream_t *pStream) {
        return CudaRuntimeInterface::cudaStreamCreate(pStream);
    }

    cudaError_t CudaContext::cudaStreamDestroy(cudaStream_t stream) {
        return CudaRuntimeInterface::cudaStreamDestroy(stream);
    }

    cudaError_t CudaContext::cudaStreamQuery(cudaStream_t stream) {
        return CudaRuntimeInterface::cudaStreamQuery(stream);
    }

    cudaError_t CudaContext::cudaStreamSynchronize(cudaStream_t stream) {
        return CudaRuntimeInterface::cudaStreamSynchronize(stream);
    }

    cudaError_t CudaContext::cudaStreamWaitEvent(cudaStream_t stream,
            cudaEvent_t event, unsigned int flags) {
        return CudaRuntimeInterface::cudaStreamWaitEvent(stream, event, flags);
    }

    cudaError_t CudaContext::cudaUnbindTexture(
            const struct textureReference *texref) {
        
        boost::unique_lock<boost::mutex> lock(_mutex);

        CUtexref texHandle = NULL;
        CudaRuntimeContext::RegisteredTextureMap::iterator texture;
        cudaError_t result = locateTexture(texref, texHandle, texture);
        if(result != cudaSuccess)
            return setLastError(result);

        texture->second.bound = false;

        return setLastError(cudaSuccess);
    }

    cudaError_t CudaContext::setLastError(cudaError_t error) const {
        if (error != cudaSuccess) {
            _error = error;
        }

        return _error;
    }

}


