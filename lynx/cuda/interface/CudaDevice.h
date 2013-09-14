/*! \file CudaDevice.h
	\date Friday June 22, 2012
	\author Naila Farooqui <naila@cc.gatech.edu>
	\brief The header file for a CUDA enabled device class
*/

#ifndef CUDA_DEVICE_H_INCLUDED
#define CUDA_DEVICE_H_INCLUDED

// C++ standard library includes
#include <map>

#include <cuda.h>
#include <ocelot/ir/interface/Module.h>

namespace cuda {

    typedef std::unordered_map<std::string, CUmodule> CudaModuleMap;
    typedef std::unordered_map<std::string, CUfunction> CudaKernelMap;
    typedef std::unordered_map<std::string, CUtexref> CudaTextureMap;
    
    /*! Interface that should be bound to a single CUDA enabled device */
    class CudaDevice {

        public:

            CudaDevice(int id);
            ~CudaDevice();
            
            const int id;    

            /* modules, kernels, and textures loaded on this device */
            CudaModuleMap modules;
            CudaKernelMap kernels;
            CudaTextureMap textures;

        public:
            /*! \brief Load module, kernel, and texture */
			void loadModule(const ir::Module* module);
            bool moduleLoaded(std::string moduleName); 

            void loadKernel(std::string kernelName, std::string moduleName);
            bool kernelLoaded(std::string kernel);

            void loadTexture(std::string textureName);
            bool textureLoaded(std::string texture);
            
    };
}

#endif
