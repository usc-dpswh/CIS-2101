#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node* link;
} *SET;

void initSet(SET *main);
SET difference(SET *A, SET *B);
void insertUnique(SET *ptr, int newData);
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
  A->link->data = 3;

  A->link->link = (SET)malloc(sizeof(struct node));
  A->link->link->data = 5;
  A->link->link->link = NULL;

  A->link->link->link = (SET)malloc(sizeof(struct node));
  A->link->link->link->data = 8;
  A->link->link->link->link = NULL;

  B = (SET)malloc(sizeof(struct node));
  B->data = 1;

  B->link = (SET)malloc(sizeof(struct node));
  B->link->data = 4;

  B->link->link = (SET)malloc(sizeof(struct node));
  B->link->link->data = 6;

  B->link->link->link = (SET)malloc(sizeof(struct node));
  B->link->link->link->data = 7;
  B->link->link->link->link = NULL;

  // Set A = {1,2,3,5}
  // Set B = {3,4,8,9}

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

void insertUnique(SET *ptr, int newData){
  SET newNode = (SET)malloc(sizeof(struct node));
  SET *trav;

  for (trav = ptr ; *trav != NULL && (*trav)->data != newData ; trav = &(*trav)->link){}

  if (*trav == NULL){

    newNode->data = newData;
    newNode->link = *trav;
    *trav = newNode;
  }
}

SET difference(SET *A, SET *B){
  SET *Aptr = A;
  SET *Bptr = B;
  SET *Cptr = NULL;
  SET C = NULL;

  for (Cptr = &C ; *Aptr != NULL && *Bptr != NULL ; ){

    if ((*Aptr)->data < (*Bptr)->data) {

      insertUnique(&C, (*Aptr)->data);

      Aptr = &(*Aptr)->link;
      Cptr = &(*Cptr)->link;

    } else if ((*Aptr)->data > (*Bptr)->data) {

      Bptr = &(*Bptr)->link;
      
    } else {
      Aptr = &(*Aptr)->link;
      Bptr = &(*Bptr)->link;
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