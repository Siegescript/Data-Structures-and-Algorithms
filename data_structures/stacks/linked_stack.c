#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef char ElementType;

typedef struct node {
    ElementType data;
    struct node *link;
} Node, *Stack;

// Core API
void initStack(Stack *S);
void freeStack(Stack *S);
void push(Stack* S, ElementType elem);
void pop(Stack *S);
ElementType top(Stack S);

// Utility
bool isEmpty(Stack S);
void display(Stack S);

// Internal helper for node allocation
static Stack createNode(ElementType elem) {
    Stack newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("CRITICAL ERROR: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = elem;
    newNode->link = NULL;
    return newNode;
}

int main(void) {
    Stack S;
    initStack(&S);
    
    push(&S, 'K');
    push(&S, 'C');
    push(&S, 'U');
    push(&S, 'F');

    printf("--- Stack Contents ---\n");
    display(S);

    printf("\nTop element: %c\n", top(S));
    
    pop(&S);
    printf("Top element after pop: %c\n", top(S));

    freeStack(&S);
    return 0;
}

void initStack(Stack* S) {
    *S = NULL;
}

void freeStack(Stack* S) {
    Stack current = *S;
    while (current != NULL) {
        Stack nextNode = current->link;
        free(current);
        current = nextNode;
    }
    *S = NULL;
}

void push(Stack* S,char elem) {
    Stack newNode = createNode(elem);
    newNode->link = *S;
    *S = newNode;
}

void pop(Stack* S) {
    if (isEmpty(*S)) {
        printf("ERROR: Stack underflow. Cannot pop from an empty stack.\n");
        return;
    }
    Stack del = *S;
    *S = (*S)->link;
    free(del);
}

bool isEmpty(Stack S) {
    return S == NULL;
}

ElementType top(Stack S) {
    if (isEmpty(S)) {
        printf("ERROR: Stack is empty. Returning null character.\n");
        return '\0'; // Safe fallback
    }
    return S->data;
}

void display(Stack S) {
    if (isEmpty(S)) {
        printf("STACK IS EMPTY\n");
        return;
    }
    
    printf("TOP -> ");
    for (Stack trav = S; trav != NULL; trav = trav->link) {
        printf("[%c] ", trav->data);
    }
    printf("<- BOTTOM\n");
}