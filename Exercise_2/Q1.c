#include <stdio.h>
#include <string.h>
#define MAX_HISTORY 100
#define MAX_URL_LENGTH 200
char history[MAX_HISTORY][MAX_URL_LENGTH];
int top = -1;
void pushURL(const char* url) {
    if (top < MAX_HISTORY - 1) {
        top++;
        strncpy(history[top], url, MAX_URL_LENGTH);
        printf("URL '%s' added to history.\n", url);
    } else {
        printf("History is full!\n");
    }
}
void popURL() {
    if (top >= 0) {
        printf("Popped URL: %s\n", history[top]);
        top--;
    } else {
        printf("No URLs to pop.\n");
    }
}
void displayHistory() {
    if (top == -1) {
        printf("No history to display.\n");
        return;
    }
    printf("Current browser history:\n");
    for (int i = 0; i <= top; i++) {
        printf("%d. %s\n", i + 1, history[i]);
    }
}
int main() {
    pushURL("https://www.google.com");
    pushURL("https://www.example.com");
    displayHistory();

    popURL();
    displayHistory();
    
    return 0;
}
