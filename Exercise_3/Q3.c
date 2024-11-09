#include <stdio.h>

#define MAX_QUEUE_SIZE 5

typedef struct {
    int callId;
    char customerName[100];
} Call;

Call queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

int isFull() {
    return (rear == MAX_QUEUE_SIZE - 1);
}

int isEmpty() {
    return (front == -1);
}

void enqueue(Call call) {
    if (isFull()) {
        printf("Queue is full! Cannot accept the call.\n");
    } else {
        if (front == -1) {
            front = 0;
        }
        rear++;
        queue[rear] = call;
        printf("Call from %s added to the queue.\n", call.customerName);
    }
}

Call dequeue() {
    if (isEmpty()) {
        printf("Queue is empty! No calls to dequeue.\n");
        Call emptyCall = {0, ""};
        return emptyCall;
    } else {
        Call call = queue[front];
        for (int i = 0; i < rear; i++) {
            queue[i] = queue[i + 1];
        }
        rear--;
        if (rear == -1) {
            front = -1;
        }
        return call;
    }
}

void displayQueue() {
    if (isEmpty()) {
        printf("No calls in the queue.\n");
    } else {
        printf("Current Call Queue:\n");
        for (int i = front; i <= rear; i++) {
            printf("Call ID: %d, Customer: %s\n", queue[i].callId, queue[i].customerName);
        }
    }
}

int main() {
    Call call1 = {1, "Alice"};
    Call call2 = {2, "Bob"};
    
    enqueue(call1);
    enqueue(call2);
    displayQueue();
    
    Call servedCall = dequeue();
    printf("Served Call: %d - %s\n", servedCall.callId, servedCall.customerName);
    
    displayQueue();
    
    return 0;
}
