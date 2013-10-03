
#ifndef __CUDA_CONTEXT_H__
#define __CUDA_CONTEXT_H__

#include <cstring>

#include <boost/thread/mutex.hpp>
#include <boost/thread/tss.hpp>
#include <cuda.h>
#include <list>
#include <vector>
#include <cuda_runtime.h>

#include <lynx/cuda/interface/CudaDevice.h>
#include <lynx/cuda/interface/CudaRuntimeContext.h>
#include <lynx/instrumentation/interface/PTXInstrumentor.h>

namespace cuda {

/* forward declaration */
class CudaRuntimeContext;

class CudaContext {

    friend class CudaRuntimeContext;

    private:
        /**
         * Sets the thread's last error.
         */
        cudaError_t setLastError(cudaError_t error) const;
        void loadDevice();
        
        /**
         * This context's device id
         */
        const int _deviceId;

        //! CUDA device associated with this context
        CudaDevice *_device;

        mutable boost::mutex _mutex;

        int _runtimeVersion;

        CudaRuntimeContext * cudaRuntime() { return _cudaRuntime; }
        const CudaRuntimeContext * cudaRuntime() const { return _cudaRuntime; }

        CudaRuntimeContext * const _cudaRuntime;
        mutable cudaError_t _error;

        /**
         * handle to the raw CUDA context
         */
        CUcontext _cuContext;

        CudaContext(CudaRuntimeContext * ctx, int device, unsigned int flags);
        virtual ~CudaContext();
        
    public:

        class Parameter : boost::noncopyable {
            public:
            
            Parameter(const void * _param, size_t _size, size_t _offset) :
                    param(new uint8_t[_size]), size(_size), offset(_offset) {
                std::memcpy(const_cast<void *>(param), _param, size);
            }

            ~Parameter() { delete[] static_cast<const uint8_t *>(param); }

            const void * param;
            const size_t size;
            const size_t offset;
        };

        /*!	configuration of kernel launch */
	    class KernelLaunchConfiguration {
	        public:
		        KernelLaunchConfiguration(dim3 grid, dim3 block, size_t shared, 
			        cudaStream_t s): gridDim(grid), blockDim(block), 
			        sharedMemory(shared), stream(s) { }
			
	        public:
		        //! dimensions of grid
		        dim3 gridDim;
		
		        //! dimensions of each block
		        dim3 blockDim;
		
		        //! number of bytes of dynamically allocated shared memory
		        size_t sharedMemory;
		
		        //! stream to which kernel launch is to be recorded
		        cudaStream_t stream;

                std::vector<Parameter *> args;
	    };

	    typedef std::list< KernelLaunchConfiguration > KernelLaunchStack;

        //! stack of launch configurations
	    KernelLaunchStack launchConfigurations;
	    
	    //! set of configured instrumentors
        instrumentation::PTXInstrumentorVector *instrumentors;

    private:

        void findSymbol(const void *symbol, std::string & name, std::string & moduleName);
        cudaError_t locateTexture(
            const struct textureReference *texref, CUtexref & texHandle,
            CudaRuntimeContext::RegisteredTextureMap::iterator & texture);

        void registerModule(ir::Module & module);
        void registerAllModules();
        cudaError_t launchKernel(CUfunction kernelHandle, KernelLaunchConfiguration launch); 

    public:


        virtual cudaError_t cudaConfigureCall(dim3 gridDim, dim3 blockDim,
            size_t sharedMem, cudaStream_t stream);
        virtual cudaError_t cudaLaunch(const void *entry);
        virtual cudaError_t cudaSetupArgument(const void *arg, size_t size,
            size_t offset);
        virtual cudaError_t cudaThreadSynchronize();

