#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define VH_SIZE 0XC     // size of Virtual Heap
#define ARRAY_SIZE 0XE   // size of the array implementation of List
#define CLOSE_DSIZE 0XB // size of Close Dictionary

/******************************************************************************
* Data Structure Definition:                                                  *
******************************************************************************/
typedef struct {
	char model[30];
	char manufacturer[40]; // Airbus, Textron Aviation, Boeing
	int passengerCount;
	int year;
} planeDesc;

typedef struct {
	char planeID[8];
	planeDesc planeInfo;
	float planePrice;
	int maxSpeed;
} Aircraft;

typedef struct {
	Aircraft data;
	int next;
} PlaneNode;

/************************
* Virtual Heap          *
************************/
typedef struct {
	PlaneNode VH_Node[VH_SIZE];
	int avail;
} VHeap;

/******************************************
* Cursor-Based Implementation of LIST     *
******************************************/
typedef struct CList {
	int elemIndex; // index of the 1st element in the set
	int count;     // holds the actual number of elements in the list
	VHeap *VHptr;  // holds the pointer to the virtual heap
}*CursorList;

/******************************************
* Array Implementation of LIST  		  *
******************************************/
typedef struct ArrList {
	Aircraft data[ARRAY_SIZE];
	int count; // holds the actual number of elements in the list
}*ArrayList;


typedef struct node {
	Aircraft elem;
	struct node *link;
}*LinkedList;

/******************************************
* Linked List Implementation of QUEUE 	  *
******************************************/
typedef struct {
	LinkedList front;
	LinkedList rear;
} LinkedQueue;

/**********************************************
* Closed Hashing with 2 pass loading          *
**********************************************/
#define EMPTY "emp" // stored in product ID field
#define DELETED "del" // stored in product ID field *

typedef Aircraft CloseDic[CLOSE_DSIZE]; // Definition of the closed hash dictionary

/**********************************************************
* Function Prototypes                                    *
*********************************************************/
//---Problem #1 ---
void initVHeap(VHeap *VH);
CursorList initCursorList(VHeap *VH);
ArrayList initArrayList();
void displayVHeap(VHeap V);
void displayArrayList(ArrayList A);
void displayCursorList(CursorList C);

//---Problem #2 ---
void populateArrayList(ArrayList *A);
int populateCListSorted(ArrayList *A, CursorList *C);
int allocSpace(VHeap *VH);

//---Problem #3 ---
void initQueue(LinkedQueue *Q);
void freeSpace(VHeap *VH, int ndx);
void enqueueFromCList(LinkedQueue *Q, CursorList *C);

//---Problem #4 ---
int closeHash(char ID[]);
void initCloseDic(CloseDic CD);
Aircraft dequeue(LinkedQueue *Q);
CloseDic *convertToCloseDic(LinkedQueue *Q);
void displayCloseDic(CloseDic CD);

