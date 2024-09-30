#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node* link;
} *Node;

typedef struct queue {
  Node front;
  Node rear;
} LIST;

//* Utility Functions
void  initQueue (LIST *main);
bool  isEmpty   (LIST main);
bool  isFull    (LIST main);      // Does not apply to Linked Lists Queue
void  display   (LIST *main);
void  createNode(Node *main, int newData);

//* Main Functions
void  enqueue   (LIST *main, int newData);
void  dequeue   (LIST *main);
int   front     (LIST main);

int main(){
  LIST Dianne;
  initQueue(&Dianne);

  enqueue(&Dianne, 1);
  enqueue(&Dianne, 2);
  enqueue(&Dianne, 3);
  enqueue(&Dianne, 4);

  display(&Dianne);
}

//* Utility Functions
void  initQueue (LIST *main){
  main->front = NULL;
  main->rear  = NULL;
  printf("initQueue()\n");
}
bool  isEmpty   (LIST main){
  return main.front == NULL && main.rear == NULL;
}
bool  isFull    (LIST main);      // Does not apply to Linked Lists Queue
void  display   (LIST *main){
  // In this case, when displaying our queue, we must pass-by-address since it affects our LIST variable in main.
  LIST temp;
  initQueue(&temp);

  printf("display()\n");

  // First loop to enqueue all main queue elements to temp through dequeue
  while (!isEmpty(*main)){
    enqueue(&temp, main->front->data);
    printf("[%d]->", temp.rear->data);
    dequeue(main);
  }
  printf("NULL\n");
  // Second loop is to place back all elements in temp back into main through enqueue
  while (!isEmpty(temp)){
    enqueue(main, temp.front->data);
    dequeue(&temp);
  }
}
void  createNode(Node *main, int newData){
  *main = (Node)malloc(sizeof(struct node));
  if (*main != NULL){
    (*main)->data = newData;
    (*main)->link = NULL;
  }
}

//* Main Functions
void  enqueue   (LIST *main, int newData){
  Node newNode;
  createNode(&newNode, newData);
  if (isEmpty(*main)){
    main->front = newNode;
    main->rear  = newNode;
  } else {
    newNode->link = main->rear;
    main->rear->link = newNode;
    main->rear = newNode;
  }
  // printf("enqueue()\n");
}
void  dequeue   (LIST *main){
  Node temp;
  if (!isEmpty(*main)){
    // First if condition checks if there's only one more node left.
    // If there is one more node, simply delete it and reset the LIST
    if (main->front == main->rear){
      temp = main->front;
      free(temp);
      main->front = NULL;
      main->rear  = NULL;
    } else {
    // Else if there are still more than one node, just keep deleting front element
      temp = main->front;
      main->front = temp->link;
      free(temp);
    }
    // printf("dequeue()\n");
  } else {
    printf("Empty queue.\n");
  }
}
int   front     (LIST main){
  return (!isEmpty(main)) ? main.front->data : -1;
}