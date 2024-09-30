#include <stdio.h>
#include <stdlib.h>
#define MAX 5

typedef int SET[MAX];

int main(){
  SET A = {1,2,3};
  SET* B = (SET*)malloc(sizeof(SET));
  if (B != NULL){
    B = (SET*)realloc(B, sizeof(SET) * MAX * 2);
  }
}