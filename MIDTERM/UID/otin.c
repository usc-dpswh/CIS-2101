#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct node {
  int arr[MAX];
  int ctr;
} SET;

void displaySet(SET main);

SET *intersection(SET A, SET B);

int main(void) {
  SET A = {{1, 2, 3, 4, 5}, 5};
  SET B = {{3, 4, 5, 6, 7}, 5};
  SET *C = intersection(A, B);

  displaySet(A);
  displaySet(B);
  displaySet(*C);

  return 0;
}

void displaySet(SET main) {
  printf("{");

  for (int x = 0; x < main.ctr; ++x) {
    if (x > 0) {
      printf(", ");
    }

    printf("%d", main.arr[x]);
  }

  printf("}\n");
}

SET *intersection(SET A, SET B) {
  SET *C = (SET *)calloc(sizeof(SET), 1);

  if (!C) {
    exit(EXIT_FAILURE);
  }

  int A_idx = 0, B_idx = 0;

  while (A_idx < A.ctr && B_idx < B.ctr) {
    if (A.arr[A_idx] < B.arr[B_idx]) {
      A_idx++;
    } else if (A.arr[A_idx] > B.arr[B_idx]) {
      B_idx++;
    } else {
      C->arr[C->ctr++] = A.arr[A_idx];
      A_idx++;
      B_idx++;
    }
  }

  return C;
}
