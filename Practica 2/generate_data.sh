#!/bin/bash
# generate_data.sh
# Prepara archivos de datos para benchmark usando Ordenado.txt existente
# Uso: ./generate_data.sh

OUTPUT_DIR="benchmark_data"
mkdir -p "$OUTPUT_DIR"

# Archivo con 10M números ordenados
SOURCE_FILE="../NumerosOrdenados/Ordenado.txt"

# Verificar que el archivo existe
if [ ! -f "$SOURCE_FILE" ]; then
    echo "ERROR: Archivo no encontrado: $SOURCE_FILE"
    echo "Por favor asegúrate que existe: NumerosOrdenados/Ordenado.txt"
    exit 1
fi

echo "✓ Archivo encontrado: $SOURCE_FILE"
wc -l "$SOURCE_FILE"

# Valores de búsqueda
SEARCH_VALUES=(322486 14700764 3128036 6337399 61396 10393545 2147445644 1295390003 450057883 187645041 1980098116 152503 5000 1493283650 214826 1843349527 1360839354 2109248666 2147470852 0)

# Crear archivos de datos de 1M a 10M elementos (extractos del archivo original)
for n in 1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000; do
    output_file="$OUTPUT_DIR/data_${n}.txt"
    
    echo "Generando $output_file con los primeros $n números..."
    
    # Extraer los primeros n líneas del archivo original
    head -n $n "$SOURCE_FILE" > "$output_file"
    
    # Verificar que se creó correctamente
    line_count=$(wc -l < "$output_file")
    if [ "$line_count" -eq "$n" ]; then
        echo "✓ Completado: $output_file ($line_count líneas)"
    else
        echo "⚠ ADVERTENCIA: Se obtuvieron $line_count líneas en lugar de $n"
    fi
done

# Guardar valores de búsqueda en un archivo
echo "Guardando valores de búsqueda..."
echo "${SEARCH_VALUES[@]}" | tr ' ' '\n' > "$OUTPUT_DIR/search_values.txt"

echo ""
echo "✓ Todos los datos preparados en directorio: $OUTPUT_DIR"
echo "Archivos creados:"
ls -lh "$OUTPUT_DIR"/data_*.txt | awk '{print "  " $9 " (" $5 ")"}'
