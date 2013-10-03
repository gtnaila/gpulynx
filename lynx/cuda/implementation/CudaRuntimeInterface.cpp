/*! \file CudaRuntimeInterface.cpp
	\date Friday June 22, 2012
	\author Naila Farooqui <naila@cc.gatech.edu>
	\brief The source file for the CUDA Runtime Interface
*/

#include <lynx/cuda/interface/CudaRuntimeInterface.h>
#include <cassert>
#include <cstdio>
#include <iostream>
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <dlfcn.h>

static void *cudart = NULL;

#define DYNLINK(function)   dlsym(cudart, #function)

using namespace cuda;


CudaRuntimeInterface::CudaRuntimeInterface() { 
}

CudaRuntimeInterface::~CudaRuntimeInterface() { 
    dlclose(cudart);
}

CudaRuntimeInterface & CudaRuntimeInterface::instance() {
    static CudaRuntimeInterface _instance;
    return _instance;
}

typedef cudaError_t (*cudaBindSurfaceToArray_t)(
        const struct surfaceReference *surfref, const struct cudaArray *array,
        const struct cudaChannelFormatDesc *desc);
        
typedef cudaError_t (*cudaBindTexture_t)(size_t *,
    const struct textureReference *, const void *,
    const struct cudaChannelFormatDesc *, size_t);
typedef cudaError_t (*cudaBindTexture2D_t)(size_t *offset,
        const struct textureReference *texref, const void *devPtr,
        const struct cudaChannelFormatDesc *desc, size_t width, size_t height,
        size_t pitch);    
typedef cudaError_t (*cudaChooseDevice_t)(int *device,
        const struct cudaDeviceProp *prop);    
typedef cudaError_t (*cudaConfigureCall_t)(dim3, dim3, size_t, cudaStream_t);

typedef cudaError_t (*cudaDeviceGetLimit_t)(size_t *pValue,
        enum cudaLimit limit);
typedef cudaError_t (*cudaDeviceSetLimit_t)(enum cudaLimit limit, size_t value);

typedef cudaError_t (*cudaDeviceGetCacheConfig_t)(enum cudaFuncCache *);
typedef cudaError_t (*cudaDeviceReset_t)();
typedef cudaError_t (*cudaDeviceSetCacheConfig_t)(enum cudaFuncCache);
typedef cudaError_t (*cudaDeviceSynchronize_t)();
typedef cudaError_t (*cudaDriverGetVersion_t)(int *);
typedef cudaError_t (*cudaEventCreate_t)(cudaEvent_t *);
typedef cudaError_t (*cudaEventCreateWithFlags_t)(cudaEvent_t *, unsigned int);
typedef cudaError_t (*cudaEventDestroy_t)(cudaEvent_t);
typedef cudaError_t (*cudaEventElapsedTime_t)(float *, cudaEvent_t,
    cudaEvent_t);
typedef cudaError_t (*cudaEventQuery_t)(cudaEvent_t);
typedef cudaError_t (*cudaEventRecord_t)(cudaEvent_t, cudaStream_t);
typedef cudaError_t (*cudaEventSynchronize_t)(cudaEvent_t);
			
typedef cudaError_t (*cudaIpcGetEventHandle_t)(cudaIpcEventHandle_t *handle,
        cudaEvent_t event);
typedef cudaError_t (*cudaIpcOpenEventHandle_t)(cudaEvent_t *event,
    cudaIpcEventHandle_t handle);
typedef cudaError_t (*cudaIpcGetMemHandle_t)(cudaIpcMemHandle_t *handle,
    void *devPtr);
typedef cudaError_t (*cudaIpcOpenMemHandle_t)(void **devPtr,
    cudaIpcMemHandle_t handle, unsigned int flags);
typedef cudaError_t (*cudaIpcCloseMemHandle_t)(void *devPtr);

typedef cudaError_t (*cudaFree_t)(void *);
typedef cudaError_t (*cudaFreeArray_t)(struct cudaArray *);
typedef cudaError_t (*cudaFreeHost_t)(void *);
typedef cudaError_t (*cudaFuncGetAttributes_t)(struct cudaFuncAttributes *attr,
        const void *func);
typedef cudaError_t (*cudaFuncSetCacheConfig_t)(const void *,
    enum cudaFuncCache);

typedef struct cudaChannelFormatDesc (*cudaCreateChannelDesc_t)(int x, int y, int z,
        int w, enum cudaChannelFormatKind f);    
typedef cudaError_t (*cudaGetChannelDesc_t)(struct cudaChannelFormatDesc *desc,
        const struct cudaArray *array);    
typedef cudaError_t (*cudaGetDeviceCount_t)(int *);
typedef cudaError_t (*cudaGetDeviceProperties_t)(struct cudaDeviceProp *, int);
typedef cudaError_t (*cudaGetLastError_t)(void);
typedef cudaError_t (*cudaGetTextureReference_t)(
    const struct textureReference **, const char *);

typedef cudaError_t (*cudaGetExportTable_t)(const void **ppExportTable,
        const cudaUUID_t *pExportTableId);
typedef cudaError_t (*cudaGetSurfaceReference_t)(
    const struct surfaceReference **surfRef, const char *symbol);
    
typedef cudaError_t (*cudaGraphicsMapResources_t)(int count,
        cudaGraphicsResource_t *resources, cudaStream_t stream);
typedef cudaError_t (*cudaGraphicsResourceGetMappedPointer_t)(void **devPtr,
    size_t *size, cudaGraphicsResource_t resource);
typedef cudaError_t (*cudaGraphicsResourceSetMapFlags_t)(
    cudaGraphicsResource_t resource, unsigned int flags);
typedef cudaError_t (*cudaGraphicsSubResourceGetMappedArray_t)(
    struct cudaArray **array, cudaGraphicsResource_t resource,
    unsigned int arrayIndex, unsigned int mipLevel);
