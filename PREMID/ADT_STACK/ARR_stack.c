#include <stdio.h>
#include <stdbool.h>
#define MAX 5

typedef struct node {
  int elems[MAX];
  int top;
} STACK;

//* Utility Functions
void initStack  (STACK *main);
void display    (STACK main);
void displayV2  (STACK* main);
bool isEmpty    (STACK main);
bool isFull     (STACK main);

//* Main Functions
int top         (STACK main);
void pop        (STACK *main);
void push       (STACK *main, int newData);

int main(){
  STACK dishes;
  initStack(&dishes);

  push(&dishes, 1);
  push(&dishes, 2);
  push(&dishes, 3);
  push(&dishes, 4);
  push(&dishes, 5);

  printf("isEmpty() = %d\n", isEmpty(dishes));
  printf("isFull() = %d\n", isFull(dishes));
  printf("top() = %d\n", top(dishes));

  // display(dishes);
  displayV2(&dishes);
  display(dishes);
}

// Utility Functions
void initStack  (STACK *main){
  main->top = -1;
  printf("initStack() success\n");
}
void display    (STACK main){
  if (main.top != -1){
    STACK temp; 
    initStack(&temp);

    while (main.top != -1){
      // 1) display main.elems[main.top]
      printf("[%d]\n", top(main));
      // 2) increment temp.top++
      temp.top++;
      // 3) return the top element of main into temp.elems[temp.top]
      temp.elems[temp.top] = top(main);
      // 4) pop the top element of main
      pop(&main);
    }  
    printf("display() successful\n");
  } else {
    printf("Cannot display an empty stack.\n");
  }
}
// displayV2() contains parameter pass-by-address so we need to handle using the stack from our main()
void displayV2    (STACK* main){
  STACK temp = {{0}, -1};
  int x;
  // Loop to put everything from main() stack to temp stack
  for (x = 0 ; main->top != -1 ; x++){
    push(&temp, top(*main));
    printf("[%d]\n", temp.elems[temp.top]);
    pop(main);
  }
  // Loop again to put all elements in temp stack to main() stack
  for (x = 0 ; temp.top != -1 ; x++){
    push(main, top(temp));
    pop(&temp);
  }
  printf("displayV2() successful\n");
}
bool isEmpty    (STACK main){
  return main.top == -1;
}
bool isFull     (STACK main){
  return main.top == MAX-1;
}

// Main Functions
int top         (STACK main){
  return main.elems[main.top];
}
void pop        (STACK *main){
  if (!isEmpty(*main)){
    main->top--;
  }
}
void push       (STACK *main, int newData){
  if (!isFull(*main)){
    main->top++;
    main->elems[main->top] = newData;
    // printf("push(%d) success\n", newData);
  } else {
    printf("Stack overflow\n");
  }
}