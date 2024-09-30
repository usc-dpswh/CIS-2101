#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUMPROGRAMS 4
#define YEARLEVELS 4
#define MAXSTUDS 100

typedef struct {
  char fName[64];
  char mi;
  char lName[32];
} studName;

typedef unsigned char personalInfo;
/*Given 8 bits: 0000 0000

 Bits
 8    = Status:            0 - Inactive, 1 - Active
 7    = Nationality:       0 - Filipino, 1 - Foreigner
 6    = Enrollment Status: 0 - Regular, 1 - Irregular
 5    = Gender:            0 - Male, 1 - Female
 3-4  = Year Level:        00 - 1st, 01 - 2nd, 10 - 3rd, 11 - 4th
 1-2  = Program:           00 - CS, 01 - IT, 10 - IS, 11 - MATH

 For example:
 1001 1001 would represent an Active Regular 3rd Year Filipino Female IT Student
*/

typedef struct {
  char idNum[9];
  studName name;
  personalInfo info;
} student;

typedef struct {
  student studs[MAXSTUDS];
  int numStuds;
} arrListStud;

typedef struct studNode {
  student stud;
  struct studNode *next;
} studNode, *studLL;

typedef studLL studDict[YEARLEVELS];

typedef struct {
  studDict programStuds;
  int studCtr; /* refers to the total number of students in the PROGRAM. */
} dcismNode;

typedef dcismNode dcismDict[NUMPROGRAMS];

typedef struct {
  char studID[9];
  studName sName;
} studRec;

typedef struct {
  studRec studs[MAXSTUDS];
  int count;
} sNode, *studSet; /* array representation of a Set of studRecs */

char *getProgram(personalInfo);
arrListStud populateStudentList(void);
void displayArrListStud(arrListStud);
int programHash(personalInfo);
int yearLevelHash(personalInfo);
int insertStudLL(studLL *, student);
void displayStudLL(studLL);
void initDCISMDict(dcismDict);
void convertToDCISMDict(dcismDict, arrListStud);
void displayDCISMDict(dcismDict);
studSet *initStudSet(void);
void insertStudSet(studSet, studRec);
studSet *removeInactiveStudents(dcismDict);
void displayStudSets(studSet *);

/*
 Write the code for the function getProgram().

 The function will return the string equivalent of the program of the provided
 personalInfo. For example: personalInfo = 1001 1001 will return the string BSIT
 because the last 2 bits are 01. Refer to the definition of personalInfo to know
 which bit pattern represent each program.
 */
char *getProgram(personalInfo I) {
  char *placeholder = (char*)malloc(5 * sizeof(char));
  personalInfo program = I&0b11;
  if (program == 0b00){ // Issue here
    strcpy(placeholder, "CS");
  } else if (program == 0b01){ // Issue here
    strcpy(placeholder, "IT");
  } else if (program == 0b10){ // Issue here
    strcpy(placeholder, "IS");
  } else {
    strcpy(placeholder, "MATH");
  }
  return placeholder;
}


/*
 Code for this function has been partially provided.
 Write the code for the function populatesetList().
 The function will read a file containing student records and return the student
 records to the calling function in the form of an arrListStud.
 */
arrListStud populateStudentList(void) {
  FILE *fp;
  student *studs;
  int dataCount;
  arrListStud SL = {{0}, 0};

  if ((fp = fopen("students.bin", "rb")) == NULL) {
    puts("Unsuccessful in opening students.txt");
  } else {
    fseek(fp, 0, 2);
    dataCount = (int)ftell(fp) / sizeof(student);
    studs = (student *)malloc(sizeof(student) * dataCount);
    if (studs != NULL) {
      fseek(fp, 0, 0);
      fread(studs, sizeof(student), dataCount, fp);
    }
    /* In this section, insert all the studs into an setList to be returned. */
    int x;
    for (x = 0; x < dataCount; x++) {
      SL.studs[x] = studs[x];
      // printf("\nInserted %s successfully.", studs[x].idNum);
      SL.numStuds++;
    }
  }
  return SL;
}

