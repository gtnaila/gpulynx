transpose: transpose.o
	g++ -o transpose transpose.o -L/usr/local/lib -llynx_runtime

transpose.o: transpose.cu
	nvcc -arch=sm_20 -c transpose.cu

clean:
	rm transpose transpose.o
