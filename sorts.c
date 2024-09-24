#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void swap(int*, int*);
void printArray(int[], int);

void selectionSort();

void insertionSort(int[], int);
void shellSort();

void quickSort();
int partition();

void mergeSort();
void merge();

void countSort();

void radixSort();
void bucketSort();

void gnomeSort();

void strandSort();

void heapify();
void heapSort();
void tournamentSort();

void bubbleSort(int[], int);
void combSort(int[], int);

int main()
{

    return 0;
}

void swap(int *A, int *B)
{
    int tmp = *A;
    *A = *B;
    *B = *A;
}

void printArray(int arr[], int size)
{
    printf("{");
    for(int n = 0; n < size; n++)
    {
        printf("%d", arr[n]);
        if(n > 0 && n < size-1)
        {
            printf(", ");
        }
    }
    printf("}\n\n");
}

void insertionSort(int arr[], int size)
{
    for (int i = 1, ndx = i - 1, key; i < size; i++, ndx--) {
        key = arr[i];
        
        while (ndx >= 0 && arr[ndx] > key) {
            arr[ndx + 1] = arr[ndx];
            ndx = ndx - 1;
        }
        arr[ndx + 1] = key;
    }
}

void bubbleSort(int arr[], int size)
{
    bool swapped = true;

    for(int i = 0; i < size - 1 && swapped; i++)
    {
        swapped = false;
        for(int ndx; ndx < size - i - 1; ndx++)
        {
            if(arr[ndx] > arr[ndx+1])
            {
                swap(&arr[ndx], &arr[ndx + 1]);
                swapped = true; 
            }
        }
    }
}

void combSort(int arr[], int size)
{
    int gap = size;
    bool swapped = true;

    while(gap != 1 || swapped)
    {
        gap = (gap < 1) ? 1 : gap * 10 / 13;
        swapped = false;

        for(int ndx = 0; ndx < size - gap; ndx++)
        {
            if(arr[ndx] > arr[ndx + gap])
            {
                swap(&arr[ndx], &arr[ndx + gap]);
                swapped = true;
            }
        }
    }
}