typedef cudaError_t (*cudaGraphicsUnmapResources_t)(int count,
    cudaGraphicsResource_t *resources, cudaStream_t stream);
typedef cudaError_t (*cudaGraphicsUnregisterResource_t)(
    cudaGraphicsResource_t resource);
            
typedef cudaError_t (*cudaHostAlloc_t)(void **, size_t , unsigned int);
typedef cudaError_t (*cudaHostGetDevicePointer_t)(void **, void *,
    unsigned int);
typedef cudaError_t (*cudaHostGetFlags_t)(unsigned int *, void *);
typedef cudaError_t (*cudaHostRegister_t)(void *, size_t, unsigned int);
typedef cudaError_t (*cudaHostUnregister_t)(void *);
typedef cudaError_t (*cudaLaunch_t)(const char *);
typedef cudaError_t (*cudaMalloc_t)(void **, size_t);
typedef cudaError_t (*cudaMalloc3D_t)(struct cudaPitchedPtr *,
    struct cudaExtent);
typedef cudaError_t (*cudaMalloc3DArray_t)(struct cudaArray**,
    const struct cudaChannelFormatDesc*, struct cudaExtent, unsigned int);
typedef cudaError_t (*cudaMallocArray_t)(struct cudaArray**,
    const struct cudaChannelFormatDesc*, size_t, size_t, unsigned int);
typedef cudaError_t (*cudaMallocHost_t)(void **, size_t);
typedef cudaError_t (*cudaMallocPitch_t)(void **, size_t *, size_t, size_t);
typedef cudaError_t (*cudaMemcpy_t)(void *, const void *, size_t,
    cudaMemcpyKind);
typedef cudaError_t (*cudaMemcpyPeer_t)(void *dst, int dstDevice,
        const void *src, int srcDevice, size_t count);   
typedef cudaError_t (*cudaMemcpyPeerAsync_t)(void *dst, int dstDevice,
        const void *src, int srcDevice, size_t count, cudaStream_t stream);
typedef cudaError_t (*cudaMemcpy2D_t)(void *dst, size_t dpitch, const void *src,
        size_t pitch, size_t width, size_t height, enum cudaMemcpyKind kind);
typedef cudaError_t (*cudaMemcpy2DAsync_t)(void *dst, size_t dpitch,
        const void *src, size_t spitch, size_t width, size_t height,
        enum cudaMemcpyKind kind, cudaStream_t stream);        
typedef cudaError_t (*cudaMemcpy3D_t)(const struct cudaMemcpy3DParms *p);
typedef cudaError_t (*cudaMemcpy3DAsync_t)(const struct cudaMemcpy3DParms *p,
        cudaStream_t stream);
typedef cudaError_t (*cudaMemcpy3DPeer_t)(const struct cudaMemcpy3DPeerParms *p);
typedef cudaError_t (*cudaMemcpy3DPeerAsync_t)(
        const struct cudaMemcpy3DPeerParms *p, cudaStream_t stream);
typedef cudaError_t (*cudaMemcpyToArray_t)(struct cudaArray *, size_t, size_t,
		const void *, size_t, enum cudaMemcpyKind kind);
typedef cudaError_t (*cudaMemcpyToArrayAsync_t)(struct cudaArray *dst,
        size_t wOffset, size_t hOffset, const void *src, size_t count,
        enum cudaMemcpyKind kind, cudaStream_t stream);		
typedef cudaError_t (*cudaMemcpyArrayToArray_t)(struct cudaArray *dst,
        size_t wOffsetDst, size_t hOffsetDst, const struct cudaArray *src,
        size_t wOffsetSrc, size_t hOffsetSrc, size_t count,
        enum cudaMemcpyKind kind);        
typedef cudaError_t (*cudaMemcpyAsync_t)(void *, const void *, size_t,
    cudaMemcpyKind, cudaStream_t);
typedef cudaError_t (*cudaMemcpyFromArray_t)(void *dst,
        const struct cudaArray *src, size_t wOffset, size_t hOffset,
        size_t count, enum cudaMemcpyKind kind);
typedef cudaError_t (*cudaMemcpyFromArrayAsync_t)(void *dst,
    const struct cudaArray *src, size_t wOffset, size_t hOffset,
    size_t count, enum cudaMemcpyKind kind, cudaStream_t stream);

typedef cudaError_t (*cudaMemcpy2DArrayToArray_t)(struct cudaArray *dst,
        size_t wOffsetDst, size_t hOffsetDst, const struct cudaArray *src,
        size_t wOffsetSrc, size_t hOffsetSrc, size_t width, size_t height,
        enum cudaMemcpyKind kind);            
typedef cudaError_t (*cudaMemcpy2DFromArray_t)(void *dst, size_t dpitch,
        const struct cudaArray *src, size_t wOffset, size_t hOffset,
        size_t width, size_t height, enum cudaMemcpyKind kind);
typedef cudaError_t (*cudaMemcpy2DFromArrayAsync_t)(void *dst, size_t dpitch,
    const struct cudaArray *src, size_t wOffset, size_t hOffset,
    size_t width, size_t height, enum cudaMemcpyKind kind,
    cudaStream_t stream);
typedef cudaError_t (*cudaMemcpy2DToArray_t)(struct cudaArray *dst,
    size_t wOffset, size_t hOffset, const void *src, size_t spitch,
    size_t width, size_t height, enum cudaMemcpyKind kind);
typedef cudaError_t (*cudaMemcpy2DToArrayAsync_t)(struct cudaArray *dst,
    size_t wOffset, size_t hOFfset, const void *src, size_t spitch,
    size_t width, size_t height, enum cudaMemcpyKind kind,
    cudaStream_t stream);    
typedef cudaError_t (*cudaMemGetInfo_t)(size_t *, size_t *);
typedef cudaError_t (*cudaMemset_t)(void *, int, size_t);
typedef cudaError_t (*cudaMemsetAsync_t)(void *, int, size_t, cudaStream_t);
typedef cudaError_t (*cudaMemset2D_t)(void *devPtr, size_t pitch, int value,
        size_t width, size_t height);
