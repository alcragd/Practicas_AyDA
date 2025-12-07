/*================================================================================
huffman.c
Versión: 1.2
Fecha: Junio 2025
Autores: Coyol Moreno Angel Zoe
         Ramirez Hernandez Christian Isaac
         Ramos Mendoza Miguel Angel
Documentación: Coyol Moreno Angel Zoe

Descripción:
------------
Implementación de utilidades para construir el árbol de Huffman a partir de un
conteo de frecuencias y para generar la tabla de códigos binarios por símbolo.

Funciones principales:
- buildHuffmanTree : construye el árbol de Huffman combinando nodos de menor frecuencia.
- getHuffmanCod    : recorre el árbol y devuelve los códigos binarios para cada hoja.
- huffmanCodRec    : función recursiva que arma los códigos.
- cmpFreq          : comparador para ordenar árboles por frecuencia.

Observaciones:
--------------
- Se usa el TAD arbol_binario (bintree.h). Los nodos de hojas contienen el
  símbolo original en elemento.b y su frecuencia en elemento.frec.
- Las estructuras auxiliares usadas durante la construcción se liberan, el
  árbol final se devuelve en *tree.
- Las cadenas de código devueltas por getHuffmanCod están alocadas dinámicamente;
  el llamador debe liberarlas.
================================================================================*/

#include "huffman.h"

/*
buildHuffmanTree

Construye el árbol de Huffman a partir del arreglo de frecuencias.
Algoritmo:
 - Crea una lista de árboles (cada árbol es una hoja con la frecuencia del símbolo).
 - Ordena la lista por frecuencia.
 - Repite: toma los dos árboles de menor frecuencia, crea un nuevo padre cuya
   frecuencia es la suma, y adjunta los dos como hijos izquierdo/derecho.
 - Continúa hasta obtener un único árbol.

Retorna el número de hojas (símbolos distintos).
*/
int buildHuffmanTree(arbol_binario *tree, int frec[256])
{
    int bytesExistentes = 0;
    for (int i = 0; i < 256; ++i)
        if (frec[i] > 0) bytesExistentes++;

    arbol_binario **list = malloc(bytesExistentes * sizeof(arbol_binario *));
    if (!list) exit(1);

    for (int i = 0, j = 0; i < 256; ++i)
    {
        if (frec[i] == 0) continue;

        list[j] = malloc(sizeof(arbol_binario));
        if (!list[j])  exit(1);

        Initialize(list[j]);
        elemento e = {(byte)i, frec[i]};
        NewRightSon(list[j], NULL, e);   /* crea una raíz-hoja con el símbolo */
        ++j;
    }

    qsort(list, bytesExistentes, sizeof(arbol_binario *), cmpFreq);

    int r=bytesExistentes;

    while (bytesExistentes > 1)
    {
        arbol_binario *izq = list[0];
        arbol_binario *der = list[1];

        int f1 = ReadNode(izq, Root(izq)).frec;
        int f2 = ReadNode(der, Root(der)).frec;

        arbol_binario *padre = malloc(sizeof(arbol_binario));
        Initialize(padre);
        elemento e = {0, f1 + f2};
        NewRightSon(padre, NULL, e);     

        AttachLeftSubtree(padre, Root(padre), *izq);
        AttachRightSubtree(padre, Root(padre), *der);

        free(izq);
        free(der);

        list[0] = padre;

        for (int i = 1; i < bytesExistentes - 1; ++i)
            list[i] = list[i + 1];
    
        qsort(list, --bytesExistentes, sizeof(arbol_binario *), cmpFreq);
    }

    *tree = *(list[0]);
    free(list[0]);
    free(list);
    return r;
}

/*
getHuffmanCod

Genera la tabla de códigos binarios recorriendo el árbol de Huffman.
Reserva un arreglo de byteCode con num_elem posiciones y usa huffmanCodRec
para llenar el arreglo.
*/
byteCode* getHuffmanCod(arbol_binario *tree,int num_elem){
    byteCode *r = malloc(num_elem * sizeof(byteCode));
    if (!r) return NULL;
    int i = 0;
    char buf[512]; 
    buf[0] = '\0';
    huffmanCodRec(tree, Root(tree), r, &i, buf, 0, num_elem);
    return r;
}

