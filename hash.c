#include <stdio.h>

int hash(int num){
  return num /= 10;
}

int hashString(char* string){
  int x;
  int sum = 0;
  for (x = 0 ; string[x] != "\0" ; x++){
    sum += string[x] - '0';
  }
}

int main(){
  int number = hash(49);
  char id[9] = "22103514";
  printf("%d", number);
  printf("%d", 10 % 15);
}