#include "tiempo/tiempo.h"
/*
Nombre del programa: busqueda_binaria.c
Version: 1.0 Noviembre 2025
Autores: Ramos Mendoza Miguel Angel / Coyol Moreno Angel Zoe / Ramirez Hernandez Christian Isaac

Programa que lee n numeros y los coloca en un arreglo A,
ejecuta un algoritmo que busca un numero v por metodo de
busqueda binaria

Compilacion: gcc busqueda_binaria.c tiempo/tiempo.c -o busqueda_binaria
Ejecucion: ./busqueda_binaria n < numeros10millones.txt
*/
#include <stdio.h>
#include <stdlib.h>
#include "tiempo/tiempo.h"
int binarySearch(int *A,int n,int v);

int main(int argc,char **argv)
{
    // Recibe por argumento el valor de la variable n (tamaño del arreglo a ordenar)
    if(argc!=2)
        exit(1);

    // Variables para el algoritmo
    int n, *A, res, val;
    
    double utime0, stime0, wtime0, utime1, stime1, wtime1; // Variables para medición de tiempos
    // Asigna a n el segundo argumento del main
    n=atoi(argv[1]);
    
    // Apartar memoria para n numeros enteros
    A=malloc(n*sizeof(int));

    if (A == NULL)
    {
        printf("\n[!]-- Error al asignar memoria");
        exit(1);
    }

    // Lee el valor a buscar en el archivo
    scanf("%d",&val);
    // Lee los n valores del archivo 10mil_numeros.txt y los coloca en el arreglo de numeros
    
    for(int i=0;i<n;++i)
        scanf("%d",&A[i]);

    // Iniciar el conteo del tiempo para las evaluaciones de rendimiento
    uswtime(&utime0, &stime0, &wtime0);

    // Llama al algoritmo
    res=binarySearch(A,n,val);

    /// Evaluar los tiempos de ejecución
    uswtime(&utime1, &stime1, &wtime1);

    printf("\n%d",res);
    printf("\n%.10e",wtime1 - wtime0);
    // Libera la memoria correspondiente al arreglo A
    free(A);
}

/*
int binarySearch(int *A,int n,int v)
Recibe: int * Referencia/Direccion al arreglo A, int tamano del arreglo,
int valor a buscar en el archivo
Devuelve: int posicion donde se encuentra el valor en el arreglo
Observaciones: Funcion que busca un valor en un arreglo por
metodo de busqueda binaria
*/
int binarySearch(int *A,int n,int v){
    int l,r,m;
    l=0; r=n-1;

    while(l<=r){
        m=(r+l)/2;
        if(A[m]==v)
         return m;
        
        A[m] > v ? (r = m - 1) : (l = m + 1);
    }
    // Retornar -1 si no se encontro el valor
    return - 1;
}
