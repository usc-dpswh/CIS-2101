#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 7
#define EMPTY '.'
#define DELETED '?'

typedef char Dictionary[MAX];

void init(Dictionary main);
int Hash(char input);
void insertElem(Dictionary main, char newData);

int main(){
  Dictionary Japanese;

  init(Japanese);
}

void init(Dictionary main){
  int x;

  for (x = 0 ; x != MAX ; x++){
    main[x] = EMPTY;
  }
}

int Hash(char input){
  
}
void insertElem(Dictionary main, char newData);

