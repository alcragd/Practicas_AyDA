#!/bin/bash

# === CONFIGURACIÓN ===
NUM_FILE="./Numeros/numeros10millones.txt"
SRC_DIR="./"
OUT_DIR="./out"
CSV_DIR="./out/csv"
GRAPH_DIR="./out/graficas"
TMP_OUT="./salida.txt"

mkdir -p "$OUT_DIR" "$CSV_DIR" "$GRAPH_DIR"

# Lista de tamaños de entrada
TAM_N=(1000 2000 3000 4000 5000 8000 10000 50000 100000 150000 200000 300000 \
       400000 500000 600000 700000 800000 900000 1000000 1500000 2000000)

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

ineficientes=("burbujaSimple" "burbujaOptimizada1" "burbujaOptimizada2" "InsertionSort" "SelectionSort" "MergeSort" "ShellSort" "TreeSort" "HeapSort")

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

    CSV_FILE="$CSV_DIR/${name}.csv"
    echo "N,TiempoReal,TiempoCPU,Tiempo E/S,% CPU/Wall" > "$CSV_FILE"

    echo "Ejecutando $name..."
    for N in "${TAM_N[@]}"; do
        echo "  -> N=$N"
        head -n $N "$NUM_FILE" | "$exe" $N > "$TMP_OUT"

        real_time=$(grep -m1 "real" "$TMP_OUT" | awk '{print $(NF-1)}')
        cpu_time=$(grep -m1 "user" "$TMP_OUT" | awk '{print $(NF-1)}')
        es_time=$(grep -m1 "sys" "$TMP_OUT" | awk '{print $(NF-1)}')
        cpu_wall=$(grep -m1 "CPU/Wall" "$TMP_OUT" | awk '{print $(NF-1)}')

        [[ -z "$real_time" ]] && real_time=0
        [[ -z "$cpu_time" ]] && cpu_time=0
        [[ -z "$es_time" ]] && es_time=0
        [[ -z "$cpu_wall" ]] && cpu_wall=0

        echo "$N,$real_time,$cpu_time,$es_time,$cpu_wall %" >> "$CSV_FILE"
    done

       # === Graficar comportamiento temporal del algoritmo ===
    gnuplot <<EOF
set datafile separator ","
set terminal pngcairo size 1000,700 enhanced font 'Arial,10'
set output "$GRAPH_DIR/${name}_tiempos.png"
set title "Comportamiento temporal - $name"
set xlabel "Tamaño de problema (N)"
set ylabel "Tiempo (s)"
set grid
set key outside
stats "$CSV_FILE" using 1 nooutput
min_x = STATS_min * 0.95
max_x = STATS_max * 1.05
set xrange [min_x:max_x]
stats "$CSV_FILE" using 2 nooutput
min_y = STATS_min * 0.95
max_y = STATS_max * 1.10
set yrange [min_y:max_y]
plot "$CSV_FILE" every ::1 using 1:2 with points linecolor rgb "#1f77b4" pointtype 7 pointsize 1.5 title "Tiempo Real", \
     "" every ::1 using 1:3 with points linecolor rgb "#2ca02c" pointtype 7 pointsize 1.5 title "Tiempo CPU", \
     "" every ::1 using 1:4 with points linecolor rgb "#ff7f0e" pointtype 7 pointsize 1.5 title "Tiempo E/S"
EOF

done

# === AHORA LOS INEFICIENTES ===
# for alg in "${ineficientes[@]}"; do
#     exe="${OUT_DIR}/${alg}.out"
#     if [[ -f "$exe" ]]; then
#         CSV_FILE="$CSV_DIR/${alg}.csv"
#         echo "N,TiempoReal,TiempoCPU,Tiempo E/S,% CPU/Wall" > "$CSV_FILE"

#         echo "Ejecutando $alg..."
#         for N in "${TAM_N[@]}"; do
#             echo "  -> N=$N"
#             head -n $N "$NUM_FILE" | "$exe" $N > "$TMP_OUT"

#             real_time=$(grep -m1 "real" "$TMP_OUT" | awk '{print $(NF-1)}')
#             cpu_time=$(grep -m1 "user" "$TMP_OUT" | awk '{print $(NF-1)}')
#             es_time=$(grep -m1 "sys" "$TMP_OUT" | awk '{print $(NF-1)}')
#             cpu_wall=$(grep -m1 "CPU/Wall" "$TMP_OUT" | awk '{print $(NF-1)}')

