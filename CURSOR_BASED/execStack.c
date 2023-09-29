#include <stdio.h>

int calculateSum(int num1, int num2);

int main(){
  int a = 5;
  int b = 10;

  int sum = calculateSum(a, b);

  printf("%d", sum);

  return 0;
}

int calculateSum(int num1, int num2){
  // int sum = num1 + num2;
  
  return num1 + num2;
}