/*
 Write the code for the function displayArrListStud().
 This function will display the ID number, First Name, and Last name of the
 student records inside the arrListStud.
 */
void displayArrListStud(arrListStud A) {
  printf("Student Data from the file\n");
  printf("%-10s", "Id Number");
  printf("%-10s", "fName");
  printf("%-10s", "lName");
  printf("%-10s", "Course");
  printf("%-10s\n", "YearLvl");

  int x, y;

  for (x = 1 ; x <= 4 ; x++) {
    // printf("\nYEAR LEVEL: %d", x);
    for (y = 0 ; y < A.numStuds ; y++){
      if (yearLevelHash(A.studs[y].info) == x){
        printf("\n%-10s%-10s%-10s%-10s%-10d",
          A.studs[y].idNum,
          A.studs[y].name.fName,
          A.studs[y].name.lName,
          getProgram(A.studs[y].info),
          yearLevelHash(A.studs[y].info)
        );
      }
    }
  }
}

/*
 Write the code for the function programHash().
 Given a personalInfo variable, the function will return the integer equivalent
 of the bits that represent a student's program.
 */
int programHash(personalInfo I) {
  return I&0b11;
}

/*
 Write the code for the function yearLevelHash().
 Given a personalInfo variable, the function will return the integer equivalent
 of the bits that represent a student's year level.
 */
int yearLevelHash(personalInfo I) {
  int year;
  // Right-shift the bits twice to align the two relevant bits to the rightmost position
  personalInfo yearBits = (I & 0b1100) >> 2;
  if (yearBits == 0b00){
    year = 0;
  } else if (yearBits == 0b01){
    year = 1;
  } else if (yearBits == 0b11){
    year = 2;
  } else {
    year = 3;
  }
  return year;
}

/*
 Write the code for the function insertStudentLL().
 Given a pointer to a studLL and a student to insert, the function will insert
 into the sorted studSet based on the student's ID number. All elements in the
 studLL should be unique. The function will return 1 if the insert was
 successful and 0 if not.
 */
int insertStudLL(studLL *SL, student S) {}

/*
 Code for this function has been partially provided.
 Write the code for the function displayStudLL().
 The function will display the contents of a given studLL.
 */
void displayStudLL(studLL SL) {
  studLL trav;
  if(SL != NULL){
    printf("\nYear %d\n\n", yearLevelHash(SL->stud.info)+1);
    printf("%-10s", "Id Number");
    printf("%-10s", "fName");
    printf("%-10s", "lName");
    printf("%-10s", "Program");
    printf("%-10s", "Year");
    printf("%-10s", "Gender");
    printf("%-15s", "Enrollment");
    printf("%-15s", "Nationality");
    printf("%-10s\n", "Status");
    for(trav = SL ; trav != NULL ; trav = trav->next){
      printf("%-10s%-10s%-10s%-10s%-10d%-10s%-15s%-15s%-10s\n",
        trav->stud.idNum,
        trav->stud.name.fName,
        trav->stud.name.lName,
        getProgram(SL->stud.info),
        yearLevelHash(SL->stud.info)+1,
        (trav->stud.info & 0b10000) ? "FEMALE" : "MALE", // Check if the 5th bit is set for gender
        (trav->stud.info & 0b100000) ? "IRREGULAR" : "REGULAR", // Check if the 6th bit is set for enrollment status
        (trav->stud.info & 0b1000000) ? "FOREIGNER" : "FILIPINO", // Check if the 7th bit is set for nationality
        (trav->stud.info & 0b10000000) ? "ACTIVE" : "INACTIVE" // Check if the 8th bit is set for status
      );
    }
  }
}

/*
 Write the code for the function initDCISMDict().
 The function will receive a dcismDict, and initialize it to be empty.
 */
