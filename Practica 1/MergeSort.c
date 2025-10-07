#include <stdlib.h>
#include <stdio.h>
#include "tiempo/tiempo.h"

void MergeSort(int *A, int p, int r);
void Merge(int *A, int p, int q, int r);

int main(int num_args, char *args[])
{
    if (num_args != 2)
        exit(1);

    int n, i, *A;
    double utime0, stime0, wtime0, utime1, stime1, wtime1; // Variables para medición de tiempos

    n = atoi(args[1]);
    A = malloc(sizeof(int) * n);
    if (A == NULL)
    {
        printf("\n[!]-- Error al asignar memoria");
        exit(1);
    }
    for (i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
    }

    // Iniciar el conteo del tiempo para las evaluaciones de rendimiento
    uswtime(&utime0, &stime0, &wtime0);

    // Llamar al algoritmo
    MergeSort(A, 0, n - 1);

    /// Evaluar los tiempos de ejecución
    uswtime(&utime1, &stime1, &wtime1);

    // for (i = 0; i < n; i++)
    // {
    //     printf("%d\n", A[i]);
    // }

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
}

void MergeSort(int *A, int p, int r)
{
    int q;
    if (p < r)
    {
        q = (p + r) / 2;
        MergeSort(A, p, q);
        MergeSort(A, q + 1, r);
        Merge(A, p, q, r);
    }
}

void Merge(int *A, int p, int q, int r)
{
    int i, j, l, k, *C;
    l = r - p + 1;
    i = p;
    j = q + 1;
    C = malloc(l * sizeof(int));
    for (k = 0; k <= (l - 1); k++)
    {
        if (i <= q && j <= r)
        {
            if (A[i] < A[j])
            {
                C[k] = A[i];
                i++;
            }
            else
            {
                C[k] = A[j];
                j++;
            }
        }
        else if (i <= q)
        {
            C[k] = A[i];
            i++;
        }
        else
        {
            C[k] = A[j];
            j++;
        }
    }
    k = p;
    for (i = 0; i <= (l - 1); i++)
    {
        A[k] = C[i];
        k++;
    }
    free(C);
}
