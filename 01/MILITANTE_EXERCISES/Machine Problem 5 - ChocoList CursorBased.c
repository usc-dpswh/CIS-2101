#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  NAME_SIZE  30
#define  ARRAY_SIZE  15
#define  ID_SIZE     10
#define  CHOCO_SIZE 15

typedef struct {
 	char name[NAME_SIZE];  /* Chocolate name */  
 	int  weight;          /*  Chocolate weight in grams */
}ChocoDesc;
 
typedef struct {
  char chocoID[ID_SIZE];   /*  product ID, uniquely identifies each product */ 
  ChocoDesc chocoDesc;     /*  product description*/  
  float chocoPrice;        /*  product price*/  
  int chocoQty;            /* product count or quantity  */
}Chocolate;                 /* product record */

typedef struct ChocoNode{
   Chocolate chocoProd;
   int nextChoco;                  
}ChocoNode, *CLL;             

typedef struct{
	ChocoNode choco[CHOCO_SIZE];				
	int avail;			
	int numChoco;
}ChocoList;

typedef int CList;

/**********************************************************
 * Function Prototypes                                    *
 *********************************************************/
 
void pause(void);

/* Problem 1 */
ChocoList initChocoList     (void);
void generateChocoRecords   (void);
void populateChocoList      (ChocoList *CL, CList *head);
void displayChocoList       (ChocoList CL, char *listDesc, CList head);
int allocSpace              (ChocoList *CL);
void deallocSpace           (ChocoList *CL, int ndx);
void initCList              (CList *head);

/* Problem 2 */
void insertLastUnique       (ChocoList *CL, Chocolate X, CList *head);

/* Problem 3 */
void insertSortedName       (ChocoList *CL, Chocolate X, CList *head);
ChocoList populateSorted    (ChocoList CL, CList head, CList *head2);

/* Problem 4 */
int deleteAllChoco          (ChocoList *CL, char chocoName[], CList *head);

/* Problem 5 */
void sortChocoList          (ChocoList *CL, CList *head);

int main(void) 
{	
    ChocoList B;           /* Unsorted List variables */
    ChocoList sortedList;     /* Sorted list variable */
    Chocolate uniqueChoco1 = {"CR1388", {"Crunch", 50}, 88, 88};
    Chocolate uniqueChoco2 = {"CR1399", {"Crunch", 100}, 159, 159};
    Chocolate duplicateChoco =	{"KI1201", {"Kitkat", 75}, 99.99, 99};
    int count = 0; 
    char deletedChoco_01[NAME_SIZE] = "Toblerone";
    char deletedChoco_02[NAME_SIZE] = "Ferrero";
  	generateChocoRecords();
  
/* Problem 1
	Instructions:
	 1) Initialize ChocoList A by calling initChocoList().
	 2) Populate ChocoList A by calling populateChocoList().
	 3) Display the contents of A by calling displayChocoList(). Pass "A (unsorted)" as the list description.
	 4) Call the pause() function.
*/

	printf("Problem 1\n");

	CList head, head2;
  initCList(&head);
  initCList(&head2);

	ChocoList A = initChocoList();
  populateChocoList(&A, &head);
  displayChocoList(A, "A (unsorted)", head);
  // printf("%d\n\n", A.choco[0].chocoProd.chocoDesc.weight);

 	// pause(); 
  

/* Problem 2
	Instructions:
	 1) Call insertLastUnique() passing A and uniqueChoco1 as parameters.
	 2) Call insertLastUnique() passing A and duplicateChoco as parameters.
	 3) Call insertLastUnique() passing A and uniqueChoco2 as parameters.
	 4) Display the contents of A by calling displayChocoList(). Pass "A (unsorted)" as the list description.
	 5) Call the pause() function.
*/
	printf("\n\nProblem 2\n");

  insertLastUnique(&A, uniqueChoco1, &head);
  insertLastUnique(&A, duplicateChoco, &head);
  insertLastUnique(&A, uniqueChoco2, &head);
  displayChocoList(A, "A (unsorted)", head);

    // pause();

/* Problem 3
	Instructions:
	 1) Populate sortedList by calling populateSorted() function, and passing A as the parameter.
	 2) Display the contents of A by calling displayChocoList(). Pass "A (Sorted List)" as the list description.
	 3) Call the pause() function.
*/
 	printf("\nProblem 3\n");

  sortedList = populateSorted(A, head, &head2);
  displayChocoList(sortedList, "A (Sorted List)", head2);

 	// pause();
	
/* Problem 4
	Instructions:
	 1) Call the deleteAllChoco() function, passing A and deletedChoco_01 as parameters.
	 2) Call the deleteAllChoco() function, passing A and deletedChoco_02 as parameters.
	 3) Display the contents of A by calling displayChocoList(). Pass "A (After deletion)" as the list description.
	 4) Call the pause() function.
*/	 
	printf("\nProblem 4\n");
  
  deleteAllChoco(&A, deletedChoco_01, &head);
  deleteAllChoco(&A, deletedChoco_02, &head);
  displayChocoList(A, "A (After deletion)", head);

    // pause();
	     
 
/*---------------------------------------------------------------------------------
 * 	Problem #5 ::  Initialize and populate an unsorted chocoList B, then arrange   *
 *                 the choco records of chocoList B in ascending order according   *
 *                 to ID by calling arrangeChocoID. Display the list by calling    *
 *                 displayList() BEFORE and AFTER the call to arrangeChocoID().    *                                               *
 *  printf("\n\n\nProblem #5:: ");                                                 *
 *---------------------------------------------------------------------------------*/
/* Problem 5
	Instructions:
	 1) Initialize ChocoList B by calling initChocoList().
	 2) Populate ChocoList B by calling populateChocoList().
	 3) Display the contents of B by calling displayChocoList(). Pass "B (unsorted)" as the list description.
	 4) Sort ChocoList B by calling the sortChocoList() function.
	 5) Display the contents of B by calling displayChocoList(). Pass "B (sorted)" as the list description.
	 
*/	 		     
	printf("\n\nProblem 5\n");

  CList BHead = -1;
  B = initChocoList();
  populateChocoList(&B, &BHead);
  displayChocoList(B, "B (unsorted)", BHead);
  sortChocoList(&B, &BHead);
  displayChocoList(B, "B (sorted)", BHead);



	// pause();

  return 0;
}