void initDCISMDict(dcismDict D) {
  int x, y;
  for (x = 0 ; x < NUMPROGRAMS ; x++){
    D[x].studCtr = 0;
    for (y = 0 ; y < YEARLEVELS ; y++){
      D[x].programStuds[y] = NULL;
    }
  }
  printf("\nInitialized DCISMDict.");
}

/*
 Write the code for the function convertToDCISMDict().
 The function will receive a dcismDict and an arrListStud. The function will go
 through list of students and insert them to their proper place in the
 dcismDict.
 */
void convertToDCISMDict(dcismDict D, arrListStud SL) {
  int x, y;
  studLL newStudent = NULL;
  studLL* trav = NULL;
  int program, year;

  // Outer loop to iterate over each student
  for (x = 0 ; x < SL.numStuds ; x++){
    // We get the programHash so that we will know which array index of dcismDict we will put, OR put simply, we know which program the student.
    program = programHash(SL.studs[x].info);
    year    = yearLevelHash(SL.studs[x].info);
    printf("\nprogram = %d, year = %d", program, year);
    // We get the year so that we know which array index in SL.
    // After knowing which year, we use that information so that we can use our trav to traverse the linked list.
    // After these two information: PROGRAM and YEAR, we perform insertSorted.
    for (trav = &(D[program].programStuds[year]) ; *trav != NULL && strcmp(SL.studs[x].idNum, (*trav)->stud.idNum) > 0 ; trav = &(*trav)->next){};
    if (*trav == NULL || strcmp(SL.studs[x].idNum, (*trav)->stud.idNum) != 0){
      newStudent = (studLL)malloc(sizeof(struct studNode));
      if (newStudent != NULL){
        newStudent->stud = SL.studs[x];
        newStudent->next = *trav;
        *trav = newStudent;
        D[program].studCtr++;
        printf("\nSuccessfully inserted [%s], studCtr[%d] = %d", SL.studs[x].idNum, yearLevelHash(newStudent->stud.info), D[program].studCtr);
      }
    } else {
      printf("\n\n**[%s] already exists!**", SL.studs[x].idNum);
    }
  }
  printf("\nConverted to DCISMDict.");
}

/*
 Code for this function has been partially provided.
 Write the code for the function displayDCISMDict().
 The function will receive a dcismDict. The function will display all the
 students in the dcismDict by program and year level.
 */
void displayDCISMDict(dcismDict D) {
  int program, year;
  unsigned char placeholder = 0b00000000;
  
  for (program = 0 ; program < NUMPROGRAMS ; program++){
    printf("\n[%s STUDENTS]", getProgram(placeholder));
    for (year = 0 ; year < YEARLEVELS ; year++){
      displayStudLL(D[program].programStuds[year]);
    }
    placeholder++;
  }
}

/*
 Write the code for the function initStudSet().
 The function will initialize an empty array of studSets that can accommodate
 the total number of programs.
 */
studSet *initStudSet(void) {
  studSet* retVal = NULL;
  return retVal;
}

/*
 Write the code for the function insertStudSet().
 The function will receive a studSet and a studRec. The function will insert the
 studRec into the studSet. Student will be inserted at the end of the set.
 */
void insertStudSet(studSet S, studRec sRecord) {}

/*
 Write the code for the function removeInactiveStudents().
 The function will go through the entire dcismDict and delete all student
 records that have the status "inactive". Deleted records will be stored in an
 array of studSets, such that each deleted student will be stored in its proper
 index in the array of studSets based on their program. Return the array of
 studSets to the calling function.
 */
