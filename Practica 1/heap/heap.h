// Coyol Moreno Angel Zoe 2025
// Implementación de un MinHeap en C

#include <stdio.h>
#include <stdlib.h>

#define MAX 5000

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