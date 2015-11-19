# Getting Started #

This page provides instructions for installing and running GPU Lynx.


## Requirements ##

### Compiler Tools ###

The following compiler tools are required:

  * C++ Compiler (GCC 4.5.x)
  * Lex Lexer Generator (Flex 2.5.35)
  * Yacc Parser Generator (Bison 2.4.1)
  * SCons

### Libraries ###

The following libraries are required to be installed:

  * [Boost](http://www.boost.org)
  * [CUDA Toolkit 4.1+](https://developer.nvidia.com/cuda-toolkit)

## Installation ##

GPU Lynx depends on CUDA 4.1+, boost, flex, bison, scons and python (for building). So far, Lynx has been developed and tested only on Ubuntu 11.10. You can install the necessary packages on Ubuntu:

  * sudo apt-get install g++ flex bison scons python libboost-all-dev

Please be sure to install the [CUDA Toolkit (4.1 or higher)](https://developer.nvidia.com/cuda-toolkit) from NVIDIA's website. Lynx currently supports PTX ISA 3.0 and requires a CUDA-capable (Fermi) GPU.

### Building GPU Lynx ###

Checkout Lynx from the [GIT repository](http://code.google.com/p/gpulynx/source/checkout), or download and extract the [latest GPU Lynx release](http://code.google.com/p/gpulynx/downloads/list).

To build Lynx, use the following command from the main directory:
  * scons

To install Lynx, use the following command (install dir: /usr/local/lib):
  * sudo scons install

The build script will obtain all of the relevant [GPU Ocelot](http://code.google.com/p/gpuocelot) dependencies before building Lynx, and in the case
of the tarball, the dependencies are already included.

Lynx can be built as a library (_liblynx.so_), where it can be linked with any runtime, or as a Lynx runtime (_liblynx\_runtime.so_), where it provides a default implementation of the CUDA Runtime to directly support the execution of CUDA applications on NVIDIA GPU devices.

### Running CUDA Applications with GPU Lynx ###

To run GPU Lynx with the currently available instrumentations, you would need to copy the **configure.lynx** file and **resources** directory to the execution directory (i.e. where the CUDA application is executed from).

Lynx currently provides the following instrumentations (associated instrumentation name to be specified in the configuration file is included in paranthesis):

  * Clock Cycle Count  (clockCycleCount)
  * Memory Efficiency  (memoryEfficiency)
  * Branch Divergence  (branchDivergence)
  * Activity Factor    (activityFactor)
  * Barrier Count      (barrierCount)

A sample **configure.lynx** file is included in the main directory.

To run a CUDA application with GPU Lynx (for example, BlackScholes), use the following command:

  * LD\_PRELOAD="$(PATH\_TO\_GPU\_LYNX\_RUNTIME\_SO)/liblynx\_runtime.so" ./BlackScholes
  * Example:
> > LD\_PRELOAD="/usr/local/lib/liblynx\_runtime.so" ./BlackScholes



You can enable/disable various instrumentations by modifying the **configure.lynx** file.