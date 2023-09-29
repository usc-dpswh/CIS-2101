#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int ID;
  char LN[16], FN[24], MI;  // Lastname, Firstname, Middle Initial
  char course[8];
  int yearLevel;
} Studrec;

typedef struct node {
  Studrec stud;
  struct node *link;
} *StudList;                // Definition of the List

StudList init();
void insertFirst(StudList *main);
void display(StudList *main);

int main(){
  StudList usc_record = NULL;

  usc_record = (StudList)malloc(sizeof(Studrec));
  usc_record->stud.ID = 22103514;
  strcpy(usc_record->stud.LN, "LANUTAN");
  strcpy(usc_record->stud.FN, "ACHILLE LORENZO");
  usc_record->stud.MI = 'M';
  strcpy(usc_record->stud.course, "BSIT");
  usc_record->stud.yearLevel = 2;
  usc_record->link = NULL;

  usc_record->link = (StudList)malloc(sizeof(Studrec));
  usc_record->link->stud.ID = 19104146;
  strcpy(usc_record->link->stud.LN, "JUAB");
  strcpy(usc_record->link->stud.FN, "JAN CARLO");
  usc_record->link->stud.MI = 'A';
  strcpy(usc_record->link->stud.course, "BSIT");
  usc_record->link->stud.yearLevel = 2;
  usc_record->link->link = NULL;

  display(&usc_record);

  insertFirst(&usc_record);

  display(&usc_record);
}

StudList init(){
  StudList newNode = (StudList)malloc(sizeof(Studrec));
  
  if (newNode != NULL){
    // Get user input
    printf("Enter your ID: ");
    scanf("%d", &newNode->stud.ID);
    fflush(stdin);

    printf("Enter your LAST NAME: ");
    scanf("%[^\n]s",newNode->stud.LN);
    fflush(stdin);

    printf("Enter your FIRST NAME: ");
    scanf("%[^\n]s", newNode->stud.FN);
    fflush(stdin);

    printf("Enter your MIDDLE INITIAL: ");
    scanf("%c", &newNode->stud.MI);
    fflush(stdin);

    printf("Enter your COURSE: ");
    scanf("%[^\n]s", newNode->stud.course);
    fflush(stdin);

    printf("Enter your YEAR LEVEL: ");
    scanf("%d", &newNode->stud.yearLevel);
    fflush(stdin);

    return newNode;
  } else {
    printf("Memory allocation unsuccessful.\n");
  }
}

void insertFirst(StudList *main){
  StudList *trav = main;
  StudList newNode = init();

  // Check if ID is unique
  for (; *trav != NULL && (*trav)->stud.ID != newNode->stud.ID ; trav = &(*trav)->link){}

  // If trav reached the end, meaning newNode ID is unique from the existing data list.
  if (*trav == NULL){

    trav = main;
    newNode->link = *trav;
    *trav = newNode;
    printf("Successfully inserted new node.\n");

  } else {

    printf("Not unique.\n");

  }
}

void display(StudList *main){
  StudList *trav = main;

  for (; *trav != NULL ; trav = &(*trav)->link){
    printf("%d - %-5s\n", 
      (*trav)->stud.ID, 
      (*trav)->stud.LN
    );
  }
}

