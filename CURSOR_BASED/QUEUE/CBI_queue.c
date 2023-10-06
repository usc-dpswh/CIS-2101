#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 5

typedef struct {
  int front;
  int rear;
} QUEUE;

typedef struct {
  struct {
    int elem;
    int link;
  } NodeType[MAX];

  int Avail;
} VirtualHeap;

// Cursor Based Functions
void initVH(VirtualHeap *main, int *head);
void display(VirtualHeap mainVH, QUEUE mainQ);
int allocSpace(VirtualHeap *main);
void deallocSpace(VirtualHeap *main, int index);
void insertFirstVH(int *main, VirtualHeap *mainVH, int newData);
void deleteElem(int *main, VirtualHeap *mainVH, int delete);

// Queue Functions
void initQueue(QUEUE *main);
void enqueue(VirtualHeap *mainVH, QUEUE *mainQ, int new);
void dequeue(VirtualHeap *mainVH, QUEUE *mainQ);
void peek(VirtualHeap *mainVH,QUEUE *mainQ);
bool isEmpty(QUEUE *mainQ);
bool isFull(QUEUE *mainQ);

int main(){
  VirtualHeap Matrix;
  int head;
  QUEUE silogan_ni_gian;

  initVH(&Matrix, &head);
  initQueue(&silogan_ni_gian);

  enqueue(&Matrix, &silogan_ni_gian, 10);
  enqueue(&Matrix, &silogan_ni_gian, 20);
  enqueue(&Matrix, &silogan_ni_gian, 30);
  enqueue(&Matrix, &silogan_ni_gian, 40);
  enqueue(&Matrix, &silogan_ni_gian, 50);
  enqueue(&Matrix, &silogan_ni_gian, 60);
  enqueue(&Matrix, &silogan_ni_gian, 60);

  display(Matrix, silogan_ni_gian);

  dequeue(&Matrix, &silogan_ni_gian);

  display(Matrix, silogan_ni_gian);

  dequeue(&Matrix, &silogan_ni_gian);
  // dequeue(&Matrix, &silogan_ni_gian);
  // dequeue(&Matrix, &silogan_ni_gian);
  // dequeue(&Matrix, &silogan_ni_gian);

  display(Matrix, silogan_ni_gian);

  peek(&Matrix, &silogan_ni_gian);
}

// Cursor-Based
void initVH(VirtualHeap *main, int *head){
  int x;

  for (x = 0 ; x < MAX-1 ; x++){
    main->NodeType[x].elem = 0;
    main->NodeType[x].link = x+1;
  }
  main->NodeType[x].link = -1;
  main->Avail = 0;
  *head = 0;
}
void display(VirtualHeap mainVH, QUEUE mainQ){
  int trav;

  for (trav = mainQ.front ; trav != -1 ; trav = mainVH.NodeType[trav].link){
    printf("%d\t", mainVH.NodeType[trav].elem);
  }
  printf("\n");
}

int allocSpace(VirtualHeap *main){
  int retVal = main->Avail;

  if (retVal != -1){
    main->Avail = main->NodeType[retVal].link;
    return retVal;
  }
}

void deallocSpace(VirtualHeap *main, int index){
  if (index >= 0 && index < MAX){
    main->NodeType[index].link = main->Avail;
    main->Avail = index;
  }
}

void insertFirstVH(int *head, VirtualHeap *mainVH, int newData){
  if (mainVH->Avail != -1){
    int newNode = allocSpace(mainVH);

    mainVH->NodeType[newNode].elem = newData;
    mainVH->NodeType[newNode].link = *head;
    *head = newNode;
  }
}
void deleteElem(int *head, VirtualHeap *mainVH, int delete){
  int *trav;
  int temp;

  for (trav = head ; *trav != -1 && mainVH->NodeType[*trav].elem != delete ; trav = &(mainVH->NodeType[*trav].link)){}

  if (*trav != -1){
    temp = *trav;
    *trav = mainVH->NodeType[temp].link;
    deallocSpace(mainVH, temp);
  }
}

// Queue
void initQueue(QUEUE *main){
  main->front = -1;
  main->rear = -1;
}

void enqueue(VirtualHeap *mainVH, QUEUE *mainQ, int new){
  if (!isFull(mainQ)){
    int newNode = allocSpace(mainVH);
    
    if (mainQ->front == -1 && mainQ->rear == -1){
      mainQ->front++;
      mainQ->rear++;
      mainVH->NodeType[newNode].elem = new;
    } else {
      mainQ->rear++;
      mainVH->NodeType[newNode].elem = new; 
    }
  }
}

void dequeue(VirtualHeap *mainVH, QUEUE *mainQ){
  if (isEmpty(mainQ)){
    printf("Queue underflow.\n");
  } else if (mainQ->front == mainQ->rear){
    mainQ->front = -1;
    mainQ->rear = -1;
  } else {
    mainQ->front++;
  }
}
void peek(VirtualHeap *mainVH,QUEUE *mainQ){
  (mainQ->front != -1) ? (printf("%d", mainVH->NodeType[mainQ->rear].elem)) : (printf("No element.\n"));
}
bool isEmpty(QUEUE *mainQ){
  return mainQ->front == -1 && mainQ->rear == -1;
}
bool isFull(QUEUE *mainQ){
  return mainQ->rear == MAX-1;
}