#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../tree/bintree.h"

#ifndef byte
    typedef unsigned char byte;
#endif


typedef struct {
    byte b;
    char* codigo;
} byteCode;
    
int buildHuffmanTree(arbol_binario *tree,int frec[256]);
byteCode* getHuffmanCod(arbol_binario *tree,int num_elem);
void huffmanCodRec(arbol_binario* t, posicion p, byteCode *arr, int *i, char *buf, int depth, int n);
int cmpFreq(const void *a, const void *b);

#endif
