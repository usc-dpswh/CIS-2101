#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define VH_SIZE 0XC     // size of Virtual Heap
#define ARRAY_SIZE 0XE   // size of the array implementation of List
#define CLOSE_DSIZE 0XB // size of Close Dictionary

/******************************************************************************
* Data Structure Definition:                                                  *
******************************************************************************/
typedef struct{
	char model[30];
	char manufacturer[40]; // Airbus, Textron Aviation, Boeing
	int passengerCount;
	int year;
}planeDesc;

typedef struct{
	char planeID[8];
	planeDesc planeInfo;
	float planePrice;
	int maxSpeed;
}Aircraft;

typedef struct {
	Aircraft data;
	int next;
}PlaneNode;

/************************
* Virtual Heap          *
************************/
typedef struct {
	PlaneNode VH_Node[VH_SIZE];
	int avail;
}VHeap;

/******************************************
* Cursor-Based Implementation of LIST     *
******************************************/
typedef struct CList{
	int elemIndex; // index of the 1st element in the set
	int count;     // holds the actual number of elements in the list
	VHeap *VHptr;  // holds the pointer to the virtual heap
}*CursorList;

/******************************************
* Array Implementation of LIST  		  *
******************************************/
typedef struct ArrList{
	Aircraft data[ARRAY_SIZE];
	int count; // holds the actual number of elements in the list
}*ArrayList;


typedef struct node{
	Aircraft elem;
	struct node *link;
}*LinkedList;

/******************************************
* Linked List Implementation of QUEUE 	  *
******************************************/
typedef struct {
	LinkedList front;
	LinkedList rear;
}LinkedQueue;

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

int main(){
	// Variable Declaration for all problems here
	
	
	/*--------------------------------------------------------------------------------------------
    * 	Problem #1 ::  1) Initializes the virtual heap, the array list and the cursor list        *
    *                  2) Displays the contents virtual heap, the array list and the cursor list  *
    *---------------------------------------------------------------------------------------------*/
    printf("\n\n\nProblem #1:: ");
    printf("\n------------");
	// Write the necessary functions for the problem here
	VHeap 			A;
	ArrayList 	B;
	CursorList 	C;

	initVHeap(&A);
	B = initArrayList();
	C = initCursorList(&A);

	displayVHeap(A);
	displayArrayList(B);
	displayCursorList(C);
	
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
	populateArrayList(&B);
	displayArrayList(B);

	populateCListSorted(&B, &C);

	displayVHeap(A);
	displayArrayList(B);
	displayCursorList(C);
	
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
	LinkedQueue QueueA;
	initQueue(&QueueA);
	enqueueFromCList(&QueueA, &C);

	displayCursorList(C);
	displayVHeap(A);
	
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
	CloseDic* D;
	D = convertToCloseDic(&QueueA);
	displayCloseDic(*D);
	// printf("\n%s", QueueA.front->elem.planeID);
	// printf("\n%s", QueueA.front->link->elem.planeID);
	// printf("\n%s", QueueA.front->link->link->elem.planeID);

	return 0;
}

/************************************************************
 *  Problem 1:: Function Definitions                        *
 ************************************************************/
