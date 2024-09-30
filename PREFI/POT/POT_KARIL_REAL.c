#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20

typedef struct name{
    char fName[50];
    char mi;
    char lName[50];
}studName;

typedef struct student{
    char idNum[10];
    studName name;
    int grade;
}student;

typedef struct node{
    student *data;
    int lastNdx;
}POT;

void insertPOT(POT *P, student info){
    int i = 0, pNdx = 0, cNdx = 0;
    if(P->lastNdx < MAX){
        for(i = 0; i <= P->lastNdx && strcmp(P->data[i].idNum, info.idNum) != 0; i++){}

        if(i > P->lastNdx){ //if i > P->lastndx then there is a similar student
            P->lastNdx += 1;
            cNdx = P->lastNdx;
            pNdx = (cNdx - 1)/2;

        while(cNdx > 0 && P->data[pNdx].grade < info.grade){ //compare if parent is greater/lesser than child then swap
            P->data[cNdx] = P->data[pNdx];
            cNdx = pNdx;
            pNdx = (cNdx - 1)/2;
        }
        P->data[cNdx] = info; 
    }else{
        printf("Cannot insert, %s already exists.\n", info.name.fName);
    }
    }
}

void generateStudent(POT *P){
    
student students[] = {
    {"STUD1008", {"Olivia", 'B', "Hernandez"}, 123},
    {"STUD1001", {"John", 'R', "Doe"}, 128},
    {"STUD1020", {"Lily", 'N', "Tanaka"}, 255},
    {"STUD1004", {"Joey", 'K', "Lee"}, 207},
    {"STUD1002", {"Jane", 'L', "Smith"}, 217},
    {"STUD1005", {"Michael", 'T', "Garcia"}, 36},
    {"STUD1008", {"Olivia", 'B', "Hernandez"}, 123},
    {"STUD1003", {"Mark", 'S', "Johnson"}, 130},
    {"STUD1010", {"Mia", 'D', "Nguyen"}, 89},
    {"STUD1011", {"Ethan", 'E', "Perez"}, 130},
    {"STUD1021", {"Elijah", 'O', "Yamamoto"}, 36},
    {"STUD1017", {"Daniel", 'K', "Cruz"}, 128},
    {"STUD1019", {"Noah", 'M', "Reyes"}, 130},
    {"STUD1012", {"Chung", 'F', "Tan"}, 231},
    {"STUD1013", {"Alexander", 'G', "Reyes"}, 44},
    {"STUD1014", {"Sofia", 'H', "Wong"}, 149},
    {"STUD1015", {"Benjamin", 'I', "Liu"}, 202},
    {"STUD1016", {"Chloe", 'J', "Gonzales"}, 59},
    {"STUD1018", {"Garret", 'L', "Santos"}, 73},
    {"STUD1029", {"Gabriel", 'W', "Nguyen"}, 108},
    };

    int i;

    for(i = 0; i < MAX; i++){
        insertPOT(P, students[i]);
    }

}

student deleteMin(POT *P){
    student min ={"XXXXX", {"XXXXX", 'X', "XXXXXX"}, 90};
    
    student temp;
    int sChild = 1, ndx = 0; //ndx is parent

    if(P->lastNdx != -1){  //check if lastndx is -1
        min = P->data[0];

        P->data[0] = P->data[P->lastNdx];
        P->lastNdx--;

        while(sChild <= P->lastNdx){ //condition to check if it is a leaf
                if(sChild + 1 <= P->lastNdx && P->data[sChild + 1].grade <= P->data[sChild].grade){ //checks if there is a right child and if right child is greater than left child
                    sChild = sChild + 1;
                }
                if(P->data[sChild].grade < P->data[ndx].grade){
                    temp = P->data[sChild];
                    P->data[sChild] = P->data[ndx];
                    P->data[ndx] = temp;
                    ndx = sChild;
                    sChild = (sChild * 2) + 1; //goes to the left child
                }else{
                sChild = P->lastNdx + 1;
                }
        }
    }

    return min;
}

void minHeapify(POT *P){
    int trav, child, parent;
    student temp;

    parent = (P->lastNdx - 1)/2;
    child = (parent * 2) + 1;
    trav = parent;

    while(parent >= 0){
        while(child <= P->lastNdx){
            if(child + 1 <= P->lastNdx && P->data[child + 1].grade <= P->data[child].grade){
                child += 1;
            }

            if(P->data[child].grade < P->data[trav].grade){
                temp = P->data[child];
                P->data[child] = P->data[trav];
                P->data[trav] = temp;
                trav = child;
                child = (child * 2) + 1;
            }else{
                child = P->lastNdx + 1;
            }

        }
        parent--;
        trav = parent;
        child = (parent * 2) + 1;
    }

}

void display(POT *P){
    int i;
    printf("\n");
    for(i = 0; i <= P->lastNdx; i++){
        printf("Index: %d - Parent:%d - %s %s %s %d\n", i,(i - 1)/2,P->data[i].idNum,P->data[i].name.fName, P->data[i].name.lName, P->data[i].grade);
    }

    printf("\n%d - Last Index\n", P->lastNdx);
}


void heapSort(POT *P){
    minHeapify(P);

    student temp;
    int origNdx =  P->lastNdx;
    while(P->lastNdx != -1){
        temp = deleteMin(P);
        P->data[P->lastNdx + 1] = temp;
    }

    P->lastNdx = origNdx;
}


int main(){

    POT P;

    P.data = (student*)malloc(sizeof(struct student) * MAX);
    P.lastNdx = -1;
    generateStudent(&P);
    display(&P);

    printf("\n----After HeapSort----");
    heapSort(&P);
    display(&P);

    // student deleted;
    
    // deleted = deleteMin(&P);

    // display(&P);
    // printf("\nStudent: %s - %s has been deleted.\n", deleted.idNum, deleted.name.lName);
    
}

