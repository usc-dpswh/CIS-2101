// AUTHOR   :   LANUTAN, ACHILLE LORENZO - 22103514
// DATE     :   TUESDAY, SEPTEMBER 19, 2023
// DESC     :   This is an Array Implementation of a Stack data structure.

#include <stdio.h>
#include <stdbool.h>
#define MAX 5

typedef struct {
  int elem[MAX];
  int top;
} STACK;

STACK initStack();
void push(STACK *main, int newData);
void pop(STACK *main);
bool isEmpty(STACK main);
bool isFull(STACK main);
void makeNull(STACK *main);
void displayStack(STACK main);

int main(){
  STACK dishes = initStack();

  // Testing push()
  push(&dishes, 1);
  push(&dishes, 2);
  push(&dishes, 3);
  push(&dishes, 4);
  push(&dishes, 5);

  displayStack(dishes);

  // Testing pop()
  pop(&dishes);
  pop(&dishes);

  displayStack(dishes);

  // Testing pop() until all elements run out
  pop(&dishes);
  pop(&dishes);
  pop(&dishes);
  pop(&dishes);         // Should not be possible

  // Testing makeNull()
  push(&dishes, 1);
  push(&dishes, 2);
  push(&dishes, 3);

  displayStack(dishes);

  makeNull(&dishes);

  displayStack(dishes);
}

STACK initStack(){
  STACK newStack;

  newStack.top = -1;
  printf("Successfully initialized stack.\n");

  return newStack;
}

bool isEmpty(STACK main){
  return main.top == -1;
}

bool isFull(STACK main){
  return main.top == MAX-1;
}

void push(STACK *main, int newData){
  
  // Check if there's space to PUSH an element
  if (!isFull(*main)){
    printf("push(%d)\n", newData);

    main->top++;
    main->elem[main->top] = newData;
  } else {
    printf("Stack overflow.\n");
  }
}

void pop(STACK *main){

  // Check if empty
  if (!isEmpty(*main)){
    printf("pop(%d)\n", main->elem[main->top]);

    main->top--;
  } else {
    printf("Stack underflow.\n");
  }
}

void makeNull(STACK *main){
  int x;

  if (!isEmpty(*main)){
    for (x = main->top ; x != -1 ; x--){
      main->elem[x] = 0;
    }
    main->top = -1;
  } else {
    printf("Stack already null.\n");
  }
}

void displayStack(STACK main){
  int x;

  printf("\ndisplayStack()\n");
  if (!isEmpty(main)){
    for (x = main.top ; x != -1 ; x--){
      printf("[%d]\n", main.elem[x]);
    }
  } else {
    printf("Stack underflow.\n");
  }
}