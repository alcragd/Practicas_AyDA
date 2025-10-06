#include "abb.h"
#include <string.h>
#include <stdlib.h>

void Initialize_ABB(arbol_bin_busqueda *A)
{
    *A = NULL;
    return;
}

void Insert_ABB(arbol_bin_busqueda *A, int num)
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

booleano NullNode_ABB(arbol_bin_busqueda *A, posicion p)
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

booleano Empty_ABB(arbol_bin_busqueda *A)
{
    if (*A == NULL)
        return TRUE;
    return FALSE;
}

void Destroy_ABB(arbol_bin_busqueda *A)
{
    if (*A == NULL)
        return;
    Destroy_ABB(&((*A)->left));
    Destroy_ABB(&((*A)->right));
    free(*A);
    *A = NULL;
}

posicion LeftSonABB(arbol_bin_busqueda *A)
{
    posicion p;
    p = &((*A)->left);
    return p;
}

posicion RightSonABB(arbol_bin_busqueda *A)
{
    posicion p;
    p = &((*A)->right);
    return p;
}

int GetNumABB(arbol_bin_busqueda *A, posicion p)
{
    if (!NullNode_ABB(A, p))
        return p->num;
    else
        printf("\nGetKey_ABB(a,p): Posición invalida");
}

// void RecorridoInOrden(arbol_bin_busqueda *A)
// {
//     if (*A != NULL)
//     {
//         RecorridoInOrden(&((*A)->left));
//         printf("%s:\n%s\n", (*A)->clave, (*A)->e.d);
//         RecorridoInOrden(&((*A)->right));
//     }
//     return;
// }