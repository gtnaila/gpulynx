/*! \file CudaRuntime.h
	\date Friday June 22, 2012
	\author Naila Farooqui <naila@cc.gatech.edu>
	\brief The header file for the CUDA Runtime (interposer)
*/

#ifndef __CUDA_RUNTIME_H_
#define __CUDA_RUNTIME_H_

#ifdef __CPLUSPLUS
 {
#endif

extern "C"
void** __cudaRegisterFatBinary(void *fatCubin);

extern "C"
void __cudaRegisterFunction(void **fatCubinHandle, const char *hostFun,
        char *deviceFun, const char *deviceName, int thread_limit, uint3 *tid,
        uint3 *bid, dim3 *bDim, dim3 *gDim, int *wSize);

extern "C"
void __cudaRegisterTexture(void **fatCubinHandle,
        const struct textureReference *hostVar, const void **deviceAddress,
        const char *deviceName, int dim, int norm, int ext);

extern "C"
void __cudaRegisterVar(void **fatCubinHandle,char *hostVar, char *deviceAddress,
        const char *deviceName, int ext, int size, int constant, int global);

extern "C"
void __cudaUnregisterFatBinary(void **fatCubinHandle);

extern "C"
struct cudaChannelFormatDesc cudaCreateChannelDesc(int x, int y, int z,
        int w, enum cudaChannelFormatKind f);   

#ifdef __CPLUSPLUS
}
#endif

#endif 
