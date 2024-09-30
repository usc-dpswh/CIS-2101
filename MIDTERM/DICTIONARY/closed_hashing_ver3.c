#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10
#define EMPTY -1
#define DELETED -2
#define PACKING_DENSITY (int)(MAX * 0.5)

typedef struct {
  int data;
  int link;
} DICTIONARY;

typedef struct node {
  DICTIONARY A[MAX];
  int avail;
  int last;
  int count;
} VHeap, *VHeapPTR;

void initDictionary   (VHeap* main, int* head);
int allocSpace        (VHeap* main);
bool isMember         (VHeap main, int find);
int hash              (int elem);
void insert           (VHeap* main, int* head, int newData);
void delete           (VHeap* main, int delete);
void display          (VHeap main);

int main(){
  VHeap Memory;
  int head;
  initDictionary(&Memory, &head);

  insert(&Memory, &head, 3);
  insert(&Memory, &head, 33);
  insert(&Memory, &head, 43);
  insert(&Memory, &head, 22);
  insert(&Memory, &head, 1);
  insert(&Memory, &head, 44);
  insert(&Memory, &head, 64);
  insert(&Memory, &head, 71);

  display(Memory);
}

void initDictionary   (VHeap* main, int* head){
  int x;
  // Initialize PRIME DATA
  for (x = -1 ; x < PACKING_DENSITY ; x++){
    main->A[x+1].link = -1;
    main->A[x+1].data = EMPTY;
  }
  // Initialize SYNONYMS AREA
  for (x = PACKING_DENSITY ; x < MAX ; x++){
    main->A[x].data = EMPTY;
    main->A[x].link = x+1; 
  }
  main->A[x-1].link = -1;
  main->avail = PACKING_DENSITY;
  main->last = PACKING_DENSITY;
  *head = -1;
  main->count = 0;
  printf("Initialized dictionary.\n");
}
int allocSpace        (VHeap* main){
  int retval = main->avail;
  if (retval != -1){
    main->avail = main->A[retval].link;
  }
  return retval;
}
int hash              (int elem){
  return elem % 10;
}
bool isMember         (VHeap main, int find){
  int trav, stopper;
  for (trav = hash(find), stopper = 0 ; stopper < PACKING_DENSITY && main.A[trav].data != find ; trav = (trav+1) % PACKING_DENSITY, stopper++){};
  return stopper < PACKING_DENSITY;
}
void insert           (VHeap* main, int* head, int newData){
  int* trav;
  int hashVal;
  int newNode;
  // Has space
  if (main->count < MAX){
    hashVal = hash(newData);
    // If unique
    if (!isMember(*main, newData)){
      // No collision
    if (main->A[hashVal].data == EMPTY || main->A[hashVal].data == DELETED){
        main->A[hashVal].data = newData;
        main->A[hashVal].link = -1;
        main->count++;
        printf("No collision. [%d] inserted.\n", newData);
      // Collision
      } else {
        newNode = allocSpace(main);
        if (newNode != -1){
          for (trav = &main->A[hashVal].link ; *trav != -1 ; trav = &main->A[*trav].link){};
          main->A[main->last].data = newData;
          main->A[main->last].link = -1;
          *trav = main->last;
          main->last++;
          printf("Collision. [%d] inserted at last.\n", newData);
        }
      }
    // If not unique
    } else {
      printf("[%d] is not unique.\n", newData);
    }
  // No space
  } else {
    printf("No more space left to insert [%d]\n", newData);
  }
}
void delete           (VHeap* main, int delete);
void display          (VHeap main){
  int x,y;
  for (x = 0 ; x < PACKING_DENSITY ; x++){
    printf("[%d] => ", x);
    for (y = x ; y != -1 && main.A[x].data != EMPTY ; y = main.A[y].link){
      // printf("%d => ", main.A[y].data);
      printf("%d => ", main.A[y].data);
    }
    printf("\n");
  }
}