/*
Nombre del programa: busqueda_abb.c
Version: 2.0 Noviembre 2025
Autores: Ramos Mendoza Miguel Angel / Coyol Moreno Angel Zoe / Ramirez Hernandez Christian Isaac

Programa que construye h Árboles Binarios de Búsqueda (ABB) a partir de n
números leídos (dividiendo los n números en h particiones equitativas),
y busca un valor v en TODOS los árboles en PARALELO usando h hilos,
midiendo el tiempo de búsqueda paralela.

Compilacion: gcc busqueda_abb.c abb/abb.c abb/abb_threads.c tiempo/tiempo.c -o busqueda_abb
Ejecucion: ./busqueda_abb n h < numeros10millones.txt

Parámetros:
  n: tamaño total de números a leer
  h: número de árboles y hilos de búsqueda paralela

Salida:
  Línea 1: resultado (1 si se encontró en al menos un árbol, -1 si no)
  Línea 2: tiempo real (wtime) en formato exponencial (%.10e)
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>
#include "abb/abb.h"
#include "tiempo/tiempo.h"

/* Estructura para pasar argumentos a los hilos de búsqueda */
typedef struct {
    abb *tree;           /* Puntero al árbol asignado a este hilo */
    int val;             /* Valor a buscar */
    booleano *result;    /* Puntero compartido para almacenar resultado */
    int thread_id;       /* ID del hilo (para debugging) */
} search_thread_arg;

/* Variable compartida para el resultado de búsqueda */
atomic_int found_flag = 0;  /* 1 si se encontró en cualquier árbol */
pthread_mutex_t result_mutex;

void *abbSearchThread(void *arg);

int main(int argc, char **argv) {
    /* Verificar argumentos: se esperan n (tamaño) y h (número de árboles/hilos) */
    if (argc != 3) {
        fprintf(stderr, "Uso: %s n h\n", argv[0]);
        fprintf(stderr, "  n: número total de elementos\n");
        fprintf(stderr, "  h: número de árboles y hilos paralelos\n");
        exit(1);
    }

    int n = atoi(argv[1]);
    int h = atoi(argv[2]);
    int val;
    int res;
    double utime0, stime0, wtime0, utime1, stime1, wtime1;

    if (n <= 0) {
        fprintf(stderr, "Error: n debe ser > 0\n");
        exit(1);
    }
    if (h <= 0) {
        fprintf(stderr, "Error: h debe ser > 0\n");
        exit(1);
    }

    if (h > n) h = n;

    /* Leer el valor a buscar */
    if (scanf("%d", &val) != 1) {
        fprintf(stderr, "Error: no se pudo leer el valor a buscar.\n");
        return 1;
    }

    /* Inicializar mutex y flag */
    pthread_mutex_init(&result_mutex, NULL);
    atomic_store(&found_flag, 0);

    /* Asignar memoria para h árboles */
    abb *trees = malloc(h * sizeof(abb));
    if (trees == NULL) {
        fprintf(stderr, "Error: no se pudo asignar memoria para los árboles\n");
        return 1;
    }

    /* Inicializar todos los árboles */
    for (int i = 0; i < h; ++i) {
        Initialize_ABB(&trees[i]);
    }

    /* Leer n números y distribuirlos entre los h árboles */
    for (int i = 0; i < n; ++i) {
        int num;
        if (scanf("%d", &num) != 1) {
            fprintf(stderr, "Error leyendo los datos (esperados %d números).\n", n);
            for (int j = 0; j < h; ++j) {
                Destroy_ABB(&trees[j]);
            }
            free(trees);
            pthread_mutex_destroy(&result_mutex);
            exit(1);
        }
        
        /* Insertar en el árbol asignado por módulo (round-robin distribution) */
        int tree_idx = i % h;
        Insert_ABB(&trees[tree_idx], num);
    }

    /* ==================== MEDIR TIEMPO DE BÚSQUEDA PARALELA ==================== */
    uswtime(&utime0, &stime0, &wtime0);

    /* Crear h hilos de búsqueda paralela */
    pthread_t *threads = malloc(h * sizeof(pthread_t));
    search_thread_arg *thread_args = malloc(h * sizeof(search_thread_arg));

    if (threads == NULL || thread_args == NULL) {
        fprintf(stderr, "Error: no se pudo asignar memoria para los hilos\n");
        for (int i = 0; i < h; ++i) {
            Destroy_ABB(&trees[i]);
        }
        free(trees);
        free(threads);
        free(thread_args);
        pthread_mutex_destroy(&result_mutex);
        return 1;
    }

    /* Lanzar h hilos de búsqueda */
    for (int i = 0; i < h; ++i) {
        thread_args[i].tree = &trees[i];
        thread_args[i].val = val;
        thread_args[i].result = NULL;  /* No usado, usar found_flag */
        thread_args[i].thread_id = i;

        if (pthread_create(&threads[i], NULL, abbSearchThread, &thread_args[i]) != 0) {
            fprintf(stderr, "Error: no se pudo crear el hilo %d\n", i);
            /* Esperar los hilos ya creados */
            for (int j = 0; j < i; ++j) {
                pthread_join(threads[j], NULL);
            }
            for (int j = 0; j < h; ++j) {
                Destroy_ABB(&trees[j]);
            }
            free(trees);
            free(threads);
            free(thread_args);
            pthread_mutex_destroy(&result_mutex);
            return 1;
        }
    }

    /* Esperar a que terminen todos los hilos de búsqueda */
    for (int i = 0; i < h; ++i) {
        pthread_join(threads[i], NULL);
    }

    /* Detener medición de tiempo */
    uswtime(&utime1, &stime1, &wtime1);
    /* ==================== FIN MEDICIÓN ==================== */

    /* Obtener resultado final */
    res = atomic_load(&found_flag) ? 1 : -1;

    /* Imprimir resultado y tiempo */
    printf("\n%d", res);
    printf("\n%.10e", wtime1 - wtime0);

    /* Liberar memoria */
    for (int i = 0; i < h; ++i) {
        Destroy_ABB(&trees[i]);
    }
    free(trees);
    free(threads);
    free(thread_args);
    pthread_mutex_destroy(&result_mutex);

    return 0;
}



/*
void *abbSearchThread(void *arg)
Recibe: void *arg -> puntero a search_thread_arg
Devuelve: void * -> NULL
Observaciones: Función ejecutada por cada hilo de búsqueda paralela.
  Busca el valor en su árbol asignado y actualiza found_flag si lo encuentra.
*/
void *abbSearchThread(void *arg) {
    search_thread_arg *args = (search_thread_arg *)arg;
    
    /* Buscar en el árbol asignado */
    booleano res = abbSearch(args->tree, args->val);
    
    /* Si se encontró, marcar el flag de forma thread-safe */
    if (res) {
        pthread_mutex_lock(&result_mutex);
        if (!atomic_load(&found_flag)) {
            atomic_store(&found_flag, 1);
        }
        pthread_mutex_unlock(&result_mutex);
    }
    
    return NULL;
}