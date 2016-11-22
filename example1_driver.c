/***
 * Excerpted from "Programming Erlang, Second Edition",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/jaerlang2 for more book information.
***/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef unsigned char byte;

int read_cmd(byte *buff);
int write_cmd(byte *buff, int len);
int sum(int x, int y);
int twice(int x);
int sum_list(int arr[], int size);
double sum_list2(double arr[], int size);

union Data {
  double x;
  byte arr[8];
};

int main() {
  int fn, arg1, arg2, result;
  byte buff[1000];

  while (read_cmd(buff) > 0) {
    fn = buff[0];
	
    if (fn == 1) {
      arg1 = buff[1];
      arg2 = buff[2];
	  
       //debug -- you can print to stderr to debug 
	    fprintf(stderr,"calling sum %d %d\n\r",arg1,arg2); 
      result = sum(arg1, arg2);
      buff[0] = result;
      write_cmd(buff, 1);
    } else if (fn == 2) {
      arg1 = buff[1];
      result = twice(arg1);
      buff[0] = result;
      write_cmd(buff, 1);
    } else if (fn == 3){
      int size = buff[1];
      int *arr = (int*)malloc(size*sizeof(int));
      for (int i = 0; i < size; ++i)
      {
        arr[i] = buff[2+i];
      }
      result = sum_list(arr, size);
      fprintf(stderr,"result is %d\n\r", result);
      buff[0] = result;
      write_cmd(buff, 1);
    } else if (fn == 4){
      byte arr[8];
      for (int i = 0; i < 8; ++i)
      {
        arr[i] = buff[8-i];
      }
      double x;
      memcpy(&x, arr, sizeof(double));
      fprintf(stderr,"the float is %f\n\r", x);
      result = 1;
      buff[0] = result;
      write_cmd(buff, 1);
    }
    else if(fn == 5){
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
      double sum = sum_list2(arr, size);
      // fprintf(stderr,"result is %f\n\r", sum);
      union Data data;
      data.x = sum;
      // for (int i = 0; i < 8; ++i)
      // {
      //   fprintf(stderr,"the bit is %d\n\r", data.arr[i]);
      // }
      write_cmd(data.arr, 8);
    }
    else{
      /* just exit on unknown function */
      exit(EXIT_FAILURE);
    }
    
  }
}
