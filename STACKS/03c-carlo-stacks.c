#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *link;
} Node;

typedef struct {
    Node *top;
} Stack;

void init(Stack *stack) { stack->top = NULL; }

void push(Stack *stack, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = value;
    newNode->link = stack->top;
    stack->top = newNode;
}

int pop(Stack *stack) {
    if (stack->top == NULL) {
        printf("Stack is empty. Cannot pop.\n");
        exit(1);
    }
    Node *temp = stack->top;
    int poppedValue = temp->data;
    stack->top = temp->link;
    free(temp);
    return poppedValue;
}

int main() {
    Stack stack;
    init(&stack);

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    printf("Popped: %d\n", pop(&stack));
    printf("Popped: %d\n", pop(&stack));
    printf("Popped: %d\n", pop(&stack));

    return 0;
}