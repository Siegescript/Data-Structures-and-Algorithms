#include <stdio.h>
#include <stdbool.h>

#define MAX 10
#define NULL_LINK -1

typedef char ElementType;
typedef int QueuePos;

typedef struct {
    ElementType data;
    QueuePos link;
} Node;

typedef struct {
    Node elem[MAX];
    QueuePos avail;
} Heap;

typedef struct {
    QueuePos front;
    QueuePos rear;
} Queue;

// Core API
void initHeap(Heap *H);
void initQueue(Queue *Q);
void freeQueue(Heap *H, Queue *Q);
void enqueue(Heap *H, Queue *Q, ElementType elem);
void dequeue(Heap *H, Queue *Q);
ElementType front(Heap H, Queue Q);

// Utility
bool isEmpty(Queue Q);
bool isHeapFull(Heap H);
void display(Heap H, Queue Q);

// Internal Memory Management Helpers
static QueuePos allocNode(Heap *H) {
    QueuePos ret = H->avail;
    if (ret != NULL_LINK) {
        H->avail = H->elem[ret].link;
        H->elem[ret].link = NULL_LINK;
    }
    return ret;
}

static void deallocNode(Heap *H, QueuePos del) {
    H->elem[del].link = H->avail;
    H->avail = del;
}

int main(void) {
    Heap H;
    Queue Q;

    initHeap(&H);
    initQueue(&Q);

    enqueue(&H, &Q, 'F');
    enqueue(&H, &Q, 'U');
    enqueue(&H, &Q, 'C');
    enqueue(&H, &Q, 'K');

    printf("--- Cursor Queue Contents ---\n");
    display(H, Q);

    printf("\nFront Element is: %c\n", front(H, Q));

    dequeue(&H, &Q);
    printf("Front Element after 1 dequeue: %c\n", front(H, Q));

    printf("\n--- Cursor Queue After Dequeue ---\n");
    display(H, Q);

    freeQueue(&H, &Q);
    return 0;
}

void initHeap(Heap *H) {
    for (int i = MAX - 1; i >= 0; i--) {
        H->elem[i].link = i - 1;
    }
    H->avail = MAX - 1;
}

void initQueue(Queue *Q) {
    Q->front = NULL_LINK;
    Q->rear = NULL_LINK;
}

void freeQueue(Heap *H, Queue *Q) {
    while (!isEmpty(*Q)) {
        dequeue(H, Q);
    }
}

bool isEmpty(Queue Q) {
    return Q.front == NULL_LINK;
}

bool isHeapFull(Heap H) {
    return H.avail == NULL_LINK;
}

void enqueue(Heap *H, Queue *Q, ElementType elem) {
    if (isHeapFull(*H)) {
        printf("ERROR: Heap overflow. Cannot enqueue '%c'.\n", elem);
        return;
    }

    QueuePos newNode = allocNode(H);
    H->elem[newNode].data = elem;
    H->elem[newNode].link = NULL_LINK;

    if (isEmpty(*Q)) {
        Q->front = newNode;
        Q->rear = newNode;
    } else {
        H->elem[Q->rear].link = newNode;
        Q->rear = newNode;
    }
}

void dequeue(Heap *H, Queue *Q) {
    if (isEmpty(*Q)) {
        printf("ERROR: Queue underflow. Cannot dequeue from an empty queue.\n");
        return;
    }

    QueuePos del = Q->front;
    Q->front = H->elem[del].link;
    deallocNode(H, del);

    // Reset rear index if queue becomes empty
    if (Q->front == NULL_LINK) {
        Q->rear = NULL_LINK;
    }
}

ElementType front(Heap H, Queue Q) {
    if (isEmpty(Q)) {
        printf("ERROR: Queue is empty. Returning null character.\n");
        return '\0'; // Safe fallback
    }
    return H.elem[Q.front].data;
}

void display(Heap H, Queue Q) {
    if (isEmpty(Q)) {
        printf("QUEUE IS EMPTY\n");
        return;
    }

    printf("FRONT -> ");
    for (QueuePos trav = Q.front; trav != NULL_LINK; trav = H.elem[trav].link) {
        printf("[%c | idx:%d] ", H.elem[trav].data, trav);
    }
    printf("<- REAR\n");
}