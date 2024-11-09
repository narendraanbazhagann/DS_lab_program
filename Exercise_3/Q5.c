#include <stdio.h>
#include <stdlib.h>

typedef struct Customer {
    int customerId;
    char name[100];
    struct Customer* next;
} Customer;

Customer* front = NULL;
Customer* rear = NULL;

int isEmpty() {
    return (front == NULL);
}

void enqueue(int customerId, const char* name) {
    Customer* newCustomer = (Customer*)malloc(sizeof(Customer));
    newCustomer->customerId = customerId;
    strcpy(newCustomer->name, name);
    newCustomer->next = NULL;

    if (rear == NULL) {
        front = rear = newCustomer;
    } else {
        rear->next = newCustomer;
        rear = newCustomer;
    }
    printf("Customer %d - %s added to the queue.\n", customerId, name);
}

Customer* dequeue() {
    if (isEmpty()) {
        printf("No customers in the queue.\n");
        return NULL;
    }
    Customer* temp = front;
    front = front->next;
    if (front == NULL) {
        rear = NULL;
    }
    return temp;
}

void displayQueue() {
    if (isEmpty()) {
        printf("No customers in the queue.\n");
    } else {
        printf("Current Bank Queue:\n");
        Customer* temp = front;
        while (temp != NULL) {
            printf("Customer ID: %d, Name: %s\n", temp->customerId, temp->name);
            temp = temp->next;
        }
    }
}

int main() {
    enqueue(1, "Alice");
    enqueue(2, "Bob");
    displayQueue();

    Customer* servedCustomer = dequeue();
    if (servedCustomer) {
        printf("Served Customer: %d - %s\n", servedCustomer->customerId, servedCustomer->name);
        free(servedCustomer);
    }

    displayQueue();

    return 0;
}
