#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define INITIAL_CAPACITY 5

// Typedef allows easy swapping to a struct for later implementations
typedef char ElementType;

typedef struct {
    ElementType *data;
    int top;
    int capacity;
} Stack;

// Core API
void initStack(Stack *S);
void freeStack(Stack *S);
void push(Stack *S, ElementType elem);
void pop(Stack *S);
ElementType top(Stack S);

// Utility
bool isEmpty(Stack S);
void display(Stack S);

// Internal helper for dynamic resizing
static void resize(Stack *S, int new_capacity) {
    ElementType *temp = realloc(S->data, sizeof(ElementType) * new_capacity);
    if (temp == NULL) {
        printf("CRITICAL ERROR: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    S->data = temp;
    S->capacity = new_capacity;
}

int main(void) {
    Stack S;
    initStack(&S);

    push(&S, 'K');
    push(&S, 'C');
    push(&S, 'U');
    push(&S, 'F');
    push(&S, 'S'); 
    push(&S, 'A'); // Triggers the dynamic resize to capacity 10
    
    printf("--- Stack Contents ---\n");
    display(S);

    printf("\nTop element: %c\n", top(S));
    
    pop(&S);
    printf("Top element after pop: %c\n", top(S));

    freeStack(&S);
    return 0;
}

void initStack(Stack* S) {
    S->top = -1;
    S->capacity = INITIAL_CAPACITY;
    S->data = malloc(sizeof(ElementType) * S->capacity);
    if (S->data == NULL) {
        printf("CRITICAL ERROR: Memory allocation failed during initialization.\n");
        exit(EXIT_FAILURE);
    }
}

void freeStack(Stack *S) {
    free(S->data);
    S->data = NULL;
    S->top = -1;
    S->capacity = 0;
}

void push(Stack* S, ElementType elem) {
    // Resize if stack is full
    if(S->top == S->capacity - 1) {
        resize(S, S->capacity * 2);
    }
    S->data[++S->top] = elem;
}

void pop(Stack* S) {
    if(isEmpty(*S)) {
        printf("ERROR: Stack underflow. Cannot pop from an empty stack.\n");
        return;
    }
    S->top--;

    // Shrink array if it is severly underutilized
    if (S->top > 0 && S->top == (S->capacity / 4) - 1) {
        resize(S, S->capacity / 2);
    }
}

ElementType top(Stack S) {
    if (isEmpty(S)) {
        printf("ERROR: Stack is empty. Returning null character.\n");
        return '\0'; // Safe fallback
    }
    return S.data[S.top];
}

bool isEmpty(Stack S) {
    return S.top == -1;
}

void display(Stack S) {
    if (isEmpty(S)) {
        printf("STACK IS EMPTY\n");
        return;
    }
    for (int i = S.top; i >= 0; i--) {
        printf("[%d] -> %c\n", i, S.data[i]);
    }
    printf("(Count: %d, Capacity: %d)\n", S.top + 1, S.capacity);
}