#include <stdio.h>
#include <stdbool.h>

bool isValid(char *s) {
    char stack[100];
    int top = -1;

    for (int i = 0; s[i] != '\0'; i++) {
        char current = s[i];

        if (current == '(' || current == '{' || current == '[') {
            stack[++top] = current;
        } 
        else if (current == ')' || current == '}' || current == ']') {
            if (top == -1) return false;

            char topChar = stack[top--]; // Pop the top element

            if ((current == ')' && topChar != '(') ||
                (current == '}' && topChar != '{') ||
                (current == ']' && topChar != '[')) {
                return false;
            }
        }
    }

    return top == -1;
}

int main() {
    char *s = "{[()]}";
    printf("%s\n", isValid(s) ? "Valid" : "Invalid");
    return 0;
}