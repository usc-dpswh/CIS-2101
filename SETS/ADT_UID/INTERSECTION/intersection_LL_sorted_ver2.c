#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node* link;
} *SET;

void initSet(SET *main);
SET setUnionSorted(SET *A, SET *B);
SET intersectionSorted(SET A, SET B);
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
  A->link->link->data = 3;

  A->link->link->link = (SET)malloc(sizeof(struct node));
  A->link->link->link->data = 5;
  A->link->link->link->link = NULL;
  
  B = (SET)malloc(sizeof(struct node));
  B->data = 2;

  B->link = (SET)malloc(sizeof(struct node));
  B->link->data = 4;
  // B->link->link = NULL;

  B->link->link = (SET)malloc(sizeof(struct node));
  B->link->link->data = 5;

  B->link->link->link = (SET)malloc(sizeof(struct node));
  B->link->link->link->data = 6;
  B->link->link->link->link = NULL;

  C = intersectionSorted(A, B);

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

SET intersectionSorted(SET A, SET B){
  SET C = NULL;
  SET *Cptr;
  Cptr = &C;

  while (A != NULL && B != NULL){

    if (A->data < B->data){
      A = A->link;

    } else if (B->data < A->data){
      B = B->link;

    } else {
      SET newNode = (SET)malloc(sizeof(struct node));

      if (newNode != NULL){
        newNode->data = A->data;
        newNode->link = NULL;

        *Cptr = newNode;
        Cptr = &(*Cptr)->link;
        
        A = A->link;
        B = B->link;
      }
      
    }
  }
  return C;
}

void displaySet(SET main){
  while (main != NULL){
    printf("%d => ", main->data);
    
    main = main->link;
  }
  printf("NULL\n");
}