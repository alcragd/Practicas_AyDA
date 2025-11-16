#!/bin/bash
# compile.sh
# Compila todos los algoritmos de búsqueda

echo "Compilando algoritmos de búsqueda..."

# Compilar con la librería de tiempo
gcc -O2 -o busqueda_lineal busqueda_lineal.c tiempo/tiempo.c
gcc -O2 -o busqueda_binaria busqueda_binaria.c tiempo/tiempo.c
gcc -O2 -o busqueda_exponencial busqueda_exponencial.c tiempo/tiempo.c
gcc -O2 -o busqueda_fibonacci busqueda_fibonacci.c tiempo/tiempo.c

# Compilar ABB (árbol binario de búsqueda)
gcc -O2 -o busqueda_abb busqueda_abb.c abb/abb.c tiempo/tiempo.c

echo "✓ Compilación completada"
echo "Ejecutables generados:"
ls -lh busqueda_* | awk '{print $9, "(" $5 ")"}'
