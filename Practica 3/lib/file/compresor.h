/*================================================================================
compresor.h
Versión: 1.0
Fecha: Diciembre 2025
Autores: Coyol Moreno Angel Zoe
         Ramirez Hernandez Christian Isaac
         Ramos Mendoza Miguel Angel

Descripción:
------------
Interfaz para utilidades de lectura de archivos y compresión por códigos
(uso esperado: códigos tipo Huffman representados como cadenas de '0' y '1').

Contenido:
- readFile : estructura con bytes leídos del archivo y frecuencias por símbolo.
- readF    : lee un archivo binario y devuelve su contenido + frecuencias.
- compress : escribe en disco una secuencia de bits codificados por bytes.

Observaciones:
--------------
- La implementación asume códigos de longitud variable representados como
  cadenas terminadas en '\0' en codigo[0..255].
- Los archivos se abren en modo binario.
- La función compress empaqueta bits MSB-first en cada byte (bit 7 -> primer bit).
- El caller es responsable de liberar readFile.bytes cuando ya no se usa.

Compilación:
------------
gcc -c compresor.c

================================================================================*/
#ifndef COMPRESSOR_H
#define COMPRESSOR_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../tree/bintree.h"
#include "../huffman/huffman.h"



/*
readFile

Estructura que contiene:
- bytes        : buffer con los bytes leidos del archivo.
- frecuencias  : contador por cada valor de byte [0..255].
- num_elements : número total de bytes leídos.

Notas:
- bytes debe liberarse por el llamador (free).
*/

#ifndef byte
    typedef unsigned char byte;
#endif

typedef struct 
{
    unsigned char *bytes;
    int frecuencias[256];
    long long num_elements;
}readFile;

typedef struct {
    byte ext_size; // 1 byte
    char* ext;  // ext_size bytes
    uint16_t tree_len; // 2 bytes
    byte *huff_tree;   // tree_len bytes
    byte last_valid_bit; // 1 byte
    byte *compressedData; // idk bytes

    long long compressedData_size;  // AGREGAR ESTO

} fileHeader;

/*
readF

Descripción:
    Lee el archivo binario indicado por 'name' y devuelve una estructura readFile
    con los bytes en memoria y el conteo de frecuencias por símbolo.

Recibe:
    char *name : ruta al archivo a leer (cadena terminada en '\0').

Devuelve:
    readFile con los campos llenos. Si hay error de E/S la función termina el
    programa (exit) después de imprimir un mensaje de error.

Observaciones:
    - El buffer bytes está alocado dinámicamente; el llamador debe liberarlo.
*/
readFile readF(char *name);

/*
compress

Descripción:
    Escribe en 'outputName' la secuencia de bits codificados salvo empaquetados
    por bytes. Las cadenas en 'codigo' deben representar los códigos binarios
    ('0'/'1') terminados en '\0'.

Recibe:
    unsigned char *byte  : arreglo de bytes a codificar.
    long long num_elements : número de elementos en 'byte'.
    char *codigo[256]    : arreglo de punteros a cadenas de código para cada símbolo.
    char *outputName       : ruta de salida (archivo binario).

Devuelve:
    Ninguno. En caso de error en escritura termina el programa (exit).

Observaciones:
    - El formato del archivo de salida es solo los bytes comprimidos (sin cabecera).
      Si se requiere información adicional (tabla de códigos, tamaño original),
      debe añadirse por el llamador.
*/
void compress(unsigned char *byte, long long num_elements,  char *codigo[256], char* outputName,fileHeader h);
/*
readCompressedF

Descripción:
    Lee un archivo con formato comprimido personalizado. Extrae la extensión 
    original, el árbol de Huffman serializado, el indicador de bits válidos 
    y el cuerpo de datos comprimidos.

Parámetros:
    fileN : Ruta del archivo comprimido (.dat).

Devuelve:
    Estructura fileHeader con todos los campos poblados y memoria dinámica 
    asignada para los datos. Termina el programa en caso de error de lectura.
*/
fileHeader readCompressedF(char *fileN);
/*
decompress

Descripción:
    Realiza la descompresión lógica del archivo. Utiliza el árbol reconstruido 
    para navegar bit a bit a través de los datos comprimidos hasta identificar 
    hojas (bytes originales) y escribirlos en el archivo de salida.

Parámetros:
    fh   : Estructura de cabecera con los datos y el árbol necesario.
    name : Nombre base para el archivo de salida (se le concatenará la extensión original).

Comportamiento:
    - Crea el archivo de salida con la extensión recuperada del header.
    - Traduce el flujo de bits navegando por el árbol desde la raíz.
    - Maneja el caso especial del último byte usando last_valid_bit.
*/
void decompress(fileHeader fh, char* name);


#endif /*COMPRESSOR_H*/