#include<stdio.h>

// Time: best - n log(n), average - n log(n), worst - n^2
// Space: log(n) or n
// No
void quickSort(int[], int, int);
int partitionLomuto(int[], int, int);
int partitionHoare(int[], int, int);

void swap(int*, int*);
void printArray(int[], int);

int main()
{
    int small_array[] = {12, 16, 20, 16, 11, 16, 5, 11, 1, 13};
    int large_array[] = {
        77, 97, 38, 82, 78, 47, 3, 82, 56, 80,
        24, 15, 100, 25, 92, 20, 43, 23, 87, 65,
        96, 55, 94, 85, 53, 5, 99, 29, 69, 12,
        41, 3, 45, 53, 90, 11, 59, 7, 13, 70,
        23, 26, 10, 79, 72, 26, 59, 79, 22, 87,
        84, 44, 23, 13, 15, 61, 37, 1, 34, 27,
        6, 52, 71, 53, 40, 58, 66, 70, 23, 68,
        14, 14, 98, 25, 91, 82, 7, 41, 84, 28,
        77, 72, 91, 45, 46, 2, 80, 41, 94, 60,
        33, 70, 26, 95, 30, 74, 8, 94, 50, 74
    };

    int size_small = sizeof(small_array) / sizeof(small_array[0]);
    int size_large = sizeof(large_array) / sizeof(large_array[0]);

    printArray(large_array, size_large);
    printf("\n");
    quickSort(large_array, 0, size_large - 1);
    printArray(large_array, size_large);

    return 0;
}

void quickSort(int arr[], int start, int end)
{
    int pivot;

    if(start < end)
    {
        // pivot = partitionLomuto(arr, start, end);
        pivot = partitionHoare(arr, start, end); 
        quickSort(arr, start, pivot);
        // quickSort(arr, start, pivot - 1);
        quickSort(arr, pivot + 1, end);
    }
}

int partitionLomuto(int arr[], int start, int end)
{
    int pivot = arr[end];
    int i = start - 1;

    for(int j = start; j <= end - 1; j++)
    {
        if(arr[j] < pivot)
        {
            swap(&arr[++i], &arr[j]);
        }
    }
    i++;
    swap(&arr[i], &arr[end]);

    return i;
}

int partitionHoare(int arr[], int start, int end)
{
    int pivot = arr[start];
    int i = start - 1, j = end + 1;

    while(1)
    {
        do 
        {
            i++;
        } 
        while(arr[i] < pivot);

        do 
        {
            j--;
        } 
        while(arr[j] > pivot);

        if(i >= j)
        {
            return j;
        }

        swap(&arr[i], &arr[j]);
    }
}

void swap(int *A, int *B)
{
    int tmp = *A;
    *A = *B;
    *B = tmp;
}

void printArray(int arr[], int size)
{
    printf("{");
    for(int n = 0; n < size; n++)
    {
        printf("%d", arr[n]);
        if(n < size-1)
        {
            printf(", ");
        }
    }
    printf("}\n");
}