int main() {
	// Variable Declaration for all problems here


	/*--------------------------------------------------------------------------------------------
	* 	Problem #1 ::  1) Initializes the virtual heap, the array list and the cursor list        *
	*                  2) Displays the contents virtual heap, the array list and the cursor list  *
	*---------------------------------------------------------------------------------------------*/
	printf("\n\n\nProblem #1:: ");
	printf("\n------------");
	// Write the necessary functions for the problem here
	VHeap head;
	initVHeap(&head);

	CursorList cList = initCursorList(&head);


	ArrayList aList = initArrayList();

	displayVHeap(head);
	displayArrayList(aList);
	displayCursorList(cList);



	printf("\n\n");
	// system("pause");
	// system("cls");

	/*--------------------------------------------------------------------------------------------
	* 	Problem #2 ::  1) Populates and displays the array list  						          *
	*                  2) Populates the cursor list which is sorted in ascending order according  *
	*                     to ID from a given array list. Inserts the data if the Aircraft was     *
	*                     manufactured by Airbus or Textron Aviation                              *
	*                  3) Displays the virtual heap, the cursor list and the array list again     *
	*                     after transfering the data to the cursor list                           *
	*---------------------------------------------------------------------------------------------*/
	printf("\n\n\nProblem #2:: ");
	printf("\n------------");
	// Write the necessary functions for the problem here
	populateArrayList(&aList);
	displayArrayList(aList);
	int cursorCount = populateCListSorted(&aList, &cList);
	displayVHeap(head);
	displayArrayList(aList);
	displayCursorList(cList);


	printf("\n\n");
	// system("pause");
	// system("cls");

	/*--------------------------------------------------------------------------------------------
	* 	Problem #3 ::  1) Initializes the queue                                                   *
	*                  2) Transfers the data from the cursor list to a queue                      *
	*                  3) Displays the empty cursor list and virtual heap                         *
	*---------------------------------------------------------------------------------------------*/
	printf("\n\n\nProblem #3:: ");
	printf("\n------------");
	// Write the necessary functions for the problem here
	LinkedQueue LQ;
	initQueue(&LQ);
	enqueueFromCList(&LQ, &cList);
	displayCursorList(cList);
	displayVHeap(head);



	printf("\n\n");
	// system("pause");
	// system("cls");

	/*--------------------------------------------------------------------------------------------
	* 	Problem #4 ::  1) Empties the queue and transfers all of its data to a close hash         *
	*                     dictionary                                                              *
	*                  2) Displays the close hash dictionary                                      *
	*---------------------------------------------------------------------------------------------*/
	printf("\n\n\nProblem #4:: ");
	printf("\n------------");
	// Write the necessary functions for the problem here
	CloseDic *CD = convertToCloseDic(&LQ);
	displayCloseDic(*CD);




	return 0;
}

/************************************************************
 *  Problem 1:: Function Definitions                        *
 ************************************************************/
void initVHeap(VHeap *VH) {
	// Write your code here!!
	int i;
	int size = VH_SIZE - 1;
	for(i = -1; i < size; i++) {
		strcpy(VH->VH_Node[i+1].data.planeID, " ");
		VH->VH_Node[i + 1].next = i;
	}
	VH->avail = size;
}
CursorList initCursorList(VHeap *VH) {
	// Write your code here!!

	CursorList retval = (CursorList)malloc(sizeof(struct CList));
	retval->count = 0;
	retval->elemIndex = -1;
	retval->VHptr = VH;

	return retval;

}
ArrayList initArrayList() {
	// Write your code here!!

	ArrayList retval = (ArrayList)malloc(sizeof(struct ArrList));
	retval->count = 0;

	return retval;

}

void displayVHeap(VHeap VH) {
	// Variable Declaration here!!

	printf("\n\nDetails of the Virtual Heap :: ");
	printf("\n------------------------------");
	printf("\nAvailable Index  ::  %d", VH.avail);
	printf("\nVHeap Address    ::  %x", VH);
	printf("\n\n%10s", "Index");
	printf("%10s", "Plane ID");
	printf("%15s", "Next Field");
	printf("\n%10s%10s%15s", "-----", "-------", "----------");

	// Write your code here!!
	int i;
	for(i = 0; i < VH_SIZE; i++) {
		printf("\n%10d%10s%15d", i, VH.VH_Node[i].data.planeID, VH.VH_Node[i].next);
	}

}
void displayArrayList(ArrayList A) {
	// Variable Declaration here!!

	printf("\n\nDetails of the Array List :: ");
	printf("\n---------------------");
	printf("\nNo. of Elements :: %d", A->count);
	printf("\n\n%-8s", "Index");
	printf("%-9s", "ID");
	printf("%-15s", "Plane Model");
	printf("%-25s", "Plane Manufacturer");
	printf("\n%-7s%-10s%-15s%-25s", "-----", "-----", "-----------", "------------------");

	// Write your code here!!
	int i;
	for(i = 0; i < A->count; i++) {
		printf("\n%-8d%-9s%-15s%-25s", i, A->data[i].planeID, A->data[i].planeInfo.model, A->data[i].planeInfo.manufacturer);
	}

}
void displayCursorList(CursorList C) {
	// Variable Declaration here!!

	printf("\n\nDetails of the Cursor List :: ");
	printf("\n---------------------");
	printf("\nNo. of Elements :: %d", C->count);
	printf("\n\n%-7s", "ID");
	printf("%-15s", "Plane Model");
	printf("%-25s", "Plane Manufacturer");
	printf("%-10s", "VHeap Index");
	printf("\n%-7s%-15s%-25s%-10s", "--", "----------", "------------------",
	       "-----------");
	// Write your code here!!
	int i;
	for(i = C->elemIndex; i != -1; i = C->VHptr->VH_Node[i].next) {
		printf("\n%-7s%-15s%-25s%-10d", C->VHptr->VH_Node[i].data.planeID, C->VHptr->VH_Node[i].data.planeInfo.model, C->VHptr->VH_Node[i].data.planeInfo.manufacturer, i);
	}

}