#             [[ -z "$real_time" ]] && real_time=0
#             [[ -z "$cpu_time" ]] && cpu_time=0
#             [[ -z "$es_time" ]] && es_time=0
#             [[ -z "$cpu_wall" ]] && cpu_wall=0

#             echo "$N,$real_time,$cpu_time,$es_time,$cpu_wall %" >> "$CSV_FILE"
#         done

#     # === Graficar comportamiento temporal del algoritmo ===
# gnuplot <<EOF
# set datafile separator ","
# set terminal pngcairo size 1000,700 enhanced font 'Arial,10'
# set output "$GRAPH_DIR/${name}_tiempos.png"
# set title "Comportamiento temporal - $name"
# set xlabel "Tamaño de problema (N)"
# set ylabel "Tiempo (s)"
# set grid
# set key outside
# stats "$CSV_FILE" using 1 nooutput
# min_x = STATS_min * 0.95
# max_x = STATS_max * 1.05
# set xrange [min_x:max_x]
# stats "$CSV_FILE" using 2 nooutput
# min_y = STATS_min * 0.95
# max_y = STATS_max * 1.10
# set yrange [min_y:max_y]
# plot "$CSV_FILE" every ::1 using 1:2 with points linecolor rgb "#1f77b4" pointtype 7 pointsize 1.5 title "Tiempo Real", \
#      "" every ::1 using 1:3 with points linecolor rgb "#2ca02c" pointtype 7 pointsize 1.5 title "Tiempo CPU", \
#      "" every ::1 using 1:4 with points linecolor rgb "#ff7f0e" pointtype 7 pointsize 1.5 title "Tiempo E/S"
# EOF
#     fi
# done

rm -f "$TMP_OUT"

# === COMPARATIVA GLOBAL DE TIEMPO REAL ENTRE ALGORITMOS ===
OUT_GLOBAL="$GRAPH_DIR/comparativa_tiempo_real.png"

# Encuentra el primer archivo CSV para los stats
first_csv=$(ls "$CSV_DIR"/*.csv | head -n 1)

echo "set datafile separator \",\"" > "$GRAPH_DIR/global.gnuplot"
echo "set terminal pngcairo size 1000,700 enhanced font 'Arial,10'" >> "$GRAPH_DIR/global.gnuplot"
echo "set output \"$OUT_GLOBAL\"" >> "$GRAPH_DIR/global.gnuplot"
echo "set title \"Comparativa Tiempo Real de Algoritmos\"" >> "$GRAPH_DIR/global.gnuplot"
echo "set xlabel \"Tamaño de problema (N)\"" >> "$GRAPH_DIR/global.gnuplot"
echo "set ylabel \"Tiempo Real (s)\"" >> "$GRAPH_DIR/global.gnuplot"
echo "set grid" >> "$GRAPH_DIR/global.gnuplot"
echo "set key outside" >> "$GRAPH_DIR/global.gnuplot"
echo "stats '$first_csv' using 1 nooutput" >> "$GRAPH_DIR/global.gnuplot"
echo "min_x = STATS_min * 0.95" >> "$GRAPH_DIR/global.gnuplot"
echo "max_x = STATS_max * 1.05" >> "$GRAPH_DIR/global.gnuplot"
echo "set xrange [min_x:max_x]" >> "$GRAPH_DIR/global.gnuplot"
echo "stats '$first_csv' using 2 nooutput" >> "$GRAPH_DIR/global.gnuplot"
echo "min_y = STATS_min * 0.95" >> "$GRAPH_DIR/global.gnuplot"
echo "max_y = STATS_max * 1.10" >> "$GRAPH_DIR/global.gnuplot"
echo "set yrange [min_y:max_y]" >> "$GRAPH_DIR/global.gnuplot"
echo -n "plot " >> "$GRAPH_DIR/global.gnuplot"

first=1
for csv in "$CSV_DIR"/*.csv; do
    alg=$(basename "$csv" .csv)
    if [[ $first -eq 0 ]]; then
        echo -n ", " >> "$GRAPH_DIR/global.gnuplot"
    fi
    echo -n "\"$csv\" every ::1 using 1:2 with points pt 7 ps 2 title \"$alg\"" >> "$GRAPH_DIR/global.gnuplot"
    first=0
done

gnuplot "$GRAPH_DIR/global.gnuplot"

echo "Todas las gráficas generadas en $GRAPH_DIR"
