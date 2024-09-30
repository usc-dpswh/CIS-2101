#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef enum {VACANT, OCCUPIED, DAMAGED} state;

typedef struct{
    char idNumber[9];
    char fName[32];
    char lName[32];
}studentRecord;

typedef struct{
    studentRecord currentUser;
    char lastUser[9]; //ID Number of the last student who used the PC.
    int pcNumber;
    state pcState;
}pcRecord;

typedef struct{
    pcRecord PC[30];
    int count;    //refers to the total number of desktops
    int occupied; //refers to the number of occupied desktops
}pcList;

/*Codes have already been provided for these functions*/
char* displayState(state S);
void displayPCRecords(pcRecord PCList[]);
void displayPCList(pcList desktops);

/*Problem 1*/
void initPCList(pcList* desktops, int numPCs);
void populatePCList(pcList* desktops);

/*Problem 2*/
void usePC(pcList* desktops, int pcNumber, studentRecord SR);

/*Problem 3*/
void vacatePC(pcList* desktops, int pcNumber);

/*Problem 4*/
pcList genPCListOccupied(pcList desktops);

/*Problem 5*/
void reportDamagedPC(pcList* desktops, studentRecord SR);
pcRecord* removeDamagedPCs(pcList* desktops);

int main(void) {
    pcList LB445;
    
    /*Problem 1*/
    //call initPCList() passing LB445 as the parameter. Initialize the list to have only 5 computers.
    initPCList(&LB445, 5);
    //call populatePCList() passing LB445 as the parameter.
    populatePCList(&LB445);
    //call displayPCList() passing LB445 as the parameter.
    displayPCList(LB445);

    /*Problem 2*/
    //Initialize a studentRecord stud1 with the values 14101941, Cris, Militante.
    studentRecord stud1 = {"14101941", "Cris", "Militante"};
    //Call usePC() passing LB445, pcNumber 8, and stud1 as the parameters. This is to check if your code works for a pcNumber that doesn't exist.
    usePC(&LB445, 8, stud1);
    //Call usePC() passing LB445, pcNumber 3, and stud1 as the parameters.
    usePC(&LB445, 3, stud1);
    //call displayPCList() passing LB445 as the parameter.
    displayPCList(LB445);


    /*Problem 3*/
    //Call vacatePC() passing LB445 and pcNumber 3 as the parameter.
    vacatePC(&LB445, 3);
    //Call displayPCList() passing LB445 as the parameter.
    displayPCList(LB445);
    //Initialize a studentRecord stud2 with the values 14101943, Gabby, Pineda.
    studentRecord stud2 = {"14101943", "Gabby", "Pineda"};
    //Call usePC() passing LB445, pcNumber 3, and stud2 as the parameters.
    usePC(&LB445, 3, stud2);
    //Call displayPCList() passing LB445 as the parameter.
    displayPCList(LB445);
    //Initialize a studentRecord stud3 with the values 14101945, Patty, Woo.
    studentRecord stud3 = {"14101945", "Patty", "Woo"};
    //Call usePC() passing LB445, pcNumber 3, and stud3 as the parameters.
    usePC(&LB445, 3, stud3);
    //Call displayPCList() passing LB445 as the parameter.
    displayPCList(LB445);


    /*Problem 4*/
    //Initialize a new pcList occLB445 using genPCListOccupied().
    pcList occLB445;
    occLB445 = genPCListOccupied(LB445);
    //Call displayPCList() passing LB445 as the parameter.
    displayPCList(occLB445);


    /*Problem 5*/
    //Call reportDamagedPC() passing LB445, and stud3 as the parameters.
    reportDamagedPC(&LB445, stud3);
    //Call reportDamagedPC() passing LB445, and stud3 as the parameters.
    reportDamagedPC(&LB445, stud3);
    //Call displayPCList() passing LB445 as the parameter.
    displayPCList(LB445);
    //Initialize a new array of pcRecords using removeDamagedPCs().
    pcRecord* damagePC;
    damagePC = removeDamagedPCs(&LB445);
    //Call displayPCList() passing LB445 as the parameter.
    displayPCList(LB445);
    //Call displayPCRecords() passing damagedPCs as the parameter.
    displayPCRecords(damagePC);
 

    return 0;
}