        virtual cudaError_t cudaBindSurfaceToArray(
            const struct surfaceReference *surfref, const struct cudaArray *array,
            const struct cudaChannelFormatDesc *desc);
        virtual cudaError_t cudaBindTexture(size_t *offset,
            const struct textureReference *texref, const void *devPtr,
            const struct cudaChannelFormatDesc *desc, size_t size);
        virtual cudaError_t cudaBindTexture2D(size_t *offset,
            const struct textureReference *texref, const void *devPtr,
            const struct cudaChannelFormatDesc *desc, size_t width, size_t height,
            size_t pitch);
        virtual cudaError_t cudaBindTextureToArray(
            const struct textureReference *texref, const struct cudaArray *array,
            const struct cudaChannelFormatDesc *desc);
        virtual cudaError_t cudaChooseDevice(int *device,
            const struct cudaDeviceProp *prop);
        virtual cudaError_t cudaDeviceGetCacheConfig(
            enum cudaFuncCache *pCacheConfig);
        virtual cudaError_t cudaDeviceGetLimit(size_t *pValue,
            enum cudaLimit limit);
        virtual cudaError_t cudaDeviceSetCacheConfig(
            enum cudaFuncCache cacheConfig);
        virtual cudaError_t cudaDeviceSetLimit(enum cudaLimit limit, size_t value);
        virtual cudaError_t cudaDeviceSynchronize();
        virtual cudaChannelFormatDesc cudaCreateChannelDesc(int x, int y, int z,
            int w, enum cudaChannelFormatKind f);
        virtual cudaError_t cudaDriverGetVersion(int *driverVersion);
        virtual cudaError_t cudaEventCreate(cudaEvent_t *event);
        virtual cudaError_t cudaEventCreateWithFlags(cudaEvent_t *event,
            unsigned int flags);
        virtual cudaError_t cudaEventDestroy(cudaEvent_t event);
        virtual cudaError_t cudaEventElapsedTime(float *ms, cudaEvent_t start,
            cudaEvent_t end);
        virtual cudaError_t cudaEventQuery(cudaEvent_t event);
        virtual cudaError_t cudaEventRecord(cudaEvent_t event,
            cudaStream_t stream);
        virtual cudaError_t cudaEventSynchronize(cudaEvent_t);
        virtual cudaError_t cudaFree(void *devPtr);
        virtual cudaError_t cudaFreeArray(struct cudaArray *array);
        virtual cudaError_t cudaFreeHost(void *ptr);
        virtual cudaError_t cudaFuncGetAttributes(struct cudaFuncAttributes *attr,
            const void *func);
        virtual cudaError_t cudaFuncSetCacheConfig(const void *func,
            enum cudaFuncCache cacheConfig);
        virtual cudaError_t cudaGetChannelDesc(struct cudaChannelFormatDesc *desc,
            const struct cudaArray *array);
        virtual cudaError_t cudaGetDeviceProperties(struct cudaDeviceProp *prop,
            int device);
        virtual cudaError_t cudaGetExportTable(const void **ppExportTable,
            const cudaUUID_t *pExportTableId);
        virtual cudaError_t cudaGetLastError();
        virtual cudaError_t cudaGetSurfaceReference(
            const struct surfaceReference **surfRef, const char *symbol);
        virtual cudaError_t cudaGetSymbolAddress(void **devPtr,
            const void *symbol);
        virtual cudaError_t cudaGetSymbolSize(size_t *size, const void *symbol);
        virtual cudaError_t cudaGetTextureAlignmentOffset(size_t *offset,
            const struct textureReference *texref);
        virtual cudaError_t cudaGetTextureReference(
            const struct textureReference **texref, const char *symbol);
        virtual cudaError_t cudaGraphicsMapResources(int count,
            cudaGraphicsResource_t *resources, cudaStream_t stream);
        virtual cudaError_t cudaGraphicsResourceGetMappedPointer(void **devPtr,
            size_t *size, cudaGraphicsResource_t resource);
        virtual cudaError_t cudaGraphicsResourceSetMapFlags(
            cudaGraphicsResource_t resource, unsigned int flags);
        virtual cudaError_t cudaGraphicsSubResourceGetMappedArray(
            struct cudaArray **array, cudaGraphicsResource_t resource,
            unsigned int arrayIndex, unsigned int mipLevel);
        virtual cudaError_t cudaGraphicsUnmapResources(int count,
            cudaGraphicsResource_t *resources, cudaStream_t stream);
        virtual cudaError_t cudaGraphicsUnregisterResource(
            cudaGraphicsResource_t resource);
        virtual cudaError_t cudaHostAlloc(void **pHost, size_t size,
            unsigned int flags);
        virtual cudaError_t cudaHostGetDevicePointer(void **pDevice, void *pHost,
            unsigned int flags);
        virtual cudaError_t cudaHostGetFlags(unsigned int *pFlags, void *pHost);
        virtual cudaError_t cudaHostRegister(void *ptr, size_t size,
            unsigned int flags);
        virtual cudaError_t cudaHostUnregister(void *ptr);

#if CUDA_VERSION >= 4010 /* cudaIpc* calls added from CUDA 4.1 onwards */
        virtual cudaError_t cudaIpcGetEventHandle(cudaIpcEventHandle_t *handle,
            cudaEvent_t event);
        virtual cudaError_t cudaIpcOpenEventHandle(cudaEvent_t *event,
            cudaIpcEventHandle_t handle);
        virtual cudaError_t cudaIpcGetMemHandle(cudaIpcMemHandle_t *handle,
            void *devPtr);
        virtual cudaError_t cudaIpcOpenMemHandle(void **devPtr,
            cudaIpcMemHandle_t handle, unsigned int flags);
        virtual cudaError_t cudaIpcCloseMemHandle(void *devPtr);
#endif

