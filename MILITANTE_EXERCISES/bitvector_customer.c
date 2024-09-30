#include <stdio.h>
#include <stdbool.h>
#define MAX 8

typedef enum {
  STUDENT,
  DOCTOR,
  DENTIST,
  ENGINEER,
  ARCHITECT,
  DAYTRADER,
  SLAVE,
  PRESIDENT
} Job;

typedef int BitVector[MAX];

void initialize(BitVector A);
void determine(BitVector A);

int main(){
  BitVector A;
  initialize(A);
  BitVector student1 = {1,0,0,1,0,0,0,0};
  determine(student1);
  return 0;
}

void initialize(BitVector A){
  int x;
  for (x = 0 ; x < MAX ; x++){
    A[x] = 0;
  }
  printf("Initialized BitVector.\n");
}

void determine(BitVector A){
  int x;
  for (x = 0; x < MAX; x++){
    if (A[x] == 1) {
      switch(x) {
        case STUDENT:
          printf("Student\n");
          break;
        case DOCTOR:
          printf("Doctor\n");
          break;
        case DENTIST:
          printf("Dentist\n");
          break;
        case ENGINEER:
          printf("Engineer\n");
          break;
        case ARCHITECT:
          printf("Architect\n");
          break;
        case DAYTRADER:
          printf("Daytrader\n");
          break;
        case SLAVE:
          printf("Slave\n");
          break;
        case PRESIDENT:
          printf("President\n");
          break;
        default:
          break;
      }
    }
  }
}

