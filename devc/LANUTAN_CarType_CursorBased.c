#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define VH_MAX 0XFF
#define TREE_SIZE 15

typedef struct {
    char    serialID[12];
    char    brand[20];
    char    model[20];
    int     year;
} CarType;

typedef struct {
    CarType car;
    int LC;
    int RC;
} carNode;

typedef struct vheap {
    carNode heap[VH_MAX];
    int avail;
} *VHeap;


typedef carNode   Tree[TREE_SIZE];

typedef struct heap {
  Tree        cars;
  int         lastNdx;
} *HeapPTR;

// Given the BST, the virtual heap, and a car record, write the code
// of the non-recursive function insertCar(). The function will insert
// a car record into the BST which is represented in memory using
// cursor based implementation. Each car record is uniquely identified
// through the car model.

//  Main Functions
void    initVHeap(VHeap* main, int* head);
int     allocSpace(VHeap main);
void    insertCar(VHeap main, carNode newCar, int* head);
void	populateBST(VHeap main, carNode carDatabase[], int* head);
bool	member(VHeap main, int head, char find[]);

//  Display Functions
void    preOrder(VHeap main, int head);
carNode    inOrder(VHeap main, int head);
void    postOrder(VHeap main, int head);

//	Tree Functions
void 	initHeap(HeapPTR* main);
void	minHeapify(HeapPTR main, VHeap mainVH, int head);
void	maxHeapify(HeapPTR main);
void	insertIntoHeap(HeapPTR main, carNode newCar);
void	populateHeap(HeapPTR main, carNode carDatabase[]);
void	displayHeap(HeapPTR main);

int main(){
    carNode CarDatabase[10] = {
        {{"A1B9C2D8E4F", "Toyota",  "Supra",     1998}, -1, -1},
        {{"X3Y7Z5Q0P2R", "Nissan",  "GTR",       2020}, -1, -1},
        {{"L9K6J1H5G3F", "Mazda",   "RX7",       1997}, -1, -1},
        {{"M5N3O1P9Q7R", "Honda",   "NSX",       2005}, -1, -1},
        {{"H4K2L8M6N4O", "Subaru",  "Impreza",   2002}, -1, -1},
        {{"T7U2V4W8X6Y", "Mitsubishi", "Evo",    2006}, -1, -1},
        {{"B3C1D7E5F9G", "Acura",   "Integra",   2001}, -1, -1},
        {{"S6T0U8V2W4X", "Lexus",   "LC500",     2021}, -1, -1},
        {{"J8K4L0M2N6O", "Porsche", "911",       2019}, -1, -1},
        {{"E9F3G7H1I5J", "BMW",     "M3",        2018}, -1, -1}
    };

//	Problem 1 (Inserting a car into BST)
//	1) Declare and initialize your VHeap and head.
//	2) Insert the cars from the database into the BST implemented via Cursor Based
//	3) Display the cars in the now populated VHeap in pre/in/postOrder.

//	Start writing your code here...
	VHeap A;
	int headBST;
	initVHeap(&A, &headBST);
	populateBST(A, CarDatabase, &headBST);
	printf("\n%s is a member = %d", "E9F3G7H1I5J", member(A, headBST, "E9F3G7H1I5J"));
	
//	printf("\nPreorder Listing of Cars...");
//	preOrder(A, headBST);
//	
//	printf("\nInorder Listing of Cars...");
//	inOrder(A, headBST);
//	
//	printf("\nPostorder Listing of Cars...");
//	postOrder(A, headBST);
	

//	Problem 2 (Converting BST into Tree)
//	1) Declare and initialize HeapPTR.
//	2) Insert the cars from the BST, into the Heap. Make sure its in minHeap. Use populateHeap() and insertIntoHeap().
//	3) Convert your heap into a maxHeap using maxHeapify().
//	4) Display the heap.
	HeapPTR B;
	initHeap(&B);
	minHeapify(B, A, headBST);

//	Start wrting your code here...

    return 0;
}

