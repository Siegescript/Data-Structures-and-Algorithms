#include<stdio.h>
#include<stdlib.h>

#define SMALL_SIZE 10
#define LARGE_SIZE 1000
#define MAX_ELEMENT_VALUE 999

void generateArray(int*, int, int);
void printArray(int*, int);

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
    int smallArray[SMALL_SIZE];
    int largeArray[LARGE_SIZE];

    return 0;
}

void generateArray(int *arr, int size, int max)
{
    for(int n = 0; n < size; n++)
    {
        arr[n] = rand() % max;
    }
}

void printArray(int *arr, int size)
{
    printf("{");
    for(int n = 0; n < size; n++)
    {
        printf("%d", arr[n]);
        if(n > 0 && n != size)
        {
            printf(", ");
        }
    }
    printf("}");
}