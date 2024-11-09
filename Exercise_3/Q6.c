#include <stdio.h>
#include <stdlib.h>

typedef struct RideRequest {
    int requestId;
    char riderName[100];
    struct RideRequest* next;
} RideRequest;

RideRequest* front = NULL;
RideRequest* rear = NULL;

int isEmpty() {
    return (front == NULL);
}

void addRideRequest(int requestId, const char* riderName) {
    RideRequest* newRequest = (RideRequest*)malloc(sizeof(RideRequest));
    newRequest->requestId = requestId;
    strcpy(newRequest->riderName, riderName);
    newRequest->next = NULL;

    if (rear == NULL) {
        front = rear = newRequest;
    } else {
        rear->next = newRequest;
        rear = newRequest;
    }
    printf("Ride request from %s added to the queue.\n", riderName);
}

RideRequest* serveRideRequest() {
    if (isEmpty()) {
        printf("No ride requests to serve.\n");
        return NULL;
    }
    RideRequest* servedRequest = front;
    front = front->next;
    if (front == NULL) {
        rear = NULL;
    }
    return servedRequest;
}

void displayQueue() {
    if (isEmpty()) {
        printf("No ride requests in the queue.\n");
    } else {
        printf("Current Ride Requests Queue:\n");
        RideRequest* temp = front;
        while (temp != NULL) {
            printf("Request ID: %d, Rider: %s\n", temp->requestId, temp->riderName);
            temp = temp->next;
        }
    }
}

int main() {
    addRideRequest(1, "John");
    addRideRequest(2, "Emily");
    displayQueue();

    RideRequest* servedRequest = serveRideRequest();
    if (servedRequest) {
        printf("Served Ride Request: %d - %s\n", servedRequest->requestId, servedRequest->riderName);
        free(servedRequest);
    }

    displayQueue();

    return 0;
}
