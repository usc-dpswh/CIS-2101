#include <stdio.h>

#define MAX 5

typedef int List;

typedef struct {
    struct {
        char data;
        int link;
    } Nodes[MAX];
    int avail;
} VH;

void init(VH *virtualHeap, List *head) {
    int i;

    for (i = -1; i < MAX; i++) {
        virtualHeap->Nodes[i + 1].link = i;
    }

    virtualHeap->avail = MAX - 1;
    *head = -1;
}

int allocSpace(VH *virtualHeap) {
    int retVal = virtualHeap->avail;

    if (retVal != -1) {
        virtualHeap->avail = virtualHeap->Nodes[retVal].link;
    }

    return retVal;
}

void deallocSpace(VH *virtualHeap, int ndx) {
    if (ndx >= 0 && ndx < MAX) {
        virtualHeap->Nodes[ndx].link = virtualHeap->avail;
        virtualHeap->avail = ndx;
    }
}

void insertFirst(VH *virtualHeap, List *head, char data) {
    if (virtualHeap->avail != -1) {
        int newNode = allocSpace(virtualHeap);

        if (newNode != -1) {
            virtualHeap->Nodes[newNode].data = data;
            virtualHeap->Nodes[newNode].link = *head;
            *head = newNode;
        }
    }
}

void printList(VH virtualHeap, List head) {
    while (head != -1) {
        printf("%c -> ", virtualHeap.Nodes[head].data);
        head = virtualHeap.Nodes[head].link;
    }
    printf("-1\n");
}

int main(void) {
    VH virtualHeap;
    List head;

    init(&virtualHeap, &head);

    insertFirst(&virtualHeap, &head, 'A');
    insertFirst(&virtualHeap, &head, 'B');
    insertFirst(&virtualHeap, &head, 'C');
    insertFirst(&virtualHeap, &head, 'D');

    printList(virtualHeap, head);

    return 0;
}