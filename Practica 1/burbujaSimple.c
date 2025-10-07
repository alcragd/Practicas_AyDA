/*
Nombre del programa: burbujaSimple.c
Version: 1.0 Septiembre 2025
Autores: Ramos Mendoza Miguel Angel / Coyol Moreno Angel Zoe / Ramirez Hernandez Christian Isaac

Programa que lee n numeros y los coloca en un arreglo A,
ejecuta un algoritmo que ordena los numeros de menor a mayor por metodo de
burbuja simple

Compilacion: gcc burbujaSimple.c -o burbujaSimple.exe
Ejecucion: .\burbujaSimple.exe n < numeros10millones.txt
*/
#include <stdlib.h>
#include <stdio.h>
#include "tiempo/tiempo.h"

void burbujaSimple(int n, int *A);

int main(int num_args, char *args[])
{
    // Recibe por argumento el valor de la variable n (tamaño del arreglo a ordenar)
    if (num_args != 2)
    {
        exit(1);
    }

    // Variables para el algoritmo
    int n, i, *A;
    double utime0, stime0, wtime0, utime1, stime1, wtime1; // Variables para medición de tiemposs
    // Asigna a n el segundo argumento del main
    n = atoi(args[1]);
    // Apartar memoria para n numeros enteros
    A = malloc(sizeof(int) * n);

    if (A == NULL)
    {
        printf("\n[!]-- Error al asignar memoria");
        exit(1);
    }

    // Lee los n valores del archivo 10mil_numeros.txt y los coloca en el arreglo de numeros
    for (i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
    }

    // Iniciar el conteo del tiempo para las evaluaciones de rendimiento
    uswtime(&utime0, &stime0, &wtime0);

    // Llama al algoritmo
    burbujaSimple(n, A);

    /// Evaluar los tiempos de ejecución
    uswtime(&utime1, &stime1, &wtime1);

    // Impresion del arreglo de numeros ordenados

    for (i = 0; i < n; i++)
    {
        printf("%d ", A[i]);
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
    // Libera la memoria correspondiente al arreglo A
    free(A);
}

/*
void burbujaSimple(int n, int *A)
Recibe: int tamano del arreglo, int * Referencia/Direccion al arreglo A
Devuelve: void
Observaciones: Funcion que ordena n numeros de menor a mayor por
metodo de burbuja simple
*/
void burbujaSimple(int n, int *A)
{
    int i, j, aux;
    /*
    Compara pares de elementos iterando el número de
    elementos que tenemos
    */
    for (i = 0; i <= n - 2; i++)
    {
        for (j = 0; j <= n - 2; j++)
        {
            if (A[j] > A[j + 1])
            {
                aux = A[j];
                A[j] = A[j + 1];
                A[j + 1] = aux;
            }
        }
    }
}