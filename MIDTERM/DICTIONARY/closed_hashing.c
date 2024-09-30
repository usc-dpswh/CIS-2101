#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 5
#define EMPTY -1
#define DELETED -2

typedef int DICTIONARY[MAX];

typedef struct node {
  DICTIONARY A;
  int count;
} SET, *SETptr;

void initDictionary(DICTIONARY main);
int hash(DICTIONARY main, int elem);
bool isMember(DICTIONARY main, int find);
void insert(DICTIONARY main, int newData);
void display(DICTIONARY main);
void delete(DICTIONARY main, int delete);
DICTIONARY* insertSorted(DICTIONARY main);

int main(){
  DICTIONARY Webster;
  DICTIONARY* sortedWebster;
  initDictionary(Webster);
  
  insert(Webster, 3);
  insert(Webster, 3);     // test case: uniqueness
  insert(Webster, 33);    // test case: collision
  insert(Webster, 44);    // test case: displacement
  insert(Webster, 21);    // test case: N\A
  insert(Webster, 93);    // test case: collision
  insert(Webster, 50);    // test case: full dictionary

  delete(Webster, 93);    // test case: delete feature
  display(Webster);

  insert(Webster, 73);    // test case: insert at DELETED

  display(Webster);

  sortedWebster = insertSorted(Webster);
  display(*sortedWebster);
}

void initDictionary(DICTIONARY main){
  int x;
  for (x = 0 ; x < MAX ; x++){
    main[x] = EMPTY;
  }
  printf("Initialized dictionary.\n");
}
int hash(DICTIONARY main, int elem){
  return elem % 10;
}
bool isMember(DICTIONARY main, int find){
  int hashValue = hash(main, find);
  int count;
  int x;
  for (x = hashValue, count = 0 ; count != MAX && main[x] != EMPTY && main[x] != DELETED && main[x] != find ; x = (x + 1) % MAX, count++){};
  return main[x] == find;
}
void insert(DICTIONARY main, int newData){
  int hashValue = hash(main, newData);
  int count;
  if (!isMember(main, newData)){
    for (count = 0 ; count < MAX && main[hashValue] != EMPTY && main[hashValue] != DELETED ; hashValue = (hashValue + 1) % MAX, count++){};
    if (count < MAX){
      main[hashValue] = newData;
      printf("Inserted %d\n", newData);
    } else {
      printf("Your dictionary is full.\n");
    }
  } else {
    printf("Not unique.\n");
  }
}
void display(DICTIONARY main){
  int x;
  printf("HASH TABLE\n");
  printf("%8s|%s\n", "INDEX", "VALUE");
  printf("=============================\n");
  for (x = 0 ; x < MAX ; x++){
    printf("%8d|%8d\n", x, main[x]);
  }
}
void delete(DICTIONARY main, int delete){
  int x;
  for (x = hash(main, delete) ; main[x] != EMPTY && main[x] != DELETED && main[x] != delete; x = (x+1) % MAX){};
  if (isMember(main, delete)){
    main[x] = DELETED;
    printf("Deleted [%d]\n", delete);
  } else {
    printf("The element to be deleted [%d] does not exist.\n", delete);
  }
}
DICTIONARY* insertSorted(DICTIONARY main){
  DICTIONARY* new;
  new = (DICTIONARY*)malloc(sizeof(DICTIONARY));
  if (new != NULL){
    int x,y,z;
    
    for (x = 0 ; x < MAX ; x++){
      for (y = 0 ; y < MAX && main[x] > new[y] ; y++){};
      for (z =)
    }
  }
  return new;
}