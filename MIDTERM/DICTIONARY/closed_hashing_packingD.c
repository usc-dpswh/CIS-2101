// Progressive Hashing

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10
#define EMPTY -1
#define DELETED -2
#define PACKING_DENSITY (int)(MAX * 0.5)

typedef int DICTIONARY[MAX];

typedef struct node {
  DICTIONARY A;
  int count;
  int last;
} SET, *SETptr;

void initDictionary   (SET* main);
bool isMember         (SET main, int find);
int hash              (int elem);
void insert           (SET* main, int newData);
void delete           (SET* main, int delete);
void display          (SET main);

int main(){
  SET Clients;
  initDictionary(&Clients);

  insert(&Clients, 4);
  insert(&Clients, 4);
  insert(&Clients, 54);
  insert(&Clients, 32);
  insert(&Clients, 31);
  insert(&Clients, 83);
  insert(&Clients, 93);
  insert(&Clients, 83);
  insert(&Clients, 75);
  insert(&Clients, 95);
  insert(&Clients, 96);
  insert(&Clients, 98);
  insert(&Clients, 97);

  display(Clients);

  delete(&Clients, 83);
  delete(&Clients, 95);
  delete(&Clients, 99);

  display(Clients);

  insert(&Clients, 41);
  insert(&Clients, 40);
  insert(&Clients, 9353290);

  display(Clients);
}

void initDictionary   (SET* main){
  int x;
  // Initializing the PRIME DATA AREA
  // This is the area where data that has no collisions go.
  for (x = 0 ; x < MAX ; x++){
    main->A[x] = EMPTY;
  }
  main->count = 0;
  main->last = PACKING_DENSITY;
  printf("Initialized dictionary.\n");
}
int hash              (int elem){
  return elem % PACKING_DENSITY;
}
bool isMember         (SET main, int find){
  int hashVal;
  int stopper;
  for (hashVal = hash(find), stopper = 0 ; stopper < MAX && main.A[hashVal] != find ; hashVal = (hashVal + 1) % MAX, stopper++){};
  return (stopper < main.count);
}
void insert           (SET* main, int newData){
  int hashVal, x;
  hashVal = hash(newData);

  // Check if there is space and if it's unique
  if (main->count < MAX && !isMember(*main, newData)){
    for (x = 0 ; x < main->count && main->A[hashVal] != EMPTY && main->A[hashVal] != DELETED ; hashVal = (hashVal + 1) % MAX, x++){};

    // Check if hashVal is in prime data area
    if (hashVal < PACKING_DENSITY){
      printf("[%d] Inserted into main dictionary.\n", newData);
      main->A[hashVal] = newData;
      main->count++;
    // If not in prime data area, start searching in synonyms area
    } else {
      for (x = PACKING_DENSITY ; x < MAX && main->A[x] != EMPTY && main->A[x] != DELETED ; x = (x + 1) % MAX){};
      // check if there is still space left to insert
      if (main->count < MAX){
        main->A[x] = newData;
        main->count++;
        // main->last++;
        printf("[%d] Inserted into synonyms area.\n", newData);
      } else {
        printf("[%d] No space.\n", newData);
      }
    }
  } else {
    printf("[%d] No space / Not unique.\n", newData);
  }
}
void delete           (SET* main, int delete){
  int stopper = 0, hashVal;
  for (hashVal = hash(delete) ; stopper < main->count && main->A[hashVal] != delete ; hashVal = (hashVal + 1) % MAX, stopper++){};
  if (stopper < main->count){
    main->A[hashVal] = DELETED;
    main->count--;
    printf("[%d] has been deleted from the dictionary.\n", delete);
  } else {
    printf("[%d] is not a valid number to delete.\n", delete);
  }
}
void display          (SET main){
  int x, y;
  printf("%-8s|%8s\n", "INDEX","VALUE");
  printf("=======================\n");
  printf("Prime Data:\n");
  for (x = 0 ; x < PACKING_DENSITY ; x++){
    printf("%8d|%8d\n", x, main.A[x]);
  }
  printf("Synonyms Area:\n");
  for (x = PACKING_DENSITY ; x < MAX ; x++){
    printf("%8d|%8d\n", x, main.A[x]);
  }
}