typedef cudaError_t (*cudaMemset2DAsync_t)(void *devPtr, size_t pitch, int value,
    size_t width, size_t height, cudaStream_t stream);
typedef cudaError_t (*cudaMemset3D_t)(struct cudaPitchedPtr pitchedDevPtr,
    int value, struct cudaExtent extent);
typedef cudaError_t (*cudaMemset3DAsync_t)(struct cudaPitchedPtr pitchedDevPtr,
    int value, struct cudaExtent extent, cudaStream_t stream);

typedef cudaError_t (*cudaPointerGetAttributes_t)(
    struct cudaPointerAttributes *, void *);
typedef cudaError_t (*cudaRuntimeGetVersion_t)(int *);
typedef cudaError_t (*cudaSetDeviceFlags_t)(unsigned int);
typedef cudaError_t (*cudaSetDoubleForDevice_t)(double *);
typedef cudaError_t (*cudaSetDoubleForHost_t)(double *);

typedef cudaError_t (*cudaSetValidDevices_t)(int *device_arr, int len);

typedef cudaError_t (*cudaSetupArgument_t)(const void *, size_t, size_t);

typedef cudaError_t (*cudaStreamCreate_t)(cudaStream_t *);
typedef cudaError_t (*cudaStreamDestroy_t)(cudaStream_t);
typedef cudaError_t (*cudaStreamQuery_t)(cudaStream_t);
typedef cudaError_t (*cudaStreamSynchronize_t)(cudaStream_t);
typedef cudaError_t (*cudaStreamWaitEvent_t)(cudaStream_t, cudaEvent_t,
    unsigned int);
    
typedef cudaError_t (*cudaThreadGetCacheConfig_t)(
        enum cudaFuncCache *pCacheConfig);
typedef cudaError_t (*cudaThreadGetLimit_t)(size_t *pValue,
    enum cudaLimit limit);
typedef cudaError_t (*cudaThreadSetCacheConfig_t)(
    enum cudaFuncCache cacheConfig);
typedef cudaError_t (*cudaThreadSetLimit_t)(enum cudaLimit limit, size_t value);    
    
typedef cudaError_t (*cudaThreadSynchronize_t)();
typedef cudaError_t (*cudaUnbindTexture_t)(const struct textureReference *);

typedef void   (*registerFunction_t)(void **, const char *,
    char *, const char *, int, uint3 *, uint3 *, dim3 *, dim3 *, int *);
typedef void** (*registerFatBinary_t)(void *);
typedef void   (*unregisterFatBinary_t)(void **);


#define _CASE(x) case x: return #x;

const char*  cudaGetErrorString(cudaError_t error) {
	switch (error) {
	_CASE(cudaSuccess)
	_CASE(cudaErrorMissingConfiguration)
	_CASE(cudaErrorMemoryAllocation)
	_CASE(cudaErrorInitializationError)
	_CASE(cudaErrorLaunchFailure)
	_CASE(cudaErrorPriorLaunchFailure)
	_CASE(cudaErrorLaunchTimeout)
	_CASE(cudaErrorLaunchOutOfResources)
	_CASE(cudaErrorInvalidDeviceFunction)
	_CASE(cudaErrorInvalidConfiguration)
	_CASE(cudaErrorInvalidDevice)
	_CASE(cudaErrorInvalidValue)
	_CASE(cudaErrorInvalidPitchValue)
	_CASE(cudaErrorInvalidSymbol)
	_CASE(cudaErrorMapBufferObjectFailed)
	_CASE(cudaErrorUnmapBufferObjectFailed)
	_CASE(cudaErrorInvalidHostPointer)
	_CASE(cudaErrorInvalidDevicePointer)
	_CASE(cudaErrorInvalidTexture)
	_CASE(cudaErrorInvalidTextureBinding)
	_CASE(cudaErrorInvalidChannelDescriptor)
	_CASE(cudaErrorInvalidMemcpyDirection)
	_CASE(cudaErrorAddressOfConstant)
	_CASE(cudaErrorTextureFetchFailed)
	_CASE(cudaErrorTextureNotBound)
	_CASE(cudaErrorSynchronizationError)
	_CASE(cudaErrorInvalidFilterSetting)
	_CASE(cudaErrorInvalidNormSetting)
	_CASE(cudaErrorMixedDeviceExecution)
	_CASE(cudaErrorCudartUnloading)
	_CASE(cudaErrorUnknown)
	_CASE(cudaErrorNotYetImplemented)
	_CASE(cudaErrorMemoryValueTooLarge)
	_CASE(cudaErrorInvalidResourceHandle)
	_CASE(cudaErrorNotReady)
	_CASE(cudaErrorInsufficientDriver)
	_CASE(cudaErrorSetOnActiveProcess)
	_CASE(cudaErrorNoDevice)
	_CASE(cudaErrorStartupFailure)
	_CASE(cudaErrorApiFailureBase)
		default:
		break;
	}
	return "unimplemented";
}

cudaError_t CudaRuntimeInterface::cudaBindSurfaceToArray(
        const struct surfaceReference *surfref, const struct cudaArray *array,
        const struct cudaChannelFormatDesc *desc) {
    return((cudaBindSurfaceToArray_t)
        DYNLINK(cudaBindSurfaceToArray))
        (surfref, array, desc);       
}        

cudaError_t CudaRuntimeInterface::cudaBindTexture(size_t *offset,
        const struct textureReference *texref, const void *devPtr,
        const struct cudaChannelFormatDesc *desc, size_t size) {
    return ((cudaBindTexture_t) DYNLINK(cudaBindTexture))(offset, texref, devPtr, desc, size);
}

