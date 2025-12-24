/*================================================================================
bintree.h
Versión: 1.0
Fecha: Junio 2025
Autor: Edgardo Adrián Franco Martínez - Mayo 2021 - Diciembre 2025
Documentación: Coyol Moreno Angel Zoe

Descripción:
------------
Definición del TAD Árbol Binario. Proporciona la estructura de datos y las
funciones necesarias para la manipulación de árboles binarios dinámicos.

Observaciones:
--------------
- Cada nodo puede tener hasta dos hijos (izquierdo y derecho).
- Los nodos almacenan un elemento de tipo 'elemento'.
- Las operaciones permiten crear, modificar, consultar y destruir árboles binarios.

================================================================================
*/
#ifndef BINTREE_H
#define BINTREE_H

#define TRUE 1
#define FALSE 0

typedef unsigned char boolean;

#ifndef byte
    typedef unsigned char byte;
#endif

/*
Estructura que almacena el elemento de cada nodo del árbol.
Puede ser modificada según las necesidades del usuario.
*/
typedef struct elemento
{
	byte b;
	int frec;
} elemento;

/*
Estructura de un nodo del árbol binario.
Contiene el elemento y apuntadores a los hijos izquierdo y derecho.
*/
typedef struct nodo
{
	elemento e;
	struct nodo *izq;
	struct nodo *der;
} nodo;

/*
Tipo de dato para el árbol binario (puntero al nodo raíz).
*/
typedef nodo *arbol_binario;

/*
Tipo de dato para la posición de un nodo en el árbol.
*/
typedef nodo *posicion;

/*
Inicializa un árbol binario para su uso.
Recibe: arbol_binario *a (Referencia al árbol a operar)
Devuelve: Nada
*/
void Initialize(arbol_binario *a);

/*
Destruye un árbol binario, liberando toda la memoria utilizada.
Recibe: arbol_binario *a (Referencia al árbol a operar)
Devuelve: Nada
*/
void Destroy(arbol_binario *a);

/*
Devuelve la posición de la raíz del árbol.
Recibe: arbol_binario *a (Referencia al árbol)
Devuelve: posicion de la raíz (o NULL si el árbol está vacío)
*/
posicion Root(arbol_binario *a);

/*
Devuelve la posición del padre del nodo p.
Recibe: arbol_binario *a (Referencia al árbol), posicion p (nodo hijo)
Devuelve: posicion del padre de p, o NULL si p es la raíz o no existe.
*/
posicion Parent(arbol_binario *a, posicion p);

/*
Devuelve la posición del hijo derecho del nodo p.
Recibe: arbol_binario *a (Referencia al árbol), posicion p (nodo padre)
Devuelve: posicion del hijo derecho, o NULL si no existe.
*/
posicion RightSon(arbol_binario *a, posicion p);

/*
Devuelve la posición del hijo izquierdo del nodo p.
Recibe: arbol_binario *a (Referencia al árbol), posicion p (nodo padre)
Devuelve: posicion del hijo izquierdo, o NULL si no existe.
*/
posicion LeftSon(arbol_binario *a, posicion p);

/*
Busca un nodo que contenga el elemento e en el árbol.
Recibe: arbol_binario *a (Referencia al árbol), elemento e (elemento a buscar)
Devuelve: posicion del nodo que contiene e, o NULL si no se encuentra.
*/
posicion Search(arbol_binario *a, elemento e);

/*
Verifica si el árbol está vacío.
Recibe: arbol_binario *a (Referencia al árbol a operar)
Devuelve: TRUE si el árbol está vacío, FALSE en caso contrario.
*/
boolean Empty(arbol_binario *a);

/*
Verifica si la posición p es nula o no pertenece al árbol.
Recibe: arbol_binario *a (Referencia al árbol), posicion p (nodo a verificar)
Devuelve: TRUE si p es nulo o no pertenece al árbol, FALSE en caso contrario.
*/
boolean NullNode(arbol_binario *a, posicion p);

/*
Devuelve el elemento almacenado en la posición p del árbol.
Recibe: arbol_binario *a (Referencia al árbol), posicion p (nodo del cual se obtiene el elemento)
Devuelve: elemento almacenado en la posición p.
*/
elemento ReadNode(arbol_binario *a, posicion p);

/*
Inserta un nuevo hijo derecho en la posición p del árbol.
Recibe: arbol_binario *a (Referencia al árbol), posicion p (nodo padre), elemento e (elemento a insertar)
Devuelve: Nada
*/
void NewRightSon(arbol_binario *a, posicion p, elemento e);

/*
Inserta un nuevo hijo izquierdo en la posición p del árbol.
Recibe: arbol_binario *a (Referencia al árbol), posicion p (nodo padre), elemento e (elemento a insertar)
Devuelve: Nada
*/
void NewLeftSon(arbol_binario *a, posicion p, elemento e);

/*
Elimina el hijo derecho del nodo en la posición p y todos sus descendientes.
Recibe: arbol_binario *a (Referencia al árbol), posicion p (nodo padre)
Devuelve: Nada
*/
void DeleteRightSon(arbol_binario *a, posicion p);

/*
Elimina el hijo izquierdo del nodo en la posición p y todos sus descendientes.
Recibe: arbol_binario *a (Referencia al árbol), posicion p (nodo padre)
Devuelve: Nada
*/
void DeleteLeftSon(arbol_binario *a, posicion p);

/*
Elimina el nodo en la posición p y todos sus descendientes.
Recibe: arbol_binario *a (Referencia al árbol), posicion p (nodo a eliminar)
Devuelve: Nada
*/
void DeleteNode(arbol_binario *a, posicion p);

/*
Reemplaza el elemento almacenado en la posición p por el elemento e.
Recibe: arbol_binario *a (Referencia al árbol), posicion p (nodo a modificar), elemento e (nuevo elemento)
Devuelve: Nada
*/
void ReplaceNode(arbol_binario *a, posicion p, elemento e);

/*
void AttachLeftSubtree(arbol_binario *a, posicion p, arbol_binario sub)

Descripción: Adjunta el subárbol 'sub' como hijo izquierdo del nodo p.
Si el árbol está vacío, 'sub' se convierte en la raíz.
Nota: Transfiere la propiedad del subárbol (no copia nodos).
*/
void AttachLeftSubtree(arbol_binario *a, posicion p, arbol_binario sub);
/*
void AttachRightSubtree(arbol_binario *a, posicion p, arbol_binario sub)

Descripción: Adjunta el subárbol 'sub' como hijo derecho del nodo p.
Si el árbol está vacío, 'sub' se convierte en la raíz.
*/
void AttachRightSubtree(arbol_binario *a, posicion p, arbol_binario sub);

#endif