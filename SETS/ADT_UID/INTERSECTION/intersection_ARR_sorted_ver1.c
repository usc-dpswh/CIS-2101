#include <stdio.h>
#include <stdlib.h>
#define MAX 5

typedef int SET[MAX];

void initSet(SET main);
SET* intersectionSorted(SET A, SET B);
void displaySet(SET main);

int main(){
  SET A = {1,2,5,6,-1};
  SET B = {2,3,6,7,-1};
  SET *C;

  // initSet(A);
  // initSet(B);
  printf("SET A\n");
  displaySet(A);

  printf("SET B\n");
  displaySet(B);

  printf("A ∩ B\n");
  C = intersectionSorted(A, B);
  displaySet(*C);

}

void initSet(SET main){
  int x;

  for (x = 0 ; x < MAX ; x++){
    main[x] = -1;
  }

  // printf("Initialized SET.\n");
}

SET* intersectionSorted(SET A, SET B){
  int A_INDEX = 0;
  int B_INDEX = 0;
  int C_INDEX = 0;
  SET *C = (SET*)calloc(sizeof(SET), 1);

  initSet(*C);

  while(A_INDEX < MAX && B_INDEX < MAX){
    if (A[A_INDEX] < B[B_INDEX]){
      A_INDEX++;       
    } else if (B[B_INDEX] < A[A_INDEX]){
      B_INDEX++;
    } else {

      (*C)[C_INDEX] = A[A_INDEX];
      A_INDEX++;
      B_INDEX++;
      C_INDEX++;

    }
  }
  return C;
}

void displaySet(SET main){
  int x;

  printf("{ ");
  for (x = 0 ; x < MAX && main[x] != -1 ; x++){
    printf("%d ", main[x]);
  }
  printf("}\n");

  // printf("{");
  // while (x < MAX && main[x] != -1){
  //   printf("%d ", main[x]);
  //   x++;
  // }
  // printf("}\n");
}