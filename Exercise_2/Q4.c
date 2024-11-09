#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Move {
    char moveDescription[100];
    struct Move* next;
} Move;
Move* top = NULL;
void pushMove(const char* moveDescription) {
    Move* newMove = (Move*)malloc(sizeof(Move));
    strcpy(newMove->moveDescription, moveDescription);
    newMove->next = top;
    top = newMove;
    printf("Move '%s' added.\n", moveDescription);
}
void popMove() {
    if (top != NULL) {
        Move* temp = top;
        top = top->next;
        printf("Move popped: %s\n", temp->moveDescription);
        free(temp);
    } else {
        printf("No moves to pop.\n");
    }
}
void displayMoves() {
    if (top == NULL) {
        printf("No moves to display.\n");
        return;
    }

    Move* current = top;
    printf("Current moves stack:\n");
    while (current != NULL) {
        printf("%s\n", current->moveDescription);
        current = current->next;
    }
}
int main() {
    pushMove("Player 1 moved to position (2, 3)");
    pushMove("Player 2 moved to position (3, 1)");
    displayMoves();

    popMove();
    displayMoves();
    
    return 0;
}
