// declarations of simple map functions on C
// Coyol Moreno Angel Zoe 2025

#include <stdio.h>
#include <stdlib.h>

#ifndef byte
    typedef unsigned char byte;
#endif
typedef struct elem {
    byte b;
    int count;
} elem;

typedef struct Map {
    elem *data;
    int size;
    int capacity; 
} Map;


void mapInitialize(Map *m);
void mapInsert(Map *m,byte b); // si no existe, insertarlo en el mapa, si existe, aumentar el numero de apariciones
int mapSearch(Map *m,byte b); // -1 si no está en el mapa, el indice en caso contrario
void mapDelete(Map *m,byte b); // self explanatory
void mapResize(Map *m);
