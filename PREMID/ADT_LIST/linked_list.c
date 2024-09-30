#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
  int elem;
  struct node* link;    //  link is a pointer to a struct node (pointer to itself)
} *LIST;                //  LIST is a pointer to a struct node

//* Initialize
void init_ver1(LIST *main);
LIST init_ver2();

//* Other operations
void insertFirst    (LIST *main, int newData);
void insertLast     (LIST *main, int newData);
void insertAt       (LIST *main, int pos, int newData);
void insertUnique   (LIST *main, int newData);
void insertSorted   (LIST *main, int newData);

void deleteFirst    (LIST *main, int delete);
void deleteLast     (LIST *main, int delete);
void delete         (LIST *main, int delete);
void deleteAll      (LIST *main);
void deleteAllOccur (LIST *main, int delete);
void deleteElem     (LIST *main, int delete);

void edit           (LIST *main, int oldData, int newData);
bool isMember       (LIST *main, int find);

void reverseList    (LIST *main);
void printList      (LIST main);

int main(){
  LIST Dinosaurs;

  init_ver1(&Dinosaurs);
  Dinosaurs = init_ver2();

  // insertFirst   (&Dinosaurs, 5);
  // insertLast    (&Dinosaurs, 10);
  // insertUnique  (&Dinosaurs, 15);
  // insertUnique  (&Dinosaurs, 15);
  // insertAt      (&Dinosaurs, 0, 20);   
  // Output:  [20] -> [15] -> [5] -> [10] -> NULL

  insertLast(&Dinosaurs, 1);
  insertLast(&Dinosaurs, 2);
  insertLast(&Dinosaurs, 3);
  insertLast(&Dinosaurs, 4);

  printList(Dinosaurs);

  // deleteAllOccur(&Dinosaurs, 2);
  reverseList(&Dinosaurs);
  deleteElem(&Dinosaurs, 3);

  // deleteAll(&Dinosaurs);

  printList(Dinosaurs);

  printf("Member %d = %d\n", 1, isMember(&Dinosaurs, 0));
}

//  Initialization
void init_ver1(LIST *main){
  *main = NULL;
}
LIST init_ver2(){
  LIST newList = NULL;
  return newList;
}

//  Insert
void insertFirst    (LIST *main, int newData){
  LIST newNode = NULL;

  newNode = (LIST)malloc(sizeof(struct node));

  //  Never forget to check if malloc() was successful
  if (newNode != NULL){
    newNode->elem = newData;
    newNode->link = *main;
    *main = newNode;
    printf("insertFirst() success.\n");
  }
}
void insertLast     (LIST *main, int newData){
  LIST newNode = NULL;
  LIST *trav;

  newNode = (LIST)malloc(sizeof(struct node));
  if (newNode != NULL){
    newNode->elem = newData;
    newNode->link = NULL;

    // Loop until last node
    //* CORRECTION: trav = main because PPN. 
    for (trav = main ; *trav != NULL ; trav = &(*trav)->link){};
    // At this point, our pointer trav would be pointing to the last node's link.
    // Using dereference, we let it point to the newly allocated node.
    *trav = newNode;
    printf("insertLast() success.\n");
  }
}
void insertAt       (LIST *main, int pos, int newData){
  // There must be existing data (at least one) for this operation to work.
  // [0] -> [1] -> [2]
  // Insert at position 0
  // [0] -> [3] -> [1] -> [2]
  LIST newNode = NULL;
  LIST *trav;
  int x;

  newNode = (LIST)malloc(sizeof(struct node));
  if (newNode != NULL){
    newNode->elem = newData;
    newNode->link = NULL;
  }

  // If no elements
  if (*main == NULL){
    *main = newNode;  
    printf("insertAt() success.\n");
  // If there are elements
  } else {
    LIST temp;
    //* CORRECTION: trav = main because PPN. 
    for (x = 0, trav = main ; *trav != NULL && x != pos ; x++, trav = &(*trav)->link){};
    // 1) Let temp point to what trav is pointing to
    temp = *trav;
    // 2) Let newNode->link point to temp
    newNode->link = temp;
    // 3) Readjust the pointer of the previous node to point to newNode
    *trav = newNode;
    printf("insertAt() success.\n");
  }
}
void insertUnique   (LIST *main, int newData){
  LIST newNode = NULL;
  LIST trav;
  // 1) Use a loop to search over the entire list and check if newData is unique.
  for (trav = *main ; trav != NULL && trav->elem != newData ; trav = trav->link){};
  // 2) If unique, insertFirst.
  if (trav == NULL){
    newNode = (LIST)malloc(sizeof(struct node));
    if (newNode != NULL){
      newNode->elem = newData;
      newNode->link = *main;
      *main = newNode;
      printf("insertUnique() success.\n");
    }
  } else {
    printf("Not unique.\n");
  }
}
void insertSorted   (LIST *main, int newData){
  LIST newNode = NULL;
  LIST *trav;

  // 1) Create a newNode
  newNode = (LIST)malloc(sizeof(struct node));
  if (newNode != NULL){
    newNode->elem = newData;

  // 2) Loop over the list to find the correct position
    for (trav = main ; *trav != NULL && newData > (*trav)->elem ; trav = &(*trav)->link){};
    newNode->link = *trav;
    *trav = newNode;
    printf("insertSorted() success.\n");
  }
}

