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

void initVH(VirtualHeap *main);
void display(VirtualHeap main);
void populate(VirtualHeap *main);   // Not used
void deAlloc(VirtualHeap *main, int index);
void insertFirstVH(VirtualHeap *main, int newData);

int main(){
  VirtualHeap spongebob;

  initVH(&spongebob);
  // populate(&spongebob);

  display(spongebob);

  insertFirstVH(&spongebob, 50);
  insertFirstVH(&spongebob, 40);
  insertFirstVH(&spongebob, 30);

  display(spongebob);

  insertFirstVH(&spongebob, 20);

  display(spongebob);

  insertFirstVH(&spongebob, 10);

  display(spongebob);

  insertFirstVH(&spongebob, 5);

  deAlloc(&spongebob, 2);

  display(spongebob);

  deAlloc(&spongebob, 1);

  display(spongebob);

}

void initVH(VirtualHeap *main){
  main->Avail = MAX-1;
  int x;

  for (x = MAX-1 ; x >= 0 ; x--){
    main->Nodes[x].data = 0;
    main->Nodes[x].link = x-1;
  }

  printf("Successfully initialized virtual heap.\n\n");
}

void display(VirtualHeap main){
  int x;

  printf("\ndisplay()\n");
  printf("INDEX\tDATA\tLINK\n");
  for (x = MAX-1 ; x > -1 ; x = main.Nodes[x].link){
    printf("%d\t%d\t%d\n", x ,main.Nodes[x].data, main.Nodes[x].link);
  }
}

void populate(VirtualHeap *main){
  int x;

  for (x = MAX-1 ; x > -1 ; x--){
    main->Nodes[x].data = x+10;
    main->Avail = main->Nodes[x].link;
  }
  // printf("Successfully populated with values.\n");
}

void deAlloc(VirtualHeap *main, int index){
  int temp;

  printf("\ndealloc(%d)\n", index);
  if (index == MAX-1){
    main->Avail = index;
  } else {
    temp = main->Nodes[index].link;
    main->Nodes[index+1].link = temp;
    main->Avail = index;
  }
}

void insertFirstVH(VirtualHeap *main, int newData){
  int x;

  printf("insertFirstVH(%d)\n", newData);
  if (main->Avail != -1){

    // Shift to make space for new element
    for (x = main->Avail ; x < MAX-1 ; x++){
      main->Nodes[x].data = main->Nodes[x+1].data;
    }
    // After shifting to make space, insert newData at 0 index
    main->Nodes[x].data = newData;
    // Since we INSERTED/ADDED, our 'Avail' variable would change 
    main->Avail = main->Nodes[main->Avail].link;

  } else {
    printf("No space for %d\n", newData);
  }
}
