/*
Nombre del archivo: heap.h
Version: 1.0 Octubre 2025
Autor: Coyol Moreno Angel Zoe

Definición de estructuras y funciones para el manejo de un MinHeap
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 10000001

typedef struct
{
    int A[MAX];
    int i;
} heap;

void HeapInit(heap *h);            // Recibe un heap y lo Inicializa
void HeapInsert(heap *h, int num); // Recibe un heap, un numero e inserta el numero en el heap
int HeapPop(heap *h);              // Recibe un heap y devuelve el numero que está en el tope
void HeapDestroy(heap *h);         // Recibe un Heap y lo Destruye
int HeapTop(heap *h);              // Recibe un Heap y muestra el numero que está en el tope, sin sacarlo del heap