#include <stdlib.h>
#include <stdio.h>
#include "tiempo/tiempo.h"

void QuickSort(int *A, int p, int r);
int Pivot(int *A, int p, int r);
void Intercambiar(int *A, int i, int j);

int main(int num_args, char *args[])
{
    if (num_args != 2)
        exit(1);

    double utime0, stime0, wtime0, utime1, stime1, wtime1; // Variables para medición de tiempos
    int n, i, *A;
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

    // for(i=0;i<n;i++){
    //     printf("%d\n",A[i]);
    // }

    // Iniciar el conteo del tiempo para las evaluaciones de rendimiento
    uswtime(&utime0, &stime0, &wtime0);

    QuickSort(A, 0, n - 1);

    /// Evaluar los tiempos de ejecución
    uswtime(&utime1, &stime1, &wtime1);

    printf("==== NUMEROS ORDENADOs: ====\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\n", A[i]);
    }
    free(A);
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
}

void QuickSort(int *A, int p, int r)
{
    int j;
    if (p < r)
    {
        j = Pivot(A, p, r);
        QuickSort(A, p, j - 1);
        QuickSort(A, j + 1, r);
    }
}
int Pivot(int *A, int p, int r)
{
    int i, j, piv;
    piv = A[p];
    i = p + 1;
    j = r;

    while (i < j)
    {
        while (A[i] <= piv && i < r)
            i++;
        while (A[j] > piv)
            j--;
        if (i < j)
            Intercambiar(A, i, j);
    }
    Intercambiar(A, p, j);
    return j;
}
void Intercambiar(int *A, int i, int j)
{
    int temp;
    temp = A[j];
    A[j] = A[i];
    A[i] = temp;
}
