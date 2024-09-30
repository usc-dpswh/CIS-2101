#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LSIZE 10

typedef struct {
  char FN[24], LN[16], MI;
} nametype;

typedef struct {
  char ID[10];
  nametype name;
  char course[8];
  int yrLevel;
} studRec;

/* Array Implementation of ADT List */
typedef struct {
  nametype names[LSIZE];
  int lastNdx; // index of the last element
} *NameList;

/* Link list implementation of list */
typedef struct node {
  studRec sElem;
  struct node *sLink;
} *LinkList;

NameList removeICT(LinkList* A);
void populateLinkList(LinkList* A);
void displayDeleted(NameList A);
void displayLinkList(LinkList A);

int main(){
  NameList A;
  LinkList studentList = NULL;
  populateLinkList(&studentList);
  // displayLinkList(studentList);

  A = removeICT(&studentList);
  displayDeleted(A);
}

NameList removeICT(LinkList* A){
  NameList new = (NameList)malloc(sizeof(*new));
  new->lastNdx = 0;

  LinkList* trav;
  LinkList temp;
  int x,y;
  if (new != NULL){
    // deleteMany()
    for (trav = A ; *trav != NULL ;){
      if (strcmp((*trav)->sElem.course, "BSICT") == 0){
        temp = *trav;
        // First for loop is to find position to insert the new data in the ARRAY
        for (x = 0 ; x < new->lastNdx && strcmp((*trav)->sElem.name.LN, new->names[x].LN) > 0 ; x++){};
        // Second for loop is for shifting the elements to make way for new data since we are doing insertSorted()
        for (y = new->lastNdx ; y != x ; y--){
          new->names[y] = new->names[y-1];
        }
        // after finding the position, insert at index [y]
        new->names[y] = temp->sElem.name;
        printf("Inserted [%s] into NameList new!\n", new->names[y].LN);
        // let *trav point to the next node
        *trav = temp->sLink;
        free(temp);
        new->lastNdx++;
      } else {
        // we only change where trav (note: not *trav) is pointing if not BSICT
        trav = &(*trav)->sLink;
      }
    }

    // insertSorted()
  }
  return new;
}
void populateLinkList(LinkList* A){
  studRec database[LSIZE] = {
    {"0001",{"DIANNE","YUVALLOS",'P'},  "BSICT",  2},
    {"0002",{"ACHILLE","LORENZO",'M'},  "BSICT",  2},
    {"0003",{"MATT","MAGDADARO",'E'},   "BSICT",   1},
    {"0004",{"CARLO","JUAB",'A'},       "BSICT",   3},
    {"0005",{"GERRILYN","YUVALLOS",'P'},"BSICT",   4},
    {"0006",{"GRAN","SABANDAL",'C'},    "BSICT",  1},
    {"0007",{"CHRISTINE","PENA",'F'},   "BSICT",   2},
  };
  int count = 7;
  LinkList *trav;
  int x;
  for (x = 0 ; x < count ; x++){
    for (trav = A ; *trav != NULL ; trav = &(*trav)->sLink){};
    LinkList newNode = (LinkList)malloc(sizeof(struct node));
    if (newNode != NULL){
      newNode->sElem = database[x];
      newNode->sLink = *trav;
      *trav = newNode;
      // printf("Inserted [%s]\n", database[x].name.FN);
    }
  }; 
}
void displayDeleted(NameList A){
  int x;
  printf("%10s%10s%10s","FNAME","LNAME","MI");
  printf("\n===================================\n");
  for (x = 0 ; x < A->lastNdx ; x++){
    printf("%-10s%10s%10c\n", A->names[x].FN, A->names[x].LN, A->names[x].MI);
  }
}
void displayLinkList(LinkList A){
  LinkList trav;
  for (trav = A ; trav != NULL ; trav = trav->sLink){
    printf("%s\n", A->sElem.course);
  }
}