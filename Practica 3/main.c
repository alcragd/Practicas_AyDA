#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "lib/huffman/huffman.h"
#include "lib/file/compresor.h"


void PrintLeaves(arbol_binario *t, posicion p);
void PrintTreeVisual(arbol_binario *t, posicion p, int depth);
void PrintTree(arbol_binario *t);

int main(int argc, char** argv){
    if(argc != 2){
        printf("Error al leer datos");
        return 1; 
    }
    char* name;
    
    sscanf(argv[1],"%[^.]",name);

    char* Codigos[256]={0};
    
    readFile rf = readF(argv[1]);
    printf("El archivo se leyo correctamente \n");

    arbol_binario tree;

    int bytesExistentes=buildHuffmanTree(&tree,rf.frecuencias);
    byteCode *bc=getHuffmanCod(&tree,bytesExistentes);
  
    for(int i=0;i<bytesExistentes;++i){
        //printf("%c: %s\n",bc[i].b,bc[i].codigo);
        Codigos[bc[i].b]=bc[i].codigo;
    }
    // for(int i=0;i<256;++i)
    //     printf("%d: %s\n",i,Codigos[i]);


    strcat(name,"_compressed.dat");
    compress(rf.bytes,rf.num_elements,Codigos,name);

    //PrintTree(&tree);

    return 0;
}



void PrintLeaves(arbol_binario *t, posicion p)
{
    if (p == NULL || NullNode(t, p))
        return;

    posicion l = LeftSon(t, p);
    posicion r = RightSon(t, p);

    // Si ambos hijos son nulos/invalidos -> es hoja
    if ((l == NULL || NullNode(t, l)) && (r == NULL || NullNode(t, r))) {
        elemento e = ReadNode(t, p);
        // imprime byte y frecuencia (formato ajustable)
        printf("%c: 0x%02X: %d\n", e.b,e.b, e.frec);
        return;
    }

    PrintLeaves(t, l);
    PrintLeaves(t, r);
}

/* Imprime el árbol visualmente rotado 90° hacia la izquierda.
   - RightSon aparece arriba, Root en el centro, LeftSon abajo.
   - depth controla la indentación (llamar con 0).
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
        printf("%c (0x%02X): %d\n",e.b,(unsigned char)e.b, e.frec);
    }
    else
    {
        /* nodo interno */
        printf("[%d]\n", e.frec);
    }

    /* imprimir subárbol izquierdo (abajo) */
    PrintTreeVisual(t, LeftSon(t, p), depth + 1);
}

/* Wrapper conveniente */
void PrintTree(arbol_binario *t)
{
    PrintTreeVisual(t, Root(t), 0);
}
