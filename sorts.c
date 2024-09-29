#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

void swap(int*, int*);
void printArray(int[], int);

void selectionSort(int[], int);

void insertionSort(int[], int);
void shellSort(int[], int);

void quickSort();
int partition();

void mergeSort();
void merge();

void countSort();

void radixSort();
void bucketSort();

void gnomeSort();

void strandSort();

void heapify(int[], int, int);
void heapSort(int[], int);
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

void selectionSort(int arr[], int size)
{
    for(int i = 0, ndx, min; i < size - 1; i++)
    {
        min = i;
        for(ndx = i + 1; ndx < size; ndx++)
        {
            if (arr[ndx] < arr[min])
            {
                min = ndx;
            }
            if(min != i)
            {
                swap(&arr[min], &arr[i]);
            }
        }
    }
}

void insertionSort(int arr[], int size)
{
    for(int i = 1, ndx, key; i < size; i++) 
    { 
        key = arr[i];
        ndx = i - 1;
        for(; ndx >= 0 && arr[ndx] > key; ndx--) {
            arr[ndx + 1] = arr[ndx];
        }
        arr[ndx + 1] = key;
    }
}

void shellSort(int arr[], int size)
{
    for (int gap = size / 2; gap > 0; gap /= 2)
    {
        for (int i = gap, ndx, key; i < size; i++)
        {  
            key = arr[i];
            ndx = i;
            for (; ndx >= gap && arr[ndx - gap] > key; ndx -= gap)
            {
                arr[ndx] = arr[ndx - gap];
            }
            arr[ndx] = key;
        }
    }
}

void heapify(int Heap[], int size, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < size && Heap[left] > Heap[right])
    {
        largest = left;
    }

    if(right < size && Heap[right] > Heap[largest])
    {
        largest = right;
    }    

    if(largest != i) 
    {
        swap(&Heap[i], &Heap[largest]);
        heapify(Heap, size, largest);
    }
}

void tournamentSort(int arr[], int size) 
{
    int tree[2 * size];

    for(int i = 0; i < size; i++) 
    {
        tree[size + i] = arr[i];
    }

    for(int i = size - 1; i > 0; --i) 
    {
        tree[i] = tree[2 * i] > tree[2 * i + 1] ? tree[2 * i] : tree[2 * i + 1];
    }

    for(int i = size - 1, index; i >= 0; --i) 
    {
        arr[i] = tree[1];
        index = 1;

        while(index < size) 
        {
            if(tree[2 * index] == tree[1]) 
            {
                tree[2 * index] = INT_MIN;
                index = 2 * index;
            }
            else
            {
                tree[2 * index + 1] = INT_MIN;
                index = 2 * index + 1;
            }
        }

        for(int j = index / 2; j > 0; j /= 2) 
        {
            tree[j] = tree[2 * j] > tree[2 * j + 1] ? tree[2 * j] : tree[2 * j + 1];
        }
    }
}


void heapSort(int arr[], int size)
{
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        heapify(arr, size, i);
    }
  
    for (int i = size - 1; i >= 0; i--)
    {
      swap(&arr[0], &arr[i]);
      heapify(arr, i, 0);
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