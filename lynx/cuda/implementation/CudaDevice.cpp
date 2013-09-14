/*! \file CudaDevice.cpp
	\date Friday June 22, 2012
	\author Naila Farooqui <naila@cc.gatech.edu>
	\brief The source file for a CUDA enabled device class
*/

#include <lynx/cuda/interface/CudaDevice.h>

// Hydrazine includes
#include <hydrazine/interface/Exception.h>
#include <hydrazine/interface/string.h>
#include <hydrazine/interface/debug.h>
#include <hydrazine/interface/Casts.h>

#include <cuda.h>

#include <iostream>
#include <cstring>

#ifdef REPORT_BASE
#undef REPORT_BASE
#endif

////////////////////////////////////////////////////////////////////////////////

// whether debugging messages are printed
#define REPORT_BASE 0


////////////////////////////////////////////////////////////////////////////////


namespace cuda {

    CudaDevice::CudaDevice(int id)
    : id(id)
    {
    }
    
	CudaDevice::~CudaDevice()
	{	
        modules.clear();
        kernels.clear();
	}

    void CudaDevice::loadModule(const ir::Module* module) 
    {
        std::stringstream stream;
        module->writeIR(stream, ir::PTXEmitter::Target_NVIDIA_PTX30);
        
        report(stream.str());

        if(modules.find(module->path()) != modules.end())
        {
            CUresult ret = cuModuleUnload(modules.find(module->path())->second);
            assert(ret == CUDA_SUCCESS);
        }   

        CUjit_option options[] = {
			CU_JIT_TARGET,
			CU_JIT_ERROR_LOG_BUFFER, 
			CU_JIT_ERROR_LOG_BUFFER_SIZE_BYTES, 
		};
		
		const uint32_t errorLogSize       = 2048;
		uint32_t       errorLogActualSize = errorLogSize - 1;

		uint8_t errorLogBuffer[errorLogSize];

		std::memset(errorLogBuffer, 0, errorLogSize);

		void* optionValues[3] = {
			(void*)CU_TARGET_COMPUTE_20,
			(void*)errorLogBuffer, 
			hydrazine::bit_cast<void*>(errorLogActualSize), 
		};
        
        CUdevice device;
        CUresult ret = cuDeviceGet(&device, id);
        assert(ret == CUDA_SUCCESS);
        
        int major = 0, minor = 0;
        ret = cuDeviceComputeCapability(&major, &minor, device);
        assert(ret == CUDA_SUCCESS);
        
        if(major == 3) {
            optionValues[0] = (void*)CU_TARGET_COMPUTE_30;
        }
      
        CUmodule moduleHandle;
        ret = cuModuleLoadDataEx(&moduleHandle, stream.str().c_str(),
            3, options, optionValues);

        report("ret: " << ret);
        assert(ret == CUDA_SUCCESS && moduleHandle);

        /* allow a moduleHandle to be re-inserted -- this requires removing
            any previously inserted moduleHandles with the same key since
            STL map does not allow duplicate keys and if a key is found, it 
            doesn't over-write the old value with the new one */
        modules.erase(module->path());
        modules.insert(std::make_pair(module->path(), moduleHandle));

    }

    void CudaDevice::loadKernel(std::string kernelName, std::string moduleName) 
    {
        CudaModuleMap::iterator module = modules.find(moduleName);
        if(module == modules.end())
        {
            throw new hydrazine::Exception("Module was never loaded on device!");
        }
		        
        CUfunction kernelHandle;
        CUresult ret = cuModuleGetFunction(&kernelHandle, module->second, 
            kernelName.c_str());

        assert(ret == CUDA_SUCCESS && kernelHandle);

        kernels.erase(kernelName);
        kernels.insert(std::make_pair(kernelName, kernelHandle));
    }

    void CudaDevice::loadTexture(std::string textureName)
    {
        CUtexref texRef;
        assert(cuTexRefCreate(&texRef) == CUDA_SUCCESS);
        textures.erase(textureName);    
        textures.insert(std::make_pair(textureName, texRef));
    }

    bool CudaDevice::moduleLoaded(std::string moduleName) 
    {
        return modules.count(moduleName) != 0; 
    }

    bool CudaDevice::kernelLoaded(std::string kernelName)
    {
        return kernels.count(kernelName) != 0;
    }

    bool CudaDevice::textureLoaded(std::string textureName)
    {
        return textures.count(textureName) != 0;
    }

}


