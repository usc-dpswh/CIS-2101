#include <stdbool.h>
#include <stdio.h>

typedef unsigned char SET;

void insertElem(SET *, unsigned char);
void deleteElem(SET *, unsigned char);
bool isMember(SET, unsigned char);
SET setUnion(SET, SET);
SET setIntersection(SET, SET);
SET setDifference(SET, SET);
void displayBitPattern(SET);
void displayElem(SET);

int main(void) {
    SET carlo = 0;

    displayBitPattern(carlo);
    insertElem(&carlo, 5);
    insertElem(&carlo, 1);
    insertElem(&carlo, 0);

    displayBitPattern(carlo);
    displayElem(carlo);
    printf("%s",isMember(carlo,5)? "TRUE":"FALSE");
}

void insertElem(SET *A, unsigned char Elem) { *A |= 1 << Elem; }
void deleteElem(SET *A, unsigned char Elem) { *A &= ~(1 << Elem); }
bool isMember(SET A, unsigned char Elmo) { return A && (1 << Elmo); }
SET setUnion(SET A, SET B) { return A | B; }
SET setIntersection(SET A, SET B) { return A & B; }
SET setDifference(SET A, SET B) { return A & ~B; }
void displayBitPattern(SET A) {
    int x;
    for (x = 1 << sizeof(SET) * 8 - 1; x > 0; x >>= 1) {
        printf("%d", A & x ? 1 : 0);
    }
    printf("\n");
}

void displayElem(SET A) {
    int x = 1 << sizeof(SET) * 8 - 1, y;
    for (y = sizeof(SET) * 8 - 1; x > 0; x >>= 1, y--) {
        if (x & A) {
            printf("%d", y);
        } else {
            printf(" ");
        }
    }
    printf("\n");
}