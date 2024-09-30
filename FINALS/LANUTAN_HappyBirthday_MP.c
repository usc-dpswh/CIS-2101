#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MONTH_SIZE

//	General Definitions
typedef struct {
	unsigned char day;
//	000000 	= first six bits represent the day
	int year;
	int month; // (0-11, January-December)
} Personal;

typedef struct {
	char fName[24];
	char lName[24];
} Name;

//	Student definition
typedef struct {
	Name 		studentName;
	Personal 	sensitiveInfo;
	unsigned char status;		// 0 - dead, 1 - alive
} Student;

//	Stack Linked List Implementation Definition
typedef struct node {
	Student A;
	struct node* next;
} *StackLL;

//	Stack Definition
typedef struct stack {
	StackLL top;
	int stackCount;
} Stack;

//	Queue Definition
typedef struct queue {
	Student studentQueue[]
};

//	Tree Definition

//	files, stack (LL), queue (arr), tree 
