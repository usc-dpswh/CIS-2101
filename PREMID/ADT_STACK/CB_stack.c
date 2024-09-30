#include <stdio.h>
#include <stdbool.h>
#define MAX 5

typedef int STACK;

typedef struct {
  int data;
  int link;
} NodeType;

typedef struct node {
  NodeType Nodes[MAX];
  int Avail;
} VHeap;

//* Utility Functions
void  initVHeap     (VHeap *main);
void  display       (VHeap main, STACK top);
void displayV2      (VHeap* main, STACK* top);
int   allocSpace    (VHeap *main);
int   deallocSpace  (VHeap *main, int index);
bool  isEmpty       (VHeap main);
bool  isFull        (VHeap main);

//* Stack Functions
void  initStack     (STACK *top);
void  push          (VHeap *main, STACK *top, int newData);
void  pop           (VHeap *main, STACK *top);
int   top           (VHeap main, STACK top);

int main(){
  VHeap Beagle;
  STACK DogFood;
  initVHeap(&Beagle);
  initStack(&DogFood);

  push(&Beagle, &DogFood, 5);
  push(&Beagle, &DogFood, 4);
  push(&Beagle, &DogFood, 3);
  push(&Beagle, &DogFood, 2);
  push(&Beagle, &DogFood, 1);

  display(Beagle, DogFood);

  pop(&Beagle, &DogFood);

  // display(Beagle, DogFood);
  displayV2(&Beagle, &DogFood);

  printf("top() = %d\n", top(Beagle, DogFood));
}

//* Utility Functions
void  initVHeap     (VHeap *main){
  int x;

  for (x = -1 ; x < MAX ; x++){
    main->Nodes[x+1].link = x;
  }
  main->Avail = MAX-1;
  printf("initVHeap()\n");
}
void  display       (VHeap main, STACK top){
  printf("display()\n");
  if (!isEmpty(main)){
    int x;
    for (x = top ; x != -1 ; x = main.Nodes[x].link){
      printf("     [%d]\n", main.Nodes[x].data);
    }
  } else {
    printf("Nothing to display\n");
  }
}
void displayV2      (VHeap* main, STACK* top){
  if (*top != -1){
    VHeap temp = {{0}, MAX-1};
    int tempHead = -1;
    while (*top != -1){
      int newNode = temp.Avail;
      if (newNode != -1){
        temp.Nodes[newNode].data = main->Nodes[*top].data;
        temp.Nodes[newNode].link = tempHead;
        tempHead = newNode;
      }

      printf("[%d]\n", temp.Nodes[newNode].data);
      
      int delete = *top;
      if (delete >= 0 && delete < MAX){
        *top = main->Nodes[delete].link;
        main->Nodes[delete].link = main->Avail;
        main->Avail = delete;
      }
    }
  }
}
int   allocSpace    (VHeap *main){
  int retVal = main->Avail;
  if (retVal != -1) main->Avail = main->Nodes[retVal].link;
  return retVal;
}
int   deallocSpace  (VHeap *main, int index){
  if (index >= 0 && index < MAX){
    main->Nodes[index].link = main->Avail;
    main->Avail = index;
  }
}
bool  isEmpty       (VHeap main){
  return main.Avail == MAX-1;
}
bool  isFull        (VHeap main){
  return main.Avail == -1;
}

//* Stack Functions
void  initStack     (STACK *top){
  *top = -1;
  printf("initStack()\n");
}
void  push          (VHeap *main, STACK *top, int newData){
  if (!isFull(*main)){
    int newNode = allocSpace(main);
    if (newNode != -1){
      main->Nodes[newNode].data = newData;
      main->Nodes[newNode].link = *top;
      *top = newNode;
      printf("%5cpush() successful\n");
    }
  } else {
    printf("No space.\n");
  }
}
void  pop           (VHeap *main, STACK *top){
  int temp;
  if (!isEmpty(*main)){
    temp = *top;
    *top = main->Nodes[*top].link;
    deallocSpace(main, temp);
    printf("%5cpop() successful\n");
  } else {
    printf("No items to pop.\n");
  }
} 
int   top           (VHeap main, STACK top){
  return main.Nodes[top].data;
}