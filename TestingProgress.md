# Testing Update #

The intent of this page is to provide an up-to-date regression test report for GPU Lynx.

Currently, GPU Lynx is being tested with CUDA applications from the CUDA SDK 4.1, Parboil, and Rodinia benchmarks. This page will be updated as bug fixes are made and/or more applications are added to GPU Lynx's regression suite.

The following table provides an up-to-date listings of the applications that have been tested with certain GPU Lynx instrumentation metrics.

The CUDA applications listed below are included as part of the GPU Lynx repository for verification.

**GPU Lynx Version: 1.0.0**

| **Application** | **Activity Factor** | **Branch Divergence** | **Memory Efficiency** |
|:----------------|:--------------------|:----------------------|:----------------------|
| **_CUDA SDK 4.1_** |                     |                       |                       |
| AlignedTypes    | PASS                | PASS                  | PASS                  |
| AsyncAPI        | PASS                | PASS                  | PASS                  |
| BandwidthTest   | PASS                | PASS                  | PASS                  |
| BlackScholes    | PASS                | PASS                  | PASS                  |
| Clock           | PASS                | PASS                  | PASS                  |
| ConcurrentKernels | PASS                | PASS                  | PASS                  |
| CppIntegration  | PASS                | PASS                  | PASS                  |
| DwtHaar1D       | PASS                | PASS                  | PASS                  |
| FastWalshTransform | PASS                | FAIL                  | PASS                  |
| Histogram       | PASS                | PASS                  | PASS                  |
| InlinePTX       | PASS                | PASS                  | PASS                  |
| Reduction       | PASS                | PASS                  | PASS                  |
| ScalarProd      | PASS                | PASS                  | PASS                  |
| Scan            | PASS                | PASS                  | PASS                  |
| SimpleAssert    | PASS                | PASS                  | PASS                  |
| SimpleAtomicIntrinsics | PASS                | PASS                  | PASS                  |
| SimpleMultiCopy | PASS                | PASS                  | PASS                  |
| SimpleMultiGPU  | PASS                | FAIL                  | PASS                  |
| SimplePrintf    | PASS                | PASS                  | PASS                  |
| SimpleStreams   | PASS                | PASS                  | PASS                  |
| SimpleVoteIntrinsics | PASS                | PASS                  | PASS                  |
| SobolQRNG       | PASS                | PASS                  | PASS                  |
| Template        | PASS                | PASS                  | PASS                  |
| ThreadFenceReduction | PASS                | PASS                  | PASS                  |
| Transpose       | PASS                | PASS                  | PASS                  |
| VectorAdd       | PASS                | PASS                  | PASS                  |
| **_Parboil_**   |                     |                       |                       |
| CUTCP           | PASS                | PASS                  | PASS                  |
| LBM             | PASS                | PASS                  | PASS                  |
| MM              | PASS                | FAIL                  | PASS                  |
| MRI-Q           | PASS                | PASS                  | PASS                  |
| SPMV            | PASS                | PASS                  | PASS                  |
| STENCIL         | PASS                | PASS                  | PASS                  |
| TPACF           | PASS                | PASS                  | PASS                  |
| **_Rodinia 2.2_** |                     |                       |                       |
| BackProp        | PASS                | PASS                  | PASS                  |
| BFS             | PASS                | PASS                  | PASS                  |
| CFD             | PASS                | PASS                  | PASS                  |
| Gaussian        | PASS                | PASS                  | PASS                  |
| HotSpot         | PASS                | PASS                  | PASS                  |
| Needle-Wunsch   | PASS                | PASS                  | PASS                  |
| PathFinder      | PASS                | PASS                  | PASS                  |
| SRAD            | PASS                | PASS                  | PASS                  |
| StreamCluster   | PASS                | PASS                  | PASS                  |