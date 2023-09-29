#ifndef UID_COMPUTER_WORD_H
#define UID_COMPUTER_WORD_H

#include <stdbool.h>
#include <stdio.h>

typedef unsigned char Set;

// UID Functions
void insertElem(Set *set, char elem);
void deleteElem(Set *set, char elem);
bool isMember(Set set, char elem);
Set setUnion(Set a, Set b);
Set setIntersection(Set a, Set b);
Set setDifference(Set a, Set b);

// General Functions
void initSet(Set *set);
void makeNull(Set *set);
void displaySet(Set set);

// Computer Word Functions
void displayBitPattern(Set set);

void insertElem(Set *set, char elem) {
    *set |= (1 << elem);
}

void deleteElem(Set *set, char elem) {
    *set &= ~(1 << elem);
}

bool isMember(Set set, char elem) {
    return (set & (1 << elem)) != 0;
}

Set setUnion(Set a, Set b) {
    return a | b;
}

Set setIntersection(Set a, Set b) {
    return a & b;
}

Set setDifference(Set a, Set b) {
    return a & (~b);
}

void initSet(Set *set) {
    *set = 0;
}

void makeNull(Set *set) {
    *set = 0;
}

void displaySet(Set set) {
    Set mask = 1 << (sizeof(Set) * 8 - 1);
    int elem;

    puts("\n[Cursor-based]\n");

    for (elem = sizeof(Set) * 8 - 1; elem >= 0; elem--, mask >>= 1) {
        if (set & mask) {
            printf("%d ", elem);
        }
    }

    printf("\n");
}

void displayBitPattern(Set set) {
    Set mask;

    puts("\n[Cursor-based]\n");

    for (mask = 1 << (sizeof(Set) * 8 - 1); mask > 0; mask >>= 1) {
        printf("%d", (set & mask) ? 1 : 0);
    }

    printf("\n");
}

#endif // COMPUTER_WORD_H