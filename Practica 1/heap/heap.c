#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

void HeapInit(heap *h)
{
    h->i = 0;
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
    int r, izq, der, i, padre, tmp;

    if (h->i == 0)
    {
        printf("\n[!]-- ERROR: Heap(h,n): \"Subesbordamiento de heap.\"");
        exit(1);
    }

    r = h->A[0];
    i = --h->i;

    padre = 0;

    while (1)
    {
        izq = 2 * padre + 1;
        der = 2 * padre + 2;

        tmp = h->A[padre];

        if (izq < i && h->A[padre] > h->A[izq])
        {
            h->A[padre] = h->A[izq];
            h->A[izq] = tmp;
            padre = izq;
        }
        else if (der < i && h->A[padre] > h->A[der])
        {
            h->A[padre] = h->A[der];
            h->A[der] = tmp;
            padre = der;
        }
        else
            break;
    }

    return r;
}
