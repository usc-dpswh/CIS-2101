#include <stdio.h>
#include <string.h>
#define MAX 50

void addString(FILE *main, char *string){
  main = fopen("students.txt", "a+");

  if (main != NULL){
    fputs(string, main);
    fclose(main);
  }
}
void getCharacter(FILE *main){
  main = fopen("students.txt", "r");
  char ch = fgetc(main);
  printf("CHAR => %c", ch);

  fclose(main);

}
void displayByLine(FILE *main){
  main = fopen("students.txt", "r");

  if (main != NULL){
    char string[MAX];

    rewind(main);
    while (!feof(main)){
      fgets(string, 5, main);
      printf("%s", string);
    }
  }
  fclose(main);
}

int main(){
  FILE *fp;
  char string[MAX];

  addString(fp, "HelloWorld");
  // displayByLine(fp);
  // getCharacter(fp);

  fp = fopen("students.txt", "r+");

  if (fp != NULL){
    fputs("Xander Labide", fp);
    rewind(fp);

    displayByLine(fp);

    fclose(fp);
  }
}