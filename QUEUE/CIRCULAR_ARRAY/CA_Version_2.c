// AUTHOR   :   LANUTAN, ACHILLE LORENZO - 22103514
// DATE     :   MONDAY, SEPTEMBER 18, 2023
// DESC     :   This is a circular array implementation of a list VERSION 2. Meaning, we are
//              sacrificing one cell/element in order to tell if the list is EMPTY or FULL.

#include <stdio.h>
#include <stdbool.h>

#define MAX 8

typedef struct{
    char elem[MAX];
    int rear;
    int front;
} QUEUE;

void initQueue(QUEUE *main);
bool isEmpty(QUEUE main);
bool isFull(QUEUE main);
void enqueue(QUEUE *main, char newData);
void dequeue(QUEUE *main);
void displayQueue(QUEUE main);

int main(){
  QUEUE McDonalds;

  initQueue(&McDonalds);

  enqueue(&McDonalds, 'M');  
  enqueue(&McDonalds, 'C');
  enqueue(&McDonalds, 'D');
  enqueue(&McDonalds, 'O');
  enqueue(&McDonalds, 'N');
  enqueue(&McDonalds, 'A');
  enqueue(&McDonalds, 'L');
  enqueue(&McDonalds, 'D');
  enqueue(&McDonalds, 'S');
  
  // dequeue(&McDonalds);
  // dequeue(&McDonalds);
  // dequeue(&McDonalds);
  // dequeue(&McDonalds);
  // dequeue(&McDonalds);
  // dequeue(&McDonalds);
  // dequeue(&McDonalds);
  // dequeue(&McDonalds);
  // dequeue(&McDonalds);
  // dequeue(&McDonalds);
  // dequeue(&McDonalds);
  
  displayQueue(McDonalds);

}

void initQueue(QUEUE *main){
  // We can choose to initialize our queue anywhere as it is circular
  main->rear = 0;
  main->front = 1;

  printf("Initialized the queue successfully!\n\n");
}

bool isFull(QUEUE main){
  return (main.rear + 2) % MAX == main.front;
}

bool isEmpty(QUEUE main){
  return (main.rear + 1) % MAX == main.front;
}

void enqueue(QUEUE *main, char newData){
  bool FULL = isFull(*main);

  // if not full, proceed to enqueue
  if (!FULL){
    printf("enqueue(%c)\n", newData);

    main->rear = (main->rear + 1) % MAX;
    main->elem[main->rear] = newData;
  } else {
    printf("Enqueue() is not allowed. Queue full.\n");
  }
}

void dequeue(QUEUE *main){
  bool EMPTY = isEmpty(*main);

  // if not empty, proceed to dequeue
  if (!EMPTY){
    printf("\ndequeue(%c)", main->elem[main->front]);

    main->front = (main->front + 1) % MAX;
  } else {
    printf("\nDequeue() is not allowed. Queue is empty.");
  }
}

void displayQueue(QUEUE main){
  int x;
  
  printf("\nCASHIER :: ");
  for (x = main.front ; x != (main.rear + 1) % MAX ; x = (x + 1) % MAX){
    printf("\n%c\t%d", main.elem[x], x);
  }
  printf("\n");
}