/************************************************************
 *  Problem 0 Completed Functions                           *
 ************************************************************/
 
void pause(void)
{
	printf("\n\nPress any key to continue...");
	// getch();
	system("CLS");
}

void generateChocoRecords(void)
{
	Chocolate data[] = {
            {"TO1701", {"Toblerone", 135}, 150.75, 20},
						{"TO1703", {"Toblerone", 100}, 125.75, 60},
						{"TO1715", {"Toblerone", 50}, 90.75, 80},
						{"CA1550", {"Cadbury", 120}, 200.00, 30},
						{"HE1501", {"Hersheys", 100}, 100.50, 10},
						{"MA1801", {"Mars", 100}, 150.75, 20},
						{"KI1201", {"Kitkat", 50}, 97.75, 40},
						{"FE1450", {"Ferrero", 100},150.50, 50},
						{"ME1601", {"Meiji", 75}, 75.50, 60},
						{"NE1301", {"Nestle", 100}, 124.50, 70},
						{"LI1525", {"Lindt", 100}, 175.50, 80},
						{"VA1545", {"Valor", 120}, 149.50, 90},
						{"TA1455", {"Tango", 75}, 49.50, 100},
						{"FE1356", {"Ferrero", 200}, 250.75, 85},
		              };
    
             /**********************************************************************
              * Write the variable declaration and code fragment that will accomplish the task   *
              * below this comment.                                                                                                            *
             ***********************************************************************/  
    FILE* fp = fopen("chocoRecord_CB.bin", "wb");
    if(fp != NULL){
    	fwrite(data, sizeof(Chocolate), 14, fp);
	}
	fclose(fp);
} 


/************************************************************
 *  Problem 1 Function Definitions                          *
 ************************************************************/

/*********************************************************************************************************
*  initChocoList() - The function will initialize a new ChocoList to be empty. The new ChocoList is then *
* 					  returned to the calling function.                  								 *		
**********************************************************************************************************/ 
ChocoList initChocoList(void)
{
  ChocoList temp;
	int x;
  for (x = -1 ; x < CHOCO_SIZE-1 ; x++){
    temp.choco[x+1].nextChoco = x;
  }
  temp.avail = CHOCO_SIZE-1;
  temp.numChoco = 0;
  printf("Initialized ChocoList\n");
  return temp;
}

