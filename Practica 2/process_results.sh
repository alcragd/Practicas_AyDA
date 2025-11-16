#!/bin/bash
# process_results.sh
# Procesa resultados del benchmark y genera CSV

RESULTS_DIR="benchmark_results"
OUTPUT_CSV="benchmark_results.csv"

echo "Procesando resultados del benchmark..."

# Encabezado CSV
echo "Tamaño_n,Búsqueda_Lineal,Búsqueda_Binaria,Búsqueda_Exponencial,Búsqueda_Fibonacci,ABB" > "$OUTPUT_CSV"

# Tamaños
SIZES=(1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000)

# Para cada tamaño
for n in "${SIZES[@]}"; do
    line="$n"
    
    # Para cada algoritmo
    for algo in "busqueda_lineal" "busqueda_binaria" "busqueda_exponencial" "busqueda_fibonacci" "busqueda_abb"; do
        results_file="$RESULTS_DIR/${algo}_times.txt"
        
        if [ -f "$results_file" ]; then
            # Buscar línea con este tamaño y extraer tiempo
            time_val=$(grep "^$n " "$results_file" | awk '{print $2}')
            
            if [ -z "$time_val" ]; then
                time_val="N/A"
            fi
        else
            time_val="N/A"
        fi
        
        line="$line,$time_val"
    done
    
    echo "$line" >> "$OUTPUT_CSV"
done

echo "✓ CSV generado: $OUTPUT_CSV"
echo ""
echo "Vista previa del CSV:"
head -n 6 "$OUTPUT_CSV" | column -t -s','

echo ""
echo "Estadísticas del archivo:"
wc -l "$OUTPUT_CSV"
