#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 5

//* Version 1
// List is a structure containing an array and variable count. 
// count represents the actual number of elements in the array. If MAX is the size of the array, count <= MAX

typedef struct node {
  int elem[MAX];
  int count;
} List;

//* Initialize
// Takes a List* as a parameter and returns void
void init_ver1(List* main);

// Takes no parameter but instead RETURNS the newly created List back to the calling function
List init_ver2();

//* The difference between init_ver1 and init_ver2 is that ver1 takes pass-by-address as parameter while ver2 RETURNS the newly created list to the calling function and no parameters.

// Makes the List empty by setting count to 0
void makeNull(List* main);

//* Other operations
// Insert - inserts an element into the array list if there is space.
void insert(List* main, int newData);

// Delete - deletes an element from the array list and subtracts 1 from count
void delete(List* main, int delete);

// Member/Locate - returns true if given element is found in the array list, else false
bool member(List main, int find);

int main(){
  List Dogs;

  // Initialization
  init_ver1(&Dogs);
  Dogs = init_ver2();

  // Insert
  insert(&Dogs, 5);
  insert(&Dogs, 10);
  insert(&Dogs, 15);
  insert(&Dogs, 20);
  insert(&Dogs, 25);
  insert(&Dogs, 30);    //  Should not be possible since List has reached MAX size

  // Member
  member(Dogs, 15);     //  Should return true
  member(Dogs, 30);     //  Should return false

  // Delete
  delete(&Dogs, 5);
  delete(&Dogs, 20);
  delete(&Dogs, 25);
  delete(&Dogs, 10);
  delete(&Dogs, 15);
  delete(&Dogs, 99);    //  Should not be possible since count is == 0
}

//* Initialize
void init_ver1(List* main){
  // Set count to 0 to initialize your array list
  main->count = 0;
}
List init_ver2(){
  List newList = {0,0};
  // List newList = {0};
  return newList;
}

//* Other operations
void insert(List* main, int newData){
  // Always remember to check for space. If there is space, insert.
  if (main->count < MAX){
    main->elem[main->count] = newData;
    main->count++;
  } else {
    printf("There is no space left in the list.\n");
  }
}

void delete(List* main, int delete){
  int x;

  // We must check if there is no elements in the list because we can't delete an element if in the first place, no elements to be deleted EXISTS in the first place.
  if (main->count > 0){
    // First loop is to find if the element to be deleted exists.
    for (x = 0 ; x < MAX && main->elem[x] != delete ; x++){};

    // If it exists, then proceed to swap.
    if (x < MAX){
      for (; x < MAX ; x++){
        main->elem[x] = main->elem[x+1];
      }
      main->count--;
    } else {
      printf("Element to be deleted does not exist.\n");
    }
  } else {
    printf("Your list is empty.\n");
  }
}

bool member(List main, int find){
  int x;

  // Empty loop to find the element based on condition.
  for (x = 0 ; x < MAX && main.elem[x] != find ; x++){};

  // if x < MAX, that means it stopped somewhere in between 0-4 which may have elements.
  // if x reached MAX, which is 5 in this case, it means that it did not find any elements that was equal to "find", therefore return false
  return (x < MAX) ? true : false;
}





