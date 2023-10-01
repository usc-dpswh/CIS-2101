#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX 10
#define EMPTY '!'
#define DELETED '@'

// typedef enum { FALSE, TRUE } Boolean;

typedef struct {
  char data;
  int next;
} nodeType;

typedef struct {
  nodeType Nodes[MAX];
  int avail;
} Dictionary;

void initDic(Dictionary *D);
int hash(char input);
int allocSpace(Dictionary *D);
void displayDic(Dictionary D);
bool isMember(Dictionary D, char elem);
void insert(Dictionary *D, char elem);
void delete(Dictionary *D, char elem);

int main() {
  Dictionary myDic;

  initDic(&myDic);
  displayDic(myDic);

  printf("\n");

  insert(&myDic, 'A');
  insert(&myDic, 'B');
  insert(&myDic, 'K');

  displayDic(myDic);

  return 0;
}

void initDic(Dictionary *D) {
  int x;
  for (x = 0; x != (MAX * 50) / 100; ++x) {
    D->Nodes[x].data = EMPTY;
    D->Nodes[x].next = -1;
  }

  for (; x != MAX - 1; ++x) {
    D->Nodes[x].next = x + 1;
  }
  D->Nodes[MAX - 1].next = -1;
  D->avail = (MAX * 50) / 100;
}

int hash(char input) {
  return (toupper(input) - 'A') % MAX;
}

int allocSpace(Dictionary *D) {
  int retVal = D->avail;

  if (D->avail != -1) {
    D->avail = D->Nodes[D->avail].next;
  }
  return retVal;
}

void displayDic(Dictionary D) {
  int x, trav;
  for (x = 0; x != MAX / 2; ++x) {
    printf("[%d] => ", x);

    for (trav = x ; trav > -1 ; trav = D.Nodes[trav].next){
      printf("%c ", D.Nodes[trav].data);
    }
    printf("\n");
  }
}

bool isMember(Dictionary D, char elem){
  int trav;

  for (trav = 0 ; trav < (MAX * 50) / 100 && D.Nodes[trav].data != elem ; trav++){}

  return (trav < (MAX * 50) / 100);    // if trav reaches 5, that means the elem is unique
}

void insert(Dictionary *D, char elem) {
  int hashValue = hash(elem);

  if (!isMember(*D, elem)) {
    if (D->Nodes[hashValue].data == EMPTY) {
      D->Nodes[hashValue].data = elem;

    } else {
      int newNode = allocSpace(D);
      int *trav;

      for (trav = &(D->Nodes[hashValue].next); *trav != -1; trav = &(D->Nodes[*trav].next)) {}

      D->Nodes[newNode].data = elem;
      D->Nodes[newNode].next = *trav;
      *trav = newNode;
    }
  }
}