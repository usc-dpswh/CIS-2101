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

typedef Student   Tree[TREE_SIZE];

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
  StudentPTR  top;
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
// The goal of problem 1 is to extract data from the cursor based database and store it into the closed dictionary.

VHeap initVheap           (void);
void  initCloseDict       (ClosedDictionary* main);
Student  deallocSpace     (VHeap* main, int index);
// Adds up all the digits of the studentID, then return the sum that's appropriate for the ClosedDictionary size as the hash value.
int   hashCD              (char studentID[]);
// Simply populate the VHeap by transferring the given data into the VHeap.
void  populateDB          (VHeap* main);
// Populates the ClosedDictionary by getting all data from the VHeap. Note that deallocSpace SHOULD be used for the VHeap.
void  populateCloseDict   (VHeap* mainVHeap, ClosedDictionary* mainCloseDict);
// Complete the function
void  displayCloseDict    (ClosedDictionary main);
// Complete the function
void  displayVHeap        (VHeap main);

//* Problem 2 Functions
// The goal of problem 2 is to filter out all the students who PASSED and FAILED students.
// All PASSED students (GWA <= 3.0) stay inside the closed dictionary while all FAILED students are transferred into the open dictionary. Make sure order is still retained inside the closed dictionary.
void  initOpenDict        (OpenDictionary* mainOD);
// Adds up all the digits of the studentID, then return half of the current sum that's appropriate for the OpenDictionary size as the hash value.
int   hashOD              (char studentID[]);
// Gets all data from the ClosedDictionary and filters the passing and failing students. Failing students are students with grades that are >3.0.
void  filterPassFromFail  (ClosedDictionary* mainCD, OpenDictionary* mainOD);
void  displayOD           (OpenDictionary mainOD);

//* Problem 3 Functions
// The goal of problem 3 is to filter out Dean's Listers (students who have a GWA <= 1.70) from the closed dictionary into the Stack.

void  initStack           (Stack* mainStack);
void  push                (Stack* mainStack, Student newData);
// [OPTIONAL] Use the Stack functions in displaying your Stack, otherwise, simply iterate and display it.
Student  pop              (Stack* mainStack);
// Filter the Dean's Listers (students with grade <= 1.70) from the OpenDictionary, transferred into the Stack. Use the push() function.
void  filterDL            (Stack* mainStack, ClosedDictionary mainCD);
void  displayStack        (Stack*  main);

//* Problem 4 Functions
// The goal of problem 4 is to simply convert the data from the Stack into a maxHeap, then display it.

void  displayTree         (HeapPTR  main);
void  initHeap            (HeapPTR* main);
// Inserts into the heap a given student while maintaining POT. It should be a minHeap.
void  insertIntoHeap	  (HeapPTR* main, Student newStudent);
// Populate the heap by using the insertIntoHeap() function.
void  populateHeap        (HeapPTR* mainHeap, ClosedDictionary* mainCD);
// [OPTIONAL] Try deleting the current student with the highest GWA.
void  deleteMax           (HeapPTR* main);
// Convert your minHeap into a maxHeap.
void  convertIntoMaxHeap	(HeapPTR* main);
void  displayHeap		  (HeapPTR main);


int main(){
  //* Problem 1 (VHeap and ClosedDictionary)
  // 1) Declare variables VHeap and ClosedDictionary, then initialize both.
  // 2) Populate the VHeap
  // 3) Display the VHeap and ClosedDictionary.
  // 4) Populate the ClosedDictionary using data from VHeap.
  // 5) Display the VHeap and ClosedDictionary again.

  // Start writing your code here //

  //* Problem 2 (OpenDictionary)
  // 1) Declare and then initialize a variable OpenDictionary
  // 2) Filter the students by calling the function filterPassFromFail()
  // 3) Display the OpenDictionary

  // Start writing your code here //


  //* Problem 3 (Stack)
  // 1) Declare and then initialize a variable Stack.
  // 2) Filter the Dean's Listers by calling the function filterDL()
  // 3) Display the stack.

  // Start writing your code here //


  //* Problem 4
  // 1) Declare and then initialize a variable HeapPTR
  // 2) Convert the data from the open dictionary into a maxHeap.
  // 3) Display the tree.
  // 4) [OPTIONAL] Call deleteMax()
  // 5) [OPTIONAL] Verify the deleted student by displaying the tree again.

  // Start writing your code here //
  
  return 0;
}

//* Problem 1 Functions
// The goal of problem 1 is to extract data from the cursor based database and store it into the closed dictionary in strictly ascending order according to GWA.

