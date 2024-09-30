#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 5

//* Version 2
// List is a pointer to a structure containing an array and variable count.
// count represents the actual number of elements in the array. If MAX is the size of the array, count <= MAX

typedef struct node {
  int elem[MAX];
  int count;
} *List;

//* Initialize
// Takes a List as a parameter (pass-by-value) and returns void
void init_ver1(List* main);

// Takes no parameter but instead returns the newly created List back to the calling function
List init_ver2();

// Makes the List empty by setting count to 0
void makeNull(List main);

//* Other operations
// Insert - inserts an element into the array list if there is space.
void insert(List main, int newData);

// Delete - deletes an element from the array list and subtracts 1 from count
void delete(List main, int delete);

// Member/Locate - returns true if given element is found in the array list, else false
bool member(List main, int find);

int main(){
  List Cats;

  // Initialize
  init_ver1(&Cats);
  Cats = init_ver2();

  // Insert
  insert(Cats, 5);
  insert(Cats, 10);
  insert(Cats, 15);
  insert(Cats, 20);
  insert(Cats, 25);
  insert(Cats, 30);

  // Member
  printf("Member 5 = %d", member(Cats, 15));
  printf("Member 5 = %d", member(Cats, 99));

  // Delete
  delete(Cats, 5);
  delete(Cats, 25);
  delete(Cats, 15);
}

//* Initialize
void init_ver1(List* main){
  // Since List in arr_ver2 is a POINTER to a structure, we must call malloc() to create space for the struct that's to be pointed by out List variable.
  *main = (List)malloc(sizeof(struct node));
  if (*main != NULL){
    (*main)->count = 0;
  } else {
    printf("Malloc failed.\n");
  }
}

List init_ver2(){
  List newList;

  newList = (List)malloc(sizeof(struct node));
  if (newList != NULL){
    newList->count = 0;
  } else {
    printf("Malloc failed.\n");
  }
  return newList;
}

void makeNull(List main){
  main->count = 0;
}

//* Other operations
void insert(List main, int newData){
  // Remember to check if there is space first.
  if (main->count < MAX){
    main->elem[main->count] = newData;
    main->count++;
  } else {
    printf("No space left.\n");
  }
}

void delete(List main, int delete){
  int x;

  // 1) Check if any elements exist. If true, proceed.
  if (main->count > 0){
  // 2) Find the element to be deleted with a loop.
    for (x = 0 ; x < MAX && main->elem[x] != delete ; x++){};
  // 3) Begin shifting starting from the to-be-deleted element if it exists.
    if (x < MAX){
      for (; x < MAX ; x++){
        main->elem[x] = main->elem[x+1];
      }
    } else {
      printf("Element to be deleted does not exist.\n");
    }
  } else {
    printf("No elements to be deleted.\n");
  }
}

bool member(List main, int find){
  int x;
  for (x = 0 ; x < MAX && main->elem[x] != find ; x++){};
  return (x < MAX) ? true : false;
}