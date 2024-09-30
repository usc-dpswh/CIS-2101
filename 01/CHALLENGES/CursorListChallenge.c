#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX 5

typedef struct {
  char box[MAX];
  int next[MAX];
} CursorList;

int isMember(CursorList main, int find);

int main(){
  CursorList CL = {{'0','A','B','C','D'},{1,3,4,2,0}};
  printf("%d\n", isMember(CL, 'C'));
  printf("%d\n", isMember(CL, 'E'));
}

int isMember(CursorList main, int find){
  int* trav;
  if (main.next != 0){
    for (trav = &main.next[0] ; *trav != 0 && main.box[*trav] != find ; trav += 1){};
  }
  return (*trav != 0) ? 1 : 0;
}