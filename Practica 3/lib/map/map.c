// definitions of simple map functions on C
// Coyol Moreno Angel Zoe 2025
#include "map.h"


void mapInitialize(Map *m)
{
    m->size=0;
    m->capacity=4;
    m->data = malloc(m->capacity*sizeof(elem));
}
void mapInsert(Map *m,byte b)
{
    int i=mapSearch(m,b);
    if(i!=-1)
        m->data[i].count++;
    else {
        if(m->size == m->capacity)
            mapResize(m);

        m->data[m->size].b=b;
        m->data[m->size++].count=1;
    }
    return;
}
int mapSearch(Map *m,byte b)
{
    for(int i=0;i<m->size;++i)
        if(m->data[i].b==b) return i;
    return -1;
}
void mapDelete(Map *m,byte b)
{
    //...
}
void mapResize(Map *m)
{
    m->capacity<<1;
    m->data = realloc(m->data,m->capacity * sizeof(elem));
}