#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

void add_imatrix(int **input1, int **input2, int **output, int *m, int *n)
{
  int i;
  int t1, t2;
  t1 = *m;
  t2 = *n;
  for(i = 0; i < t1*t2; i++)
  {
    *(*output+i) = *(*input1+i) + *(*input2+i);
  }
}

void add_fmatrix(float **input1, float **input2, float **output, int *m, int *n)
{
  int i;
  int t1, t2;
  t1 = *m;
  t2 = *n;
  for(i = 0; i < t1*t2; i++)
  {
    *(*output+i) = *(*input1+i) + *(*input2+i);
  }
}

void read_imatrix(char *filename, int *m, int *n, int **values)
{
  FILE* name;
  int i, j, k;
  int t1, t2, t3;
  name = fopen(filename, "r+");
  if(name != NULL)
  {
    k = 0;
    fscanf(name, "%d %d\n", &t1, &t2);
    *m = t1;
    *n = t2;
    *values = (int *)calloc(t1*t2, sizeof(int));
    for(i = 1; i <= t1; i++)
    {
      for(j = 1; j <= t2; j++)
      {
        if(j < t2)
        {
          fscanf(name, "%d,", &t3);
          *(*values+k) = t3;
          k++;
        }
        else
        {
          fscanf(name, "%d\n", &t3);
          *(*values+k) = t3;
          k++;
        }
      }
    }
    fclose(name);
  }
  else
  {
    printf("File read failed\n");
		exit(1);
  }
}

void read_fmatrix(char *filename, int *m, int *n, float **values)
{
  FILE* name;
  int i, j, k;
  int t1, t2;
  float t3;
  name = fopen(filename, "r+");
  if(name != NULL)
  {
    k = 0;
    fscanf(name, "%d %d\n", &t1, &t2);
    *m = t1;
    *n = t2;
    *values = (float *)calloc(t1*t2, sizeof(float));
    for(i = 1; i <= t1; i++)
    {
      for(j = 1; j <= t2; j++)
      {
        if(j < t2)
        {
          fscanf(name, "%f,", &t3);
          *(*values+k) = t3;
          k++;
        }
        else
        {
          fscanf(name, "%f\n", &t3);
          *(*values+k) = t3;
          k++;
        }
      }
    }
    fclose(name);
  }
  else
  {
    printf("File read failed\n");
		exit(1);
  }
}

void write_imatrix(char *filename, int *m, int *n, int **values)
{
  FILE* name;
  int i, j, k;
  int t1, t2, t3;
  name = fopen(filename, "w+");
  if(name != NULL)
  {
    k = 0;
    t1 = *m;
    t2 = *n;
    fprintf(name, "%d %d\n", t1, t2);
    for(i = 1; i <= t1; i++)
    {
      for(j = 1; j <= t2; j++)
      {
        if(j < t2)
        {
          t3 = *(*values+k);
          fprintf(name, "%d,", t3);
          k++;
        }
        else
        {
          t3 = *(*values+k);
          fprintf(name, "%d\n", t3);
          k++;
        }
      }
    }
    fclose(name);
  }
  else
  {
    printf("File write failed\n");
		exit(1);
  }
}

void write_fmatrix(char *filename, int *m, int *n, float **values)
{
  FILE* name;
  int i, j, k;
  int t1, t2;
  float t3;
  name = fopen(filename, "w+");
  if(name != NULL)
  {
    k = 0;
    t1 = *m;
    t2 = *n;
    fprintf(name, "%d %d\n", t1, t2);
    for(i = 1; i <= t1; i++)
    {
      for(j = 1; j <= t2; j++)
      {
        if(j < t2)
        {
          t3 = *(*values+k);
          fprintf(name, "%f,", t3);
          k++;
        }
        else
        {
          t3 = *(*values+k);
          fprintf(name, "%f\n", t3);
          k++;
        }
      }
    }
    fclose(name);
  }
  else
  {
    printf("File write failed\n");
		exit(1);
  }
}

void matrix_check(int m1, int n1, int m2, int n2)
{
  if ((m1-m2)+(n1-n2) != 0)
  {
    printf("Matrix dimensions must be PxQ and PxQ respectively\n");
    exit(1);
  }
}

int main(int argc, char *argv[])
{
  clock_t t1, t2, t3, t4;
  double time_k, time_f;
  t1 = clock();
  int m1, n1, m2, n2, matrix_size;

  if (argc != 5)
  {
    printf("Usage: ./matrix-addition matrix1.mat matrix2.mat matrix3.mat float/int \n");
    exit(1);
  }

  if (strcmp(argv[4], "float") == 0)
  {

    float *hostmatrix1, *hostmatrix2, *hostmatrix3;
    read_fmatrix(argv[1], &m1, &n1, &hostmatrix1);
    read_fmatrix(argv[2], &m2, &n2, &hostmatrix2);
    matrix_check(m1, n1, m2, n2);
    matrix_size = m1 * n1;
    hostmatrix3 = (float *)calloc(matrix_size, sizeof(float));
    t2 = clock();
    add_fmatrix(&hostmatrix1, &hostmatrix2, &hostmatrix3, &m1, &n1);
    t3 = clock();
    write_fmatrix(argv[3], &m1, &n1, &hostmatrix3);
    free(hostmatrix1);
    free(hostmatrix2);
    free(hostmatrix3);
  }

  if (strcmp(argv[4], "int") == 0)
  {
    int *hostmatrix1, *hostmatrix2, *hostmatrix3;
    read_imatrix(argv[1], &m1, &n1, &hostmatrix1);
    read_imatrix(argv[2], &m2, &n2, &hostmatrix2);
    matrix_check(m1, n1, m2, n2);
    matrix_size = m1 * n1;
    hostmatrix3 = (int *)calloc(matrix_size, sizeof(int));
    t2 = clock();
    add_imatrix(&hostmatrix1, &hostmatrix2, &hostmatrix3, &m1, &n1);
    t3 = clock();
    write_imatrix(argv[3], &m1, &n1, &hostmatrix3);
    free(hostmatrix1);
    free(hostmatrix2);
    free(hostmatrix3);
  }
  t4 = clock();
	time_k = (double)(t3-t2)/CLOCKS_PER_SEC;
  time_f = (double)(t4-t1)/CLOCKS_PER_SEC;
	printf("Kernel Time %f\n", time_k);
  printf("Total time %f\n", time_f);

  return 0;
}
