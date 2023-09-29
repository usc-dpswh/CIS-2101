// AUTHOR   :   LANUTAN, ACHILLE LORENZO - 22103514
// DATE     :   TUESDAY, SEPTEMBER 19, 2023
// DESC     :   This is an Array Implementation of a Stack data structure.
//              Note that instead of our STACK data type being just a STRUCTURE,
//              I am practicing by making my life harder using a POINTER instead. (see line 19)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 5

typedef struct node {
  int data;
  struct node* link;
} *NODE;

typedef struct stack {
  NODE top;
} *STACK;

STACK initStack();
void push(STACK *main, int newData);
void pop(STACK *main);
bool isEmpty(STACK main);
void makeNull(STACK *main);
void displayStack(STACK main);

int main(){
  STACK dishes = initStack();

  push(&dishes, 1);
  push(&dishes, 2);
  push(&dishes, 3);

  displayStack(dishes);

  pop(&dishes);

  displayStack(dishes);

  pop(&dishes);

  displayStack(dishes);

  pop(&dishes);

  displayStack(dishes);

  push(&dishes, 1);
  push(&dishes, 2);
  push(&dishes, 3);

  displayStack(dishes);

  makeNull(&dishes);

  displayStack(dishes);

}

STACK initStack(){
  STACK newStack = (STACK)malloc(sizeof(struct stack));

  if (newStack != NULL){
    newStack->top = NULL;
    printf("Successfully initialized stack.\n");
    return newStack;
  }
}

bool isEmpty(STACK main){
  return main == NULL;
}

void push(STACK *main, int newData){
  NODE newNode = (NODE)malloc(sizeof(struct node));

  if (!isEmpty(*main)){
    newNode->data = newData;
    newNode->link = NULL;
    
    if (isEmpty(*main)){   
      (*main)->top = newNode;
    } else {
      newNode->link = (*main)->top;
      (*main)->top = newNode;
    }
  }
}

void pop(STACK *main){
  NODE temp;

  if ((*main)->top != NULL){
    printf("Successfully popped %d!\n", (*main)->top->data);

    temp = (*main)->top;
    (*main)->top = temp->link;
    free(temp);

  } else {
    printf("Stack underflow.\n");
  }
}

void makeNull(STACK *main){
  NODE temp;
  NODE trav;

  for (trav = (*main)->top ; trav != NULL ; free(temp)){
    temp = trav;
    trav = temp->link;
  }
  (*main)->top = NULL;

  printf("Successfully made stack null.\n");
}

void displayStack(STACK main){
  NODE *trav;
  
  if (main->top != NULL){
    for (trav = &(main->top) ; *trav != NULL ; trav = &(*trav)->link){
      printf("[%d]\n", (*trav)->data);
    }
  } else {
    printf("Stack underflow.\n");
  }
  
}