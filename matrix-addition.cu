#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda.h>
#include <cuda_runtime.h>

__global__ void MatrixAddI(int *matrix1, int *matrix2, int *matrix3, int m, int n)
{
	int x = blockIdx.x * blockDim.x + threadIdx.x;
	int y = blockIdx.y * blockDim.y + threadIdx.y;

	if (x < m && y < n)
	{
    int offset = ????;
		matrix3[offset] = matrix1[offset] + matrix2[offset];
	}
}

__global__ void MatrixAddF(float *matrix1, float *matrix2, float *matrix3, int m, int n)
{
	int x = blockIdx.x * blockDim.x + threadIdx.x;
	int y = blockIdx.y * blockDim.y + threadIdx.y;

	if (x < m && y < n)
	{
    int offset = ????;
		matrix3[offset] = matrix1[offset] + matrix2[offset];
	}
}

void read_imatrix(char *filename, int *m, int *n, int **values)
{
	FILE* name;
  int i, j, k;

	name = fopen(filename, "r+");
	if(name != NULL)
	{
    k = 0;
    fscanf(name, "%d %d\n", m, n);
    for(i = 1; i <= *m; i++)
    {
      for(j = 1; j <= *n; j++)
      {
        if(j < *n)
        {
          fscanf(name, "%d,", values[k]);
          k++;
        }
        else
        {
          fscanf(name, "%d\n", values[k]);
          k++
        }
      }
    }
    fclose(name);
  }
  else
  {
    printf("File read failed\n");
  }
}

void read_fmatrix(char *filename, int *m, int *n, float **values)
{
	FILE* name;
  int i, j, k;

	name = fopen(filename, "r+");
	if(name != NULL)
	{
    k = 0;
    fscanf(name, "%d %d\n", m, n);
    for(i = 1; i <= *m; i++)
    {
      for(j = 1; j <= *n; j++)
      {
        if(j < *n)
        {
          fscanf(name, "%f,", values[k]);
          k++;
        }
        else
        {
          fscanf(name, "%f\n", values[k]);
          k++
        }
      }
    }
    fclose(name);
  }
  else
  {
    printf("File read failed\n");
  }
}

void write_imatrix(char *filename, int *m, int *n, int **values)
{
	FILE* name;
  int i, j, k;

	name = fopen(filename, "w+");
	if(name != NULL)
	{
    k = 0;
    fprintf(name, "%d %d\n", m, n);
    for(i = 1; i <= *m; i++)
    {
      for(j = 1; j <= *n; j++)
      {
        if(j < *n)
        {
          fprintf(name, "%d,", values[k]);
          k++;
        }
        else
        {
          fprintf(name, "%d\n", values[k]);
          k++
        }
      }
    }
    fclose(name);
  }
  else
  {
    printf("File write failed\n");
  }
}

void write_fmatrix(char *filename, int *m, int *n, float **values)
{
	FILE* name;
  int i, j, k;

	name = fopen(filename, "w+");
	if(name != NULL)
	{
    k = 0;
    fprintf(name, "%d %d\n", m, n);
    for(i = 1; i <= *m; i++)
    {
      for(j = 1; j <= *n; j++)
      {
        if(j < *n)
        {
          fprintf(name, "%f,", values[k]);
          k++;
        }
        else
        {
          fprintf(name, "%f\n", values[k]);
          k++
        }
      }
    }
    fclose(name);
  }
  else
  {
    printf("File write failed\n");
  }
}

void matrix_check(int m1, int n1, int m2, int n2)
{
  if ((m1-m2)+(n1-n2) != 0)
  {
    printf("Matrix dimensions m and n need to be same \n");
    exit(1);
  }
}

int main(int argc, char *argv[])
{
  int m1, n1, m2, n2, matrix_size;

	if (argc != 5)
	{
		printf("Usage: ./matrix-addition matrix1.mat matrix2.mat matrix3.mat float/int \n");
		exit(1);
	}

	if (argv[4] == "float")
  {
		float *hostmatrix1, *hostmatrix2, *hostmatrix3;
		float *devicematrix1, *devicematrix2, *devicematrix3;
  	read_matrix(argv[1], &m1, &n1, &hostmatrix1);
		read_matrix(argv[2], &m2, &n2, &hostmatrix2);
		matrix_size = m1 * n1;
  	hostmatrix3 = (float *)calloc(matrix_size, sizeof(float));
		cudaMalloc(&devicematrix1, matrix_size);
  	cudaMalloc(&devicematrix2, matrix_size);
  	cudaMalloc(&devicematrix3, matrix_size);
		cudaMemcpy(devicematrix1, hostmatrix1, matrix_size, cudaMemcpyHostToDevice);
  	cudaMemcpy(devicematrix2, hostmatrix2, matrix_size, cudaMemcpyHostToDevice);
		dim3 dimGrid(????,????);
		dim3 dimBlock(????, ????, 1);
		MatrixAdd <<< dimGrid, dimBlock >>> (devicematrix1, devicematrix2, devicematrix3, m1, n1);
		cudaMemcpy(hostmatrix3, devicematrix3, matrix_size, cudaMemcpyDeviceToHost);
  	write_matrix(argv[3], &m1, &n1, &hostmatrix3);
		cudaFree(devicematrix1);
  	cudaFree(devicematrix2);
  	cudaFree(devicematrix3)
		free(hostmatrix1);
  	free(hostmatrix2);
  	free(hostmatrix3);
	}

	if (argv[4] == "int")
  {
		int *hostmatrix1, *hostmatrix2, *hostmatrix3;
		int *devicematrix1, *devicematrix2, *devicematrix3;
  	read_matrix(argv[1], &m1, &n1, &hostmatrix1);
		read_matrix(argv[2], &m2, &n2, &hostmatrix2);
		matrix_size = m1 * n1;
  	hostmatrix3 = (int *)calloc(matrix_size, sizeof(int));
		cudaMalloc(&devicematrix1, matrix_size);
  	cudaMalloc(&devicematrix2, matrix_size);
  	cudaMalloc(&devicematrix3, matrix_size);
		cudaMemcpy(devicematrix1, hostmatrix1, matrix_size, cudaMemcpyHostToDevice);
  	cudaMemcpy(devicematrix2, hostmatrix2, matrix_size, cudaMemcpyHostToDevice);
		dim3 dimGrid(????,????);
		dim3 dimBlock(????, ????, 1);
		MatrixAdd <<< dimGrid, dimBlock >>> (devicematrix1, devicematrix2, devicematrix3, m1, n1);
		cudaMemcpy(hostmatrix3, devicematrix3, matrix_size, cudaMemcpyDeviceToHost);
  	write_matrix(argv[3], &m1, &n1, &hostmatrix3);
		cudaFree(devicematrix1);
  	cudaFree(devicematrix2);
  	cudaFree(devicematrix3)
		free(hostmatrix1);
  	free(hostmatrix2);
  	free(hostmatrix3);
	}

  return 0;
}
