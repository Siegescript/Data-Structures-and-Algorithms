#include <stdio.h>
#include <stdbool.h>

#define MAX 10
#define NULL_LINK -1

typedef char ElementType;
typedef int StackPos;

typedef struct node {
    ElementType data;
    StackPos link;
} Node;

typedef struct heap {
    Node elem[MAX];
    StackPos avail;
} Heap;

// Core API
void initHeap(Heap *H);
void initStack(StackPos *S);
void freeStack(Heap *H, StackPos *S);
void push(Heap *H, StackPos *S, ElementType elem);
void pop(Heap *H, StackPos *S);
ElementType top(Heap H, StackPos S);

// Utility
bool isEmpty(StackPos S);
void display(Heap H, StackPos S);

// Internal Memory Helpers
static StackPos allocNode(Heap *H) {
    StackPos ret = H->avail;
    if (ret != NULL_LINK) {
        H->avail = H->elem[ret].link;
        H->elem[ret].link = NULL_LINK;
    }
    return ret;
}

static void deallocNode(Heap *H, StackPos del) {
    if (del < 0 || del >= MAX) return;
    H->elem[del].link = H->avail;
    H->avail = del;
}

int main(void) {
    Heap H;
    StackPos S;

    initHeap(&H);
    initStack(&S);
    
    push(&H, &S, 'K');
    push(&H, &S, 'C');
    push(&H, &S, 'U');
    push(&H, &S, 'F');

    printf("--- Cursor Stack Contents ---\n");
    display(H, S);

    printf("\nTop element: %c\n", top(H, S));
    pop(&H, &S);
    printf("Top element after pop: %c\n", top(H, S));

    freeStack(&H, &S);

    return 0;
}

void initHeap(Heap *H) {
    for (int i = MAX - 1; i >= 0; i--) {
        H->elem[i].link = i - 1;
    }
    H->avail = MAX - 1;
}

void initStack(StackPos *S) {
    *S = NULL_LINK;
}

void freeStack(Heap *H, StackPos *S) {
    while (!isEmpty(*S)) {
        pop(H, S);
    }
}

void push(Heap *H,StackPos *S, ElementType elem) {
    StackPos newNode = allocNode(H);
    if (newNode == NULL_LINK) {
        printf("ERROR: Heap overflow. Virtual heap is full.\n");
        return;
    }
    H->elem[newNode].data=  elem;
    H->elem[newNode].link = *S;
    *S = newNode;
}

void pop(Heap *H, StackPos *S) {
    if (isEmpty(*S)) {
        printf("ERROR: Stack underflow. Cannot pop from an empty stack.\n");
        return;
    }
    StackPos del = *S;
    *S = H->elem[*S].link;
    deallocNode(H, del);
}

ElementType top(Heap H, StackPos S) {
    if (isEmpty(S)) {
        printf("ERROR: Stack is empty. Returning null character.\n");
        return '\0';
    }
    return H.elem[S].data;
}

bool isEmpty(StackPos S) {
    return S == NULL_LINK;
}

void display(Heap H, StackPos S) {
    if (isEmpty(S)) {
        printf("STACK IS EMPTY\n");
        return;
    }
    printf("TOP -> ");
    for (StackPos trav = S; trav != NULL_LINK; trav = H.elem[trav].link) {
        printf("[%c | idx:%d] ", H.elem[trav].data, trav);
    }
    printf("<- BOTTOM\n");
}