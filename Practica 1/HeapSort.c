#include <stdio.h>
#include <stdlib.h>
#include "heap/heap.h"

void HeapSort(int *A, int n);

int main()
{
    int i, n, *A;

    scanf("%d", &n);

    A = malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
        scanf("%d", &A[i]);

    HeapSort(A, n);

    for (i = 0; i < n; i++)
        printf("%d\n", A[i]);

    free(A);
    return 0;
}

void HeapSort(int *A, int n)
{
    int i;
    heap *h;

    h = malloc(sizeof(heap)); // Para evitar stack overflow con tamaños de heap muy grandes
    HeapInit(h);

    for (i = 0; i < n; i++)
        HeapInsert(h, A[i]);

    for (i = 0; i < n; i++)
        A[i] = HeapPop(h);

    HeapDestroy(h);
    return;
}
