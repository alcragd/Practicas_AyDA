#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    unsigned char *bytes;
    int frecuencias[256];
    long long num_elements;
}readFile;

readFile readF(char *name);