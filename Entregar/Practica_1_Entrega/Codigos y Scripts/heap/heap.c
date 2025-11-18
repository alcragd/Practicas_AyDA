/*
Nombre del programa: heap.c
Version: 1.0 Octubre 2025
Autor: Coyol Moreno Angel Zoe

Implementación de las funciones para el manejo de Heap
utilizado en el algoritmo HeapSort.

Compilacion: gcc heap.c -c
*/

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

/*
void HeapInit(heap *h)
Recibe: heap * Referencia/Direccion al heap
Devuelve: void
Observaciones: Funcion que inicializa el heap
*/
void HeapInit(heap *h)
{
    h->i = 0;
}

/*
void HeapDestroy(heap *h)
Recibe: heap * Referencia/Direccion al heap
Devuelve: void
Observaciones: Funcion que destruye el heap
*/
void HeapDestroy(heap *h)
{
    h->i = 0;
}

/*
int HeapTop(heap *h)
Recibe: heap * Referencia/Direccion al heap
Devuelve: void
Observaciones: Funcion que regresa el tope del heap
*/
int HeapTop(heap *h)
{
    if (h->i == 0)
    {
        printf("\n[!]-- ERROR: Heap(h,n): \"Subesbordamiento de heap.\"");
        exit(1);
    }
    return h->A[0];
}

/*
void HeapInsert(heap *h, int num)
Recibe: heap * Referencia/Direccion al heap, int numero a insertar
Devuelve: void
Observaciones: Funcion que inserta un elemento al heap
*/
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

    // Acomoda el elemento insertado y sus padres en el heap
    while (i > 0 && h->A[i] < h->A[padre])
    {

        temp = h->A[i];
        h->A[i] = h->A[padre];
        h->A[padre] = temp;

        i = padre;
        padre = (i - 1) / 2;
    }
}

/*
int HeapPop(heap *h)
Recibe: heap * Referencia/Direccion al heap
Devuelve: int
Observaciones: Funcion que extrae el elemento del tope del heap
*/
int HeapPop(heap *h)
{
    int r, izq, der, i, padre, tmp, menor;

    if (h->i == 0)
    {
        printf("\n[!]-- ERROR: Heap(h,n): \"Subesbordamiento de heap.\"");
        exit(1);
    }

    r = HeapTop(h);
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
