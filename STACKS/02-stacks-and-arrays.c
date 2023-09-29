#include <stdio.h>
#include <stdlib.h>
#define SIZE 5

// Static memory allocation for our stack with array
int stack[SIZE];
int top = -1;

void push(int main[], int newData);
void pop();
void peek();
void display();

int main(){

  push(stack, 1);
  display();

  push(stack, 2);
  display();

  push(stack, 3);
  display();

  push(stack, 4);
  display();

  push(stack, 5);
  display();

  pop();

  display();


}

void push(int main[], int newData){

  // Check if stack is full
  if (top == SIZE - 1){
    printf("Stack overflow.");
  } else {
    printf("push(%d)\n", newData);
    top++;
    main[top] = newData;
  }
}

void pop(){
  int item;

  if (top == -1){
    printf("Stack underflow.");
  } else {
    printf("pop(%d)\n", stack[top]);
    item = stack[top];
    top--;
    // printf("%d", item);
  }
}

void peek(){
  if (top == -1){
    printf("Stack is empty.");
  } else {
    printf("%d", stack[top]);
  }
}

void display(){
  int i = top;
  printf("display()\n");

  for (; i >= 0 ; i--){
    printf("[%d]\n", stack[i]);
  }
  printf("\n");
}
