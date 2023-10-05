#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h>
#include <ctype.h>

#define MAX 10
// Packing density should ideally be 80% of our MAX
#define PACKING_DENSITY (int)(MAX * 0.8)
#define EMPTY '?'
#define DELETED '!'

typedef struct {
  struct {
    char elem;
    int link;
  } NodeType[MAX];
  
  int Avail;
} Dictionary;

Dictionary initDictionary(void);
int getHash(char data);
bool isMember(Dictionary dict, char data);
void insertElem(Dictionary *dict, char data);
void deleteElem(Dictionary *dict, char data);
void displayDictionary(Dictionary dict);

int main(){
  Dictionary Merriam;

  Merriam = initDictionary();

  insertElem(&Merriam, 'A');
  // insertElem(&Merriam, 'B');
  // insertElem(&Merriam, 'U');
  insertElem(&Merriam, 'I');
  insertElem(&Merriam, 'Q');

  displayDictionary(Merriam);
}

Dictionary initDictionary(void){
  // We initialize two areas of our Dictionary.
  Dictionary newDic;
  int x;
  // loop to initialize PRIME DATA AREA
  for (x = 0 ; x < PACKING_DENSITY ; x++){
    newDic.NodeType[x].elem = EMPTY;
    newDic.NodeType[x].link = -1;
  }

  // loop to initialize SYNONYM AREA
  for (x = PACKING_DENSITY ; x < MAX-1 ; x++){
    newDic.NodeType[x].elem = EMPTY;
    newDic.NodeType[x].link = x+1;
  }
  newDic.NodeType[x].elem = EMPTY;
  newDic.NodeType[x].link = -1;
  newDic.Avail = PACKING_DENSITY;
  return newDic;
}

int getHash(char data){
  return (toupper(data) - 'A') % PACKING_DENSITY;
}

bool isMember(Dictionary dict, char data){
  int hashVal;

  for (hashVal = getHash(data) ; dict.NodeType[hashVal].link != -1 && dict.NodeType[hashVal].elem != data ; hashVal = dict.NodeType[hashVal].link){}

  return dict.NodeType[hashVal].elem == data;
}

int allocSpace(Dictionary *dict){
  int retVal = dict->Avail;

  if (retVal != -1){
    dict->Avail = dict->NodeType[retVal].link;
  }
  return retVal;
}

void insertElem(Dictionary *dict, char data){
  int hashVal;

  if (!isMember(*dict, data)){
    hashVal = getHash(data);

    // if block if no collision
    if (dict->NodeType[hashVal].elem == EMPTY || dict->NodeType[hashVal].elem == DELETED){
      dict->NodeType[hashVal].elem = data;

    } else {
      // else block is if there is collision
      int newNode = allocSpace(dict);
      int *trav;

      for (trav = &(dict->NodeType[hashVal].link) ; *trav != -1 ; trav = &(dict->NodeType[*trav].link)){}

      if (newNode != -1){
        // dict->Avail = dict->NodeType[newNode].link;
        dict->NodeType[newNode].elem = data;
        // dict->NodeType[newNode].link = dict->NodeType[hashVal].link;
        dict->NodeType[newNode].link = *trav;
        *trav = newNode;
      }
    }
  }
}

// void displayDictionary(Dictionary dict){
//   int x;
//   int trav;

//   for (x = 0 ; x < PACKING_DENSITY ; x = dict.NodeType[x].link){
//     printf("[%d]", x);
//     for (trav = x ; trav != -1 ; trav = dict.NodeType[trav].link){
//       printf("%2c", dict.NodeType[x].elem);
//     }
//   }
//   printf("\n");
// }

void displayDictionary(Dictionary dict) {
    int index;
    int trav;

    for (index = 0; index < PACKING_DENSITY; index++) {
        printf("%2d[ %c | %2d ] ", 
          index, dict.NodeType[index].elem,
          dict.NodeType[index].link);

        for (trav = dict.NodeType[index].link; trav != -1;
            trav = dict.NodeType[trav].link) {
            printf("%2d[ %c | %2d ] ", 
              trav, 
              dict.NodeType[trav].elem,
              dict.NodeType[trav].link);
        }
        printf("\n");
    }
}