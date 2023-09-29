#include <stdio.h>

#define MAX 10

typedef struct{
    char elem[MAX];
    int rear;
    int head;
} Queue;

void initQueue(Queue *);
void enQueue(Queue *, char);
void deQueue(Queue *);
void showQueue(Queue);

int main(){
    Queue T;
    initQueue(&T);
    enQueue(&T, 'A');
    enQueue(&T, 'B');
    enQueue(&T, 'C');
    enQueue(&T, 'D');

    // showQueue(T);

    // deQueue(&T);
    // showQueue(T);

    // deQueue(&T);
    // deQueue(&T);

    showQueue(T);

    // enQueue(&T, 'A');
    // enQueue(&T, 'B');
    // enQueue(&T, 'C');
}

void initQueue(Queue *Q){
    Q->head = 0;
    Q->rear = -1;
}

void enQueue(Queue *W, char new){
    printf("enqueue()\n");

    // if not full
    if ((W->rear + 2) % MAX != W->head){
        W->rear = (W->rear + 1) % MAX;
        W->elem[W->rear] = new;
    }
}

void deQueue(Queue *E){
    printf("\ndequeue()\n");
    // if not empty
    if ((E->rear + 1) % MAX != E->head){
        E->head = (E->head + 1) % MAX;
    }
}

void showQueue(Queue R){
    int x;
    printf("\nQueue: \n");
    for (x = R.head; x != R.rear; x = (x + 1) % MAX){
        printf("\n%c%d", R.elem[x], x);
    }
}