int allocSpace(ChocoList *CL){
  int newNode = CL->avail;
  if (newNode != -1){
    CL->avail = CL->choco[newNode].nextChoco;
  }
  return newNode;
}

void deallocSpace(ChocoList *CL, int ndx){
	if (ndx >= 0 && ndx < CHOCO_SIZE){
    CL->choco[ndx].nextChoco = CL->avail;
    CL->avail = ndx;
  }
}

void initCList(CList *head){
  *head = -1;
}

/************************************************************************************************************
*  populateChocoList() - The function will read a file called "chocoRecords.bin", and populate the ChocoList*
*						 with the records inside the file.	                 								*		
************************************************************************************************************/

void populateChocoList(ChocoList *CL, CList *head){
  FILE* fp;
  fp = fopen("chocoRecord_CB.bin", "rb");
  // printf("head = %d\n", *head);
  if (fp != NULL){
    Chocolate newChoco;
    while (fread(&newChoco, sizeof(Chocolate), 1, fp)){
      int newNode = allocSpace(CL);
      if (newNode != -1){
        // insertLast
        CList* trav;
        for (trav = head ; *trav != -1 ; trav = &CL->choco[*trav].nextChoco){};
        CL->choco[newNode].chocoProd = newChoco;
        CL->choco[newNode].nextChoco = -1;
        *trav = newNode;
        CL->numChoco++;
      }
    }
  }
  fclose(fp);
}

/************************************************************************************************************
*  displayChocoList() - The function will display the contents of the ChocoList	                 			*
************************************************************************************************************/
void displayChocoList(ChocoList CL, char listDesc[], CList head) 
{
	printf("\n\nElements of the Chocolate Product List :: %s", listDesc);
	printf("\n\n%-10s","ID");
	printf("%-15s","Description");
	printf("%10s","Weight");
	printf("%10s","Price");
	printf("%10s\n","Quantity");
	
	 
             /**********************************************************************
              * Write the variable declaration and code fragment that will accomplish the task   *
              * below this comment.                                                *
             ***********************************************************************/  
	CList trav;
	for(trav = head ; trav != -1; trav = CL.choco[trav].nextChoco){
		printf("%-10s%-15s%10d%10.2f%10d\n", 
      CL.choco[trav].chocoProd.chocoID, 
      CL.choco[trav].chocoProd.chocoDesc.name, 
      CL.choco[trav].chocoProd.chocoDesc.weight, 
      CL.choco[trav].chocoProd.chocoPrice, 
      CL.choco[trav].chocoProd.chocoQty);
	}	
	printf("\n\nTOTAL NUMBER OF CHOCO RECORDS:: %d", CL.numChoco);
}


/************************************************************
 *  Problem 2 Function Definition                           *
 ************************************************************/

/*************************************************************************************************************
*  insertLastUnique() - The function will insertLast into the ChocoList a new Chocolate X if the chocoID of X*
*						still does not exist in the list. If this is true, and there is still space inside   *
*						the ChocoList (denoted by the CHOCO_SIZE), then insert into the list.		 		 *
*						Else if the chocoID already exists, then update the price and weight of the record	 *
*						to be equal to the new Chocolate X. Also update the qty to be the sum of the old	 *
*						and new qty.											                 			 *
*************************************************************************************************************/
void insertLastUnique(ChocoList *CL, Chocolate X, CList *head){
  CList *trav;
  for (trav = head ; *trav != -1 && strcmp(CL->choco[*trav].chocoProd.chocoID, X.chocoID) != 0 ; trav = &CL->choco[*trav].nextChoco){};

  if (*trav != -1){
    CL->choco[*trav].chocoProd.chocoPrice = X.chocoPrice;
    CL->choco[*trav].chocoProd.chocoDesc.weight = X.chocoDesc.weight;
    CL->choco[*trav].chocoProd.chocoQty += X.chocoQty;
		printf("Choco Record: [%s] has been successfully updated.\n", X.chocoID);
  } else if (*trav == -1 && CL->numChoco != CHOCO_SIZE){
    CList newNode = allocSpace(CL);
    if (newNode != -1){
      CL->choco[newNode].chocoProd = X;
      CL->choco[newNode].nextChoco = -1;
      *trav = newNode;
      CL->numChoco++;
      printf("Choco Record: [%s] has been successfully inserted.\n", X.chocoID);
    }
  } else {
    printf("There is no more space to add chocolate [%s] to our ChocoList.\n", X.chocoID);
  }
}

