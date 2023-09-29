//* Introduction to Queues
// Queues follow the rule FIFO (First in, First out) or LILO
// enqueue(insert), dequeue(delete)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5

typedef struct node {
  int elem;
  struct node* link;
} *LIST;

typedef struct {
  LIST front;
  LIST rear;
} QUEUE;

// initialize the queue
QUEUE init();

LIST createNewNode();

// insert
void enqueue(QUEUE *main, int newData);

// delete
void dequeue(QUEUE *main);

// return element at the front
void peek(QUEUE *main);

// check if queue is currently empty
void isEmpty(QUEUE *main);

// check if queue is already full
void isFull(QUEUE *main);

// display queue
void display(QUEUE main);

int main(){
  QUEUE kfc;

  kfc = init();

  enqueue(&kfc, 5);
  enqueue(&kfc, 10);
  enqueue(&kfc, 15);

  display(kfc);

  dequeue(&kfc);

  display(kfc);

  dequeue(&kfc);

  display(kfc);

  dequeue(&kfc);

  display(kfc);

}

LIST createNewNode(){
  LIST newNode = (LIST)malloc(sizeof(struct node));

  if (newNode != NULL){
    return newNode;
  } else {
    printf("Memory allocation unsuccessful!\n");
  }
}

QUEUE init(){
  QUEUE temp;

  temp.front = NULL;
  temp.rear = NULL;

  printf("Successfully initialized queue linked list!\n");

  return temp;
}

void enqueue(QUEUE *main, int newData){
  LIST newNode = createNewNode();

  newNode->elem = newData;
  newNode->link = NULL;

  if (main->front == NULL && main->rear == NULL){
    printf("enqueue(%d)\n", newData);
    main->rear = main->front = newNode;
  } else {
    printf("enqueue(%d)\n", newData);
    main->rear->link = newNode;
    main->rear = newNode;
  }
}

void dequeue(QUEUE *main){
  LIST temp = NULL;

  if (main->front == NULL && main->rear == NULL){
    printf("**Queue underflow.**\n");
    
  } else if (main->front->link == NULL){
    printf("dequeue(%d)\n", main->front->elem);

    temp = main->front;
    main->front = NULL;
    main->rear = NULL;

  } else {
    printf("dequeue(%d)\n", main->front->elem);

    temp = main->front;
    main->front = main->front->link;
    free(temp);
  }
}

void display(QUEUE main){
  printf("display()\n");

  if(main.front == NULL && main.rear == NULL){
    printf("**Queue underflow**\n");
  }

  for (; main.front != NULL ; main.front = main.front->link){
    printf("%d\t", main.front->elem);
  }

  printf("\n");
}

