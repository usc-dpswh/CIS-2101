#include <stdio.h>
#include <stdlib.h>

// INSERT / DELETE only from the beginning

typedef struct node {
  int data;
  struct node* link;
} *LIST;

LIST init();
void display(LIST head);
void push(LIST *head, int newData);
void pop(LIST *head);

int main(){
  LIST head = NULL;
  
  // head = (LIST)malloc(sizeof(struct node));
  // head->data = 1;
  // head->link;

  // head->link = (LIST)malloc(sizeof(struct node));
  // head->link->data = 2;
  // head->link->link = NULL;

  // display(head);

  push(&head, 3);
  push(&head, 6);
  push(&head, 9);
  
  display(head);

  pop(&head);

  display(head);
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
    printf("[%d]\n", head->data);
  }
  printf("NULL\n");
}

void push(LIST *head, int newData){
  printf("push()\n");

  LIST newNode = init();
  newNode->data = newData;
  newNode->link = NULL;

  if (*head == NULL){
    *head = newNode;
  } else {
    LIST *trav = head;

    if(*trav != NULL){
      newNode->link = *trav;
      *trav = newNode;
    }
  }

}

void pop(LIST *main){
  printf("pop()\n");

  LIST *trav = main;
  LIST next = (*trav)->link;

  if (*trav == NULL){
    printf("Stack underflow.");
  } else {
    free(*trav);
    *trav = next;
  }

}