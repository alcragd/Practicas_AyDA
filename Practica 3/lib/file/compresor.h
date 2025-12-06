#ifndef COMPRESOR_H
#define COMPRESOR_H

#include <stdio.h>
#include <stdlib.h>
#include "../huffman/huffman.h"


void compress(unsigned char *byte, long long num_elements,  char *codigo[256], char* );

#endif