#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef char ElementType;

typedef struct node {
    ElementType data;
    struct node *link;
} Node, *NodeList;

// Core API
void initList(NodeList *head);
void freeList(NodeList *head);
void insert(NodeList *head, ElementType elem, int ndx);
void delete(NodeList *head, int ndx);

// Wrappers
void insFirst(NodeList *head, ElementType elem);
void insLast(NodeList *head, ElementType elem);
void delFirst(NodeList *head);
void delLast(NodeList *head);

// Utility
bool isEmpty(NodeList head);
int indexOf(NodeList head, ElementType elem);
void display(NodeList head);

// Internal helper for node allocation
static NodeList createNode(ElementType elem) {
    NodeList newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("CRITICAL ERROR: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = elem;
    newNode->link = NULL;
    return newNode;
}

int main(void) {
    NodeList head;

    initList(&head);

    insLast(&head, 'U');
    insLast(&head, 'K');
    insFirst(&head, 'F');
    insert(&head, 'C', 2);

    printf("--- Initial List ---\n");
    display(head);

    delete(&head, 2); // Delete 'C' (index 2)

    printf("\n--- After Deleting Index 2 ---\n");
    display(head);

    freeList(&head);

    return 0;
}

void initList(NodeList *head) {
    *head = NULL;
}

void freeList(NodeList *head) {
    NodeList current = *head;
    while (current != NULL) {
        NodeList nextNode = current->link;
        free(current);
        current = nextNode;
    }
    *head = NULL;
}

void insert(NodeList *head, ElementType elem, int ndx) {
    if (ndx < 0) {
        printf("ERROR: Invalid index.\n");
        return;
    }

    NodeList *trav = head;
    int ctr = 0;

    // Traverse using pointer2pointer until target index or end of list
    while(*trav != NULL && ctr < ndx) {
        trav = &((*trav)->link);
        ctr++;
    }

    if (ctr < ndx) {
        printf("ERROR: index out of bounds.\n");
        return;
    }

    NodeList newNode = createNode(elem);
    newNode->link = *trav;
    *trav = newNode;
}

void delete(NodeList *head, int ndx) {
    if (isEmpty(*head)) {
        printf("ERROR: Cannot delete from an empty list.\n");
        return;
    }
    if (ndx < 0) {
        printf("ERROR: Indalid index.\n");
        return;
    }

    NodeList *trav = head;
    int ctr = 0;

    while (*trav != NULL && ctr < ndx) {
        trav = &((*trav)->link);
        ctr++;
    }

    if (*trav == NULL) {
        printf("ERROR: Index out of bounds.\n");
        return;
    }

    NodeList temp = *trav;
    *trav = temp->link;
    free(temp);
}

void insFirst(NodeList *head, ElementType elem) {
    insert(head, elem, 0);
}

void insLast(NodeList *head, ElementType elem) {
    NodeList *trav = head;
    while (*trav != NULL) {
        trav = &((*trav)->link);
    }
    *trav = createNode(elem);
}

void delFirst(NodeList *head) {
    delete(head, 0);
}

void delLast(NodeList *head) {
    if (isEmpty(*head)) return;

    NodeList *trav = head;
    while ((*trav)->link != NULL) {
        trav = &((*trav)->link);
    }
    free(*trav);
    *trav = NULL;
}

bool isEmpty(NodeList head) {
    return head == NULL;
}

int indexOf(NodeList head, ElementType elem) {
    int index = 0;
    for (NodeList trav = head; trav != NULL; trav = trav->link, index++) {
        if (trav->data == elem) {
            return index;
        }
    }
    return -1;
}

void display(NodeList head) {
    if (isEmpty(head)) {
        printf("LIST IS EMPTY\n");
        return;
    }
    for (NodeList trav = head; trav != NULL; trav = trav->link) {
        printf("%c", trav->data);
        if (trav->link != NULL) {
            printf(" --> ");
        }
    }
    printf("\n");
}