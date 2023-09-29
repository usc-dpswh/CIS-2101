#include <stdio.h>
#include <stdlib.h>

// INSERT / DELETE only from the beginning

typedef struct node {
  int data;
  int count;
  struct node* link;
} *LIST;

// typedef struct {

// }

LIST init();
void display(LIST *top);

void push(LIST *main, int newData);
void pop(LIST *head);
void peek(LIST *main);

void isEmpty(LIST *main);
void isFull(LIST *main);


int main(){

  LIST top = NULL;

  display(&top);

  push(&top, 3);
  display(&top);

  push(&top, 4); 
  display(&top);

  push(&top, 5);
  display(&top);

  pop(&top);
  display(&top);

  peek(&top);
  
  push(&top, 6);
  display(&top);
  
  push(&top, 7);
  display(&top);
  
  push(&top, 8);
  display(&top);

  isFull(&top);

  pop(&top);

  pop(&top);

  pop(&top);

  pop(&top);

  pop(&top);

  display(&top);

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

void display(LIST *top){
  LIST trav = *top;
  if (trav == NULL){
    printf("Stack underflow.\n");
  } else {
    for (; trav != NULL ; trav = trav->link){
      printf("[%d]\n", trav->data);
    }
    // printf("NULL\n");
  }
}

void push(LIST *main, int newData){

  printf("push(%d)\n", newData);

  LIST newNode = init();

  newNode->data = newData;
  newNode->link = *main;

  if (*main == NULL){
    newNode->link = NULL;
    *main = newNode;
  } else {
    *main = newNode;
  }
}

void pop(LIST *main){
  LIST delete = *main;

  printf("pop(%d)\n", (*main)->data);

  *main = (*main)->link;
  free(delete);
}

void peek(LIST *main){
  printf("peek()\n");
  printf("[%d]\n", (*main)->data);
}

void isEmpty(LIST *main){
  if (*main == NULL){
    printf("Stack underflow.\n");
  } else {
    printf("Stack is not empty.\n");
  }
}

void isFull(LIST *main){
  LIST *trav = main;
  int count = 0;

  for (; *trav != NULL ; trav = &(*trav)->link){ count++; }

  if (count == 5){
    printf("Stack overflow.\n");
  } else {
    printf("Stack is not full.\n");
  }
}