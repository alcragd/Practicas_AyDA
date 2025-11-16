
/*
Nombre del programa: busqueda_fibonacci.c
Version: 1.0 Noviembre 2025
Autores: Ramos Mendoza Miguel Angel / Coyol Moreno Angel Zoe / Ramirez Hernandez Christian Isaac

Programa que lee n numeros y los coloca en un arreglo A,
ejecuta un algoritmo que busca un numero v por metodo de
busqueda de fibonacci

Compilacion: gcc busqueda_fibonacci.c tiempo/tiempo.c -o busqueda_fibonacci
Ejecucion: ./busqueda_fibonacci n < numeros10millones.txt
*/
#include <stdio.h>
#include <stdlib.h>
#include "tiempo/tiempo.h"
int fiboSearch(int *A,int n,int v);
int binarySearch(int *A,int l,int r,int v);

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
    res=fiboSearch(A,n,val);

    /// Evaluar los tiempos de ejecución
    uswtime(&utime1, &stime1, &wtime1);

    printf("\n%d",res);
    printf("\n%.10e",wtime1 - wtime0);
    // Libera la memoria correspondiente al arreglo A
    free(A);
}

/*
int fiboSearch(int *A,int n,int v)
Recibe: int * Referencia/Direccion al arreglo A, int tamaño
del arreglo, int valor a buscar en el archivo
Devuelve: int posicion donde se encuentra el valor en el arreglo
Observaciones: Funcion que busca un valor en un arreglo por
metodo de busqueda de fibonacci
*/
int fiboSearch(int *A,int n,int v){
    int a = 0, b = 1, c = 1, i;

    while(c - 1 < n){
        if(A[c-1]==v)
            return c-1; 
        if(A[c-1]>v) 
            break;
        // Calcula la serie de fibonacci
        a = b;
        b = c;
        c = a+b;
    }
    // Buscar por busqueda binaria en un rango
    return binarySearch(A, b-1, c-1>n-1 ? n-1 : c-1, v);
}

/*
int binarySearch(int *A,int l,int r,int v)
Recibe: int * Referencia/Direccion al arreglo A, int posicion inicial
del rango a buscar, posicion final del rango a buscar, int valor a buscar 
en el archivo
Devuelve: int posicion donde se encuentra el valor en el arreglo
Observaciones: Funcion que busca un valor en un arreglo por
metodo de busqueda binaria
*/
int binarySearch(int *A,int l,int r,int v){
    int m;
    while(l<=r){
        m=(r+l)/2;
        if(A[m]==v)
         return m;
        
        A[m] > v ? (r = m - 1) : (l = m + 1);
    }
    // Retornar -1 si no se encontro el valor
    return -1;
}
