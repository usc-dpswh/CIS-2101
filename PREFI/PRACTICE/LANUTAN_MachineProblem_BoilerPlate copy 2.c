#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 10
#define CLOSE_SIZE 10
#define OPEN_DICT 12
#define TREE_SIZE 15
#define EMPTY "EMPTY"
#define DELETED "DELETED"

//============================================//

// Struct Definitions
typedef struct {
  char        fName[16];
  char        lName[16];
} Name;

typedef struct {
  float       GWA;
  char        studentID[16];
  char        program[8];
} schoolInfo;

typedef struct node {
  schoolInfo  studentInfo;
  Name        studentName;
  struct node* next;
} Student, *StudentPTR;

typedef struct {
  Student     person;
  int         link;
} NodeType;

typedef int   Tree[TREE_SIZE];

//============================================//

// Cursor Based
// Serves as the database in which data is fetched from.
typedef struct {
  NodeType    Nodes[SIZE];
  int         Avail;
  int         count;
} VHeap;

//============================================//

// Closed Dictionary 
// Stores ALL student information STRICTLY in ascending order.
typedef struct {
  Student     studentsCDict[CLOSE_SIZE];
  int         count;
} ClosedDictionary;

// Open Dictionary
// Stores students that have grades above 3.0 / FAILED
typedef struct openD {
  StudentPTR  header[OPEN_DICT];
  int         openDCount;
} OpenDictionary;

//============================================//

// Stack Linked List
// Fetch data from Closed Dictionary and store all the Dean's Listers (students that have a GWA below 1.7)
// Must STRICTLY be sorted in ascending order
typedef struct stack {
  StudentPTR  front;
  StudentPTR  rear;
  int         stackCount;
} Stack;

//============================================//

// Tree
// Stores all students in a maxHeap according to their grade.
typedef struct heap {
  Tree        treeStudents;
  int         lastNdx;
} *HeapPTR;

//============================================//

//* Problem 1 Functions
// The goal of problem 1 is to extract data from the cursor based database and store it into the closed dictionary in strictly ascending order according to GWA.

VHeap initVheap           (void);
void  initCloseDict       (ClosedDictionary* main);
int   allocSpace          (VHeap* main);
Student  deallocSpace     (VHeap* main, int index);
int   hashCD              (char studentID[]);
void  populateDB          (VHeap* main);
void  populateCloseDict   (VHeap* mainVHeap, ClosedDictionary* mainCloseDict);
void  displayCloseDict    (ClosedDictionary main);
void  displayVHeap        (VHeap main);

//* Problem 2 Functions
// The goal of problem 2 is to filter out all the students who PASSED and FAILED students.
// All PASSED students (GWA <= 3.0) stay inside the closed dictionary while all FAILED students are transferred into the open dictionary. Make sure order is still retained inside the closed dictionary.
void  initOpenDict        (OpenDictionary* mainOD);
int   hashOD              (char studentID[]);
void  filterPassFromFail  (ClosedDictionary* mainCD, OpenDictionary* mainOD);
void  displayOD           (OpenDictionary mainOD);

//* Problem 3 Functions
// The goal of problem 3 is to filter out Dean's Listers (students who have a GWA <= 1.70) from the closed dictionary into the Stack.

void  initStack           (Stack* mainStack);
void  push                (Stack* mainStack, Student newData);
void  pop                 (Stack* mainStack);
void  filterDL            (Stack* mainStack, ClosedDictionary mainCD);

//* Problem 4 Functions
// The goal of problem 4 is to simply convert the data from the Stack into a maxHeap, then display it.

void  displayTree         (HeapPTR  main);
void  initHeap            (HeapPTR* main);
void  convertToMaxHeap    (HeapPTR* main);
void  deleteMax           (HeapPTR* main);

