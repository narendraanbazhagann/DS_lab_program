#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_EXPR_LENGTH 100
#define MAX_STACK_SIZE 50

char stack[MAX_STACK_SIZE];
int top = -1;
int precedence(char operator) {
    if (operator == '+' || operator == '-') return 1;
    if (operator == '*' || operator == '/') return 2;
    return 0;
}
void push(char operator) {
    if (top < MAX_STACK_SIZE - 1) {
        stack[++top] = operator;
    } else {
        printf("Stack overflow.\n");
    }
}
char pop() {
    if (top >= 0) {
        return stack[top--];
    } else {
        return -1;  // Indicates empty stack
    }
}
void infixToPostfix(const char* expr) {
    char result[MAX_EXPR_LENGTH];
    int j = 0;
    
    for (int i = 0; expr[i] != '\0'; i++) {
        if (isdigit(expr[i])) {
            result[j++] = expr[i];
        } else if (expr[i] == '(') {
            push(expr[i]);
        } else if (expr[i] == ')') {
            while (top >= 0 && stack[top] != '(') {
                result[j++] = pop();
            }
            pop();  // Pop '('
        } else if (strchr("+-*/", expr[i])) {
            while (top >= 0 && precedence(stack[top]) >= precedence(expr[i])) {
                result[j++] = pop();
            }
            push(expr[i]);
        }
    }
    
    while (top >= 0) {
        result[j++] = pop();
    }
    
    result[j] = '\0';
    printf("Postfix expression: %s\n", result);
}
int main() {
    const char* expr = "3+(2*5)-8";
    infixToPostfix(expr);
    return 0;
}
