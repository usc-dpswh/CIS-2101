#include <stdio.h>
#include <stdbool.h>
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

typedef struct {
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
void    initVHeap(VHeap* main);
int     allocSpace(VHeap main);
void    insertCar(VHeap main);

//  Display Functions
void    preOrder(VHeap main);
void    inOrder(VHeap main);
void    postOrder(VHeap main);

//	Tree Functions
void 	initHeap(HeapPTR* main);
void	minHeapify(HeapPTR main);
void	maxHeapify(HeapPTR main);
void	insertIntoHeap(HeapPTR main, carNode newCar);
void	populateHeap(HeapPTR main, carNode carDatabase[]);
void	displayHeap(HeapPTR main);

int main(){
    carNode CarDatabase[10] = {
        {{"S123456789", "Toyota",  "Supra",     1998}, -1, -1},
        {{"S234567890", "Nissan",  "GTR",       2020}, -1, -1},
        {{"S345678901", "Mazda",   "RX7",       1997}, -1, -1},
        {{"S456789012", "Honda",   "NSX",       2005}, -1, -1},
        {{"S567890123", "Subaru",  "Impreza",   2002}, -1, -1},
        {{"S678901234", "Mitsubishi", "Evo",    2006}, -1, -1},
        {{"S789012345", "Acura",   "Integra",   2001}, -1, -1},
        {{"S890123456", "Lexus",   "LC500",     2021}, -1, -1},
        {{"S901234567", "Porsche", "911",       2019}, -1, -1},
        {{"S012345678", "BMW",     "M3",        2018}, -1, -1}
    };

//	Problem 1 (Inserting a car into BST)
//	1) Declare and initialize your VHeap.
//	2) Insert the cars from the database into the BST implemented via Cursor Based
//	3) Display the cars in the now populated VHeap in pre/in/postOrder.

//	Start writing your code here...

//	Problem 2 (Converting BST into Tree)
//	1) Declare and initialize HeapPTR.
//	2) Insert the cars from the BST, into the Heap. Make sure its in minHeap. Use populateHeap() and insertIntoHeap().
//	3) Convert your heap into a maxHeap using maxHeapify().
//	4) Display the heap.

//	Start wrting your code here...

    return 0;
}

//  Main Functions
void    initVHeap(VHeap* main);
int     allocSpace(VHeap main);
void    insertCar(VHeap main);

//  Display Functions
void    preOrder(VHeap main);
void    inOrder(VHeap main);
void    postOrder(VHeap main);

//	Tree Functions
void 	initHeap(HeapPTR* main);
void	minHeapify(HeapPTR main);
void	maxHeapify(HeapPTR main);
void	insertIntoHeap(HeapPTR main, carNode newCar);
void	populateHeap(HeapPTR main, carNode carDatabase[]);
void	displayHeap(HeapPTR main);
