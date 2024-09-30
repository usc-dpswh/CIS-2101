#include <stdbool.h>
#include <stdio.h>
#define SIZE 15

typedef int Tree[SIZE];
typedef struct set {
  int setElem[SIZE];
  int count;
} SET;

typedef struct {
  Tree elems;
  int lastNdx;
} Heap, *HeapPTR;

// Auxiliary Functions
void initHeap(Heap *main);
void populateHeap(SET source, Heap *dest);
void display(Heap main);

// Main Functions
void insert(Heap *main, int newData);
int deleteMin(Heap *main);
int deleteMax(Heap *main);
void minHeapify(Heap *main);
void maxHeapify(Heap *main);

int main() {
  Heap Yuvallos;
  initHeap(&Yuvallos);

  SET A = {3, 4, 9, 12, 15, 9, 10};
  A.count = 7;

  populateHeap(A, &Yuvallos);

  insert(&Yuvallos, 1);
  insert(&Yuvallos, 5);
  insert(&Yuvallos, 2);
  printf("\n");
  display(Yuvallos);

  maxHeapify(&Yuvallos);
  printf("\nAfter maxHeapify()\n");
  display(Yuvallos);
  
  deleteMax(&Yuvallos);
  printf("\n After deleteMax()\n");
  display(Yuvallos);

  minHeapify(&Yuvallos);
  printf("\n After minHeapify()\n");
  display(Yuvallos);
  deleteMin(&Yuvallos);
  printf("\n After deleteMin()\n");
  display(Yuvallos);

  return 0;
}

// Auxiliary Functions
void display(Heap main) {
  int x;
  for (x = 0; x <= main.lastNdx; x++) {
    printf("%d -> ", main.elems[x]);
  }
  printf("NULL\n");
}
void initHeap(Heap *main) {
  int x;
  for (x = 0; x < SIZE; x++) {
    main->elems[x] = 0;
  }
  main->lastNdx = -1;
  printf("\nInitialized the heap.");
}
void populateHeap(SET source, Heap *dest) {
  int x;
  for (x = 0; x < source.count; x++) {
    dest->elems[x] = source.setElem[x];
  }
  dest->lastNdx = source.count - 1;
  printf("\nPopulated the heap.");
}

// Main Functions
void insert(Heap *main, int newData) {
  int currNdx;
  if (main->lastNdx < SIZE) {
    main->lastNdx++;
    currNdx = main->lastNdx;
    main->elems[currNdx] = newData;

    while (currNdx > 0 && main->elems[(currNdx - 1) / 2] > newData) {
      // Shift down parent element to currNdx element
      main->elems[currNdx] = main->elems[(currNdx - 1) / 2];
      // Change currNdx to parent index;
      currNdx = (currNdx - 1) / 2;
    }
    main->elems[currNdx] = newData;
    printf("\nSuccessfully inserted %d", newData);
  } else {
    printf("\nTree is full.");
  }
}
int deleteMin(Heap *main) {
  int min, temp;
  int sChild = 1, ndx = 0;
  // store root value in min
  min = main->elems[0];
  // assign elems[0] to lastNdx
  main->elems[0] = main->elems[main->lastNdx];
  main->lastNdx--;

  if (main->lastNdx != -1) {
    // while !leaf
    while (sChild <= main->lastNdx) {
      // to check if there is still a leaf/chilren
      // condition to check if RIGHT CHILD exists && RIGHT CHILD < LEFT CHILD
      if (sChild + 1 <= main->lastNdx &&
          main->elems[sChild + 1] <= main->elems[sChild]) {
        // if RC is smaller, we want our smaller child to be at the index of
        // RC in preparation for SWAP
        sChild = sChild + 1;
      }
      // swap
      if (main->elems[ndx] > main->elems[sChild]) {
        temp = main->elems[sChild];
        main->elems[sChild] = main->elems[ndx];
        main->elems[ndx] = temp;
        ndx = sChild;
        sChild = (sChild * 2) + 1;
      } else {
        sChild = main->lastNdx + 1;
      }
    }
  }
  printf("\nSuccessfully deleted min.");
  return min;
}
int deleteMax(Heap *main) {
  int max, temp;
  int sChild = 1, ndx = 0;
  // store root value in max
  max = main->elems[0];
  // assign elems[0] to lastNdx
  main->elems[0] = main->elems[main->lastNdx];
  main->lastNdx--;

  if (main->lastNdx != -1) {
    // while !leaf
    while (sChild <= main->lastNdx) {
      // condition to check if RIGHT CHILD exists && RIGHT CHILD < LEFT CHILD
      if (sChild + 1 <= main->lastNdx &&
          main->elems[sChild + 1] >= main->elems[sChild]) {
        // if RC is bigger, we want our  child to be at the index of
        // RC in preparation for SWAP
        sChild = sChild + 1;
      }
      // swap
      if (main->elems[ndx] < main->elems[sChild]) {
        temp = main->elems[sChild];
        main->elems[sChild] = main->elems[ndx];
        main->elems[ndx] = temp;
        ndx = sChild;
        sChild = (sChild * 2) + 1;
      } else {
        sChild = main->lastNdx + 1;
      }
    }
  }
  printf("\nSuccessfully deleted max.");
  return max;
}
void minHeapify(Heap *main) {
  int temp, trav, parNdx, childNdx;
  parNdx = (main->lastNdx - 1) / 2;
  trav = parNdx;
  childNdx = (parNdx * 2) + 1;
  while (parNdx >= 0) {
    while (childNdx <= main->lastNdx) {
      if (childNdx + 1 <= main->lastNdx && main->elems[childNdx + 1] < main->elems[childNdx]) {
        childNdx += 1;
      }
      if (main->elems[trav] > main->elems[childNdx]) {
        temp = main->elems[trav];
        main->elems[trav] = main->elems[childNdx];
        main->elems[childNdx] = temp;
        trav = childNdx;
        childNdx = (childNdx * 2) + 1;
      } else {
        childNdx = main->lastNdx + 1;
      }
    }
    parNdx--;
    trav = parNdx;
    childNdx = (parNdx * 2) + 1;
  }
}
void maxHeapify(Heap *main) {
  int temp, trav, parNdx, childNdx;
  parNdx = (main->lastNdx - 1) / 2;
  trav = parNdx;
  childNdx = (parNdx * 2) + 1;
  while (parNdx >= 0) {
    while (childNdx <= main->lastNdx) {
      if (childNdx + 1 <= main->lastNdx &&
          main->elems[childNdx + 1] > main->elems[childNdx]) {
        childNdx += 1;
      }
      if (main->elems[trav] < main->elems[childNdx]) {
        temp = main->elems[trav];
        main->elems[trav] = main->elems[childNdx];
        main->elems[childNdx] = temp;
        trav = childNdx;
        childNdx = (childNdx * 2) + 1;
      } else {
        childNdx = main->lastNdx + 1;
      }
    }
    parNdx--;
    trav = parNdx;
    childNdx = (parNdx * 2) + 1;
  }
}
