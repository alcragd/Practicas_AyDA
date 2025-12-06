/*
================================================================================
main.c
Versión: 1.1
Fecha: Diciembre 2025
Autores: Coyol Moreno Angel Zoe
         Ramirez Hernandez Christian Isaac
         Ramos Mendoza Miguel Angel

Descripción:
------------
Programa principal para la práctica de compresión Huffman.
- Lee un archivo de entrada (ruta pasada como argumento).
- Construye el árbol de Huffman a partir de frecuencias leídas del archivo.
- Genera códigos Huffman por byte.
- Comprime el contenido y escribe el resultado en un archivo de salida.

Uso:
----
./programa archivo.ext

Observaciones:
--------------
- depende de los módulos:
    lib/huffman/huffman.h   (con buildHuffmanTree, getHuffmanCod, etc.)
    lib/file/compresor.h    (con readF, compress, etc.)

- Este archivo contiene funciones auxiliares para imprimir el árbol.
================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/huffman/huffman.h"
#include "lib/file/compresor.h"


/* Prototipos de funciones auxiliares para impresión del árbol */
void PrintLeaves(arbol_binario *t, posicion p);
void PrintTreeVisual(arbol_binario *t, posicion p, int depth);
void PrintTree(arbol_binario *t);

int main(int argc, char** argv){
    if(argc != 2){
        printf("Error al leer datos");
        return 1; 
    }

    /* buffers para separar nombre y extensión del archivo */
    char name[512] = {0};
    char ext[64] = {0};
    char outname[600];

    /* parsea nombre.ext -> name, ext (evita overflow) */
    int n = sscanf(argv[1], "%511[^.].%63s", name, ext);

    /* arreglo de punteros a códigos por byte (inicializados a NULL) */
    char* Codigos[256] = {0};

    /* lectura del archivo: retorna frecuencias, bytes y tamaño */
    readFile rf = readF(argv[1]);
    printf("El archivo se leyo correctamente \n");

    arbol_binario tree;

    /* construye árbol de Huffman y obtiene cantidad de bytes presentes */
    int bytesExistentes = buildHuffmanTree(&tree, rf.frecuencias);

    /* obtiene los códigos Huffman (array de byteCode) */
    byteCode *bc = getHuffmanCod(&tree, bytesExistentes);

    /* llena la tabla de códigos indexada por el valor del byte */
    for(int i = 0; i < bytesExistentes; ++i)
        Codigos[(unsigned char)bc[i].b] = bc[i].codigo;

    /* nombre de salida: <nombre>_compressed.dat */
    snprintf(outname, sizeof(outname), "%s_compressed.dat", name);

    /* realiza la compresión y escribe el archivo de salida */
    compress(rf.bytes, rf.num_elements, Codigos, outname);

    return 0;
}


/*
PrintLeaves

Descripción:
    Recorre el árbol y imprime solo las hojas (byte y frecuencia).

Parámetros:
    t - árbol binario.
    p - posición desde la cual iniciar el recorrido (usualmente Root).
*/
void PrintLeaves(arbol_binario *t, posicion p)
{
    if (p == NULL || NullNode(t, p))
        return;

    posicion l = LeftSon(t, p);
    posicion r = RightSon(t, p);

    /* Si ambos hijos son nulos/invalidos -> es hoja */
    if ((l == NULL || NullNode(t, l)) && (r == NULL || NullNode(t, r))) {
        elemento e = ReadNode(t, p);
        /* imprime byte y frecuencia (formato ajustable) */
        printf("%c: 0x%02X: %d\n", e.b, (unsigned char)e.b, e.frec);
        return;
    }

    PrintLeaves(t, l);
    PrintLeaves(t, r);
}

/*
PrintTreeVisual

Descripción:
    Imprime el árbol visualmente rotado 90° hacia la izquierda.
    RightSon aparece arriba, Root en el centro, LeftSon abajo.
    depth controla la indentación (llamar con 0).

Parámetros:
    t     - árbol binario.
    p     - posición actual (usualmente Root).
    depth - nivel de indentación (usar 0 al llamar).
*/
void PrintTreeVisual(arbol_binario *t, posicion p, int depth)
{
    if (p == NULL || NullNode(t, p))
        return;

    /* imprimir subárbol derecho primero (se verá arriba) */
    PrintTreeVisual(t, RightSon(t, p), depth + 1);

    /* indentación */
    for (int i = 0; i < depth; ++i)
        printf("    ");

    /* imprimir nodo (byte y frecuencia) */
    elemento e = ReadNode(t, p);
    if ((LeftSon(t, p) == NULL || NullNode(t, LeftSon(t, p))) &&
        (RightSon(t, p) == NULL || NullNode(t, RightSon(t, p))))
    {
        /* hoja */
        printf("%c (0x%02X): %d\n", e.b, (unsigned char)e.b, e.frec);
    }
    else
    {
        /* nodo interno */
        printf("[%d]\n", e.frec);
    }

    /* imprimir subárbol izquierdo (abajo) */
    PrintTreeVisual(t, LeftSon(t, p), depth + 1);
}

/*
PrintTree

Descripción:
    Imprime el árbol completo a partir de la raíz.

Parámetros:
    - arbol_binario t: referencia al arbol a imprimir
*/
void PrintTree(arbol_binario *t)
{
    PrintTreeVisual(t, Root(t), 0);
}