cudaError_t CudaRuntimeInterface::cudaBindTexture2D(size_t *offset,
        const struct textureReference *texref, const void *devPtr,
        const struct cudaChannelFormatDesc *desc, size_t width, size_t height,
        size_t pitch){
        return ((cudaBindTexture2D_t) DYNLINK(cudaBindTexture2D))
        (offset, texref, devPtr, desc, width, height, pitch);
}        

cudaError_t CudaRuntimeInterface::cudaChooseDevice(int *device,
        const struct cudaDeviceProp *prop) {
    return ((cudaChooseDevice_t) DYNLINK(cudaChooseDevice))(device, prop);        
}        

cudaError_t CudaRuntimeInterface::cudaConfigureCall(dim3 gridDim, dim3
        blockDim, size_t sharedMem, cudaStream_t stream) {
    return ((cudaConfigureCall_t)
        DYNLINK(cudaConfigureCall))(gridDim, blockDim, sharedMem, stream);
}

cudaError_t CudaRuntimeInterface::cudaDeviceGetLimit(size_t *pValue,
        enum cudaLimit limit) {
    return ((cudaDeviceGetLimit_t)
        DYNLINK(cudaDeviceGetLimit))
        (pValue, limit);     
}        
        
cudaError_t CudaRuntimeInterface::cudaDeviceSetLimit(enum cudaLimit limit, size_t value) {
    return ((cudaDeviceSetLimit_t)
        DYNLINK(cudaDeviceSetLimit))
        (limit, value);     
}        

cudaError_t CudaRuntimeInterface::cudaDeviceGetCacheConfig(enum cudaFuncCache *
        pCacheConfig) {
    return ((cudaDeviceGetCacheConfig_t) DYNLINK(cudaDeviceGetCacheConfig))
        (pCacheConfig);
}

cudaError_t CudaRuntimeInterface::cudaDeviceReset() {
    return ((cudaDeviceReset_t) DYNLINK(cudaDeviceReset))();
}

cudaError_t CudaRuntimeInterface::cudaDeviceSetCacheConfig(enum cudaFuncCache
        cacheConfig) {
        return ((cudaDeviceSetCacheConfig_t) DYNLINK(cudaDeviceSetCacheConfig))
            (cacheConfig);
}

cudaError_t CudaRuntimeInterface::cudaDeviceSynchronize() {
    return ((cudaDeviceSynchronize_t) DYNLINK(cudaDeviceSynchronize))();
}

cudaError_t CudaRuntimeInterface::cudaDriverGetVersion(int *driverVersion) {
    return ((cudaDriverGetVersion_t) DYNLINK(cudaDriverGetVersion))
        (driverVersion);
}

cudaError_t CudaRuntimeInterface::cudaEventCreate(cudaEvent_t *event) {
   return((cudaEventCreate_t) DYNLINK(cudaEventCreate))(event);
}

cudaError_t CudaRuntimeInterface::cudaEventCreateWithFlags(cudaEvent_t *event,
        unsigned int flags) {
    return ((cudaEventCreateWithFlags_t) DYNLINK(cudaEventCreateWithFlags))
        (event, flags);
}

cudaError_t CudaRuntimeInterface::cudaEventDestroy(cudaEvent_t event) {
    return ((cudaEventDestroy_t) DYNLINK(cudaEventDestroy))
        (event);
}

cudaError_t CudaRuntimeInterface::cudaEventElapsedTime(float *ms, cudaEvent_t start,
        cudaEvent_t end) {
    return ((cudaEventElapsedTime_t) DYNLINK(cudaEventElapsedTime))
        (ms, start, end);
}

cudaError_t CudaRuntimeInterface::cudaEventQuery(cudaEvent_t event) {
    return ((cudaEventQuery_t) DYNLINK(cudaEventQuery))(event);
}

cudaError_t CudaRuntimeInterface::cudaEventRecord(cudaEvent_t event, cudaStream_t stream) {
    return ((cudaEventRecord_t) DYNLINK(cudaEventRecord))(event, stream);
}

cudaError_t CudaRuntimeInterface::cudaEventSynchronize(cudaEvent_t event) {
    return ((cudaEventSynchronize_t) DYNLINK(cudaEventSynchronize))
    	(event);
}

cudaError_t CudaRuntimeInterface::cudaFree(void *devPtr) {
   return ((cudaFree_t) DYNLINK(cudaFree))
    	(devPtr);
}

cudaError_t CudaRuntimeInterface::cudaFreeArray(struct cudaArray * array) {
    return ((cudaFreeArray_t) DYNLINK(cudaFreeArray))
    	(array);
}

cudaError_t CudaRuntimeInterface::cudaFreeHost(void *ptr) {
    return ((cudaFreeHost_t) DYNLINK(cudaFreeHost))
    	(ptr);
}

cudaError_t CudaRuntimeInterface::cudaFuncGetAttributes(struct cudaFuncAttributes *attr,
        const void *func) {
    return ((cudaFuncGetAttributes_t) DYNLINK(cudaFuncGetAttributes))
    	(attr, func);           
}        

cudaError_t CudaRuntimeInterface::cudaFuncSetCacheConfig(const void *func,
        enum cudaFuncCache cacheConfig) {
    return ((cudaFuncSetCacheConfig_t) DYNLINK(cudaFuncSetCacheConfig))
    	(func, cacheConfig);
}

struct cudaChannelFormatDesc CudaRuntimeInterface::cudaCreateChannelDesc(int x, int y, int z,
        int w, enum cudaChannelFormatKind f) {
    return ((cudaCreateChannelDesc_t) DYNLINK(cudaCreateChannelDesc))
        (x, y, z, w, f);           
}        

cudaError_t CudaRuntimeInterface::cudaGetChannelDesc(
        struct cudaChannelFormatDesc *desc,
        const struct cudaArray *array) {
        return ((cudaGetChannelDesc_t) DYNLINK(cudaGetChannelDesc))
    	(desc, array);
}        

