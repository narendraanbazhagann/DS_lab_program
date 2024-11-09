#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Inquiry {
    int inquiryId;
    char customerName[100];
    struct Inquiry* next;
} Inquiry;

Inquiry* front = NULL;
Inquiry* rear = NULL;

int isEmpty() {
    return (front == NULL);
}

void addInquiry(int inquiryId, const char* customerName) {
    Inquiry* newInquiry = (Inquiry*)malloc(sizeof(Inquiry));
    newInquiry->inquiryId = inquiryId;
    strcpy(newInquiry->customerName, customerName);
    newInquiry->next = NULL;

    if (rear == NULL) {
        front = rear = newInquiry;
    } else {
        rear->next = newInquiry;
        rear = newInquiry;
    }
    printf("Inquiry from %s added to the queue.\n", customerName);
}

Inquiry* resolveInquiry() {
    if (isEmpty()) {
        printf("No inquiries to resolve.\n");
        return NULL;
    }
    Inquiry* resolvedInquiry = front;
    front = front->next;
    if (front == NULL) {
        rear = NULL;
    }
    return resolvedInquiry;
}

void displayQueue() {
    if (isEmpty()) {
        printf("No inquiries in the queue.\n");
    } else {
        printf("Current Inquiry Queue:\n");
        Inquiry* temp = front;
        while (temp != NULL) {
            printf("Inquiry ID: %d, Customer: %s\n", temp->inquiryId, temp->customerName);
            temp = temp->next;
        }
    }
}

int main() {
    addInquiry(1, "Darshana");
    addInquiry(2, "Shivani");
    displayQueue();

    Inquiry* resolved = resolveInquiry();
    if (resolved) {
        printf("Resolved Inquiry: %d - %s\n", resolved->inquiryId, resolved->customerName);
        free(resolved);
    }

    displayQueue();

    return 0;
}
