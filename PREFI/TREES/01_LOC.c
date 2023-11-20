#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Macros
#define MAX   10
#define ROOT  -1
#define INV   -2

// Datatypes
typedef struct node {
  int elem;
  struct node* link;
} *LIST;

typedef struct tree {
  LIST Header[MAX];
  int root;
} Tree;

typedef int node;
typedef int label;

// Function Prototypes
void initialize(Tree *T);
// initializes the tree so that it can be used for the first time.

void display(Tree T);
// simply display the whole tree.

void children(node n, Tree T);
// given a particular node/subtree, display all of its children.

void insert(node n, int newData, Tree *T);
// inserts a new node in your tree

void makeNull(Tree *T);
// makes all the pointers in your Header NULL so that it won't be pointing to anything

node parent(node n, Tree T);
// return to the calling function the parent of the given node 

node leftmost_child(node n, Tree T);
// return to the calling function the leftmost child of a particular node

node right_sibling(node n, Tree T);
// return to the calling function the right sibling of a particular node

node root(Tree T);
// returns the root of your tree

label Label(node n, Tree T);

int main(){
  Tree Kamunggay;

  initialize(&Kamunggay);

  insert(5, 0, &Kamunggay);
  insert(5, 6, &Kamunggay);
  insert(5, 2, &Kamunggay);

  insert(0, 9, &Kamunggay);

  insert(6, 3, &Kamunggay);
  insert(6, 1, &Kamunggay);

  insert(1, 4, &Kamunggay);
  insert(1, 7, &Kamunggay);

  insert(2, 8, &Kamunggay);

  display(Kamunggay);

  printf("Parent = %d\n", parent(3, Kamunggay));
  printf("Parent = %d\n", parent(6, Kamunggay));

  printf("LC = %d\n", leftmost_child(6, Kamunggay));
  printf("LC = %d\n", leftmost_child(5, Kamunggay));
  printf("LC = %d\n", leftmost_child(0, Kamunggay));
  printf("LC = %d\n", leftmost_child(1, Kamunggay));

  printf("RS = %d\n", right_sibling(6, Kamunggay));
  printf("RS = %d\n", right_sibling(1, Kamunggay));
  printf("RS = %d\n", right_sibling(4, Kamunggay));

  printf("Root = %d\n", root(Kamunggay));

  printf("Label = %d\n", Label(6, Kamunggay));
  printf("Label = %d\n", Label(4, Kamunggay));
}

void initialize(Tree *T){
  int x;

  for (x = 0 ; x < MAX ; x++){
    T->Header[x] = NULL;
  }
  T->root = -1;
  printf("Initialized tree.\n");
}

void display(Tree T){
  LIST trav;
  int node;

  for (node = 0 ; node < MAX ; node++){
    printf("[%d] => ", node);
    for (trav = T.Header[node] ; trav != NULL ; trav = trav->link){
      printf("%d ", trav->elem);
    }
    printf("\n");
  }
  printf("\n");
}

void children(node n, Tree T){
  LIST trav;

  if (n >= 0 && n < MAX){
    printf("Children of %d:\n", n);
    printf("[%d] => ", n);
    for (trav = T.Header[n] ; trav != NULL ; trav = trav->link){
      printf("%d ", trav->elem);
    }
    printf("\n");
  }
}

void insert(node n, int newData, Tree *T){
  // The reason why we have this first condition is so that the node we're going to insert is a valid node. Remember that our ARRAY of Headers only range from 0-9 (total of 10) so those are the only valid indexes/nodes.
  if (n >= 0 && n < MAX){
    LIST *trav;
    LIST newNode;

    newNode = (LIST)malloc(sizeof(struct node));
    
    if (newNode != NULL){
      newNode->elem = newData;
      newNode->link = NULL;
    }

    if (T->root == -1){
      T->Header[n] = newNode;
      T->root = n;
    } else {
      for (trav = &(T->Header[n]) ; *trav != NULL ; trav = &(*trav)->link){}
      *trav = newNode;
    }
    printf("Inserted %d successfully!\n", newData);
  }
}

void makeNull(Tree *T){
  int x;

  for (x = 0 ; x < MAX ; x++){
    T->Header[x] = NULL;
  }
  printf("Tree is now null.\n");
}

node parent(node n, Tree T){
  LIST trav = NULL;
  int x;
  int retval = -1;

  for (x = 0 ; x < MAX && trav == NULL ; x++){
    for (trav = T.Header[x] ; trav != NULL && trav->elem != n ; trav = trav->link){}
  }

  return (trav != NULL) ? x-1 : retval;
}

node leftmost_child(node n, Tree T){
  return T.Header[n] == NULL ? -1 : T.Header[n]->elem;
}

node right_sibling(node n, Tree T){
  LIST trav = NULL;
  LIST temp = NULL;
  int retval = -1;
  int x;

  for (x = 0 ; x < MAX && trav == NULL ; x++){
    for (trav = T.Header[x] ; trav != NULL && trav->elem != n ; trav = trav->link){}
  }
  return (trav->link == NULL) ? retval : trav->link->elem;
}

node root(Tree T){
  return T.root;
}

label Label(node n, Tree T){
  return T.Header[n] == NULL ? -1 : n;
}