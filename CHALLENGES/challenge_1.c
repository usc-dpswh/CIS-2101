// USC is working on a database that concerns with Student Records. Technical staff
// are thinking of implementing the student record with a Cursor-Based Implementation.
// However, deleted students are stored in a separate data structure Linked int. Make
// the function that returns the deleted studrec and make a linked int out of the 
// deleted studrecs.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5

typedef struct {
  char fName[25];
  char lName[25];
  char MI;
} Personal;

typedef struct {
  int id;
  char course[25];
  Personal name;
} StudentInfo, *ptr_StudentInfo;

typedef struct node {
  StudentInfo USC;
  int link;
  struct node* next;
} NodeType, *ptr_NodeType;

typedef struct {
  NodeType Nodes[MAX];
  int Avail;
} VirtualHeap;

void initVH(VirtualHeap *main, int *head);
void display(VirtualHeap mainVH, int head);
int allocSpace(VirtualHeap *main);
void deallocSpace(VirtualHeap *main, int index);
void insertFirstVH(int *head, VirtualHeap *mainVH, int newData);
int deleteElem(int *head, VirtualHeap *mainVH, int delete);

void LL_insertFirst(ptr_NodeType *main, int deleted);
void LL_display(ptr_NodeType main);

int main() {
  VirtualHeap TC;
  int head = 2;
  TC.Avail = 1;

  // initVH(&TC, &head);

  TC.Nodes[4].USC.id = 22103514;
  strcpy(TC.Nodes[4].USC.course, "BSIT");
  strcpy(TC.Nodes[4].USC.name.fName, "Achille");
  strcpy(TC.Nodes[4].USC.name.lName, "Lanutan");
  TC.Nodes[4].USC.name.MI = 'M';
  TC.Nodes[4].link = -1;

  TC.Nodes[3].USC.id = 22105648;
  strcpy(TC.Nodes[3].USC.course, "BSCS");
  strcpy(TC.Nodes[3].USC.name.fName, "Xander");
  strcpy(TC.Nodes[3].USC.name.lName, "Labide");
  TC.Nodes[3].USC.name.MI = 'J';
  TC.Nodes[3].link = 4;

  TC.Nodes[2].USC.id = 22104487;
  strcpy(TC.Nodes[2].USC.course, "BSCOMM");
  strcpy(TC.Nodes[2].USC.name.fName, "Leonardo");
  strcpy(TC.Nodes[2].USC.name.lName, "Dicaprio");
  TC.Nodes[2].USC.name.MI = 'A';
  TC.Nodes[2].link = 3;

  TC.Nodes[1].link = 0;
  TC.Nodes[0].link = -1;


  insertFirstVH(&head, &TC, 22101111);
  insertFirstVH(&head, &TC, 22102222);

  printf("Cursor-Based Students\n");

  display(TC, head);

  ptr_NodeType DELETED = NULL;

  printf("\ndeleteElem(22102222)\n");
  int deletedStudent = deleteElem(&head, &TC, 22102222);

  LL_insertFirst(&DELETED, deletedStudent);

  // printf("%d", deletedStudent);

  // display(TC, head);
  
  printf("\nDeleted Students [Linked List]\n");
  LL_display(DELETED);
}


void initVH(VirtualHeap *main, int *head){
  int x;

  for (x = -1 ; x < MAX-1 ; x++){
    main->Nodes[x+1].USC.id = 0;
    main->Nodes[x+1].link = x;
  }
  main->Avail = MAX-1;
  *head = -1;
}

void display(VirtualHeap mainVH, int head){
  int trav;
  for (trav = head ; trav != -1 ; trav = mainVH.Nodes[trav].link){
    printf("%-10d-\t%s %s\n",
      mainVH.Nodes[trav].USC.id,
      mainVH.Nodes[trav].USC.name.fName,
      mainVH.Nodes[trav].USC.name.lName
    );
  }
}

int allocSpace(VirtualHeap *main){
  int retVal = main->Avail;

  if (retVal > -1){
    main->Avail = main->Nodes[retVal].link;
    return retVal;
  }
}

void deallocSpace(VirtualHeap *main, int index){
  if (index >= 0 && index < MAX){
    main->Nodes[index].link = main->Avail;
    main->Avail = index;
  }
}

void insertFirstVH(int *head, VirtualHeap *mainVH, int newData){
  if (mainVH->Avail != -1){

    int newNode = allocSpace(mainVH);

    mainVH->Nodes[newNode].USC.id = newData;
    strcpy(mainVH->Nodes[newNode].USC.course, "XXXXX");
    strcpy(mainVH->Nodes[newNode].USC.name.fName, "XXXXX");
    strcpy(mainVH->Nodes[newNode].USC.name.lName, "XXXXX");

    mainVH->Nodes[newNode].link = *head;
    *head = newNode;
  }
}

int deleteElem(int *head, VirtualHeap *mainVH, int id){
  int *trav;
  int temp;

  for (trav = head ; *trav != -1 && mainVH->Nodes[*trav].USC.id != id ; trav = &(mainVH->Nodes[*trav].link)){};

  if (*trav != -1){
    temp = *trav;
    mainVH->Nodes[*trav].link = mainVH->Nodes[temp].link;
    deallocSpace(mainVH, temp);

    temp = mainVH->Nodes[temp].USC.id;
    return temp; 
  }
}

void LL_insertFirst(ptr_NodeType *main, int deleted){
  ptr_NodeType newNode = (ptr_NodeType)malloc(sizeof(struct node));

  if (newNode != NULL){
    newNode->USC.id = deleted;
    newNode->next = *main;
    *main = newNode;
  }
}

void LL_display(ptr_NodeType main){
  for (; main != NULL ; main = main->next){
    printf("%d => ", main->USC.id);
  }
  printf("NULL\n");
}