#include "../tree/bintree.h"

#define TRUE 1
#define FALSE 0

#ifndef boolean
typedef unsigned char boolean;
#endif

typedef struct elem
{
	posicion p;
} elem;

typedef struct p_nodo
{
	elem e;
	struct p_nodo *abajo;
} p_nodo;

typedef struct pila
{
	int size;
	p_nodo *tope;
} pila;

/*
Inicializar pila (Initialize): recibe<- pila (S);
Initialize(S);
Efecto: Recibe una pila y la inicializa para su trabajo normal.
*/
void P_Initialize(pila *S);

/*
Empilar (Push): recibe<- pila (S); recibe<- elem (e)
Push(S,e);
Efecto: Recibe la pila y aumenta su tamaño, poniendo el elem en la cima de la pila.
*/
void P_Push(pila *S, elem e);

/*
Desempilar (Pop): recibe<- pila (S); retorna -> elem
e=Pop(S);
Efecto: Recibe la pila, remueve el elem tope y lo retorna.
Excepción: Si la pila esta vacía, produce error.
*/ elem P_Pop(pila *S);

/*
Es vacía (Empty): recibe<- pila (S); retorna -> boolean
b=Empty(S);
Efecto: Recibe una pila y devuelve true si esta vacía y false en caso contrario.
*/
boolean P_Empty(pila *S);

/*
Tope pila (Top): recibe<- pila (S); retorna -> elem
e=Top(S);
Efecto: Devuelve el elem cima de la pila.
Excepción: Si la pila esta vacía produce error
*/ elem P_Top(pila *S);

/*
Tamaño pila (Size): recibe<- pila (S); retorna -> tamaño de la pila (entero)
n=Size(S);
Efecto: Devuelve el número de elems que contiene la pila (Altura de la pila).
*/
int P_Size(pila *S);

/*
Eliminar pila (Destroy): recibe<- pila (S)
Destroy(S);
Efecto: Recibe una pila y la libera completamente
*/
void P_Destroy(pila *S);