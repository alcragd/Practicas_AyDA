#!/bin/bash
# benchmark.sh
# Ejecuta benchmark de todos los algoritmos y captura tiempos

OUTPUT_DIR="benchmark_data"
RESULTS_DIR="benchmark_results"
mkdir -p "$RESULTS_DIR"

ALGORITHMS=("busqueda_lineal" "busqueda_binaria" "busqueda_exponencial" "busqueda_fibonacci" "busqueda_abb")
SIZES=(1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000)

# Leer valores de búsqueda
mapfile -t SEARCH_VALUES < "$OUTPUT_DIR/search_values.txt"

echo "Iniciando benchmark..."
echo "Algoritmos: ${ALGORITHMS[@]}"
echo "Tamaños: ${SIZES[@]}"
echo "Valores a buscar: ${#SEARCH_VALUES[@]} valores"
echo ""

# Para cada algoritmo
for algo in "${ALGORITHMS[@]}"; do
    echo "=========================================="
    echo "Procesando: $algo"
    echo "=========================================="
    
    results_file="$RESULTS_DIR/${algo}_times.txt"
    > "$results_file"  # Limpiar archivo
    
    # Para cada tamaño
    for n in "${SIZES[@]}"; do
        data_file="$OUTPUT_DIR/data_${n}.txt"
        
        if [ ! -f "$data_file" ]; then
            echo "ERROR: Archivo de datos no encontrado: $data_file"
            continue
        fi
        
        echo "  Tamaño n=$n..."
        
        times=()
        found_count=0
        not_found_count=0
        
        # Para cada valor de búsqueda
        for val in "${SEARCH_VALUES[@]}"; do
            # Ejecutar algoritmo y capturar salida completa
            output=$(./$algo $n < <(echo "$val"; cat "$data_file") 2>&1)
            
            # Extraer líneas: primera es resultado, luego vienen muchas líneas de tiempos
            # Nosotros queremos la última línea que es el tiempo en exponencial
            result=$(echo "$output" | head -n1)
            time_output=$(echo "$output" | tail -n1)
            
            # Validar que es un número en formato científico (simple check)
            if [[ $time_output =~ ^-?[0-9]\.[0-9]+e[+-][0-9]+ ]]; then
                times+=("$time_output")
                if [ "$result" -eq "-1" ]; then
                    ((not_found_count++))
                else
                    ((found_count++))
                fi
            fi
        done
        
        # Calcular promedio usando awk
        if [ ${#times[@]} -gt 0 ]; then
            avg_time=$(printf '%s\n' "${times[@]}" | awk '{sum+=$1; count++} END {printf "%.10e", sum/count}')
            echo "    Búsquedas: ${#times[@]} (encontradas: $found_count, no encontradas: $not_found_count)"
            echo "    Tiempo promedio: $avg_time"
            echo "$n $avg_time" >> "$results_file"
        else
            echo "    ERROR: No se obtuvieron tiempos"
        fi
    done
    
    echo "✓ Resultados guardados en: $results_file"
    echo ""
done

echo "✓ Benchmark completado"
echo "Resultados en: $RESULTS_DIR"
