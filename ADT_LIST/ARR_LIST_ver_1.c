//* Array Implementation (Version 1)  
// List is a structure containing an array and variable count
// Note : count represents the actual number of elements in the array
// If MAX is the size of the array, count <= MAX

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10

typedef struct node {
  int arr[MAX];
  int count;
} LIST;

typedef enum { TRUE, FALSE } Boolean;

// Given the list as parameter, set count to 0.
void init_ver1(LIST *main);

// Set the count field to 0 of a locally declared list, which is returned to the calling function.
LIST init_ver2();


void display(LIST main);

void insert();

void delete();

void member();

void locate();

int findElem(LIST *main, int find);

// The function will insert a new given element in the given list at the 1st position if there is still space in the list. This is done by moving existing elements 1 index higher to make room for the new element and updating necessary variables.
void insertFirst(LIST *main, int newNum);

int deleteElem(LIST *main, int delete);

int main(){
  LIST usc_record;

  init_ver1(&usc_record);

  usc_record = init_ver2();

  insertFirst(&usc_record, 5);
  insertFirst(&usc_record, 10);
  insertFirst(&usc_record, 15);
  insertFirst(&usc_record, 20);
  insertFirst(&usc_record, 25);

  display(usc_record);

  deleteElem(&usc_record, 20);

  display(usc_record);

  deleteElem(&usc_record, 5);
  deleteElem(&usc_record, 25);

  display(usc_record);

  deleteElem(&usc_record, 15);
  deleteElem(&usc_record, 10);

  display(usc_record);

}

// Given the list as parameter, set count to 0.
void init_ver1(LIST *main){
  main->count = 0;
  printf("Successfully initialized count to 0.\n");
}

// Set the count field to 0 of a locally declared list, which is returned to the calling function.
LIST init_ver2(){
  LIST newList;
  newList.count = 0;

  printf("Successfully initialized count to 0.\n");

  return newList;
}

int findElem(LIST *main, int find){
  int i = 0;
  int found;

  for(; i < main->count && main->arr[i] != find ; i++){};
  found = i == main->count  ? FALSE : TRUE;

  if(found == TRUE){
    printf("Found the element %d at index [%d]\n", find, i);
  } else {
    printf("%d is not found in the array.\n", find);
  }

  return found;
}

void insertFirst(LIST *main, int newNum){
  int i;

  // Check if there is still space in the list
  if (main->count != MAX){
    for (i = main->count; i != 0 ; i--){
      main->arr[i] = main->arr[i-1];
    }
    main->arr[0] = newNum;
  } else {
    printf("No space.\n");
  }

  if (main->arr[0] == newNum){
    printf("Successfully inserted %d in the array list.\n", newNum);
    main->count++;
  }
}

void display(LIST main){
  int i = 0;
  for (; i < main.count ; i++){
    printf("[%d]", main.arr[i]);
  }
  printf("\n");
}

int deleteElem(LIST *main, int delete){
  int i = 0, x = 0;
  int found;

  for(; main->arr[i] != delete ; i++){};
  found = i == main->count ? 0 : 1;
  
  if (found == 1){
    printf("Deleted %d from the array list.\n", delete);
  }
  
  for(x = i ; x < main->count ; x++){
    main->arr[x] = main->arr[x+1];
  }
  main->count--;
  return found;
}