#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

void bubbleSort(int[],int);
void combSort(int[], int);

int main()
{

    return 0;
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

void bubbleSort(int arr[], int size)
{
    int tmp;
    bool swapped = true;

    for(int i = 0; i < size - 1 && swapped; i++)
    {
        swapped = false;
        for(int ndx; ndx < size - i - 1; ndx++)
        {
            if(arr[ndx] > arr[ndx+1])
            {
                tmp = arr[ndx];
                arr[ndx] = arr[ndx + 1];
                arr[ndx + 1] = tmp;
                swapped = true; 
            }
        }
    }
}

void combSort(int arr[], int size)
{
    int tmp;
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
                tmp = arr[ndx];
                arr[ndx] = arr[ndx + gap];
                arr[ndx + gap] = tmp;
                swapped = true;
            }
        }
    }
}