int main(){
  //* Problem 1 (VHeap and ClosedDictionary)
  // 1) Declare variables VHeap and ClosedDictionary, then initialize both.
  // 2) Populate the VHeap
  // 3) Display the ClosedDictionary.
  // 4) Populate the ClosedDictionary using data from VHeap.
  // 5) Display the VHeap and ClosedDictionary again.

  // Start writing your code here //
  VHeap A;
  ClosedDictionary B;
  A = initVheap();
  initCloseDict(&B);
  populateDB(&A);
  displayVHeap(A);
  displayCloseDict(B);
  populateCloseDict(&A, &B);
  displayVHeap(A);
  displayCloseDict(B);

  //* Problem 2 (OpenDictionary)
  // 1) Declare and then initialize a variable OpenDictionary
  // 2) Filter the students by calling the function filterPassFromFail()
  // 3) Display the OpenDictionary

  // Start writing your code here //

  OpenDictionary C;
  initOpenDict(&C);
  filterPassFromFail(&B, &C);
  displayOD(C);


  //* Problem 3 (Stack)
  // 1) Declare and then initialize a variable Stack.
  // 2) Filter the Dean's Listers by calling the function filterDL()

  // Start writing your code here //


  //* Problem 4
  // 1) Declare and then initialize a variable HeapPTR
  // 2) Convert the data from the open dictionary into a maxHeap.
  // 3) Display the tree.
  // 4) Call deleteMax()
  // 5) Verify the deleted student by displaying the tree again.

  // Start writing your code here //


  return 0;
}

//* Problem 1 Functions
// The goal of problem 1 is to extract data from the cursor based database and store it into the closed dictionary in strictly ascending order according to GWA.

