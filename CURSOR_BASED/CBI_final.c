#include <stdio.h>
#include <stdlib.h>
#define MAX 5

typedef int LIST;

typedef struct {
  int data;
  int link;
} NodeType;

typedef struct node {
  NodeType Nodes[MAX];
  int Avail;
} VirtualHeap;

void initVH(VirtualHeap *main, LIST *head);
void display(VirtualHeap mainVH, LIST head);
void deAlloc(VirtualHeap *main, int index);
int allocSpace(VirtualHeap *main);
void deallocSpace(VirtualHeap *main, int index);
void insertFirstVH(LIST *main, VirtualHeap *mainVH, int newData);
void deleteElem(LIST *main, VirtualHeap *mainVH, int delete);

int main(){
  VirtualHeap spongebob;
  LIST head;

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

void initVH(VirtualHeap *main, LIST *head){
  int x;

  for (x = -1 ; x < MAX ; x++){
    main->Nodes[x].data = 0;
    main->Nodes[x+1].link = x;
  }

  main->Avail = MAX-1;
  *head = -1;

  printf("Successfully initialized virtual heap.\n\n");
}

void display(VirtualHeap mainVH, LIST head){

  printf("\ndisplay()\n");
  for(; head != -1 ; head = mainVH.Nodes[head].link){
    printf("%d -> ", mainVH.Nodes[head].data);
  }
  printf("-1\n");

}

int allocSpace(VirtualHeap *main){
  int retVal = main->Avail;

  if (retVal > -1){
    main->Avail = main->Nodes[retVal].link;
    return retVal;
  }
}

void insertFirstVH(LIST *main, VirtualHeap *mainVH, int newData){
  if (mainVH->Avail != -1){

    int newNode = allocSpace(mainVH);

    if (newNode != -1){
      mainVH->Nodes[newNode].data = newData;
      mainVH->Nodes[newNode].link = *main;
      *main = newNode;

      printf("Successfully inserted first inside VH.\n");
    }
  }
}

void deallocSpace(VirtualHeap *main, int index){
  if (index >= 0 && index < MAX){
    main->Nodes[index].link = main->Avail;
    main->Avail = index;
  }
}

void deleteElem(LIST *main, VirtualHeap *mainVH, int delete){
  LIST *trav;
  LIST temp;

  for (
    trav = main 
    ; *trav != -1 && mainVH->Nodes[*trav].data != delete 
    ; trav = &(mainVH->Nodes[*trav].link)
    ){}

  if (*trav != -1){

    temp = *trav;
    *trav = mainVH->Nodes[temp].link;
    deallocSpace(mainVH, temp);

    printf("Successfully deleted the node with %d.\n", delete);
  }
}

