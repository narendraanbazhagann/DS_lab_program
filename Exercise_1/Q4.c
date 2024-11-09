#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Task {
    char taskName[100];
    struct Task* next;
} Task;
Task* head = NULL;
void addTaskAtBeginning(const char* taskName) {
    Task* newTask = (Task*)malloc(sizeof(Task));
    strcpy(newTask->taskName, taskName);
    newTask->next = head;
    head = newTask;
}
void removeTaskFromEnd() {
    if (head == NULL) {
        printf("No tasks to remove.\n");
        return;
    }

    Task* temp = head;
    Task* prev = NULL;
    
    while (temp->next != NULL) {
        prev = temp;
        temp = temp->next;
    }

    if (prev != NULL) {
        prev->next = NULL;
    } else {
        head = NULL;
    }

    free(temp);
    printf("Task removed from the end.\n");
}
void displayTasks() {
    if (head == NULL) {
        printf("No tasks to display.\n");
        return;
    }

    Task* temp = head;
    printf("Tasks:\n");
    while (temp != NULL) {
        printf("%s\n", temp->taskName);
        temp = temp->next;
    }
}
int main() {
    addTaskAtBeginning("Task 1");
    addTaskAtBeginning("Task 2");
    displayTasks();
    
    removeTaskFromEnd();
    displayTasks();
    
    return 0;
}
