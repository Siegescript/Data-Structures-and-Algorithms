#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef char ElementType;

typedef struct node {
    ElementType data;
    struct node *link;
} Node, *NodePtr;

typedef struct {
    NodePtr front;
    NodePtr rear;
} Queue;

// Core API
void initQueue(Queue *Q);
void freeQueue(Queue *Q);
void enqueue(Queue *Q, ElementType elem);
void dequeue(Queue *Q);
ElementType front(Queue Q);

// Utililty
bool isEmpty(Queue Q);
void display(Queue Q);

// Internal helper for node allocation
static NodePtr createNode(ElementType elem) {
    NodePtr newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("CRITICAL ERROR: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = elem;
    newNode->link = NULL;
    return newNode;
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

    printf("\n--- Linked Queue After Dequeue ---\n");
    display(Q);

    freeQueue(&Q);
    return 0;
}

void initQueue(Queue *Q) {
    Q->front = NULL;
    Q->rear = NULL;
}

void freeQueue(Queue *Q) {
    while (!isEmpty(*Q)) {
        dequeue(Q);
    }
}

void enqueue(Queue *Q, ElementType elem) {
    NodePtr newNode = createNode(elem);
    
    if (isEmpty(*Q)) {
        Q->front = newNode;
        Q->rear = newNode;
    } else {
        Q->rear->link = newNode;
        Q->rear = newNode;
    }
}

void dequeue(Queue *Q) {
    if (isEmpty(*Q)) {
        printf("ERROR: Queue underflow. Cannot dequeue from an empty queue.\n");
        return;
    }
    
    NodePtr del = Q->front;
    Q->front = Q->front->link;
    free(del);

    // If the very last node was dequeued, reset the rear pointer as well
    if(Q->front == NULL) {
        Q->rear = NULL;
    }
}

ElementType front(Queue Q) {
    if (isEmpty(Q)) {
        printf("ERROR: Queue is empty. Returning null character.\n");
        return '\0'; // Safe fallback
    }
    return Q.front->data;
}

bool isEmpty(Queue Q) {
    return Q.front == NULL;
}

void display(Queue Q) {
    if (isEmpty(Q)) {
        printf("QUEUE IS EMPTY\n");
        return;
    }
    
    printf("FRONT -> ");
    for (NodePtr trav = Q.front; trav != NULL; trav = trav->link) {
        printf("[%c] ", trav->data);
    }
    printf("<- REAR\n");
}