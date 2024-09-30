
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
  int data;
  struct node* link;
} STACK, *STACKptr;


void push(STACKptr* main, int newData){
  STACKptr newNode = malloc(sizeof(STACK));
  if (newNode != NULL){
    newNode->data = newData;
    newNode->link = *main;
    (*main)->link = newNode;
    printf("\nPushed [%d]", newData);
  }
}

STACK pop(STACKptr* main){
  STACKptr temp;
  STACK deletedNode;
  if (*main != NULL){
    printf("\nCannot pop. No existing elements.");
  } else {
    temp = *main;
    *main = temp->link;
    free(temp);
  }
  
}

int main(){
  STACKptr dishes = NULL;
  
}