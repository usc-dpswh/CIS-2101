#include <stdio.h>
#include <string.h>

int main(){
  FILE *fp = NULL;
  fp = fopen("text.bin", "wb");

  int num[] = {1,2,3,4,5};

  if (fp != NULL){
    fwrite(&num, 4, 5, fp);
  }

  fclose(fp);
}
