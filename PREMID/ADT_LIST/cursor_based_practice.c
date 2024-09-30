#include <stdio.h>
#include <stdbool.h>
#define MAX 5

typedef int LIST;

typedef struct {
  int elem;
  int link;
} NodeType;

typedef struct node {
  NodeType Nodes[MAX];
  int avail;
} VirtualHeap;

//* Utility Functions
void initVH         (VirtualHeap *main, LIST *head);
void display        (VirtualHeap mainVH, LIST head);
void deAlloc        (VirtualHeap *main, int index);
int allocSpace      (VirtualHeap *main);
void deallocSpace   (VirtualHeap *main, int index);
bool isMember       (LIST head, VirtualHeap main, int find);

//* Insert
void insertFirst    (LIST *main, VirtualHeap *mainVH, int newData);
void insertLast     (LIST *main, VirtualHeap *mainVH, int newData);
void insertUnique   (LIST *main, VirtualHeap *mainVH, int newData);
void insertSorted   (LIST *main, VirtualHeap *mainVH, int newData);

//* Delete
void deleteFirst     (LIST *main, VirtualHeap *mainVH);
void deleteLast     (LIST *main, VirtualHeap *mainVH);
void deleteAll      (LIST *main, VirtualHeap *mainVH);
void deleteAllOccur (LIST *main, VirtualHeap *mainVH, int delete);
void deleteElem     (LIST *main, VirtualHeap *mainVH, int delete);


int main(){
  VirtualHeap Dianne;
  LIST Achille;
  
  initVH(&Dianne, &Achille);

  // insertFirst(&Achille, &Dianne, 5);
  // insertFirst(&Achille, &Dianne, 1);
  // insertLast(&Achille, &Dianne, 7);
  // insertSorted(&Achille, &Dianne, 6);
  // insertSorted(&Achille, &Dianne, 3);
  // insertSorted(&Achille, &Dianne, 0);
  // // insertUnique(&Achille, &Dianne, 10);
  // // insertUnique(&Achille, &Dianne, 20);

  // printf("isMember(%d) = %d\n", 15, isMember(Achille, Dianne, 15));
  // printf("isMember(%d) = %d\n", 20, isMember(Achille, Dianne, 20));

  // display(Dianne, Achille);

  // deleteFirst(&Achille, &Dianne);
  // deleteLast(&Achille, &Dianne);

  // display(Dianne, Achille);

  // deleteAll(&Achille, &Dianne);
  insertLast(&Achille, &Dianne, 1);
  insertLast(&Achille, &Dianne, 2);
  insertLast(&Achille, &Dianne, 2);
  insertLast(&Achille, &Dianne, 3);
  insertLast(&Achille, &Dianne, 2);

  deleteAllOccur(&Achille, &Dianne, 2);

  display(Dianne, Achille);

}

void initVH         (VirtualHeap *main, LIST *head){
  // 1) Declare your needed variables
  int x;
  // 2) Loop to initialize your VirtualHeap by setting the links from -1 to MAX
  for (x = -1 ; x < MAX-1 ; x++){
    main->Nodes[x+1].link = x;
  }
  // 3) Set avail to MAX-1
  main->avail = MAX-1;
  // 4) Set your head as well to -1 since your list is currently empty.
  // Think of it as a pointer variable that's currently NULL.
  *head = -1;
  printf("Initialized VH.\n");
}
void display        (VirtualHeap mainVH, LIST head){
  LIST trav;
  for (trav = head ; trav != -1 ; trav = mainVH.Nodes[trav].link){
  	printf("[%d] -> ", mainVH.Nodes[trav].elem);
  }
  printf("NULL\n");
}
int allocSpace      (VirtualHeap *main){
  int newNode = main->avail;
  if (newNode != -1){
  	main->avail = main->Nodes[newNode].link;
  }
  return newNode;
}
void deallocSpace   (VirtualHeap *main, int index){
  if (index >= 0 && index < MAX){
  	main->Nodes[index].link = main->avail;
  	main->avail = index;
  }
  
}
bool isMember       (LIST head, VirtualHeap mainVH, int find){
  LIST trav;
  for (trav = head ; trav != -1 && mainVH.Nodes[trav].elem != find ; trav = mainVH.Nodes[trav].link){};
  return trav != -1;
}

