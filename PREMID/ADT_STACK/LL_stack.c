#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
  int data;
  struct node* link;
} NODE;

typedef struct stack {
  NODE *top;
} STACK;

//* Utility functions
void initStack  (STACK *main);
void display    (STACK main);
void displayV2  (STACK* main);
void displayV3  (STACK *main);
bool isEmpty    (STACK main);
// bool isFull     (STACK main);    Not applicable to Linked Lists

//* Main Functions
int top         (STACK main);
int pop         (STACK *main);
void push       (STACK *main, int newData);

int main(){
  STACK dishes;
  initStack(&dishes);

  push(&dishes, 1);
  push(&dishes, 2);
  push(&dishes, 3);

  pop(&dishes);

  displayV3(&dishes);
  display(dishes);
}

// Utility functions
void initStack  (STACK *main){
  main->top = NULL;
  printf("initStack() successful\n");
}
void display    (STACK main){
  if (main.top != NULL){
    STACK temp;
    initStack(&temp);

    printf("display()\n");
    while (main.top != NULL){
      push(&temp, top(main));
      printf("[%d]\n", top(temp));
      pop(&main);
    }
  } else {
    printf("Cannot print an empty stack.\n");
  }
}
// pass-by-address
void displayV2  (STACK* main){
  if (main->top != NULL){
    STACK temp = {NULL};
    // Loop to place in temp
    while (main->top != NULL){
      push(&temp, top(*main));
      printf("[%d]\n", temp.top->data);
      pop(main);
    }
    // Loop to place back to *main
    while (temp.top != NULL){
      push(main, top(temp));
      pop(&temp);
    }
    printf("displayV2() successful\n");
  } else {
    printf("Cannot print an empty stack.\n");
  }
}
void displayV3  (STACK *main){
  if (main->top != NULL){
    STACK temp = {NULL};
    while (main->top != NULL){
      NODE* new = (NODE*)malloc(sizeof(struct node));
      if (new != NULL){
        new->data = main->top->data;
        new->link = temp.top;
        temp.top = new;
      }
      printf("[%d]\n", temp.top->data);
      if (main->top != NULL){
        NODE* temp = main->top;
        main->top = temp->link;
        free(temp);
      }
    }
    printf("displayV3() successful\n"); 
  }
}
bool isEmpty    (STACK main){
  return main.top == NULL;
}
// bool isFull     (STACK main)     Not applicable to Linked Lists

// Main functions
int top         (STACK main){
  if (!isEmpty(main)){
    return main.top->data;
  }
}
int pop         (STACK *main){
  // Basically deleteFirst
  NODE *temp;
  int poppedValue;
  if (!isEmpty(*main)){
    poppedValue = main->top->data;
    temp = main->top;
    main->top = temp->link;
    free(temp);
    // printf("pop(%d) successful\n", poppedValue);
  }
  return poppedValue;
}
void push       (STACK *main, int newData){
  // Basically insertFirst
  NODE *newNode = (NODE*)malloc(sizeof(struct node));
  if (newNode != NULL){
    newNode->data = newData;
    newNode->link = main->top;
    main->top = newNode;
    // printf("push(%d) successful\n", newData);
  }
}