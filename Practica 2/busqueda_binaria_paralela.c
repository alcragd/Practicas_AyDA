/*
Nombre del programa: busqueda_binaria_paralela.c
Version: 1.0 Noviembre 2025
Autores: Ramos Mendoza Miguel Angel / Coyol Moreno Angel Zoe / Ramirez Hernandez Christian Isaac

Programa que lee n numeros y los coloca en un arreglo A,
ejecuta un algoritmo que busca un numero v por metodo de
busqueda binaria paralela con multiples hilos

Compilacion: gcc busqueda_binaria_paralela.c tiempo/tiempo.c -o busqueda_binaria_paralela
Ejecucion: ./busqueda_binaria_paralela n h < numeros10millones.txt
Donde: n = tamaño del arreglo, h = numero de hilos
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>
#include <unistd.h>
#include "tiempo/tiempo.h"

void *binarySearchThread(void *arg);

int res = -1;
atomic_int encontrado = 0;
pthread_mutex_t mutex;

struct datos {
    int *A;
    int l;
    int r;
    int val;
    int id;
};

typedef struct datos DATOS;

int main(int argc, char **argv)
{
    if(argc != 2)
        exit(1);

    int n, h, *A, val;
    double utime0, stime0, wtime0, utime1, stime1, wtime1;
    
    n = atoi(argv[1]);
    h = sysconf(_SC_NPROCESSORS_ONLN);
    
    pthread_mutex_init(&mutex, NULL);
    pthread_t *hilos = malloc(sizeof(pthread_t) * h);
    DATOS *datos_hilos = malloc(sizeof(DATOS) * h);
    
    A = malloc(n * sizeof(int));
    
    if (A == NULL) {
        printf("\n[!]-- Error al asignar memoria");
        exit(1);
    }

    scanf("%d", &val);
    
    for(int i = 0; i < n; ++i)
        scanf("%d", &A[i]);

    uswtime(&utime0, &stime0, &wtime0);

    // Dividir el rango [0, n-1] en h segmentos para búsqueda binaria paralela
    int tam = n / h;
    
    for(int i = 0; i < h; i++) {
        datos_hilos[i].A = A;
        datos_hilos[i].l = i * tam;
        // El último hilo toma hasta el final del arreglo
        datos_hilos[i].r = (i == h - 1) ? n - 1 : (i + 1) * tam - 1;
        datos_hilos[i].val = val;
        datos_hilos[i].id = i;
        
        pthread_create(&hilos[i], NULL, binarySearchThread, &datos_hilos[i]);
    }

    // Esperar a que terminen todos los hilos
    for(int i = 0; i < h; i++) {
        pthread_join(hilos[i], NULL);
    }

    uswtime(&utime1, &stime1, &wtime1);

    printf("\n%d", res);
    printf("\n%.10e", wtime1 - wtime0);

    free(A);
    free(hilos);
    free(datos_hilos);
    pthread_mutex_destroy(&mutex);

    return(0);
}

/*
void *binarySearchThread(void *arg)
Recibe: puntero a estructura DATOS con parámetros de búsqueda
Devuelve: NULL
Observaciones: Cada hilo ejecuta búsqueda binaria en su rango asignado.
                Como el arreglo está ordenado, cada hilo puede buscar
                independientemente en su segmento.
*/
void *binarySearchThread(void *arg) {
    DATOS *d = (DATOS*)arg;
    int m;
    int l = d->l;
    int r = d->r;
    
    // Búsqueda binaria en el rango [l, r]
    while(l <= r) {
        // Si otro hilo ya encontró el valor, salir
        if(atomic_load(&encontrado)) {
            return NULL;
        }
        
        m = (r + l) / 2;
        
        if(d->A[m] == d->val) {
            // Usar mutex para evitar race condition en la asignación de res
            pthread_mutex_lock(&mutex);
            if (!atomic_load(&encontrado)) {
                res = m;
                atomic_store(&encontrado, 1);
            }
            pthread_mutex_unlock(&mutex);
            return NULL;
        }
        
        // Ajustar los límites según si el valor está a la derecha o izquierda
        if(d->A[m] > d->val) {
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    
    // Retornar sin encontrar en este rango
    return NULL;
}
