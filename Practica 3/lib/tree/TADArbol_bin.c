
/*
================================================================================
tadarbolbin.c
Versión: 1.0
Fecha: Junio 2025
Autor: Edgardo Adrián Franco Martínez - Mayo 2021
Documentación: Coyol Moreno Angel Zoe

Descripción:
------------
Este archivo contiene la implementación del TAD Árbol Binario (tadarbolbin.h).
Un árbol binario es una estructura de datos dinámica en la que cada nodo tiene
a lo sumo dos hijos, denominados hijo izquierdo e hijo derecho.

Observaciones:
--------------
- El TAD Árbol Binario permite operaciones de inserción, recorrido, búsqueda,
  y eliminación de nodos.
- La implementación es dinámica, utilizando nodos enlazados.
- Los nodos contienen un elemento y apuntadores a sus hijos izquierdo y derecho,
  así como a su padre (si aplica).

Compilación:
------------
gcc TADArbol_bin.c -c

================================================================================
*/

// LIBRERÍAS
#include "TADArbol_bin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***************************************************
Operaciones de construcción
***************************************************/

/*
void Initialize(arbol_binario *a)

Descripción: Inicializa un árbol binario para su uso.
Recibe: arbol *a (Referencia al árbol a operar)
Devuelve: Nada
Observaciones: El usuario debe crear el árbol y pasar la referencia.
*/
void Initialize(arbol_binario *a)
{
	*a = NULL;
	return;
}

/*
void Destroy(arbol_binario *a)

Descripción: Destruye un árbol binario, liberando toda la memoria utilizada.
Recibe: arbol *a (Referencia al árbol a operar)
Devuelve: Nada
Observaciones: El usuario debe crear el árbol y pasar la referencia.
*/
void Destroy(arbol_binario *a)
{
	if (*a != NULL)
	{
		if ((*a)->izq != NULL)
			Destroy(&((*a)->izq));
		if ((*a)->der != NULL) //(*(*a))).der
			Destroy(&((*a)->der));
		free(*a);
		*a = NULL;
	}
	return;
}

/***************************************************
Operaciones de modificaicón
***************************************************/

/*
void NewRightSon(arbol_binario *a, posicion p, elemento e)

Descripción: Inserta un nuevo hijo derecho en la posición p del árbol.
Recibe: arbol_binario *a (Referencia al árbol), posicion p (nodo padre), elemento e (elemento a insertar)
Devuelve: Nada
Observaciones: Si el árbol está vacío, el nuevo nodo será la raíz.
*/
void NewRightSon(arbol_binario *a, posicion p, elemento e)
{
	if (Empty(&(*a)))
	{
		*a = malloc(sizeof(nodo));
		if (*a == NULL)
		{
			printf("ERROR: NewRightSon(a,p,e) desbordamiento del arbol");
			exit(1);
		}
		(*a)->e = e;
		(*a)->der = NULL;
		(*a)->izq = NULL;
	}
	else
	{
		if (!NullNode(&(*a), p))
		{
			if (p->der != NULL)
			{
				printf("ERROR: NewRightSon(a,p,e) p ya tiene un hijo derecho");
				exit(1);
			}
			p->der = malloc(sizeof(nodo));
			p->der->e = e;
			p->der->der = NULL;
			p->der->izq = NULL;
		}
		else
		{
			printf("ERROR (NewRightSon):La posición dada no es valida");
			exit(1);
		}
	}
	return;
}

/*
void NewLeftSon(arbol_binario *a, posicion p, elemento e)

Descripción: Inserta un nuevo hijo izquierdo en la posición p del árbol.
Recibe: arbol_binario *a (Referencia al árbol), posicion p (nodo padre), elemento e (elemento a insertar)
Devuelve: Nada
Observaciones: Si el árbol está vacío, el nuevo nodo será la raíz.
*/
void NewLeftSon(arbol_binario *a, posicion p, elemento e)
{
	if (Empty(&(*a)))
	{
		*a = malloc(sizeof(nodo));
		(*a)->e = e;
		(*a)->der = NULL;
		(*a)->izq = NULL;
	}
	else
	{
		if (!NullNode(&(*a), p))
		{
			if (p->izq != NULL)
			{
				printf("ERROR: NewLeftSon(a,p,e) p ya tiene un hijo izquierdo");
				exit(1);
			}
			p->izq = malloc(sizeof(nodo));
			p->izq->e = e;
			p->izq->der = NULL;
			p->izq->izq = NULL;
		}
		else
		{
			printf("ERROR (NewLeftSon):La posición dada no es valida");
			exit(1);
		}
	}

	return;
}

