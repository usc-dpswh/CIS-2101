#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX 9
#define EMPTY '.'
#define DELETED '?'

typedef char Dictionary[MAX];

void init(Dictionary main);
int Hash(char input);
bool isMember(Dictionary main, char elem);
void displayDic(Dictionary D);
void insert(Dictionary *D, char elem);
void delete(Dictionary *main, char delete);

int main(){
  Dictionary Japanese;

  init(Japanese);

  insert(&Japanese, 'A');
  // delete()
  insert(&Japanese, 'V');
  insert(&Japanese, 'V');
  // insert(&Japanese, 'C');
  // insert(&Japanese, 'W');
  // insert(&Japanese, 'P');
  // insert(&Japanese, 'X');
  // insert(&Japanese, 'Z');
  // insert(&Japanese, 'R');
  // insert(&Japanese, 'T');

  displayDic(Japanese);

  // delete(&Japanese, 'X');

  // displayDic(Japanese);

}

void init(Dictionary main){
  int x;

  for (x = 0 ; x != MAX ; x++){
    main[x] = EMPTY;
  }
}

int Hash(char input){
  return (toupper(input)-'A') % MAX;
}

bool isMember(Dictionary main, char elem){
  int count;
  int index;

  for (count = 0, index = Hash(elem) ; 
      count < MAX && main[index] != EMPTY && main[index] != elem ;
      count++, index = (index + 1) % MAX);

  return main[index] == elem;
}

void displayDic(Dictionary D) {
  int x;
  for (x = 0; x != MAX; ++x) {
    printf("[%d] => %c\n", x, D[x]);
  }
}

void insert(Dictionary *main, char elem) {
  int hashValue = Hash(elem);
  int x;

  // Remember that for sets, we must first check if it's unique via our isMember()
  if (!isMember(*main, elem)){
      
    for (x = hashValue ; (*main)[x] != DELETED && (*main)[x] != EMPTY ; x = (x + 1) % MAX){}

    if ((*main)[x] == DELETED || (*main)[x] == EMPTY){
      (*main)[x] = elem;
    }
  }
}

void delete(Dictionary *main, char delete){
  int hashVal = Hash(delete);
  int x;

  for (x = 0 ; x < MAX && (*main)[hashVal] != delete ; hashVal = (hashVal + 1) % MAX, x++){}

  if (x != MAX){
    (*main)[hashVal] = DELETED;
  }
}
