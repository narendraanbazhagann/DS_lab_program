#include <stdio.h>
#include <string.h>

#define MAX_QUEUE_SIZE 5

typedef struct {
    int jobId;
    char documentName[100];
} PrintJob;

PrintJob queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

int isFull() {
    return (rear == MAX_QUEUE_SIZE - 1);
}

int isEmpty() {
    return (front == -1);
}

void enqueue(PrintJob job) {
    if (isFull()) {
        printf("Queue is full! Cannot add print job.\n");
    } else {
        if (front == -1) {
            front = 0;
        }
        rear++;
        queue[rear] = job;
        printf("Added job: %d - %s\n", job.jobId, job.documentName);
    }
}

PrintJob dequeue() {
    if (isEmpty()) {
        printf("Queue is empty! No jobs to dequeue.\n");
        PrintJob emptyJob = {0, ""};
        return emptyJob;
    } else {
        PrintJob job = queue[front];
        for (int i = 0; i < rear; i++) {
            queue[i] = queue[i + 1];
        }
        rear--;
        if (rear == -1) {
            front = -1;
        }
        return job;
    }
}
void displayQueue() {
    if (isEmpty()) {
        printf("No print jobs in the queue.\n");
    } else {
        printf("Current Print Queue:\n");
        for (int i = front; i <= rear; i++) {
            printf("Job ID: %d, Document: %s\n", queue[i].jobId, queue[i].documentName);
        }
    }
}
int main() {
    PrintJob job1 = {1, "Document1.pdf"};
    PrintJob job2 = {2, "Document2.docx"};
    
    enqueue(job1);
    enqueue(job2);
    displayQueue();
    
    PrintJob dequeuedJob = dequeue();
    printf("Dequeued Job: %d - %s\n", dequeuedJob.jobId, dequeuedJob.documentName);
    
    displayQueue();
    
    return 0;
}
