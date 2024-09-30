#include <stdio.h>
#include <stdbool.h>
#define SIZE 10
#define CLOSE_SIZE 10
#define OPEN_DICT 12
#define TREE_SIZE 15

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
void  deallocSpace        (VHeap* main, int index);
int   hashCD              (VHeap main);
void  insertSorted        (VHeap* main, Student newData);
void  populateDB          (VHeap* main);
void  populateCloseDict   (VHeap* mainVHeap, ClosedDictionary* mainCloseDict);
void  displayCloseDict    (ClosedDictionary main);

//* Problem 2 Functions
// The goal of problem 2 is to filter out all the students who PASSED and FAILED students.
// All PASSED students (GWA <= 3.0) stay inside the closed dictionary while all FAILED students are transferred into the open dictionary. Make sure order is still retained inside the closed dictionary.
void  initOpenDict        (OpenDictionary* mainOD);
int   hashOD              (ClosedDictionary main);
void  filterPassFromFail  (ClosedDictionary* mainCD, OpenDictionary* mainOD);
void  displayOD           (OpenDictionary* mainOD);

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
  // 1) Declare variables VHeap and ClosedDictionary
  // 2) Populate the VHeap
  // 3) Populate the ClosedDictionary using data from VHeap. Make sure it's in ascending order, so use the function insertSorted()
  // 4) Display the ClosedDictionary

  // Start writing your code here //
  

  //* Problem 2 (OpenDictionary)
  // 1) Declare and then initialize a variable OpenDictionary
  // 2) Filter the students by calling the function filterPassFromFail()
  // 3) Display the OpenDictionary

  // Start writing your code here //


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

VHeap initVheap           (void);
void  initCloseDict       (ClosedDictionary* main);
int   allocSpace          (VHeap* main);
void  deallocSpace        (VHeap* main, int index);
int   hashCD              (VHeap main);
void  insertSorted        (VHeap* main, Student newData);
void  populateDB          (VHeap* main);
void  populateCloseDict   (VHeap* mainVHeap, ClosedDictionary* mainCloseDict);
void  displayCloseDict    (ClosedDictionary main);

//* Problem 2 Functions
// The goal of problem 2 is to filter out all the students who PASSED and FAILED students.
// All PASSED students (GWA <= 3.0) stay inside the closed dictionary while all FAILED students are transferred into the open dictionary. Make sure order is still retained inside the closed dictionary.
void  initOpenDict        (OpenDictionary* mainOD);
int   hashOD              (ClosedDictionary main);
void  filterPassFromFail  (ClosedDictionary* mainCD, OpenDictionary* mainOD);
void  displayOD           (OpenDictionary* mainOD);

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