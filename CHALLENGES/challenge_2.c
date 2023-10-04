//  AUTHOR    :     LANUTAN, ACHILLE -- 22103514
//  DATE      :     10/05/2023
//  TIME      :     3:03

// INSTRUCTIONS //
// SET A and B are circular arrays (QUEUE)
// Perform set difference (sorted) with these two circular arrays 
// and put the result inside a new array (SET C)
// Return SET C to main()
// Display SET ELEMENTS
// Display BIT REPRESENTATION of set elements (bit vector)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 8

// Bit vector declaration
typedef char SET[MAX];

typedef struct node {
  int elem[MAX];
  int front;
  int rear;
} QUEUE;

// QUEUE functions
void initQueue(QUEUE *main);
bool isEmpty(QUEUE main);
bool isFull(QUEUE main);
void enqueue(QUEUE *main, char newData);
void dequeue(QUEUE *main);
void displayQueue(QUEUE main);


// SET functions
void initSet(SET A);
SET *differenceSorted(QUEUE A, QUEUE B);
void insertElem(SET A, char newData);
void displaySet(SET main);
void displayBits(SET main);

int main(){
  QUEUE A;
  QUEUE B;
  SET *C;

  initQueue(&A);
  initQueue(&B);

  enqueue(&A, 1);
  enqueue(&A, 2);
  enqueue(&A, 5);
  enqueue(&A, 7);

  enqueue(&B, 1);
  enqueue(&B, 3);
  enqueue(&B, 4);
  enqueue(&B, 7);

  printf("(A - B)\n\n");

  printf("SET A = ");
  displayQueue(A);
  printf("SET B = ");
  displayQueue(B);

  C = differenceSorted(A, B);

  printf("SET C = ");
  displaySet(*C);
  printf("Bit representation = ");
  displayBits(*C);

  // Output:
  // SET A = { 1 2 5 7 }
  // SET B = { 1 3 4 7 }
  // SET C = { 2 5 }        7 6 5 4 3 2 1 0 
  // Bit representation = { 0 0 1 0 0 1 0 0 }
}

void initQueue(QUEUE *main){
  main->front = 3;
  main->rear = 2;
}

bool isEmpty(QUEUE main){
  return (main.rear + 1) % MAX == main.front;
}
bool isFull(QUEUE main){
  return (main.rear + 2) % MAX == main.front;
}
void enqueue(QUEUE *main, char newData){
  if (!isFull(*main)){
    // We increment our rear by 1
    main->rear = (main->rear + 1) % MAX;
    // After incrementing, we add our element
    main->elem[main->rear] = newData;
  } else {
    printf("Enqueue() not allowed. Queue full.\n");
  }
}
void dequeue(QUEUE *main){
  if (!isEmpty(*main)){
    main->front = (main->front + 1) % MAX;
  } else {
    printf("Dequeue() is not allowed. Queue empty.\n");
  }
}
void displayQueue(QUEUE main){
  int A;

  printf("{ ");
  for (A = main.front ; A != (main.rear + 1) % MAX ; A = (A + 1) % MAX){
    printf("%d ", main.elem[A]);
  }
  printf("}\n");
}

void initSet(SET A){
  int x;

  for (x = 0 ; x < MAX ; x++){
    A[x] = -1;
  }
}

SET *differenceSorted(QUEUE A, QUEUE B){
  int a = A.front;
  int b = B.front;
  int count = 0;

  SET *C = (SET*)malloc(sizeof(SET));
  
  initSet(*C);

  while (A.front != A.rear && B.front != B.rear){
    if (A.elem[A.front] < B.elem[B.front]){
      
      // (*C)[count] = 1;
      insertElem(*C, A.elem[A.front]);
      A.front = (A.front + 1) % MAX;
      count++;

    } else if (B.elem[B.front] < A.elem[A.front]){

      // (*C)[count] = 1;
      insertElem(*C, A.elem[A.front]);
      B.front = (B.front + 1) % MAX;
      count++;

    } else {
      A.front = (A.front + 1) % MAX;
      B.front = (B.front + 1) % MAX;
    }
  } 
  return C;
}

void insertElem(SET A, char newData){
  if (newData < MAX){
    A[newData] = 1;
  }
}

void displaySet(SET main){
  int x;
  
  printf("{ ");
  for (x = 0 ; x < MAX ; x++){
    if (main[x] == 1){
      printf("%d ", x);
    }
  }
  printf("}\n");
}

void displayBits(SET main){
  int x;

  // printf("{ ");
  // for (x = 0 ; x < MAX ; x++){
  //   if (main[x] == 1){
  //     printf("%d ", x);
  //   } else {
  //     printf("0 ");
  //   }
  // }
  // printf("}\n");
  printf("{ ");
  for (x = 0 ; x < MAX ; x++){
    printf("%d ", main[x] == 1 ? 1 : 0);
  }
  printf("}\n");
}