/*
Nombre del programa: HeapSort.c
Version: 1.0 Octubre 2025
Autores: Ramos Mendoza Miguel Angel / Coyol Moreno Angel Zoe / Ramirez Hernandez Christian Isaac

Programa que lee n numeros y los coloca en un arreglo A,
ejecuta el algoritmo HeapSort para ordenarlos de menor a mayor utilizando una estructura heap auxiliar.
Además, mide y muestra los tiempos de ejecución: tiempo real, tiempo de usuario, tiempo de sistema y el porcentaje de uso de CPU.

Compilacion:
gcc HeapSort.c heap/heap.c tiempo/tiempo.c -o HeapSort

Ejecucion:
./HeapSort n < numeros10millones.txt

Dependencias:
- heap/heap.h y heap/heap.c: Implementación de la estructura y funciones de heap.
- tiempo/tiempo.h y tiempo/tiempo.c: Funciones para medición de tiempos de ejecución.

El programa realiza las siguientes acciones:
1. Lee n números desde la entrada estándar y los almacena en un arreglo.
2. Ordena los números usando HeapSort.
3. Mide los tiempos de ejecución (real, usuario, sistema, CPU/Wall).
4. Muestra los resultados de los tiempos en formato decimal y exponencial.
*/

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

    // for (i = 0; i < n; i++)
    //     printf("%d\n", A[i]);

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

/*
void HeapSort(int *A, int n)
Recibe: int * Referencia/Direccion al arreglo A, int tamano del arreglo
Devuelve: void
Observaciones: Funcion que ordena n numeros de menor a mayor por
metodo HeapSort utilizando una estructura heap auxiliar.
*/
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
