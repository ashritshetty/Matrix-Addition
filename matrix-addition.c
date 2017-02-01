#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

void add_imatrix(int **input1, int **input2, int **output, int *m, int *n)
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

void add_fmatrix(float **input1, float **input2, float **output, int *m, int *n)
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
    read_fmatrix(argv[1], &m1, &n1, &hostmatrix1);
  	read_fmatrix(argv[2], &m2, &n2, &hostmatrix2);
    matrix_check(m1, n1, m2, n2);
    matrix_size = m1 * n1;
    hostmatrix3 = (float *)calloc(matrix_size, sizeof(float));
    add_fmatrix(&hostmatrix1, &hostmatrix2, &hostmatrix3, &m1, &n1);
    write_fmatrix(argv[3], &m1, &n1, &hostmatrix3);
    free(hostmatrix1);
    free(hostmatrix2);
    free(hostmatrix3);
  }

  if (argv[4] == "int")
  {
    int *hostmatrix1, *hostmatrix2, *hostmatrix3;
    read_imatrix(argv[1], &m1, &n1, &hostmatrix1);
  	read_imatrix(argv[2], &m2, &n2, &hostmatrix2);
    matrix_check(m1, n1, m2, n2);
    matrix_size = m1 * n1;
    hostmatrix3 = (int *)calloc(matrix_size, sizeof(int));
    add_imatrix(&hostmatrix1, &hostmatrix2, &hostmatrix3, &m1, &n1);
    write_imatrix(argv[3], &m1, &n1, &hostmatrix3);
    free(hostmatrix1);
    free(hostmatrix2);
    free(hostmatrix3);
  }

  return 0;
}
