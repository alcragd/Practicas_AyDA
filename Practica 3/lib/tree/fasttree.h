#ifndef FASTTREE_H
#define FASTTREE_H

#include <stdint.h>
#include "bintree.h"

/*
===============================================
 TAD FastTree
 Autor: 
 Fecha: 2025
===============================================
Este TAD convierte tu arbol_binario dinámico
en una representación **compacta e indexada**
ideal para acceder MUY rápido durante
la descompresión Huffman.
===============================================
*/

/*
 Cada nodo se guarda en un arreglo.
 No hay punteros, solo índices.
*/
typedef struct {
    uint16_t left;     // índice del hijo izquierdo, NO_CHILD si no existe
    uint16_t right;    // índice del hijo derecho, NO_CHILD si no existe
    byte     symbol;   // símbolo (solo válido si es hoja)
    uint8_t  isLeaf;   // 1 si es hoja
} FastNode;

#define NO_CHILD 0xFFFF

typedef struct {
    FastNode *nodes;      // arreglo indexado
    uint16_t count;       // número total de nodos
} FastTree;

/*
 Construye el FastTree desde un arbol_binario dinámico.
 Debe llamarse justo después de decodeTree().
*/
void buildFastTree(FastTree *ft, arbol_binario *tree);

/*
 Libera la memoria del fast tree.
*/
void freeFastTree(FastTree *ft);

/*
 Decodifica los bits usando el fast tree.
 (La escritura en archivo la haces tú afuera)
*/
byte decodeNextSymbol(FastTree *ft, byte currentByte, int bit, uint16_t *cursor);

#endif
