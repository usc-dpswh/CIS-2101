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

  enqueue(&jolibee, 10);
  enqueue(&jolibee, 15);

  display(jolibee);



  // isEmpty(&jolibee);

  // dequeue(&jolibee);

  // display(jolibee);

  // enqueue(&jolibee, 10);
  // enqueue(&jolibee, 20);

  // peek(&jolibee);

  // display(jolibee);

  // isFull(&jolibee);

  // enqueue(&jolibee, 30);
  // enqueue(&jolibee, 40);
  // enqueue(&jolibee, 50);

  // display(jolibee);

  // isFull(&jolibee);

  // dequeue(&jolibee);
  // display(jolibee);
  // dequeue(&jolibee);
  // display(jolibee);
  // dequeue(&jolibee);
  // display(jolibee);
  // dequeue(&jolibee);
  // display(jolibee);
  // dequeue(&jolibee);
  // display(jolibee);

  // isEmpty(&jolibee);
}

QUEUE init(){
  QUEUE temp;

  temp.front = -1;
  temp.rear = -1;

  return temp;
}

void enqueue(QUEUE *main, int newData){

  // If there's no element yet
  if (main->front == -1 && main->rear == -1){
    main->front++;
    main->rear = main->front;
    main->queue[main->front] = newData;

  // If there is at least one element and there's still space
  } else if (main->rear < MAX-1){

    main->rear++;
    main->queue[main->rear] = newData;
    
  } else {
    printf("Stack overflow.\n");
  }
}

void display(QUEUE main){
  for (; main.front <= main.rear ; main.front++) { 
    printf("[%d]", main.queue[main.front]);
  } 
  printf("\n");
}