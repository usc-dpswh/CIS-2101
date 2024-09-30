#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define HEAP_SIZE 10
#define STUDENT_SIZE 20


//	ARRAY OF STRUCTURES

typedef struct {
	char fName[16];
	char lName[16];
} Personal;

typedef unsigned char binaryCourse;
typedef unsigned short binaryBaon;

typedef struct {
	char 			studentID[16];
	binaryCourse 	course;				// 00 - IT, 01 - CS, 10 - IS, 11 - MATH
	binaryBaon 		baon;				// Baon (money they have for snacks in school) is represented in binary
} School;

typedef struct {
	Personal 		name;
	School 			info;
} Student;

//	BST

typedef struct node {
	Student			A;
	struct node* 	LC;
	struct node* 	RC;
} *BST;

//	POT

typedef struct heap{
	Student 		studentTree[HEAP_SIZE];
	int 			lastNdx;
} Heap;

//	Open Dict

typedef struct LL {
	Student A;
	struct LL* next;
} *StudentPTR;

typedef struct open {
	StudentPTR students[HEAP_SIZE];
} OpenDict;

// 	Problem 1 Functions
void generateStudentData(void);
void initBST			(BST* main);
void populateBST		(BST* main);
char* getCourse			(unsigned char course);
void inOrder			(BST main);
void displayBST			(BST main);

//	Problem 2 Functions
char* findStudent		(unsigned short find, BST main);

//	Problem 3 Functions
void initHeap			(Heap* main);
void convertFILEtoPOT	(Heap* main);
void displayPOT			(Heap main);

//	Problem 4 Functions
void initOpenDict		(OpenDict* main);
Student deletePoorest	(Heap* main);
void convertToOpenDict	(Heap* mainHeap, OpenDict* mainOpen);

int main(){
	
	//	Problem 1
	//	The goal of Problem 1 is to insert all data from the file students that have a Baon of 2500+ into a BST
	//	1) Declare and initialize BST.
	//	2) Generate student data.
	//	3) Using the student data generated, populate the BST with only students that have a Baon exceeding 2,500php.
	//	4) Display the data in the BST in inOrder.
	BST studentTree;
	initBST(&studentTree);
	generateStudentData();
	populateBST(&studentTree);
	displayBST(studentTree);
//	inOrder(A);
	

	//	Problem 2
	//	The goal is to find a student with a particular amount of Baon and delete it. If the student is found, return its ID else return "XXXXXXXX"
	//	1)	Test the function findStudent(). printf()
	printf("\n");
	printf("\nfindStudent = %s", findStudent(2600, studentTree));
	printf("\nfindStudent = %s", findStudent(300, studentTree));

	//	Problem 3
	//	The goal is to convert all data from FILE into POT (minHeap) according to its Baon.
	//	1) Convert the FILE into POT.
	//	2) Display the POT.
	Heap B;
	initHeap(&B);
	convertFILEtoPOT(&B);
	displayPOT(B);
	

	//	Problem 4
	//	1) Declare and initialize your Open Dictionary.
	//	2) Using the function convertToOpenDict(), delete all contents inside the Heap while transferring/converting it into an Open Dictionary according to its hash ID.	
	OpenDict C;
	initOpenDict(&C);
	convertToOpenDict(&B, &C);
	
	return 0;
}