/*
huffmanCodRec

Recorrido recursivo en preorden que construye los códigos:
 - Si el nodo es hoja: copia el contenido de buf (hasta depth) en una nueva cadena
   y la asigna a arr[*i].codigo junto con el byte arr[*i].b.
 - Si no es hoja: escribe '0' en buf[depth] y desciende a la izquierda; escribe
   '1' en buf[depth] y desciende a la derecha.

Parámetros:
 - t, p : árbol y posición actual.
 - arr  : arreglo de salida.
 - i    : índice actual en arr (puntero, se incrementa al añadir una hoja).
 - buf  : buffer temporal para construir el código.
 - depth: nivel actual (posición en buf).
 - n    : tamaño máximo de arr (seguridad).
*/
void huffmanCodRec(arbol_binario* t, posicion p, byteCode *arr, int *i, char *buf, int depth, int n){
    if (p == NULL || NullNode(t, p) || *i >= n)
        return;

    posicion l = LeftSon(t, p);
    posicion r = RightSon(t, p);

   
    if ((l == NULL || NullNode(t, l)) && (r == NULL || NullNode(t, r))) {
        elemento e = ReadNode(t, p);
        buf[depth] = '\0';
        int len = depth + 1;
        char *code = malloc(len);
        memcpy(code, buf, depth);
        code[depth] = '\0';
        arr[*i].b = e.b;
        arr[*i].codigo = code;
        (*i)++;
        return;
    }

    
    buf[depth] = '0';
    huffmanCodRec(t, l, arr, i, buf, depth + 1, n);

    buf[depth] = '1';
    huffmanCodRec(t, r, arr, i, buf, depth + 1, n);

    buf[depth] = '\0';
}

/*
cmpFreq

Comparador usado por qsort. Recupera la frecuencia almacenada en la raíz de
cada arbol_binario y las compara para ordenar de menor a mayor.
*/
int cmpFreq(const void *a, const void *b)
{
    arbol_binario *A = *(arbol_binario **)a;
    arbol_binario *B = *(arbol_binario **)b;

    int fa = ReadNode(A, Root(A)).frec;
    int fb = ReadNode(B, Root(B)).frec;

    return (fa > fb) - (fa < fb);
}


int getCoddedTree(arbol_binario *huff_tree, byte** out){
  char buff[1024];  
  int i = 0,size_bits,size_bytes;
  
  getCoddedTree_dfs(huff_tree, Root(huff_tree), buff, &i);
  buff[i] = '\0';  

  //printf("%s",buff);

  size_bits = getPackedSize(buff,i);
  size_bytes = (size_bits+7)/8;

  byte tmp_byte = 0;       
  int bitCount = 0;      
  int pos = 0;            

  *out = malloc(sizeof(byte) * size_bytes);  
  if (*out == NULL) return -1;  

  for (int j = 0; j < i; j++) {
      if (buff[j] == '0' || buff[j] == '1') {
          int bit = buff[j] - '0';
          tmp_byte = (tmp_byte << 1) | (bit & 1);
          bitCount++;

          if (bitCount == 8) {
              (*out)[pos++] = tmp_byte;  
              tmp_byte = 0;
              bitCount = 0;
          }
      } else {
          byte value = (byte)buff[j];
          for (int b = 7; b >= 0; b--) {  
              int bit = (value >> b) & 1;
              tmp_byte = (tmp_byte << 1) | bit;
              bitCount++;

              if (bitCount == 8) {
                  (*out)[pos++] = tmp_byte;  
                  tmp_byte = 0;
                  bitCount = 0;
              }
          }
      }
  }

  if (bitCount > 0) {
      tmp_byte <<= (8 - bitCount);  
      (*out)[pos++] = tmp_byte;  
  }
 
  return size_bits;

}

void getCoddedTree_dfs(arbol_binario *t, posicion p,char* buff,int *i){
  if (p == NULL || NullNode(t, p))
    return;

  posicion l = LeftSon(t, p);
  posicion r = RightSon(t, p);

  if (NullNode(t, l) && NullNode(t, r)) {
    elemento e = ReadNode(t,p);
    buff[(*i)++]='1';
    buff[(*i)++]=(char)e.b;
    return;
  }

  buff[(*i)++]='0';
  getCoddedTree_dfs(t,l,buff,i);
  getCoddedTree_dfs(t,r,buff,i);
}


int getPackedSize(char *buff, int len) {
  int bits=0;

  for(int i=0;i<len;++i)
    if(buff[i] == '0' || buff[i] == '1') bits++;
    else bits+=8;

    return bits;
}