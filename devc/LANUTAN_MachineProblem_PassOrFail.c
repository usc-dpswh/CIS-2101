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
// Stores ALL student information.
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
  // 3) Display the stack.

  // Start writing your code here //
  Stack D;
  initStack(&D);
  filterDL(&D, B);
  displayStack(&D);


  //* Problem 4
  // 1) Declare and then initialize a variable HeapPTR
  // 2) Convert the data from the open dictionary into a maxHeap.
  // 3) Display the tree.
  // 4) Call deleteMax()
  // 5) Verify the deleted student by displaying the tree again.

  // Start writing your code here //
  HeapPTR E;
  initHeap(&E);
  populateHeap(&E, &B);
  displayHeap(E);
  convertIntoMaxHeap(&E);
  displayHeap(E);
  
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
  return new;
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
    for (x = 0 ; x < main.count ; x++){
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
            mainOD->openDCount++;
          }
        }
      } 
      // else {
      //   printf("\n[%s] is not a failing student.", mainCD->studentsCDict[x].studentInfo.studentID);
      // }
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
        printf("%s[%.2f] :: ", trav->studentInfo.studentID, trav->studentInfo.GWA);
      }
    }
  } else {
    printf("\nYour OpenDictionary is empty.");
  }
}

//* Problem 3 Functions
// The goal of problem 3 is to filter out Dean's Listers (students who have a GWA < 1.71) from the closed dictionary and store it into the stack.

void  initStack           (Stack* mainStack){
  mainStack->top = NULL;
  mainStack->stackCount = 0;
}
void  push                (Stack* mainStack, Student newData){
  StudentPTR newStudent = (StudentPTR)malloc(sizeof(struct node));
  if (newStudent != NULL){
    	newStudent->studentInfo = newData.studentInfo;
    	newStudent->studentName = newData.studentName;
    	newStudent->next 		= mainStack->top;
    	mainStack->top		 	= newStudent;
    	mainStack->stackCount++;
//    	printf("\nInserted [%s] into stack.", newStudent->studentInfo.studentID);
	}
}
Student pop               (Stack* mainStack) {
  StudentPTR temp = NULL;
  Student retVal;
  if (mainStack->top != NULL){
  	temp = mainStack->top;
  	retVal.studentInfo = temp->studentInfo;
  	retVal.studentName = temp->studentName;
	mainStack->top 	= temp->next;
	mainStack->stackCount--;
//	printf("Popped.");
  }
  return retVal;
}
void  filterDL            (Stack* mainStack, ClosedDictionary mainCD){
  int x;
  for (x = 0 ; x < CLOSE_SIZE ; x++){
    if (mainCD.studentsCDict[x].studentInfo.GWA < 1.71 && mainCD.studentsCDict[x].studentInfo.GWA >= 1.0){
      push(mainStack, mainCD.studentsCDict[x]);
    } 
  }
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
    Stack tempStack;
    StudentPTR tempStudent;
    initStack(&tempStack);
    
    while (main->top != NULL){
//    	printf("\nLINE 477");
    	Student newStudent;
    	newStudent = pop(main);
    	main->stackCount--;
    	push(&tempStack, newStudent);
    	printf("\n%-12s%-12s%-12s%-12s%-12.2f",
			tempStack.top->studentInfo.studentID,
			tempStack.top->studentName.fName,
			tempStack.top->studentName.lName,
			tempStack.top->studentInfo.program,
			tempStack.top->studentInfo.GWA
		);
	}
    
  } else {
    printf("\nNothing to display from your stack.");
  }
} 

//* Problem 4 Functions
// The goal of problem 4 is to simply convert the data from the ClosedDictionary into a maxHeap, then display it. Priority number will be based on the student's GWA.

void  displayTree         (HeapPTR  main){
  if (main->lastNdx != -1){
    int x;
    for (x = 0 ; x <= main->lastNdx ; x++){
      printf("%d -> ", main->treeStudents[x]);
    }
  }
  printf("\n");
}
void  initHeap            (HeapPTR* main){
	*main = (HeapPTR)malloc(sizeof(struct heap));
	if (*main != NULL){
	  (*main)->lastNdx = -1;
	  printf("\nInitialized Tree Heap.");
	}
}
void insertIntoHeap		  (HeapPTR* main, Student newStudent){
	int currNdx;
	if ((*main)->lastNdx < SIZE && strcmp(newStudent.studentInfo.studentID, DELETED) != 0){
		(*main)->lastNdx++;
		currNdx = (*main)->lastNdx;
		(*main)->treeStudents[currNdx] = newStudent;
		
		while (currNdx > 0 && (*main)->treeStudents[(currNdx - 1)/2].studentInfo.GWA > newStudent.studentInfo.GWA){
			(*main)->treeStudents[currNdx] = (*main)->treeStudents[(currNdx - 1)/2];
			currNdx = (currNdx - 1) / 2;
		}
		(*main)->treeStudents[currNdx] = newStudent;
//		printf("\nSuccessfully inserted [%s]", newStudent.studentInfo.studentID);
	} else {
		printf("\nNo space left to insert.");
	}
}
void  populateHeap    (HeapPTR* mainHeap, ClosedDictionary* mainCD){
	if (mainCD->count > 0){
		int x;
		for (x = 0 ; x < mainCD->count ; x++){
			insertIntoHeap(mainHeap, mainCD->studentsCDict[x]);
		}
	}
}
//void  deleteMax           (HeapPTR* main)
void  convertIntoMaxHeap	(HeapPTR* main){
	int trav, parNdx, childNdx;
	Student temp;
	parNdx = ((*main)->lastNdx - 1)/2;
	childNdx = (parNdx * 2)+1;
	trav = parNdx;
	
	while (parNdx >= 0){
		while (childNdx <= (*main)->lastNdx){
			if (childNdx + 1 <= (*main)->lastNdx && (*main)->treeStudents[childNdx + 1].studentInfo.GWA > (*main)->treeStudents[childNdx].studentInfo.GWA){
				childNdx += 1;
			}
			if ((*main)->treeStudents[trav].studentInfo.GWA < (*main)->treeStudents[childNdx].studentInfo.GWA){
				temp = (*main)->treeStudents[trav];
				(*main)->treeStudents[trav] = (*main)->treeStudents[childNdx];
				(*main)->treeStudents[childNdx] = temp;
				trav = childNdx;
				childNdx = (childNdx * 2)+1;
			} else {
				childNdx = (*main)->lastNdx + 1;
			}
		}
		parNdx--;
		trav = parNdx;
		childNdx = (parNdx * 2)+1;
	}
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
