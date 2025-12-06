#ifndef COMPRESSOR_H
#define COMPRESSOR_H
#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    unsigned char *bytes;
    int frecuencias[256];
    long long num_elements;
}readFile;

readFile readF(char *name);
void compress(unsigned char *byte, long long num_elements,  char *codigo[256], char* fileName);

#endif //COMPRESSOR_H