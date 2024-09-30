#include <stdio.h>
#include <stdbool.h>
#define MAX 5

typedef struct {
  int data;
  int link;
} NodeType;

typedef struct node {
  NodeType elems[MAX];
  int front;
  int rear;
  int Avail;
  int count;
} QUEUE;

//* Utility Functions
int   allocSpace  (QUEUE *main);
int   deallocSpace(QUEUE *main, int index);
void  initQueue   (QUEUE *main);
bool  isEmpty     (QUEUE main);
bool  isFull      (QUEUE main);
void  display     (QUEUE main);

//* Main Functions
void  enqueue     (QUEUE *main, int newData);
void  dequeue     (QUEUE *main);
int   front       (QUEUE main);   // Alternatively called "peek"

int main(){
  QUEUE IlaoIlao;
  initQueue(&IlaoIlao);

  enqueue(&IlaoIlao, 1);
  enqueue(&IlaoIlao, 2);
  enqueue(&IlaoIlao, 3);
  enqueue(&IlaoIlao, 4);
  enqueue(&IlaoIlao, 5);
  enqueue(&IlaoIlao, 6);

  dequeue(&IlaoIlao);
  dequeue(&IlaoIlao);

  display(IlaoIlao);
}

//* Utility Functions
int   allocSpace  (QUEUE *main){
  int retval = main->Avail;
  if (retval != -1) main->Avail = main->elems[retval].link;
  return retval;
}
int   deallocSpace(QUEUE *main, int index){
  if (index >= 0 && index < MAX){
    main->elems[index].link = main->Avail;
    main->Avail = index;
  }
}
void  initQueue   (QUEUE *main){
  int x;
  for (x = -1 ; x < MAX-1 ; x++){
    main->elems[x+1].link = x; 
  }
  main->Avail = MAX-1;
  main->front = -1;
  main->rear  = -1;
  main->count = 0;
}
bool  isEmpty     (QUEUE main){
  return main.count == 0;
}
bool  isFull      (QUEUE main){
  return main.count == MAX;
}
void  display     (QUEUE main){
  int x;
  for (; !isEmpty(main) ; dequeue(&main)){
    printf("[%d]->", main.elems[main.front].data);
  }
  printf("NULL\n");
}

//* Main Functions
void  enqueue     (QUEUE *main, int newData){
  if (!isFull(*main)){
    int newNode = allocSpace(main);
    if (newNode != -1){
      main->elems[newNode].data = newData;
      if (isEmpty(*main)){
        main->front = newNode;
        main->rear  = newNode;
      } else {
        main->elems[newNode].link     = main->elems[main->rear].link;
        main->elems[main->rear].link  = newNode;
        main->rear                    = newNode;
      }
      main->count++;
    }
  } else {
    printf("Queue full\n");
  }
}
void  dequeue     (QUEUE *main){
  int temp;
  if (!isEmpty(*main)){
    if (main->rear == main->front){
      temp = main->front;
      deallocSpace(main, temp);
      main->front = -1;
      main->rear  = -1;
    } else {
      temp = main->front;
      main->front = main->elems[temp].link;
      deallocSpace(main, temp);
    }
    main->count--;
  }
}
int   front       (QUEUE main){
  return (!isEmpty(main)) ? main.elems[main.front].data : -1;
}   // Alternatively called "peek"