// 	Problem 1 Functions
void generateStudentData(void){
	Student data[STUDENT_SIZE] = {
	    {{"John",      "Doe"},         {"22103514", 0b00, 1500}},
	    {{"Jane",      "Smith"},       {"22103841", 0b01, 3000}},
	    {{"Alice",     "Johnson"},     {"22102001", 0b10, 2500}},
	    {{"Bob",       "Williams"},    {"22101322", 0b11, 1200}},
	    {{"Michael",   "Brown"},       {"22100923", 0b00, 2700}},
	    {{"Emily",     "Jones"},       {"22109523", 0b01, 2800}},
	    {{"David",     "Garcia"},      {"22104953", 0b10, 1600}},
	    {{"Sarah",     "Martinez"},    {"22109999", 0b11, 2900}},
	    {{"James",     "Hernandez"},   {"22103222", 0b00, 1100}},
	    {{"Emma",      "Lopez"},       {"22100098", 0b01, 800}},
	    {{"Matthew",   "Gonzalez"},    {"22100012", 0b10, 1000}},
	    {{"Olivia",    "Wilson"},      {"22106565", 0b11, 3300}},
	    {{"Daniel",    "Taylor"},      {"22108721", 0b00, 2600}},
	    {{"Chloe",     "Anderson"},    {"22100090", 0b01, 2800}},
	    {{"Christopher","Thomas"},     {"22102322", 0b10, 2700}},
	    {{"Ava",       "Moore"},       {"22108888", 0b11, 5000}},
	    {{"Andrew",    "Jackson"},     {"22100901", 0b00, 50}},
	    {{"Ella",      "White"},       {"22105990", 0b01, 1600}},
	    {{"Joshua",    "Harris"},      {"22105012", 0b10, 1800}},
	    {{"Sophia",    "Clark"},       {"22109011", 0b11, 1900}},
	};

	FILE *fp = fopen("BAON_studentData.bin", "wb");
	// Start writing your code here.
	if (fp != NULL){
		fwrite(data, sizeof(Student), STUDENT_SIZE, fp);
		printf("\nGenerated student data.");
	}
  	fclose(fp);
}
void initBST			(BST* main){
	*main = NULL;
	printf("\nInitialized BST.");
}
void populateBST		(BST* main){
	BST newStudent;
	Student temp;
	BST* trav = NULL;
	FILE* fp = NULL;
	
	fp = fopen("BAON_studentData.bin", "rb");
	if (fp != NULL){
		while (fread(&temp, sizeof(Student), 1, fp)){
			if (temp.info.baon >= 2500){
				for (trav = main ; *trav != NULL ; ){
					trav = (temp.info.baon < (*trav)->A.info.baon) ? &(*trav)->LC : &(*trav)->RC;
				}
				newStudent = (BST)malloc(sizeof(struct node));
				if (newStudent != NULL){
					newStudent->A = temp;
					newStudent->LC = NULL;
					newStudent->RC = NULL;
					*trav = newStudent;
					printf("\nInserted student [%s] with Baon [%d]", newStudent->A.info.studentID, newStudent->A.info.baon);
				}
			}
		}
	}
	fclose(fp);
}
char* getCourse			(unsigned char course){
	char* temp = (char*)malloc(sizeof(char) * 6); // variable to store the string
	unsigned char mask = course & 0b11; // mask to get the bits for the course
	if (temp != NULL){ // store the resulting bits to temp
		if (mask == 0b00){
			strcpy(temp, "IT");
		} else if (mask == 0b01){
			strcpy(temp, "CS");
		} else if (mask == 0b10){
			strcpy(temp, "IS");
		} else {
			strcpy(temp, "MATH");
		}
	}
	return temp;
}
void inOrder			(BST main){	
	if (main != NULL){
		inOrder(main->LC);
		printf("\n%-12s%-12s%-12s%-12s%-12hu",
			main->A.info.studentID,
			main->A.name.fName,
			main->A.name.lName,
			getCourse(main->A.info.course),
			main->A.info.baon
		);
		inOrder(main->RC);
	}
}
void displayBST			(BST main){
	printf("\n\nStudents with Baon greater than 2500 ::");
	printf("\n%-12s%-12s%-12s%-12s%-12s",
		"ID Number",
		"First Name",
		"Last Name",
		"Course",
		"Baon"
	);
	printf("\n==========================================================");
	inOrder(main);
}

//	Problem 2 Functions
char* findStudent		(unsigned short find, BST main){
	char* retval = (char*)malloc(sizeof(char) * 9);
	strcpy(retval, "XXXXXXXX");
	BST trav = NULL;
	
	if (main != NULL){
		for (trav = main ; trav != NULL && trav->A.info.baon != find; ){
			trav = (find < trav->A.info.baon) ? trav->LC : trav->RC;
//			printf("\n%s", trav->A.info.studentID);
		}
		if (trav != NULL){
			strcpy(retval, trav->A.info.studentID);
		}
	}
	
	return retval;
}

