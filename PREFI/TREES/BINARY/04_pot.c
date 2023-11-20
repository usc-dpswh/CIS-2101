#include <stdio.h>
#include <stdlib.h>
#define MAX 15

typedef struct heap {
  int elem[MAX];
  int count;
} Heap;

void Initialize(Heap *main);
void Populate(Heap *main, int values[]);
void Display(Heap main);

// Heapify
void Heapify(Heap *main,    int type);
void HeapifyMin(Heap *main, int parent);
void HeapifyMax(Heap *main, int parent);

// Insert
void Insert(Heap *main,     int newData);
void InsertMin(Heap *main,  int newData);
// void InsertMax(Heap *main,  int newData);

// __order
// void Preorder(Heap main);

int main(){
  Heap harryPOTter = {{6,7,4,3,1,2,5,8}, 8};
  // int values[MAX] = {6,7,4,3,1,2,5,8};

  // Initialize(&harryPOTter);
  // Populate(&harryPOTter, values);
  Display(harryPOTter);
  // printf("%d\n", harryPOTter.elem[9]);

  // InsertMin(&harryPOTter, 2);
  // InsertMin(&harryPOTter, 1);

  // Display(harryPOTter);

  // Heapify(&harryPOTter, 1);
  Heapify(&harryPOTter, 2);
  Display(harryPOTter);
}

void Display(Heap main){
  int x;

  printf("{");
  for (x = 0 ; x < main.count ; x++){
    printf("%d%c", main.elem[x], (x == main.count-1) ? '}' : ',');
  }
  printf("\n");
}

void Initialize(Heap *main){
  main->count = 0;

  printf("==========================\n");
  printf("Initialized the POT.\n");
  printf("==========================\n");

}
// void Populate(Heap *main, int values[]){
//   int x;
  
//   for (x = 0 ; x < MAX && ; x++){
//     main->elem[x] = values[x];
//     main->count++;
//   }
  
//   printf("Populated the POT.\n");
//   printf("==========================\n");
// }
void Insert(Heap *main, int newData){
  if (main->count != MAX-1){
    main->count++;
    main->elem[main->count] = newData;
    printf("Inserted %d normally.\n", newData);
  }
}

void InsertMin(Heap *main, int newData){

  int child;
  int parent;
  int temp;

  if (main->count != MAX-1){
    main->count++;

    // Establish CHILD and PARENT indexes
    child = main->count - 1;
    parent = (child - 1) / 2;

    // We simply use the 'child' variable to insert our newData
    main->elem[child] = newData;

    // Condition is to make sure that the element inserted retains POT characteristic
    while (parent >= 0 && main->elem[parent] > main->elem[child]){

      // Swapping 
      temp = main->elem[parent];
      main->elem[parent] = main->elem[child];
      main->elem[child] = temp;

      // Update
      child = parent;
      parent = (child - 1) / 2;
    }
    printf("Successfully inserted %d!\n", newData);
  } else {
    printf("There is no more space in your POT.\n");
  }
}

void HeapifyMin(Heap *main, int parent){
  // Establish where the LC and RC are
  int LC = (parent * 2) + 1;
  int RC = (parent * 2) + 2;
  int small, temp;

  // The first condition is to check if your LC value is valid in the first place.
  // If it's not a valid value, meaning the element probably doesn't exist in the tree.
  if (LC <= main->count-1){
    // We first assume that the smallest value is the LC because in the first place,
    // when inserting our elements, we go from LEFT -> RIGHT, so, there would be a
    // possibility that the RC doesn't even exist yet.
    small = LC;

    // Naturally, we also check if RC exists or is a valid value. We then compare our RC
    // to our LC to check which child is lesser. Whichever is lesser, its value is assigned to our small variable.
    if (RC <= main->count-1 && main->elem[RC] < main->elem[LC]) { small = RC; }
    // Now that we know which is the lesser child, we can now perform our swapping between PARENT <--> CHILD.
    // Since for a minHeap, the parent should be LESSER THAN or EQUAL to its child, this is the condition.
    if (main->elem[parent] > main->elem[small]){
      // If condition is TRUE, perform swap logic below.
      temp = main->elem[parent];
      main->elem[parent] = main->elem[small];
      main->elem[small] = temp;

      // Recursive function. When the swapping happens, it is possible that POT characteristic is destroyed.
      // In order to maintain POT, we must pass in the swapped element's index.
      HeapifyMin(main, small);
    }
  }
}
void HeapifyMax(Heap *main, int parent){
  
  int LC = (parent * 2) + 1;
  int RC = (parent * 2) + 2;
  int big, temp;

  if (LC <= main->count-1){

    big = LC;

    if (RC <= main->count-1 && main->elem[RC] > main->elem[LC]) { big = RC; }

    if (main->elem[parent] < main->elem[big]){

      temp = main->elem[parent];
      main->elem[parent] = main->elem[big];
      main->elem[big] = temp;

      HeapifyMax(main, big);
    }
  }
}

void Heapify(Heap *main, int type){
  int parent;

  switch (type){  
    // HeapifyMin
    case 1:
      printf("Building your list into a MinHeap...\n");
      for (parent = (main->count-2) / 2 ; parent >= 0 ; parent--){
        HeapifyMin(main, parent);
        printf("MinHeap build successful.\n");
      }  
      break;
    // HeapifyMax
    case 2:
      printf("Building your list into a MaxHeap...\n");
      for (parent = (main->count-2) / 2 ; parent >= 0 ; parent--){
        HeapifyMax(main, parent);
      }
      printf("MaxHeap build successful.\n");
      break;
    default:
      printf("Not a valid choice.\n");
    break;
  }
}


// void insertMin(Set *A, int x) {
// 	int childPosition; //new elem
// 	int parentPosition; //parent of new elem
// 	if(A->last < MAX - 1) {
// 		A->last++;
// 		childPosition = A->last;
// 		A->elem[childPosition] = x;
// 		for(parentPosition = (childPosition - 1)/2; parentPosition >= 0 && A->elem[childPosition] < A->elem[parentPosition]; childPosition = parentPosition, parentPosition = (childPosition - 1)/2) {
// 			A->elem[childPosition] = A->elem[parentPosition];
// 			A->elem[parentPosition] = x;
// 		}
// 	}
// }