VHeap initVheap           (void){
  VHeap new;
  int x;
  for (x = -1 ; x < SIZE-1 ; x++){
    new.Nodes[x+1].link = x;
  }
  new.Avail = SIZE-1;
  new.count = 0;
  printf("\nInitialized VHeap.");
}
void  initCloseDict       (ClosedDictionary* main){
  int x;
  for (x = 0 ; x < CLOSE_SIZE ; x++){
    strcpy(main->studentsCDict[x].studentInfo.studentID, EMPTY);
    strcpy(main->studentsCDict[x].studentName.fName, "John");
    strcpy(main->studentsCDict[x].studentName.lName, "Doe");
    strcpy(main->studentsCDict[x].studentInfo.program, "N/A");
    main->studentsCDict[x].studentInfo.GWA = 3.0;
  }
  main->count = 0;
  printf("\nInitialized Close Dictionary.");
}
Student  deallocSpace     (VHeap* main, int index){
  Student temp = {{3.0, "XXXXXXXX", "N/A"}};
  if (index >= 0 && index < SIZE){
    temp = main->Nodes[index].person;
    main->Nodes[index].link = main->Avail;
    main->Avail = index;
    // printf("\n[%s] Dealloc successful.", temp.studentInfo.studentID);
  }
  return temp;
}
int   hashCD              (char studentID[]){
  int x;
  int hashVal = 0;
  for (x = 0 ; studentID[x] != '\0' ; x++){
    hashVal = hashVal + studentID[x] - '0';
  }
  hashVal = hashVal % CLOSE_SIZE;
  return hashVal % CLOSE_SIZE;
}
void  populateDB          (VHeap* main){
  Student data[SIZE] = {
    {{3.00, "22103514", "BS-IT"},     {"Achille", "Lanutan"}},
    {{2.10, "11600006", "BA-COMM"},   {"Dianne",  "Yuvallos"}},
    {{1.44, "22103244", "BS-IT"},     {"Xander",  "Labide"}},
    {{1.10, "22103312", "BS-CS"},     {"Julz",    "Cortes"}},
    {{3.23, "22103110", "BS-CS"},     {"Karylle", "Bernate"}},
    {{1.70, "21102204", "BS-IS"},     {"Carlo",   "Juab"}},
    {{4.29, "22103277", "BS-IT"},     {"Jasper",  "Marbella"}},
    {{3.89, "22102001", "BS-IT"},     {"Gabriel", "dela Cruz"}},
    {{2.50, "22102003", "BS-CS"},     {"Sarah",   "Palabrica"}},
    {{1.90, "22102002", "BS-CS"},     {"Emma",    "Myers"}},
  };

  int x;
  for (x = -1 ; x < SIZE-1 && main->Avail >= 0 ; x++){
    main->Nodes[x+1].person = data[x+1];
    main->Nodes[x+1].link = x;
    main->Avail--;
    main->count++;
  }
  printf("\nPopulated VHeap database.");
}
void  populateCloseDict   (VHeap* mainVHeap, ClosedDictionary* mainCloseDict){
  int x, y;
  int hashVal;
  for (x = 0 ; x < SIZE && mainVHeap->count > 0 ; x++){
    if (mainCloseDict->count < CLOSE_SIZE){
      for (hashVal = hashCD(mainVHeap->Nodes[x].person.studentInfo.studentID) ; strcmp(mainCloseDict->studentsCDict[hashVal].studentInfo.studentID, EMPTY) != 0 && strcmp(mainCloseDict->studentsCDict[hashVal].studentInfo.studentID, DELETED) != 0 ; hashVal = (hashVal + 1) % CLOSE_SIZE){};
      Student newStudent = deallocSpace(mainVHeap, x);
      if (strcmp(newStudent.studentInfo.studentID, "XXXXXXXX") != 0){
        mainCloseDict->studentsCDict[hashVal] = deallocSpace(mainVHeap, x);
        mainVHeap->count--;
        mainCloseDict->count++;
        // printf("\nSuccessfully inserted [%s]", newStudent.studentInfo.studentID);
      } else {
        printf("\nVHeap is now empty.");
      }
    } else {
      printf("\nNo more space in ClosedDictionary to insert.");
    }
  }
  printf("\nConverted data from VHeap into ClosedDictionary.");
}
void  displayCloseDict    (ClosedDictionary main){
  printf("\n\nDetails of Close Dictionary");
  printf("\nCount :: %d", main.count);
  printf("\n-------------------------------------");
  if (main.count > 0){
    printf("\n\n%-6s", "Index");
    printf("%-12s", "Student ID");
    printf("%-12s", "First Name");
    printf("%-12s", "Last Name");
    printf("%-12s", "Program");
    printf("%-12s", "GWA");
    printf("\n%-6s%-12s%-12s%-12s%-12s%-12.2s",
      "-----",
      "-----------",
      "-----------",
      "-----------",
      "-----------",
      "-----------"
    );

    int x; 
    for (x = 0 ; x < CLOSE_SIZE ; x++){
      printf("\n%-6d%-12s%-12s%-12s%-12s%-12.2f",
        x,
        main.studentsCDict[x].studentInfo.studentID,
        main.studentsCDict[x].studentName.fName,
        main.studentsCDict[x].studentName.lName,
        main.studentsCDict[x].studentInfo.program,
        main.studentsCDict[x].studentInfo.GWA
      );
    }
  } else {
    printf("\nYour ClosedDictionary is empty.");
  }
}
void  displayVHeap        (VHeap main){
  printf("\n\nDetails of VHeap");
  printf("\nCount :: %d", main.count);
  printf("\n-------------------------------------");
  if (main.count > 0){
    printf("\n\n%-6s", "Index");
    printf("%-12s", "Student ID");
    printf("%-12s", "First Name");
    printf("%-12s", "Last Name");
    printf("%-12s", "Program");
    printf("%-12s", "GWA");
    printf("\n%-6s%-12s%-12s%-12s%-12s%-12.2s",
      "-----",
      "-----------",
      "-----------",
      "-----------",
      "-----------",
      "-----------"
    );
  
    int x; 
    for (x = 0 ; x < CLOSE_SIZE ; x++){
      printf("\n%-6d%-12s%-12s%-12s%-12s%-12.2f",
        x,
        main.Nodes[x].person.studentInfo.studentID,
        main.Nodes[x].person.studentName.fName,
        main.Nodes[x].person.studentName.lName,
        main.Nodes[x].person.studentInfo.program,
        main.Nodes[x].person.studentInfo.GWA
      );
    }
  } else {
    printf("\nYour VHeap is empty.");
  }
}

