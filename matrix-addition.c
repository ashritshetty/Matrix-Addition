#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

void add_matrix(int **input1, int **input2, int **output, int *m, int *n)
{
  int i, j, offset;

  for(i = 0; i < m; i++)
  {
    for(j = 0; j < n; j++)
    {
      offset = ;
      *output[offset] = *input1[offset] + *input2[offset];
    }
  }
}

int main(int argc, char *argv[])
{
  int m1, n1, m2, n2, matrix_size;
	int *hostmatrix1, *hostmatrix2, *hostmatrix3;

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

  // Add the two input matrices
  add_matrix(&hostmatrix1, &hostmatrix2, &hostmatrix3, &m1, &n1);

	// Write result matrix to output file
  write_matrix(argv[3], &m1, &n1, &hostmatrix3);

	// Free host memory (for output image)
	free(hostmatrix1);
  free(hostmatrix2);
  free(hostmatrix3);

  return 0;
}
