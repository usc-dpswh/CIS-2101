#include <stdio.h>
#include <stdlib.h>

// INSERT / DELETE only from the beginning

typedef struct node {
  int data;
  struct node* link;
} *LIST;

// typedef struct {

// }

LIST init();
void display(LIST head);
void push(LIST *main, LIST *top, int newData);
void pop(LIST *head);


int main(){
  LIST head = NULL;
  LIST top = NULL;
  
  // head = (LIST)malloc(sizeof(struct node));
  // head->data = 1;
  // head->link;

  // head->link = (LIST)malloc(sizeof(struct node));
  // head->link->data = 2;
  // head->link->link = NULL;

  display(head);

  push(&head, &top, 3);
  
  display(head);

  push(&head, &top, 4);
  
  display(head);

  // pop(&head);

  // display(head);

  // head->link->link = (LIST)malloc(sizeof(struct node));
  // head->link->link->data = 3;
  // head->link->link->link = NULL;
}

LIST init(){
  LIST newNode = (LIST)malloc(sizeof(struct node));

  if (newNode != NULL){
    return newNode;
  } else {
    printf("Memory allocation failed.");
  }
}

void display(LIST head){
  for (; head != NULL ; head = head->link){
    printf("%d -> ", head->data);
  }
  printf("NULL\n");
}

void push(LIST *main, LIST *top, int newData){

  printf("push()\n");

  top = main;
  LIST newNode = init();
  newNode->data = newData;
  newNode->link = NULL;

  if (*top == NULL){
    *top = newNode;
    top = &(*top)->link;
  } else {
    (*top)->link = newNode;
    top = &(*top)->link;
  }
  
}

void pop(LIST *main){
  printf("pop()\n");

  

}