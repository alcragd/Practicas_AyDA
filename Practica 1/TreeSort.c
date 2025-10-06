#include <stdio.h>
#include <stdlib.h>
#include "abb/abb.h"

void TreeSort(int *A);

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
}

void TreeSort(int *A, int i)
{

    if (*A != NULL)
    {
        TreeSort(LeftSonABB(A), i);
        A[i] = GetNumABB(A, A);
        i++;
        TreeSort(RightSonABB(A), i);
    }
}