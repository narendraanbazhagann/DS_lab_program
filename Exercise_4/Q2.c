#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

typedef struct {
    char data[MAX_STACK_SIZE];
    int top;
} Stack;
void initStack(Stack *s) {
    s->top = -1;
}
void push(Stack *s, char value) {
    if (s->top < MAX_STACK_SIZE - 1) {
        s->data[++(s->top)] = value;
    } else {
        printf("Stack overflow\n");
    }
}
char pop(Stack *s) {
    if (s->top >= 0) {
        return s->data[(s->top)--];
    } else {
        printf("Stack underflow\n");
        return '\0'; // Return an error value
    }
}
int isOpening(char ch) {
    return (ch == '(' || ch == '{' || ch == '[');
}
int isMatchingPair(char opening, char closing) {
    return (opening == '(' && closing == ')') ||
           (opening == '{' && closing == '}') ||
           (opening == '[' && closing == ']');
}
int checkBalancedParentheses(const char *expr) {
    Stack s;
    initStack(&s);

    for (int i = 0; expr[i] != '\0'; i++) {
        char ch = expr[i];

        if (isOpening(ch)) {
            push(&s, ch);
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (s.top == -1) {
                return 0; // No matching opening bracket
            }

            char opening = pop(&s);
            if (!isMatchingPair(opening, ch)) {
                return 0; // Mismatched pair
            }
        }
    }

    // If the stack is empty, parentheses are balanced
    return s.top == -1;
}

int main() {
    const char *expr1 = "if (x > 0) { return (x); }";
    const char *expr2 = "if (x > 0 { return (x); }";
    
    printf("Expression 1 is %sbalanced.\n", checkBalancedParentheses(expr1) ? "" : "un");
    printf("Expression 2 is %sbalanced.\n", checkBalancedParentheses(expr2) ? "" : "un");

    return 0;
}
