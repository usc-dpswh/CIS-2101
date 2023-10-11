#include <stdio.h>
#include <stdlib.h>
#define MAX 5

typedef struct {
  int data;
  int link;
} NodeType;

typedef struct node {
  NodeType Nodes[MAX];
  int Avail;
} VirtualHeap;

void initVH(VirtualHeap *main, int *head);
void display(VirtualHeap main, int head);
void deAlloc(VirtualHeap *main, int index);
int allocSpace(VirtualHeap *main);
void deallocSpace(VirtualHeap *main, int index);
void insertFirstVH(int *head, VirtualHeap *mainVH, int newData);
void deleteElem(int *head, VirtualHeap *mainVH, int delete);

int main(){
  VirtualHeap spongebob;
  int head;

  initVH(&spongebob, &head);
  // populate(&spongebob);

  insertFirstVH(&head ,&spongebob, 5);

  display(spongebob, head);

  insertFirstVH(&head ,&spongebob, 10);
  insertFirstVH(&head ,&spongebob, 15);

  display(spongebob, head);

  deleteElem(&head, &spongebob, 5);

  display(spongebob, head);
}

void initVH(VirtualHeap *main, int *head){
  int x;

  for (x = -1 ; x < MAX-1 ; x++){
    main->Nodes[x].data = 0;
    main->Nodes[x+1].link = x;
  }
  main->Avail = MAX-1;
  *head = -1;
}

int allocSpace(VirtualHeap *main){
  // newNode gets the current main->Avail
  int newNode = main->Avail;

  // if newNode is not -1 or not NULL, 
  // we update our main->Avail to the next available node
  if (newNode > -1){
    main->Avail = main->Nodes[newNode].link;
  }
  return (newNode > -1) ? newNode : -1;
}

void deallocSpace(VirtualHeap *main, int index){
  // if the index to be deAlloc is VALID, perform deAlloc
  if (index >= 0 && index < MAX){
    // perform insert first
    main->Nodes[index].link = main->Avail;
    main->Avail = index;
  }
}

void display(VirtualHeap main, int head){
  for (; head > -1 ; head = main.Nodes[head].link){
    printf("%d => ", main.Nodes[head].data);
  }
  printf("-1\n");
}

void insertFirstVH(int *head, VirtualHeap *mainVH, int newData){

  // Check if there's space
  if (mainVH->Avail != -1){
    // allocSpace
    int newNode = allocSpace(mainVH);

    if (newNode > -1){
      mainVH->Nodes[newNode].data = newData;
      mainVH->Nodes[newNode].link = *head;
      *head = newNode;
    }
  }
}

void deleteElem(int *head, VirtualHeap *mainVH, int delete){
  int *trav;
  int temp;

  if (mainVH->Avail > -1){
    for (trav = head ; *trav != -1 && mainVH->Nodes[*trav].data != delete ; trav = &(mainVH->Nodes[*trav].link)){};

    if (*trav != -1){
      temp = *trav;
      *trav = mainVH->Nodes[temp].link;
      deallocSpace(mainVH, temp);
    }
  }
}



