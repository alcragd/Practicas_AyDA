/*
shell.c
V 1.0 Marzo 2025
Autor: Ramirez Hernandez Christian Isaac

Programa que lee n n�meros desde la entrada est�ndar, los almacena en un arreglo din�mico,
aplica el algoritmo de ordenamiento Shell Sort y mide el tiempo de ejecuci�n.

Compilaci�n:
Windows: gcc shell.c -o shell.exe
Linux: gcc shell.c -o shell
*/

#include <stdio.h>
#include <stdlib.h>
#include "tiempo/tiempo.h"

// Prototipo de la funci�n de ordenamiento Shell Sort
void shell(int *A, int n);

int main(int num_args, char *args[])
{

    int n, *A, i;
    double utime0, stime0, wtime0, utime1, stime1, wtime1; // Variables para medición de tiempos

    // Verificaci�n de argumentos
    if (num_args != 2)
    {
        exit(1);
    }

    // Convertir argumento a entero
    n = atoi(args[1]);

    // Reservar memoria din�micamente
    A = malloc(n * sizeof(int));
    if (A == NULL)
    {
        printf("\n[!]-- Error al asignar memoria\n");
        exit(1);
    }

    // Leer los valores del arreglo
    for (i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
    }

    // Iniciar el conteo del tiempo para las evaluaciones de rendimiento
    uswtime(&utime0, &stime0, &wtime0);

    shell(A, n);

    // Evaluar los tiempos de ejecución
    uswtime(&utime1, &stime1, &wtime1);

    // Imprimir el arreglo ordenado
    printf("\nArreglo ordenado:\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\n", A[i]);
    }

    // Liberar memoria y mostrar tiempo de ejecuci�n

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
void shell(int *A, int n)
Recibe: int * Referencia al arreglo A, int tama�o del arreglo
Devuelve: void (No retorna valor expl�cito)
Observaciones: Ordena el arreglo usando el algoritmo Shell Sort.
*/
void shell(int *A, int n)
{
    int k = n / 2, b, i, temp;
    while (k >= 1)
    {
        b = 1;
        while (b != 0)
        {
            b = 0;
            for (i = k; i <= n - 1; i++)
            {
                if (A[i - k] > A[i])
                {
                    temp = A[i];
                    A[i] = A[i - k];
                    A[i - k] = temp;
                    b++;
                }
            }
        }
        k = k / 2;
    }
}