studSet* removeInactiveStudents(dcismDict D) {
  int program, year;
  studLL* trav;
  studLL temp;
  studSet* inactiveStudents = initStudSet(); // Allocate memory properly
  if (inactiveStudents != NULL) {
    for (program = 0; program < NUMPROGRAMS; program++) {
      for (year = 0; year < YEARLEVELS; year++) {
        for (trav = &(D[program].programStuds[year]); *trav != NULL && (*inactiveStudents)->count < MAXSTUDS; trav = &(*trav)->next) {
          if (((*trav)->stud.info & 0b10000000) == 0b00000000) {
            temp = *trav;
            *trav = temp->next;
            strcpy((*inactiveStudents)->studs[(*inactiveStudents)->count].sName.fName, temp->stud.name.fName);
            strcpy((*inactiveStudents)->studs[(*inactiveStudents)->count].sName.lName, temp->stud.name.lName);
            strcpy((*inactiveStudents)->studs[(*inactiveStudents)->count].studID, temp->stud.idNum);
            (*inactiveStudents)->count++;
            printf("\nRemoved [%s]", temp->stud.idNum);
            free(temp);
          } else {
            printf("\nRemove failed. 4");
          }
        }
        printf("\nRemove failed. 3");
      }
      printf("\nRemove failed. 2");
    }
    printf("\nRemove failed. 1");
  }
  printf("\nRemoved inactive students.");
  return inactiveStudents;
}


/*
 Code for this function has been partially provided.
 Write the code for the function displayStudSets
 The function will go through the entire dcismDict and delete all student
 records that have the status "inactive". Deleted records will be stored in an
 array of studSets, such that each deleted student will be stored in its proper
 index in the array of studSets based on their program. Return the array of
 studSets to the calling function.
 */
void displayStudSets(studSet *S) {
  printf("\nAll Inactive Students");
  printf("%-10s", "Id Number");
  printf("%-10s", "fName");
  printf("%s", "lName\n");

  personalInfo program = 0b00;
  int stopper;
  for (stopper = 0 ; stopper < (*S)->count ; stopper++){
    printf("%-10s%-10s%s\n",
      (*S)->studs[stopper].studID,
      (*S)->studs[stopper].sName.fName,
      (*S)->studs[stopper].sName.lName
    );
  }
}

