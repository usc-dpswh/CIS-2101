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

    for(i = 0; i <= P->lastNdx && strcmp(P->data[i].idNum, info.idNum) != 0; i++){}

    if(i > P->lastNdx){
        P->lastNdx += 1;
        cNdx = P->lastNdx;
        pNdx = (cNdx - 1)/2;

        if(pNdx >= 0){
            
            while(cNdx != 0 && P->data[pNdx].grade > info.grade){
            P->data[cNdx] = P->data[pNdx];
            cNdx = pNdx;
            pNdx = (cNdx - 1)/2;
            }

        }

        P->data[cNdx] = info;
    }else{
        printf("Cannot insert, %s already exists.\n", info.name.fName);
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
    student min;

    int sChild = 0, ndx = 0;

    if(P->lastNdx != -1){
        min = P->data[0];

        P->data[0] = P->data[P->lastNdx];
        P->lastNdx-=1;

        while(sChild <= P->lastNdx){
            if(P->data[ndx + 1].grade < P->data[ndx + 2].grade){
                sChild += 1;
            }else{
                sChild += 2;
            }

            P->data[ndx] = P->data[sChild];
            P->data[sChild] = P->data[ndx];
            ndx = sChild;
        }
    }

    return min;
}

void display(POT *P){
    int i;
    printf("\n");
    for(i = 0; i <= P->lastNdx; i++){
        printf("%s %s %s %d\n", P->data[i].idNum,P->data[i].name.fName, P->data[i].name.lName, P->data[i].grade);
    }

    printf("\n%d - Last Index\n", P->lastNdx);
}


int main(){

    POT P;

    P.data = (student*)malloc(sizeof(struct student) * MAX);
    P.lastNdx = -1;
    generateStudent(&P);
    display(&P);

    student deleted = deleteMin(&P);

    display(&P);
    printf("\nStudent: %s - %s has been deleted.\n", deleted.idNum, deleted.name.fName);
}

