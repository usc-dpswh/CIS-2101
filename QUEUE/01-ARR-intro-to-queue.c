//* Introduction to Queues
// Queues follow the rule FIFO (First in, First out) or LILO
// enqueue(insert), dequeue(delete)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5

typedef struct node {
  int queue[MAX];
  int front;
  int rear;
} QUEUE;

// initialize the queue
QUEUE init();

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
  QUEUE jolibee;

  jolibee = init();

  enqueue(&jolibee, 5);

  display(jolibee);

  isEmpty(&jolibee);

  dequeue(&jolibee);

  display(jolibee);

  enqueue(&jolibee, 10);
  enqueue(&jolibee, 20);

  peek(&jolibee);

  display(jolibee);

  isFull(&jolibee);

  enqueue(&jolibee, 30);
  enqueue(&jolibee, 40);
  enqueue(&jolibee, 50);

  display(jolibee);

  isFull(&jolibee);

  dequeue(&jolibee);
  display(jolibee);
  dequeue(&jolibee);
  display(jolibee);
  dequeue(&jolibee);
  display(jolibee);
  dequeue(&jolibee);
  display(jolibee);
  dequeue(&jolibee);
  display(jolibee);

  isEmpty(&jolibee);
}

QUEUE init(){
  QUEUE temp;

  temp.front = -1;
  temp.rear = -1;

  return temp;
}

void enqueue(QUEUE *main, int newData){
  printf("enqueue(%d)\n", newData);

  if (main->front == -1 && main->rear == -1){
    main->front++;
    main->rear = main->front;
    main->queue[main->front] = newData;
  } else {
    if (main->rear < MAX-1){
      main->rear++;
      main->queue[main->rear] = newData;
    } else {
      printf("Stack overflow.");
    }
  }
}

void dequeue(QUEUE *main){
  // if there are no elements yet
  if (main->front == -1 && main->rear == -1){
    printf("Queue underflow.\n");

  // if there is exactly ONE element
  } else if (main->front == main->rear) {
    printf("dequeue(%d)\n", main->queue[main->front]);
    main->front = main->rear = -1;

  // if there are more than one element
  } else {
    printf("dequeue(%d)\n", main->queue[main->front]);
    main->front++;
  }
}

void peek(QUEUE *main){
  printf("peak(%d)\n", main->queue[main->front]);
}

void display(QUEUE main){
  for (; main.front <= main.rear ; main.front++){ printf("%d\t", main.queue[main.front]); }
  printf("\n");
}

void isEmpty(QUEUE *main){
  if (main->front == -1 && main->rear == -1){
    printf("isEmpty() => {Queue underflow.}\n");
  } else {
    printf("isEmpty() => {Queue exists.}\n");
  }
}

void isFull(QUEUE *main){
  if (main->rear == MAX-1){
    printf("isFull() => {Queue is full!}\n");
  } else {
    printf("isFull() => {Queue is not yet full.}\n");
  }
  
}