/*
void DeleteRightSon(arbol_binario *a, posicion p)

Descripción: Elimina el hijo derecho del nodo en la posición p.
Recibe: arbol_binario *a (Referencia al árbol), posicion p (nodo padre)
Devuelve: Nada
Observaciones: Libera la memoria de todo el subárbol derecho.
*/
void DeleteRightSon(arbol_binario *a, posicion p)
{
	if (!NullNode(&(*a), p))
	{
		Destroy(&(p->der));
		p->der = NULL;
	}
	else
	{
		printf("ERROR (DeleteRightSon):La posición dada no es valida");
		exit(1);
	}
	return;
}

/*
void DeleteLeftSon(arbol_binario *a, posicion p)

Descripción: Elimina el hijo izquierdo del nodo en la posición p.
Recibe: arbol_binario *a (Referencia al árbol), posicion p (nodo padre)
Devuelve: Nada
Observaciones: Libera la memoria de todo el subárbol izquierdo.
*/
void DeleteLeftSon(arbol_binario *a, posicion p)
{
	if (!NullNode(&(*a), p))
	{
		Destroy(&(p->izq));
		p->izq = NULL;
	}
	else
	{
		printf("ERROR (DeleteLeftSon):La posición dada no es valida");
		exit(1);
	}
	return;
}

/*
void DeleteNode(arbol_binario *a, posicion p)

Descripción: Elimina el nodo en la posición p del árbol.
Recibe: arbol_binario *a (Referencia al árbol), posicion p (nodo a eliminar)
Devuelve: Nada
Observaciones: Libera la memoria del nodo y actualiza el puntero del padre.
*/
void DeleteNode(arbol_binario *a, posicion p)
{
	if (!NullNode(&(*a), p))
	{
		posicion padre = Parent(a, p);

		if (padre->der == p)
			padre->der = NULL;
		else if (padre->izq == p)
			padre->izq = NULL;
		Destroy(&p);
	}
	else
	{
		printf("ERROR (DeleteNode):La posición dada no es valida");
		exit(1);
	}
	return;
}

/*
void ReplaceNode(arbol_binario *a, posicion p, elemento e)

Descripción: Reemplaza el elemento almacenado en la posición p por el elemento e.
Recibe: arbol_binario *a (Referencia al árbol), posicion p (nodo a modificar), elemento e (nuevo elemento)
Devuelve: Nada
Observaciones: La posición p debe ser válida.
*/
void ReplaceNode(arbol_binario *a, posicion p, elemento e)
{
	if (!NullNode(&(*a), p))
	{
		p->e = e;
	}
	else
	{
		printf("ERROR (ReplaceNode):La posición dada no es valida");
		exit(1);
	}
	return;
}

/***************************************************
Operaciones de posicionamiento y búsqueda
***************************************************/

/*
posicion Root(arbol_binario *a)

Descripción: Devuelve la posición de la raíz del árbol.
Recibe: arbol_binario *a (Referencia al árbol)
Devuelve: posicion de la raíz (o NULL si el árbol está vacío)
Observaciones: El árbol debe estar inicializado.
*/
posicion Root(arbol_binario *a)
{
	return *a;
}

/*
posicion Parent(arbol_binario *a, posicion p)

Descripción: Devuelve la posición del padre del nodo p.
Recibe: arbol_binario *a (Referencia al árbol), posicion p (nodo hijo)
Devuelve: posicion del padre de p, o NULL si p es la raíz o no existe.
Observaciones: La posición p debe ser válida.
*/
posicion Parent(arbol_binario *a, posicion p)
{
	posicion padre = NULL;
	if (*a != NULL)
	{
		if ((*a)->der == p || (*a)->izq == p)
			return *a;
		if ((*a)->izq != NULL)
			padre = Parent(&((*a)->izq), p);
		if ((*a)->der != NULL && padre == NULL)
			padre = Parent(&((*a)->der), p);
	}
	else
	{
		printf("ERROR (Parent):La posición dada no es valida");
		exit(1);
	}
	return padre;
}

