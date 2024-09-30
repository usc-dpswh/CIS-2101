#include <stdio.h>
#include <string.h>

typedef unsigned char SET;
int getHash(SET studentInfo);

int main(){
  //* Course codes
  // 00 - CS
  // 01 - IT
  // 10 - IS
  // 11 - MATH

  //* Year level
  // 00 - 1
  // 01 - 2
  // 10 - 3
  // 11 - 4

  //* Remaining 4 digits is student ID
  // 0000 _ _ _ _ 
  // 1111 = 240

  SET stud1 = 0b11011010; // 1101 10 10
  char course[12];
  int yearLvl;

  SET bitCourse = stud1 & 0b11;
  SET bitYearLvl = stud1&12;
  SET bitStudID = stud1&240;

  if (bitCourse == 0b00){
    strcpy(course, "CS");
  } else if (bitCourse == 0b01){
    strcpy(course, "IT");
  } else if (bitCourse == 0b10){
    strcpy(course, "IS");
  } else {
    strcpy(course, "MATH");
  }
  
  // switch (bitCourse) {
  //   case 0:
  //     strcpy(course, "CS");
  //     break;
  //   case 1:
  //     strcpy(course, "IT");
  //     break;
  //   case 2:
  //     strcpy(course, "IS");
  //     break;
  //   default:
  //     strcpy(course, "MATH");
  // }

  // switch (bitYearLvl) {
  //   case 0:
  //     yearLvl = 1;
  //     break;
  //   case 4:
  //     yearLvl = 2;
  //     break;
  //   case 8:
  //     yearLvl = 3;
  //     break;
  //   default:
  //     yearLvl = 4;
  // }

  if (bitYearLvl == 0){
    yearLvl = 1;
  } else if (bitYearLvl == 1){
    yearLvl = 2;
  } else if (bitYearLvl == 2){
    yearLvl = 3;
  } else {
    yearLvl = 4;
  }
  printf("Stud1:");
  printf("\nCourse: %s", course);
  printf("\nYearLvl: %d", yearLvl);
  printf("\nID: %d", bitStudID); //128+64+16 = 208
  printf("\nHashVal = %d", getHash(stud1));
  
}

// Gets the student's ID and hashes it according to their yearLvl divided by 3.
int getHash(SET studentInfo){
  SET studID      = studentInfo & 240;
  SET studYearLvl = studentInfo & 12;
  int sum;
  int x;
  return (studID / 3) % studYearLvl;
}