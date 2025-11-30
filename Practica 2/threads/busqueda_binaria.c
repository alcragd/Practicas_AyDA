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
#include <pthread.h>
#include <stdatomic.h>
#include <unistd.h>
#include "../tiempo/tiempo.h"

void binarySearch(int *A,int n,int v);
void *pivot_check(void *arg);


int res=-1;
atomic_int flag = 0;
pthread_mutex_t mutex;

int main(int argc,char **argv)
{
    // Recibe por argumento el valor de la variable n (tamaño del arreglo a ordenar)
    if(argc!=2)
        exit(1);

    // Variables para el algoritmo
    int n, *A, val;
    
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
    binarySearch(A,n,val);

    /// Evaluar los tiempos de ejecución
    uswtime(&utime1, &stime1, &wtime1);

    printf("\n%d",res);
    //Imprime el tiempo en formato exponencial.
    printf("\n%.10e",wtime1 - wtime0);
    // Libera la memoria correspondiente al arreglo A
    free(A);

    return 0;
}

/*
int binarySearch(int *A,int n,int v)
Recibe: int * Referencia/Direccion al arreglo A, int tamano del arreglo,
int valor a buscar en el archivo
Devuelve: int posicion donde se encuentra el valor en el arreglo
Observaciones: Funcion que busca un valor en un arreglo por
metodo de busqueda binaria
*/
void *pivot_check(void *arg) {
    
    struct pivot_arg {
        int *A;
        int idx;
        int val;
        int cmp; // -1: A[idx] < val, 0: equal, 1: A[idx] > val
    };
    struct pivot_arg *p = (struct pivot_arg*)arg;

    int x = p->A[p->idx];
    if (x == p->val) {
        pthread_mutex_lock(&mutex);
        if (!atomic_load(&flag)) {
            res = p->idx;
            atomic_store(&flag, 1);
        }
        pthread_mutex_unlock(&mutex);
        p->cmp = 0;
        return NULL;
    }
    p->cmp = (x < p->val) ? -1 : 1;
    return NULL;
}

void binarySearch(int *A,int n,int v){

    int t = 4; // numero de pivotes/hilos por ronda
    if (n <= 0) return;

    if (t > n) t = n;

    pthread_mutex_init(&mutex,NULL);

    // estado inicial
    res = -1;
    atomic_store(&flag, 0);

    int l = 0, r = n - 1;

    // pivot_arg definido localmente para usar en hilos
    struct pivot_arg {
        int *A;
        int idx;
        int val;
        int cmp;
    };

    while (l <= r && !atomic_load(&flag)) {
        int len = r - l + 1;

        // Si el segmento es pequeño, hacer búsqueda lineal 
        if (len <= t) {
            for (int i = l; i <= r && !atomic_load(&flag); ++i) {
                if (A[i] == v) {
                    pthread_mutex_lock(&mutex);
                    if (!atomic_load(&flag)) {
                        res = i;
                        atomic_store(&flag, 1);
                    }
                    pthread_mutex_unlock(&mutex);
                    break;
                }
            }
            break;
        }

        // calcular pivotes equiespaciados dentro de [l,r]
        int piv_count = t;
        pthread_t *threads = malloc(piv_count * sizeof(pthread_t));
        struct pivot_arg *pargs = malloc(piv_count * sizeof(struct pivot_arg));
        if (threads == NULL || pargs == NULL) {
            free(threads);
            free(pargs);
            break;
        }

        for (int i = 0; i < piv_count; ++i) {
            int pivot = l + ((i + 1) * len) / (piv_count + 1) - 1;
            if (pivot < l) pivot = l;
            if (pivot > r) pivot = r;
            pargs[i].A = A;
            pargs[i].idx = pivot;
            pargs[i].val = v;
            pargs[i].cmp = 0;
            if (pthread_create(&threads[i], NULL, pivot_check, &pargs[i]) != 0) {
                // error creando hilo: fallback a búsqueda secuencial en este rango
                for (int j = 0; j < i; ++j) pthread_join(threads[j], NULL);
                free(threads);
                free(pargs);
            }
        }

        for (int i = 0; i < piv_count; ++i)
            pthread_join(threads[i], NULL);

        // si alguno encontró el valor, salir
        if (atomic_load(&flag)) {
            free(threads);
            free(pargs);
            break;
        }

        // determinar nuevo subrango entre pivotes
        // recabar pivots y comparaciones
        int *pivots = malloc(piv_count * sizeof(int));
        int *cmps = malloc(piv_count * sizeof(int));
        if (pivots == NULL || cmps == NULL) {
            free(threads);
            free(pargs);
            free(pivots);
            free(cmps);
            break;
        }
        for (int i = 0; i < piv_count; ++i) {
            pivots[i] = pargs[i].idx;
            cmps[i] = pargs[i].cmp;
        }

        // caso: todos menores -> ir a la derecha del último pivote
        int all_less = 1, all_greater = 1;
        for (int i = 0; i < piv_count; ++i) {
            if (cmps[i] >= 0) all_less = 0;
            if (cmps[i] <= 0) all_greater = 0;
        }
        if (all_less) {
            l = pivots[piv_count - 1] + 1;
        } else if (all_greater) {
            r = pivots[0] - 1;
        } else {
            // encuentra primer pivote con cmp > 0
            int j = 0;
            while (j < piv_count && cmps[j] < 0) ++j;
            int new_l = (j == 0) ? l : pivots[j - 1] + 1;
            int new_r = pivots[j] - 1;
            l = new_l;
            r = new_r;
        }

        free(threads);
        free(pargs);
        free(pivots);
        free(cmps);
        
    }

    pthread_mutex_destroy(&mutex);
    
}