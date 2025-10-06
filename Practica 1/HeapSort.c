#include <stdio.h>
#include <stdlib.h>
#include "heap/heap.h"
#include "tiempo/tiempo.h"

void HeapSort(int *A, int n);

int main(int argc, char **argv)
{
    int i, n, *A;
    double utime0, stime0, wtime0, utime1, stime1, wtime1; // Variables para medición de tiempos

    if (argc != 2)
    {
        exit(1);
    }

    n = atoi(argv[1]);

    A = malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
        scanf("%d", &A[i]);

    // Iniciar el conteo del tiempo para las evaluaciones de rendimiento
    uswtime(&utime0, &stime0, &wtime0);

    HeapSort(A, n);

    // Evaluar los tiempos de ejecución
    uswtime(&utime1, &stime1, &wtime1);
    for (i = 0; i < n; i++)
        printf("%d\n", A[i]);

    // Cálculo del tiempo de ejecución del programa
    printf("\n");
    printf("real (Tiempo total)  %.10f s\n", wtime1 - wtime0);
    printf("user (Tiempo de procesamiento en CPU) %.10f s\n", utime1 - utime0);
    printf("sys (Tiempo en acciónes de E/S)  %.10f s\n", stime1 - stime0);
    printf("CPU/Wall   %.10f %% \n", 100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
    printf("\n");

    // Mostrar los tiempos en formato exponecial
    printf("\n");
    printf("real (Tiempo total)  %.10e s\n", wtime1 - wtime0);
    printf("user (Tiempo de procesamiento en CPU) %.10e s\n", utime1 - utime0);
    printf("sys (Tiempo en acciónes de E/S)  %.10e s\n", stime1 - stime0);
    printf("CPU/Wall   %.10f %% \n", 100.0 * (utime1 - utime0 + stime1 - stime0) / (wtime1 - wtime0));
    printf("\n");
    //******************************************************************

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
    free(h);
    return;
}