/************************************************************
 *  Problem 2:: Function Definitions                        *
 ************************************************************/
void populateArrayList(ArrayList *A) {
	int COUNT = 15;
	Aircraft data[] = {{"17839",{"A330", "Airbus", 150, 2012}, 300000, 250},
		{"18367",{"737 MAX", "Boeing", 200, 2021}, 150000, 275},
		{"23748",{"BBJ", "Boeing", 175, 2020}, 275000, 290},
		{"16790",{"Caravan", "Textron Aviation", 100, 2017}, 125000, 315},
		{"17489",{"A350", "Airbus", 175, 2020}, 310000, 270},
		{"17839",{"A400M", "Airbus", 140, 2013}, 175000, 220},
		{"16778",{"Caravan", "Textron Aviation", 140, 2018}, 165000, 310},
		{"23748",{"300F", "Boeing", 180, 2022}, 140000, 250},
		{"17888",{"Beechcraft", "Textron Aviation", 175, 2019}, 180000, 220},
		{"13435",{"BBJ", "Boeing", 190, 2021}, 180000, 280},
		{"15049",{"Denali", "Textron Aviation", 205, 2017}, 190000, 230},
		{"17888",{"A330", "Airbus", 180, 2021}, 290000, 200},
		{"18367",{"KC-767", "Boeing", 200, 2022}, 220000, 240},
		{"16790",{"737 MAX", "Boeing", 340, 2023}, 430000, 220},
		{"23929",{"A400M", "Airbus", 300, 2019}, 300000, 340}
	};

	// Inserts each element of the array to the array list
	// Write your code here!!
	int i;
	for(i = 0; i < ARRAY_SIZE; i++) {
		(*A)->data[(*A)->count] = data[i];
		(*A)->count++;
	}

}

int populateCListSorted(ArrayList *A, CursorList *C) {
	// Write your code here!!
	int i, j;
	int *trav;
	for(i = 0; i < ARRAY_SIZE;) {
		for(trav = &(*C)->elemIndex; *trav != -1 && strcmp((*C)->VHptr->VH_Node[*trav].data.planeID, (*A)->data[i].planeID) < 0 && strcmp((*C)->VHptr->VH_Node[*trav].data.planeID, (*A)->data[i].planeID) != 0; trav = &(*C)->VHptr->VH_Node[*trav].next) {}
		if(strcmp((*A)->data[i].planeInfo.manufacturer, "Airbus") == 0 || strcmp((*A)->data[i].planeInfo.manufacturer, "Textron Aviation") == 0) {
			int index = allocSpace((*C)->VHptr);
			if(index != -1) {
				(*C)->VHptr->VH_Node[index].data = (*A)->data[i];
				(*C)->VHptr->VH_Node[index].next = *trav;
				*trav = index;
				(*C)->count++;
				(*A)->count--;
				for(j = i; j < (*A)->count; j++) {
					(*A)->data[j] = (*A)->data[j+1];
				}
			}
		} else {
			i++;
		}
	}
	return (*C)->count;
}
int allocSpace(VHeap *VH) {
	// Write your code here!!
	int retval = VH->avail;
	if(retval != -1) {
		VH->avail = VH->VH_Node[retval].next;
	}
	return retval;

}

/************************************************************
 *  Problem 3:: Function Definitions                        *
 ************************************************************/
