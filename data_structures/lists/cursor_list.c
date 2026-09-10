#include <stdio.h>
#include <stdbool.h>

#define MAX 10
#define NULL_LINK -1

typedef int ListPos;
typedef char ElementType;

typedef struct node {
    ElementType data;
    ListPos link;
} Node;

typedef struct heap {
    Node elem[MAX];
    ListPos avail;
} Heap;

// Core API
void initHeap(Heap *H);
void initList(ListPos *head);
void insert(Heap *H, ListPos *head, ElementType elem, int ndx);
void delete(Heap *H, ListPos *head, int ndx);

// Wrappers
void insFirst(Heap *H, ListPos *head, ElementType elem);
void insLast(Heap *H, ListPos *head, ElementType elem);
void delFirst(Heap *H, ListPos *head);
void delLast(Heap *H, ListPos *head);
void freeList(Heap *H, ListPos *head);

// Utility
void display(Heap H, ListPos head);

// Internal Memory Management Helpers
static ListPos allocNode(Heap *H) {
    ListPos ret = H->avail;
    if (ret != NULL_LINK) {
        H->avail = H->elem[ret].link;
        H->elem[ret].link = NULL_LINK;
    }
    return ret;
}

static void deallocNode(Heap *H, ListPos del) {
    H->elem[del].link = H->avail;
    H->avail = del;
}

int main(void) {
    Heap H;
    ListPos head;
    
    initHeap(&H);
    initList(&head);

    insLast(&H, &head, 'U');
    insLast(&H, &head, 'K');
    insFirst(&H, &head, 'F');
    insert(&H, &head, 'C', 2);

    printf("--- Cursor List Initial ---\n");
    display(H, head);

    delete(&H, &head, 2); // Delete index 2 ('C')

    printf("\n--- After Deleting Index 2 ---\n");
    display(H, head);

    freeList(&H, &head);
    return 0;
}

void initHeap(Heap *H) {
    for (int i = MAX - 1; i >= 0; i--) {
        H->elem[i].link = i - 1;
    }
    H->avail = MAX - 1;
}

void initList(ListPos *head) {
    *head = NULL_LINK;
}

void freeList(Heap *H, ListPos *head) {
    while (*head != NULL_LINK) {
        delFirst(H, head);
    }
}

void insert(Heap *H, ListPos *head, ElementType elem, int ndx) {
    if (ndx < 0) return;

    ListPos newNode = allocNode(H);
    if (newNode == NULL_LINK) {
        printf("ERROR: Heap overflow (Cursor list is full).\n");
        return;
    }
    H->elem[newNode].data = elem;

    if (ndx == 0) {
        H->elem[newNode].link = *head;
        *head = newNode;
        return;
    }

    ListPos trav = *head;
    int ctr = 0;
    while (trav != NULL_LINK && ctr < ndx - 1) {
        trav = H->elem[trav].link;
        ctr++;
    }

    if (trav == NULL_LINK) {
        printf("Error: Index out of bounds.\n");
        deallocNode(H, newNode);
        return;
    }

    H->elem[newNode].link = H->elem[trav].link;
    H->elem[trav].link = newNode;
}

void delete(Heap *H, ListPos *head, int ndx) {
    if (*head == NULL_LINK || ndx < 0) {
        printf("ERROR: List is empty or index invalid.\n");
        return;
    }

    ListPos delNode = NULL_LINK;

    if (ndx == 0) {
        delNode = *head;
        *head = H->elem[delNode].link;
    } else {
        ListPos trav = *head;
        int ctr = 0;
        while (trav != NULL_LINK && ctr < ndx - 1) {
            trav = H->elem[trav].link;
            ctr++;
        }

        if (trav == NULL_LINK || H->elem[trav].link == NULL_LINK) {
            printf("ERROR: Index out of bounds.\n");
            return;
        }

        delNode = H->elem[trav].link;
        H->elem[trav].link = H->elem[delNode].link;
    }

    deallocNode(H, delNode);
}

void insFirst(Heap *H, ListPos *head, ElementType elem) {
    insert(H, head, elem, 0);
}

void insLast(Heap *H, ListPos *head, ElementType elem) {
    ListPos newNode = allocNode(H);
    if (newNode == NULL_LINK) {
        printf("ERROR: Heap overflow.\n");
        return;
    }
    H->elem[newNode].data = elem;
    H->elem[newNode].link = NULL_LINK;

    if (*head == NULL_LINK) {
        *head = newNode;
    } else {
        ListPos trav = *head;
        while (H->elem[trav].link != NULL_LINK) {
            trav = H->elem[trav].link;
        }
        H->elem[trav].link = newNode;
    }
}

void delFirst(Heap *H, ListPos *head) {
    delete(H, head, 0);
}

void delLast(Heap *H, ListPos *head) {
    if (*head == NULL_LINK) return;

    if (H->elem[*head].link == NULL_LINK) {
        deallocNode(H, *head);
        *head = NULL_LINK;
        return;
    }

    ListPos trav = *head;
    while (H->elem[H->elem[trav].link].link != NULL_LINK) {
        trav = H->elem[trav].link;
    }

    deallocNode(H, H->elem[trav].link);
    H->elem[trav].link = NULL_LINK;
}

void display(Heap H, ListPos head) {
    if (head == NULL_LINK) {
        printf("LIST IS EMPTY\n");
        return;
    }
    for (ListPos trav = head; trav != NULL_LINK; trav = H.elem[trav].link) {
        printf("%c | idx:%d (link:%d)", H.elem[trav].data, trav, H.elem[trav].link);
        if (H.elem[trav].link != NULL_LINK) {
            printf(" --> ");
        }
    }
    printf("\n");
}