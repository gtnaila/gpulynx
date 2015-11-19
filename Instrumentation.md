# Instrumentation with Lynx #

Instrumenting GPU applications with GPU Lynx requires both specifying the instrumentation code that must be inserted into an application's PTX kernels prior to execution, and allocating storage on the GPU device to store instrumentation results. After each kernel execution, these instrumentation results can be copied back to the CPU for further analysis/processing.

GPU Lynx provides a user-friendly C++ interface, which can be extended to provide runtime management of instrumentation data, and a C-based instrumentation language, which is used to define the instrumentation code that needs to be inserted into the target application. This enables end-users to specify instrumentation using a C-based language (instead of a lower-level intermediate representation language, such as PTX), and gives them the necessary control for initializing and extracting instrumentation results from the GPU device.

As a result, there are two components to instrumenting GPU applications:

  * Runtime Insertion of Desired Instrumentation
  * Runtime Management of Instrumentation Data

**In other words, in order to write your own instrumentation routines with GPU Lynx, the end-user must provide two things to GPU Lynx:**

  1. An instrumentation specification, written using GPU Lynx's C-based instrumentation language.
  1. A C++ class implementation of the _PTXInstrumentor_ interface that provides methods for performing the specific data initialization and management tasks for the instrumentation in question.


We cover each of these components, namely runtime insertion of instrumentation and runtime management of instrumentation data, in the subsequent sections below.

## Runtime Insertion of Desired Instrumentation ##

GPU Lynx provides the relevant software abstractions to specify and insert customized instrumentation routines into applications at runtime. The end-user, in addition to providing the _PTXInstrumentor_ implementation, needs to provide a C-based instrumentation specification, using GPU Lynx's instrumentation API.

The GPU Lynx Instrumentation API provides both relevant functions to perform instrumentation in a data-parallel programming paradigm and _instrumentation specifiers_, which designate where instrumentation needs to be inserted.

### Instrumentation API ###

The Instrumentation API captures major constructs of the data-parallel programming paradigm used by GPUs, such as threads, thread blocks, warps and streaming multi-processors (SMs). A subset of the Lynx Instrumentation API is shown in the table below:

| **API Name** | **Description** |
|:-------------|:----------------|
| globalThreadId | Global thread identifier for the current thread. |
| blockThreadId | Thread identifier for the current thread within its thread block. |
| blockId      | Thread block identifier for the current thread block within its grid. |
| blockDim     | Number of threads per thread block. |
| syncThreads  | Barrier synchronization within a thread block. |
| computeBaseAddress | Computes the base address for the corresponding memory instruction (only applicable to memory instructions). |
| leastActiveThreadInWarp | The least active thread in the current warp. |
| uniqueElementCount | Total number of unique elements in a given buffer of warp or half-warp size. |
| basicBlockId | Index of the current basic block. |
| basicBlockExecutedInstructionCount | Total number of executed instructions in the current basic block. |

### Instrumentation Specifiers ###

The _instrumentation specifiers_ are defined as C labels in the Lynx instrumentation language, and can be categorized into four types: instrumentation targets, instruction classes, address spaces, and data types.

The following table shows some of the available specifiers in the Lynx instrumentation language:

| **Specifier Type** | **Available Specifiers** |
|:-------------------|:-------------------------|
| Instrumentation Target | ON\_KERNEL\_ENTRY, ON\_KERNEL\_EXIT, ON\_BASIC\_BLOCK\_ENTRY, ON\_BASIC\_BLOCK\_EXIT, ON\_INSTRUCTION |
| Instruction Class  | MEM\_READ, MEM\_WRITE, PREDICATED, BRANCH, CALL, BARRIER, ATOMIC, ARITHMETIC |
| Address Space      | GLOBAL, LOCAL, SHARED, CONST, PARAM, TEXTURE |
| Data Types         | INTEGER, FLOATING\_POINT |

#### Instrumentation Target Specifiers ####

Instrumentation target specifiers describe where the instrumentation needs to be inserted, such as at the beginning or end of kernels, beginning or end of basic blocks, and/or every instruction. They also serve as loop constructs, implying that the instrumentation routine following the target specifier is applied to _each and every_ kernel, basic block, or instruction, depending on the target specifier. If no instrumentation target is specified, the instrumentation is inserted at the beginning of the kernel by default.

#### Instrumentation Class and Address Space Specifiers ####

Given that a user may wish to certain classes of instructions, or only instrument memory operations of certain address spaces, the Lynx API includes instrumentation class and address space specifiers. The multiple address space notion is part of the memory hierarchy model of GPU architectures. Threads may access data from various memory spaces, including on-device and off-device memory units. Additionally, data type specifiers are provided to characterize arithmetic operations by integer and floating-point functional units.

## Runtime Management of Instrumentation Data ##

GPU applications are hosted by CPU threads and thus require data transfers between the host (CPU) and the device (GPU). When instrumenting GPU applications, the instrumentation data is collected and stored on the GPU device memory during kernel execution, and is copied to the host after each kernel execution. The host-side can then perform the necessary aggregation of data to obtain the final instrumentation results. This runtime management of data between the host and device is a key aspect of GPU instrumentation, and as a result, GPU Lynx exposes a _PTXInstrumentor_ interface to end-users that can be implemented to satisfy each instrumentation's unique data initialization/management requirements.

