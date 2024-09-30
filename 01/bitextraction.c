#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned char SET;

// 00 - IT
// 01 - CS
// 10 - IS
// 11 - MATH
// 100 - MALE
// 000 - FEMALE

// 11000000

char* getProgram(SET main);
char* getSex(SET main);

int main(){
  SET student = 0b00000110;
  char* programString = getProgram(student);
  char* sexString = getSex(student);
  printf("\n%-10s%-10s%-10s", programString, getProgram(programString), getSex(sexString));
  printf("\n%s", sexString);
}

char* getProgram(SET main){
  char* programString = (char*)malloc(sizeof(char)*7);
  strcpy(programString, "N/A");
  SET program = main & 0b11; // 00000010
  // 00000110
  // 00000011
  // 00000010
  if (programString != NULL){
    if (program == 0b00){
      strcpy(programString, "BSIT");
    } else if (program == 0b01){
      strcpy(programString, "BSCS");
    } else if (program == 0b10){
      strcpy(programString, "BSIS");
    } else {
      strcpy(programString, "BSMATH");
    }
  }
  return programString;
}
char* getSex(SET main){
  char* sexString = (char*)malloc(sizeof(char)*7);
  strcpy(sexString, "N/A");
  SET mask = main & 0b100;
  if (sexString != NULL){
    if (mask == 0b100){
      strcpy(sexString, "FEMALE");
    } else {
      strcpy(sexString, "MALE");
    }
  }
  return sexString;
}
