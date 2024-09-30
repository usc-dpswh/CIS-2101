#include <stdio.h>

#define MAX 8
typedef int BV_SET[MAX];
typedef unsigned char CW_SET;

int findSmallestElem(BV_SET main);
int findSmallestElemCW(CW_SET main);

int main(){
    BV_SET A = {1,0,0,1,1,0,1,0};   // 1
    printf("%d\n", findSmallestElem(A));
    BV_SET B = {1,0,0,1,1,0,0,0};   // 3
    printf("%d\n", findSmallestElem(B));

    CW_SET C = 0b00100011; // Initialize using binary representation
    printf("%d\n", findSmallestElemCW(C));

    return 0;
}

int findSmallestElem(BV_SET main){
    int x, retval;
    for (x = MAX-1, retval = 0 ; x >= 0 && main[x] != 1 ; x--, retval++) {}
    return x >= 0 ? retval : -1;
}

int findSmallestElemCW(CW_SET main){
    int mask, x;
    // for (mask = 1 >> (sizeof(CW_SET) * 0), x = 0 ; mask > 0 && mask && !(mask & main); mask <<= 1, x++) {}

    for (mask = 1 << sizeof(CW_SET) * 1, x = 0; mask != 0 && mask && !(main & mask) ; mask <<= 1, x++); 
    return x;
}