### PTXInstrumentor ###

The _PTXInstrumentor_ class methods that need to be implemented for each unique instrumentation are shown below:

```

/*! \brief Provides methods for runtime management of instrumentation data */
class PTXInstrumentor
{
    public:					
       		
        /*! \brief The validate method checks to make sure that all the 
            defined conditions are met for this instrumentation */
        virtual bool validate() = 0;

        /*! \brief The analyze method performs any necessary static analyses */
        virtual void analyze(ir::Module &module) = 0;
			
        /*! \brief The initialize method performs any necessary 
            runtime initialization prior to instrumentation */
        virtual void initialize() = 0;
			
        /*! \brief The instrumentationSpecificationPath method returns 
            the path for the C instrumentation code specification */
        virtual std::string specificationPath() = 0;	    

        /*! \brief The extractResults method extracts instrumentation-specific 
            data after kernel execution */
        virtual void extractResults(std::ostream *out) = 0;
};

```

Note that the methods are called in the following order:
  * Prior to kernel execution:
    1. _validate_
    1. _analyze_
    1. _initialize_
    1. _specificationPath_ (as part of the actual insertion of instrumentation)
  * After kernel execution:
    1. _extractResults_

The _validate_ method lets the end-user define conditions on when to apply the instrumentation on an application's kernels. For example, in this method, the end-user can keep track of the number of kernel executions and only instrument a particular kernel once that may be launched many times to incur minimal runtime overheads due to instrumentation. Similarly, the end-user can define conditions to only instrument certain kernels versus others, and so on.

The _analyze_ method lets the end-user perform any required static analysis on a given application's PTX module. For example, if an end-user wants to maintain runtime data for each basic block, the _analyze_ method can obtain the number of basic blocks exhibited by a certain kernel, and this basic block count can be used by the _initialize_ and _extractResults_ methods to allocate/de-allocate the required amount of memory on the device based on the number of basic blocks.

The _initialize_ method is responsible for allocating memory on the GPU device to store instrumentation results prior to kernel execution, and the _extractResults_ method subsequently can read the instrumentation data from the device to a host-side data structure after the kernel has executed.

An example instrumentor implementation is provided in the next section.

## Example Instrumentation: Memory Efficiency Metric ##

The memory efficiency metric characterizes the spatial locality of memory operations to global memory, which has the highest latency in the GPU memory hierarchy. To alleviate this latency, the GPU memory model enables coalescing of global memory accesses for threads of a half-warp. The goal of the memory efficiency metric, therefore, is to characterize memory bandwidth utilization by determining the ratio of dynamic half-warps executing each global memory dynamic instruction to the number of memory transactions needed to complete these instructions.

### Memory Efficiency C Specification: Defining the Instrumentation ###

We implement the memory efficiency metric as an instruction-level instrumentation, applied only to global memory read and write instructions. The base address of each global memory operation is computed and stored for all threads in a thread block in shared memory. If the base address is the same for all threads belonging to a half-warp, then the memory accesses will be coalesced. A single thread within each warp, determined by the _leastActiveThreadInWarp_ API, performs an online reduction of the base addresses written to shared memory by all threads in each half-warp. The _uniqueElementCount_ API is used to keep a count of unique base addresses within each half-warp to determine the total number of memory transactions required for a particular memory operation.

The total number of dynamic warps and memory transactions per half-warp are aggregated in global memory for each warp.

The C code specification for this instrumentation is as follows:

```

{
    unsigned long threadId = blockThreadId();
    unsigned long warpId = (blockId() * blockDim() + threadId) >> 5;
    
    ON_INSTRUCTION:
    MEM_READ:
    MEM_WRITE:
    GLOBAL:
    {
        sharedMem[threadId] = computeBaseAddress();

        if(leastActiveThreadInWarp())
        {
            unsigned long uniqueCount = uniqueElementCount(sharedMem, 1);
            globalMem[warpId * 2] = globalMem[warpId * 2] + uniqueCount;
            globalMem[warpId * 2 + 1] = globalMem[warpId * 2 + 1] + 1;
        }
    }    
}

```

### Memory Efficiency Instrumentor: Runtime Management of Instrumentation Data ###

The memory efficiency instrumentor class must increment two counters for each warp, one for the total number of dynamic warps, and another for the total number of memory transactions needed to complete each global memory read/write operation.

Therefore, we must allocate _(2 `*` warpCount)_ amount of memory for this instrumentation. The sample instrumentor class methods are shown below.