cudaError_t CudaRuntimeInterface::cudaGetDeviceCount(int * count) {
    return ((cudaGetDeviceCount_t) DYNLINK(cudaGetDeviceCount))
    	(count);
}

cudaError_t CudaRuntimeInterface::cudaGetDeviceProperties(struct cudaDeviceProp *prop,
        int device) {
    return ((cudaGetDeviceProperties_t)
        DYNLINK(cudaGetDeviceProperties))
    	(prop, device);
}

cudaError_t CudaRuntimeInterface::cudaGetLastError() {
    return ((cudaGetLastError_t)
        DYNLINK(cudaGetLastError))
    	();
}

cudaError_t CudaRuntimeInterface::cudaGetTextureReference(
        const struct textureReference **texref, const char *symbol) {
    return ((cudaGetTextureReference_t)
        DYNLINK(cudaGetTextureReference))
    	(texref, symbol);
}

cudaError_t CudaRuntimeInterface::cudaGetExportTable(const void **ppExportTable,
        const cudaUUID_t *pExportTableId) {
    return ((cudaGetExportTable_t)
        DYNLINK(cudaGetExportTable))
        (ppExportTable, pExportTableId);
}        
        
cudaError_t CudaRuntimeInterface::cudaGetSurfaceReference(
    const struct surfaceReference **surfRef, const char *symbol) {
    return ((cudaGetSurfaceReference_t)
        DYNLINK(cudaGetSurfaceReference))
        (surfRef, symbol);
}        

cudaError_t CudaRuntimeInterface::cudaGraphicsMapResources(int count,
        cudaGraphicsResource_t *resources, cudaStream_t stream) {
    return ((cudaGraphicsMapResources_t)
        DYNLINK(cudaGraphicsMapResources))
        (count, resources, stream);
}        
        
cudaError_t CudaRuntimeInterface::cudaGraphicsResourceGetMappedPointer(void **devPtr,
    size_t *size, cudaGraphicsResource_t resource) {
    return ((cudaGraphicsResourceGetMappedPointer_t)
        DYNLINK(cudaGraphicsResourceGetMappedPointer))
        (devPtr, size, resource);
}        
    
cudaError_t CudaRuntimeInterface::cudaGraphicsResourceSetMapFlags(
    cudaGraphicsResource_t resource, unsigned int flags) {
    return ((cudaGraphicsResourceSetMapFlags_t)
        DYNLINK(cudaGraphicsResourceSetMapFlags))
        (resource, flags);
}        
    
cudaError_t CudaRuntimeInterface::cudaGraphicsSubResourceGetMappedArray(
    struct cudaArray **array, cudaGraphicsResource_t resource,
    unsigned int arrayIndex, unsigned int mipLevel) {
    return ((cudaGraphicsSubResourceGetMappedArray_t)
        DYNLINK(cudaGraphicsSubResourceGetMappedArray))
        (array, resource, arrayIndex, mipLevel);
}        
    
cudaError_t CudaRuntimeInterface::cudaGraphicsUnmapResources(int count,
    cudaGraphicsResource_t *resources, cudaStream_t stream) {
    return ((cudaGraphicsUnmapResources_t)
        DYNLINK(cudaGraphicsUnmapResources))
        (count, resources, stream);
}        
    
cudaError_t CudaRuntimeInterface::cudaGraphicsUnregisterResource(
    cudaGraphicsResource_t resource) {
    return ((cudaGraphicsUnregisterResource_t)
        DYNLINK(cudaGraphicsUnregisterResource))
        (resource);
}        

cudaError_t CudaRuntimeInterface::cudaHostAlloc(void **pHost, size_t size,
        unsigned int flags) {
    return ((cudaHostAlloc_t)
         DYNLINK(cudaHostAlloc))
    	(pHost, size, flags);
}

cudaError_t CudaRuntimeInterface::cudaHostGetDevicePointer(void **pDevice, void *pHost,
        unsigned int flags) {
    return ((cudaHostGetDevicePointer_t)
         DYNLINK(cudaHostGetDevicePointer))
    	(pDevice, pHost, flags);
}

cudaError_t CudaRuntimeInterface::cudaHostGetFlags(unsigned int *pFlags, void *pHost) {
    return ((cudaHostGetFlags_t)
         DYNLINK(cudaHostGetFlags))
    	(pFlags, pHost);
}

cudaError_t CudaRuntimeInterface::cudaHostRegister(void *ptr, size_t size,
        unsigned int flags) {
    return ((cudaHostRegister_t)
         DYNLINK(cudaHostRegister))
    	(ptr, size, flags);
}

cudaError_t CudaRuntimeInterface::cudaHostUnregister(void *ptr) {
    return ((cudaHostUnregister_t)
         DYNLINK(cudaHostUnregister))
    	(ptr);
}

cudaError_t CudaRuntimeInterface::cudaIpcGetEventHandle(cudaIpcEventHandle_t *handle,
        cudaEvent_t event) {
        return ((cudaIpcGetEventHandle_t)
         DYNLINK(cudaIpcGetEventHandle))
    	(handle, event);
}        

cudaError_t CudaRuntimeInterface::cudaIpcOpenEventHandle(cudaEvent_t *event,
        cudaIpcEventHandle_t handle) {   
    return ((cudaIpcOpenEventHandle_t)
         DYNLINK(cudaIpcOpenEventHandle))
    	(event, handle);
}                

cudaError_t CudaRuntimeInterface::cudaIpcGetMemHandle(cudaIpcMemHandle_t *handle,
        void *devPtr) {   
    return ((cudaIpcGetMemHandle_t)
         DYNLINK(cudaIpcGetMemHandle))
    	(handle, devPtr);
}                

cudaError_t CudaRuntimeInterface::cudaIpcOpenMemHandle(void **devPtr,
        cudaIpcMemHandle_t handle, unsigned int flags) {   
    return ((cudaIpcOpenMemHandle_t)
         DYNLINK(cudaIpcOpenMemHandle))
    	(devPtr, handle, flags);
}                

