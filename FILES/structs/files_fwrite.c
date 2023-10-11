#include <stdio.h>
#include <string.h>
#define MAX 50

typedef struct {
  char name[25];
  int age;
} Student;

void displayStruct(Student *data, int size) {
  int x;

  for (x = 0; x < size; x++) {
    printf("NAME: %5s AGE: %d\n", data[x].name, data[x].age);
  }
}

void writeToFile(FILE *main, Student *data, int size) {
  main = fopen("StudRec.bin", "wb");

  if (main != NULL) {
    fwrite(data, sizeof(Student), size, main);
    fclose(main); // Close the file after writing
  } else {
    printf("Failed to open the file for writing.\n");
  }
}

void fetchDataToStruct(FILE *main, Student *data, int size) {
  main = fopen("StudRec.bin", "rb");

  if (main != NULL) {
    fread(data, sizeof(Student), size, main);
    fclose(main);
  } else {
    printf("FAILED\n");
  }
}

int main() {
  Student list[3] = {
    {"Achille", 20},
    {"Dianne", 20},
    {"Marlon", 22}
  };
  int size = sizeof(list) / sizeof(list[0]);
  Student fetchedData[3];

  FILE *fp = NULL;

  // writeToFile(fp, list, size);
  fetchDataToStruct(fp, fetchedData, size);
  displayStruct(fetchedData, size);

  return 0;
}
