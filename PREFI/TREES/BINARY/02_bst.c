#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Binary Search Tree Datatype definition
typedef struct node {
  int elem;
  struct node* LC;
  struct node* RC;
} *BST;

void Init(BST *main);
void Insert(int newData, BST *main);
bool Member(int findMe, BST main);

// __order 
void Preorder(BST main);
void Inorder(BST main);
void Postorder(BST main);

// Delete
int DeleteMin(BST *main);
int DeleteMax(BST *main);
int Delete(BST *main, int node);

int main(){
  BST Mango;

  Init(&Mango);

  Insert(10, &Mango);
  Insert(5, &Mango);
  Insert(14, &Mango);
  Insert(7, &Mango);
  Insert(12, &Mango);
  Insert(18, &Mango);
  Insert(11, &Mango);
  Insert(15, &Mango);


  printf("Preorder:\n");
  Preorder(Mango);
  printf("\nInorder:\n");
  Inorder(Mango);
  printf("\nPostorder:\n");
  Postorder(Mango);

  // Where 1 = found and 0 = not found
  printf("\nMember %d = %d\n", 5, Member(5, Mango));
  printf("Member %d = %d\n", 15, Member(15, Mango));
  printf("Member %d = %d\n", 20, Member(20, Mango));
  printf("Member %d = %d\n", 10, Member(10, Mango));

  printf("Deleted min = %d\n", DeleteMin(&Mango));
  printf("Deleted max = %d\n", DeleteMax(&Mango));

  Preorder(Mango);
}

void Init(BST *main){
  *main = NULL;
  printf("Initialized BST.\n");
}
void Insert(int newData, BST *main){
  BST *trav;
  BST newNode = NULL;

  for (trav = main ; *trav != NULL ; trav = (newData < (*trav)->elem) ? &(*trav)->LC : &(*trav)->RC){}

  newNode = (BST)malloc(sizeof(struct node));
  if (newNode != NULL){
    newNode->LC = newNode->RC = NULL;
    newNode->elem = newData;
    *trav = newNode;
    printf("Inserted %d successfully.\n", newData);
  }
}
void Preorder(BST main){
  if (main != NULL){
    printf("%d ", main->elem);
    Preorder(main->LC);
    Preorder(main->RC);
  }
}
void Inorder(BST main){
  if (main != NULL){
    Inorder(main->LC);
    printf("%d ", main->elem);
    Inorder(main->RC);
  }
}
void Postorder(BST main){
  if (main != NULL){
    Postorder(main->LC);
    Postorder(main->RC);
    printf("%d ", main->elem);
  }
}
bool Member(int findMe, BST main){
  while (main != NULL && main->elem != findMe){
    main = (findMe < main->elem) ? main->LC : main->RC;
  }
  return (main != NULL) ? 1 : 0;
}
int DeleteMin(BST *main){
  BST *trav;
  int retval;

  trav = main;
  // for (trav = main ; *trav != NULL ; trav = &(*trav)->LC){}
  while ((*trav)->LC != NULL){
    if (*trav != NULL){
      trav = &(*trav)->LC;
    }
  }
  if ((*trav)->LC == NULL){
    BST temp = *trav;
    // *trav = temp->LC;
    retval = temp->elem;
    *trav = (*trav)->RC;
    free(temp);
    printf("Deleted min of BST.\n");
  }
  return retval;
}
int DeleteMax(BST *main){
  BST *trav;
  int retval;

  trav = main;
  // for (trav = main ; *trav != NULL ; trav = &(*trav)->LC){}
  while ((*trav)->RC != NULL){
    if (*trav != NULL){
      trav = &(*trav)->RC;
    }
  }
  if ((*trav)->RC == NULL){
    BST temp = *trav;
    // *trav = temp->LC;
    retval = temp->elem;
    *trav = (*trav)->LC;
    free(temp);
    printf("Deleted max of BST.\n");
  }
  return retval;
}


