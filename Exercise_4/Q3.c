#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void reverseString(char *str) {
    Stack s;
    initStack(&s);
    for (int i = 0; str[i] != '\0'; i++) {
        push(&s, str[i]);
    }
    int i = 0;
    while (s.top >= 0) {
        str[i++] = pop(&s);
    }
    str[i] = '\0'; 
}

int main() {
    char str[] = "Hello World!";
    
    printf("Original string: %s\n", str);
    
    reverseString(str);
    
    printf("Reversed string: %s\n", str);

    return 0;
}
