#include <stdio.h>
#include <stdlib.h>
#define MAX 8

typedef char SET[MAX];

void displaySet(SET main);
void displayBits(SET main);
void insertElem(SET main, char index);
void deleteElem(SET main, char index);
SET* setUnion(SET A, SET B);
SET* setIntersection(SET A, SET B);
SET* setDifference(SET A, SET B);

int main() {
  SET A = {0};
  SET B = {0};
  SET *C;

  insertElem(A, 3);
  insertElem(A, 5);
  insertElem(A, 0);
  insertElem(A, 6);

  insertElem(B, 4);
  insertElem(B, 5);
  insertElem(B, 1);
  insertElem(B, 0);

  printf("SET A\n");
  displaySet(A);
  displayBits(A);
  
  printf("\nSET B\n");
  displayBits(B);
  displaySet(B);

  printf("\nA U B\n");
  C = setUnion(A, B);
  displayBits(*C);
  displaySet(*C);

  printf("\nA ∩ B\n");
  C = setIntersection(A, B);
  displayBits(*C);
  displaySet(*C);

  printf("\nA - B\n");
  C = setDifference(A, B);
  displayBits(*C);
  displaySet(*C);

  return 0;
}

SET* setUnion(SET A, SET B){
  SET *C = (SET*)calloc(sizeof(SET), 1);
  int x;

  printf("-- initial bits --\n");
  displayBits(A);
  displayBits(B);
  printf("-- initial bits --\n");

  if (C != NULL){
    for (x = 0 ; x < MAX ; x++){
      (*C)[x] = A[x] | B[x];
    }
  }
  return C;
}

SET* setIntersection(SET A, SET B){
  SET *C = (SET*)calloc(sizeof(SET), 1);
  int x;

  printf("-- initial bits --\n");
  displayBits(A);
  displayBits(B);
  printf("-- initial bits --\n");

  if (C != NULL){
    for (x = 0 ; x < MAX ; x++){
      (*C)[x] = A[x] & B[x];
    }
  }
  return C;
}

SET* setDifference(SET A, SET B){
  SET *C = (SET*)calloc(sizeof(SET), 1);
  int x;

  printf("-- initial bits --\n");
  displayBits(A);
  displayBits(B);
  printf("-- initial bits --\n");

  if (C != NULL){
    for (x = 0 ; x < MAX ; x++){
      (*C)[x] = A[x] & ~B[x];
    }
  }
  return C;
}

void displaySet(SET main){
  int x;

  for (x = 0 ; x < MAX ; x++){
    if (main[x] == 1){
      printf("%d ", x);
    }
  }
  printf("\n");
}

void displayBits(SET main){
  int x;

  for (x = 0 ; x < MAX ; x++){
    printf("%d ", main[x] == 1 ? 1 : 0);
  }
  printf("\n");
}

void insertElem(SET main, char index){
  if (index < MAX){
    main[index] = 1;
  }
}

void deleteElem(SET main, char index){
  if (index < MAX){
    main[index] = 0;
  }
}



