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

void file_compress(char* fileName,char* fileExt);
void file_decompress(char* fileName, char* outputName);

int main(int argc, char** argv){
    if(argc != 3){
        printf("Uso:\n");
        printf("  Comprimir:   %s archivo.ext 1\n", argv[0]);
        printf("  Descomprimir: %s archivo_compressed.dat 2\n", argv[0]);
        return 1; 
    }

    int opc = atoi(argv[2]);

    if(opc == 1)
    {
        char name[512] = {0};
        char ext[64] = {0};
        
        // Validar formato del nombre de archivo
        if (sscanf(argv[1], "%511[^.].%63s", name, ext) != 2) {
            printf("Error: formato de archivo inválido (esperado: nombre.extensión)\n");
            return 1;
        }

        file_compress(name, ext);
        printf("Compresión completada: %s_compressed.dat\n", name);
    }
    else if (opc == 2)
    {
        file_decompress(argv[1], "uncompressed");
    }
    else
    {
        printf("Error: opción inválida. Use 1 para comprimir, 2 para descomprimir\n");
        return 1;
    }

    return 0;
}


/*
file_decompress

Descripción:
    Orquestador del proceso de descompresión. Lee el archivo comprimido, extrae
    la cabecera (metadatos), reconstruye el árbol de Huffman y recupera el 
    archivo original.

Parámetros:
    fileName   : Ruta del archivo comprimido (.dat) a procesar.
    outputName : Nombre base que se le dará al archivo resultante.

Comportamiento:
    - Llama a readCompressedF para cargar el header (extensión, árbol, datos).
    - Valida la integridad de los datos leídos.
    - Invoca a la función de descompresión bit a bit.
    - Informa las estadísticas del archivo (tamaño del árbol, bits válidos).
    - Garantiza la liberación de toda la memoria dinámica del header (ext, 
      huff_tree y compressedData).
*/
void file_decompress(char* fileName, char* outputName){
    // Leer archivo comprimido
    fileHeader fh = readCompressedF(fileName);
    
    // Validar que se leyó correctamente
    if (fh.huff_tree == NULL || fh.tree_len == 0) {
        printf("Error: archivo comprimido inválido o corrupto\n");
        // Liberar memoria parcialmente asignada
        if (fh.ext != NULL) free(fh.ext);
        if (fh.huff_tree != NULL) free(fh.huff_tree);
        if (fh.compressedData != NULL) free(fh.compressedData);
        return;
    }
    
    printf("Archivo comprimido leído correctamente\n");
    printf("  Extensión: %s\n", fh.ext);
    printf("  Tamaño del árbol: %u bits\n", fh.tree_len);
    printf("  Datos comprimidos: %lld bytes\n", fh.compressedData_size);
    printf("  Bits válidos último byte: %u\n", fh.last_valid_bit);
    
    // Descomprimir
    decompress(fh, outputName);
    
    printf("Descompresión completada exitosamente\n");
    
    // Liberar memoria asignada por readCompressedF
    if (fh.ext != NULL) {
        free(fh.ext);
    }
    if (fh.huff_tree != NULL) {
        free(fh.huff_tree);
    }
    if (fh.compressedData != NULL) {
        free(fh.compressedData);
    }
}

/*
file_compress

Descripción:
    Orquestador del proceso de compresión. Lee un archivo original, construye
    el árbol de Huffman, genera los códigos binarios, serializa el árbol para
    la cabecera y finalmente genera el archivo comprimido (.dat).

Parámetros:
    fileName : Nombre del archivo base (sin extensión).
    fileExt  : Extensión original del archivo (ej. "txt", "jpg").

Comportamiento:
    - Carga el archivo completo a memoria y calcula frecuencias.
    - Genera un árbol de Huffman y su tabla de códigos asociada.
    - Serializa la estructura del árbol en un formato bitstream para incluirlo en el header.
    - Crea un archivo de salida con el sufijo "_compressed.dat".
    - Libera la memoria dinámica utilizada para la extensión y el árbol codificado.
*/
void file_compress(char* fileName,char* fileExt){
   
    char* Codigos[256] = {0};


    char f[576] = {0};
    sprintf(f,"%s.%s",fileName,fileExt);

    readFile rf = readF(f);
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
    char outname[600];
    snprintf(outname, sizeof(outname), "%s_compressed.dat", fileName);

    byte *codded_tree = NULL;  

    fileHeader fh;
    size_t ext_len = strlen(fileExt);

    fh.ext = malloc(ext_len + 1);  
    if (fh.ext == NULL) {
        fprintf(stderr, "Error: no se pudo asignar memoria para extensión\n");
        return;
    }

    strcpy(fh.ext, fileExt);
    fh.ext_size = ext_len;
    fh.tree_len = getCoddedTree(&tree, &codded_tree); 
    fh.huff_tree = codded_tree;

    /* realiza la compresión y escribe el archivo de salida */
    compress(rf.bytes, rf.num_elements, Codigos, outname, fh);

    // Liberar memoria al final
    free(fh.ext);
    free(codded_tree);
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
