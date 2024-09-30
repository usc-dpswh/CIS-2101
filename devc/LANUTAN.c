#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define OPEN_SIZE 10
#define VH_SIZE 10

typedef struct {
	char studentID[16];
	char fName[16];
	char lName[16];
} Personal;

typedef struct node {
	Personal student;
	int next;
	struct node* link;
} *LL, NodeType;

//	VHeap
typedef struct heap {
	NodeType elem[VH_SIZE];
	int avail;
	int count;
} VHeap;

typedef struct {
	LL headers[OPEN_SIZE];
	int count;
} OpenDictionary;

//	VHeap Functions
void	initVH(VHeap* main, int* head);
int		allocSpace(VHeap* main);
void	deallocSpace(VHeap* main, int delete);
void	populateVHeap(VHeap* main, int* head);
void	displayVHeap(VHeap main, int head);

//	Open Dictionary Functions
void	initOD(OpenDictionary* main);
void	insertSorted(OpenDictionary* mainOD, Personal newStudent);
void	insertIntoVHeap(OpenDictionary* mainOD, VHeap* mainVH, int* head);
void	displayOD(OpenDictionary main);

int main(){
	//	Problem 1
	//	Populate the VHeap by using the given data.
	VHeap A;
	int headVH;
	initVH(&A, &headVH);
	populateVHeap(&A, &headVH);
	displayVHeap(A, headVH);
	
	//	Problem 2
	//	Fetch the data from VHeap then convert it into an OpenDictionary. Make sure it's sorted in ascending order according to studentID.	
	OpenDictionary B;
	initOD(&B);
	insertIntoVHeap(&B, &A, &headVH);
	displayOD(B);
	
	return 0;
}

//	VHeap Functions
void	initVH(VHeap* main, int* head){
	int x;
	for (x = -1 ; x < VH_SIZE-1 ; x++){
		main->elem[x+1].next = x;
	}
	main->avail = VH_SIZE-1;
	main->count = 0;
	*head = -1;
	printf("\nInitialized VHeap.");
}
int		allocSpace(VHeap* main){
	int retval = main->avail;
	if (retval != -1){
		main->avail = main->elem[retval].next;
	}
	return retval;
}
void	deallocSpace(VHeap* main, int delete){
	if (delete >= 0 && delete < VH_SIZE){
		main->elem[delete].next = main->avail;
		main->avail = delete;
	}
}
void	populateVHeap(VHeap* main, int* head){
	NodeType data[VH_SIZE] = {
    {{"22103514", "Achille", "Lanutan"}},
    {{"11600006", "Dianne",  "Yuvallos"}},
    {{"22103244", "Xander",  "Labide"}},
    {{"22103312", "Julz",    "Cortes"}},
    {{"22103110", "Karylle", "Bernate"}},
    {{"21102204", "Carlo",   "Juab"}},
    {{"22103277", "Jasper",  "Marbella"}},
    {{"22102001", "Gabriel", "dela Cruz"}},
    {{"22102003", "Sarah",   "Palabrica"}},
    {{"22102002", "Emma",    "Myers"}},
  };
  
  int x;
  int *trav;
  for (x = 0 ; x < VH_SIZE ; x++){
  	printf("\nline 91");
  	for (trav = head ; *trav != -1 ; trav = &main->elem[*trav].next){};
	int newNode = allocSpace(main);
	if (newNode != -1){
		printf("\n%d", newNode);
		main->elem[newNode] = data[x];
		main->elem[newNode].next = -1;
		*trav = newNode;
		main->count++;
		printf("\nInserted [%s]", data[x].student.studentID);
	} else {
		printf("\nVHeap has no more space.");
	}
  }
}
void	displayVHeap(VHeap main, int head){
	if (head != -1){
		printf("\n\nContents of VHeap...");
		printf("\n%-6s", "Index");
		printf("%-12s", "Student ID");
		printf("%-12s", "First name");
		printf("%-12s", "Last name");
		printf("\n%-6s", "------");
		printf("%-12s", "------------");
		printf("%-12s", "------------");
		printf("%-12s", "------------");
		int trav;
		for (trav = head ; trav != -1 ; trav = main.elem[trav].next){
			printf("\n%-6d%-12s%-12s%-12s",
				main.elem[trav].next,
				main.elem[trav].student.studentID,
				main.elem[trav].student.fName,
				main.elem[trav].student.lName
			);
		}
	}
}

//	Open Dictionary Functions
void	initOD(OpenDictionary* main){
	int x;
	for (x = 0 ; x < OPEN_SIZE ; x++){
		main->headers[x] = NULL;
	}
	main->count = 0;
	printf("\n\nInitialized open dictionary.");
}
int		hashOD(char string[]){
	int x, sum = 0;
	for (x = 0 ; string[x] != '\0' ; x++){
		sum = sum + string[x] - '0';
	}
	return sum % OPEN_SIZE;
}
void	insertSorted(OpenDictionary* mainOD, Personal newStudent){
	LL* trav;
	int hashval = hashOD(newStudent.studentID);
	for (trav = &mainOD->headers[hashval] ; *trav != NULL && strcmp(newStudent.studentID, (*trav)->student.studentID) > 0 ; trav = &(*trav)->link){};
	LL new = (LL)malloc(sizeof(struct node));
	if (new != NULL || strcmp(newStudent.studentID, (*trav)->student.studentID) != 0){
		new->student = newStudent;
		new->link = NULL;
		*trav = new;
		printf("\nInserted [%s] into open dictionary.", newStudent.studentID);
	}
}
void	insertIntoVHeap(OpenDictionary* mainOD, VHeap* mainVH, int* head){
	if (mainVH->count > 0){
		int* trav;
		int hashval;
		for (trav = head ; *trav != -1 ; trav = &mainVH->elem[*trav].next){
			insertSorted(mainOD, mainVH->elem[*trav].student);
		}
	} else {
		printf("\nelse 188");
	}
}

void	displayOD(OpenDictionary main){
	int x;
	LL trav;
	printf("\n\nContents of OpenDictionary...");
	for (x = 0 ; x < OPEN_SIZE ; x++){
		if (main.headers[x] != NULL){
			printf("\n%-6s", "Index");
			printf("%-12s", "Student ID");
			printf("%-12s", "First name");
			printf("%-12s", "Last name");
			printf("\n%-6s", "------");
			printf("%-12s", "------------");
			printf("%-12s", "------------");
			printf("%-12s\n", "------------");
		}
		for (trav = main.headers[x] ; trav != NULL ; trav = trav->link){
			printf("\n%-6d%-12s%-12s%-12s",
				x,
				trav->student.studentID,
				trav->student.fName,
				trav->student.lName
			);
		}
	}
}
	