//	Problem 3 Functions
void initHeap			(Heap* main){
	int x;
	for (x = 0 ; x < HEAP_SIZE ; x++){
		strcpy(main->studentTree[x].info.studentID, "XXXXXXXX");
	}
	main->lastNdx = -1;
	printf("\nInitialized Heap.");
}
void convertFILEtoPOT	(Heap* main){
	FILE* fp = fopen("BAON_studentData.bin", "rb");
	Student newStudent;
	int currNdx;
	
	if (fp != NULL){
		while (fread(&newStudent, sizeof(Student), 1, fp)){
			main->lastNdx++;
			if (main->lastNdx < HEAP_SIZE){
				currNdx = main->lastNdx;
				main->studentTree[currNdx] = newStudent;
				
				while (currNdx > 0 && main->studentTree[(currNdx - 1)/2].info.baon > newStudent.info.baon){
					main->studentTree[currNdx] = main->studentTree[(currNdx - 1)/2];
					currNdx = (currNdx - 1)/2;
				}
				main->studentTree[currNdx] = newStudent;
				printf("\nInserted [%s] into MinHeap.", newStudent.info.studentID);
			}
		}
		printf("\nSuccessfully converted FILE to POT.");
	} else {
		printf("\nThere was an error in opening the file.");
	}
	fclose(fp);
}
void displayPOT			(Heap main){
	printf("\n\nStudents with Baon greater than 2500 ::");
	printf("\n%-12s%-12s%-12s%-12s%-12s",
		"ID Number",
		"First Name",
		"Last Name",
		"Course",
		"Baon"
	);
	printf("\n==========================================================");
	
	int x = 0;
	for (x = 0 ; x < HEAP_SIZE ; x++){
		printf("\n%-12s%-12s%-12s%-12s%-12hu",
			main.studentTree[x].info.studentID,
			main.studentTree[x].name.fName,
			main.studentTree[x].name.lName,
			getCourse(main.studentTree[x].info.course),
			main.studentTree[x].info.baon
		);
	}
}

//	Problem 4 Functions
void initOpenDict		(OpenDict* main){
	int x;
	for (x = 0 ; x < HEAP_SIZE ; x++){
		main->students[x] = NULL;
	}
	printf("\n\nInitialized Open Dictionary.");
}
int openHash			(char string[]){
	int x;
	int hashVal = 0;
	for (x = 0 ; string[x] != '\0' ; x++){
		hashVal = hashVal + string[x] - '0';
	}
	hashVal = hashVal % HEAP_SIZE;
	printf("\n%d", hashVal);
	return hashVal;
}			
Student deletePoorest	(Heap* main){
	Student min, temp;
	int parent, child;
	
	if (main->lastNdx != -1){
		min = main->studentTree[0];
		main->studentTree[0] = main->studentTree[main->lastNdx];
		main->lastNdx--;
		parent = 0;
		child = 1;
		
		while (child <= main->lastNdx){
			if (child + 1 <= main->lastNdx && main->studentTree[child + 1].info.baon < main->studentTree[child].info.baon){
				child += 1;
			}
			if (main->studentTree[parent].info.baon > main->studentTree[child].info.baon){
				temp = main->studentTree[parent];
				main->studentTree[parent] = main->studentTree[child];
				main->studentTree[child] = temp;
				parent = child;
				child = (child * 2) + 1;
				printf("\nDeleted current poorest student [%s]", min.info.studentID);
			} else {
				child = main->lastNdx + 1;
			}
		}
	} else {
		printf("\nNothing to delete inside your MinHeap.");
	}
	return min;
}
void convertToOpenDict	(Heap* mainHeap, OpenDict* mainOpen){
	printf("\n\nConverting from MinHeap to Open Dictionary.");
	Student deletedStudent;
	StudentPTR* trav = NULL;
	StudentPTR newStudent = NULL;
	int x, hashVal;
	
	for (x = 0 ; x < mainHeap->lastNdx ; x++){
		deletedStudent = deletePoorest(mainHeap);
//		printf("\nDeleted student %s", deletedStudent.info.studentID);
		hashVal = openHash(deletedStudent.info.studentID);
		printf("\n%d hashval", hashVal);
		for (trav = &mainOpen->students[hashVal] ; *trav != NULL && deletedStudent.info.baon > (*trav)->A.info.baon ; trav = &(*trav)->next){};
		
		if (*trav == NULL || deletedStudent.info.baon < (*trav)->A.info.baon){
			newStudent = (StudentPTR)malloc(sizeof(struct LL));
			if (newStudent != NULL){
				newStudent->A = deletedStudent;
				newStudent->next = *trav;
				*trav = newStudent;
				printf("\nInserted student [%s] into Open Dictionary.", newStudent->A.info.studentID);
			}
		}
	}
}
void displayOpenDict	(OpenDict main){
	
}



