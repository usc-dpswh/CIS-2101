#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#define MAX 20

int main(){
  FILE *fp;

  // w  - write, overwrites existing file
  // a  - append to existing file,  no overwrite
  // r  - simply only READ file without changes
  // r+   = reading and writing (if file does not exist, it doesn't overwrite) can write anywhere
  // w+   = reading / writing
  // a+   = reading / appending (writing at end of file while WRITING can be ANYWHERE in the file)

  
  fp = fopen("students.txt","a");

  char string[MAX] = "Dianne";
  int num = 50;

  if (fp != NULL){
    // fputc('D', fp);
    // fputs("Dianne", fp);
    // fprintf(fp, "%d-%s", num, string);

    // char ch = fgetc(fp);
    // printf("%c\n", ch);
    char ch;

    // while not at the end of file
    // while(!feof(fp)){
    //   ch = fgetc(fp);
    //   printf("%c", ch);
    // }

    char str[MAX];
    // fgets(str, 5, fp);
    // printf("\n%s", str);

    // once fgets finds a new line character, it will stop. so how will we be able to read a new line ? loop.

    // read lines
    int x = 0;
    while(x < 5){
      // fgets(str, 5, fp);
      // printf("%s", str);
      fprintf(fp, "\n%s", "OTIN");
      x++;
    }

    printf("\nExecuted file operations.\n");
    fclose(fp);
  }
}

// fputc    = write a CHARACTER
// fputs    = write a STRING
// fprintf  = write 
// fgetc    = simply gets the first character in your txt file (if you want to read more than one character AKA a string, you need to loop)
// feof     = returns TRUE or FALSE if its at the end of file