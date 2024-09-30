#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 5

typedef enum    {YES, NO} status;

typedef struct {
  char          fName[24];
  char          lName[24];
  int           dishesWashed;
  status        isExperienced;
} StudentInfo;

typedef struct {
  StudentInfo   students[MAX];
  int           count;
} DataBase, *DataBaseLL;

typedef struct node {
  StudentInfo   data;
  struct node*  next;
} *LinkedList;

typedef struct {
  DataBase      TC;
  LinkedList    deletedStudents;
  int           ArrayListCount;
  LinkedList    top;
  int deletedCount;
} API_STACK;

//* Utility Functions
void initStack        (API_STACK* main);
void displayStack     (API_STACK main);
void displayLinkList  (API_STACK main);
bool isEmpty          (API_STACK main);
bool isFull           (API_STACK main);

//* Main Functions
void push             (API_STACK* main, StudentInfo newData);
StudentInfo top       (API_STACK main);
void pop              (API_STACK* main);
void generateExperienced  (API_STACK* main);

// Add Files

int main(){
  API_STACK school;
  initStack(&school);

  StudentInfo stud1 = {"Achille","Lanutan",5,YES};
  StudentInfo stud2 = {"Dianne","Yuvallos",0,NO};
  StudentInfo stud3 = {"Xander","Labide",12,YES};

  push(&school, stud1);
  push(&school, stud2);
  push(&school, stud3);

  displayStack(school);

  generateExperienced(&school);
  displayLinkList(school);
}

//* Utility Functions
void initStack        (API_STACK* main){
  main->ArrayListCount = -1;
  main->deletedCount = 0;
  main->deletedStudents = NULL;
  // printf("%-20s", "FUNCTION");
  // printf("%-15s\n", "STATUS");
  // printf("%-20s", "initStack()");
  // printf("%-15s", "SUCCESS");
}
void displayStack     (API_STACK main){
  API_STACK temp;
  initStack(&temp);
  printf("%-15s", "FIRST NAME");
  printf("%-15s", "LAST NAME");
  printf("%-15s", "EXPERIENCED");
  printf("\n=============================================");
  printf("\n");
  while(main.ArrayListCount != -1){
    printf("%-15s%-15s%-15d", top(main).fName, top(main).lName, top(main).isExperienced);
    temp.ArrayListCount++;
    temp.TC.students[temp.ArrayListCount] = top(main);
    pop(&main);
    printf("\n");
  }
}
void displayLinkList  (API_STACK main){
  LinkedList trav;
  printf("\nDisplaying experienced students");
  printf("\n%-15s", "FIRST NAME");
  printf("%-15s", "LAST NAME");
  printf("\n======================");
  printf("\n");
  for (trav = main.deletedStudents ; trav != NULL ; trav = trav->next){
    printf("%-15s%-15s\n", trav->data.fName, trav->data.lName);
  }
}
bool isEmpty          (API_STACK main){
  return main.ArrayListCount == -1;
}
bool isFull           (API_STACK main){
  return main.ArrayListCount == MAX-1;
}

//* Main Functions
void push             (API_STACK* main, StudentInfo newData){
  if(!isFull(*main)){
    main->ArrayListCount++;
    main->TC.students[main->ArrayListCount] = newData;
    main->TC.count++;
    printf("push() successful\n");
  } else {
    printf("Full.\n");
  }
}
StudentInfo top       (API_STACK main){
  StudentInfo dummy = {"XXXXX","XXXXX",0,NO};
  return (!isEmpty(main)) ? main.TC.students[main.ArrayListCount] : dummy;
}
void pop              (API_STACK* main){
  if (!isEmpty(*main)) main->ArrayListCount--;
}
void generateExperienced  (API_STACK* main){
  if (!isEmpty(*main)){
    LinkedList* top;
    LinkedList newNode;
    int x;
    for (x = 0, top = &main->deletedStudents ; x < main->TC.count ; x++){
      if (main->TC.students[x].isExperienced == YES){
        newNode  = (LinkedList)malloc(sizeof(struct node));
        if (newNode != NULL){
          newNode->data = main->TC.students[x];
          newNode->next = *top;
          *top = newNode;
        }
      }
    }
    printf("Generated deleted students!\n");
  }
}

