/*
Nombre del programa: TreeSort.c
Version: 1.0 Octubre 2025
Autores: Ramos Mendoza Miguel Angel / Coyol Moreno Angel Zoe / Ramirez Hernandez Christian Isaac

Programa que lee n numeros y los coloca en un arreglo A,
ejecuta el algoritmo TreeSort para ordenarlos de menor a mayor.

Compilacion: gcc TreeSort.c tiempo/tiempo.c -o TreeSort
Ejecucion: ./TreeSort n < numeros10millones.txt
*/

#include <stdio.h>
#include <stdlib.h>
#include "abb/abb.h"
#include "tiempo/tiempo.h"

void TreeSortRecursivo(arbol_bin_busqueda *A, int *array, int *i);
void TreeSort(int *A, int n);

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

    TreeSort(A, n);

    // Evaluar los tiempos de ejecución
    uswtime(&utime1, &stime1, &wtime1);

    // for (i = 0; i < n; i++)
    //     printf("%d\n", A[i]);
    // printf("\n");

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

void TreeSort(int *A, int n)
{
    int i;
    arbol_bin_busqueda tree;
    Initialize_ABB(&tree);

    for (i = 0; i < n; i++)
        Insert_ABB(&tree, A[i]);

    i = 0;
    TreeSortRecursivo(&tree, A, &i);

    Destroy_ABB(&tree);
}

void TreeSortRecursivo(arbol_bin_busqueda *A, int *array, int *i) // Recorrido InOrder
{
    if (*A != NULL)
    {
        TreeSortRecursivo(&((*A)->left), array, i);
        array[(*i)++] = (*A)->num;
        TreeSortRecursivo(&((*A)->right), array, i);
    }
}