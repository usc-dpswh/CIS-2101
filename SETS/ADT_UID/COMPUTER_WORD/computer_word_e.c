#include <stdbool.h>
#include <stdio.h>

typedef unsigned char SET;

void insertElem(SET *main, unsigned char elem);
void deleteElem(SET *main, unsigned char elem);
bool isMember(SET main, unsigned char elem);
SET setUnion(SET A, SET B);
SET setIntersection(SET A, SET B);
SET setDifference(SET A, SET B);
void displayBitPattern(SET main, char type);
void displayElem(SET main);

int main(){
  SET A = 0;
  SET B = 0;
  SET C = 0;

  printf("SET A\n");
  insertElem(&A, 7);
  insertElem(&A, 3);
  insertElem(&A, 4);
  insertElem(&A, 1);
  displayBitPattern(A, 'A');

  printf("SET B\n");
  insertElem(&B, 2);
  insertElem(&B, 7);
  insertElem(&B, 5);
  insertElem(&B, 1);

  displayBitPattern(B, 'B');

  // Showcasing union { A | B }
  printf("union\n");
  C = setUnion(A, B);
  displayBitPattern(C, 'C');

  // Showcasing intersection { A ∩ B }
  printf("intersection\n");
  C = setIntersection(A, B);
  displayBitPattern(C, 'C');

  // Showcasing difference { A — B }
  printf("difference\n");
  C = setDifference(A, B);
  displayBitPattern(C, 'C');

  printf("\ndisplayElem(A)\n");
  displayElem(A);

  printf("displayElem(B)\n");
  displayElem(B);

  printf("displayElem(C)\n");
  displayElem(C);

  printf("MEMBER = %s\n", (isMember(A, 3)) ? "TRUE" : "FALSE");

  printf("\ndeleteElem(&A, 4)\n");
  deleteElem(&A, 4);
  displayBitPattern(A, 'A');
}

void insertElem(SET *main, unsigned char elem){
  *main |= 1 << elem;
}
void deleteElem(SET *main, unsigned char elem){
  *main &= ~(1 << elem);
}
bool isMember(SET main, unsigned char elem){
  return main & (1 << elem);
}
SET setUnion(SET A, SET B){
  return A | B;
}
SET setIntersection(SET A, SET B){
  return A & B;
}
SET setDifference(SET A, SET B){
  return A & ~B;
}
void displayBitPattern(SET main, char type){
  int mask;

  for (mask = 1 << sizeof(SET) * 8 - 1 ; mask != 0 ; mask = mask >> 1){
    if (main & mask){
      printf("1");
    } else {
      printf("0");
    }
  }
  printf("\n");
}
void displayElem(SET main){
  int mask = 1 << sizeof(SET) * 8 - 1;
  int counter;

  for (counter = sizeof(SET) * 8 - 1 ; mask != 0 ; mask >>= 1 ,counter--){
    printf("%d", (mask & main) ? counter : 0);
  }
  printf("\n");
}

