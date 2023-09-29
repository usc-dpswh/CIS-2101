//*  Array Implementation (Version 4)
//   Exercise

#include <stdio.h>
#include <stdlib.h>
#define MAX 5

typedef struct node {
  int *Elem;
  int count;
} *LIST;

//* Function prototypes

LIST initList();
void insertFirst(LIST main, int newData);
void updateAt(LIST main, int atIndex, int newData);
void deleteFirst(LIST main);
void displayList(LIST main);
void nextTo(LIST main, int index);

// Sorting Algorithms
void selectionSort(LIST main);
void bubbleSort(LIST main);

int main(){
  LIST usc = initList();

  insertFirst(usc, 5);
  insertFirst(usc, 10);
  insertFirst(usc, 15);
  insertFirst(usc, 20);
  
  displayList(usc);

  deleteFirst(usc);

  displayList(usc);

  updateAt(usc, 0, 20);

  displayList(usc);

  selectionSort(usc);

  displayList(usc);

  nextTo(usc, 1);

  nextTo(usc, 3);
}

LIST initList(){
  LIST newList = (LIST)calloc(1,sizeof(struct node));

  if (newList != NULL){

    newList->Elem = (int*)calloc(1,sizeof(int) * MAX);

    if(newList->Elem != NULL){
      printf("Malloc successful.\n");
      return newList;
    }
    
  } else {
    printf("Malloc failed.\n");
  }

}

void insertFirst(LIST main, int newData){
  // Check if there is space
  if (main->count != MAX){
    int x;
    
    for (x = main->count ; x > 0 ; x--){
      main->Elem[x] = main->Elem[x-1];
    }
    main->Elem[x] = newData;
    main->count++;
    printf("Inserted %d at 0 index.\n", newData);
  } else {
    printf("No space.\n");
  }
}

void updateAt(LIST main, int atIndex, int newData){
  // Check if index exists
  int x = 0;

  for (; x < main->count && x != atIndex ; x++){}

  // if selected index is a valid update position
  if (x == atIndex && main->count != 0){
    printf("Updated [%d] -> [%d] !\n", main->Elem[x], newData);
    main->Elem[x] = newData;
  } else {
    printf("Not a valid index for the current array.\n");
  }
}

void deleteFirst(LIST main){
  int x = 0, y = main->Elem[x];

  for (; x < main->count ; x++){
    main->Elem[x] = main->Elem[x+1];
  }
  
  // Check validity of operation
  if (y != main->Elem[x]){
    printf("Successfully deleted array elements.\n");
    main->count--;
  } else {
    printf("Something went wrong!\n");
  }

}
void displayList(LIST main){
  int x = 0;

  if (main->count == 0){

    printf("No elements to be displayed.\n");

  } else {

    for (; x < main->count ; x++){
      printf("%d\t", main->Elem[x]);
    }
    printf("\nDisplayed list!\n");

  }
}

void selectionSort(LIST main){
  int x,y, smallest, temp;

  for (x = 0 ; x < main->count-1 ; x++){
    smallest = x;
    for (y = x+1 ; y < main->count ; y++){
      if (main->Elem[y] < main->Elem[smallest]){
        smallest = y;
      }
    }
    
    if (x != smallest){
      temp = main->Elem[x];
      main->Elem[x] = main->Elem[smallest];
      main->Elem[smallest] = temp;
    }
  }
}

void bubbleSort(LIST main);

void nextTo(LIST main, int index){
  int x;

  for (x = 0 ; x < main->count && x < index ; x++){}

  if (x < main->count){
    printf("Number next to [%d] is [%d] !\n", main->Elem[x], main->Elem[index+1]);
  } else {
    printf("Not a valid index to check next number to!\n");
  }
}