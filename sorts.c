#include <stdio.h>
#include <stdlib.h>

void printArray(int[], int);

void selectionSort();

void insertionSort();
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

void bubbleSort();
void combSort();

int main()
{

    return 0;
}

void printArray(int *arr, int size)
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