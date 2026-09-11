#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INITIAL_CAPACITY 5

// Typedef allows easy swapping to complex structs later
typedef char ElementType;

typedef struct {
    ElementType *data;
    int front;
    int rear;
    int count;
    int capacity;
} Queue;

// Core API
void initQueue(Queue *Q);
void freeQueue(Queue *Q);
void enqueue(Queue *Q, char elem);
void dequeue(Queue *Q);
ElementType front(Queue Q);

// Utility
bool isEmpty(Queue Q);
void display(Queue Q);

// Internal helper for dynamic resizing and unwrapping
static void resize(Queue *Q, int new_capacity) {
    ElementType *temp = malloc(sizeof(ElementType) * new_capacity);
    if (temp == NULL) {
        printf("CRITICAL ERROR: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < Q->count; i++) {
        temp[i] = Q->data[(Q->front + i) % Q->capacity];
    }

    free(Q->data);
    Q->data = temp;
    Q->capacity = new_capacity;
    Q->front = 0;
    Q->rear = Q->count - 1;
}

int main(void) {
    Queue Q;
    initQueue(&Q);

    enqueue(&Q, 'F');
    enqueue(&Q, 'U');
    enqueue(&Q, 'C');
    enqueue(&Q, 'K');
    
    printf("--- Queue Contents ---\n");
    display(Q);

    printf("\nFront Element is: %c\n", front(Q));
    
    dequeue(&Q);
    printf("Front Element after 1 dequeue: %c\n\n", front(Q));

    // Force a wrap-around and then a resize to prove the logic holds
    enqueue(&Q, 'S');
    enqueue(&Q, 'Y'); 
    enqueue(&Q, 'S'); // This will trigger the resize() and realignment

    printf("--- Queue After Wrap and Resize ---\n");
    display(Q);

    freeQueue(&Q);
    return 0;
}

void initQueue(Queue *Q) {
    Q->capacity = INITIAL_CAPACITY;
    Q->data = malloc(sizeof(ElementType) * Q->capacity);
    if (Q->data == NULL) {
        printf("CRITICAL ERROR: Memory allocation failed during initialization.\n");
        exit(EXIT_FAILURE);
    }
    Q->front = 0;
    Q->rear = -1;
    Q->count = 0;
}

void freeQueue(Queue *Q) {
    free(Q->data);
    Q->data = NULL;
    Q->front = 0;
    Q->rear = -1;
    Q->count = 0;
    Q->capacity = 0;
}

void enqueue(Queue *Q,char elem) {
    if (Q->count == Q->capacity) {
        resize(Q, Q->capacity * 2);
    }
    
    Q->rear = (Q->rear + 1) % Q->capacity;
    Q->data[Q->rear] = elem;
    Q->count++;
}

void dequeue(Queue *Q) {
    if (isEmpty(*Q)) {
        printf("ERROR: Queue underflow. Cannot dequeue from an empty queue.\n");
        return;
    }
    
    Q->front = (Q->front + 1) % Q->capacity;
    Q->count--;
    
    // Shrink array if it is severely underutilized
    if (Q->count > 0 && Q->count == (Q->capacity / 4)) {
        resize(Q, Q->capacity / 2);
    }
}

bool isEmpty(Queue Q) {
    return Q.count == 0;
}

ElementType front(Queue Q) {
    if (isEmpty(Q)) {
        printf("ERROR: Queue is empty. Returning null character.\n");
        return '\0'; // Safe fallback
    }
    return Q.data[Q.front];
}

void display(Queue Q) {
    if (isEmpty(Q)) {
        printf("QUEUE IS EMPTY\n");
        return;
    }
    
    printf("FRONT -> ");
    for (int i = 0; i < Q.count; i++) {
        int index = (Q.front + i) % Q.capacity;
        printf("[%c] ", Q.data[index]);
    }
    printf("<- REAR (Count: %d, Capacity: %d)\n", Q.count, Q.capacity);
}