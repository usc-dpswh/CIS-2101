/******************************************************************
 * Project Name:  List, Set and Dictionary                        *
 * Programmer  :  Put your Name here                              *
 * Date Completed: March 25, 2023                                 *
 ******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VH_SIZE 0XC     // size of Virtual Heap (12)
#define OPEN_DSIZE 0XA  // size of Open Hash Table (10)
#define CLOSE_DSIZE 0XC // size of Close Hash Table (12)
#define LIST_SIZE 0XF   // size of the array implementation of List (15)
/******************************************************************************
 * Data Structure Definition:                                                 *
 ******************************************************************************/
typedef struct {
  char name[24]; // Chocolate name
  int weight;    // Chocolate weight in grams
} chocoDesc;

typedef struct {
  char prodID[8];     //  product ID uniquely identifies the products; EMPTY or
                      //  DELETED
  chocoDesc prodDesc; //  product description
  float prodPrice;    //  product price
  int prodQty;        //  product count or quantity
} product;            //  product record

typedef struct {
  product elem;
  int next;
} prodNode; // Product node, used in cursor-based implementation of Set

/************************
 * Virtual Heap         *
 ************************/
typedef struct {
  prodNode VH_node[VH_SIZE];
  int avail;
} VHeap;

/******************************************
 * Cursor-Based Implementation of SET     *
 ******************************************/
typedef struct {
  int elemIndex; // index of the 1st element in the set
  int count;     // holds the actual number of elements in the set
  VHeap *VHptr;  // holds the pointer to the virtual heap
} cursorSet;

/********************************************
 * Open Hashing Implementation of Dictionary*
 ********************************************/
typedef struct {
  int header[OPEN_DSIZE]; // array of sets
  int count;              // total number of elements in the dictionary
  VHeap *dicVHptr;        // holds the pointer to the virtual heap
} openDic;

/**********************************************
 * Closed Hashing with 2 pass loading          *
 **********************************************/
#define EMPTY "empty" // stored in product ID field
#define DELETED "del" // stored in product ID field *

typedef product closeDic[CLOSE_DSIZE]; // Definition of the closed hash dictionary

typedef struct {
  product prod[LIST_SIZE];
  int last; // index of the last element; -1 if list is empty
} List;

/**********************************************************
 * Function Prototypes                                    *
 *********************************************************/
//---Problem #1 ---
void initVHeap(VHeap *VH);
cursorSet initCursorSet(VHeap *VH);
void displayVHeap(VHeap V);
void displaySet(cursorSet A);

//---Problem #2 ---
int mallocInVHeap(VHeap *VH);
void insertSorted(cursorSet *A, product P);
void populateSet(cursorSet *A);

//---Problem #3 ---
int openHash(char *IDen);
openDic initOpenDict(VHeap *VH);
openDic convertToOpenDict(cursorSet *A);
void displayOpenDict(openDic D);

//---Problem #4 ---
void freeInVHeap(VHeap *VH, int ndx);
void deleteDict(openDic *D, char *IDen);

//---Problem #5 ---
int closeHash(char *ID);
void initCloseDict(closeDic CD);
closeDic *convertToCloseDict(openDic *D);
void displayCloseDict(closeDic CD);

/************************************************************************************
 * READ ME FIRST before ANSWERING * 1)  To facilitate the checking of the
 *machine problem, follow the instructions * in each PROBLEM #. * 2)  To
 *accomplish the task for each PROBLEM, a series of function calls may be *
 *       necessary. * 3)  Write you answer BELOW THE COMMENTS. DO NOT DELETE
 *COMMENTS                *
 *                                                                                  *
 ***********************************************************************************/
