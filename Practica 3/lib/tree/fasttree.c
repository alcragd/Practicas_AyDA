#include <stdlib.h>
#include <stdint.h>
#include "fasttree.h"
#include "bintree.h"

// Recorrido para recolectar punteros en preorden
static void collectNodes(posicion p, posicion *list, uint16_t *count) {
    if (p == NULL) return;
    list[(*count)++] = p;
    collectNodes(p->izq, list, count);
    collectNodes(p->der, list, count);
}

static int findIndex(posicion *list, uint16_t n, posicion p) {
    for (uint16_t i = 0; i < n; i++)
        if (list[i] == p) return i;
    return -1;
}

void buildFastTree(FastTree *ft, arbol_binario *tree) {
    ft->nodes = NULL;
    ft->count = 0;

    if (tree == NULL || *tree == NULL)
        return;

    const uint16_t MAX = 2048;  // suficiente para cualquier árbol Huffman
    posicion *plist = malloc(sizeof(posicion) * MAX);
    if (!plist) return;

    uint16_t n = 0;
    collectNodes(*tree, plist, &n);

    ft->nodes = malloc(sizeof(FastNode) * n);
    if (!ft->nodes) {
        free(plist);
        return;
    }

    ft->count = n;

    for (uint16_t i = 0; i < n; ++i) {
        posicion p = plist[i];

        // hijo izquierdo
        if (p->izq) {
            int idx = findIndex(plist, n, p->izq);
            ft->nodes[i].left = (idx >= 0 ? idx : NO_CHILD);
        } else {
            ft->nodes[i].left = NO_CHILD;
        }

        // hijo derecho
        if (p->der) {
            int idx = findIndex(plist, n, p->der);
            ft->nodes[i].right = (idx >= 0 ? idx : NO_CHILD);
        } else {
            ft->nodes[i].right = NO_CHILD;
        }

        // hoja = no hijos
        uint8_t leaf = (ft->nodes[i].left == NO_CHILD &&
                        ft->nodes[i].right == NO_CHILD);

        ft->nodes[i].isLeaf = leaf;
        ft->nodes[i].symbol = p->e.b;
    }

    free(plist);
}

void freeFastTree(FastTree *ft) {
    if (ft->nodes) free(ft->nodes);
    ft->nodes = NULL;
    ft->count = 0;
}

/*
 Devuelve un símbolo si se llegó a hoja.
 Si NO es hoja, devuelve 0 y no modifica output.
 cursor: índice actual del nodo.
*/
byte decodeNextSymbol(FastTree *ft, byte currentByte, int bit, uint16_t *cursor) {
    FastNode *nodes = ft->nodes;
    uint16_t c = *cursor;

    int b = (currentByte >> (7 - bit)) & 1;

    if (b == 0)
        c = nodes[c].left;
    else
        c = nodes[c].right;

    *cursor = c;

    if (nodes[c].isLeaf) {
        byte sym = nodes[c].symbol;
        *cursor = 0; // volver a raíz
        return sym;
    }

    return 0; // aún no es símbolo
}