/*
posicion RightSon(arbol_binario *a, posicion p)

Descripción: Devuelve la posición del hijo derecho del nodo p.
Recibe: arbol_binario *a (Referencia al árbol), posicion p (nodo padre)
Devuelve: posicion del hijo derecho, o NULL si no existe.
Observaciones: La posición p debe ser válida.
*/
posicion RightSon(arbol_binario *a, posicion p)
{
	if (!NullNode(&(*a), p))
	{
		return p->der;
	}
	else
	{
		printf("ERROR (RightSon):La posición dada no es valida");
		exit(1);
	}
}

/*
posicion LeftSon(arbol_binario *a, posicion p)

Descripción: Devuelve la posición del hijo izquierdo del nodo p.
Recibe: arbol_binario *a (Referencia al árbol), posicion p (nodo padre)
Devuelve: posicion del hijo izquierdo, o NULL si no existe.
Observaciones: La posición p debe ser válida.
*/
posicion LeftSon(arbol_binario *a, posicion p)
{
	if (!NullNode(&(*a), p))
	{
		return p->izq;
	}
	else
	{
		printf("ERROR (LeftSon):La posición dada no es valida");
		exit(1);
	}
}

/*
posicion Search(arbol_binario *a, elemento e)

Descripción: Busca un nodo que contenga el elemento e en el árbol.
Recibe: arbol_binario *a (Referencia al árbol), elemento e (elemento a buscar)
Devuelve: posicion del nodo que contiene e, o NULL si no se encuentra.
Observaciones: La comparación se realiza con memcmp.
*/
posicion Search(arbol_binario *a, elemento e)
{
	posicion p = NULL;
	if (Empty(&(*a)))
		return p;
	if (memcmp(&((*a)->e), &e, sizeof(elemento)) == 0)
		return *a;
	if ((*a)->izq != NULL)
		p = Search(&((*a)->izq), e);
	if ((*a)->der != NULL && p == NULL)
		p = Search(&((*a)->der), e);

	return p;
}

/***************************************************
Operaciones de consulta
***************************************************/

/*
boolean Empty(arbol_binario *a)

Descripción: Verifica si el árbol está vacío.
Recibe: arbol *a (Referencia al árbol a operar)
Devuelve: TRUE si el árbol está vacío, FALSE en caso contrario.
Observaciones: El árbol debe estar correctamente inicializado.
*/
boolean Empty(arbol_binario *a)
{
	if (*a != NULL)
		return FALSE;
	else
		return TRUE;
}

/*
boolean NullNode(arbol_binario *a, posicion p)

Descripción: Verifica si la posición p es nula o no pertenece al árbol.
Recibe: arbol_binario *a (Referencia al árbol), posicion p (nodo a verificar)
Devuelve: TRUE si p es nulo o no pertenece al árbol, FALSE en caso contrario.
Observaciones: El árbol debe estar correctamente inicializado.
*/
boolean NullNode(arbol_binario *a, posicion p)
{
	boolean b = TRUE;
	if (*a == NULL || p == NULL)
		return TRUE;
	if (*a == p)
		return FALSE;
	if ((*a)->izq != NULL)
		b = NullNode(&((*a)->izq), p);
	if ((*a)->der != NULL && b == TRUE)
		b = NullNode(&((*a)->der), p);

	return b;
}

/*
elemento ReadNode(arbol_binario *a, posicion p)

Descripción: Devuelve el elemento almacenado en la posición p del árbol.
Recibe: arbol_binario *a (Referencia al árbol), posicion p (nodo del cual se obtiene el elemento)
Devuelve: elemento almacenado en la posición p.
Observaciones: La posición p debe ser válida y pertenecer al árbol.
*/
elemento ReadNode(arbol_binario *a, posicion p)
{
	if (!NullNode(&(*a), p))
	{
		return p->e;
	}
	else
	{
		printf("ERROR (ReadNode):La posición dada no es valida");
		exit(1);
	}
}
