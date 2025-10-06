#include <stdio.h>
#include <stdlib.h>
#include "abb/abb.h"

void TreeSortRecursivo(arbol_bin_busqueda *A, int *array, int *i);
void TreeSort(int *A, int n);

int main(int argc, char **argv)
{
    int i, n, *A;

    if (argc != 2)
    {
        exit(1);
    }

    n = atoi(argv[1]);
    A = malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
        scanf("%d", &A[i]);

    TreeSort(A, n);

    for (i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");

    free(A);
    return 0;
}

void TreeSort(int *A, int n)
{
    int i;
    arbol_bin_busqueda tree;
    Initialize_ABB(&tree);

    for (i = 0; i < n; i++)
        Insert_ABB(&tree, A[i]);

    i = 0;
    TreeSortRecursivo(&tree, A, &i);

    Destroy_ABB(&tree);
}

void TreeSortRecursivo(arbol_bin_busqueda *A, int *array, int *i) // Recorrido InOrder
{
    if (*A != NULL)
    {
        TreeSortRecursivo(&((*A)->left), array, i);
        array[(*i)++] = (*A)->num;
        TreeSortRecursivo(&((*A)->right), array, i);
    }
}