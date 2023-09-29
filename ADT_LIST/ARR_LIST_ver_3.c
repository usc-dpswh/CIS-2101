//* Array Implementation (Version 3)
// List is a structure containing variable count and a pointer the first element of a dynamically allocated array.

#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct node {
  char *elemPtr;
  int count;
} LIST;

int main(){
  LIST L;

  char *Elements = (char*)malloc(sizeof(char) * MAX);

  L.elemPtr = Elements;
  L.count = 4;

  // Manually populate the array elements
  Elements[0] = 'H';
  Elements[1] = 'O';
  Elements[2] = 'P';
  Elements[3] = 'E';

  for(int i = 0 ; i < L.count ; i++){
    printf("%c ", *(L.elemPtr + i));
  }

  free(Elements);
}
