#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define HEAP_SIZE 10
#define STUDENT_SIZE 20


//	ARRAY OF STRUCTURES
//	Last index has -1

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
	printf("\n");
	displayBST(studentTree);
	

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
	Heap POT;
	initHeap(&POT);
	convertFILEtoPOT(&POT);
	displayPOT(POT);

	//	Problem 4
	//	1) Declare and initialize your Open Dictionary.
	//	2) Using the function convertToOpenDict(), delete all contents inside the Heap while transferring/converting it into an Open Dictionary according to its hash ID.	
	OpenDict Open;
	initOpenDict(&Open);
	convertToOpenDict(&POT, &Open);
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
  	//		src									dest
  	fwrite(data, sizeof(Student), STUDENT_SIZE, fp);
  	printf("\nGenerated successfully.");
  } else {
  	printf("\nGenerated unsuccessfully.");
  }
  fclose(fp);
}
void initBST			(BST* main){
	*main = NULL;
	printf("\nInitialized BST.");
}
void populateBST		(BST* main){
	BST* trav;
	Student temp;
	BST newStudent;
	
	FILE* fp = fopen("BAON_studentData.bin", "rb");
	if (fp != NULL){
		while(fread(&temp, sizeof(Student), 1, fp)){
			if (temp.info.baon >= 2500){
				for (trav = main ; *trav != NULL ; ){
					trav = (temp.info.baon < (*trav)->A.info.baon) ? &(*trav)->LC : &(*trav)->RC;
				}
				BST newStudent = (BST)malloc(sizeof(struct node));
				if (newStudent != NULL){
					newStudent->A.info	 = temp.info;
					newStudent->A.name	 = temp.name;
					newStudent->LC   	 = NULL;
					newStudent->RC   	 = NULL;
					*trav = newStudent;
					printf("\nInserted [%s] succesfully.", newStudent->A.name.fName);
				} else {
					printf("\nInsert unsuccessful.");
				}
			} 
		}
	}
	fclose(fp);
	printf("\nPopulated BST successfully.");
}
char* getCourse			(unsigned char course){
	char* retval = (char*)malloc(sizeof(char)*7);
	unsigned char mask = course & 0b11;
	if (retval != NULL){
		if (mask == 0b00){
			strcpy(retval, "BSIT");
		} else if (mask == 0b01){
			strcpy(retval, "BSCS");
		} else if (mask == 0b10){
			strcpy(retval, "BSIS");
		} else {
			strcpy(retval, "BSMATH");
		}
	}
	return retval;
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
	printf("\n\n%-12s%-12s%-12s%-12s%-12s",
		"Student ID",
		"First name",
		"Last name",
		"Course",
		"Baon"
	);
	printf("\n============================================================");
	inOrder(main);
}

//	Problem 2 Functions
char* findStudent		(unsigned short find, BST main){
	BST trav;
	char* retval = (char*)malloc(sizeof(char)*10);
	strcpy(retval, "XXXXXXXX");
	if (retval != NULL){
		for (trav = main ; trav != NULL && trav->A.info.baon != find ; ){
			trav = (find < trav->A.info.baon) ? trav->LC : trav->RC;
		}
		if (trav != NULL) {
            strcpy(retval, trav->A.info.studentID);
        }
	}
	return retval;
}

//	Problem 3 Functions
void initHeap			(Heap* main){
	main->lastNdx = -1;
	printf("\n\nInitialized heap.");
}
void convertFILEtoPOT	(Heap* main){
	Student temp;
	//	Open file
	FILE* fp = fopen("BAON_studentData.bin", "rb");
	if (fp != NULL){
		while(fread(&temp, sizeof(Student), 1, fp)){
			int currNdx;
			main->lastNdx++;
			if (main->lastNdx < HEAP_SIZE){
				currNdx = main->lastNdx;
				main->studentTree[currNdx] = temp;
				while (currNdx > 0 && main->studentTree[(currNdx - 1)/2].info.baon > temp.info.baon){
					main->studentTree[currNdx] = main->studentTree[(currNdx-1)/2];
					currNdx = (currNdx - 1)/2;
				}
				main->studentTree[currNdx] = temp;
				printf("\nInserted into POT [%s]", temp.name.fName);
			}
		}
	}
	fclose(fp);
}
void displayPOT			(Heap main){
	printf("\n\n%-12s%-12s%-12s%-12s%-12s",
		"Student ID",
		"First name",
		"Last name",
		"Course",
		"Baon"
	);
	printf("\n============================================================");
	
	int x;
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
}
int openHash			(char string[]){
	int x, sum = 0;
	for (x = 0 ; string[x] != '\0' ; x++){
		sum += string[x] - '0';
	}
	return sum % HEAP_SIZE;
}			
Student deletePoorest	(Heap* main){
	int trav, parNdx, childNdx;
	Student temp, min;
	strcpy(min.info.studentID, "XXXXXXXX");
	if (main->lastNdx != -1){
		parNdx = 0;
		childNdx = 1;
		min = main->studentTree[0];
		main->studentTree[0] = main->studentTree[main->lastNdx];
		main->lastNdx--;
		
		while (childNdx <= main->lastNdx){
			if (childNdx + 1 <= main->lastNdx && main->studentTree[childNdx].info.baon < main->studentTree[childNdx + 1].info.baon){
				childNdx += 1;
			}
			if (main->studentTree[parNdx].info.baon > main->studentTree[childNdx].info.baon){
				temp = main->studentTree[parNdx];
				main->studentTree[parNdx] = main->studentTree[childNdx];
				main->studentTree[childNdx] = temp;
				parNdx = childNdx;
				childNdx = (childNdx * 2)+1;
			} else {
				childNdx = main->lastNdx + 1;
			}
		}
	}
	return min;
}
void convertToOpenDict	(Heap* mainHeap, OpenDict* mainOpen){
	while (mainHeap->lastNdx != -1){
		Student newStudent = deletePoorest(mainHeap);
		int hashVal = openHash(newStudent.info.studentID);
		StudentPTR* trav;
		if (strcmp(newStudent.info.studentID, "XXXXXXXX") != 0){
			for (trav = &mainOpen->students[hashVal] ; *trav != NULL ; trav = &(*trav)->next){};
			StudentPTR newNode = (StudentPTR)malloc(sizeof(struct LL));
			if (newNode != NULL){
				newNode->A = newStudent;
				newNode->next = NULL;
				*trav = newNode;
				printf("\nInserted into open dictionary.");
			}		
		}
	}
	printf("\nConverted to Open Dictionary.");
}
void displayOpenDict	(OpenDict main);



