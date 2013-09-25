#include <stdlib.h>
#include <stdio.h>

#include "cuda_utils.h"
#include "timer.c"

#define BLOCK_DIM     16

typedef float dtype;

__global__
void naiveTrans(dtype *AT, dtype *A, int N) {
    
    int x = blockIdx.x * BLOCK_DIM + threadIdx.x;
    int y = blockIdx.y * BLOCK_DIM + threadIdx.y;

    if(x < N && y < N)
        AT[x * N + y] = A[y * N + x];
    
}

__global__ 
void matTrans(dtype* AT, dtype* A, int N)  {

    __shared__ dtype block[BLOCK_DIM][BLOCK_DIM+1];

    int x = blockIdx.x * BLOCK_DIM + threadIdx.x;
    int y = blockIdx.y * BLOCK_DIM + threadIdx.y;

    if(x < N && y < N)
        block[threadIdx.y][threadIdx.x] = A[y * N + x];

    __syncthreads();

    x = blockIdx.y * BLOCK_DIM + threadIdx.x;
    y = blockIdx.x * BLOCK_DIM + threadIdx.y;

    if(x < N && y < N)
	    AT[y * N + x] = block[threadIdx.x][threadIdx.y];
    
}

void
parseArg (int argc, char** argv, int* N)
{
	if(argc == 2) {
		*N = atoi (argv[1]);
		assert (*N > 0);
	} else {
		fprintf (stderr, "usage: %s <N>\n", argv[0]);
		exit (EXIT_FAILURE);
	}
}


void
initArr (dtype* in, int N)
{
	int i;

	for(i = 0; i < N; i++) {
		in[i] = (dtype) rand () / RAND_MAX;
	}
}

void
cpuTranspose (dtype* A, dtype* AT, int N)
{
	int i, j;

	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			AT[j * N + i] = A[i * N + j];
		}
	}
}

int
cmpArr (dtype* a, dtype* b, int N)
{
	int cnt, i;

	cnt = 0;
	for(i = 0; i < N; i++) {
		if(abs(a[i] - b[i]) > 1e-6) cnt++;
	}

	return cnt;
}

void
gpuTranspose (dtype* A, dtype* AT, int N)
{
    struct stopwatch_t* timer = NULL;
    long double t_gpu;

    cudaError_t error;

    /* allocate data on GPU */
    dtype *A_gpu, *AT_gpu;
    error = cudaMalloc((void **) &A_gpu, (N * N * sizeof (dtype)));
    if(error != cudaSuccess)
    {
	    printf("cudaMalloc failed: %d\n", error);
    }
    error = cudaMalloc((void **) &AT_gpu, (N * N * sizeof (dtype)));
    if(error != cudaSuccess)
    {
	    printf("cudaMalloc failed: %d\n", error);
    }

    // copy host data to GPU
    error = cudaMemcpy(A_gpu, A, N * N * sizeof (dtype), cudaMemcpyHostToDevice);	
    if(error != cudaSuccess)
    {
        printf("cudaMemcpy failed: %d\n", error);
    } 
    error = cudaMemset(AT_gpu, 0, N * N * sizeof(dtype));
    if(error != cudaSuccess)
    {
        printf("cudaMemset failed: %d\n", error);
    }

    dim3 grid(N/BLOCK_DIM, N/BLOCK_DIM, 1), threads(BLOCK_DIM, BLOCK_DIM, 1);

    /* Setup timers */
    stopwatch_init ();
    timer = stopwatch_create ();

    

    /* warmup */
    matTrans<<<grid, threads>>>(AT_gpu, A_gpu, N);
    error = cudaThreadSynchronize();
    printf("cudaThreadSynchronize error code: %d\n", error);
    
    int numIterations = 1;
    /* run transpose kernel */
    for(int i = 0; i < numIterations; i++)
    {
        stopwatch_start (timer);
	
        matTrans<<<grid, threads>>>(AT_gpu, A_gpu, N);

        error = cudaThreadSynchronize ();
        printf("cudaThreadSynchronize error code: %d\n", error);
        t_gpu = stopwatch_stop (timer);
        fprintf (stderr, "GPU transpose: %Lg secs ==> %Lg billion elements/second\n",               
            t_gpu, (N * N) / t_gpu * 1e-9 );
    }

    /* copy results from GPU back to host */
    error = cudaMemcpy(AT, AT_gpu, N * N * sizeof (dtype), cudaMemcpyDeviceToHost);
    if(error != cudaSuccess)
    {
	    printf("cudaMemcpy (copying back from device to host) failed: %d\n", error);
    }

    cudaFree(A_gpu);
    cudaFree(AT_gpu);
}

int 
main(int argc, char** argv)
{
    /* variables */
    dtype *A, *ATgpu, *ATcpu;
    int err;

	int N;

    struct stopwatch_t* timer = NULL;
    long double t_cpu;


	N = -1;
	parseArg (argc, argv, &N);

    /* input and output matrices on host */
    /* output */
    ATcpu = (dtype*) malloc (N * N * sizeof (dtype));
    ATgpu = (dtype*) malloc (N * N * sizeof (dtype));

    /* input */
    A = (dtype*) malloc (N * N * sizeof (dtype));

    initArr (A, N * N);

	/* GPU transpose kernel */
	gpuTranspose (A, ATgpu, N);

    /* Setup timers */
    stopwatch_init ();
    timer = stopwatch_create ();

	stopwatch_start (timer);
    
    /* compute reference array */	
    cpuTranspose (A, ATcpu, N);
    t_cpu = stopwatch_stop (timer);
    fprintf (stderr, "Time to execute CPU transpose kernel: %Lg secs\n",
           t_cpu);

    /* check correctness */
	err = cmpArr (ATgpu, ATcpu, N * N);
	if(err) {
		fprintf (stderr, "Transpose failed: %d\n", err);
	} else {
		fprintf (stderr, "Transpose successful\n");
	}

	free (A);
	free (ATgpu);
	free (ATcpu);

  return 0;
}
