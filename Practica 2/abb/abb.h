/*
Nombre del archivo: abb.h
Version: 1.0 Octubre 2025
Autores: Ramos Mendoza Miguel Angel / Coyol Moreno Angel Zoe / Ramirez Hernandez Christian Isaac

Definición de estructuras y funciones para el manejo de Árbol Binario de Búsqueda (ABB)
utilizado en el algoritmo TreeSort.
*/

#ifndef __TAD_ABB
#define __TAD_ABB
#include <stdio.h>

#define TRUE 1
#define FALSE 0

typedef char booleano;

// Nodo del árbol binario de búsqueda.
typedef struct nodo
{
    int num;

    struct nodo *left;  // Hijo izquierdo
    struct nodo *right; // Hijo derecho
} nodo;

typedef nodo *abb; // Puntero al árbol
typedef nodo *posicion;           // Puntero a un nodo (posición)

void Initialize_ABB(abb *A);
void Destroy_ABB(abb *A);
void Insert_ABB(abb *A, int num);
booleano Empty_ABB(abb *A);
booleano NullNode_ABB(abb *A, posicion p);
booleano abbSearch(abb *A,int v);

#endif //__TAD_ABB