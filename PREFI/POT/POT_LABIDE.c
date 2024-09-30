#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define leftChild 2 * index + 1 
#define rightChild 2* index + 2 
#define parentformula (index -1)/2 

typedef struct{
    int data; 
    int prio; 
}Node;

typedef struct{
    Node *arr; 
    int capacity; 
    int size;
}Queue;

Queue* initPrioQueue(int ); 
void swap(Node*, Node* ); 
void enqueue(Queue *, int , int); 
bool isFull(Queue );
bool isEmpty(Queue );
Node dequeue(Queue *);
void minheapify(Queue *, int );
void printPrioQueue(Queue *);

int main(){
    Queue* Q = initPrioQueue(10);
    enqueue(Q, 12, 4);
    enqueue(Q, 45, 6);
    enqueue(Q, 3, 1);
    enqueue(Q, 6, 5);

    printPrioQueue(Q);
    Node temp = dequeue(Q); 
    printf("Dequeued Node: %d, %d\n", temp.data, temp.prio);

    printPrioQueue(Q);
    return 0;
}

Queue* initPrioQueue(int capacity){
    Queue *Q = (Queue*)malloc(sizeof(Queue));
    Q->arr = (Node*)malloc(sizeof(Node)*capacity);
    Q->capacity = capacity;
    Q->size = 0;
    return Q;
}

void swap(Node *a, Node *b){
    Node temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

bool isFull(Queue Q){
    return Q.size == Q.capacity;
}

bool isEmpty(Queue Q){
    return Q.size == 0; 
}

void enqueue(Queue *Q, int data, int priority){

    if(isFull(*Q)){
        printf("Queue is full\n");
    }
    Q->size++;
    int i = Q->size - 1;
    Q->arr[i].data = data;
    Q->arr[i].prio = priority;
    while(i != 0 && Q->arr[(i -1)/2].prio > Q->arr[i].prio){
        swap(&Q->arr[i], &Q->arr[(i -1)/2]);
        i = (i -1)/2;
    }
}

void minheapify(Queue *Q, int index){
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2* index + 2;
    if(left < Q->size && Q->arr[left].prio < Q->arr[smallest].prio)
        smallest = left;
    if(right < Q->size && Q->arr[right].prio < Q->arr[smallest].prio)
        smallest = right;
    if(smallest != index){
        swap(&Q->arr[smallest], &Q->arr[index]);
        minheapify(Q, smallest);
    }
}

Node dequeue(Queue* Q){
    if(isEmpty(*Q)){
        printf("Queue is empty\n");
        Node nothing = {0,0};
        return nothing;
    }
  Node temp = Q->arr[0];
  Q->arr[0] = Q->arr[Q->size-1];
  Q->size--;
  minheapify(Q, 0);
  return temp;
}

void printPrioQueue(Queue *Q) {
   int i;
   printf("PRIO QUEUE: \n");
   printf("DATA\t\tPRIO\n");
   for (i = 0; i < Q->size; i++) {
       printf("%d\t\t%d\n", Q->arr[i].data, Q->arr[i].prio);
   }
}