cudaError_t CudaRuntimeInterface::cudaIpcCloseMemHandle(void *devPtr) {   
    return ((cudaIpcCloseMemHandle_t)
         DYNLINK(cudaIpcGetMemHandle))
    	(devPtr);
}                

cudaError_t CudaRuntimeInterface::cudaLaunch(const char *entry) {
    return ((cudaLaunch_t)
        DYNLINK(cudaLaunch))
    	(entry);
}

cudaError_t CudaRuntimeInterface::cudaMalloc(void **devPtr, size_t size) {
    return ((cudaMalloc_t)
        DYNLINK(cudaMalloc))
    	(devPtr, size);
}

cudaError_t CudaRuntimeInterface::cudaMalloc3D(struct cudaPitchedPtr *pitchedDevPtr, struct
        cudaExtent extent) {
    return ((cudaMalloc3D_t)
        DYNLINK(cudaMalloc3D))
    	(pitchedDevPtr, extent);
}

cudaError_t CudaRuntimeInterface::cudaMalloc3DArray(struct cudaArray** array, const struct
        cudaChannelFormatDesc *desc, struct cudaExtent extent, unsigned int
        flags) {
    return ((cudaMalloc3DArray_t)
        DYNLINK(cudaMalloc3DArray))
    	(array, desc, extent, flags);
}

cudaError_t CudaRuntimeInterface::cudaMallocArray(struct cudaArray **array,
        const struct cudaChannelFormatDesc *desc, size_t width, size_t height,
        unsigned int flags) {
   return ((cudaMallocArray_t)
        DYNLINK(cudaMallocArray))
    	(array, desc, width, height, flags);
}

cudaError_t CudaRuntimeInterface::cudaMallocHost(void **ptr, size_t size) {
    return ((cudaMallocHost_t)
        DYNLINK(cudaMallocHost))
    	(ptr, size);
}

cudaError_t CudaRuntimeInterface::cudaMallocPitch(void **devPtr, size_t *pitch,
        size_t width, size_t height) {
    return ((cudaMallocPitch_t)
        DYNLINK(cudaMallocPitch))
    	(devPtr, pitch, width, height);
}

cudaError_t CudaRuntimeInterface::cudaMemcpy(void *dst, const void *src, size_t count,
        cudaMemcpyKind kind) {
    return ((cudaMemcpy_t)
        DYNLINK(cudaMemcpy))
    	(dst, src, count, kind);
}

cudaError_t CudaRuntimeInterface::cudaMemcpyPeer(void *dst, int dstDevice,
        const void *src, int srcDevice, size_t count) {
        return ((cudaMemcpyPeer_t)
        DYNLINK(cudaMemcpyPeer))
    	(dst, dstDevice, src, srcDevice, count);
}        

cudaError_t CudaRuntimeInterface::cudaMemcpyPeerAsync(void *dst, int dstDevice,
        const void *src, int srcDevice, size_t count, cudaStream_t stream) {
        return ((cudaMemcpyPeerAsync_t)
        DYNLINK(cudaMemcpyPeerAsync))
    	(dst, dstDevice, src, srcDevice, count, stream);
}     

cudaError_t CudaRuntimeInterface::cudaMemcpy2D(void *dst, size_t dpitch, const void *src,
        size_t pitch, size_t width, size_t height, enum cudaMemcpyKind kind) {
        return ((cudaMemcpy2D_t)
        DYNLINK(cudaMemcpy2D))
    	(dst, dpitch, src, pitch, width, height, kind);  
}

cudaError_t CudaRuntimeInterface::cudaMemcpy2DAsync(void *dst, size_t dpitch, const void *src,
        size_t pitch, size_t width, size_t height, enum cudaMemcpyKind kind, cudaStream_t stream) {
        return ((cudaMemcpy2DAsync_t)
        DYNLINK(cudaMemcpy2DAsync))
    	(dst, dpitch, src, pitch, width, height, kind, stream);  
}

cudaError_t CudaRuntimeInterface::cudaMemcpy3D(const struct cudaMemcpy3DParms *p){
    return ((cudaMemcpy3D_t)
        DYNLINK(cudaMemcpy3D))
    	(p);
}

cudaError_t CudaRuntimeInterface::cudaMemcpy3DAsync(const struct cudaMemcpy3DParms *p,
        cudaStream_t stream) {
    return ((cudaMemcpy3DAsync_t)
    DYNLINK(cudaMemcpy3DAsync))
    (p, stream);        
}        
        
cudaError_t CudaRuntimeInterface::cudaMemcpy3DPeer(const struct cudaMemcpy3DPeerParms *p) {
    return ((cudaMemcpy3DPeer_t)
    DYNLINK(cudaMemcpy3DPeer))
    (p);          
}

cudaError_t CudaRuntimeInterface::cudaMemcpy3DPeerAsync(
        const struct cudaMemcpy3DPeerParms *p, cudaStream_t stream) {
    return ((cudaMemcpy3DPeerAsync_t)
    DYNLINK(cudaMemcpy3DPeerAsync))
    (p, stream);          
}

cudaError_t CudaRuntimeInterface::cudaMemcpyToArray(struct cudaArray *dst, 
        size_t wOffset, size_t hOffset, const void *src, size_t count,
		enum cudaMemcpyKind kind) {
    return ((cudaMemcpyToArray_t) DYNLINK(cudaMemcpyToArray))
        (dst, wOffset, hOffset, src, count, kind);
} 	

cudaError_t CudaRuntimeInterface::cudaMemcpyToArrayAsync(struct cudaArray *dst,
        size_t wOffset, size_t hOffset, const void *src, size_t count,
        enum cudaMemcpyKind kind, cudaStream_t stream) {
        return ((cudaMemcpyToArrayAsync_t) DYNLINK(cudaMemcpyToArrayAsync))
        (dst, wOffset, hOffset, src, count, kind, stream);
}

