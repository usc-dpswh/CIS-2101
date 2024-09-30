#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define SIZE 15

typedef enum {NORMAL, NIGGA, MONGGOLOID} ETHNICITY;

typedef struct {
  char        fName       [32];
  char        lName       [32];
  char        course      [5];
  int         id;
} Personal, *PersonalPTR;

typedef struct node {
  Personal    Student;
  ETHNICITY   type;
  int         next;
} Data, *DataPTR;

typedef struct node {
  Data        classRecord [SIZE];
  int         count;
  int         Avail;
} VirtualHeap;

// Initializes the VirtualHeap by setting count to 0 and Avail to the first available node
void      initVH           (VirtualHeap *main, int* head);
// Inserts the given Data sorted by ID
void      insertSorted     (VirtualHeap *main, int* head, Data newData);
// Loop insertSorted to populate the VirtualHeap
void      populate         (VirtualHeap *main, int* head, Data* newData);
// Malloc()
void      allocSpace       (VirtualHeap *main);
// Deletes a node and places it back to the available nodes via insertFirst
void      deallocSpace     (VirtualHeap *main, int index);
// Returns TRUE if found, else FALSE
bool      findByID         (VirtualHeap main, int search);
// Gets all niggas from the linked list and returns the address it holds to the calling function
DataPTR   getAllNiggas     (VirtualHeap main, int* head, DataPTR ptr);
// Displays the info of the niggas in a linked list
void      displayNiggas    (VirtualHeap main, int* head);

int main(){
  VirtualHeap Dogs;
  int List;
  initVH(&Dogs, &List);

  // Existing Data
  Data uscRecord[SIZE] = {
    {{"Xander", "Labide",       "BSIT", 22100001},NIGGA,      NULL},
    {{"Julz",   "Pussy",        "BSCS", 22100002},NORMAL,     NULL},
    {{"Carlo",  "Aparri",       "BSIS", 22100003},MONGGOLOID, NULL},
    {{"Eman",   "Patalinghug",  "BSIT", 22100004},NIGGA,      NULL},
    {{"Nelson", "Ochavo",       "BSCS", 22100005},NIGGA,      NULL},
    {{"Eman",   "Patalinghug",  "BSIT", 22100006},NORMAL,     NULL},
    {{"Dianne", "Yuvallos",     "BSIS", 22100007},NIGGA,      NULL},
    {{"John",   "Santillan",    "BSIS", 22100008},NORMAL,     NULL},
    {{"Kyle",   "Santillan",    "BSIS", 22100009},NIGGA,      NULL},
    {{"Anne",   "Laranjo",      "BSIS", 22100010},NORMAL,     NULL},
  };

  populate(&Dogs, &List, uscRecord);
  
  // insertSorted(&Dogs, &List, uscRecord[0])
}

void      initVH           (VirtualHeap *main, int head){
  int x;
  for (x = -1 ; x < SIZE ; x++){
    main->classRecord[x+1].next = x;
  }
  main->Avail = SIZE-1;
  main->count = 0;
}
void      insertSorted     (VirtualHeap *main, int head, Data newData);
void      populate         (VirtualHeap *main, int* head, Data* newData);
void      allocSpace       (VirtualHeap *main);
void      deallocSpace     (VirtualHeap *main, int index);
bool      findByID         (VirtualHeap main, int search);
DataPTR   getAllNiggas     (VirtualHeap main, int head, DataPTR ptr);
void      displayNiggas    (VirtualHeap main, int head);


