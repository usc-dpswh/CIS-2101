#include <stdio.h>
#include <stdlib.h>
#define MAX 5

// Reminder that returning an elemsay is not allowed.

// typedef int SET[MAX];
typedef struct node {
  int *elems;
  int count;
} SET;

//* Utility Functions
void initSet(SET *main);
void displaySet(SET main, char name);

//* Main Functions
SET *setUnion(SET A, SET B);
SET *unionSorted(SET A, SET B);
SET *intersectionSorted(SET A, SET B);
SET *differenceSorted(SET A, SET B);

int main() {
  SET A = {NULL, 0};
  SET B = {NULL, 0};
  // The reason why we declare it as a pointer to a SET variable is because we
  // want it to point to the address returned from SET operations. Plus, you
  // cannot return elemsay themselves. What you can do is return the address
  // pointing to the first element of an elems.
  SET *C;

  // int A_ARR[MAX] = {1, 3, 5, 7, 9};
  // int B_ARR[MAX] = {2, 4, 6, 8, 10};
  int A_ARR[MAX] = {1, 3, 5, 7, 9};
  int B_ARR[MAX] = {2, 3, 6, 7, 9};
  A.elems = A_ARR;
  B.elems = B_ARR;
  A.count = 5;
  B.count = 5;

  displaySet(A, 'A');
  displaySet(B, 'B');

  C = intersectionSorted(A, B);
  displaySet(*C, 'C');

  // C = differenceSorted(A, B);
  // displaySet(*C, 'C');
  // C = unionSorted(A, B);
  // displaySet(*C, 'C');
}

//* Utility Functions
void initSet(SET *main) {
  main = (SET *)calloc(sizeof(SET), 1);
  printf("initSet()\n");
}
void displaySet(SET main, char name) {
  int x;
  printf("SET %c:\n", name);
  printf("{");
  for (x = 0; x < main.count; x++) {
    if (x > 0) {
      printf(",");
    }
    printf("%d", main.elems[x]);
  }
  printf("}\n");
}

//* Main Functions
SET *setUnion(SET A, SET B);
SET *unionSorted(SET A, SET B) {
  // 1 2 4 7
  // 2 4 5 8
  // 1 2 4 5 7 8

  int A_INDEX = 0;
  int B_INDEX = 0;
  SET *C = (SET *)calloc(sizeof(SET), 1);
  if (C != NULL) {
    C->elems = (int *)malloc(sizeof(int) * MAX);
    C->count = 0;
    if (C->elems != NULL) {

      while (A_INDEX < A.count && B_INDEX < B.count) {
        if (A_INDEX == MAX) {
          C->elems[C->count] = B.elems[B_INDEX];
          B_INDEX++;
          C->count++;
        } else if (B_INDEX == MAX) {
          C->elems[C->count] = A.elems[A_INDEX];
          A_INDEX++;
          C->count++;
        } else if (A.elems[A_INDEX] < B.elems[B_INDEX]) {
          C->elems[C->count] = A.elems[A_INDEX];
          A_INDEX++;
          C->count++;
        } else if (B.elems[B_INDEX] < A.elems[A_INDEX]) {
          C->elems[C->count] = B.elems[B_INDEX];
          B_INDEX++;
          C->count++;
        } else {
          C->elems[C->count] = A.elems[A_INDEX];
          A_INDEX++;
          B_INDEX++;
          C->count++;
        }
        if (C->count == MAX) {
          C->elems = (int *)realloc(C->elems, sizeof(int) * MAX * 2);
        } 
      }
    }
  }
  return C;
}
// SET *intersectionSorted(SET A, SET B) {
//   SET *C = (SET *)calloc(sizeof(SET), 1);
//   C->count = 0;

//   if (C == NULL) {
//     exit(EXIT_FAILURE);
//   } else {
//     C->elems = (int*)malloc(sizeof(int)*MAX);
//     if (C->elems != NULL){
//       int A_idx = 0, B_idx = 0;

//       while (A_idx < A.count && B_idx < B.count) {
//         if (A.elems[A_idx] < B.elems[B_idx]) {
//           A_idx++;
//         } else if (A.elems[A_idx] > B.elems[B_idx]) {
//           B_idx++;
//         } else {
//           C->elems[C->count] = A.elems[A_idx];
//           A_idx++;
//           B_idx++;
//           C->count++;
//         }
//       }
//     }
//   }

//   return C;
// }
SET *intersectionSorted(SET A, SET B){
  SET *C = (SET*)calloc(sizeof(SET),1);
  if (C != NULL){
    C->count = 0;
    C->elems = (int*)malloc(sizeof(int)*MAX);
    if (C->elems != NULL){
      int A_INDEX = 0;
      int B_INDEX = 0;
      while (A_INDEX < A.count || B_INDEX < B.count){
        if (A.elems[A_INDEX] < B.elems[B_INDEX]){
          A_INDEX++;
        } else if (B.elems[B_INDEX] < A.elems[A_INDEX]){
          B_INDEX++;
        } else {
          C->elems[C->count] = A.elems[A_INDEX];
          A_INDEX++;
          B_INDEX++;
          C->count++;
        }
      }
    }
  }
  return C;
}
SET *differenceSorted(SET A, SET B) {
  // 1257
  // 2589
  // 17
  int A_INDEX = 0;
  int B_INDEX = 0;
  SET *C = (SET *)calloc(sizeof(SET), 1);
  if (C != NULL) {
    while (A_INDEX < A.count) {
      // if A < B, place A element to C
      if (A.elems[A_INDEX] < B.elems[B_INDEX]) {
        C->elems[C->count] = A.elems[A_INDEX];
        C->count++;
        A_INDEX++;
        // if B < A, increment B index
      } else if (B.elems[B_INDEX] < A.elems[A_INDEX]) {
        B_INDEX++;
        // if A == B, increment both indexes
      } else {
        A_INDEX++;
        B_INDEX++;
      }
    }
  }
  return C;
}