void initQueue(LinkedQueue *Q) {
	// Write your code here!!
	Q->front = NULL;
	Q->rear = NULL;

}
void freeSpace(VHeap *VH, int ndx) {
	// Write your code here!!
	if(ndx > -1 && ndx < VH_SIZE) {
		strcpy(VH->VH_Node[ndx].data.planeID, " ");
		VH->VH_Node[ndx].next = VH->avail;
		VH->avail = ndx;
	}
}
void enqueueFromCList(LinkedQueue *Q, CursorList *C) {
	// Write your code here!!
	int *i, index;

	for(i = &(*C)->elemIndex; *i != -1;) {
		index = *i;
		*i = (*C)->VHptr->VH_Node[index].next;
		LinkedList temp = (LinkedList)malloc(sizeof(struct node));
		if(temp != NULL) {
			temp->elem = (*C)->VHptr->VH_Node[index].data;
			temp->link = NULL;
			if(Q->front == NULL) {
				Q->front = temp;
			} else {
				Q->rear->link = temp;
			}
			Q->rear = temp;
		}
		freeSpace((*C)->VHptr, index);
		(*C)->count--;
	}
	LinkedList trav;
	int count = 0;
	for(trav = Q->front; trav != NULL; trav = trav->link) {
		count++;
	}
	printf("\n%d\n", count);
}

/************************************************************
 *  Problem 4:: Function Definitions                        *
 ************************************************************/
int closeHash(char ID[]) {
	// Write your code here!!
	int retval = 0, i;
	for(i = 0; ID[i] != '\0'; i++) {
		if(ID[i] >= '0' && ID[i] <= '9') {
			retval += ID[i] - '0';
		}
	}
	return retval % CLOSE_DSIZE;

}

void initCloseDic(CloseDic CD) {
	// Write your code here!!
	int i = 0;
	for(i = 0; i < CLOSE_DSIZE; i++) {
		strcpy(CD[i].planeID, EMPTY);
		strcpy(CD[i].planeInfo.model, " ");
	}

}

Aircraft dequeue(LinkedQueue *Q) {
	// Write your code here!!
	Aircraft retval;
	LinkedList temp;
	if(Q->front != NULL) {
		temp = Q->front;
		Q->front = Q->front->link;
		if(Q->front == NULL) {
			Q->rear = NULL;
		}
		retval = temp->elem;
		free(temp);
	}
	return retval;
}

CloseDic *convertToCloseDic(LinkedQueue *Q) {
	// Write your code here!!
	Aircraft temp;
	CloseDic *retval = (CloseDic*)malloc(sizeof(CloseDic));
	initCloseDic(*retval);
	ArrayList tempList = initArrayList();
	int i, hash, trav, dupe;
	while(Q->front != NULL) {
		temp = dequeue(Q);
		hash = closeHash(temp.planeID);
		if(strcmp((*retval)[hash].planeID, EMPTY) == 0 || strcmp((*retval)[hash].planeID, DELETED) == 0) {
			(*retval)[hash] = temp;
		} else {
			tempList->data[tempList->count] = temp;
			tempList->count++;
		}
	}
	for(i = 0; i < tempList->count; i++) {
		hash = closeHash(tempList->data[i].planeID);
		for(trav = 0; strcmp((*retval)[hash].planeID, EMPTY) != 0 && strcmp((*retval)[hash].planeID, DELETED) != 0 && trav < CLOSE_DSIZE; trav++, hash = (hash + 1) % CLOSE_DSIZE) {}
		for(dupe = 0; strcmp((*retval)[dupe].planeID, tempList->data[i].planeID) != 0 && dupe < CLOSE_DSIZE; dupe++) {}
		if(trav < CLOSE_DSIZE && dupe == CLOSE_DSIZE) {
			(*retval)[hash] = tempList->data[i];
			tempList->count--;
		}
	}
	return retval;
}
void displayCloseDic(CloseDic CD) {
	// Variable declaration here

	printf("\n\nDetails of Closed Hash Dictionary :: ");
	printf("\n-------------------------------------");
	printf("\n\n%-6s", "Index");
	printf("%-10s", "PlaneID");
	printf("%-15s", "Plane Model");
	printf("\n%-6s%-10s%-15s", "-----", "-------", "----------");

	// Write your code here!!
	int i;
	for(i = 0; i < CLOSE_DSIZE; i++) {
		printf("\n%-6d%-10s%-15s", i, CD[i].planeID, CD[i].planeInfo.model);
	}

}

