/*================================================================================
huffman.c
Versión: 1.2
Fecha: Diciembre 2025
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

/*
getCoddedTree

Descripción:
    Serializa la estructura del árbol de Huffman en un flujo de bits. Utiliza
    un recorrido DFS para representar nodos internos con '0' y hojas con '1' 
    seguido del valor del byte (8 bits).

Parámetros:
    huff_tree : Puntero al árbol de Huffman construido.
    out       : Puntero doble donde se asignará el buffer de bytes empaquetados.

Devuelve:
    Entero que representa la longitud total del árbol en bits. Retorna -1 si 
    falla la asignación de memoria.
*/
int getCoddedTree(arbol_binario *huff_tree, byte** out){
  char buff[4096];  // Buffer más grande
  int i = 0, size_bits, size_bytes;
  
  getCoddedTree_dfs(huff_tree, Root(huff_tree), buff, &i);
  
  size_bits = i;  // Ahora es simple: cada char es 1 bit
  size_bytes = (size_bits + 7) / 8;

  byte tmp_byte = 0;       
  int bitCount = 0;      
  int pos = 0;            

  *out = malloc(sizeof(byte) * size_bytes);  
  if (*out == NULL) return -1;  

  // Empacar los bits '0'/'1' en bytes
  for (int j = 0; j < i; j++) {
      int bit = buff[j] - '0';  // Convertir '0'->'0', '1'->'1'
      tmp_byte = (tmp_byte << 1) | (bit & 1);
      bitCount++;

      if (bitCount == 8) {
          (*out)[pos++] = tmp_byte;  
          tmp_byte = 0;
          bitCount = 0;
      }
  }

  if (bitCount > 0) {
      tmp_byte <<= (8 - bitCount);  
      (*out)[pos++] = tmp_byte;  
  }
 
  return size_bits;

}
/*
getCoddedTree_dfs

Descripción:
    Función auxiliar recursiva que realiza un recorrido en preorden para 
    generar una cadena de caracteres '0' y '1' que representa el árbol.

Parámetros:
    t    : Árbol binario procesado.
    p    : Posición actual en el recorrido.
    buff : Buffer temporal para almacenar la secuencia de bits como caracteres.
    i    : Índice del bit actual en el buffer.
*/
void getCoddedTree_dfs(arbol_binario *t, posicion p, char* buff, int *i){
  if (p == NULL || NullNode(t, p))
    return;

  posicion l = LeftSon(t, p);
  posicion r = RightSon(t, p);

  if (NullNode(t, l) && NullNode(t, r)) {
    // NODO HOJA: guardar como "1" + 8 bits del símbolo
    elemento e = ReadNode(t, p);
    buff[(*i)++] = '1';
    
    // Convertir e.b a 8 dígitos binarios
    for (int b = 7; b >= 0; b--) {
      int bit = (e.b >> b) & 1;
      buff[(*i)++] = (char)('0' + bit);  // '0' o '1'
    }
    return;
  }

  // NODO INTERNO: guardar como "0"
  buff[(*i)++] = '0';
  getCoddedTree_dfs(t, l, buff, i);
  getCoddedTree_dfs(t, r, buff, i);
}

int getPackedSize(char *buff, int len) {
  // Ahora buff contiene SOLO '0' y '1', sin bytes especiales
  return len;  // Cada carácter es 1 bit
}
/*
decodeTree

Descripción:
    Reconstruye un árbol de Huffman a partir de su representación serializada 
    leída de un archivo comprimido. Utiliza una pila para gestionar la 
    jerarquía de nodos durante la reconstrucción.

Parámetros:
    t          : Árbol binario donde se reconstruirá la estructura.
    codded_t   : Buffer de bytes que contiene el árbol empaquetado.
    tree_len   : Longitud del árbol en bits.
*/
void decodeTree(arbol_binario *t, byte *codded_t, unsigned short tree_len){
  pila S;
  P_Initialize(&S);
  int byte_idx = 0, bit_idx = 0;
  int bits_read = 0;

  while(bits_read < tree_len){
      int leaf = (codded_t[byte_idx] >> (7 - bit_idx)) & 1;
      bits_read++;
      bit_idx++;
      if(bit_idx >= 8){
        byte_idx++;
        bit_idx = 0;
      }

      if(!leaf){
          // NODO INTERNO
          if (P_Empty(&S)) { 
            Initialize(t); 
            NewRightSon(t, NULL, (elemento){0, 0}); 
            P_Push(&S, (elem){Root(t)}); 
          }
          else{
            posicion padre =P_Top(&S).p;
            arbol_binario tmp_tree;
            Initialize(&tmp_tree);
            NewRightSon(&tmp_tree, NULL, (elemento){0, 0});
            posicion newNode = Root(&tmp_tree);
            
            if(LeftSon(t, padre) == NULL) AttachLeftSubtree(t, padre, tmp_tree);
            else{
              AttachRightSubtree(t, padre, tmp_tree);
              P_Pop(&S);
            }
            P_Push(&S, (elem){newNode});
          }
        } 
        else{
          // NODO HOJA
          byte value = 0;
          for (int j = 0; j < 8; ++j){
            int bit = (codded_t[byte_idx] >> (7 - bit_idx)) & 1;
            value = (value << 1) | bit;
            bits_read++;
            bit_idx++;
            if(bit_idx >= 8){
              byte_idx++;
              bit_idx = 0;
            }
          }

          posicion padre = P_Top(&S).p;
          
          if(LeftSon(t, padre) == NULL) {
            NewLeftSon(t, padre, (elemento){value, 0});
          }
          else {
            NewRightSon(t, padre, (elemento){value, 0});
            P_Pop(&S);
          }     
      }
  }
  P_Destroy(&S);
}