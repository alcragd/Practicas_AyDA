/*
Nombre del programa: busqueda_abb.c
Version: 1.0 Noviembre 2025
Autores: Ramos Mendoza Miguel Angel / Coyol Moreno Angel Zoe / Ramirez Hernandez Christian Isaac

Programa que construye un Árbol Binario de Búsqueda (ABB) a partir de n
números leídos y busca un valor v en el árbol midiendo el tiempo de búsqueda.

Compilacion: gcc busqueda_abb.c abb/abb.c tiempo/tiempo.c -o busqueda_abb
Ejecucion: ./busqueda_abb n < numeros10millones.txt

Salida:
  Línea 1: resultado (1 si se encontró, 0 si no) según la implementación de `abbSearch`
  Línea 2: tiempo real (wtime) en formato exponencial (%.10e)
*/

#include <stdio.h>
#include <stdlib.h>
#include "abb/abb.h"

#include "tiempo/tiempo.h"


int main(int argc, char **argv) {
    /* Verificar argumentos: se espera el tamaño n */
    if (argc != 2) {
        fprintf(stderr, "Uso: %s n\n", argv[0]);
        exit(1);
    }

    int n, res;
    int val;
    double utime0, stime0, wtime0, utime1, stime1, wtime1;
    abb tree;
    Initialize_ABB(&tree);

    n = atoi(argv[1]);

    /* Primer entero en la entrada es el valor a buscar */
    if (scanf("%d", &val) != 1) {
        fprintf(stderr, "Error: no se pudo leer el valor a buscar.\n");
        return 1;
    }

    /* Leer n números y construir el ABB mediante inserciones */
    for (int i = 0; i < n; ++i) {
        int num;
        if (scanf("%d", &num) != 1) {
            fprintf(stderr, "Error leyendo los datos (esperados %d números).\n", n);
            Destroy_ABB(&tree);
            exit(1);
        }
        Insert_ABB(&tree, num);
    }

    /* Medir únicamente el tiempo de búsqueda en el ABB */
    uswtime(&utime0, &stime0, &wtime0);
    res = abbSearch(&tree, val);
    uswtime(&utime1, &stime1, &wtime1);

     /* Imprimir resultado y tiempo en dos líneas (compatibilidad con el pipeline)
         Mapear el resultado booleano del ABB a -1 cuando NO se encuentre
         (coherente con el resto de algoritmos que devuelven -1 en 'no encontrado'). */
     int output_result = (res ? 1 : -1);
    printf("\n%d", output_result);
    printf("\n%.10e", wtime1 - wtime0);

    Destroy_ABB(&tree);

    return 0;
}

