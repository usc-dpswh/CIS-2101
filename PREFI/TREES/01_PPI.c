
#include <stdio.h>
#include <stdlib.h>
#define MAX 10
#define ROOT -1
#define INV -2

typedef int Tree[MAX];
typedef int node;
typedef int label;

void initialize(Tree T, int values[]);
void display(Tree T);
node parent(node n, Tree T);
node root(Tree T);
void makeNull(Tree T);

//NOTE: For this representation, the value that is to be returned from this function is basically the parent. Meaning, the label is == parent.
label Label(node n, Tree T);

//NOTE: THESE OPERATIONS CANNOT BE EXECUTED DUE TO THE NATURE OF THIS IMPLEMENTATION
// node Leftmost_Child(node N, Tree T);
// node Right_Sibling(node N, Tree T);

int main(){
  Tree Mango;
  int values[] = {0,-1,1,1,1,3,3,5,5,5,4};

  initialize(Mango, values);
  display(Mango);

  printf("Parent = %d\n", parent(3, Mango));
  printf("Parent = %d\n", parent(7, Mango));
  printf("Parent = %d\n", parent(99, Mango));

  printf("Root = %d\n", root(Mango));

  printf("Label = %d\n", Label(5, Mango));
  makeNull(Mango);
  display(Mango);

}

void initialize(Tree T, int values[]){
  int x;

  for (x = 0 ; x < MAX ; x++){
    T[x] = values[x];
  }
  printf("Initialized tree.\n");
}
void display(Tree T){
  int x;

  for (x = 0 ; x < MAX ; x++){
    printf("[%d] => %d\n", x, T[x]);
  }
  printf("\n");
}
node parent(node n, Tree T){
  return (n != ROOT && n != INV) ? T[n] : INV;
}
node root(Tree T){
  int x;
  for (x = 0 ; x < MAX && T[x] != ROOT ; x++){}
  return (x < MAX) ? x : INV;
}
void makeNull(Tree T){
  int x;
  for (x = 0 ; x < MAX ; x++){
    T[x] = INV;
  }
  printf("Tree is now null!\n");
}
label Label(node n, Tree T){
  return T[n];
}