int main() {
  /*---------------------------------------------------------------------------------
   * 	Problem #1 ::  1) Initializes the virtual heap and the cursor Set * 2)
   *Displays the contents  virtual heap and cursor Set          *
   *--------------------------------------------------------------------------------*/
  printf("\n\n\nProblem #1:: ");
  printf("\n------------");
  // Declare variables needed for Problem #1
  VHeap A;
	cursorSet B;

  // Function Calls for Problem #1
  initVHeap(&A);
	B = initCursorSet(&A);
	displayVHeap(A);
	displaySet(B);

  /*---------------------------------------------------------------------------------
   * 	Problem #2 ::  1) Populates the Cursor set which is sorted in ascending
   *order * according to ID                                             * 2)
   *Displays the Cursor set                                     *
   *--------------------------------------------------------------------------------*/
  printf("\n\n\nProblem #2:: ");
  printf("\n------------");
  // Declare variables needed for Problem #2

  // Function Calls for Problem #2
	populateSet(&B);
	displaySet(B);


  /*---------------------------------------------------------------------------------
   * 	Problem #3 ::  1) Converts the Cursor set into an Open Hash Dictionary *
   *                 2) Displays the Open Hash Dictionary * 3) Displays the
   *empty Cursor set.                              *
   *--------------------------------------------------------------------------------*/
  printf("\n\n\nProblem #3:: ");
  printf("\n------------");
  // Declare variables needed for Problem #3
	openDic C;

  // Function Calls for Problem #3
	C = convertToOpenDict(&B);
	displayOpenDict(C);
  /*---------------------------------------------------------------------------------
   * 	Problem #4 ::  1) Perform 3 delete operations on the Open Hash
   *Dictionary     * 2) Displays the Open Hash Dictionary * 3) Displays the
   *Virtual Heap                                   *
   *--------------------------------------------------------------------------------*/
  printf("\n\n\nProblem #4:: ");
  printf("\n------------");
  // Declare variables needed for Problem #4
  char delete01[] = "1703";
  char delete02[] = "1358";
  char delete03[] = "1601";

  // Function Calls for Problem #4
	deleteDict(&C, delete01);
	deleteDict(&C, delete02);
	deleteDict(&C, delete03);

	displayOpenDict(C);
	displayVHeap(A);

  /*------------------------------------------------------------------------------------
   * 	Problem #5 :: 1) Converts the Open Hash Dictionary into a Closed Hash
   *Dictionary * 2) Displays the Closed Hash Dictionary * 3) Displays the
   *virtual heap                                       *
   *---------------------------------------------------------------------------------*/
  printf("\n\n\nProblem #5:: ");
  printf("\n------------");
  // Declare variables needed for Problem #5
	closeDic* D;

  // Function Calls for Problem #5
	D = convertToCloseDict(&C);
	displayCloseDict(*D);
	displayVHeap(A);

  return 0;
}

/************************************************************
 *  Problem 1:: Function Definitions                          *
 ************************************************************/
void initVHeap(VHeap *V) {
  int i;

  for (i = 0 ; i < VH_SIZE ; i++) {
		strcpy(V->VH_node[i+1].elem.prodID, EMPTY);
		V->VH_node[i+1].next = i;
  }
	V->avail = VH_SIZE-1;
	printf("\nInitialized VHeap.\n");
}

cursorSet initCursorSet(VHeap *VH) {
	printf("Initialized cursorSet.\n");
  return (cursorSet){-1,0,VH};
}

void displayVHeap(VHeap V) {
  // Variable Declaration here
  int i, j;

  printf("\n\nDetails of the Virtual Heap :: ");
  printf("\n------------------------------");
  printf("\nAvailable Index  ::  %d", V.avail);    // Complete this statement
  printf("\nVHeap Address    ::  %p", &V.VH_node); // Complete this statemet

  printf("\n\n%10s", "Index");
  printf("%10s", "Prod ID");
  printf("%15s", "Next Field");
  printf("\n%10s%10s%15s\n", "-----", "-------", "----------");

  // Write your code here
  for (i = 0 ; i < VH_SIZE; i++) {
    printf("%10d", i);
    printf("%10s", V.VH_node[i].elem.prodID);
    printf("%15d", V.VH_node[i].next);
		printf("\n");
  }

  printf("\n\n");
  // system("Pause");
}

void displaySet(cursorSet A) {
  int x;
  product p;

  printf("\n\nDetails of the Set :: ");
  printf("\n---------------------");
  printf("\nNo. of elements ::  %d", A.count); // Complete this code
  printf("\n\n%-7s", "ID");
  printf("%-12s", "Choco Name");
  printf("%-15s", "Choco Weight");
  printf("%-10s", "VHeap Index");
  printf("\n%-7s%-12s%-15s%-10s\n", "--", "----------", "------------",
         "-----------");

  // Write your code here
	for (x = A.elemIndex ; x != -1 ; x = A.VHptr->VH_node[x].next){
		printf("%-7s", A.VHptr->VH_node[x].elem.prodID);
		printf("%-12s", A.VHptr->VH_node[x].elem.prodDesc.name);
		printf("%-15d", A.VHptr->VH_node[x].elem.prodDesc.weight);
		printf("%-10d", x);
		printf("\n");
	}

  printf("\n\n");
  // system("Pause");
}

/************************************************************
 *  Problem 2:: Function Definitions                         *
 ************************************************************/
int mallocInVHeap(VHeap *VH) {
  int newNode = VH->avail;
	if (newNode != -1){
		VH->avail = VH->VH_node[newNode].next;
	}
  return newNode;
}