```

#include <lynx/api/interface/lynx.h>
#include <lynx/instrumentation/interface/PTXInstrumentor.h>

#include <cuda_runtime.h>

namespace instrumentation
{

    class MemoryEfficiencyInstrumentor : public PTXInstrumentor
    {
        public:
         
            size_t *counter;
            unsigned int warpCount;
            unsigned int size;
    
        public:
        
            MemoryEfficiencyInstrumentor();
    
            /*! \brief The validate method verifies that the defined conditions 
                are met for this instrumentation */
            bool validate();

            /*! \brief The analyze method performs any necessary 
                static analyses */
            void analyze(ir::Module &module);

            /*! \brief The initialize method performs any necessary  
                runtime initialization prior to instrumentation */
            void initialize();

            /*! \brief The specificationPath method specifies the 
                C code instrumentation specification file path */
            std::string specificationPath();

            /*! \brief extracts results for the instrumentation */
            void extractResults(std::ostream *out);
    };


    MemoryEfficiencyInstrumentor::MemoryEfficiencyInstrumentor() :
    counter(0), warpCount(1), size(0)
    {
    
    }

    bool MemoryEfficiencyInstrumentor::validate() {
        return true;
    }

    void MemoryEfficiencyInstrumentor::analyze(ir::Module &module) {
        //no static analysis necessary for this instrumentation
    }

    std::string MemoryEfficiencyInstrumentor::specificationPath() {
        return "memoryEfficiency.c";
    }

    void MemoryEfficiencyInstrumentor::initialize() {
    
        counter = 0;
        
        warpCount = (threads * threadBlocks)/32;
        //less than 32 threads still means we have at least one warp
        if(warpCount == 0) warpCount = 1;
    
        size = warpCount * 2;

        if(cudaMalloc((void **) &counter, size * sizeof(size_t)) 
            != cudaSuccess){
            std::cerr << "cudaMalloc failed!" << std::endl;
            exit(-1);
        }
        if(cudaMemset( counter, 0, size * sizeof(size_t)) != cudaSuccess){
            std::cerr << "cudaMemset failed!" << std::endl;
            exit(-1);
        }
        
        if(cudaMemcpyToSymbol(GLOBAL_MEM_BASE_ADDRESS, &counter, 
        sizeof(size_t *), 0, cudaMemcpyHostToDevice) != cudaSuccess) {
            std::cerr << "cudaMemcpyToSymbol failed!" << std::endl;
            exit(-1);
        }
    }
    
    void MemoryEfficiencyInstrumentor::extractResults(std::ostream *out) {
    
        size_t *info = new size_t[size];

        if(counter) {
            cudaMemcpy(info, counter, size * sizeof( size_t ), 
                cudaMemcpyDeviceToHost);
            cudaFree(counter);
        }
        
        unsigned int dynamicWarps = 0;
        unsigned int memTransactions = 0;
        
        for(unsigned int i = 0; i < warpCount; i++) {
        
            memTransactions += info[i * 2];
            dynamicWarps += info[i * 2 + 1];
        }
    
        *out << "Dynamic Half-Warps: " << dynamicWarps * 2 << std::endl;
        *out << "Memory Transactions: " << memTransactions <<std::endl;
        
        *out << "\nMemory Efficiency: " << 
            ((double)(dynamicWarps * 2))/((double)memTransactions) 
                * 100 << "%" << std::endl;
    
    }
}

extern void sampleKernel();

int main()
{
    lynx::addInstrumentor(new instrumentation::MemoryEfficiencyInstrumentor());
    
    sampleKernel();
}

```

Note that the _initialize_ method allocates _(2 `*` warpCount)_ amount of data on the device and the _extractResults_ method reads this data from the device back to the host, using the CUDA Runtime API. The _GLOBAL\_MEM\_BASE\_ADDRESS_ is a Lynx-specific identifier exposed to end-users, representing the GPU's global device memory reference to be used for instrumentation data. In other words, this data is allocated on the GPU's global device memory.

Here is the code for _sampleKernel.cu_:

```
__global__ void sampleKernel( int* a )
{
        a[ threadIdx.x ] += threadIdx.x;
}

void sampleKernel()
{
        int* a;
        cudaMalloc( (void**) &a, sizeof( int ) * 128 );
        cudaMemset( a, 0, sizeof( int ) * 128 );
        
        sampleKernel<<< 1, 128, 0 >>>( a );
        
        cudaFree( a );
}

```

### Building our Memory Efficiency Instrumentation ###

Here is a simple Makefile to build our example instrumentation:

```
all: MemoryEfficiencyInstrumentor

MemoryEfficiencyInstrumentor: MemoryEfficiencyInstrumentor.o sampleKernel.o
	g++ *.o -o MemoryEfficiencyInstrumentor -L/usr/local/lib -llynx_runtime

MemoryEfficiencyInstrumentor.o: MemoryEfficiencyInstrumentor.cpp
	g++ -std=c++0x MemoryEfficiencyInstrumentor.cpp -c -I/usr/local/include -I/usr/local/cuda/include

sampleKernel.o: sampleKernel.cu
	nvcc -arch=sm_20 -c sampleKernel.cu

clean:
	rm -rf *o MemoryEfficiencyInstrumentor

```

And finally, here is the output from running our memory efficiency instrumentor:

```
naila@naila-pc:~/projects/examples$ ./MemoryEfficiencyInstrumentor 
Dynamic Half-Warps: 16
Memory Transactions: 16

Memory Efficiency: 100%

```