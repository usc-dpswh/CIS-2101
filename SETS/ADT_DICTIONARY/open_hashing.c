#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct node {
  int elem;
  struct node* link;
} *LIST;

typedef LIST Dictionary[MAX];

void init(Dictionary main);
int Hash(int num);
void insertElem(Dictionary main, int newData);
void deleteElem(Dictionary main, int deleteThis);
bool isMember(Dictionary main, int number);
void displayDictionary(Dictionary main);


int main(){
  Dictionary Webster;
  
  init(Webster);

  insertElem(Webster, 0);
  insertElem(Webster, 10);
  insertElem(Webster, 20);
  insertElem(Webster, 45);
  insertElem(Webster, 37);
  insertElem(Webster, 78);
  insertElem(Webster, 48);
  insertElem(Webster, 99);
  insertElem(Webster, 9);

  displayDictionary(Webster);

  deleteElem(Webster, 9);

  displayDictionary(Webster);

  isMember(Webster, 9);
  isMember(Webster, 45);

  return 0;
}

void init(Dictionary main){
  int x;
  
  for (x = 0 ; x < MAX ; x++){
    main[x] = NULL;
  }
}
int Hash(int num){
  return num % 10;
}

bool isMember(Dictionary main, int number){
  LIST *trav;
  int hashVal = Hash(number);

  for (trav = &(main[hashVal]) ; *trav != NULL && (*trav)->elem != number ; trav = &(*trav)->link){};

  printf("isMember(%d) = %s\n", number, (*trav == NULL) ? "FALSE" : "TRUE");
  return (*trav == NULL) ? 0 : 1;
}

void insertElem(Dictionary main, int newData){
  LIST *trav;
  int hashVal = Hash(newData);

  printf("insertElem(%d)\n", newData);

  for (trav = &(main[hashVal]) ; *trav != NULL ; trav = &(*trav)->link){}

  if (!isMember(main, newData)) {
    LIST newNode = (LIST)malloc(sizeof(struct node));

    if (newNode != NULL){
      newNode->elem = newData;
      newNode->link = *trav;
      *trav = newNode;
    }
  } else {
    printf("[%d] is an existing element. Failed to insert element.\n");
  }
}
void deleteElem(Dictionary main, int deleteThis){
  LIST temp;
  LIST *trav;
  int hashVal = Hash(deleteThis);


  if (isMember(main, deleteThis)){

    // can we remove the condition at line 81 *trav != NULL since we already checked
    // if the element to be deleted is a member through the isMember() ?
    // if isMember() returns TRUE, we execute the loop, else we don't.
    // So, if isMember() returns TRUE, it means that the element exists inside the
    // array so we don't have to check if the loop reaches the end with *trav != NULL since the isMember() function did it for us already.
    for (trav = &(main[hashVal]) ; *trav != NULL && (*trav)->elem != deleteThis ; trav = &(*trav)->link){}

    temp = *trav;
    *trav = temp->link;
    free(temp);
  }

}
void displayDictionary(Dictionary main){
  LIST *trav;
  int x;

  for (x = 0 ; x != MAX ; x++){
    printf("[%d] => ", x);

    for (trav = &(main[x]) ; *trav != NULL ; trav = &(*trav)->link){

      printf("%d => ", (*trav)->elem);
    }
    printf("\n");
  }
  printf("\n\n");
  
}