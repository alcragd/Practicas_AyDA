/*================================================================================
huffman.h
Versión: 1.2
Fecha: Diciembre 2025
Autores: Coyol Moreno Angel Zoe
         Ramirez Hernandez Christian Isaac
         Ramos Mendoza Miguel Angel

Descripción:
------------
Interfaz para la construcción de un árbol de Huffman y la generación de los
códigos binarios por símbolo. Se apoya en el TAD árbol binario definido en
lib/tree/bintree.h.

Contenido:
- byteCode          : estructura que asocia un byte con su código (cadena).
- buildHuffmanTree  : construye el árbol de Huffman a partir de frecuencias.
- getHuffmanCod     : genera la tabla de códigos a partir del árbol.
- huffmanCodRec     : recorrido recursivo para obtener códigos.
- cmpFreq           : comparador usado por qsort para ordenar nodos por frecuencia.

Observaciones:
--------------
- Las funciones usan el tipo arbol_binario definido en bintree.h.
- buildHuffmanTree devuelve el árbol completo en *tree (la memoria de nodos
  pertenece al árbol resultante).
- getHuffmanCod devuelve un arreglo de byteCode con num_elem entradas.
  Las cadenas codigo deben liberarse por el llamador cuando ya no se necesiten.
- El orden de códigos depende del recorrido: '0' para rama izquierda, '1'
  para rama derecha. Longitud máxima de código asumida por huffmanCodRec: 511.

Compilación:
------------
gcc -c huffman.c

================================================================================*/
#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../pila_dinamica/pila_din.h"
#include "../tree/bintree.h"

#ifndef byte
    typedef unsigned char byte;
#endif

/*
byteCode

Descripción:
    Asociación entre un símbolo (byte) y su código binario representado
    como cadena terminada en '\0' (por ejemplo: "0101").

Notas:
    - La cadena codigo es alocada dinámicamente por getHuffmanCod/huffmanCodRec.
      El llamador es responsable de liberarla.
*/
typedef struct {
    byte b;
    char* codigo;
} byteCode;
    
/*
buildHuffmanTree

Descripción:
    Crea un árbol de Huffman a partir del arreglo de frecuencias 'frec'.

Recibe:
    arbol_binario *tree : dirección donde se almacenará el árbol resultante.
    int frec[256]       : contador de frecuencias por cada valor de byte [0..255].

Devuelve:
    Entero con el número de símbolos distintos (cantidad de hojas).

Observaciones:
    - El árbol devuelto en *tree contiene nodos con elemento.frec = frecuencia
      (suma de subárboles) y elemento.b = símbolo en hojas (0 en nodos internos).
    - En caso de error de memoria la función termina con exit(1).
*/
int buildHuffmanTree(arbol_binario *tree,int frec[256]);

/*
getHuffmanCod

Descripción:
    Genera la tabla de códigos (array de byteCode) recorriendo el árbol de
    Huffman y asignando a cada hoja su código binario.

Recibe:
    arbol_binario *tree : árbol de Huffman ya construido.
    int num_elem        : número de hojas esperadas (generalmente valor devuelto por buildHuffmanTree).

Devuelve:
    Puntero a arreglo dinámico de byteCode con num_elem elementos. NULL si falla
    la alocación. El llamador debe liberar las cadenas codigo y el arreglo.
*/
byteCode* getHuffmanCod(arbol_binario *tree,int num_elem);

/*
huffmanCodRec

Descripción:
    Rutina recursiva auxiliar que recorre el árbol y construye los códigos.
    Se usa internamente por getHuffmanCod.

Parámetros:
    arbol_binario* t : árbol en el que se recorre.
    posicion p       : posición actual en el recorrido.
    byteCode *arr    : arreglo donde se almacenan los resultados.
    int *i           : índice actual en arr (se incrementa cuando se agrega una hoja).
    char *buf        : buffer temporal para construir el código (must be large enough).
    int depth        : profundidad actual (posición en buf).
    int n            : tamaño máximo del arreglo arr (para evitar sobreescrituras).

Notas:
    - '0' se escribe en buf cuando se desciende a la izquierda, '1' para la derecha.
    - Cuando se alcanza una hoja se aloca una copia de la porción válida de buf.
*/
void huffmanCodRec(arbol_binario* t, posicion p, byteCode *arr, int *i, char *buf, int depth, int n);

/*
cmpFreq

Descripción:
    Comparador para qsort que ordena punteros a arbol_binario por la frecuencia
    almacenada en la raíz (elemento.frec).

Usos:
    - Ordenación de la lista de árboles auxiliares en buildHuffmanTree.
*/
int cmpFreq(const void *a, const void *b);
/*
getCoddedTree

Descripción:
    Serializa la estructura del árbol de Huffman en un flujo de bits. Utiliza
    un recorrido DFS para representar nodos internos con '0' y hojas con '1' 
    seguido del valor del byte (8 bits).

Parámetros:
    huff_tree : Puntero al árbol de Huffman construido.
    out       : Puntero doble donde se asignará el buffer de bytes empaquetados.

Devuelve:
    Entero que representa la longitud total del árbol en bits. Retorna -1 si 
    falla la asignación de memoria.
*/
int getCoddedTree(arbol_binario *huff_tree, byte** out);
/*
getCoddedTree_dfs

Descripción:
    Función auxiliar recursiva que realiza un recorrido en preorden para 
    generar una cadena de caracteres '0' y '1' que representa el árbol.

Parámetros:
    t    : Árbol binario procesado.
    p    : Posición actual en el recorrido.
    buff : Buffer temporal para almacenar la secuencia de bits como caracteres.
    i    : Índice del bit actual en el buffer.
*/
void getCoddedTree_dfs(arbol_binario *t, posicion p,char* buff,int *i);
int getPackedSize(char *buff, int len);
/*
decodeTree

Descripción:
    Reconstruye un árbol de Huffman a partir de su representación serializada 
    leída de un archivo comprimido. Utiliza una pila para gestionar la 
    jerarquía de nodos durante la reconstrucción.

Parámetros:
    t          : Árbol binario donde se reconstruirá la estructura.
    codded_t   : Buffer de bytes que contiene el árbol empaquetado.
    tree_len   : Longitud del árbol en bits.
*/
void decodeTree(arbol_binario *t, byte *codded_t, unsigned short tree_len);


#endif
