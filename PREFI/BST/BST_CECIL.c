#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int elem;
    struct node *left;
    struct node *right;
}*nodePtr;

void insert(nodePtr *A, int elem);
void deleteElem(nodePtr *A, int elem);

int main() {
    nodePtr A = NULL;

    insert(&A, 5);
    insert(&A, 7);
    insert(&A, 4);
    insert(&A, 0);
    insert(&A, 2);
    insert(&A, 9);
    deleteElem(&A, 4);

    return 0;
}

void insert(nodePtr *A, int elem) {
    if(*A != NULL && (*A)->elem >= elem) {
        insert(&(*A)->left, elem);
    } else if (*A != NULL && (*A)->elem < elem) {
        insert(&(*A)->right, elem);
    } else {
        nodePtr temp = (nodePtr) malloc(sizeof(struct node));
        if(temp != NULL) {
            temp->elem = elem;
            temp->left = temp->right = NULL;
        *A = temp;
        }
    }
}
void deleteElem(nodePtr *A, int elem) {
  if (*A == NULL) return; 
  if (*A != NULL && (*A)->elem > elem) {
    deleteElem(&(*A)->left, elem);
  } else if (*A != NULL && (*A)->elem < elem) {
    deleteElem(&(*A)->right, elem);
  } else {
    nodePtr temp = *A;
    *A = (*A)->left ? (*A)->left : (*A)->right;
    free(temp);
  }
}