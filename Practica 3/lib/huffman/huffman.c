#include "huffman.h"

int buildHuffmanTree(arbol_binario *tree, int frec[256])
{
    int bytesExistentes = 0;
    for (int i = 0; i < 256; ++i)
        if (frec[i] > 0) bytesExistentes++;

    arbol_binario **list = malloc(bytesExistentes * sizeof(arbol_binario *));
    if (!list) exit(1);

    for (int i = 0, j = 0; i < 256; ++i)
    {
        if (frec[i] == 0) continue;

        list[j] = malloc(sizeof(arbol_binario));
        if (!list[j])  exit(1);

        Initialize(list[j]);
        elemento e = {(byte)i, frec[i]};
        NewRightSon(list[j], NULL, e);   
        ++j;
    }

    qsort(list, bytesExistentes, sizeof(arbol_binario *), cmpFreq);

    int r=bytesExistentes;

    while (bytesExistentes > 1)
    {
        arbol_binario *izq = list[0];
        arbol_binario *der = list[1];

        int f1 = ReadNode(izq, Root(izq)).frec;
        int f2 = ReadNode(der, Root(der)).frec;

        arbol_binario *padre = malloc(sizeof(arbol_binario));
        Initialize(padre);
        elemento e = {0, f1 + f2};
        NewRightSon(padre, NULL, e);     

        AttachLeftSubtree(padre, Root(padre), *izq);
        AttachRightSubtree(padre, Root(padre), *der);

        free(izq);
        free(der);

        list[0] = padre;

        for (int i = 1; i < bytesExistentes - 1; ++i)
            list[i] = list[i + 1];
    
        qsort(list, --bytesExistentes, sizeof(arbol_binario *), cmpFreq);
    }

    *tree = *(list[0]);
    free(list[0]);
    free(list);
    return r;
}

byteCode* getHuffmanCod(arbol_binario *tree,int num_elem){
    byteCode *r = malloc(num_elem * sizeof(byteCode));
    if (!r) return NULL;
    int i = 0;
    char buf[512]; 
    buf[0] = '\0';
    huffmanCodRec(tree, Root(tree), r, &i, buf, 0, num_elem);
    return r;
}


void huffmanCodRec(arbol_binario* t, posicion p, byteCode *arr, int *i, char *buf, int depth, int n){
    if (p == NULL || NullNode(t, p) || *i >= n)
        return;

    posicion l = LeftSon(t, p);
    posicion r = RightSon(t, p);

   
    if ((l == NULL || NullNode(t, l)) && (r == NULL || NullNode(t, r))) {
        elemento e = ReadNode(t, p);
        buf[depth] = '\0';
        int len = depth + 1;
        char *code = malloc(len);
        memcpy(code, buf, depth);
        code[depth] = '\0';
        arr[*i].b = e.b;
        arr[*i].codigo = code;
        (*i)++;
        return;
    }

    
    buf[depth] = '0';
    huffmanCodRec(t, l, arr, i, buf, depth + 1, n);

    buf[depth] = '1';
    huffmanCodRec(t, r, arr, i, buf, depth + 1, n);

    buf[depth] = '\0';
}

int cmpFreq(const void *a, const void *b)
{
    arbol_binario *A = *(arbol_binario **)a;
    arbol_binario *B = *(arbol_binario **)b;

    int fa = ReadNode(A, Root(A)).frec;
    int fb = ReadNode(B, Root(B)).frec;

    return (fa > fb) - (fa < fb);
}