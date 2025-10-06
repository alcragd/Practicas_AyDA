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

typedef nodo *arbol_bin_busqueda; // Puntero al árbol
typedef nodo *posicion;           // Puntero a un nodo (posición)

void Initialize_ABB(arbol_bin_busqueda *A);
void Destroy_ABB(arbol_bin_busqueda *A);
void Insert_ABB(arbol_bin_busqueda *A, int num);
booleano Empty_ABB(arbol_bin_busqueda *A);
booleano NullNode_ABB(arbol_bin_busqueda *A, posicion p);
posicion LeftSonABB(arbol_bin_busqueda *A);
posicion RightSonABB(arbol_bin_busqueda *A);
int GetNumABB(arbol_bin_busqueda *A, posicion p);

#endif //__TAD_ABB