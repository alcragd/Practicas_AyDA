#include <stdlib.h>
#include <stdio.h>
#include "tiempo/tiempo.h"

void Inserccion(int *A, int n);

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

    Inserccion(A, n);

    /// Evaluar los tiempos de ejecución
    uswtime(&utime1, &stime1, &wtime1);

    for (i = 0; i < n; i++)
    {
        printf("%d\n", A[i]);
    }

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

void Inserccion(int *A, int n)
{
    int i, j, temp;
    for (i = 0; i <= n - 1; i++)
    {
        j = i;
        temp = A[i];
        while (j > 0 && temp < A[j - 1])
        {
            A[j] = A[j - 1];
            j--;
        }
        A[j] = temp;
    }
}