/*
Nombre del programa: busqueda_fibonacci_paralela.c
Version: 1.0 Noviembre 2025
Autores: Ramos Mendoza Miguel Angel / Coyol Moreno Angel Zoe / Ramirez Hernandez Christian Isaac

Programa que lee n numeros y los coloca en un arreglo A,
ejecuta un algoritmo que busca un numero v por metodo de
busqueda fibonacci seguida de busqueda binaria paralela.
El número de hilos se detecta automáticamente según el número de cores.

ESTRATEGIA:
- FASE 1: Búsqueda Fibonacci secuencial (encuentra el rango)
- FASE 2: Búsqueda binaria paralela en el rango encontrado

Compilacion: gcc busqueda_fibonacci_paralela.c tiempo/tiempo.c -o busqueda_fibo_par
Ejecucion: ./busqueda_fibo_par n < numeros10millones.txt
Donde: n = tamaño del arreglo
       (los hilos se detectan automáticamente)
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>
#include <unistd.h>
#include "../tiempo/tiempo.h"

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
    
    // ============ DETECTAR NÚMERO DE CORES DISPONIBLES ============
    h = sysconf(_SC_NPROCESSORS_ONLN);
    
    if(h <= 0) {
        printf("\n[!]-- Error al detectar número de cores, usando 1\n");
        h = 1;
    }
    
    printf("\n[*] Cores detectados: %d\n", h);
    
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

    // ============ FASE 1: BÚSQUEDA FIBONACCI (secuencial) ============
    // Esta fase es rápida y encuentra el rango donde está el valor
    // usando números de Fibonacci para los saltos
    int a = 0, b = 1, c = 1;
    int left_range = 0;
    int right_range = n - 1;
    
    // Búsqueda Fibonacci para encontrar el rango
    while(c - 1 < n) {
        if(A[c - 1] == val) {
            res = c - 1;
            atomic_store(&encontrado, 1);
            goto finish;
        }
        
        if(A[c - 1] > val) {
            right_range = c - 2;
            break;
        }
        
        // Calcular siguiente número de Fibonacci
        left_range = b;
        a = b;
        b = c;
        c = a + b;
    }
    
    // Ajustar el rango derecho si es necesario
    if(c - 2 < n - 1) {
        right_range = c - 2 > n - 1 ? n - 1 : c - 2;
    }

    // ============ FASE 2: BÚSQUEDA BINARIA PARALELA EN EL RANGO ============
    // Distribuir la búsqueda binaria entre múltiples hilos
    int rango_size = right_range - left_range + 1;
    int tam_segmento = rango_size / h;
    
    // Si el rango es muy pequeño, no vale la pena paralelizar
    if(tam_segmento < 100) {
        // Hacer búsqueda binaria secuencial
        int l = left_range;
        int r = right_range;
        int m;
        
        while(l <= r) {
            m = (r + l) / 2;
            
            if(A[m] == val) {
                res = m;
                atomic_store(&encontrado, 1);
                goto finish;
            }
            
            A[m] > val ? (r = m - 1) : (l = m + 1);
        }
    } else {
        // Distribuir el rango entre h hilos
        for(int i = 0; i < h; i++) {
            datos_hilos[i].A = A;
            datos_hilos[i].l = left_range + i * tam_segmento;
            
            if(i == h - 1) {
                // El último hilo toma hasta el final del rango
                datos_hilos[i].r = right_range;
            } else {
                datos_hilos[i].r = left_range + (i + 1) * tam_segmento - 1;
            }
            
            datos_hilos[i].val = val;
            datos_hilos[i].id = i;
            
            pthread_create(&hilos[i], NULL, binarySearchThread, &datos_hilos[i]);
        }

        // Esperar a que terminen todos los hilos
        for(int i = 0; i < h; i++) {
            pthread_join(hilos[i], NULL);
        }
    }

finish:
    uswtime(&utime1, &stime1, &wtime1);

    printf("\n%d", res);
    printf("\n%.10f", wtime1 - wtime0);

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
Observaciones: Cada hilo ejecuta búsqueda binaria en su rango asignado
                dentro del rango ya acotado por la búsqueda Fibonacci.
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
            pthread_mutex_lock(&mutex);
            if (!atomic_load(&encontrado)) {
                res = m;
                atomic_store(&encontrado, 1);
            }
            pthread_mutex_unlock(&mutex);
            return NULL;
        }
        
        if(d->A[m] > d->val) {
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    
    return NULL;
}