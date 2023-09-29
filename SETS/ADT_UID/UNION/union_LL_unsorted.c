#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node* link;
} *SET;

void initSet(SET *main);
SET setUnionUnsorted(SET *A, SET *B);
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
  A->link->data = 3;

  A->link->link = (SET)malloc(sizeof(struct node));
  A->link->link->data = 5;
  A->link->link->link = NULL;

  // A->link->link->link = (SET)malloc(sizeof(struct node));
  // A->link->link->link->data = 5;

  // A->link->link->link->link = (SET)malloc(sizeof(struct node));
  // A->link->link->link->link->data = 8;
  // A->link->link->link->link->link = NULL;

  B = (SET)malloc(sizeof(struct node));
  B->data = 1;

  B->link = (SET)malloc(sizeof(struct node));
  B->link->data = 3;

  B->link->link = (SET)malloc(sizeof(struct node));
  B->link->link->data = 2;

  B->link->link->link = (SET)malloc(sizeof(struct node));
  B->link->link->link->data = 4;
  B->link->link->link->link = NULL;

  printf("SET A\n");
  displaySet(A);

  printf("SET B\n");
  displaySet(B);
  
  printf("A U B\n");
  C = setUnionUnsorted(&A, &B);
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

SET setUnionUnsorted(SET *A, SET *B){

  SET *Aptr = A;
  SET *Bptr = B;
  SET *Cptr = NULL;
  SET C = NULL;
  SET *trav = NULL;

  // (1) Copy all elements from Set A to Set C
  for (Cptr = &C ; *Aptr != NULL ; Aptr = &(*Aptr)->link){
    SET newNode = (SET)malloc(sizeof(struct node));

    if (newNode != NULL){
      newNode->data = (*Aptr)->data;
      newNode->link = *Cptr;
      *Cptr = newNode;
      Cptr = &(*Cptr)->link;
    }
  }

  // (2) Compare EACH element from Set B to EACH element from Set C
  for ( ; *Bptr != NULL ; Bptr = &(*Bptr)->link){

    for (trav = &C ; *trav != NULL && (*trav)->data != (*Bptr)->data ; trav = &(*trav)->link){}

    SET newNode = (SET)malloc(sizeof(struct node));

    if (newNode != NULL && *trav == NULL){
      newNode->data = (*Bptr)->data;
      newNode->link = *Cptr;
      *Cptr = newNode;
      Cptr = &(*Cptr)->link;
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