VHeap initVheap           (void){
  VHeap new;
  
  return new;
}
void  initCloseDict       (ClosedDictionary* main){
  int x;
  
  printf("\nInitialized Close Dictionary.");
}
Student  deallocSpace     (VHeap* main, int index){
  Student temp = {{3.0, "XXXXXXXX", "N/A"}};
  
  return temp;
}
int   hashCD              (char studentID[]){
  
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
  for ( ; ; ){
    // Write the body of the loop.
  }
  printf("\nPopulated VHeap database.");
}
void  populateCloseDict   (VHeap* mainVHeap, ClosedDictionary* mainCloseDict){
  
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
    for ( ; ; ){
      printf("",
        // Write the code here
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
    for ( ; ; ){
      printf("",
		// Write the code here.        
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
  
}
int   hashOD              (char studentID[]){
  
}
void  filterPassFromFail  (ClosedDictionary* mainCD, OpenDictionary* mainOD){
  StudentPTR* trav;
  StudentPTR newStudent = NULL;
  int x, hashVal;
  
//  Start writing your code here.
}
void  displayOD           (OpenDictionary mainOD){
  printf("\n\nDetails of Open Dictionary (FAILING STUDENTS)");
  printf("\nCount :: %d", mainOD.openDCount);
  printf("\n-------------------------------------");
  if (mainOD.openDCount > 0){
    StudentPTR trav;
    int x; 
    printf("", "INDEX", "STUDENTS");		// Write the code for proper formatting. How much spacing is up to you, just make it look clean.
    for (x = 0 ; x < OPEN_DICT ; x++){
      printf("", );							// Displays the INDEX
      for ( ;  ; ){
        printf("%s[%.2f] :: ", );			// Displays the studentID and the GWA of that student.
      }
    }
  } else {
    printf("\nYour OpenDictionary is empty.");
  }
}

//* Problem 3 Functions
// The goal of problem 3 is to filter out Dean's Listers (students who have a GWA < 1.71) from the closed dictionary and store it into the stack.

void  initStack           (Stack* mainStack){
  
}
void  push                (Stack* mainStack, Student newData){
  StudentPTR newStudent = (StudentPTR)malloc(sizeof(struct node));
  if (// Write the proper condition){
		// Write the code of the if-block here.   		
	}
}
Student pop               (Stack* mainStack) {
  StudentPTR temp = NULL;
  Student retVal;
  if (){
  	
  }
  return retVal;
}
void  filterDL            (Stack* mainStack, ClosedDictionary mainCD){
  int x;
  
  printf("\nFiltered all Dean's Listers into a stack.");
}
void  displayStack        (Stack*  main){
  printf("\n\nDetails of Stack (DEAN'S LISTERS)");
  printf("\nCount :: %d", main->stackCount);
  printf("\n-------------------------------------");
  if (main->stackCount > 0){
    printf("\n\n%-12s", "Student ID");
    printf("%-12s", "First Name");
    printf("%-12s", "Last Name");
    printf("%-12s", "Program");
    printf("%-12s", "GWA");
    printf("\n%-12s%-12s%-12s%-12s%-12.2s",
      "-----------",
      "-----------",
      "-----------",
      "-----------",
      "-----------"
    );
    
    // Start writing your code here.
    
  } else {
    printf("\nNothing to display from your stack.");
  }
} 

//* Problem 4 Functions
// The goal of problem 4 is to simply convert the data from the ClosedDictionary into a maxHeap, then display it. Priority number will be based on the student's GWA.

void  displayTree         (HeapPTR  main){
  
}
void  initHeap            (HeapPTR* main){
	
}
void insertIntoHeap		  (HeapPTR* main, Student newStudent){
	
}
void  populateHeap    (HeapPTR* mainHeap, ClosedDictionary* mainCD){
	
}
void  deleteMax           (HeapPTR* main)
void  convertIntoMaxHeap	(HeapPTR* main){
	
	printf("\n\nConverted into MaxHeap.");
}
void  displayHeap		(HeapPTR main){
	printf("\n\nDisplaying the heap...");
	int x;
	for (x = 0 ; x <= main->lastNdx ; x++){
		printf("\n%-12s%-12s%-12s%-12s%-12.2f",
			main->treeStudents[x].studentInfo.studentID,
			main->treeStudents[x].studentName.fName,
			main->treeStudents[x].studentName.lName,
			main->treeStudents[x].studentInfo.program,
			main->treeStudents[x].studentInfo.GWA
		);
	} 
}
