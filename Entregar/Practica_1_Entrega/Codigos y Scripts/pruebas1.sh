#!/bin/bash

# === CONFIGURACIÓN === 
N=2000000
NUM_FILE="./Numeros/numeros10millones.txt"
LOG_FILE="./logs/tiempos.csv"
SRC_DIR="./"
OUT_DIR="./out"
TMP_OUT="./salida.txt"

mkdir -p "$(dirname "$LOG_FILE")"
mkdir -p "$OUT_DIR"

echo "Algoritmo,Tiempo Real,Tiempo CPU,Tiempo E/S,% CPU/Wall" > "$LOG_FILE"

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

ineficientes=("burbujaSimple" "burbujaOptimizada1" "burbujaOptimizada2" "InsertionSort" "SelectionSort")

# === PRIMERO LOS EFICIENTES ===
for exe in "$OUT_DIR"/*.out; do
    name=$(basename "$exe" .out)
    skip=0
    for alg in "${ineficientes[@]}"; do
        if [[ "$name" == "$alg" ]]; then
            skip=1
            break
        fi
    done
    if [[ $skip -eq 1 ]]; then
        continue
    fi

    echo "Ejecutando $name..."
    head -n $N "$NUM_FILE" | "$exe" $N > "$TMP_OUT"
    real_time=$(grep -m1 "real" "$TMP_OUT" | awk '{print $(NF-1)}')
    cpu_time=$(grep -m1 "user" "$TMP_OUT" | awk '{print $(NF-1)}')
    es_time=$(grep -m1 "sys" "$TMP_OUT" | awk '{print $(NF-1)}')
    cpu_wall=$(grep -m1 "CPU/Wall" "$TMP_OUT" | awk '{print $(NF-1)}')
    [[ -z "$real_time" ]] && real_time=0
    [[ -z "$cpu_time" ]] && cpu_time=0
    [[ -z "$es_time" ]] && es_time=0
    [[ -z "$cpu_wall" ]] && cpu_wall=0
    echo "$name,$real_time,$cpu_time,$es_time,$cpu_wall %" >> "$LOG_FILE"
done

# === AHORA LOS INEFICIENTES ===
for alg in "${ineficientes[@]}"; do
    exe="${OUT_DIR}/${alg}.out"
    if [[ -f "$exe" ]]; then
        echo "Ejecutando $alg..."
        head -n $N "$NUM_FILE" | "$exe" $N > "$TMP_OUT"
        real_time=$(grep -m1 "real" "$TMP_OUT" | awk '{print $(NF-1)}')
        cpu_time=$(grep -m1 "user" "$TMP_OUT" | awk '{print $(NF-1)}')
        es_time=$(grep -m1 "sys" "$TMP_OUT" | awk '{print $(NF-1)}')
        cpu_wall=$(grep -m1 "CPU/Wall" "$TMP_OUT" | awk '{print $(NF-1)}')
        [[ -z "$real_time" ]] && real_time=0
        [[ -z "$cpu_time" ]] && cpu_time=0
        [[ -z "$es_time" ]] && es_time=0
        [[ -z "$cpu_wall" ]] && cpu_wall=0
        echo "$alg,$real_time,$cpu_time,$es_time,$cpu_wall" >> "$LOG_FILE"
    fi
done

rm -f "$TMP_OUT"

echo "Resultados guardados en $LOG_FILE"

# === GENERAR GRÁFICAS CON GNUPLOT ===

# --- Gráfica de tiempo real ---
gnuplot <<EOF
set datafile separator ","
set terminal pngcairo size 800,500 enhanced font 'Arial,10'
set output "./logs/grafica_tiempo_real.png"
set title "Comparativa de Tiempo Real ($N números)"
set style fill solid 0.6 border -1
set boxwidth 0.7
set ylabel "Tiempo (s)"
set grid ytics
set xtics rotate by -45
stats "$LOG_FILE" using 2 nooutput
max_y = STATS_max * 1.15
set yrange [0:max_y]
plot "$LOG_FILE" using 2:xtic(1) with boxes lc rgb "#1f77b4" title "Tiempo Real (s)"
EOF

# --- Gráfica de tiempo CPU ---
gnuplot <<EOF
set datafile separator ","
set terminal pngcairo size 800,500 enhanced font 'Arial,10'
set output "./logs/grafica_tiempo_cpu.png"
set title "Comparativa de Tiempo CPU ($N números)"
set style fill solid 0.6 border -1
set boxwidth 0.7
set ylabel "Tiempo (s)"
set grid ytics
set xtics rotate by -45
stats "$LOG_FILE" using 3 nooutput
max_y = STATS_max * 1.15
set yrange [0:max_y]
plot "$LOG_FILE" using 3:xtic(1) with boxes lc rgb "#2ca02c" title "Tiempo CPU (s)"
EOF

# # --- Gráfica de tiempo E/S ---
# gnuplot <<EOF
# set datafile separator ","
# set terminal pngcairo size 800,500 enhanced font 'Arial,10'
# set output "./logs/grafica_tiempo_es.png"
# set title "Comparativa de Tiempo E/S ($N números)"
# set style fill solid 0.6 border -1
# set boxwidth 0.7
# set ylabel "Tiempo (s)"
# set grid ytics
# set xtics rotate by -45
# stats "$LOG_FILE" using 4 nooutput
# max_y = STATS_max * 1.15
# set yrange [0:max_y]
# plot "$LOG_FILE" using 4:xtic(1) with boxes lc rgb "#ff7f0e" title "Tiempo E/S (s)"
# EOF

# # --- Gráfica de CPU/Wall ---
# gnuplot <<EOF
# set datafile separator ","
# set terminal pngcairo size 800,500 enhanced font 'Arial,10'
# set output "./logs/grafica_cpu_wall.png"
# set title "Comparativa de CPU/Wall ($N números)"
# set style fill solid 0.6 border -1
# set boxwidth 0.7
# set ylabel "Porcentaje (%)"
# set grid ytics
# set xtics rotate by -45
# stats "$LOG_FILE" using 5 nooutput
# max_y = STATS_max * 1.15
# set yrange [0:max_y]
# plot "$LOG_FILE" using 5:xtic(1) with boxes lc rgb "#d62728" title "CPU/Wall (%)"
# EOF

echo "Gráficas generadas en ./logs/"
