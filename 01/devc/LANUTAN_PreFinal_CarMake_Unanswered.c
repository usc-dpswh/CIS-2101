#include <stdio.h>
#include <string.h>
#define MAX 6

typedef enum {ASIAN, EU_US} makeType;
typedef enum {FALSE, TRUE}  Boolean;

typedef struct {
  char brand[20];
  char model[20];
  int year;
  makeType carMake;
} CarType;

typedef struct {
  int top;
  CarType stackCars[MAX];
} Stack;

typedef struct {
  int front;
  int rear;
  CarType queueCars[MAX];
} Queue;

typedef struct {
  Stack S;
  Queue Q;
} ComboSQ;

//* Stack Functions
void      initStack     (Stack* S);
void      push          (CarType C, Stack* S);
CarType   pop           (Stack* S);
Boolean   isEmptyStack  (Stack S);
Boolean   isFullStack   (Stack S);

//* Queue Functions
void      initQueue     (Queue* Q);
void      enqueue       (CarType C, Queue* Q);
CarType   dequeue       (Queue* Q);
Boolean   isEmptyQueue  (Queue Q);
Boolean   isFullQueue   (Queue Q);

void displayCarList     (ComboSQ main);

// Given the ADDRESS OF A CAR RECORD and the ADDRESS OF ComboSQ variable, write the code of the function searchCarModel().

// The function will search for a given car in the stack of the given ComboSQ if the car is Asian made, otherwise search the car in the queue. Car is uniquely identified by its model.

// If the given car is found in the ComboSQ, return TRUE otherwise FALSE.
Boolean   searchCarModel(CarType* record, ComboSQ* main);
ComboSQ      populateList  ();

int main(){

  ComboSQ CarList;
  CarType car1 = {"NISSAN","KICKS",2020,ASIAN};
  CarType car2 = {"TOYOTA","VIOS",2020,ASIAN};
  CarType car3 = {"PORSCHE","GT3RS",2020,EU_US};
  CarType car4 = {"VOLVO","TEST",2018,EU_US};

  CarList = populateList();
  displayCarList(CarList);

  // Test the searchCarModel() here by calling it and using cars 1-4 for parameters  as test cases
  
}

//* Stack Functions
void      initStack     (Stack* S){
  S->top = -1;
}
Boolean   isEmptyStack  (Stack S){
  return (S.top == -1) ? TRUE : FALSE;
}
Boolean   isFullStack   (Stack S){
  return (S.top == MAX-1) ? TRUE : FALSE;
}
void      push          (CarType C, Stack* S){
  if (!isFullStack(*S)){
    S->top++;
    S->stackCars[S->top] = C;
  }
}
CarType   pop           (Stack* S){
  if (!isEmptyStack(*S)){
    S->top--;
  } else {
    printf("Cannot pop() an empty stack.\n");
  }
}

//* Queue Functions
void      initQueue     (Queue* Q){
  Q->front  = -1;
  Q->rear   = -1;
}
Boolean   isEmptyQueue  (Queue Q){
  return (Q.front == -1 && Q.rear == -1) ? TRUE : FALSE;
}
Boolean   isFullQueue   (Queue Q){
  return (Q.rear == MAX-1) ? TRUE : FALSE;
}
void      enqueue       (CarType C, Queue* Q){
  if (!isFullQueue(*Q)){
    if (isEmptyQueue(*Q)){
      Q->front++; 
      Q->rear++;
      Q->queueCars[Q->front] = C;
    } else {
      Q->rear++;
      Q->queueCars[Q->rear] = C;
    }
  }
}
CarType   dequeue       (Queue* Q){
  if (!isEmptyQueue(*Q)){
    if (Q->front == Q->rear){
      Q->front = Q->rear = -1;
    } else {
      Q->front++;
    }
  }
}

void displayCarList     (ComboSQ main){
  int x,y;
  printf("\nSTACK List of ASIAN cars...\n");
  printf("%-14s%-10s%-10s\n", "BRAND", "MODEL", "YEAR");
  printf("===============================\n");
  for (x = 0 ; x < main.S.top ; x++){
    printf("%-14s%-10s%-10d\n", 
      main.S.stackCars[x].brand,
      main.S.stackCars[x].model,
      main.S.stackCars[x].year
    );
  }
  printf("\nQUEUE List of EU_US cars...\n");
  printf("%-14s%-10s%-10s\n", "BRAND", "MODEL", "YEAR");
  printf("===============================\n");
  for (y = 0 ; y < main.Q.rear ; y++){
    printf("%-14s%-10s%-10d\n", 
      main.Q.queueCars[y].brand,
      main.Q.queueCars[y].model,
      main.Q.queueCars[y].year
    );
  }
}
//* Write the code for this function
Boolean searchCarModel(CarType* record, ComboSQ* main){}

ComboSQ      populateList  (){
  ComboSQ newList;
  initQueue(&newList.Q);
  initStack(&newList.S);
  CarType carStacks[MAX] = {
    {"TOYOTA","RX7",2000,ASIAN},
    {"NISSAN","KICKS",2022,ASIAN},
    {"NISSAN","GTR",2022,ASIAN},
    {"MONTERO","SPORTS",2022,ASIAN},
    {"HONDA","NSX",2022,ASIAN}
  };
  CarType carQueues[MAX] = {
    {"PAGANI",      "HUAYRA",   2020,EU_US},
    {"LAMBORGHINI", "HURACAN",  2006,EU_US},
    {"FERRARI",     "S2000",    2004,EU_US},
    {"PORSCHE",     "GT3RS",    2009,EU_US},
  };
  int x,y;
  for (x = 0 ; x < MAX ; x++){
    push(carStacks[x], &newList.S);
  }
  for (y = 0 ; y < MAX ; y++){
    enqueue(carQueues[y], &newList.Q);
  }
  // printf("Populated list!\n");
  return newList;
}

