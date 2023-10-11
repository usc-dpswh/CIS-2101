#include <stdio.h>
#include <string.h>

int main(){
  FILE *fp = NULL;
  fp = fopen("text.bin", "rb");
  int num;

  if (fp != NULL){
    while(fread(&num, 4, 1, fp) != 0){
      printf("%d", num);
    }
    // fread(&num, 4, 1, fp);
    // printf("%d", num);
  }

  fclose(fp);
}
