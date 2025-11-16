/*
Nombre del programa: busqueda_Lineal.c
Version: 1.0 Noviembre 2025
Autores: Ramos Mendoza Miguel Angel / Coyol Moreno Angel Zoe / Ramirez Hernandez Christian Isaac

Programa que lee n numeros y los coloca en un arreglo A,
ejecuta un algoritmo que busca un numero v por metodo de
busqueda lineal

Compilacion: gcc busqueda_Lineal.c tiempo/tiempo.c -o busqueda_Lineal
Ejecucion: ./busqueda_Lineal n < numeros10millones.txt
*/
#include <stdio.h>
#include <stdlib.h>

int linearSearch(int *A,int n,int v);

int main(int argc,char **argv){
    if(argc!=2)
        exit(1);

    int n, *A, res, val;
    n=atoi(argv[1]);
    A=malloc(n*sizeof(int));

    scanf("%d",&val);

    for(int i=0;i<n;++i)
        scanf("%d",&A[i]);

    res=linearSearch(A,n,val);

    printf("\n%d",res);

    free(A);

    return 0;
}

int main(int num_args, char *args[])
{
    // Recibe por argumento el valor de la variable n (tamaño del arreglo a ordenar)
    if (num_args != 2)
    {
        exit(1);
    }

    // Variables para el algoritmo
    int n, i, *A;
    double utime0, stime0, wtime0, utime1, stime1, wtime1; // Variables para medición de tiempos
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

    // for (i = 0; i < n; i++)
    // {
    //     printf("%d ", A[i]);
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
    // Libera la memoria correspondiente al arreglo A
    free(A);
}

int linearSearch(int *A,int n,int v){
    for(int i=0;i<n;++i)
        if(A[i]==v)
            return i;
    return -1;
}

