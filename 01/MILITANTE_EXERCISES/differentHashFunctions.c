#include <ctype.h>
#include <stdio.h>
#include <string.h>

int hash10(char string1[]);
int hash100(char elem[]);
int hashSumOfAllThenDivide(char elem[]);
int hashASCII(char string1[]);
int hashEvenOnly(char string1[]);
int addOnlyNumerics(char string1[]);

int main(){
  char string1[12] = "3913";
  int num1 = 3599;
  int num2 = 9551;
  char string2[12] = "abCDE";
  char string3[12] = "123458";
  char string4[12] = "ABCD1236";
  // C = 67-65=2
  // D = 68-65=3
  // E = 69-65=4
  // hashval = 9

  // 48 - 0
  // 49 - 1
  // 50 - 2
  // 51 - 3
  // 52 - 4
  // 53 - 5
  // 54 - 6
  // 55 - 7
  // 56 - 8
  // 57 - 9

  // sum = 0 + 51 - 48 (3)
  // sum = 3 + 57 - 48 (9)
  // sum = 12 + 49 - 48 (1)
  // sum = 13 + 51 - 48 (3)
  // sum = 16 % 10

  int hashVal;

  printf("\n%d", hash10(string1));
  printf("\n%d", hash100(string1));
  printf("\n%d", hashSumOfAllThenDivide(string1));
  printf("\n%d", hashASCII(string2));
  printf("\n%d", hashEvenOnly(string3));
  printf("\n%d", addOnlyNumerics(string4));
  // printf("\n%s", strupr(string2));
}

int hash10(char string1[]){
  int x;
  int sum;
  for (x = 0, sum = 0 ; string1[x] != '\0' ; x++){
    sum = sum + string1[x] - '0';
  }
  return sum % 10;
}
int hash100(char elem[]){
  int x;
  int sum;
  int length = strlen(elem);
  for (x = length ; x < length ; x++){
    sum = sum + elem[x] - '0';
  }

}
int hashSumOfAllThenDivide(char elem[]){
  int x;
  int sum;
  for (x = 0, sum = 0 ; elem[x] != '\0' ; x++){
    sum += elem[x] - '0';
  }
  return (sum / 5) % 10;
}
int hashASCII(char string1[]){
  int x;
  int sum;
  for (x = 0, sum = 0 ; string1[x] != '\0' ; x++){
    if (isupper(string1[x])){
      sum += string1[x] - 'A';
    }
  }
  return sum % 10;
}
int hashEvenOnly(char string1[]){
  int x;
  int sum;
  for (x = 0, sum = 0 ; string1[x] != '\0' ; x++){
    if (string1[x] % 2 == 0){
      sum = sum + string1[x] - '0';
    }
  }
  return sum % 10;
}
int addOnlyNumerics(char string1[]){
  int x;
  int sum;
  for (x = 0, sum = 0 ; string1[x] != '\0' ; x++){
    if (isdigit(string1[x])){
      sum += string1[x] - '0';
    }
  }
  return sum % 10;
}
