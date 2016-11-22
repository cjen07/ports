#include "stdio.h"
#include "stdlib.h"
#include "cblas.h"

double sum_list(double arr[], int size){
  double sum = 0.0;
  
  for (int i = 0; i < size; ++i)
  {
    sum += arr[i];
  }
  return sum;
}

double* mul(int m, int k, int n, double *A, double *B)
{
  double alpha, beta;

  alpha = 1.0; beta = 0.0;

  double *C = (double*)malloc(m*n*sizeof(double));

  for (int i = 0; i < m*n; i++) {
    C[i] = 0.0;
  }

  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
                m, n, k, alpha, A, k, B, n, beta, C, n);

  return C;
}

