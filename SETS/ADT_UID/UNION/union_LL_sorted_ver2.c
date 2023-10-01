#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node* link;
} *SET;

void initSet(SET *main);
SET setUnionSorted(SET A, SET B);
void displaySet(SET main);
void insertLast(SET *ptr, int newData);

int main(){
  SET A;
  SET B;
  SET C;

  initSet(&A);
  initSet(&B);
  initSet(&C);

  A = (SET)malloc(sizeof(struct node));
  A->data = 1;

  A->link = (SET)malloc(sizeof(struct node));
  A->link->data = 2;

  A->link->link = (SET)malloc(sizeof(struct node));
  A->link->link->data = 5;

  A->link->link->link = (SET)malloc(sizeof(struct node));
  A->link->link->link->data = 6;
  A->link->link->link->link = NULL;
  
  B = (SET)malloc(sizeof(struct node));
  B->data = 2;

  B->link = (SET)malloc(sizeof(struct node));
  B->link->data = 3;
  // B->link->link = NULL;

  B->link->link = (SET)malloc(sizeof(struct node));
  B->link->link->data = 4;

  B->link->link->link = (SET)malloc(sizeof(struct node));
  B->link->link->link->data = 7;
  B->link->link->link->link = NULL;

  // B->link->link->link->link = (SET)malloc(sizeof(struct node));
  // B->link->link->link->link->data = 5;
  // B->link->link->link->link->link = NULL;


  printf("SET A:\n");
  displaySet(A);

  printf("SET B:\n");
  displaySet(B);

  printf("A U B:\n");
  C = setUnionSorted(A, B);
  displaySet(C);
}

void initSet(SET *main){
  *main = NULL;

  printf("Initialized SET.\n");
}

void insertLast(SET *ptr, int newData){
  SET newNode = (SET)malloc(sizeof(struct node));

  if (newNode != NULL){
    newNode->data = newData;
    newNode->link = *ptr;
    *ptr = newNode;
  }
}

SET setUnionSorted(SET A, SET B) {
  SET C = NULL;
  SET *Cptr = &C;

  while (A != NULL && B != NULL) {
    SET newNode = (SET)malloc(sizeof(struct node));

    if (newNode != NULL) {
      if (A->data < B->data) {
        newNode->data = A->data;
        newNode->link = NULL;

        *Cptr = newNode;
        Cptr = &(*Cptr)->link;

        A = A->link;
      } else if (B->data < A->data) {
        newNode->data = B->data;
        newNode->link = NULL;

        *Cptr = newNode;
        Cptr = &(*Cptr)->link;

        B = B->link;
      } else {
        newNode->data = A->data;
        newNode->link = NULL;

        *Cptr = newNode;
        Cptr = &(*Cptr)->link;
        
        A = A->link;
        B = B->link;
      }
    }
  }

  // Add remaining elements from A and B if any
  while (A != NULL) {
    SET newNode = (SET)malloc(sizeof(struct node));
    if (newNode != NULL) {
      newNode->data = A->data;
      newNode->link = NULL;
      *Cptr = newNode;
      Cptr = &(*Cptr)->link;
      A = A->link;
    }
  }

  while (B != NULL) {
    SET newNode = (SET)malloc(sizeof(struct node));
    if (newNode != NULL) {
      newNode->data = B->data;
      newNode->link = NULL;
      *Cptr = newNode;
      Cptr = &(*Cptr)->link;
      B = B->link;
    }
  }

  return C;
}

void displaySet(SET main){
  SET *trav;

  printf("{ ");
  for (trav = &main ; *trav != NULL ; trav = &(*trav)->link){
    printf("%d ", (*trav)->data);
  }
  printf("}\n");
}