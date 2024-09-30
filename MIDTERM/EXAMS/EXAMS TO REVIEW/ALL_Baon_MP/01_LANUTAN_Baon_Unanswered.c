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
	

	//	Problem 4
	//	1) Declare and initialize your Open Dictionary.
	//	2) Using the function convertToOpenDict(), delete all contents inside the Heap while transferring/converting it into an Open Dictionary according to its hash ID.	
	

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
  
}
void initBST			(BST* main){

}
void populateBST		(BST* main){

}
char* getCourse			(unsigned char course){

}
void inOrder			(BST main){

}
void displayBST			(BST main){

}

//	Problem 2 Functions
char* findStudent		(unsigned short find, BST main){

}

//	Problem 3 Functions
void initHeap			(Heap* main){

}
void convertFILEtoPOT	(Heap* main){
	
}
void displayPOT			(Heap main){

}

//	Problem 4 Functions
void initOpenDict		(OpenDict* main){

}
int openHash			(char string[]){

}			
Student deletePoorest	(Heap* main){

}
void convertToOpenDict	(Heap* mainHeap, OpenDict* mainOpen){
	
}
void displayOpenDict	(OpenDict main);



