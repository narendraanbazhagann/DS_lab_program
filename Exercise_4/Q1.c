#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_STACK_SIZE 100

typedef struct {
    int data[MAX_STACK_SIZE];
    int top;
} Stack;
void initStack(Stack *s) {
    s->top = -1;
}
void push(Stack *s, int value) {
    if (s->top < MAX_STACK_SIZE - 1) {
        s->data[++(s->top)] = value;
    } else {
        printf("Stack overflow\n");
    }
}
int pop(Stack *s) {
    if (s->top >= 0) {
        return s->data[(s->top)--];
    } else {
        printf("Stack underflow\n");
        return -1; // Return an error value
    }
}
int evaluatePostfix(const char *expr) {
    Stack s;
    initStack(&s);
    
    for (int i = 0; expr[i] != '\0'; i++) {
        if (isspace(expr[i])) {
            continue;
        }
        if (isdigit(expr[i])) {
            int num = expr[i] - '0';
            push(&s, num);
        }
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            int operand2 = pop(&s);
            int operand1 = pop(&s);
            
            switch (expr[i]) {
                case '+': push(&s, operand1 + operand2); break;
                case '-': push(&s, operand1 - operand2); break;
                case '*': push(&s, operand1 * operand2); break;
                case '/': push(&s, operand1 / operand2); break;
            }
        }
    }
    return pop(&s);
}

int main() {
    char postfixExpression[] = "23 45 + 6 *";
    int result = evaluatePostfix(postfixExpression);
    printf("Result of postfix evaluation: %d\n", result);
    return 0;
}