void insertSorted(cursorSet *A, product P) {
	int *x, trav;
	if (A->count < VH_SIZE){
		for (x = &A->elemIndex ; *x != -1 && strcmp(P.prodID, A->VHptr->VH_node[*x].elem.prodID) > 0 ; x = &A->VHptr->VH_node[*x].next){};
		if (strcmp(P.prodID, A->VHptr->VH_node[*x].elem.prodID) == 0){
			printf("\nProduct with ID: %s already exists in the set.", P.prodID);
		} else {
			int newNode = mallocInVHeap(A->VHptr);
			if (newNode != -1){
				A->VHptr->VH_node[newNode].elem = P;
				A->VHptr->VH_node[newNode].next = *x;
				*x = newNode;
				A->count++;
					// printf("\nInserted [%s]", P.prodID);
			}
		}
	} else {
		printf("No available space. Product with ID: %s cannot be inserted.\n", P.prodID);
	}
}

void populateSet(cursorSet *A) {
  const int COUNT = 15;
  product data[] = {
      {"1701", {"Toblerone", 135}, 150.75, 20},
      {"1356", {"Ferrero", 200}, 250.75, 85},
      {"1109", {"Patchi", 50}, 99.75, 35},
      {"1550", {"Cadbury", 120}, 200.00, 30},
      {"1807", {"Mars", 100}, 150.75, 20},
      {"1201", {"Kitkat", 50}, 97.75, 40},
      {"1450", {"Ferrero", 100}, 150.50, 50},
      {"1701", {"Toblerone", 50}, 90.75, 80},
      {"1601", {"Meiji", 75}, 75.50, 60},
      {"1310", {"Nestle", 100}, 124.50, 70},
      {"1807", {"Valor", 120}, 149.50, 90},
      {"1455", {"Tango", 75}, 49.50, 100},
      {"1703", {"Toblerone", 100}, 125.75, 60},
      {"1284", {"Lindt", 100}, 250.75, 15},
      {"1688", {"Guylian", 50}, 99.75, 35},

  };
  // Inserts each element of the array to the cursor set
  // Write your code here!!
  int i;
  for (i = 0; i < COUNT; i++) {
		insertSorted(A, data[i]);
  }
}

/************************************************************
 *  Problem 3:: Function Definitions                        *
 ************************************************************/
int openHash(char *prodID) {
	int x, sum;
	for (x = 0, sum = 0 ; prodID[x] != '\0' ; x++){
		sum = sum + prodID[x] - '0';
	}
	return sum % OPEN_DSIZE;
}

openDic initOpenDict(VHeap *VH) {
	openDic temp;
	int x;
	temp.count = 0;
	temp.dicVHptr = VH;
	for (x = 0 ; x < OPEN_DSIZE ; x++){
		temp.header[x] = -1;
	}
	printf("\nInitialized open dictionary.");
	return temp;
}


openDic convertToOpenDict(cursorSet *A) {
	openDic temp = initOpenDict(A->VHptr);
	int x;
	for (x = 0 ; x < VH_SIZE ; x++){
		int hashVal = openHash(A->VHptr->VH_node[x].elem.prodID);
		int* trav;
		for (trav = &temp.header[hashVal] ; *trav != -1 && strcmp(A->VHptr->VH_node[x].elem.prodID, A->VHptr->VH_node[*trav].elem.prodID) > 0 ; trav = &temp.dicVHptr->VH_node[*trav].next){};
		// If there is nothing in the header yet
		if (*trav == -1 || strcmp(A->VHptr->VH_node[x].elem.prodID, 		A->VHptr->VH_node[*trav].elem.prodID) != 0){
			A->VHptr->VH_node[x].next = *trav;
			*trav = x;
			temp.count++;
			A->count--;
		}
	}
	A->elemIndex = -1;
	printf("Converted to open dictionary.\n");
	return temp;
}

void displayOpenDict(openDic D) {
  // Variable declaration here

  printf("\n\nDetails of the Open Hash Dictionary:: ");
  printf("\n-------------------------------------");

  printf("\nNo. of elements :: %d", D.count);
  printf("\n\n%-7s", "GROUPS");
  printf("%15s", "ID Numbers");
  printf("\n%-7s%15s", "------", "----------");

  // Write your code here
	int x;
	int trav;
	for (x = 0 ; x < OPEN_DSIZE ; x++){
		printf("\nGroup[%d] :: ", x);
		for (trav = D.header[x] ; trav != -1 ; trav = D.dicVHptr->VH_node[trav].next){
			printf("%-7s", D.dicVHptr->VH_node[trav].elem.prodID);
		}
	}
  printf("\n\n");
  // system("Pause");
}

