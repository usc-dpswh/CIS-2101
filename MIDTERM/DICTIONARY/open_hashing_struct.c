#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 10
#define EMPTY -1
#define DELETED -2

typedef struct node {
  int data;
  struct node* link;
} *SET;

typedef SET DICTIONARY[MAX];

void initDictionary (DICTIONARY main);
int hash            (int elem);
bool isMember       (DICTIONARY main, int find);
void insert         (DICTIONARY main, int newData);
void display        (DICTIONARY main);
void delete         (DICTIONARY main, int delete);

int main(){
  DICTIONARY Portugese;
  initDictionary(Portugese);

  insert(Portugese, 2);
  insert(Portugese, 32);
  insert(Portugese, 11);
  insert(Portugese, 55);
  insert(Portugese, 45);
  insert(Portugese, 49);
  insert(Portugese, 98);
  insert(Portugese, 25);
  insert(Portugese, 1);

  display(Portugese);

  delete(Portugese, 45);
  delete(Portugese, 2);
  delete(Portugese, 11);

  display(Portugese);
}

void initDictionary (DICTIONARY main){
  int x;
  for (x = 0 ; x < MAX ; x++){
    main[x] = NULL;
  }
  printf("Initialized dictionary.\n");
}
int hash            (int elem){
  return elem % 10;
}
bool isMember       (DICTIONARY main, int find){
  SET trav;
  int hashVal = hash(find);
  for (trav = main[hashVal] ; trav != NULL && trav->data != find ; trav = trav->link){};
  return trav != NULL;
}
void insert         (DICTIONARY main, int newData){
  int hashVal = hash(newData);
  SET* trav;
  for (trav = &main[hashVal] ; *trav != NULL ; trav = &(*trav)->link){};
  SET newNode = (SET)malloc(sizeof(struct node));
  if (newNode != NULL){
    newNode->data = newData;
    newNode->link = *trav;
    *trav = newNode;
  }
}
void display        (DICTIONARY main){
  SET trav;
  int x;
  for (x = 0 ; x < MAX ; x++){
    printf("[%d]", x);
    for (trav = main[x] ; trav != NULL ; trav = trav->link){
      printf("->[%d]", trav->data);
    }
    printf("%s\n", (trav != NULL) ? "->NULL" : "");
  }
}
void delete         (DICTIONARY main, int delete){
  SET* trav;
  SET temp;
  int hashVal = hash(delete);
  for (trav = &main[hashVal] ; *trav != NULL && (*trav)->data != delete ; trav = &(*trav)->link){};
  if (*trav != NULL){
    temp = *trav;
    *trav = temp->link;
    free(temp);
    printf("Deleted [%d]\n", delete);
  } else {
    printf("Not a valid number to delete.\n");
  }
}

