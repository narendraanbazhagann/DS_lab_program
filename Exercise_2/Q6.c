#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    char data;
    struct Node* next;
} Node;

Node* top = NULL;
void push(char ch) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation error!\n");
        return;
    }
    newNode->data = ch;
    newNode->next = top;
    top = newNode;
}
char pop() {
    if (top == NULL) {
        return '\0';  // Return null if stack is empty
    }
    Node* temp = top;
    char poppedChar = top->data;
    top = top->next;
    free(temp);
    return poppedChar;
}
int isBalanced(const char* expr) {
    for (int i = 0; expr[i] != '\0'; i++) {
        char ch = expr[i];
        
        // If it's an opening bracket, push to stack
        if (ch == '(' || ch == '{' || ch == '[') {
            push(ch);
        } 
        
        else if (ch == ')' || ch == '}' || ch == ']')
            char topChar = pop();
            if ((ch == ')' && topChar != '(') ||
                (ch == '}' && topChar != '{') ||
                (ch == ']' && topChar != '[')) {
                return 0;  
            }
        }
    }
    return top == NULL;
}

int main() {
    const char* expr1 = "{[()]}";  
    const char* expr2 = "{[(])}";  
    const char* expr3 = "{[(";     
    if (isBalanced(expr1)) {
        printf("Expression 1 is balanced.\n");
    } else {
        printf("Expression 1 is unbalanced.\n");
    }

    if (isBalanced(expr2)) {
        printf("Expression 2 is balanced.\n");
    } else {
        printf("Expression 2 is unbalanced.\n");
    }

    if (isBalanced(expr3)) {
        printf("Expression 3 is balanced.\n");
    } else {
        printf("Expression 3 is unbalanced.\n");
    }

    return 0;
}
