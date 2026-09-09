#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define INITIAL_CAPACITY 5

// Typedef makes swapping 'char' for complex structs easier
typedef char ElementType;

typedef struct {
    ElementType *elem;
    int count;
    int capacity;
} ArrayList;

// Core API
void initArr(ArrayList *LIST);
void freeArr(ArrayList *LIST);
void insert(ArrayList *LIST, ElementType elem, int ndx);
void delete(ArrayList *LIST, int ndx);

// Wrappers
void insFirst(ArrayList *LIST, ElementType elem);
void insLast(ArrayList *LIST, ElementType elem);
void delFirst(ArrayList *LIST);
void delLast(ArrayList *LIST);

// Utility
bool getElem(ArrayList LIST, int ndx, ElementType *outElem);
void setElem(ArrayList *LIST, int ndx, ElementType elem);
int indexOf(ArrayList LIST, ElementType elem);
bool isEmpty(ArrayList LIST);
void display(ArrayList LIST);

// Internal helper
static void resize(ArrayList *LIST, int new_capacity) {
    ElementType *temp = realloc(LIST->elem, sizeof(ElementType) * new_capacity);
    if (temp == NULL) {
        printf("CRITICAL ERROR: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    LIST->elem = temp;
    LIST->capacity = new_capacity;
}

int main() {
    ArrayList array;

    initArr(&array);
    
    insLast(&array,'K');
    insFirst(&array,'U');
    insert(&array,'C',1);
    insFirst(&array,'F');
    insLast(&array, 'S'); // Will trigger a resize to accomodate more elements

    printf("--- After Insertions ---\n");
    display(array);

    delete(&array,2);

    printf("\n--- After Deleting Index 2 ---\n");
    display(array);

    printf("\nIndex of 'S': %d\n", indexOf(array, 'S'));

    freeArr(&array); // Clean up memory before exiting
    return 0;
}

void initArr(ArrayList* LIST) {
    LIST->count = 0;
    LIST->capacity = INITIAL_CAPACITY;
    LIST->elem = malloc(sizeof(ElementType) * LIST->capacity);
    if (LIST->elem == NULL) {
        printf("CRITICAL ERROR: Memory allocation failed during initialization.\n");
        exit(EXIT_FAILURE);
    }
}

void freeArr(ArrayList *LIST) {
    free(LIST->elem);
    LIST->elem = NULL;
    LIST->count = 0;
    LIST->capacity = 0;
} 

void insert(ArrayList *LIST, ElementType elem, int ndx) {
    if (ndx < 0 || ndx > LIST->count) {
        printf("ERROR: Index %d out of bounds for insertion.\n", ndx);
        return;
    }

    if (LIST->count == LIST->capacity) {
        resize(LIST, LIST->capacity * 2);
    }

    // Shift elements to the right
    if (ndx < LIST->count) {
        memmove(&(LIST->elem[ndx + 1]), &(LIST->elem[ndx]), sizeof(ElementType) * (LIST->count - ndx));
    }

    LIST->elem[ndx] = elem;
    LIST->count++;
}

void delete(ArrayList *LIST, int ndx) {
    if (isEmpty(*LIST)) {
        printf("ERROR: Cannot delete from an empty list.\n");
        return;
    }
    if (ndx < 0 || ndx >= LIST->count) {
        printf("ERROR: Index %d out of bounds for deletion.\n", ndx);
        return;
    }

    // Shift elements to the left
    if (ndx < LIST->count - 1) {
        memmove(&(LIST->elem[ndx]), &(LIST->elem[ndx + 1]), sizeof(ElementType) * (LIST->count - ndx - 1));
    }

    LIST->count--;

    // Shrink array if it is severely underutilized to save memory
    if (LIST->count > 0 && LIST->count == LIST->capacity / 4) {
        resize(LIST, LIST->capacity / 2);
    }
}

void insFirst(ArrayList *LIST, ElementType elem) {
    insert(LIST, elem, 0);
}

void insLast(ArrayList *LIST, ElementType elem) {
    insert(LIST, elem, LIST->count);
}

void delFirst(ArrayList *LIST) {
    delete(LIST, 0);
}

void delLast(ArrayList *LIST) {
    delete(LIST, LIST->count);
}

bool getElem(ArrayList LIST, int ndx, ElementType *outElem) {
    if (ndx < 0 || ndx >= LIST.count) {
        return false; // Out of bounds
    }
    *outElem = LIST.elem[ndx];
    return true; 
}

void setElem(ArrayList *LIST, int ndx, ElementType elem) {
    if (ndx >= 0 && ndx < LIST->count) {
        LIST->elem[ndx] = elem;
    } else {
        printf("ERROR: Index out of bounds for setting element.\n");
    }
}

int indexOf(ArrayList LIST, ElementType elem) {
    for (int i = 0; i < LIST.count; i++) {
        if (LIST.elem[i] == elem) {
            return i;
        }
    }
    return -1; // Not found
}

bool isEmpty(ArrayList LIST) {
    return LIST.count == 0;
}

void display(ArrayList LIST) {
    if (isEmpty(LIST)) {
        printf("LIST IS EMPTY\n");
        return;
    }
    for (int i = 0; i < LIST.count; i++) {
        printf("[%d] -> %c\n", i, LIST.elem[i]);
    }
    printf("(Count: %d, Capacity: %d)\n", LIST.count, LIST.capacity);
}