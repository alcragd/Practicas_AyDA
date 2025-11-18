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
void *binarySearch_t(void *arg);

typedef struct {
    int *A;
    int l;
    int r;
    int val;
} datos_t;

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
}

/*
int binarySearch(int *A,int n,int v)
Recibe: int * Referencia/Direccion al arreglo A, int tamano del arreglo,
int valor a buscar en el archivo
Devuelve: int posicion donde se encuentra el valor en el arreglo
Observaciones: Funcion que busca un valor en un arreglo por
metodo de busqueda binaria
*/
void binarySearch(int *A,int n,int v){

    int t = sysconf(_SC_NPROCESSORS_ONLN); // numero de cores logicos del sistema

    pthread_mutex_init(&mutex,NULL);
    pthread_t *threads = malloc(t*sizeof(pthread_t));
    datos_t *thread = malloc(t*sizeof(datos_t));

    
    int tam = n/t;

    for(int i=0;i<t;++i){
        thread[i].A = A;
        thread[i].l = i * tam;
        thread[i].r = (i == t - 1) ? n : (i + 1) * tam;
        thread[i].val=v;

        pthread_create(&threads[i],NULL,binarySearch_t,&thread[i]);
    }

    for(int i = 0; i < t; i++){
        pthread_join(threads[i], NULL);
    }

    free(threads);
    free(thread);

    pthread_mutex_destroy(&mutex);
    
}


void *binarySearch_t(void *arg){
    datos_t *t =(datos_t*)arg;
    int m;

    while(t->l<=t->r){
        if(atomic_load(&flag)) return NULL;
        m=(t->r+t->l)/2;

        
        if(t->A[m]==t->val){
            pthread_mutex_lock(&mutex);
            if(!atomic_load(&flag)) {
                res=m;
                atomic_store(&flag,1);
            }
            pthread_mutex_unlock(&mutex);
            return NULL;
        }
        
        t->A[m] > t->val ? (t->r = m - 1) : (t->l = m + 1);
    }
    return NULL;    
}