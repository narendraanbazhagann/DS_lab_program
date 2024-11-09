#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node {
    char data;
    struct Node* next;
} Node;
Node* top = NULL;
void push(char ch) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = ch;
    newNode->next = top;
    top = newNode;
}
char pop() {
    if (top != NULL) {
        char ch = top->data;
        Node* temp = top;
        top = top->next;
        free(temp);
        return ch;
    } else {
        return '\0';  // Stack is empty
    }
}
int isBalanced(const char* expr) {
    for (int i = 0; expr[i] != '\0'; i++) {
        if (expr[i] == '(' || expr[i] == '[' || expr[i] == '{') {
            push(expr[i]);
        } else if (expr[i] == ')' || expr[i] == ']' || expr[i] == '}') {
            char topChar = pop();
            if ((expr[i] == ')' && topChar != '(') || 
                (expr[i] == ']' && topChar != '[') ||
                (expr[i] == '}' && topChar != '{')) {
                return 0;  // Not balanced
            }
        }
    }
    
    return top == NULL;  // If stack is empty, the expression is balanced
}
int main() {
    const char* expr = "{[()]}";
    if (isBalanced(expr)) {
        printf("The expression is balanced.\n");
    } else {
        printf("The expression is not balanced.\n");
    }
    
    return 0;
}
