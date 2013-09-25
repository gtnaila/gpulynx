/*! \file CudaRuntimeContext.h
	\date Friday June 22, 2012
	\author Naila Farooqui <naila@cc.gatech.edu>
	\brief The header file for the CUDA runtime context
*/

#ifndef CUDA_RUNTIME_CONTEXT_H_DEFINED
#define CUDA_RUNTIME_CONTEXT_H_DEFINED

#include <boost/thread/mutex.hpp>
#include <boost/thread/tss.hpp>
#include <boost/unordered_map.hpp>
#include <boost/utility.hpp>

#include <vector>

#include <ocelot/cuda/interface/FatBinaryContext.h>
#include <ocelot/ir/interface/Module.h>

#include <cuda_runtime.h>

namespace cuda {


class CudaContext;

/**
 * Lynx's design is heavily influenced (in fact stems from) GPU Ocelot. Lynx 
 * was initially implemented as a branch of GPU Ocelot. This effort strives
 * to provide Lynx's dynamic instrumentation capability as a stand-alone tool,
 * encapsulating only the necessary GPU Ocelot dependencies.
 *
 * Lynx, like GPU Ocelot and Panoptes, adopts the CUDA 4.0 context model 
 * (single CUDA context per device). The current implementation borrows from the
 * above two projects the notion of a deviceContext vector and maintaining a 
 * device ID per host thread for indexing into this vector to retrieve the 
 * context associated with the current device.
 *
 * GPU Ocelot: http://code.google.com/p/gpuocelot/
 * Panoptes: https://github.com/ckennelly/panoptes
 *
 * The implementation also more or less duplicates GPU Ocelot's CUDA registration 
 * related data structures.
 *
 * The NVIDIA CUDA Driver documentation states that having more than one 
 * context per device can lead to degraded performance.
 */
class CudaRuntimeContext : public boost::noncopyable {

    friend class CudaContext;

    public:
    
        static CudaRuntimeContext & instance();
        virtual ~CudaRuntimeContext();
        CudaRuntimeContext();

        /**
         * Accessors for this thread's current context.
         */
        CudaContext & context();
        const CudaContext & context() const;


    private:

        virtual CudaContext * cudaContextFactory(int device, unsigned int flags) 
            const;

        mutable boost::mutex _mutex;
        mutable std::vector<CudaContext *> _deviceContexts;

        unsigned int _deviceFlags;
        unsigned currentDevice() const;
        unsigned _deviceCount;


        /**
         * Maintains state per host (CPU) thread
         */
        class HostThread {
            public:
                HostThread();

                unsigned device;
                bool contextSetOnThread;
        };

        mutable boost::thread_specific_ptr<HostThread> _threads;
              HostThread * currentThread();
        const HostThread * currentThread() const;
    

    private:
    
            class RegisteredGlobal
	        {
		        public:
			        RegisteredGlobal(const std::string& module = "", 
				        const std::string& global = "") : module(module), 
                        global(global) {}
	
		        public:
			        /*! \brief The module that the global is declared in */
			        std::string module;
			        /*! \brief The name of the global */
			        std::string global;
	        };

            class RegisteredTexture
	        {
		        public:
			        RegisteredTexture(const std::string& module = "", 
				        const std::string& texture = "", bool norm = false) : 
                        module(module), texture(texture), norm(norm), bound(false), 
                        offset(0) 
                    {}
	
		        public:
			        /*! \brief The module that the texture is declared in */
			        std::string module;
			        /*! \brief The name of the texture */
			        std::string texture;
			        // Should the texture be normalized?
			        bool norm;
                    // Is the texture bound?
                    bool bound;
                    // Offset if texture has been bound
                    size_t offset;
        
	        };
	
            class RegisteredKernel 
            {
                public:
		            RegisteredKernel(size_t cubinHandle = 0, 
                        const std::string& module = "", 
			            const std::string& kernel = "") : 
                        cubinHandle(cubinHandle), kernel(kernel), module(module)
                         {}

	        public:
		            size_t cubinHandle;

                    std::string kernel;
                    std::string module;
            };
        
            typedef std::map< unsigned int, FatBinaryContext > FatBinaryMap;
            typedef std::map< std::string, ir::Module> ModuleMap;
            typedef std::map< void*, RegisteredKernel > RegisteredKernelMap;
            typedef std::map< void*, RegisteredGlobal > RegisteredGlobalMap;
	        typedef std::map< void*, RegisteredTexture > RegisteredTextureMap;
            

            //! fatbinaries
		    FatBinaryMap _fatBinaries;

            //! Registered modules, kernels, textures, and variables
    	    ModuleMap _modules;
            RegisteredKernelMap _kernels;
            RegisteredGlobalMap _globals;       
            RegisteredTextureMap _textures;

    public:

        /**
         * CUDA registration methods
         */
        virtual void** cudaRegisterFatBinary(void *fatCubin);
        virtual void cudaUnregisterFatBinary(void **fatCubinHandle);
        virtual void cudaRegisterFunction(void **fatCubinHandle,
            const char *hostFun, char *deviceFun, const char *deviceName,
            int thread_limit, uint3 *tid, uint3 *bid, dim3 *bDim, dim3 *gDim,
            int *wSize);
        virtual void cudaRegisterVar(void **fatCubinHandle,char *hostVar,
            char *deviceAddress, const char *deviceName, int ext, int size,
            int constant, int global);
        virtual void cudaRegisterTexture(void **fatCubinHandle,
            const struct textureReference *hostVar, const void **deviceAddress,
            const char *deviceName, int dim, int norm, int ext);


        /**
         * CUDA device methods
         */
        cudaError_t cudaDeviceCanAccessPeer(int *canAccessPeer, int device, int
            peerDevice);
        cudaError_t cudaDeviceDisablePeerAccess(int peerDevice);
        cudaError_t cudaDeviceEnablePeerAccess(int peerDevice, unsigned int flags);
        cudaError_t cudaDeviceGetByPCIBusId(int *device, char *pciBusId);
        cudaError_t cudaDeviceGetPCIBusId(char *pciBusId, int len, int device);
        cudaError_t cudaDeviceReset();
        cudaError_t cudaGetDevice(int *device) const;
        cudaError_t cudaGetDeviceCount(int *count) const;
        cudaError_t cudaSetDevice(int device);
        cudaError_t cudaSetDeviceFlags(unsigned int flags);
        cudaError_t cudaSetValidDevices(int *device_arr, int len);
        cudaError_t cudaThreadExit(void);

    }; // end class CudaRuntimeContext

} // end namespace cuda

#endif 
