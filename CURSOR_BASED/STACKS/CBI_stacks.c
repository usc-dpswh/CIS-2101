#include <stdio.h>
#include <stdlib.h>
#define MAX 5

typedef int STACK;

typedef struct {
  int data;
  int link;
} NodeType;

typedef struct node {
  NodeType Nodes[MAX];
  int Avail;
} VirtualHeap;

void initVH(VirtualHeap *main, STACK *top);
void display(VirtualHeap mainVH, STACK top);
int allocSpace(VirtualHeap *main);
void deallocSpace(VirtualHeap *main, int index);

// Stack Operations

// Equivalent to insert first in Linked List
void push(VirtualHeap *main, STACK *top, int newData);

// Pop the node at the top variable
void pop(VirtualHeap *main, STACK *top);

// Returns the element at the top of the stack
void peek(VirtualHeap main, STACK top);

void isEmpty(STACK top);


int main(){
  VirtualHeap spongebob;
  STACK top;

  initVH(&spongebob, &top);

  push(&spongebob, &top, 5);
  push(&spongebob, &top, 10);
  push(&spongebob, &top, 15);
  push(&spongebob, &top, 20);

  display(spongebob, top);

  pop(&spongebob, &top);

  display(spongebob, top);

  peek(spongebob, top);

  pop(&spongebob, &top);

  display(spongebob, top);


}

void initVH(VirtualHeap *main, STACK *top){
  int x;

  for (x = -1 ; x < MAX ; x++){
    main->Nodes[x].data = 0;
    main->Nodes[x+1].link = x;
  }

  main->Avail = MAX-1;
  *top = -1;

  printf("Successfully initialized virtual heap.\n\n");
}

void display(VirtualHeap mainVH, STACK top){

  printf("\ndisplay()\n");
  for(; top != -1 ; top = mainVH.Nodes[top].link){
    printf("%d -> ", mainVH.Nodes[top].data);
  }
  printf("-1\n");

}

int allocSpace(VirtualHeap *main){
  int retVal = main->Avail;

  if (retVal > -1){
    main->Avail = main->Nodes[retVal].link;
    return retVal;
  }
}

void deallocSpace(VirtualHeap *main, int index){
  if (index >= 0 && index < MAX){
    main->Nodes[index].link = main->Avail;
    main->Avail = index;
    printf("Successfully deallocated space from index %d!\n", index);
  }
}

void push(VirtualHeap *main, STACK *top, int newData){
  int newNode = allocSpace(main);
  
  if (newNode != -1){
    main->Nodes[newNode].data = newData;
    main->Nodes[newNode].link = *top;
    *top = newNode;
    printf("push(%d)\n", newData);
  }
}

void pop(VirtualHeap *main, STACK *top){
  STACK temp;

  printf("pop(%d)\n", main->Nodes[*top].data);
  if (*top == -1){
    printf("Stack underflow.\n");
  } else {
    temp = *top;
    *top = main->Nodes[*top].link;
    deallocSpace(main, temp);
  }
}

void peek(VirtualHeap main, STACK top){
  printf("TOP -> [%d]\n", main.Nodes[top].data);
}

void isEmpty(STACK top){
  if (top == -1){
    printf("Stack underflow.\n");
  } else {
    printf("Stack is not empty.\n");
  }
}