/*Code for function displayState() has already been provided*/
char* displayState(state S)
{
    char* stateDescription = NULL;
    char buffer[64];
    switch(S){
        case 0:
            strcpy(buffer, "VACANT");
            break;
        case 1:
            strcpy(buffer, "OCCUPIED");
            break;
        case 2:
            strcpy(buffer, "DAMAGED");
            break;
        default:
            strcpy(buffer, "Error Occured");
    }
   
    stateDescription = (char*) malloc (sizeof(strlen(buffer) + 1));
    if(stateDescription != NULL){
        strcpy(stateDescription, buffer);
    }
    return stateDescription;
}

/* Write the code for the function initPCList(). This function will receive a pcList,
and the inital number of PCs. The function will initialize the arrayList of desktops to have its proper count and occupied values based on the parameters.
 */
void initPCList(pcList* desktops, int numPCs)
{
  desktops->count = numPCs;
  desktops->occupied = 0;
}
 
/* Write the code for the function populatePCList(). This function will receive a pcList. The function
   will populate the pcList with default values for each PC. The default studentRecord will contain strings
   containing "XXX" for both names, and "XXXXXXXX" for the idNumber. Initialize the other structure elements
   with values that make sense. CLUE: Look at the structure of the pcRecord and think of the values that should
   be populated to those fields when a PC is initially empty.
 */
void populatePCList(pcList* desktops){
  int x;
  for (x = 0 ; x < desktops->count ; x++){
    strcpy(desktops->PC[x].currentUser.fName, "XXX");
    strcpy(desktops->PC[x].currentUser.lName, "XXX");
    strcpy(desktops->PC[x].currentUser.idNumber, "XXXXXXXX");
    strcpy(desktops->PC[x].lastUser, "XXXXXXXX");
    desktops->PC[x].pcNumber = x;
    desktops->PC[x].pcState = VACANT;
  }
  printf("Initialized PC List.\n");
}

/* Code for the function displayPCList() is partially given.*/
void displayPCList(pcList desktops){
  int x;
  for(x = 0 ; x < desktops.count ; x++){
    printf("PC[%d]\nState: %s\nCurrent User: %s, \nLast User: %s\n\n",
      desktops.PC[x].pcNumber,
      displayState(desktops.PC[x].pcState),
      desktops.PC[x].currentUser,
      desktops.PC[x].lastUser);
  }
  printf("Occupancy Rate: %d/%d\n\n", desktops.occupied, desktops.count);
}
 
/* Write the code for the function usePC(). The function will receive a pcList, a pcNumber, and a studentRecord.
   The function will simulate the process of a student who wants to use the given pcNumber. The function will check
   for the following:
    1) If the pcNumber is a valid pcNumber (meaning, if there are only 5 PCs, only pcNumber 0-4 are valid.
    2) If there are still PCs that are unnoccupied.
    3) If the pcNumber that the student has selected is VACANT.
        If it is, then assign that PC to the student by setting the student's records in the pcList.
        If it isn't, then look for the nearest available PC that can be used (forward search).
        
 */
void usePC(pcList* desktops, int pcNumber, studentRecord SR){
  if (pcNumber < desktops->count && desktops->occupied < desktops->count){
    if (desktops->PC[pcNumber].pcState == VACANT){
      desktops->PC[pcNumber].currentUser = SR;
      desktops->PC[pcNumber].pcState = OCCUPIED;
      desktops->occupied++;
    } else {
      int x;
      for (x = pcNumber ; desktops->PC[x].pcState != VACANT ; x = (x + 1) % desktops->count){};
      desktops->PC[x].currentUser = SR;
      desktops->PC[x].pcState = OCCUPIED;
      desktops->occupied++;
    }
  } 
}


/* Write the code for the function vacatePC(). The function will receive a pcList and a pcNumber as parameters.
   The function will remove the student student from the passed pcNumber from the pcList, and revert the values
   to their defaults EXCEPT for the lastUser member. Update values where it makes sense.
 */
