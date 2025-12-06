/*
================================================================================
compresor.c
Versión: 1.0
Fecha: Junio 2025
Autores: Coyol Moreno Angel Zoe
         Ramirez Hernandez Christian Isaac
         Ramos Mendoza Miguel Angel


Descripción:
------------
Implementación de funciones para lectura de archivos y compresión de un flujo
de bytes usando códigos binarios representados como cadenas de '0'/'1'.

Funciones implementadas:
- readF     : lectura binaria completa del archivo y cálculo de frecuencias.
- compress  : empaqueta los códigos bit a bit y escribe los bytes resultantes.

Observaciones:
--------------
- Las funciones reportan errores por consola y terminan el programa (exit) en
  fallas críticas de E/S o asignación de memoria.
- El empaquetado es MSB-first dentro de cada byte (primer bit escrito va al
  bit 7 del primer byte resultante).
- El archivo de salida no contiene metadatos; si se requiere información para
  descompresión (tabla de códigos, tamaño original), debe ser gestionada
  externamente.

Compilación:
------------
gcc -c compresor.c

================================================================================
*/

#include "compresor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
compress

Descripción: Escribe en 'fileName' la secuencia de bits resultante de
             concatenar los códigos de cada byte del arreglo 'bytes'.
Parámetros:
    bytes        : datos de entrada a codificar.
    num_elements : número de bytes en 'bytes'.
    codigo       : tabla de códigos; codigo[b] es la cadena de '0'/'1' para b.
    fileName     : nombre del archivo de salida (binario).

Comportamiento:
    - Calcula el número total de bits que producirá la codificación.
    - Reserva el buffer de bytes empaquetados y llena cada byte con 8 bits
      (MSB-first). Si los bits totales no son múltiplo de 8, el último byte
      se rellena por ceros en los bits menos significativos.
    - Escribe el buffer resultante en el archivo en modo binario.
    - En caso de error de escritura o creación del archivo termina el programa.
*/
void compress(unsigned char *bytes, long long num_elements,  char *codigo[256], char* fileName){

    long long size_bits = 0;
    for(long long i = 0; i < num_elements; i++){
        char *temp = codigo[bytes[i]];
        int j=0;
        while(temp[j++] != '\0') size_bits++;
    }

    /* número de bytes necesarios para almacenar los bits */
    long long out_size = (size_bits + 7) / 8;

    int count_bit = 0, code_pos = 0;
    unsigned char tmp_byte = 0;
    unsigned char *compress = malloc(out_size * sizeof(unsigned char));
    if (compress == NULL) {
        printf("Error al reservar memoria para compresión\n");
        exit(1);
    }

    long long written_bytes = 0; /* índice en buffer de salida */

    for(long long i = 0; i < num_elements; i++){
        char *hoffman = codigo[bytes[i]];
        code_pos = 0;

        while(hoffman[code_pos] != '\0'){
            if(hoffman[code_pos] == '1')
                tmp_byte |= (1 << (7 - count_bit));
            code_pos++;
            count_bit++;

            if(count_bit == 8){
                compress[written_bytes++] = tmp_byte;
                count_bit = 0;
                tmp_byte = 0;
            }
        }
    }
    if(count_bit > 0){
        compress[written_bytes++] = tmp_byte;
    }

    FILE * file = fopen(fileName, "wb");
    if(file == NULL){
        printf("Error al crear el archivo de salida: %s\n", fileName);
        free(compress);
        exit(1);
    }

    long long written = fwrite(compress, sizeof(unsigned char), written_bytes, file);
    if (written != written_bytes) {
        printf("Error al escribir el archivo\n");
        fclose(file);
        free(compress);
        exit(1);
    }

    fflush(file);
    fclose(file);
    free(compress);
}

/*
readF

Descripción:
    Abre en modo binario el archivo 'name', obtiene su tamaño, lee todos los
    bytes en memoria dinámica y calcula la frecuencia de cada símbolo.

Parámetros:
    name : ruta al archivo a leer (cadena terminada en '\0').

Devuelve:
    readFile con los campos:
      - bytes apuntando al buffer (heap),
      - frecuencias con el conteo por símbolo,
      - num_elements con el número de bytes leídos.

Comportamiento en errores:
    - Si falla abrir el archivo o reservar memoria imprime un mensaje y sale
      con exit(1).
*/
readFile readF(char *name){
    FILE * file = fopen(name, "rb");
    if(file == NULL){
        printf("Error al abrir el archivo: %s\n", name);
        exit(1);
    }

    readFile rf = {0}; /* inicializa miembros a 0 */

    if (fseek(file, 0, SEEK_END) != 0) {
        printf("Error al buscar fin de archivo\n");
        fclose(file);
        exit(1);
    }
    rf.num_elements = ftell(file);
    if (rf.num_elements < 0) {
        printf("Error al obtener tamaño del archivo\n");
        fclose(file);
        exit(1);
    }
    rewind(file);

    rf.bytes = malloc(sizeof(unsigned char) * rf.num_elements);
    if(rf.bytes == NULL){
        printf("Error al reservar memoria\n");
        fclose(file);
        exit(1);
    }

    size_t read_count = fread(rf.bytes, sizeof(unsigned char), rf.num_elements, file);
    if ((long long)read_count != rf.num_elements) {
        printf("Error al leer archivo: se esperaba %lld bytes, leidos %zu\n", rf.num_elements, read_count);
        free(rf.bytes);
        fclose(file);
        exit(1);
    }

    fclose(file);

    for(long long i = 0; i < rf.num_elements; i++){
        rf.frecuencias[rf.bytes[i]]++;
    }
    
    return rf;
}

