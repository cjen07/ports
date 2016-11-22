#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef unsigned char byte;

int read_cmd(byte *buff);
int write_cmd(byte *buff, int len);
double sum_list(double arr[], int size);
double* mul(int m, int k, int n, double *A, double *B);

union Data {
  double x;
  byte arr[8];
};

int main() {
  int fn, arg1, arg2, result;
  byte buff[1000];

  while (read_cmd(buff) > 0) {
    fn = buff[0];
	
    if (fn == 1){
      int size = buff[1];
      double *arr = (double*)malloc(size*sizeof(double));
      for (int i = 0; i < size; ++i)
      {
        byte num[8];
        for (int j = 0; j < 8; ++j)
        {
          num[j] = buff[2+j+i*8];
        }
        double x;
        memcpy(&x, num, sizeof(double));
        arr[i] = x;
      }
      double sum = sum_list(arr, size);
      union Data data;
      data.x = sum;
      buff[0] = 1;
      for (int i = 0; i < 8; ++i)
      {
        buff[1+i] = data.arr[i];
      }
      write_cmd(buff, 9);
    }
    else if(fn == 2){
      int m = buff[1];
      int k = buff[2];
      int n = buff[3];
      double *A = (double*)malloc(m*k*sizeof(double));
      double *B = (double*)malloc(k*n*sizeof(double));
      int c = 4;
      for (int i = 0; i < m*k; ++i)
      {
        byte num[8];
        for (int j = 0; j < 8; ++j)
        {
          num[j] = buff[c+j+i*8];
        }
        double x;
        memcpy(&x, num, sizeof(double));
        A[i] = x;
      }
      c += m*k*8;
      for (int i = 0; i < k*n; ++i)
      {
        byte num[8];
        for (int j = 0; j < 8; ++j)
        {
          num[j] = buff[c+j+i*8];
        }
        double x;
        memcpy(&x, num, sizeof(double));
        B[i] = x;
      }
      double *C = mul(m, k, n, A, B);

      buff[0] = 2;
      buff[1] = m;
      buff[2] = n;
      c = 3;

      for (int i = 0; i < m*n; ++i)
      {
        union Data data;
        data.x = C[i];
        for (int j = 0; j < 8; ++j)
        {
          buff[c+j+i*8] = data.arr[j]; 
        }
      }
      
      write_cmd(buff, c+m*n*8);
    }
    else{
      /* just exit on unknown function */
      exit(EXIT_FAILURE);
    }
    
  }
}