void initVHeap(VHeap *VH){
	int x;
	for (x = -1 ; x < VH_SIZE ; x++){
		strcpy(VH->VH_Node[x+1].data.planeID, "");
		VH->VH_Node[x+1].next = x;
	}
	VH->avail = VH_SIZE-1;
	printf("\nInitialized VHeap.");
}
CursorList initCursorList(VHeap *VH){
	CursorList new = (CursorList)malloc(sizeof(struct CList));
	if (new != NULL){
		new->count = 0;
		new->elemIndex = -1;
		new->VHptr = VH;
	}
	printf("\nInitialized cursor list.");
	return new;
}
ArrayList initArrayList(){
	ArrayList new = (ArrayList)malloc(sizeof(struct ArrList));
	if (new != NULL){
		new->count = 0;
	}
	printf("\nInitialized ArrayList.");
	return new;
}
void displayVHeap(VHeap VH){
	// Variable Declaration here!!
	
	printf("\n\nDetails of the Virtual Heap :: ");
	printf("\n------------------------------");
	printf("\nAvailable Index  ::  %d", VH.avail);
	printf("\nVHeap Address    ::  %p", VH);
	printf("\n\n%10s", "Index");
	printf("%10s", "Plane ID");
	printf("%15s", "Next Field");
	printf("\n%10s%10s%15s\n", "-----", "-------", "----------");
	
	// Write your code here!!
	int x;
	for (x = 0 ; x < VH_SIZE ; x++){
		printf("%10d%10s%15d\n",
			x,
			VH.VH_Node[x].data.planeID,
			VH.VH_Node[x].next
		);
	}

}
void displayArrayList(ArrayList A){
	// Variable Declaration here!!
	
	printf("\n\nDetails of the Array List :: ");
	printf("\n---------------------");
	printf("\nNo. of Elements :: %d", A->count);
	printf("\n\n%-8s", "Index");
	printf("%-9s", "ID");
	printf("%-15s", "Plane Model");
	printf("%-25s", "Plane Manufacturer");
	printf("\n%-7s%-10s%-15s%-25s\n", "-----", "-----", "-----------", "------------------");
	
	// Write your code here!!
	int x;
	for (x = 0 ; x < A->count ; x++){
		printf("%-8d%-9s%-15s%-25s\n",
			x,
			A->data[x].planeID,
			A->data[x].planeInfo.model,
			A->data[x].planeInfo.manufacturer
		);
	}

}
void displayCursorList(CursorList C){
	// Variable Declaration here!!
	
	printf("\n\nDetails of the Cursor List :: ");
	printf("\n---------------------");
	printf("\nNo. of Elements :: %d", C->count);
	printf("\n\n%-7s", "ID");
	printf("%-15s", "Plane Model");
	printf("%-25s", "Plane Manufacturer");
	printf("%-10s", "VHeap Index");
	printf("\n%-7s%-15s%-25s%-10s\n", "--", "----------", "------------------",
         "-----------");
	// Write your code here!!
	int x, trav;
	for (x = 0, trav = C->elemIndex ; x < C->count && trav != -1 ; trav = C->VHptr->VH_Node[trav].next, x++){
		printf("%-7s%-15s%-25s%-10d\n",
			C->VHptr->VH_Node[trav].data.planeID,
			C->VHptr->VH_Node[trav].data.planeInfo.model,
			C->VHptr->VH_Node[trav].data.planeInfo.manufacturer,
			C->VHptr->VH_Node[trav].next
		);
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
					   {"23929",{"A400M", "Airbus", 300, 2019}, 300000, 340}};

	// Inserts each element of the array to the array list
    // Write your code here!!
	int x;
	for (x = 0 ; x < COUNT && (*A)->count < ARRAY_SIZE ; x++){
		(*A)->data[x] = data[x];
		(*A)->count++;
		// printf("\nInserted [%s]!", data[x].planeID);
	}
}

// Given an array list and a cursor list, the function
// deletes/removes the elements from the array list and
// transfers it to the cursor list if the manufacturer of the
// element is Airbus or Textron Aviation. The function calls
// allocSpace() for insertion. The function also returns the
// number of elements inserted to the cursor list.
int populateCListSorted(ArrayList *A, CursorList *C){
	// Write your code here!!
	int numInserted = 0;
	int x, *trav;
	for (x = 0 ; x < (*A)->count ; x++){
		if (strcmp((*A)->data[x].planeInfo.manufacturer, "Airbus") == 0 || strcmp((*A)->data[x].planeInfo.manufacturer, "Textron Aviation") == 0){
			// Loop at the right spot to insert
			for (trav = &(*C)->elemIndex ; *trav != -1 && strcmp((*A)->data[x].planeID, (*C)->VHptr->VH_Node[*trav].data.planeID) > 0 ; trav = &(*C)->VHptr->VH_Node[*trav].next){};

			// After looping, allocate space for your newNode.
			int newNode = allocSpace((*C)->VHptr);
			// We make sure that newNode has been successfully allocated space and that what we're inserting is unique.
			if (newNode != -1){
				(*C)->VHptr->VH_Node[newNode].data = (*A)->data[x];
				(*C)->VHptr->VH_Node[newNode].next = *trav;
				*trav = newNode;
				(*C)->count++;
				numInserted++;
				printf("Inserted [%s] into Cursor List.\n", (*A)->data[x].planeID);
			}
		} else {
			printf("Plane with ID: [%s] is not manufactured by Airbus or Textron Aviation!\n", (*A)->data[x].planeID);
		}
	}
	return numInserted;
}
int allocSpace(VHeap *VH){
	// Write your code here!!
	int retval = VH->avail;
	if (retval != -1){
		VH->avail = VH->VH_Node[retval].next;
	}
	return retval;
}

/************************************************************
 *  Problem 3:: Function Definitions                        *
 ************************************************************/
