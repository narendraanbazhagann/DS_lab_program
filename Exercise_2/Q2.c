#include <stdio.h>
#include <string.h>
#define MAX_CHANGES 100
#define MAX_CHANGE_LENGTH 200
char undoStack[MAX_CHANGES][MAX_CHANGE_LENGTH];
int top = -1;
void pushChange(const char* change) {
    if (top < MAX_CHANGES - 1) {
        top++;
        strncpy(undoStack[top], change, MAX_CHANGE_LENGTH);
        printf("Change '%s' saved for undo.\n", change);
    } else {
        printf("Undo stack is full!\n");
    }
}
void undoChange() {
    if (top >= 0) {
        printf("Undone change: %s\n", undoStack[top]);
        top--;
    } else {
        printf("No changes to undo.\n");
    }
}
void displayChanges() {
    if (top == -1) {
        printf("No changes to display.\n");
        return;
    }
    printf("Undo stack:\n");
    for (int i = 0; i <= top; i++) {
        printf("%d. %s\n", i + 1, undoStack[i]);
    }
}
int main() {
    pushChange("Typed 'Hello World'");
    pushChange("Typed 'Welcome to the editor'");
    displayChanges();

    undoChange();
    displayChanges();
    
    return 0;
}
