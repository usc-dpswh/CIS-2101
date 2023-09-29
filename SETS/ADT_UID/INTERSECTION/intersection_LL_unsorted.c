#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node* link;
} *SET;

void initSet(SET *main);
SET setUnionSorted(SET *A, SET *B);
SET intersectionSorted(SET *A, SET* B);
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

  A->link->link->link = (SET)malloc(sizeof(struct node));
  A->link->link->link->data = 2;
  A->link->link->link->link = NULL;
  
  B = (SET)malloc(sizeof(struct node));
  B->data = 2;

  B->link = (SET)malloc(sizeof(struct node));
  B->link->data = 5;
  // B->link->link = NULL;

  B->link->link = (SET)malloc(sizeof(struct node));
  B->link->link->data = 1;

  B->link->link->link = (SET)malloc(sizeof(struct node));
  B->link->link->link->data = 6;
  B->link->link->link->link = NULL;

  printf("SET A:\n");
  displaySet(A);

  printf("SET B:\n");
  displaySet(B);

  printf("A ∩ B:\n");
  C = intersectionSorted(&A, &B);
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

SET intersectionSorted(SET *A, SET *B){
  SET *Aptr = A;
  SET *Bptr = B;
  SET *reset = B;
  SET C = NULL;
  SET *Cptr = NULL;

  for (Cptr = &C ; *Aptr != NULL ; Aptr = &(*Aptr)->link){
    
    for (Bptr = reset ; *Bptr != NULL && (*Bptr)->data != (*Aptr)->data ; Bptr = &(*Bptr)->link){}

    if (*Bptr != NULL){
      SET newNode = (SET)malloc(sizeof(struct node));

      newNode->data = (*Aptr)->data;
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