#include "huffman.h"

void buildHuffmanTree(arbol_binario *tree, int frec[256])
{
    int bytesUnicos = 0;
    for (int i = 0, j = 0; i < 256; ++i)
        if (frec[i] > 0)
            bytesUnicos++;

    arbol_binario **list = malloc(bytesUnicos * sizeof(arbol_binario *));

    for (int i = 0, j = 0; i < 256; ++i)
    {
        if (frec[i] == 0)
            continue;

        list[j] = malloc(sizeof(arbol_binario));
        Initialize(list[j]);
        elemento e = {(byte)i, frec[i]};
        NewLeftSon(list[j++], NULL, e);
    }

    qsort(list, bytesUnicos, sizeof(arbol_binario), cmpFreq);

    while (bytesUnicos > 1)
    {

        arbol_binario *izq = list[0];
        arbol_binario *der = list[1];

        int f1 = ReadNode(izq, Root(izq)).frec;
        int f2 = ReadNode(der, Root(der)).frec;

        arbol_binario *padre = malloc(sizeof(arbol_binario));
        Initialize(padre);
        elemento e = {0, f1 + f2};
        NewLeftSon(padre, NULL, e);

        AttachLeftSubtree(padre, Root(padre), *izq);
        AttachRightSubtree(padre, Root(padre), *der);

        list[0] = padre;

        for (int i = 1; i < bytesUnicos - 1; ++i)
        {
            list[i] = list[i + 1];
        }
        free(list[bytesUnicos]);

        qsort(list, --bytesUnicos, sizeof(arbol_binario), cmpFreq);
    }

    *tree = *(list[0]);
    free(list[0]);
    free(list);

    return;
}

int cmpFreq(const void *a, const void *b)
{
    arbol_binario *A = *(arbol_binario **)a;
    arbol_binario *B = *(arbol_binario **)b;

    int fa = ReadNode(A, Root(A)).frec;
    int fb = ReadNode(B, Root(B)).frec;

    return (fa > fb) - (fa < fb);
}