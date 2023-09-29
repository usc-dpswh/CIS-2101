//* Array Implementation (Version 2)
// List is a pointer to a structure containing an array and variable count

#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct node {
  char Elements[MAX];
  int count;
} *LIST;

int main(){
  // Pointer to a structure
  LIST L;
}