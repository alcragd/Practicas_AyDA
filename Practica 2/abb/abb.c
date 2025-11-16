/*
Nombre del programa: abb.c
Version: 1.0 Octubre 2025
Autores: Ramos Mendoza Miguel Angel / Coyol Moreno Angel Zoe / Ramirez Hernandez Christian Isaac

Implementación de las funciones para el manejo de Árbol Binario de Búsqueda (ABB)
utilizado en el algoritmo TreeSort.

Compilacion: gcc abb.c -c
*/

#include "abb.h"
#include <string.h>
#include <stdlib.h>

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
Devuelve: booleanon
Observaciones: Funcion que verifica si un arbol està vacio
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


booleano abbSearch(abb *A,int v){
    if(*A==NULL)
        return FALSE;
    if((*A)->num==v)
        return TRUE;
    if((*A)->num>v)
        return abbSearch(&((*A)->left),v);
    if((*A)->num<v)
        return abbSearch(&((*A)->right),v);
}