void vacatePC(pcList* desktops, int pcNumber){
  if (pcNumber < desktops->count && desktops->PC[pcNumber].pcState == OCCUPIED){
    strcpy(desktops->PC[pcNumber].lastUser,desktops->PC[pcNumber].currentUser.idNumber);
    strcpy(desktops->PC[pcNumber].currentUser.fName, "XXX");
    strcpy(desktops->PC[pcNumber].currentUser.lName, "XXX");
    strcpy(desktops->PC[pcNumber].currentUser.idNumber, "XXXXXXXX");
    desktops->PC[pcNumber].pcState = VACANT;
    desktops->occupied--;
  }
}
 
/* Write the code for the function reportDamagedPC(). This function will receive a pcList and a studentRecord.
   The function will go through the pcList and check if the pass studentRecord is currently using a PC. If they are,
   then update the state of the PC they are using as damaged, and assign them the next available PC from PC 0.
   CLUE: You are allowed to use functions that have already been coded.
 */
void reportDamagedPC(pcList* desktops, studentRecord SR){
  int x;
  int isUsingPC;
  for (x = 0 ; x < desktops->count && strcmp(desktops->PC[x].currentUser.idNumber, SR.idNumber) != 0 ; x++){};

  if (x < desktops->count){
    // vacatePC(desktops, x);
    desktops->PC[x].pcState = DAMAGED;
    usePC(desktops, 0, SR);
    desktops->occupied--;
  }    
}

/* Write the code for the function genPCListOccupied(). The function will receive a pcList. The function will go
 through the passed pcList and return a new pcList containing only the OCCUPIED PCs. Do not remove the occupied
  PCs from the original list.
 */
pcList genPCListOccupied(pcList desktops){
  pcList occupiedPCs;
  initPCList(&occupiedPCs, 0);
  int x, y;
  for (x = 0, y = 0 ; x < desktops.count ; x++){
    if (desktops.PC[x].pcState == OCCUPIED){
      occupiedPCs.PC[y] = desktops.PC[x];
      occupiedPCs.count++;
      y++;
    }
  }
  occupiedPCs.occupied = occupiedPCs.count; 
  return occupiedPCs;
}

/* Write the code for the function removeDamagedPCs(). The function will receive a pcList. The function will go
  through the given pcList and return an array of pcRecords that contain all the DAMAGED PCs from the pcList.
  Let the first index of the array of pcRecords containg a sentinel value containing "00000000", END, END, END,
  -1, VACANT. This function also deletes the damaged PCs from the original list.
 */
pcRecord* removeDamagedPCs(pcList* desktops){
  pcRecord* damage;
  pcRecord sentinel = {{"00000000", "END", "END"}, "END", -1, VACANT};
  int x, damageCount = 0;

  for (x = 0 ; x < desktops->count ; x++){
    if (desktops->PC[x].pcState == DAMAGED){
      damageCount++;
    }
  }
  damage = (pcRecord*)malloc(sizeof(pcRecord)*(damageCount + 1));
  
  if (damage != NULL){
    int y,z;
    for (x = 0, y = 0 ; x < desktops->count ; x++){
      if (desktops->PC[x].pcState == DAMAGED){
        damage[y] = desktops->PC[x];
        for (z = x ; z < desktops->count ; z++){
          desktops->PC[z] = desktops->PC[z+1];
        }
        desktops->count--;
        y++;
      }
    }
    damage[damageCount] = sentinel;
  }
  return damage;
}

/* Code for the function displayPCRecords() is partially given.*/
void displayPCRecords(pcRecord PCList[]){
  int x;
  for( x = 0 ; PCList[x].pcNumber != -1 ; x++){
    printf("PC[%d]\nState: %s\nCurrent User: %s, \nLast User: %s\n\n",
    PCList[x].pcNumber,
    displayState(PCList[x].pcState),
    PCList[x].currentUser.idNumber,
    PCList[x].lastUser);
  }
}
