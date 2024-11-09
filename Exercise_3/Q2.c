#include <stdio.h>

#define MAX_QUEUE_SIZE 5

typedef struct {
    int customerId;
    char name[100];
} Customer;

Customer queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

int isFull() {
    return (rear == MAX_QUEUE_SIZE - 1);
}

int isEmpty() {
    return (front == -1);
}

void addCustomer(Customer customer) {
    if (isFull()) {
        printf("Queue is full! Cannot add customer.\n");
    } else {
        if (front == -1) {
            front = 0;
        }
        rear++;
        queue[rear] = customer;
        printf("Customer %s added to the queue.\n", customer.name);
    }
}

Customer serveCustomer() {
    if (isEmpty()) {
        printf("Queue is empty! No customers to serve.\n");
        Customer emptyCustomer = {0, ""};
        return emptyCustomer;
    } else {
        Customer customer = queue[front];
        for (int i = 0; i < rear; i++) {
            queue[i] = queue[i + 1];
        }
        rear--;
        if (rear == -1) {
            front = -1;
        }
        return customer;
    }
}

void displayQueue() {
    if (isEmpty()) {
        printf("No customers in the queue.\n");
    } else {
        printf("Current Customer Queue:\n");
        for (int i = front; i <= rear; i++) {
            printf("Customer ID: %d, Name: %s\n", queue[i].customerId, queue[i].name);
        }
    }
}

int main() {
    Customer customer1 = {1, "John Doe"};
    Customer customer2 = {2, "Jane Smith"};
    
    addCustomer(customer1);
    addCustomer(customer2);
    displayQueue();
    
    Customer servedCustomer = serveCustomer();
    printf("Served Customer: %d - %s\n", servedCustomer.customerId, servedCustomer.name);
    
    displayQueue();
    
    return 0;
}
