/***
 * Excerpted from "Programming Erlang, Second Edition",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/jaerlang2 for more book information.
***/
int sum(int x, int y){
  return x+y;
}

int twice(int x){
  return 2*x;
}

int sum_list(int arr[], int size){
  int sum = 0;

  for (int i = 0; i < size; ++i)
  {
    sum += arr[i];
  }
  return sum;
}

double sum_list2(double arr[], int size){
  double sum = 0.0;
  
  for (int i = 0; i < size; ++i)
  {
    sum += arr[i];
  }
  return sum;
}

