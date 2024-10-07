#include <stdio.h>
#include <stdlib.h>

// Time: best - n + k, average - n log(n), worst - n^2
// where d = number of digits, n = number of elements, and b = base of the number system
// Space: n + k
// Stable

// Node structure for each bucket
typedef struct node {
    float value;
    struct node *next;
} *NODE;

// Function to insert elements in sorted order (insertion sort)
void sortedInsert(NODE *head, float value) {
    NODE newNode = (NODE)malloc(sizeof(struct node));
    newNode->value = value;
    newNode->next = NULL;

    if (*head == NULL || (*head)->value >= value) {
        newNode->next = *head;
        *head = newNode;
    } else {
        NODE current = *head;
        while (current->next != NULL && current->next->value < value) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// Bucket sort function
void bucketSort(float arr[], int n) {
    // 1) Create n empty buckets
    NODE buckets[n];

    // Initialize empty buckets
    for (int i = 0; i < n; i++) {
        buckets[i] = NULL;
    }

    // 2) Put array elements into different buckets
    for (int i = 0; i < n; i++) {
        int bi = n * arr[i]; // Index in bucket
        sortedInsert(&buckets[bi], arr[i]);
    }

    // 3) Concatenate all buckets into arr[]
    int index = 0;
    for (int i = 0; i < n; i++) {
        NODE current = buckets[i];
        while (current != NULL) {
            arr[index++] = current->value;
            NODE temp = current;
            current = current->next;
            free(temp); // Free the memory after use
        }
    }
}

// Driver function to test bucket sort
int main() {
    float arr[] = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
    int n = sizeof(arr) / sizeof(arr[0]);

    bucketSort(arr, n);

    printf("Sorted array is:\n");
    for (int i = 0; i < n; i++) {
        printf("%f ", arr[i]);
    }
    printf("\n");

    return 0;
}
