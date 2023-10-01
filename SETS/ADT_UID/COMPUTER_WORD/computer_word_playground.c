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

  printf("SET B\n");
  insertElem(&B, 2);
  insertElem(&B, 7);
  insertElem(&B, 5);
  insertElem(&B, 1);

  displayBitPattern(A, 'A');
  displayBitPattern(B, 'B');

  // Showcasing union { A | B }
  C = setUnion(A, B);
  displayBitPattern(C, 'C');

  // Showcasing intersection { A ∩ B }
  C = setIntersection(A, B);
  displayBitPattern(C, 'C');

  // Showcasing difference { A — B }
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
  *main = *main | (1 << elem); 
  printf("Added [%d] to SET...\n", elem);
}

void deleteElem(SET *main, unsigned char elem){
  *main = *main & ~(1 << elem);
}

bool isMember(SET main, unsigned char elem){
  return main & (1 << elem);
  
  // This will return TRUE because suppose our elem is 3. We compare main to a bit value shifter to the left by 3.
  // main   10011010
  // elem   00001000
}

SET setUnion(SET A, SET B){
  printf("\nC = A U B\n");
  return A | B;
}

SET setIntersection(SET A, SET B){
  printf("\nC = A ∩ B\n");
  return A & B;
}

SET setDifference(SET A, SET B){
  printf("\nC = A — B\n");
  return A & ~B;
}

void displayBitPattern(SET main, char type){
  int mask;

  printf("Displaying SET %c\n", type);
  for (mask = 1 << sizeof(SET) * 8 - 1 ; mask > 0 ; mask = mask >> 1){
    printf("%d", main & mask ? 1 : 0);
  }
  printf("\n");

  // mask will be initilialized to 10000000
  // suppose we insert {7,3,4,1} into A, our main in this case will be 10011010
  // in line 44, it will print 1 or 0 depending on the evaluation of main & mask (meaning there should be 1s present in both main and mask)

  // main     10000000   00010000   00001000   00000010
  // mask     10011010   10011010   10011010   10011010
  // output   10000000   10010000   10011000   10011010
}

void displayElem(SET main){
  int mask = 1 << sizeof(SET) * 8 - 1;
  int counter;

  for (counter = sizeof(SET) * 8 - 1 ; mask > 0 ; mask >>= 1, counter--){
    printf("%d", (main & mask) ? counter : 0);
  }
  printf("\n");
}

// void displayElem(SET main) {
//     int x = 1 << sizeof(SET) * 8 - 1, y;
//     for (y = sizeof(SET) * 8 - 1; x > 0; x >>= 1, y--) {
//         if (x & main) {
//             printf("%d", y);
//         } else {
//             printf(" ");
//         }
//     }
//     printf("\n");
// }

