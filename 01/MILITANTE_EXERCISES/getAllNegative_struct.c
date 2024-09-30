// Author      :    Lanutan, Achille
// Date        :    01/30/2024
#include <stdio.h>
#include <stdlib.h>

// typedef struct node {
//   int A[]
// }

// Given a SIZE and an ARRAY OF INTEGERS, write the function getAllNegative(). The function will return an ARRAY containing all negative integers from the past array.
// First index of the returned function will hold the size.
int* getAllNegative (int size, int Arr[]);
int* getAllNegative_ver2 (int size, int Arr[]);
void display        (int Arr[]);

int main(){
  int A[] = {-2, -4, -5, -8, -9, -1};
  int* B;
  int size = sizeof(A)/sizeof(A[0]);

  B = getAllNegative_ver2(size, A);
  display(B);
}

int* getAllNegative (int size, int Arr[]){
  int *new;
  int count = 0;
  int x, y;
  // Get total number of negative numbers
  for (x = 0 ; x < size ; x++){
    Arr[x] < 0 ? (count++) : NULL;
  }
  // Malloc based on # of negative numbers
  new = (int*)malloc(sizeof(int)*(count+1));
  if (new != NULL){
    new[0] = count;
  // Loop to place negative numbers in new array
    for (x = 0 , y = 1 ; x < size ; x++){
      if (Arr[x] < 0){
        new[y] = Arr[x];
        y++;
      }
    }
  }
  return new;
}
int* getAllNegative_ver2 (int size, int Arr[]){
  int *new;
  int x, y;
  
  new = (int*)malloc(sizeof(int)*size);
  if (new != NULL){
    new[0] = 0;
  // Loop to place all negative numbers in new array
    for (x = 0 , y = 1 ; x < size ; x++){
  // If no more space, realloc
      if (new[0] == size-1){
        new = realloc(new, (size+1) * sizeof(int));
      } 
      if (Arr[x] < 0){
        new[y] = Arr[x];
        new[0]++;
        y++;
      }
    }
  }
  return new;
}
void display        (int Arr[]){
  int x;
  printf("ARRAY SIZE = %d\n", Arr[0]);
  for (x = 1 ; x <= Arr[0] ; x++){
    printf("%d ", Arr[x]);
  }
  printf("\n");
}