// Insert
void insertFirst    (LIST *main, VirtualHeap *mainVH, int newData){
  // When inserting, always check if there is space.
  if (mainVH->avail != -1){
    int newNode = allocSpace(mainVH);
    if (newNode != -1){
      mainVH->Nodes[newNode].elem = newData;
      mainVH->Nodes[newNode].link = *main;
      *main = newNode;
    }
  }
}
void insertLast     (LIST *main, VirtualHeap *mainVH, int newData){
  LIST *trav;
  // When inserting, always check if there is space.
  if (mainVH->avail != -1){
    int newNode = allocSpace(mainVH);
  // Always check if allocSpace is successful
    if (newNode != -1){
      // Don't forget to set the link of your node to null since we are inserting last.
      mainVH->Nodes[newNode].elem = newData;
      mainVH->Nodes[newNode].link = -1;
      // Loop to go to the end of your list using PPN (pointer-pointer-node)
      for (trav = main ; *trav != -1 ; trav = &mainVH->Nodes[*trav].link){};
      // Link the last node to the newNode
      *trav = newNode;
      printf("insertLast() successful.\n");
    }
  }
}
void insertSorted   (LIST *main, VirtualHeap *mainVH, int newData){
  if (mainVH->avail != -1){
  	LIST* trav;
  	for (trav = main ; *trav != -1 && newData > mainVH->Nodes[*trav].elem ; trav = &mainVH->Nodes[*trav].link){};
	LIST newNode = allocSpace(mainVH);
	if (newNode != -1){
		mainVH->Nodes[newNode].elem = newData;
		mainVH->Nodes[newNode].link = *trav;
		*trav = newNode;
		printf("\nInsert sorted successfully.");
	}
  }
}
void insertUnique   (LIST *main, VirtualHeap *mainVH, int newData){
  // Check if member first
  if(!isMember(*main, *mainVH, newData)){
    LIST newNode = allocSpace(mainVH);
    if (newNode != -1){
      insertFirst(main, mainVH, newData);
      printf("insertUnique(%d) successful.\n", newData);
    }
  } else {
    printf("%d is not unique in the list.\n", newData);
  }
}

// Delete
void deleteFirst    (LIST *main, VirtualHeap *mainVH){
  if (*main != -1){
    LIST temp;
    // Let temp point to the first node
    temp = *main;
    // Reroute main and let it point to the next node
    *main = mainVH->Nodes[*main].link;
    printf("deleteFirst() successful.\n");
    // Delete via deallocSpace()
    deallocSpace(mainVH, temp);
  } else {
    printf("No elements to be deleted.\n");
  }
}
void deleteLast     (LIST *main, VirtualHeap *mainVH){
  if (*main != -1){
    LIST *trav;
    LIST temp;

    for (trav = main ; mainVH->Nodes[*trav].link != -1 ; trav = &mainVH->Nodes[*trav].link){};

    temp = *trav;
    *trav = -1;
    deallocSpace(mainVH, temp);
    printf("deleteLast() successful.\n");
  }
}
void deleteAll      (LIST *main, VirtualHeap *mainVH){
  LIST temp, trav;
  for (trav = *main ; mainVH->Nodes[trav].link != -1 ; deallocSpace(mainVH, temp)){
    temp = trav;
    trav = mainVH->Nodes[trav].link;
  }
  *main = -1;
  printf("deleteAll() successful\n");
}
void deleteAllOccur (LIST *main, VirtualHeap *mainVH, int delete){
  LIST *trav;
  LIST temp;
  
  for (trav = main ; *trav != -1 ; ){
  	if (mainVH->Nodes[*trav].elem == delete){
  		temp = *trav;
  		*trav = mainVH->Nodes[*trav].link;
  		deallocSpace(mainVH, temp);
	} else {
		trav = &mainVH->Nodes[*trav].link;
	}
  }
  printf("deleteAllOccur() successful\n");
}
void deleteElem     (LIST *main, VirtualHeap *mainVH, int delete){
  LIST *trav;
  LIST temp;
  for (trav = main ; *trav != -1 && mainVH->Nodes[*trav].elem != delete ; trav = &mainVH->Nodes[*trav].link){};
  temp = *trav;
  *trav = mainVH->Nodes[temp].link;
  deallocSpace(mainVH, temp);
  printf("deleteElem() successful\n");
}

