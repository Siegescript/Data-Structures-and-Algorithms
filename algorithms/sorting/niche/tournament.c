#include<stdio.h>
#include <limits.h>

// Time: best - n log(n), average - n log(n), worst - n log(n)
// Space: n
// Unstable
void tournamentSort(int[], int);
void createTree(int[], int[], int, int*);
void recreate(int[], int, int*);
int winner(int, int, int[], int);

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

    printArray(small_array, size_small);
    printf("\n");
    tournamentSort(small_array, size_small);
    printArray(small_array, size_small);

    return 0;
}

void tournamentSort(int arr[], int size) 
{
    int tmp[2 * size];
    int value;

    createTree(arr, tmp, size, &value);

    for(int i = 0; i < size; i++) 
    {
        arr[i] = value;
        recreate(tmp, size, &value);
    }
}


void createTree(int arr[], int tmp[], int size, int *value) 
{
    for(int i = 0; i < size; i++)
    {
        tmp[size + i] = arr[i];
    }

    for(int i = 2 * size - 1; i > 1; i -= 2) 
    {
        int k = i / 2;
        int j = i - 1;
        tmp[k] = winner(i, j, tmp, size);
    }

    *value = tmp[tmp[1]];
    tmp[tmp[1]] = INT_MAX;
}

void recreate(int tmp[], int size, int *value) 
{
    int i = tmp[1];

    while(i > 1) 
    {
        int j, k = i / 2;
        if(i % 2 == 0 && i < 2 * size - 1)
        {
            j = i + 1;
        }else
        {
            j = i - 1;
        }

        tmp[k] = winner(i, j, tmp, size);
        i = k;
    }

    *value = tmp[tmp[1]];
    tmp[tmp[1]] = INT_MAX;
}

int winner(int pos1, int pos2, int tmp[], int size) 
{
    int u = pos1 >= size ? pos1 : tmp[pos1]; 
    int v = pos2 >= size ? pos2 : tmp[pos2];

    return (tmp[u] <= tmp[v]) ? u : v;
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