#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda.h>
#include <cuda_runtime.h>

__global__ void MatrixAdd(int *matrix1, int *matrix2, int *matrix3, int m, int n)
{
	int x = blockIdx.x * blockDim.x + threadIdx.x;
	int y = blockIdx.y * blockDim.y + threadIdx.y;

	if (x < m && y < n)
	{
    int offset = ????;
		matrix3[offset] = matrix1[offset] + matrix2[offset];
	}
}

void read_matrix(char *filename, int *m, int *n, int **values)
{
  int a, b;
  int ret, size;
	FILE* name;

	name = fopen(filename, "rb");
	if(name != NULL)
	{
    ret =  fread(m, sizeof(int), 1, name);
    ret += fread(n, sizeof(int), 1, name);
    a = *m;
    b = *n;
    size = a*b;
    *values = (int *)calloc(size, sizeof(int));
    ret += fread(*values, sizeof(int), size, name);
  }

  if(ret != 0)
  {
    printf("Improper read operation");
    fflush(stdout);
  }
  fclose(name);
}

void write_matrix(char *filename, int *m, int *n, int **values)
{
  int a, b;
  int ret, size;
  FILE* name;

  name = fopen(filename, "wb");
  if(name != NULL)
  {
    ret =  fwrite(m, sizeof(int), 1, name);
    ret += fwrite(n, sizeof(int), 1, name);
    a = *m;
    b = *n;
    size = a*b;
    ret += fwrite(*values, sizeof(int), size, name);
  }

  if(ret != 0)
  {
    printf("Improper write operation");
    fflush(stdout);
  }
  fclose(name);
}

int main(int argc, char *argv[])
{
  int m1, n1, m2, n2, matrix_size;
	int *hostmatrix1, *hostmatrix2, *hostmatrix3;
	int *devicematrix1, *devicematrix2, *devicematrix3;

	if (argc != 4)
	{
		printf("Usage: ./matrix-addition matrix1.mat matrix2.mat matrix3.mat \n");
		exit(1);
	}

  // Read the two input matrix
  read_matrix(argv[1], &m1, &n1, &hostmatrix1);
	read_matrix(argv[2], &m2, &n2, &hostmatrix2);

  // Check if matrix addition is possible
  if ((m1-m2)+(n1-n2) != 0)
  {
    printf("Matrix dimensions m and n need to be same \n");
  }

	// Set matrix size information
	matrix_size = m1 * n1 * sizeof(int);

	// Allocate memory for host matrix (output)
  hostmatrix3 = (int *)calloc(matrix_size, sizeof(int));

	// Allocate memory for matrix (input and output) on GPU
	cudaMalloc(&devicematrix1, matrix_size);
  cudaMalloc(&devicematrix2, matrix_size);
  cudaMalloc(&devicematrix3, matrix_size);

	// Copy host input matrix to device input matrix
	cudaMemcpy(devicematrix1, hostmatrix1, matrix_size, cudaMemcpyHostToDevice);
  cudaMemcpy(devicematrix2, hostmatrix2, matrix_size, cudaMemcpyHostToDevice);

	// Set kernel dimensions and call kernel
	dim3 dimGrid(????,????);
	dim3 dimBlock(????, ????, 1);
	MatrixAdd <<< dimGrid, dimBlock >>> (devicematrix1, devicematrix2, devicematrix3, m1, n1);

	// Copy result matrix back to host
	cudaMemcpy(hostmatrix3, devicematrix3, matrix_size, cudaMemcpyDeviceToHost);

	// Write result matrix to output file
  write_matrix(argv[3], &m1, &n1, &hostmatrix3);

	// Free device memory (for input and output image)
	cudaFree(devicematrix1);
  cudaFree(devicematrix2);
  cudaFree(devicematrix3)

	// Free host memory (for output image)
	free(hostmatrix1);
  free(hostmatrix2);
  free(hostmatrix3);

  return 0;
}
