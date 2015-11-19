# Overview #
As parallel execution platforms continue to proliferate, there is a growing need for real-time introspection tools to provide insight into platform behavior for performance debugging, correctness checks, and to drive effective resource management schemes. To address this need, we present the **_Lynx_** dynamic instrumentation system. Lynx provides the capability to write instrumentation routines that are (1) **selective**, instrumenting
only what is needed, (2) **transparent**, without changes to the applications’ source code, (3) **customizable**, and (4) **efficient**.

Lynx was originally implemented as a branch of [GPU Ocelot](http://code.google.com/p/gpuocelot), a framework that provides run-time code generation of CUDA programs for heterogeneous architectures. Lynx now exists as a stand-alone, PTX editing tool, encapsulating only the necessary Ocelot dependencies (namely, Ocelot's PTX Parser, PTX IR and CFG/DFG Analyses components).

![http://www.cc.gatech.edu/~naila/lynx/lynx-overview.jpg](http://www.cc.gatech.edu/~naila/lynx/lynx-overview.jpg)

To instrument a CUDA application with Lynx, the user can specify instrumentation specifications as C code snippets and provide it to the framework. The Lynx engine JIT compiles the C code specification and translates it into PTX.

CUDA applications compiled by _nvcc_ are converted into C++ programs, with PTX kernels embedded as string literals. When such a program links with our framework, our CUDA runtime parses these PTX kernels into an internal representation. The original PTX kernel is provided as input to the PTX-PTX transformation engine, together with the instrumentation PTX generated from the C code specification. The transformation engine applies a sequence of PTX kernel transformations to the original PTX kernel, resulting in the final instrumented PTX kernel, which is then executed on the CUDA device.