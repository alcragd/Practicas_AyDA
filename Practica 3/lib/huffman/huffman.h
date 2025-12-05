#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <stdio.h>
#include <stdlib.h>

#include "bintree.h"

#ifndef byte
    typedef unsigned char byte;
#endif


void buildHuffmanTree(arbol_binario *tree,int frec[256]);
int cmpFreq(const void *a, const void *b);

#endif