/************************************************************
 *  Problem 3 Function Definition                           *
 ************************************************************/
 
/****************************************************************************************************************
*  insertSortedName() - The function will insert into the ChocoList a new Chocolate X. Insertion will be done   *
*						in ascending order, sorted by the name of the Chocolate. Insertion can only be possible *
*						if there is still space in the Chocolist (max elements is denoted by CHOCO_SIZE).		*									                 			 *
*****************************************************************************************************************/
void insertSortedName(ChocoList *CL, Chocolate X, CList* head){
  CList* trav;
  if (CL->numChoco < CHOCO_SIZE){
    for (trav = head ; *trav != -1 && strcmp(CL->choco[*trav].chocoProd.chocoDesc.name, X.chocoDesc.name) < 0 ; trav = &CL->choco[*trav].nextChoco){};
    CList newNode = allocSpace(CL);
    if (newNode != -1){
      CL->choco[newNode].chocoProd = X;
      CL->choco[newNode].nextChoco = *trav;
      *trav = newNode;
      printf("insertSorted(%s)!\n", X.chocoID);
    }
  }
}

/*********************************************************************************************************************
*  populateSorted() - The function will go through an unsorted ChocoList, and insert all if its elements into a new  *
*					  sorted ChocoList. This new list is returned to the calling function. This function will insert *
*					  using insertSortedName().																		 *									                 			 
*********************************************************************************************************************/
ChocoList populateSorted(ChocoList CL, CList head, CList *head2)
{
  ChocoList newList = initChocoList();
  CList trav;
  for (trav = head ; trav != -1 ; trav = CL.choco[trav].nextChoco){
    insertSortedName(&newList, CL.choco[trav].chocoProd, head2);
  }
  return newList;
}

/************************************************************
 *  Problem 4 Function Definition                           *
 ************************************************************/
/*********************************************************************************************************************
*  deleteAllChoco() - The function will go through the ChocoList, and delete all the elements with the same name as  *
*					  the passed chocoName. At the end of the function, display the total number of deleted nodes,   *
*					  and return that number to the calling function.												 *																		 *									                 			 
*********************************************************************************************************************/
int deleteAllChoco(ChocoList *CL, char chocoName[], CList *head){
  int totalDeleted = 0;
  CList *trav;
  CList temp;

  if (CL->numChoco > 0){
    for (trav = head ; *trav != -1 ;){
      if (strcmp(CL->choco[*trav].chocoProd.chocoDesc.name, chocoName) == 0){
        temp = *trav;
        *trav = CL->choco[temp].nextChoco;
        deallocSpace(CL, temp);
        CL->numChoco--;
        totalDeleted++;
        printf("Deleted [%s]!\n", chocoName);
      } else {
        trav = &CL->choco[*trav].nextChoco;
      }
    }
  }

  return totalDeleted;
}
 
 /************************************************************
 *  Problem 5 Function Definition                           *
 ************************************************************/
/*************************************************************************************************************************
*  sortChocoList() - The function will go through a ChocoList and sort the values in ascending order using selectionSort.*												 *																		 *									                 			 
*************************************************************************************************************************/
void sortChocoList(ChocoList* CL, CList* head) {
	CList step, min, smallest;
	for (step = *head ; step != -1 ; step = CL->choco[step].nextChoco){
		for (min = step, smallest = step ; smallest != -1 ; smallest = CL->choco[smallest].nextChoco){
			if (strcmp(CL->choco[smallest].chocoProd.chocoDesc.name, CL->choco[min].chocoProd.chocoDesc.name) < 0){
				min = smallest;
			}
		}
		Chocolate temp;
		temp = CL->choco[step].chocoProd;
		CL->choco[step].chocoProd = CL->choco[min].chocoProd;
		CL->choco[min].chocoProd = temp;
		printf("Swapped!\n");
	}
}