cudaError_t CudaRuntimeInterface::cudaMemcpy2DArrayToArray(struct cudaArray *dst,
        size_t wOffsetDst, size_t hOffsetDst, const struct cudaArray *src,
        size_t wOffsetSrc, size_t hOffsetSrc, size_t width, size_t height,
        enum cudaMemcpyKind kind) {
    return ((cudaMemcpy2DArrayToArray_t)
        DYNLINK(cudaMemcpy2DArrayToArray))
        (dst, wOffsetDst, hOffsetDst, src, wOffsetSrc, hOffsetSrc, width, height, kind);       
}        
        
cudaError_t CudaRuntimeInterface::cudaMemcpy2DFromArray(void *dst, size_t dpitch,
        const struct cudaArray *src, size_t wOffset, size_t hOffset,
        size_t width, size_t height, enum cudaMemcpyKind kind){
        return ((cudaMemcpy2DFromArray_t) DYNLINK(cudaMemcpy2DFromArray))
        (dst, dpitch, src, wOffset, hOffset, width, height, kind);
}

cudaError_t CudaRuntimeInterface::cudaMemcpy2DFromArrayAsync(void *dst, size_t dpitch,
        const struct cudaArray *src, size_t wOffset, size_t hOffset,
        size_t width, size_t height, enum cudaMemcpyKind kind,
        cudaStream_t stream){
        return ((cudaMemcpy2DFromArrayAsync_t) DYNLINK(cudaMemcpy2DFromArrayAsync))
        (dst, dpitch, src, wOffset, hOffset, width, height, kind, stream);
}

cudaError_t CudaRuntimeInterface::cudaMemcpy2DToArray(struct cudaArray *dst,
        size_t wOffset, size_t hOffset, const void *src, size_t spitch,
        size_t width, size_t height, enum cudaMemcpyKind kind){
        return ((cudaMemcpy2DToArray_t) DYNLINK(cudaMemcpy2DToArray))
        (dst, wOffset, hOffset, src, spitch, width, height, kind);
        
}

cudaError_t CudaRuntimeInterface::cudaMemcpy2DToArrayAsync(struct cudaArray *dst,
        size_t wOffset, size_t hOffset, const void *src, size_t spitch,
        size_t width, size_t height, enum cudaMemcpyKind kind,
        cudaStream_t stream){
        return ((cudaMemcpy2DToArrayAsync_t) DYNLINK(cudaMemcpy2DToArrayAsync))
        (dst, wOffset, hOffset, src, spitch, width, height, kind, stream);
}


cudaError_t CudaRuntimeInterface::cudaMemcpyArrayToArray(struct cudaArray *dst,
        size_t wOffsetDst, size_t hOffsetDst, const struct cudaArray *src,
        size_t wOffsetSrc, size_t hOffsetSrc, size_t count,
        enum cudaMemcpyKind kind) {
        return ((cudaMemcpyArrayToArray_t)
        DYNLINK(cudaMemcpyArrayToArray))
        (dst, wOffsetDst, hOffsetDst, src, wOffsetSrc, hOffsetSrc, count, kind);
        
}
        
cudaError_t CudaRuntimeInterface::cudaMemcpyAsync(void *dst, const void *src, size_t count,
        cudaMemcpyKind kind, cudaStream_t stream) {
    return ((cudaMemcpyAsync_t)
        DYNLINK(cudaMemcpyAsync))
    	(dst, src, count, kind, stream);
}

cudaError_t CudaRuntimeInterface::cudaMemcpyFromArray(void *dst,
        const struct cudaArray *src, size_t wOffset, size_t hOffset,
        size_t count, enum cudaMemcpyKind kind) {
    return ((cudaMemcpyFromArray_t)
        DYNLINK(cudaMemcpyFromArray))
        (dst, src, wOffset, hOffset, count, kind); 
}        
        
cudaError_t CudaRuntimeInterface::cudaMemcpyFromArrayAsync(void *dst,
        const struct cudaArray *src, size_t wOffset, size_t hOffset,
        size_t count, enum cudaMemcpyKind kind, cudaStream_t stream) {
    return ((cudaMemcpyFromArrayAsync_t)
        DYNLINK(cudaMemcpyFromArrayAsync))
        (dst, src, wOffset, hOffset, count, kind, stream);        
}        

cudaError_t CudaRuntimeInterface::cudaMemGetInfo(size_t *free, size_t *total) {
    return ((cudaMemGetInfo_t)
        DYNLINK(cudaMemGetInfo))
    	(free, total);
}

cudaError_t CudaRuntimeInterface::cudaMemset(void *devPtr, int value, size_t count) {
    return ((cudaMemset_t)
        DYNLINK(cudaMemset))
    	(devPtr, value, count);
}

cudaError_t CudaRuntimeInterface::cudaMemset2D(void *devPtr, size_t pitch, int value,
        size_t width, size_t height) {
    return((cudaMemset2D_t)
        DYNLINK(cudaMemset2D))
        (devPtr, pitch, value, width, height);        
}
        
cudaError_t CudaRuntimeInterface::cudaMemset2DAsync(void *devPtr, size_t pitch, int value,
        size_t width, size_t height, cudaStream_t stream) {
    return((cudaMemset2DAsync_t)
        DYNLINK(cudaMemset2DAsync))
        (devPtr, pitch, value, width, height, stream);        
}
cudaError_t CudaRuntimeInterface::cudaMemset3D(struct cudaPitchedPtr pitchedDevPtr,
        int value, struct cudaExtent extent) {
    return((cudaMemset3D_t)
        DYNLINK(cudaMemset3D))
        (pitchedDevPtr, value, extent);        
}
        
cudaError_t CudaRuntimeInterface::cudaMemset3DAsync(struct cudaPitchedPtr pitchedDevPtr,
        int value, struct cudaExtent extent, cudaStream_t stream) {
        return((cudaMemset3DAsync_t)
        DYNLINK(cudaMemset3DAsync))
        (pitchedDevPtr, value, extent, stream);     
}        

