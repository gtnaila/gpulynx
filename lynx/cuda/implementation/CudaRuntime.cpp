/*! \file CudaRuntime.cpp
	\date Friday June 22, 2012
	\author Naila Farooqui <naila@cc.gatech.edu>
	\brief The source file for the CUDA Runtime (interposer)
*/

#include <lynx/cuda/interface/CudaRuntimeInterface.h>
#include <cassert>
#include <lynx/cuda/interface/CudaContext.h>
#include <cstdio>
#include <cstring>
#include <cuda_runtime_api.h>
#include <crt/host_runtime.h>
#include <lynx/cuda/interface/CudaRuntimeContext.h>
#include <lynx/cuda/interface/CudaRuntime.h>
#include <map>

#ifdef REPORT_BASE
#undef REPORT_BASE
#endif

// whether debugging messages are printed
#define REPORT_BASE 0

using namespace cuda;

#ifdef __CPLUSPLUS
 {
#endif

extern "C"
void** __cudaRegisterFatBinary(void *fatCubin) {
    return CudaRuntimeContext::instance().cudaRegisterFatBinary(fatCubin);
}

typedef std::map<const char *, std::string> func_map_t;
func_map_t func_to_name;

extern "C"
void __cudaRegisterFunction(void **fatCubinHandle, const char *hostFun,
        char *deviceFun, const char *deviceName, int thread_limit, uint3 *tid,
        uint3 *bid, dim3 *bDim, dim3 *gDim, int *wSize) {
    
    CudaRuntimeContext::instance().cudaRegisterFunction(
        fatCubinHandle, hostFun, deviceFun, deviceName, thread_limit, tid,
        bid, bDim, gDim, wSize);
}

extern "C"
void __cudaRegisterTexture(void **fatCubinHandle,
        const struct textureReference *hostVar, const void **deviceAddress,
        const char *deviceName, int dim, int norm, int ext) {
    CudaRuntimeContext::instance().cudaRegisterTexture(
        fatCubinHandle, hostVar, deviceAddress, deviceName,
        dim, norm, ext);
}

extern "C"
void __cudaRegisterVar(void **fatCubinHandle,char *hostVar,
        char *deviceAddress, const char *deviceName, int ext, int size,
        int constant, int global) {
    CudaRuntimeContext::instance().cudaRegisterVar(fatCubinHandle, hostVar,
        deviceAddress, deviceName, ext, size, constant, global);
}

extern "C"
void __cudaUnregisterFatBinary(void **fatCubinHandle) {
    CudaRuntimeContext::instance().cudaUnregisterFatBinary(fatCubinHandle);
}

cudaError_t cudaBindSurfaceToArray(const struct surfaceReference *surfref,
        const struct cudaArray *array,
        const struct cudaChannelFormatDesc *desc) {
    return CudaRuntimeContext::instance().context().cudaBindSurfaceToArray(
        surfref, array, desc);
}

cudaError_t cudaBindTexture(size_t *offset,
        const struct textureReference *texref, const void *devPtr,
        const struct cudaChannelFormatDesc *desc, size_t size) {
    return CudaRuntimeContext::instance().context().cudaBindTexture(
        offset, texref, devPtr, desc, size);
}

cudaError_t cudaBindTexture2D(size_t *offset, const struct
        textureReference *texref, const void *devPtr, const struct
        cudaChannelFormatDesc *desc, size_t width, size_t height, size_t
        pitch) {
    return CudaRuntimeContext::instance().context().cudaBindTexture2D(
        offset, texref, devPtr, desc, width, height, pitch);
}

cudaError_t cudaBindTextureToArray(const struct textureReference *texref,
        const struct cudaArray *array, const struct
        cudaChannelFormatDesc *desc) {
    return CudaRuntimeContext::instance().context().cudaBindTextureToArray(
        texref, array, desc);
}

cudaError_t cudaChooseDevice(int *device, const struct cudaDeviceProp *prop) {
    return CudaRuntimeContext::instance().context().cudaChooseDevice(device,
        prop);
}

cudaError_t cudaConfigureCall(dim3 gridDim, dim3 blockDim,
        size_t sharedMem, cudaStream_t stream) {
    return CudaRuntimeContext::instance().context().cudaConfigureCall(gridDim,
        blockDim, sharedMem, stream);
}

cudaError_t cudaDeviceCanAccessPeer(int *canAccessPeer, int device, int
        peerDevice) {
    return CudaRuntimeContext::instance().cudaDeviceCanAccessPeer(
        canAccessPeer, device, peerDevice);
}

cudaError_t cudaDeviceDisablePeerAccess(int peerDevice) {
    return CudaRuntimeContext::instance().cudaDeviceDisablePeerAccess(peerDevice);
}

cudaError_t cudaDeviceEnablePeerAccess(int peerDevice, unsigned int flags) {
    return CudaRuntimeContext::instance().cudaDeviceEnablePeerAccess(
        peerDevice, flags);
}

cudaError_t cudaDeviceGetByPCIBusId(int *device, char *pciBusId) {
    return CudaRuntimeContext::instance().cudaDeviceGetByPCIBusId(device,
        pciBusId);
}

cudaError_t cudaDeviceGetCacheConfig(enum cudaFuncCache *pCacheConfig) {
    return CudaRuntimeContext::instance().context().cudaDeviceGetCacheConfig(
        pCacheConfig);
}

cudaError_t cudaDeviceGetLimit(size_t *pValue, enum cudaLimit limit) {
    return CudaRuntimeContext::instance().context().cudaDeviceGetLimit(
        pValue, limit);
}

cudaError_t cudaDeviceGetPCIBusId(char *pciBusId, int len, int device) {
    return CudaRuntimeContext::instance().cudaDeviceGetPCIBusId(pciBusId,
        len, device);
}

cudaError_t cudaDeviceReset() {
    return CudaRuntimeContext::instance().cudaDeviceReset();
}

cudaError_t cudaDeviceSetCacheConfig(enum cudaFuncCache cacheConfig) {
    return CudaRuntimeContext::instance().context().cudaDeviceSetCacheConfig(
        cacheConfig);
}

cudaError_t cudaDeviceSetLimit(enum cudaLimit limit, size_t value) {
    return CudaRuntimeContext::instance().context().cudaDeviceSetLimit(
        limit, value);
}

cudaError_t cudaDeviceSynchronize() {
    return CudaRuntimeContext::instance().context().cudaDeviceSynchronize();
}

cudaError_t cudaDriverGetVersion(int *driverVersion) {
    return CudaRuntimeContext::instance().context().cudaDriverGetVersion(
        driverVersion);
}

cudaError_t cudaEventCreate(cudaEvent_t *event) {
    return CudaRuntimeContext::instance().context().cudaEventCreate(event);
}

cudaError_t cudaEventCreateWithFlags(cudaEvent_t *event, unsigned int flags) {
    return CudaRuntimeContext::instance().context().cudaEventCreateWithFlags(
        event, flags);
}

cudaError_t cudaEventDestroy(cudaEvent_t event) {
    return CudaRuntimeContext::instance().context().cudaEventDestroy(event);
}

cudaError_t cudaEventElapsedTime(float *ms, cudaEvent_t start,
        cudaEvent_t end) {
    

    return CudaRuntimeContext::instance().context().cudaEventElapsedTime(
        ms, start, end);
}

cudaError_t cudaEventQuery(cudaEvent_t event) {
    return CudaRuntimeContext::instance().context().cudaEventQuery(event);
}

cudaError_t cudaEventRecord(cudaEvent_t event, cudaStream_t stream) {
    return CudaRuntimeContext::instance().context().cudaEventRecord(event,
        stream);
}

cudaError_t cudaEventSynchronize(cudaEvent_t event) {
    return CudaRuntimeContext::instance().context().cudaEventSynchronize(event);
}

cudaError_t cudaFree(void *devPtr) {
    return CudaRuntimeContext::instance().context().cudaFree(devPtr);
}

cudaError_t cudaFreeArray(struct cudaArray *array) {
    return CudaRuntimeContext::instance().context().cudaFreeArray(array);
}

cudaError_t cudaFreeHost(void *ptr) {
    return CudaRuntimeContext::instance().context().cudaFreeHost(ptr);
}

cudaError_t cudaFuncGetAttributes(struct cudaFuncAttributes *attr, const
        void *func) {
    return CudaRuntimeContext::instance().context().cudaFuncGetAttributes(
        attr, func);
}

cudaError_t cudaFuncSetCacheConfig(const void *func, enum cudaFuncCache
        cacheConfig) {
    return CudaRuntimeContext::instance().context().cudaFuncSetCacheConfig(
        func, cacheConfig);
}

cudaError_t cudaGetChannelDesc(struct cudaChannelFormatDesc *desc, const
        struct cudaArray *array) {
    return CudaRuntimeContext::instance().context().cudaGetChannelDesc(desc,
        array);
}

cudaError_t cudaGetDevice(int *device) {
    return CudaRuntimeContext::instance().cudaGetDevice(device);
}

cudaError_t cudaGetDeviceCount(int *count) {
    return CudaRuntimeContext::instance().cudaGetDeviceCount(count);
}

cudaError_t cudaGetDeviceProperties(struct cudaDeviceProp *prop, int device) {
    return CudaRuntimeContext::instance().context().cudaGetDeviceProperties(
        prop, device);
}

/**
 * Not implemented:
 *
 * const char * cudaGetErrorString(cudaError_t error);
 */

cudaError_t cudaGetExportTable(const void **ppExportTable, const cudaUUID_t
        *pExportTableId) {
    return CudaRuntimeContext::instance().context().cudaGetExportTable(
        ppExportTable, pExportTableId);
}

cudaError_t cudaGetLastError(void) {
    return CudaRuntimeContext::instance().context().cudaGetLastError();
}

cudaError_t cudaGetSurfaceReference(const struct surfaceReference **surfRef,
        const char *symbol) {
    return CudaRuntimeContext::instance().context().cudaGetSurfaceReference(
        surfRef, symbol);
}

cudaError_t cudaGetSymbolAddress(void **devPtr, const char *symbol) {
    return CudaRuntimeContext::instance().context().cudaGetSymbolAddress(
        devPtr, symbol);
}

cudaError_t cudaGetSymbolSize(size_t *size, const char *symbol) {
    return CudaRuntimeContext::instance().context().cudaGetSymbolSize(size,
        symbol);
}

cudaError_t cudaGetTextureAlignmentOffset(size_t *offset, const struct
        textureReference *texref) {
    return CudaRuntimeContext::instance().context().cudaGetTextureAlignmentOffset(
        offset, texref);
}

cudaError_t cudaGetTextureReference(const struct textureReference **texref,
        const char *symbol) {
    return CudaRuntimeContext::instance().context().cudaGetTextureReference(
        texref, symbol);
}

cudaError_t cudaGraphicsMapResources(int count, cudaGraphicsResource_t
        *resources, cudaStream_t stream) {
    return CudaRuntimeContext::instance().context().cudaGraphicsMapResources(
        count, resources, stream);
}

cudaError_t cudaGraphicsResourceGetMappedPointer(void **devPtr, size_t *size,
        cudaGraphicsResource_t resource) {
    return CudaRuntimeContext::instance().context().
        cudaGraphicsResourceGetMappedPointer(devPtr, size, resource);
}

cudaError_t cudaGraphicsResourceSetMapFlags(cudaGraphicsResource_t resource,
        unsigned int flags) {
    return CudaRuntimeContext::instance().context().
        cudaGraphicsResourceSetMapFlags(resource, flags);
}

cudaError_t cudaGraphicsSubResourceGetMappedArray(struct cudaArray **array,
        cudaGraphicsResource_t resource, unsigned int arrayIndex, unsigned int
        mipLevel) {
    return CudaRuntimeContext::instance().context().
        cudaGraphicsSubResourceGetMappedArray(array, resource, arrayIndex,
        mipLevel);
}

cudaError_t cudaGraphicsUnmapResources(int count, cudaGraphicsResource_t
        *resources, cudaStream_t stream) {
    return CudaRuntimeContext::instance().context().cudaGraphicsUnmapResources(
        count, resources, stream);
}

cudaError_t cudaGraphicsUnregisterResource(cudaGraphicsResource_t resource) {
    return CudaRuntimeContext::instance().context().cudaGraphicsUnregisterResource(
       resource);
}

cudaError_t cudaHostAlloc(void **pHost, size_t size, unsigned int flags) {
    return CudaRuntimeContext::instance().context().cudaHostAlloc(pHost, size,
        flags);
}

cudaError_t cudaHostGetDevicePointer(void **pDevice, void *pHost,
        unsigned int flags) {
    return CudaRuntimeContext::instance().context().cudaHostGetDevicePointer(
        pDevice, pHost, flags);
}

cudaError_t cudaHostGetFlags(unsigned int *pFlags, void *pHost) {
    return CudaRuntimeContext::instance().context().cudaHostGetFlags(pFlags,
        pHost);
}

cudaError_t cudaHostRegister(void *ptr, size_t size, unsigned int flags) {
    return CudaRuntimeContext::instance().context().cudaHostRegister(ptr, size,
        flags);
}

cudaError_t cudaHostUnregister(void *ptr) {
    return CudaRuntimeContext::instance().context().cudaHostUnregister(ptr);
}

#if CUDA_VERSION >= 4010 /* cudaIpc* calls added from CUDA 4.1 onwards */
cudaError_t cudaIpcGetEventHandle(cudaIpcEventHandle_t *handle,
        cudaEvent_t event) {
    return CudaRuntimeContext::instance().context().
        cudaIpcGetEventHandle(handle, event);
}

cudaError_t cudaIpcOpenEventHandle(cudaEvent_t *event,
        cudaIpcEventHandle_t handle) {
    return CudaRuntimeContext::instance().context().
        cudaIpcOpenEventHandle(event, handle);
}

cudaError_t cudaIpcGetMemHandle(cudaIpcMemHandle_t *handle, void *devPtr) {
    return CudaRuntimeContext::instance().context().
        cudaIpcGetMemHandle(handle, devPtr);
}

cudaError_t cudaIpcOpenMemHandle(void **devPtr, cudaIpcMemHandle_t handle,
        unsigned int flags) {
    return CudaRuntimeContext::instance().context().
        cudaIpcOpenMemHandle(devPtr, handle, flags);
}

cudaError_t cudaIpcCloseMemHandle(void *devPtr) {
    return CudaRuntimeContext::instance().context().cudaIpcCloseMemHandle(devPtr);
}

#endif

cudaError_t cudaMalloc(void **devPtr, size_t size) {
    return CudaRuntimeContext::instance().context().cudaMalloc(devPtr, size);
}

cudaError_t cudaMalloc3D(struct cudaPitchedPtr *pitchedDevPtr, struct
        cudaExtent extent) {
    return CudaRuntimeContext::instance().context().cudaMalloc3D(
        pitchedDevPtr, extent);
}

cudaError_t cudaMalloc3DArray(struct cudaArray** array, const struct
        cudaChannelFormatDesc *desc, struct cudaExtent extent, unsigned int
        flags) {
    return CudaRuntimeContext::instance().context().cudaMalloc3DArray(array,
        desc, extent, flags);
}

cudaError_t cudaMallocArray(struct cudaArray **array, const struct
        cudaChannelFormatDesc *desc, size_t width, size_t height, unsigned int
        flags) {
    return CudaRuntimeContext::instance().context().cudaMallocArray(array,
        desc, width, height, flags);
}

cudaError_t cudaMallocHost(void **ptr, size_t size) {
    return CudaRuntimeContext::instance().context().cudaMallocHost(ptr, size);
}

cudaError_t cudaMallocPitch(void **devPtr, size_t *pitch, size_t width,
        size_t height) {
    return CudaRuntimeContext::instance().context().cudaMallocPitch(devPtr,
        pitch, width, height);
}

cudaError_t cudaMemcpy(void *dst, const void *src, size_t size,
        enum cudaMemcpyKind kind) {
    return CudaRuntimeContext::instance().context().cudaMemcpy(dst, src, size,
        kind);
}

cudaError_t cudaMemcpy2D(void *dst, size_t dpitch, const void *src, size_t
        pitch, size_t width, size_t height, enum cudaMemcpyKind kind) {
    return CudaRuntimeContext::instance().context().cudaMemcpy2D(dst, dpitch,
        src, pitch, width, height, kind);
}

cudaError_t cudaMemcpy2DAsync(void *dst, size_t dpitch, const void *src,
        size_t spitch, size_t width, size_t height, enum cudaMemcpyKind kind,
        cudaStream_t stream) {
    return CudaRuntimeContext::instance().context().cudaMemcpy2DAsync(dst,
        dpitch, src, spitch, width, height, kind, stream);
}

cudaError_t cudaMemcpy2DArrayToArray(struct cudaArray *dst, size_t wOffsetDst,
        size_t hOffsetDst, const struct cudaArray *src, size_t wOffsetSrc,
        size_t hOffsetSrc, size_t width, size_t height, enum cudaMemcpyKind
        kind) {
    return CudaRuntimeContext::instance().context().cudaMemcpy2DArrayToArray(dst,
        wOffsetDst, hOffsetDst, src, wOffsetSrc, hOffsetSrc, width, height,
        kind);
}

cudaError_t cudaMemcpy2DFromArray(void *dst, size_t dpitch, const struct
        cudaArray *src, size_t wOffset, size_t hOffset, size_t width, size_t
        height, enum cudaMemcpyKind kind) {
    return CudaRuntimeContext::instance().context().cudaMemcpy2DFromArray(dst,
        dpitch, src, wOffset, hOffset, width, height, kind);
}

cudaError_t cudaMemcpy2DFromArrayAsync(void *dst, size_t dpitch, const struct
        cudaArray *src, size_t wOffset, size_t hOffset, size_t width, size_t
        height, enum cudaMemcpyKind kind, cudaStream_t stream) {
    return CudaRuntimeContext::instance().context().cudaMemcpy2DFromArrayAsync(
        dst, dpitch, src, wOffset, hOffset, width, height, kind, stream);
}

cudaError_t cudaMemcpy2DToArray(struct cudaArray *dst, size_t wOffset,
        size_t hOffset, const void *src, size_t spitch, size_t width, size_t
        height, enum cudaMemcpyKind kind) {
    return CudaRuntimeContext::instance().context().cudaMemcpy2DToArray(dst,
        wOffset, hOffset, src, spitch, width, height, kind);
}

cudaError_t cudaMemcpy2DToArrayAsync(struct cudaArray *dst, size_t wOffset,
        size_t hOffset, const void *src, size_t spitch, size_t width, size_t
        height, enum cudaMemcpyKind kind, cudaStream_t stream) {
    return CudaRuntimeContext::instance().context().cudaMemcpy2DToArrayAsync(
        dst, wOffset, hOffset, src, spitch, width, height, kind, stream);
}

cudaError_t cudaMemcpy3D(const struct cudaMemcpy3DParms *p) {
    return CudaRuntimeContext::instance().context().cudaMemcpy3D(p);
}

cudaError_t cudaMemcpy3DAsync(const struct cudaMemcpy3DParms *p,
        cudaStream_t stream) {
    return CudaRuntimeContext::instance().context().cudaMemcpy3DAsync(p, stream);
}

cudaError_t cudaMemcpy3DPeer(const struct cudaMemcpy3DPeerParms *p) {
    return CudaRuntimeContext::instance().context().cudaMemcpy3DPeer(p);
}

cudaError_t cudaMemcpy3DPeerAsync(const struct cudaMemcpy3DPeerParms *p,
        cudaStream_t stream) {
    return CudaRuntimeContext::instance().context().cudaMemcpy3DPeerAsync(p,
        stream);
}

cudaError_t cudaMemcpyArrayToArray(struct cudaArray *dst, size_t wOffsetDst,
        size_t hOffsetDst, const struct cudaArray *src, size_t wOffsetSrc,
        size_t hOffsetSrc, size_t count, enum cudaMemcpyKind kind) {
    return CudaRuntimeContext::instance().context().cudaMemcpyArrayToArray(dst,
        wOffsetDst, hOffsetDst, src, wOffsetSrc, hOffsetSrc, count, kind);
}

cudaError_t cudaMemcpyAsync(void *dst, const void *src, size_t count,
        enum cudaMemcpyKind kind, cudaStream_t stream) {
    return CudaRuntimeContext::instance().context().cudaMemcpyAsync(dst, src,
        count, kind, stream);
}

cudaError_t cudaMemcpyFromArray(void *dst, const struct cudaArray *src,
        size_t wOffset, size_t hOffset, size_t count,
        enum cudaMemcpyKind kind) {
    return CudaRuntimeContext::instance().context().cudaMemcpyFromArray(dst, src,
        wOffset, hOffset, count, kind);
}

cudaError_t cudaMemcpyFromArrayAsync(void *dst, const struct cudaArray *src,
        size_t wOffset, size_t hOffset, size_t count, enum cudaMemcpyKind kind,
        cudaStream_t stream) {
    return CudaRuntimeContext::instance().context().cudaMemcpyFromArrayAsync(
        dst, src, wOffset, hOffset, count, kind, stream);
}

cudaError_t cudaMemcpyFromSymbol(void *dst, const void *symbol, size_t count,
        size_t offset, enum cudaMemcpyKind kind) {
    return CudaRuntimeContext::instance().context().cudaMemcpyFromSymbol(dst,
        symbol, count, offset, kind);
}

cudaError_t cudaMemcpyFromSymbolAsync(void *dst, const void *symbol, size_t
        count, size_t offset, enum cudaMemcpyKind kind, cudaStream_t stream) {
    return CudaRuntimeContext::instance().context().cudaMemcpyFromSymbolAsync(
        dst, symbol, count, offset, kind, stream);
}

cudaError_t cudaMemcpyPeer(void *dst, int dstDevice, const void *src, int
        srcDevice, size_t count) {
    return CudaRuntimeContext::instance().context().cudaMemcpyPeer(dst,
        dstDevice, src, srcDevice, count);
}

cudaError_t cudaMemcpyPeerAsync(void *dst, int dstDevice, const void *src, int
        srcDevice, size_t count, cudaStream_t stream) {
    return CudaRuntimeContext::instance().context().cudaMemcpyPeerAsync(dst,
        dstDevice, src, srcDevice, count, stream);
}

cudaError_t cudaMemcpyToArray(struct cudaArray *dst, size_t wOffset, size_t
        hOffset, const void *src, size_t count, enum cudaMemcpyKind kind) {
    return CudaRuntimeContext::instance().context().cudaMemcpyToArray(dst,
        wOffset, hOffset, src, count, kind);
}

cudaError_t cudaMemcpyToArrayAsync(struct cudaArray *dst, size_t wOffset,
        size_t hOffset, const void *src, size_t count, enum cudaMemcpyKind
        kind, cudaStream_t stream) {
    return CudaRuntimeContext::instance().context().cudaMemcpyToArrayAsync(dst,
        wOffset, hOffset, src, count, kind, stream);
}

cudaError_t cudaMemcpyToSymbol(const void *symbol, const void *src, size_t
        count, size_t offset, enum cudaMemcpyKind kind) {
    return CudaRuntimeContext::instance().context().cudaMemcpyToSymbol(symbol,
        src, count, offset, kind);
}

cudaError_t cudaMemcpyToSymbolAsync(const void *symbol, const void *src,
        size_t count, size_t offset, enum cudaMemcpyKind kind, cudaStream_t
        stream) {
    return CudaRuntimeContext::instance().context().cudaMemcpyToSymbolAsync(
        symbol, src, count, offset, kind, stream);
}

cudaError_t cudaMemGetInfo(size_t *free, size_t *total) {
    return CudaRuntimeContext::instance().context().cudaMemGetInfo(free, total);
}

cudaError_t cudaMemset(void *devPtr, int value, size_t count) {
    return CudaRuntimeContext::instance().context().cudaMemset(devPtr, value,
        count);
}

cudaError_t cudaMemset2D(void *devPtr, size_t pitch, int value, size_t
        width, size_t height) {
    return CudaRuntimeContext::instance().context().cudaMemset2D(devPtr, pitch,
        value, width, height);
}

cudaError_t cudaMemset2DAsync(void *devPtr, size_t pitch, int value, size_t
        width, size_t height, cudaStream_t stream) {
    return CudaRuntimeContext::instance().context().cudaMemset2DAsync(devPtr,
        pitch, value, width, height, stream);
}

cudaError_t cudaMemset3D(struct cudaPitchedPtr pitchedDevPtr, int value,
        struct cudaExtent extent) {
    return CudaRuntimeContext::instance().context().cudaMemset3D(pitchedDevPtr,
        value, extent);
}

cudaError_t cudaMemset3DAsync(struct cudaPitchedPtr pitchedDevPtr, int value,
        struct cudaExtent extent, cudaStream_t stream) {
    return CudaRuntimeContext::instance().context().cudaMemset3DAsync(
        pitchedDevPtr, value, extent, stream);
}

cudaError_t cudaMemsetAsync(void *devPtr, int value, size_t count,
        cudaStream_t stream) {
    return CudaRuntimeContext::instance().context().cudaMemsetAsync(devPtr,
        value, count, stream);
}

cudaError_t cudaLaunch(const void *entry) {
    return CudaRuntimeContext::instance().context().cudaLaunch(entry);
}

cudaError_t cudaPeekAtLastError(void) {
    return CudaRuntimeContext::instance().context().cudaPeekAtLastError();
}

#if CUDA_VERSION >= 4010 /* 4.1 */
cudaError_t cudaPointerGetAttributes(struct cudaPointerAttributes *, void *);
#endif

cudaError_t cudaPointerGetAttributes(struct cudaPointerAttributes *attributes,
        void *ptr) {
    return CudaRuntimeContext::instance().context().cudaPointerGetAttributes(
        attributes, ptr);
}

#if CUDA_VERSION >= 4010 /* 4.1 */
/**
 * CUDA 4.1 version
 */
cudaError_t cudaPointerGetAttributes(struct cudaPointerAttributes *attributes,
        const void *ptr) {
    return CudaRuntimeContext::instance().context().cudaPointerGetAttributes(
        attributes, ptr);
}
#endif

cudaError_t cudaRuntimeGetVersion(int *runtimeVersion) {
    return CudaRuntimeContext::instance().context().cudaRuntimeGetVersion(
        runtimeVersion);
}

cudaError_t cudaSetDevice(int device) {
    return CudaRuntimeContext::instance().cudaSetDevice(device);
}

cudaError_t cudaSetDeviceFlags(unsigned int flags) {
    return CudaRuntimeContext::instance().cudaSetDeviceFlags(flags);
}

cudaError_t cudaSetDoubleForDevice(double *d) {
    

    return CudaRuntimeContext::instance().context().cudaSetDoubleForDevice(d);
}

cudaError_t cudaSetDoubleForHost(double *d) {
    return CudaRuntimeContext::instance().context().cudaSetDoubleForHost(d);
}

cudaError_t cudaSetupArgument(const void *arg, size_t size, size_t offset) {
    return CudaRuntimeContext::instance().context().cudaSetupArgument(arg, size,
        offset);
}

cudaError_t cudaSetValidDevices(int *device_arr, int len) {
    return CudaRuntimeContext::instance().cudaSetValidDevices(device_arr, len);
}

cudaError_t cudaStreamCreate(cudaStream_t *pStream) {
    return CudaRuntimeContext::instance().context().cudaStreamCreate(pStream);
}

cudaError_t cudaStreamDestroy(cudaStream_t stream) {
    return CudaRuntimeContext::instance().context().cudaStreamDestroy(stream);
}

cudaError_t cudaStreamQuery(cudaStream_t stream) {
    return CudaRuntimeContext::instance().context().cudaStreamQuery(stream);
}

cudaError_t cudaStreamSynchronize(cudaStream_t stream) {
    return CudaRuntimeContext::instance().context().cudaStreamSynchronize(stream);
}

cudaError_t cudaStreamWaitEvent(cudaStream_t stream, cudaEvent_t event,
        unsigned int flags) {
    return CudaRuntimeContext::instance().context().cudaStreamWaitEvent(stream,
        event, flags);
}

cudaError_t cudaThreadExit(void) {
    return CudaRuntimeContext::instance().cudaThreadExit();
}

cudaError_t cudaThreadGetCacheConfig(enum cudaFuncCache *pCacheConfig) {
    return CudaRuntimeContext::instance().context().cudaThreadGetCacheConfig(
        pCacheConfig);
}

cudaError_t cudaThreadGetLimit(size_t *pValue, enum cudaLimit limit) {
    return CudaRuntimeContext::instance().context().cudaThreadGetLimit(pValue,
        limit);
}

cudaError_t cudaThreadSetCacheConfig(enum cudaFuncCache cacheConfig) {
    return CudaRuntimeContext::instance().context().cudaThreadSetCacheConfig(
        cacheConfig);
}

cudaError_t cudaThreadSetLimit(enum cudaLimit limit, size_t value) {
    return CudaRuntimeContext::instance().context().cudaThreadSetLimit(limit,
        value);
}

cudaError_t cudaThreadSynchronize() {
    return CudaRuntimeContext::instance().context().cudaThreadSynchronize();
}

cudaError_t cudaUnbindTexture(const struct textureReference *texref) {
    return CudaRuntimeContext::instance().context().cudaUnbindTexture(texref);
}

struct cudaChannelFormatDesc cudaCreateChannelDesc(int x, int y, int z,
        int w, enum cudaChannelFormatKind f) {
    return CudaRuntimeContext::instance().context().cudaCreateChannelDesc(x, y, z, w, f);           
}        

#ifdef __CPLUSPLUS
}
#endif
