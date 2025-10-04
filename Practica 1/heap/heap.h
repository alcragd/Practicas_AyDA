#include <stdio.h>
#include <stdlib.h>

#define MAX 5000

typedef struct
{
    int A[MAX];
} heap;

void HeapInsert(heap *h);
int HeapPop(heap *h);