cudaError_t CudaRuntimeInterface::cudaMemsetAsync(void *devPtr, int value, size_t count,
        cudaStream_t stream) {
    return ((cudaMemsetAsync_t)
        DYNLINK(cudaMemsetAsync))
    	(devPtr, value, count, stream);
}

cudaError_t CudaRuntimeInterface::cudaPointerGetAttributes(
        struct cudaPointerAttributes *attributes, void *ptr) {
    return ((cudaPointerGetAttributes_t) DYNLINK(cudaPointerGetAttributes))
    	(attributes, ptr);
}

cudaError_t CudaRuntimeInterface::cudaRuntimeGetVersion(int *runtimeVersion) {
    cudart = dlopen("libcudart.so", RTLD_LAZY);
    assert(cudart);
    return ((cudaRuntimeGetVersion_t)
        DYNLINK(cudaRuntimeGetVersion))(runtimeVersion);
}

cudaError_t CudaRuntimeInterface::cudaSetDeviceFlags(unsigned int flags) {
    return ((cudaSetDeviceFlags_t)
        DYNLINK(cudaSetDeviceFlags))
    	(flags);
}

cudaError_t CudaRuntimeInterface::cudaSetDoubleForDevice(double *d) {
    return ((cudaSetDoubleForDevice_t)
        DYNLINK(cudaSetDoubleForDevice))
    	(d);
}

cudaError_t CudaRuntimeInterface::cudaSetDoubleForHost(double *d) {
    return ((cudaSetDoubleForHost_t)
        DYNLINK(cudaSetDoubleForHost))
    	(d);
}

cudaError_t CudaRuntimeInterface::cudaSetupArgument(const void *arg, size_t size, size_t
        offset) {
    return ((cudaSetupArgument_t)
        DYNLINK(cudaSetupArgument))
    	(arg, size, offset);
}

cudaError_t CudaRuntimeInterface::cudaSetValidDevices(int *device_arr, int len) {
    return ((cudaSetValidDevices_t)
        DYNLINK(cudaSetValidDevices))
        (device_arr, len);
}

cudaError_t CudaRuntimeInterface::cudaStreamCreate(cudaStream_t *pStream) {
    return ((cudaStreamCreate_t)
        DYNLINK(cudaStreamCreate))
    	(pStream);
}

cudaError_t CudaRuntimeInterface::cudaStreamDestroy(cudaStream_t stream) {
    return ((cudaStreamDestroy_t)
        DYNLINK(cudaStreamDestroy))
    	(stream);
}

cudaError_t CudaRuntimeInterface::cudaStreamQuery(cudaStream_t stream) {
    return ((cudaStreamQuery_t)
        DYNLINK(cudaStreamQuery))
    	(stream);
}

cudaError_t CudaRuntimeInterface::cudaStreamSynchronize(cudaStream_t stream) {
    return ((cudaStreamSynchronize_t)
        DYNLINK(cudaStreamSynchronize))
    	(stream);
}

cudaError_t CudaRuntimeInterface::cudaStreamWaitEvent(cudaStream_t stream,
        cudaEvent_t event, unsigned int flags) {
    return ((cudaStreamWaitEvent_t)
        DYNLINK(cudaStreamWaitEvent))
    	(stream, event, flags);
}

cudaError_t CudaRuntimeInterface::cudaThreadGetCacheConfig(
        enum cudaFuncCache *pCacheConfig) {
    return ((cudaThreadGetCacheConfig_t)
        DYNLINK(cudaThreadGetCacheConfig))
        (pCacheConfig); 
}        
        
cudaError_t CudaRuntimeInterface::cudaThreadGetLimit(size_t *pValue,
        enum cudaLimit limit) {
    return ((cudaThreadGetLimit_t)
        DYNLINK(cudaThreadGetLimit))
        (pValue, limit); 
}   
     
cudaError_t CudaRuntimeInterface::cudaThreadSetCacheConfig(
        enum cudaFuncCache cacheConfig) {
    return ((cudaThreadSetCacheConfig_t)
        DYNLINK(cudaThreadSetCacheConfig))
        (cacheConfig); 
}
        
cudaError_t CudaRuntimeInterface::cudaThreadSetLimit(enum cudaLimit limit, size_t value) {
    return ((cudaThreadSetLimit_t)
        DYNLINK(cudaThreadSetLimit))
        (limit, value); 
}        

cudaError_t CudaRuntimeInterface::cudaThreadSynchronize() {
    return ((cudaDeviceSynchronize_t) DYNLINK(cudaDeviceSynchronize))
    	();
}

void CudaRuntimeInterface::cudaRegisterFunction(void **fatCubinHandle, const char *hostFun,
        char *deviceFun, const char *deviceName, int thread_limit, uint3 *tid,
        uint3 *bid, dim3 *bDim, dim3 *gDim, int *wSize) {
    return ((registerFunction_t)
        DYNLINK(__cudaRegisterFunction))
    	(fatCubinHandle, hostFun, deviceFun, deviceName,
        thread_limit, tid, bid, bDim, gDim, wSize);
}

void** CudaRuntimeInterface::cudaRegisterFatBinary(void *fatCubin) {
    return ((registerFatBinary_t)
        DYNLINK(__cudaRegisterFatBinary))
    	(fatCubin);
}

void CudaRuntimeInterface::cudaUnregisterFatBinary(void **fatCubinHandle) {
    return ((unregisterFatBinary_t)
        DYNLINK(__cudaUnregisterFatBinary))
    	(fatCubinHandle);
}

cudaError_t CudaRuntimeInterface::cudaUnbindTexture(const struct textureReference *texref) {
    return ((cudaUnbindTexture_t) DYNLINK(cudaUnbindTexture))
    	(texref);
}