//* Problem 2 Functions
// The goal of problem 2 is to filter out all the students who PASSED and FAILED students.
// All PASSED students (GWA <= 3.0) stay inside the closed dictionary while all FAILED students are transferred into the open dictionary. Make sure order is still retained inside the closed dictionary.
void  initOpenDict        (OpenDictionary* mainOD){
  int x;
  for (x = 0 ; x < OPEN_DICT ; x++){
    mainOD->header[x] = NULL;
  }
  mainOD->openDCount = 0;
}
int   hashOD              (char studentID[]){
  int x;
  int hashVal = 0;
  for (x = 0 ; studentID[x] != '\0' ; x++){
    hashVal = (hashVal + studentID[x]) - '0';
  }
  hashVal = (hashVal / 2) % OPEN_DICT;
  return hashVal;
}
void  filterPassFromFail  (ClosedDictionary* mainCD, OpenDictionary* mainOD){
  StudentPTR* trav;
  StudentPTR newStudent = NULL;
  int x, hashVal;
  
  for (x = 0 ; x < CLOSE_SIZE ; x++){
    if (mainCD->count > 0){
      if (mainCD->studentsCDict[x].studentInfo.GWA > 3.0){
        hashVal = hashOD(mainCD->studentsCDict[x].studentInfo.studentID);
        Student temp = mainCD->studentsCDict[x];
        printf("hashVal = %d");
        for (trav = &(mainOD->header[hashVal]) ; *trav != NULL && strcmp(mainCD->studentsCDict[x].studentInfo.studentID, (*trav)->studentInfo.studentID) > 0 ; trav = &(*trav)->next){
          printf("\n%d > %d", mainCD->studentsCDict[x].studentInfo.studentID, (*trav)->studentInfo.studentID);
        };

        if (*trav == NULL || strcmp((*trav)->studentInfo.studentID, mainCD->studentsCDict[x].studentInfo.studentID) != 0){
          newStudent = (StudentPTR)malloc(sizeof(struct node));
          if (newStudent != NULL){
            newStudent->studentInfo = temp.studentInfo;
            newStudent->studentName = temp.studentName;
            newStudent->next = *trav;
            *trav = newStudent;
            strcpy(mainCD->studentsCDict[x].studentInfo.studentID, DELETED);
            mainCD->count--;
            mainOD->openDCount++;
          }
        }
      } else {
        printf("\n[%s] is not a failing student.", mainCD->studentsCDict[x].studentInfo.studentID);
      }
    } else {
      printf("\nClosedDictionary is now full.");
    }
  }
}
void  displayOD           (OpenDictionary mainOD){
  printf("\n\nDetails of Open Dictionary (FAILING STUDENTS)");
  printf("\nCount :: %d", mainOD.openDCount);
  printf("\n-------------------------------------");
  if (mainOD.openDCount > 0){
    StudentPTR trav;
    int x; 
    printf("\n%-6s%s", "INDEX", "STUDENTS");
    for (x = 0 ; x < OPEN_DICT ; x++){
      printf("\n%-6d ", x);
      for (trav = mainOD.header[x] ; trav != NULL ; trav = trav->next){
        printf("%s[%.2f%-6c :: ", trav->studentInfo.studentID, trav->studentInfo.GWA, ']');
      }
    }
  } else {
    printf("\nYour OpenDictionary is empty.");
  }
}

//* Problem 3 Functions
// The goal of problem 3 is to filter out Dean's Listers (students who have a GWA <= 1.70) from the closed dictionary and store it into the stack.

void  initStack           (Stack* mainStack);
void  push                (Stack* mainStack, Student newData);
void  pop                 (Stack* mainStack);
void  filterDL            (Stack* mainStack, ClosedDictionary mainCD);

//* Problem 4 Functions
// The goal of problem 4 is to simply convert the data from the Stack into a maxHeap, then display it.

void  displayTree         (HeapPTR  main);
void  initHeap            (HeapPTR* main);
void  convertToMaxHeap    (HeapPTR* main);
void  deleteMax           (HeapPTR* main);