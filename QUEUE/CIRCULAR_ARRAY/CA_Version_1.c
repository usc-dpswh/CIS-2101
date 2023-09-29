// AUTHOR   :   LANUTAN, ACHILLE LORENZO - 22103514
// DATE     :   MONDAY, SEPTEMBER 18, 2023
// DESC     :   This is a circular array implementation of a list VERSION 1. Meaning, we are not
//              sacrificing one cell/element in order to tell if the list is EMPTY or FULL.

#include <stdio.h>
#include <stdbool.h>
#define MAX 7

typedef struct {
    int elem[MAX];
    int count;
    int front;
    int rear;
} QUEUE;

QUEUE initQueue();
bool isFull(QUEUE main);
bool isEmpty(QUEUE main);
void enqueue(QUEUE *main, int newData);
void dequeue(QUEUE *main);
void displayQueue(QUEUE main);

int main(){
    QUEUE Vikings = initQueue();

    enqueue(&Vikings, 1);
    enqueue(&Vikings, 2);
    enqueue(&Vikings, 3);
    enqueue(&Vikings, 4);
    enqueue(&Vikings, 5);
    enqueue(&Vikings, 6);
    enqueue(&Vikings, 7);
    enqueue(&Vikings, 8);   // Should not be possible since our count is == to MAX at this point

    displayQueue(Vikings);

    dequeue(&Vikings);
    dequeue(&Vikings);
    dequeue(&Vikings);
    dequeue(&Vikings);
    dequeue(&Vikings);
    dequeue(&Vikings);
    dequeue(&Vikings);
    dequeue(&Vikings);      // Should not be possible since by this time, our QUEUE will be EMPTY.
    dequeue(&Vikings);      // Should not be possible since by this time, our QUEUE will be EMPTY.
    
}

QUEUE initQueue(){
    QUEUE newQueue;

    newQueue.rear = 3;
    newQueue.front = 4;
    newQueue.count = 0;

    printf("Successfully initialized queue!\n");
    return newQueue;
}

bool isFull(QUEUE main){
    return main.count == MAX;
}

bool isEmpty(QUEUE main){
    return main.count == 0;  
}

void enqueue(QUEUE *main, int newData){
    bool FULL = isFull(*main);

    if (!FULL){
        main->rear = (main->rear + 1) % MAX;
        main->elem[main->rear] = newData;
        main->count++;
    } else {
        printf("Queue is full. Enqueue is not possible.\n");
    }
}

void dequeue(QUEUE *main){
    bool EMPTY = isEmpty(*main);

    if (!EMPTY){
        main->front = (main->front + 1) % MAX;
        main->count--;
    } else {
        printf("Queue is empty. Dequeue is not possible.\n");
    }
}

void displayQueue(QUEUE main){
    bool EMPTY = isEmpty(main);
    int x;

    if (!EMPTY){
        for (x = main.front ; x != main.rear ; x = (x + 1) % MAX){
            printf("%d ", main.elem[x]);
        }
        printf("%d\n", main.elem[x]);
    } else {
        printf("No queue to display.\n");
    }
}