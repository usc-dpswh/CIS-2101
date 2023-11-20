#include <stdio.h>
#include <stdlib.h>

#define MAX 5

// Binary Tree
typedef struct bt {
  int LC;
  int RC;
} BTree[MAX];

typedef struct node {
  int elem;
  struct node* LC;
  struct node* RC;
} NodeType;

typedef struct bst {
  int elem;
  struct bst* LC;
  struct bst* RC;
} *BSTree;

typedef int node;

int Member(node n, BSTree main){
  BSTree trav;
  trav = main;

  if (trav == NULL) {
    printf("No existing tree.\n");
  } else {
    while (trav != NULL && trav->elem != n){
      trav = (n < trav->elem) ? trav->LC : trav->RC;
    }
  }

  return (trav != NULL) ? 1 : 0;
}
int Insert(node n, BSTree *main){
  
}

int main(){
  BSTree Kamunggay;

  Kamunggay = NULL;

  Member(5, Kamunggay);
}