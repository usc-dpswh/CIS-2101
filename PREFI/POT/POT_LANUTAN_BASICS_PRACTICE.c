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
	if (main->lastNdx < SIZE){
		main->lastNdx++;
		currNdx = main->lastNdx;
		main->elems[currNdx] = newData;
		
		while (currNdx > 0 && main->elems[(currNdx - 1)/2] > newData){
			main->elems[currNdx] = main->elems[(currNdx - 1)/2];
			currNdx = (currNdx - 1)/2;
		}
		main->elems[currNdx] = newData;
	}
}
int deleteMin(Heap *main) {
	int min, temp, parent, child;
	if (main->lastNdx != -1){
		min = main->elems[0];
		main->elems[0] = main->elems[main->lastNdx];
		main->lastNdx--;
		parent = 0;
		child = 1;
		
		while (child <= main->lastNdx){
			if (child + 1 && main->elems[child + 1] < main->elems[child]){
				child += 1;
			}
			if (main->elems[parent] > main->elems[child]){
				temp = main->elems[parent];
				main->elems[parent] = main->elems[child];
				main->elems[child] = temp;
				parent = child;
				child = (child * 2) + 1;
			} else {
				child = main->lastNdx + 1;
			}
		}
	}
}
int deleteMax(Heap *main) {
	int max, temp, parent, child;
	if (main->lastNdx != -1){
		max = main->elems[0];
		main->elems[0] = main->elems[main->lastNdx];
		main->lastNdx--;
		parent = 0;
		child = 1;
		
		while (child <= main->lastNdx){
			if (child + 1 <= main->lastNdx && main->elems[child+1] > main->elems[child]){
				child += 1;
			}
			if (main->elems[parent] < main->elems[child]){
				temp = main->elems[parent];
				main->elems[parent] = main->elems[child];
				main->elems[child] = temp;
				parent = child;
				child = (child * 2) + 1;
			} else {
				child = main->lastNdx + 1;
			}
		}
	}
}

void minHeapify(Heap *main) {
	int temp, trav, parent, child;
	parent = (main->lastNdx - 1)/2;
	child = (parent * 2) + 1;
	trav = parent;
	if (main->lastNdx != -1){
		
		while (parent >= 0){
			while (child <= main->lastNdx){
				if (child + 1 <= main->lastNdx && main->elems[child+1] <= main->elems[child]){
					child += 1;
				}
				if (main->elems[trav] > main->elems[child]){
					temp = main->elems[trav];
					main->elems[trav] = main->elems[child];
					main->elems[child] = temp;
					trav = child;
					child = (child * 2) + 1;
				} else {
					child = main->lastNdx + 1;
				}
			}
			parent--;
			trav = parent;
			child = (parent * 2) + 1;
		}
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
