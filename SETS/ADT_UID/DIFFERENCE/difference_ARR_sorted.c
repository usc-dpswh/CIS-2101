#include <stdio.h>
#include <stdlib.h>
#define MAX 5

typedef struct node {
  int *elems;
  int count;
} SET;

void initSet(SET *main);

// union functions
SET unionSorted(SET A, SET B);
SET unionUnsorted(SET A, SET B);

// intersection functions
SET interSorted(SET A, SET B);
SET internUnsorted(SET A, SET B);

// difference functions
SET diffSorted(SET A, SET B);
SET diffUnsorted(SET A, SET B);

// helper functions
void displaySet(SET main);
void insertUnique(SET *main, int newData);

int main(){
  SET A;
  SET B;
  SET C;

  initSet(&A);
  initSet(&B);
  initSet(&C);

  insertUnique(&A, 1);
  insertUnique(&A, 2);
  insertUnique(&A, 3);

  insertUnique(&B, 4);
  insertUnique(&B, 7);
  insertUnique(&B, 2);
  insertUnique(&B, 3);
  insertUnique(&B, 5);

  // C = unionSorted(A, B);
  // printf("SET C = ");
  // displaySet(C);

  C = unionUnsorted(A, B);
  printf("SET C = ");
  displaySet(C);
}

// union functions
SET unionSorted(SET A, SET B){
  SET *C = (SET*)malloc(sizeof(SET));
  int A_INDEX = 0;
  int B_INDEX = 0;
  
  initSet(C);

  while (A_INDEX < A.count || B_INDEX < B.count){

    // if we have copied all elements from SET A
    if (A_INDEX == A.count){

      if (C->count == MAX-1){
        C->elems = (int*)realloc(C->elems, sizeof(int)* (MAX * 2));
      }

      (*C).elems[C->count] = B.elems[B_INDEX];
      C->count++;
      B_INDEX++;

    // if we have copied all elements from SET B
    } else if (B_INDEX == B.count) {

      if (C->count == MAX-1){
        C->elems = (int*)realloc(C->elems, sizeof(int)* (MAX * 2));
      }

      (*C).elems[C->count] = A.elems[A_INDEX];
      C->count++;
      A_INDEX++;

    // A less than B
    } else if (A_INDEX < A.count && A.elems[A_INDEX] < B.elems[B_INDEX]){

      (*C).elems[C->count] = A.elems[A_INDEX];
      C->count++;
      A_INDEX++;

    // B less than A
    } else if (B_INDEX < B.count && B.elems[B_INDEX] < A.elems[A_INDEX]){

      (*C).elems[C->count] = B.elems[B_INDEX];
      C->count++;
      B_INDEX++;

    // equal
    } else {

      (*C).elems[C->count] = A.elems[A_INDEX];
      C->count++;
      A_INDEX++;
      B_INDEX++;
    }
  }
  return *C;
}
SET unionUnsorted(SET A, SET B){
  SET *C = (SET*)malloc(sizeof(SET));
  int A_INDEX;
  int B_INDEX;
  int C_INDEX;

  initSet(C);

  // Copy all SET A -> SET C
  for (A_INDEX = 0 ; A_INDEX < A.count ; A_INDEX++){
    C->elems[C->count] = A.elems[A_INDEX];
    C->count++;
  }

  // Compare each element of SET B to SET C
  for (B_INDEX = 0 ; B_INDEX < B.count ; B_INDEX++){

    // realloc C if full and SET B has still elements
    if (C->count == MAX-1 && B_INDEX < B.count){
      C->elems = (int*)realloc(C->elems, sizeof(int) * (MAX * 2));
    }

    // If B no matching in C, put B in C
    for (C_INDEX = 0 ; C_INDEX < C->count && B.elems[B_INDEX] != C->elems[C_INDEX] ; C_INDEX++){}

    if (C_INDEX == C->count){
      C->elems[C->count] = B.elems[B_INDEX];  
      C->count++;
    }
  }
  return *C;
}

// helper functions
void initSet(SET *main){
  main->elems = (int*)malloc(sizeof(int) * MAX);
  main->count = 0;
}

void insertUnique(SET *main, int newData){
  if (main->count < MAX){
    main->elems[main->count] = newData;
    main->count++;
  } else {
    printf("No space available.\n");
  }
}

void displaySet(SET main){
  int x;

  printf("{ ");
  for (x = 0 ; x < main.count ; x++){
    printf("%d ", main.elems[x]);
  }
  printf("}\n");
}

