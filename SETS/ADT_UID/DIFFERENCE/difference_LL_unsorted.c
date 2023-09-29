#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node* link;
} *SET;

void initSet(SET *main);
SET difference(SET *A, SET *B);
void displaySet(SET main);

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
  A->link->link->link = NULL;

  A->link->link->link = (SET)malloc(sizeof(struct node));
  A->link->link->link->data = 5;

  A->link->link->link->link = (SET)malloc(sizeof(struct node));
  A->link->link->link->link->data = 8;
  A->link->link->link->link->link = NULL;

  B = (SET)malloc(sizeof(struct node));
  B->data = 3;

  B->link = (SET)malloc(sizeof(struct node));
  B->link->data = 4;

  B->link->link = (SET)malloc(sizeof(struct node));
  B->link->link->data = 8;

  B->link->link->link = (SET)malloc(sizeof(struct node));
  B->link->link->link->data = 9;
  B->link->link->link->link = NULL;

  // B->link->link->link->link = (SET)malloc(sizeof(struct node));
  // B->link->link->link->link->data = 7;
  // B->link->link->link->link->link = NULL;

  printf("SET A:\n");
  displaySet(A);

  printf("SET B:\n");
  displaySet(B);

  printf("A - B:\n");
  C = difference(&A, &B);
  displaySet(C);


}

void initSet(SET *main){
  *main = NULL;

  printf("Initialized SET.\n");
}

SET difference(SET *A, SET *B){
  SET *Aptr = A;
  SET *Bptr = B;
  SET *reset = B;
  
  SET *Cptr;
  SET C = NULL;

  for (Cptr = &C ; *Aptr != NULL ; Aptr = &(*Aptr)->link){

    for (Bptr = reset ; *Bptr != NULL && (*Bptr)->data != (*Aptr)->data ; Bptr = &(*Bptr)->link){}

    if (*Bptr == NULL){
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
  printf("}\n\n");
}