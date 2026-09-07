#include<stdio.h>
#define SIZE 10

typedef struct heap
{
    int elem[SIZE];
    int last;
}HEAP;

void initHEAP(HEAP* H);
void sort(HEAP* H);
void heapify(HEAP* H);
void insert(HEAP* H);
int deleteMIN(HEAP* H);
int deleteMAX(HEAP* H);
