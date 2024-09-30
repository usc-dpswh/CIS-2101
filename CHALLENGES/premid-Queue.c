#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

typedef struct {
  char FN[24], LN[16], MI;
} nametype;

typedef struct {
  char ID[10];
  nametype name;
  char course[8];
  int yrLevel;
} studRec;

/* Virtual Heap Definition */
typedef struct {
  studRec stud;
  int link;
} nodetype;

typedef struct {
  nodetype VSpace[MAX];
  int firstAvail; // index of 1st available node
} VHeap;
/* Queue Definition */
typedef struct {
  int start; // front or head
  int end;   // rear or tail
  int cnt;
  VHeap *vptr;
} queue;

int main(){
  NameLi
}