#!/bin/bash
# Compila los ejecutables en bin/
set -euo pipefail

CFLAGS="-O2"
BIN_DIR="bin"
mkdir -p "$BIN_DIR"

echo "Compilando (salida en $BIN_DIR/)..."

# Ajusta los archivos fuente si la estructura de carpetas difiere
gcc $CFLAGS -o "$BIN_DIR/busqueda_lineal" busqueda_lineal.c tiempo/tiempo.c
gcc $CFLAGS -o "$BIN_DIR/busqueda_lineal_t" threads/busqueda_lineal.c tiempo/tiempo.c


gcc $CFLAGS -o "$BIN_DIR/busqueda_binaria" busqueda_binaria.c tiempo/tiempo.c
gcc $CFLAGS -o "$BIN_DIR/busqueda_binaria_t" threads/busqueda_binaria.c tiempo/tiempo.c

gcc $CFLAGS -o "$BIN_DIR/busqueda_exponencial" busqueda_exponencial.c tiempo/tiempo.c
gcc $CFLAGS -o "$BIN_DIR/busqueda_exponencial_t" threads/busqueda_exp.c tiempo/tiempo.c

gcc $CFLAGS -o "$BIN_DIR/busqueda_fibonacci" busqueda_fibonacci.c tiempo/tiempo.c
gcc $CFLAGS -o "$BIN_DIR/busqueda_fibonacci_t" threads/busqueda_fibo.c tiempo/tiempo.c

gcc $CFLAGS -o "$BIN_DIR/busqueda_abb" busqueda_abb.c abb/abb.c tiempo/tiempo.c
gcc $CFLAGS -o "$BIN_DIR/busqueda_abb_t" threads/busqueda_abb.c abb/abb.c tiempo/tiempo.c


echo "✓ Compilación completada. Ejecutables:"
ls -lh "$BIN_DIR"/busqueda_* 2>/dev/null || true