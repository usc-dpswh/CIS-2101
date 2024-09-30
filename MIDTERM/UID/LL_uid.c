#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
  int data;
  struct node* link;
} *SET;

SET UnionSorted(SET A, SET B);
void insertLast(SET* A, int newData);
void displaySet(SET A);

int main(){
  SET A = NULL;
  insertLast(&A,1);
  insertLast(&A,3);
  insertLast(&A,5);
  insertLast(&A,6);

  SET B = NULL;
  insertLast(&B,1);
  insertLast(&B,2);
  insertLast(&B,3);
  insertLast(&B,4);
  insertLast(&B,7);

  // A = {1,3,5,6}
  // B = {1,2,3,4,7}

  SET C = UnionSorted(A,B);
  displaySet(C);
}

SET UnionSorted(SET A, SET B){
  SET C = NULL;
  SET* Cptr = &C;
  while (A != NULL || B != NULL){
    SET newNode = (SET)malloc(sizeof(struct node));
    if (newNode != NULL){
      if (A == NULL && B != NULL){
        newNode->data = B->data;
        newNode->link = NULL;
        *Cptr = newNode;
        Cptr = &newNode->link;

        B = B->link;
      } else if (B == NULL && A != NULL){
        newNode->data = A->data;
        newNode->link = *Cptr;
        *Cptr = newNode;
        Cptr = &newNode->link;

        A = A->link;
      } else if (A->data < B->data){
        newNode->data = A->data;
        newNode->link = *Cptr;
        *Cptr = newNode;
        Cptr = &newNode->link;

        A = A->link;
      } else if (B->data < A->data){
        newNode->data = B->data;
        newNode->link = *Cptr;
        *Cptr = newNode;
        Cptr = &newNode->link;

        B = B->link;
      } else {
        newNode->data = A->data;
        *Cptr = newNode;
        Cptr = &newNode->link;

        A = A->link;
        B = B->link;
      }
    }
  }
  return C;
}


void insertLast(SET* A, int newData){
  SET* trav;
  for (trav = A ; *trav != NULL ; trav = &(*trav)->link){};
  SET newNode = (SET)malloc(sizeof(struct node));
  if (newNode != NULL){
    newNode->data = newData;
    newNode->link = NULL;
    *trav = newNode;
  }
}

void displaySet(SET A){
  SET trav;
  for (trav = A ; trav != NULL ; trav = trav->link){
    printf("[%d]->", trav->data);
  }
}

