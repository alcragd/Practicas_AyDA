#!/bin/bash

# === CONFIGURACIÓN ===

SRC_DIR="./"
OUT_DIR="./out"


echo "Compilando algoritmos..."
for file in "$SRC_DIR"/*.c; do
    base=$(basename "$file" .c)
    exe="${OUT_DIR}/${base}.out"
    if [[ "$base" == "HeapSort" ]]; then
        gcc "$file" heap/heap.c tiempo/tiempo.c -o "$exe"
    elif [[ "$base" == "TreeSort" ]]; then
        gcc "$file" abb/abb.c tiempo/tiempo.c -o "$exe"
    else
        gcc "$file" tiempo/tiempo.c -o "$exe"
    fi
done
echo "Compilación completada."