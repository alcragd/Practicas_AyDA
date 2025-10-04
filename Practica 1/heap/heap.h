#include <stdio.h>
#include <stdlib.h>

#define MAX 5000

typedef struct
{
    int A[MAX];
    int i;
} heap;

void HeapInit(heap *h);
void HeapInsert(heap *h, int num);
int HeapPop(heap *h);
void HeapDestroy(heap *h);
int HeapTop(heap *h);