//  Main Functions
void    initVHeap(VHeap* main, int* head){
	int x;
	*main = (VHeap)malloc(sizeof(struct vheap));
	if (*main != NULL){
		for (x = -1 ; x < VH_MAX-1 ; x++){
			printf("\n%d", VH_MAX);
			(*main)->heap[x].LC = x;
			(*main)->heap[x].RC = -1;
		}
		*head = -1;
		(*main)->avail = VH_MAX-1;
		printf("\nInitialized VHeap.");
	}
}
int     allocSpace(VHeap main){
	int retval = main->avail;
	if (retval != -1){
		main->avail--;
	} 
	return retval;
}
void    insertCar(VHeap main, carNode newCar, int* head){
	if (main->avail != -1){
//		printf("\nmain->avail = %d", main->avail);
		int newNode = allocSpace(main);
//		printf("\nline120");
//		printf("\nnewNode = %d", newNode);
		if (newNode != -1){
			int* trav;
			for (trav = head ; *trav != -1 ; ){
//				printf("\nline124");
				if (strcmp(newCar.car.serialID, main->heap[*trav].car.serialID) > 0){
					trav = &main->heap[*trav].RC;
//					printf("\nnewCar[%s] > main[%s]", newCar.car.serialID, main->heap[*trav].car.serialID);
				} else {
					trav = &main->heap[*trav].LC;
				}
//				printf("after if");
			};
//			printf("\nline131");
			
			main->heap[newNode] = newCar;
			*trav = newNode;
//			printf("\nSuccessfully inserted [%s]", newCar.car.serialID);
		}
	} else {
		printf("\nno more space");
	}
}
void	populateBST(VHeap main, carNode carDatabase[], int* head){
	if (main->avail != -1){
		int* trav;
		int x;
		for (x = 0 ; x < 10 ; x++){
			insertCar(main, carDatabase[x], head);
//			printf("\nInserted [%s]", carDatabase[x].car.serialID);
		}
	} else {
		printf("main->avail == -1");
	}
}
bool	member(VHeap main, int head, char find[]){
	int trav;
	for (trav = head ; trav != -1 && strcmp(main->heap[trav].car.serialID, find) != 0 ; ){
		trav = (strcmp(find, main->heap[trav].car.serialID) < 0) ? main->heap[trav].LC : main->heap[trav].RC;
	}
	return trav != -1;
}

//  Display Functions
void    preOrder(VHeap main, int head){
	if (head != -1){
		printf("\n%s", main->heap[head].car.serialID);
		preOrder(main, main->heap[head].LC);
		preOrder(main, main->heap[head].RC);
	}
}
carNode    inOrder(VHeap main, int head){
	carNode temp = {0};
	if (head != -1){
		preOrder(main, main->heap[head].LC);
//		printf("\n%s", main->heap[head].car.serialID);
		temp = main->heap[head];
		printf("\n***********%s", temp.car.serialID);
		preOrder(main, main->heap[head].RC);
	}
	return temp;
}
void    postOrder(VHeap main, int head){
	if (head != -1){
		preOrder(main, main->heap[head].LC);
		preOrder(main, main->heap[head].RC);
		printf("\n%s", main->heap[head].car.serialID);
	}
}

//	Tree Functions
void 	initHeap(HeapPTR* main){
	*main = (HeapPTR)malloc(sizeof(struct heap));
	if (*main != NULL){
		(*main)->lastNdx = -1;
	}
	printf("\n\nInitialized HeapTree.");
}
void	minHeapify(HeapPTR main, VHeap mainVH, int head){
	if (mainVH->avail != VH_MAX-1){	
		int temp, trav, parNdx, childNdx;
	//	Insert in an empty POT
		int x;
		for (x = 0 ; x < 10 ; x++){
//			carNode newCar = inOrder(mainVH, head);
//			main->cars[x] = newCar;
			printf("\nInserted [%s]", newCar.car.serialID);
		}
	
//		if (main->lastNdx)
	}
}
void	maxHeapify(HeapPTR main);
void	insertIntoHeap(HeapPTR main, carNode newCar);
void	populateHeap(HeapPTR main, carNode carDatabase[]);
void	displayHeap(HeapPTR main);