void initQueue(LinkedQueue *Q){
	Q->front 	= NULL;
	Q->rear		= NULL;
	printf("\nInitialized Queue!");
}
void freeSpace(VHeap *VH, int ndx){
	// Write your code here!!
	if (ndx >= 0 && ndx < VH_SIZE){
		strcpy(VH->VH_Node[ndx].data.planeID, EMPTY);
		VH->VH_Node[ndx].next = VH->avail;
		VH->avail = ndx;
		// printf("\nSuccessfully deleted [%s]", VH->VH_Node[ndx].data.planeID);
	} else {
		printf("Not a valid airplane to destroy.\n");
	}
}
void enqueueFromCList(LinkedQueue *Q, CursorList *C){
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
// This function returns the hash value of a given ID
// number by adding its NUMERIC digits and reducing its
// value appropriate to the size of the
// hash table. Example: ID numbers “13567” and “17019”
// have hash values of 0 and 7 respectively.
int closeHash(char ID[]){
	// Write your code here!!
	int x;
	int hashVal;
	for (x = 0 ; ID[x] != '\0' ; x++){
		hashVal = hashVal + ID[x] - '0';
	}
	return hashVal % CLOSE_DSIZE;
}

void initCloseDic(CloseDic CD){
	// Write your code here!!
	int x;
	for (x = 0 ; x < CLOSE_DSIZE ; x++){
		strcpy(CD[x].planeID, EMPTY);
		strcpy(CD[x].planeInfo.model, EMPTY);
	}
	printf("\nInitialized close dictionary.\n");
}

Aircraft dequeue(LinkedQueue *Q){
	// Write your code here!!
	Aircraft retval;
	LinkedList temp;
	if (Q->front != NULL){
		retval = Q->front->elem;
		temp = Q->front;
		if (Q->front == NULL){
			Q->rear = NULL;
		}
		Q->front = temp->link;
		free(temp);
	} 
	return retval;
}
// The function converts the given queue into a closed
// hash dictionary using a 2 pass loading (synonyms are
// temporarily stored in an array implemented list). In the
// 2
// nd round of insertions, the elements stored in the list
// are added in the close dictionary. NOTE: The elements
// of the close dictionary MUST be UNIQUE. The Aircraft is
// uniquely identified by their ID.
CloseDic *convertToCloseDic(LinkedQueue *Q){
	// Write your code here!!
	CloseDic* newDic = (CloseDic*)malloc(sizeof(CloseDic));
	initCloseDic(*newDic);
	ArrayList temp = (ArrayList)malloc(sizeof(struct ArrList));
	if (temp != NULL){
		temp = initArrayList();
	}
	int x,y;
	int hashVal;

	LinkedList* trav;
	LinkedList delete;
	Aircraft airplane;
	if (newDic != NULL){
		// First loop to get all data from QUEUE -> CLOSE_DICTIONARY
		while (Q->front != NULL){
			airplane = dequeue(Q);
			hashVal = closeHash(airplane.planeID);
			if (strcmp((*newDic)[hashVal].planeID, EMPTY) == 0 || strcmp((*newDic)[hashVal].planeID, DELETED) == 0){
				(*newDic)[hashVal] = airplane;
				printf("\nInserted into newDic.");
			} else {
				temp->data[temp->count] = airplane;
				temp->count++;
				printf("\nInserted into temp.");
			}
		}
		// Second loop to hash all the elements in the temp, to place it in newDic
		for (x = 0 ; x < temp->count ; x++){
			hashVal = closeHash(temp->data[x].planeID);
			for (y = 0 ; y < CLOSE_DSIZE && strcmp((*newDic)[hashVal].planeID, EMPTY) != 0 && strcmp((*newDic)[hashVal].planeID, DELETED) != 0 ; hashVal = (hashVal + 1) % CLOSE_DSIZE, y++){};
			if (y < CLOSE_DSIZE && strcmp(temp->data[x].planeID, (*newDic)[hashVal].planeID) != 0){
				(*newDic)[hashVal] = temp->data[x];
				printf("\nInserted from temp.");
				temp->count--;
			} else {
				printf("\n[%s] Not unique.", temp->data[x].planeID);
			}
		}
		
	}
	return newDic;
}
void displayCloseDic(CloseDic CD){
	// Variable declaration here

	printf("\n\nDetails of Closed Hash Dictionary :: ");
	printf("\n-------------------------------------");
	printf("\n\n%-6s", "Index");
	printf("%-10s", "PlaneID");
	printf("%-15s", "Plane Model");
	printf("\n%-6s%-10s%-15s", "-----", "-------", "----------");
	
	// Write your code here!!
	int x;
	for (x = 0 ; x < CLOSE_DSIZE ; x++){
		printf("\n%-6d%-10s%-15s",
			x,
			CD->planeID,
			CD->planeInfo.model
		);
	}
	
}