void generateStudentFile(void) {
  student students[] = {{"STUD1008", {"Olivia", 'B', "Hernandez"}, 0b01111011},
                        {"STUD1001", {"John", 'R', "Doe"}, 0b10000000},
                        {"STUD1020", {"Lily", 'N', "Tanaka"}, 0b11111111},
                        {"STUD1004", {"Joey", 'K', "Lee"}, 0b11001111},
                        {"STUD1002", {"Jane", 'L', "Smith"}, 0b11011001},
                        {"STUD1005", {"Michael", 'T', "Garcia"}, 0b00100100},
                        {"STUD1008", {"Olivia", 'B', "Hernandez"}, 0b01111011},
                        {"STUD1003", {"Mark", 'S', "Johnson"}, 0b10000010},
                        {"STUD1010", {"Mia", 'D', "Nguyen"}, 0b01011001},
                        {"STUD1011", {"Ethan", 'E', "Perez"}, 0b10000010},
                        {"STUD1021", {"Elijah", 'O', "Yamamoto"}, 0b00100100},
                        {"STUD1017", {"Daniel", 'K', "Cruz"}, 0b10000000},
                        {"STUD1019", {"Noah", 'M', "Reyes"}, 0b10000010},
                        {"STUD1012", {"Chung", 'F', "Tan"}, 0b11100111},
                        {"STUD1013", {"Alexander", 'G', "Reyes"}, 0b00101100},
                        {"STUD1014", {"Sofia", 'H', "Wong"}, 0b10010101},
                        {"STUD1015", {"Benjamin", 'I', "Liu"}, 0b11001010},
                        {"STUD1016", {"Chloe", 'J', "Gonzales"}, 0b00111011},
                        {"STUD1018", {"Garret", 'L', "Santos"}, 0b01001001},
                        {"STUD1029", {"Gabriel", 'W', "Nguyen"}, 0b01101100},
                        {"STUD1022", {"Harper", 'P', "Kim"}, 0b11011001},
                        {"STUD1009", {"James", 'C', "Kim"}, 0b10001000},
                        {"STUD1023", {"Lucas", 'Q', "Chen"}, 0b10101110},
                        {"STUD1024", {"Aria", 'R', "Garcia"}, 0b01110011},
                        {"STUD1033", {"Dylan", 'A', "Rodriguez"}, 0b00000000},
                        {"STUD1034", {"Zoe", 'B', "Hernandez"}, 0b10111101},
                        {"STUD1026", {"Evelyn", 'T', "Reyes"}, 0b00011101},
                        {"STUD1027", {"Joseph", 'U', "Tan"}, 0b11000110},
                        {"STUD1028", {"Victor", 'V', "Park"}, 0b10101111},
                        {"STUD1045", {"Eli", 'M', "Reyes"}, 0b01001100},
                        {"STUD1030", {"Axcel", 'X', "Garcia"}, 0b10001001},
                        {"STUD1031", {"Samuel", 'Y', "Lopez"}, 0b00100010},
                        {"STUD1032", {"Hannah", 'Z', "Martinez"}, 0b11011011},
                        {"STUD1035", {"Luke", 'C', "Kim"}, 0b11001010},
                        {"STUD1006", {"Emlio", 'P', "Martinez"}, 0b10100001},
                        {"STUD1025", {"Logan", 'S', "Rivera"}, 0b10001000},
                        {"STUD1036", {"Norton", 'D', "Nguyen"}, 0b00001111},
                        {"STUD1037", {"Isaac", 'E', "Perez"}, 0b11000100},
                        {"STUD1007", {"David", 'A', "Rodriguez"}, 0b10100110},
                        {"STUD1038", {"Eleanor", 'F', "Tan"}, 0b00011001},
                        {"STUD1039", {"Levi", 'G', "Reyes"}, 0b10100010},
                        {"STUD1040", {"Penelope", 'H', "Wong"}, 0b11010111},
                        {"STUD1050", {"Hazel", 'R', "Garcia"}, 0b01011001},
                        {"STUD1041", {"Aaron", 'I', "Liu"}, 0b00101000},
                        {"STUD1042", {"John", 'J', "Gonzales"}, 0b10000001},
                        {"STUD1043", {"Leo", 'K', "Cruz"}, 0b01001110},
                        {"STUD1044", {"Stella", 'L', "Santos"}, 0b10111111},
                        {"STUD1046", {"Maya", 'N', "Tanaka"}, 0b10010101},
                        {"STUD1047", {"Owen", 'O', "Yamamoto"}, 0b11000010},
                        {"STUD1039", {"Levi", 'G', "Reyes"}, 0b10100010},
                        {"STUD1048", {"Vince", 'P', "Kim"}, 0b00000011},
                        {"STUD1049", {"Caleb", 'Q', "Chen"}, 0b10100100},
                        {"STUD1050", {"Hazel", 'R', "Garcia"}, 0b01011001}};

  FILE *file = fopen("students.bin", "wb");
  if (file != NULL) {
    fwrite(students, sizeof(student), 52, file);
  }
  fclose(file);
}

int main(void) {
  // generateStudentFile
  /* Problem 1
      1) Declare a variable SL of type arrListStud and call
     populateStudentList() to populate it 2) Call displayArrListStud()
   */
  arrListStud SL;
  SL = populateStudentList();
  displayArrListStud(SL);

  /* Problem 2
      1) Declare a variable D of type dcismDict
      2) Call initDCISMDict()
      3) Call convertToDCISMDict()
      4) Call displayDCISMDict()
   */
  dcismDict D;
  initDCISMDict(D);
  convertToDCISMDict(D, SL);
  // printf("\n%d", D[0].studCtr);
  // printf("\n%d", D[1].studCtr);
  // printf("\n%d", D[2].studCtr);
  // printf("\n%d", D[3].studCtr);

  displayDCISMDict(D);

  /* Problem 3
      1) Declare a variable inactive of type studSet* and call
     removeInactiveStudents() to populate it 2) Call displayDCISMDict() 3) Call
     displayStudSets()
   */
  studSet* inactiveStudents;
  inactiveStudents = removeInactiveStudents(D);
  displayDCISMDict(D);
  displayStudSets(inactiveStudents);

  return 0;
}
