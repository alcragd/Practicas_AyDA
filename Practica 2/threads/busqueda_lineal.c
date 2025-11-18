/*
Nombre del programa: busqueda_lineal.c
Version: 1.0 Noviembre 2025
Autores: Ramos Mendoza Miguel Angel / Coyol Moreno Angel Zoe / Ramirez Hernandez Christian Isaac

Programa que lee n numeros y los coloca en un arreglo A,
ejecuta un algoritmo que busca un numero v por metodo de
busqueda lineal

Compilacion: gcc busqueda_lineal.c tiempo/tiempo.c -o busqueda_lineal
Ejecucion: ./busqueda_lineal n < numeros10millones.txt
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>
#include <unistd.h>
#include "../tiempo/tiempo.h"

void *linearSearch(void *arg);

int res = -1;
atomic_int encontrado = 0;

pthread_mutex_t mutex;

struct datos{
    int *A;
    int l;
    int r;
    int val;
    int id;
};

typedef struct datos DATOS;

int main(int argc,char **argv)
{
    // Recibe por argumento el valor de la variable n (tamaño del arreglo a ordenar)
    if(argc!=3)
        exit(1);

    // Variables para el algoritmo
    int n, h, *A, val;
    double utime0, stime0, wtime0, utime1, stime1, wtime1; // Variables para medición de tiempos

    // Asigna a n el segundo argumento del main
    n=atoi(argv[1]);
    h=atoi(argv[2]);

    pthread_mutex_init(&mutex, NULL);
    pthread_t *hilos = malloc(sizeof(pthread_t) * h);
    DATOS *hilo = malloc(sizeof(DATOS) * h);

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

    int cores = sysconf(_SC_NPROCESSORS_ONLN);

    h = h < cores ? h : cores;

    int tam = n/h;
    for(int i = 0; i < h; i++){
        hilo[i].A = A;
        hilo[i].l = i * tam;
        hilo[i].r = (i == h - 1) ? n : (i + 1) * tam;
        hilo[i].val = val;
        hilo[i].id = i;

        // Llama al algoritmo
        pthread_create(&hilos[i], NULL, linearSearch, &hilo[i]);
    }

    for(int i = 0; i < h; i++){
        pthread_join(hilos[i], NULL);
    }
    
    /// Evaluar los tiempos de ejecución
    uswtime(&utime1, &stime1, &wtime1);

    // Mostrar la posicion del valor en el arreglo
    printf("\n%d",res);
 // Mostrar los tiempos en formato exponecial
    printf("\n%.10e",wtime1 - wtime0);

    //Libera la memoria correspondiente al arreglo A*/
    free(A);
    free(hilos);
    free(hilo);

    pthread_mutex_destroy(&mutex);

    return(0);
}

/*
int linearSearch(int *A,int n,int v)
Recibe: int * Referencia/Direccion al arreglo A, int tamano del arreglo,
int valor a buscar en el archivo
Devuelve: int posicion donde se encuentra el valor en el arreglo
Observaciones: Funcion que busca un valor en un arreglo por
metodo de busqueda lineal
*/
void *linearSearch(void *arg){
    DATOS *d = (DATOS*)arg;

    for(int i = d->l; i < d->r; i++){
        if(atomic_load(&encontrado)){
            return NULL;
        }
        if(d->A[i] == d->val){
            pthread_mutex_lock(&mutex);
            if (!atomic_load(&encontrado)) {
                res = i;
                atomic_store(&encontrado, 1);
            }
            pthread_mutex_unlock(&mutex);
            return NULL;
        }
    }
    
    return NULL;    
}