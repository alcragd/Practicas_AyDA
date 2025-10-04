// Coyol Moreno Angel Zoe 2025
// Implementación de un MinHeap en C

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

void HeapInit(heap *h)
{
    h->i = 0;
}

void HeapDestroy(heap *h)
{
    h->i = 0;
}

int HeapTop(heap *h)
{
    if (h->i == 0)
    {
        printf("\n[!]-- ERROR: Heap(h,n): \"Subesbordamiento de heap.\"");
        exit(1);
    }
    return h->A[0];
}

void HeapInsert(heap *h, int num)
{
    int padre, temp, i;

    if (h->i == MAX - 1)
    {
        printf("\n[!]-- ERROR: Heap(h,n): \"Desbordamiento de heap.\"");
        exit(1);
    }

    h->A[h->i] = num;
    i = h->i;
    h->i++;

    padre = (i - 1) / 2;

    while (i > 0 && h->A[i] < h->A[padre])
    {

        temp = h->A[i];
        h->A[i] = h->A[padre];
        h->A[padre] = temp;

        i = padre;
        padre = (i - 1) / 2;
    }
}

int HeapPop(heap *h)
{
    int r, izq, der, i, padre, tmp, menor;

    if (h->i == 0)
    {
        printf("\n[!]-- ERROR: Heap(h,n): \"Subesbordamiento de heap.\"");
        exit(1);
    }

    r = h->A[0];
    h->i--;
    h->A[0] = h->A[h->i];

    padre = 0;

    while (1)
    {
        izq = 2 * padre + 1;
        der = 2 * padre + 2;
        menor = padre;

        if (izq < h->i && h->A[izq] < h->A[menor])
            menor = izq;
        if (der < h->i && h->A[der] < h->A[menor])
            menor = der;

        if (h->A[padre] > h->A[menor])
        {
            tmp = h->A[padre];
            h->A[padre] = h->A[menor];
            h->A[menor] = tmp;
        }
        else
            break;

        padre = menor;
    }

    return r;
}