        virtual cudaError_t cudaMalloc(void **devPtr, size_t size);
        virtual cudaError_t cudaMalloc3D(struct cudaPitchedPtr *pitchedDevPtr,
            struct cudaExtent extent);
        virtual cudaError_t cudaMalloc3DArray(struct cudaArray** array,
            const struct cudaChannelFormatDesc *desc, struct cudaExtent extent,
            unsigned int flags);
        virtual cudaError_t cudaMallocArray(struct cudaArray **array,
            const struct cudaChannelFormatDesc *desc, size_t width, size_t height,
            unsigned int flags);
        virtual cudaError_t cudaMallocHost(void **ptr, size_t size);
        virtual cudaError_t cudaMallocPitch(void **devPtr, size_t *pitch,
            size_t width, size_t height);
        virtual cudaError_t cudaMemcpy(void *dst, const void *src, size_t size,
            enum cudaMemcpyKind kind);
        virtual cudaError_t cudaMemcpy2D(void *dst, size_t dpitch, const void *src,
            size_t pitch, size_t width, size_t height, enum cudaMemcpyKind kind);
        virtual cudaError_t cudaMemcpy2DAsync(void *dst, size_t dpitch,
            const void *src, size_t spitch, size_t width, size_t height,
            enum cudaMemcpyKind kind, cudaStream_t stream);
        virtual cudaError_t cudaMemcpy2DArrayToArray(struct cudaArray *dst,
            size_t wOffsetDst, size_t hOffsetDst, const struct cudaArray *src,
            size_t wOffsetSrc, size_t hOffsetSrc, size_t width, size_t height,
            enum cudaMemcpyKind kind);
        virtual cudaError_t cudaMemcpy2DFromArray(void *dst, size_t dpitch,
            const struct cudaArray *src, size_t wOffset, size_t hOffset,
            size_t width, size_t height, enum cudaMemcpyKind kind);
        virtual cudaError_t cudaMemcpy2DFromArrayAsync(void *dst, size_t dpitch,
            const struct cudaArray *src, size_t wOffset, size_t hOffset,
            size_t width, size_t height, enum cudaMemcpyKind kind,
            cudaStream_t stream);
        virtual cudaError_t cudaMemcpy2DToArray(struct cudaArray *dst,
            size_t wOffset, size_t hOffset, const void *src, size_t spitch,
            size_t width, size_t height, enum cudaMemcpyKind kind);
        virtual cudaError_t cudaMemcpy2DToArrayAsync(struct cudaArray *dst,
            size_t wOffset, size_t hOFfset, const void *src, size_t spitch,
            size_t width, size_t height, enum cudaMemcpyKind kind,
            cudaStream_t stream);
        virtual cudaError_t cudaMemcpy3D(const struct cudaMemcpy3DParms *p);
        virtual cudaError_t cudaMemcpy3DAsync(const struct cudaMemcpy3DParms *p,
            cudaStream_t stream);
        virtual cudaError_t cudaMemcpy3DPeer(
            const struct cudaMemcpy3DPeerParms *p);
        virtual cudaError_t cudaMemcpy3DPeerAsync(
            const struct cudaMemcpy3DPeerParms *p, cudaStream_t stream);
        virtual cudaError_t cudaMemcpyArrayToArray(struct cudaArray *dst,
            size_t wOffsetDst, size_t hOffsetDst, const struct cudaArray *src,
            size_t wOffsetSrc, size_t hOffsetSrc, size_t count,
            enum cudaMemcpyKind kind);
        virtual cudaError_t cudaMemcpyAsync(void *dst, const void *src,
            size_t count, enum cudaMemcpyKind kind, cudaStream_t stream);
        virtual cudaError_t cudaMemcpyFromArray(void *dst,
            const struct cudaArray *src, size_t wOffset, size_t hOffset,
            size_t count, enum cudaMemcpyKind kind);
        virtual cudaError_t cudaMemcpyFromArrayAsync(void *dst,
            const struct cudaArray *src, size_t wOffset, size_t hOffset,
            size_t count, enum cudaMemcpyKind kind, cudaStream_t stream);
        virtual cudaError_t cudaMemcpyFromSymbol(void *dst, const void *symbol,
            size_t count, size_t offset, enum cudaMemcpyKind kind);
        virtual cudaError_t cudaMemcpyFromSymbolAsync(void *dst,
            const void *symbol, size_t count, size_t offset,
            enum cudaMemcpyKind kind, cudaStream_t stream);
        virtual cudaError_t cudaMemcpyPeer(void *dst, int dstDevice,
            const void *src, int srcDevice, size_t count);
        virtual cudaError_t cudaMemcpyPeerAsync(void *dst, int dstDevice,
            const void *src, int srcDevice, size_t count, cudaStream_t stream);
        virtual cudaError_t cudaMemcpyToArray(struct cudaArray *dst,
            size_t wOffset, size_t hOffset, const void *src, size_t count,
            enum cudaMemcpyKind kind);
        virtual cudaError_t cudaMemcpyToArrayAsync(struct cudaArray *dst,
            size_t wOffset, size_t hOffset, const void *src, size_t count,
            enum cudaMemcpyKind kind, cudaStream_t stream);
        virtual cudaError_t cudaMemcpyToSymbol(const void *symbol, const void *src,
            size_t count, size_t offset, enum cudaMemcpyKind kind);
        virtual cudaError_t cudaMemcpyToSymbolAsync(const void *symbol,
            const void *src, size_t count, size_t offset, enum cudaMemcpyKind kind,
            cudaStream_t stream);
        virtual cudaError_t cudaMemGetInfo(size_t *free, size_t *total);
        virtual cudaError_t cudaMemset(void *devPtr, int value, size_t count);
        virtual cudaError_t cudaMemset2D(void *devPtr, size_t pitch, int value,
            size_t width, size_t height);
        virtual cudaError_t cudaMemset2DAsync(void *devPtr, size_t pitch,
            int value, size_t width, size_t height, cudaStream_t stream);
        virtual cudaError_t cudaMemset3D(struct cudaPitchedPtr pitchedDevPtr,
            int value, struct cudaExtent extent);
        virtual cudaError_t cudaMemset3DAsync(struct cudaPitchedPtr pitchedDevPtr,
            int value, struct cudaExtent extent, cudaStream_t stream);
        virtual cudaError_t cudaMemsetAsync(void *devPtr, int value, size_t count,
            cudaStream_t stream);
        virtual cudaError_t cudaPeekAtLastError();
        virtual cudaError_t cudaPointerGetAttributes(
            struct cudaPointerAttributes *attributes, const void *ptr);
        virtual cudaError_t cudaRuntimeGetVersion(int *runtimeVersion);
        virtual cudaError_t cudaSetDoubleForDevice(double *d);
        virtual cudaError_t cudaSetDoubleForHost(double *d);
        virtual cudaError_t cudaStreamCreate(cudaStream_t *pStream);
        virtual cudaError_t cudaStreamDestroy(cudaStream_t stream);
        virtual cudaError_t cudaStreamQuery(cudaStream_t stream);
        virtual cudaError_t cudaStreamSynchronize(cudaStream_t stream);
        virtual cudaError_t cudaStreamWaitEvent(cudaStream_t stream,
            cudaEvent_t event, unsigned int flags);
        virtual cudaError_t cudaThreadGetCacheConfig(
            enum cudaFuncCache *pCacheConfig);
        virtual cudaError_t cudaThreadGetLimit(size_t *pValue,
            enum cudaLimit limit);
        virtual cudaError_t cudaThreadSetCacheConfig(
            enum cudaFuncCache cacheConfig);
        virtual cudaError_t cudaThreadSetLimit(enum cudaLimit limit, size_t value);
        virtual cudaError_t cudaUnbindTexture(
            const struct textureReference *texref);

    }; // end class CudaContext

} // end namespace cuda

#endif 