/************************************************************
 *  Problem 4:: Function Definitions                        *
 ************************************************************/
void freeInVHeap(VHeap *VH, int ndx) {
	if (ndx >= 0 && ndx < VH_SIZE){
		VH->VH_node[ndx].next = VH->avail;
		VH->avail = ndx;
		// printf("Free successful.\n");
	} 
	// else {
	// 	printf("Not a valid node to delete.\n");
	// }
}

void deleteDict(openDic *D, char *IDen) {
	int temp;
	int* trav;
	int hashVal = openHash(IDen);
	for (trav = &D->header[hashVal] ; *trav != -1 && strcmp(D->dicVHptr->VH_node[*trav].elem.prodID, IDen) != 0 ; trav = &D->dicVHptr->VH_node[*trav].next){};
	if (*trav != -1){
		temp = *trav;
		*trav = D->dicVHptr->VH_node[temp].next;
		freeInVHeap(D->dicVHptr, temp);
		printf("\nProduct with ID: [%s] is successfuly deleted!", IDen);
	} else {
		printf("\nProduct with ID: [%s] is not in the dictionary.", IDen);
	}
}

/************************************************************
 *  Problem 5:: Function Definitions                        *
 ************************************************************/
// This function returns the hash value of a given ID number by adding its NUMERIC digits and reducing its value appropriate to the size of the hash table. Example: ID numbers “1284” and “1701” have hash values of 3 and 9 respectively.
int closeHash(char *ID) {
	int x;
	int sum;
	for (x = 0, sum = 0 ; ID[x] != '\0' ; x++){
		sum = sum + ID[x] - '0';
	}
	return sum % CLOSE_DSIZE;
}

void initCloseDict(closeDic CD) {
	int x;
	for (x = 0 ; x < CLOSE_DSIZE ; x++){
		strcpy(CD[x].prodID, EMPTY);
		strcpy(CD[x].prodDesc.name, "     ");
	}
	printf("\nInitialized close dictionary.\n");
}

closeDic *convertToCloseDict(openDic *D) {
	int x,y, temp;
	int* trav;
	int hashVal;
	// Where we will place our synonyms
	List synonymsTemp;
	synonymsTemp.last = -1;
	// What we will return back to the calling function
	closeDic* newDic = (closeDic*)malloc(sizeof(closeDic));
	if (newDic != NULL){
		initCloseDict(*newDic);
		for (x = 0 ; x < OPEN_DSIZE ; x++){
			for (trav = &D->header[x] ; *trav != -1 ;){
				hashVal = closeHash(D->dicVHptr->VH_node[*trav].elem.prodID);
				if (strcmp((*newDic)[hashVal].prodID, EMPTY) == 0){
					(*newDic)[hashVal] = D->dicVHptr->VH_node[*trav].elem;
				} else {
					if (synonymsTemp.last < LIST_SIZE){
						synonymsTemp.last++;
						synonymsTemp.prod[synonymsTemp.last] = D->dicVHptr->VH_node[*trav].elem;
					}
				}
				D->count--;
				temp = *trav;
				*trav = D->dicVHptr->VH_node[temp].next;
				freeInVHeap(D->dicVHptr, temp);
			}
		}
		// After loop, put back all synonyms into close dic
		int stopper;
		for (x = 0 ; x < synonymsTemp.last ; x++){
			hashVal = closeHash(synonymsTemp.prod[x].prodID);
			for (stopper = 0 ; stopper < CLOSE_DSIZE && strcmp((*newDic)[hashVal].prodID, EMPTY) != 0 && strcmp((*newDic)[hashVal].prodID, DELETED) != 0 ; stopper++, hashVal++){};
			if (stopper < CLOSE_DSIZE){
				(*newDic)[hashVal] = synonymsTemp.prod[x];
			}
		}
	}
	return newDic;
}

void displayCloseDict(closeDic CD) {
  // Variable declaration here

  printf("\n\nDetails of Closed Hash Dictionary :: ");
  printf("\n-------------------------------------");
  printf("\n\n%-6s", "Index");
  printf("%-10s", "ChocoID");
  printf("%-15s", "Choco Name");
  printf("\n%-6s%-10s%-15s", "-----", "-------", "----------");

  // Write your code here
	int x;
	for(x = 0; x < CLOSE_DSIZE; x++){
		printf("\n%2d%10s%13s", x, CD[x].prodID, CD[x].prodDesc.name);
	}
  printf("\n\n");
  // system("Pause"); 
}
