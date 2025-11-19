/*
Nombre del programa: abb_threads.c
Version: 2.0 Octubre 2025
Autores: Ramos Mendoza Miguel Angel / Coyol Moreno Angel Zoe / Ramirez Hernandez Christian Isaac

Implementación de las funciones para el manejo de Árbol Binario de Búsqueda (ABB)
con soporte para búsquedas paralelas thread-safe.

Compilacion: gcc abb_threads.c -c
*/

#include "abb.h"
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

/*
void Initialize_ABB(abb *A)
Recibe: abb * Referencia/Direccion al arbol
Devuelve: void
Observaciones: Funcion que inicializa el arbol
*/
void Initialize_ABB(abb *A)
{
    *A = NULL;
    return;
}

/*
void Insert_ABB(abb *A, int num)
Recibe: abb * Referencia/Direccion al arbol, int numero a insertar
Devuelve: void
Observaciones: Funcion que inserta y acomoda un elemento al abb
*/
void Insert_ABB(abb *A, int num)
{
    nodo *newNode;

    if (Empty_ABB(&(*A)))
    {
        newNode = malloc(sizeof(nodo));
        if (newNode == NULL)
        {
            printf("\nInsert_ABB(A,e): ERROR Desbordamiento de Arbol.");
            exit(1);
        }

        newNode->num = num;
        newNode->left = NULL;
        newNode->right = NULL;
        *A = newNode;
    }
    else
    {
        if (num < (*A)->num)
            Insert_ABB(&((*A)->left), num);
        else if (num > (*A)->num)
            Insert_ABB(&((*A)->right), num);
        else
        {
            printf("\nInsert_ABB(A,e): el numero '%d' ya existe.", num);
        }
    }
    return;
}

/*
booleano NullNode_ABB(abb *A, posicion p)
Recibe: abb * Referencia/Direccion al arbol, posicion p
Devuelve: booleano
Observaciones: Funcion que verifica si un nodo en un arbol es valido
*/
booleano NullNode_ABB(abb *A, posicion p)
{
    booleano b = TRUE;
    if (*A == NULL || p == NULL)
        return TRUE;
    if (*A == p)
        return FALSE;
    if ((*A)->left != NULL)
        b = NullNode_ABB(&((*A)->left), p);
    if ((*A)->right != NULL && b)
        b = NullNode_ABB(&((*A)->right), p);

    return b;
}

/*
booleano Empty_ABB(abb *A)
Recibe: abb * Referencia/Direccion al arbol
Devuelve: booleano
Observaciones: Funcion que verifica si un arbol esta vacio
*/
booleano Empty_ABB(abb *A)
{
    if (*A == NULL)
        return TRUE;
    return FALSE;
}

/*
void Destroy_ABB(abb *A)
Recibe: abb * Referencia/Direccion al arbol
Devuelve: void
Observaciones: Funcion recursiva que destruye un abb
*/
void Destroy_ABB(abb *A)
{
    if (*A == NULL)
        return;
    Destroy_ABB(&((*A)->left));
    Destroy_ABB(&((*A)->right));
    free(*A);
    *A = NULL;
}

/*
booleano abbSearch(abb *A, int v)
Recibe:   abb *A   -> puntero al ABB (raíz)
          int v    -> valor a buscar
Devuelve: booleano -> TRUE si el valor existe en el árbol, FALSE en caso contrario

Observaciones:
- La función recorre recursivamente el árbol comparando 'v' con el campo num
  del nodo actual. Si el nodo es NULL devuelve FALSE (no encontrado).
- Si el valor es igual al del nodo devuelve TRUE.
- Si el valor es menor, busca en el subárbol izquierdo; si es mayor, en el derecho.
- No modifica la estructura del árbol, por lo que es THREAD-SAFE para lectura.
- Múltiples hilos pueden buscar en el MISMO árbol simultáneamente sin problemas,
  siempre que NO haya inserciones/eliminaciones concurrentes.
*/
booleano abbSearch(abb *A, int v){
    if(*A == NULL)
        return FALSE;
    if((*A)->num == v)
        return TRUE;
    if((*A)->num > v)
        return abbSearch(&((*A)->left), v);
    else  /* (*A)->num < v */
        return abbSearch(&((*A)->right), v);
}

