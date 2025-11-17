#!/bin/bash
# generate_data.sh
# Prepara archivos de datos para benchmark usando Ordenado.txt existente
# Uso: ./generate_data.sh

OUTPUT_DIR="benchmark_data"
mkdir -p "$OUTPUT_DIR"

# Archivos fuente
SOURCE_SORTED="../NumerosOrdenados/Ordenado.txt"
SOURCE_UNSORTED="../numeros10millones.txt"

# Verificar que los archivos existen
if [ ! -f "$SOURCE_SORTED" ]; then
    echo "ERROR: Archivo no encontrado: $SOURCE_SORTED"
    echo "Por favor asegúrate que existe: NumerosOrdenados/Ordenado.txt"
    exit 1
fi

if [ ! -f "$SOURCE_UNSORTED" ]; then
    echo "ERROR: Archivo no encontrado: $SOURCE_UNSORTED"
    echo "Por favor asegúrate que existe: numeros10millones.txt"
    exit 1
fi

echo "✓ Archivo ordenado encontrado: $SOURCE_SORTED"
wc -l "$SOURCE_SORTED"
echo "✓ Archivo sin ordenar encontrado: $SOURCE_UNSORTED"
wc -l "$SOURCE_UNSORTED"

# Valores de búsqueda
SEARCH_VALUES=(322486 14700764 3128036 6337399 61396 10393545 2147445644 1295390003 450057883 187645041 1980098116 152503 5000 1493283650 214826 1843349527 1360839354 2109248666 2147470852 0)

# Crear archivos de datos de 1M a 10M elementos
# - data_sorted_*: desde Ordenado.txt (para binaria, exponencial, fibonacci)
# - data_unsorted_*: desde numeros10millones.txt (para lineal y ABB)
for n in 1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000; do
    output_file_sorted="$OUTPUT_DIR/data_sorted_${n}.txt"
    output_file_unsorted="$OUTPUT_DIR/data_unsorted_${n}.txt"
    
    echo "Generando $output_file_sorted con los primeros $n números (ordenados)..."
    head -n $n "$SOURCE_SORTED" > "$output_file_sorted"
    line_count=$(wc -l < "$output_file_sorted")
    if [ "$line_count" -eq "$n" ]; then
        echo "✓ Completado: $output_file_sorted ($line_count líneas)"
    else
        echo "⚠ ADVERTENCIA: Se obtuvieron $line_count líneas en lugar de $n"
    fi
    
    echo "Generando $output_file_unsorted con los primeros $n números (sin ordenar)..."
    head -n $n "$SOURCE_UNSORTED" > "$output_file_unsorted"
    line_count=$(wc -l < "$output_file_unsorted")
    if [ "$line_count" -eq "$n" ]; then
        echo "✓ Completado: $output_file_unsorted ($line_count líneas)"
    else
        echo "⚠ ADVERTENCIA: Se obtuvieron $line_count líneas en lugar de $n"
    fi
done

# Guardar valores de búsqueda en un archivo
echo "Guardando valores de búsqueda..."
echo "${SEARCH_VALUES[@]}" | tr ' ' '\n' > "$OUTPUT_DIR/search_values.txt"

echo ""
echo "✓ Todos los datos preparados en directorio: $OUTPUT_DIR"
echo "Archivos de datos ordenados:"
ls -lh "$OUTPUT_DIR"/data_sorted_*.txt | awk '{print "  " $9 " (" $5 ")"}'
echo ""
echo "Archivos de datos sin ordenar:"
ls -lh "$OUTPUT_DIR"/data_unsorted_*.txt | awk '{print "  " $9 " (" $5 ")"}'