// Delete
void deleteFirst    (LIST *main, int delete){
  LIST temp;
  if (*main != NULL){
    temp = *main;
    *main = temp->link;
    free(temp);
    printf("deleteFirst() success.\n");
  } else {
    printf("Nothing to be deleted.\n");
  }
}
void deleteLast     (LIST *main, int delete){
  LIST temp;
  LIST *trav;
  if (*main != NULL){
    for (trav = main ; (*trav)->link != NULL ; trav = &(*trav)->link){};
    temp = *trav;
    *trav = NULL;
    free(temp);
    printf("deleteLast() success.\n");
  } else {
    printf("Nothing to be deleted.\n");
  }
}
void deleteAll      (LIST *main){
  LIST trav;
  LIST temp;

  // 1) Let temp point to what trav is pointing to
  // 2) Let trav point to the next available node
  // 3) Delete the node pointed by temp
  for (trav = *main ; trav != NULL ; free(temp)){
    temp = trav;
    trav = trav->link;
  }
  *main = NULL;
  printf("deleteAll() success.\n");
}
void deleteAllOccur (LIST *main, int delete){
  LIST *trav = NULL;
  LIST p1 = NULL;

  trav = main;
  while (*trav != NULL){
    if ((*trav)->elem == delete){
      p1 = *trav;
      *trav = (*trav)->link;
      free(p1);
    } else {
      trav = &(*trav)->link;
    }
  }
}
void deleteElem     (LIST *main, int delete){
  if (*main != NULL){
    LIST *trav;
    LIST temp;
    for (trav = main ; *trav != NULL && (*trav)->elem != delete ; trav = &(*trav)->link){};
    temp = *trav;
    *trav = temp->link;
    free(temp);
  }
}

// Edit
void edit           (LIST *main, int oldData, int newData){
  LIST trav;
  for (trav = *main ; trav != NULL && trav->elem != oldData ; trav = trav->link){};
  trav->elem = newData;
  printf("edit() success.\n");
}

// Others
void reverseList    (LIST *main) {
  LIST x, y, z;
  x = *main;
  y = NULL;

  while (x != NULL) {
    z = x->link;  
    // Update the link to reverse the direction
    x->link = y;
    // Move to the next nodes
    y = x;
    x = z;
  }
  *main = y;
}
void printList      (LIST main){
  for (; main != NULL ; main = main->link){
    printf("[%d] -> ", main->elem);
  }
  printf("NULL\n");
}
bool isMember       (LIST *main, int find){
  LIST trav;
  for (trav = *main ; trav != NULL && trav->elem != find ; trav = trav->link){};
  return (trav != NULL) ? true : false;
}