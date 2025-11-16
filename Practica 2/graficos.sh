#!/bin/bash
# graficos.sh
# Genera gráficos con gnuplot

RESULTS_DIR="benchmark_results"
GRAPHS_DIR="graphs"
mkdir -p "$GRAPHS_DIR"

echo "Generando gráficos con gnuplot..."

# Crear gráfico comparativo de todos los algoritmos
gnuplot <<EOF
set terminal png size 1200,700
set output '$GRAPHS_DIR/comparacion_algoritmos.png'
set title 'Comparación de Tiempos de Búsqueda vs Tamaño del Problema'
set xlabel 'Tamaño del Problema (n)'
set ylabel 'Tiempo Promedio de Búsqueda (segundos)'
set xtics (1000000, 2000000, 3000000, 4000000, 5000000, 6000000, 7000000, 8000000, 9000000, 10000000)
set grid
set logscale y
set key outside right top

plot '$RESULTS_DIR/busqueda_lineal_times.txt' using 1:2 with lines lw 2 title 'Búsqueda Lineal', \
     '$RESULTS_DIR/busqueda_binaria_times.txt' using 1:2 with lines lw 2 title 'Búsqueda Binaria', \
     '$RESULTS_DIR/busqueda_exponencial_times.txt' using 1:2 with lines lw 2 title 'Búsqueda Exponencial', \
     '$RESULTS_DIR/busqueda_fibonacci_times.txt' using 1:2 with lines lw 2 title 'Búsqueda Fibonacci', \
     '$RESULTS_DIR/busqueda_abb_times.txt' using 1:2 with lines lw 2 title 'ABB'
EOF

echo "✓ Gráfico comparativo: $GRAPHS_DIR/comparacion_algoritmos.png"

# Gráficos individuales
for algo in "busqueda_lineal" "busqueda_binaria" "busqueda_exponencial" "busqueda_fibonacci" "busqueda_abb"; do
    name_pretty=$(echo "$algo" | sed 's/_/ /g' | sed 's/\b\(.\)/\u\1/g')
    
    gnuplot <<EOF
set terminal png size 800,600
set output '$GRAPHS_DIR/${algo}.png'
set title 'Tiempo de Búsqueda: $name_pretty'
set xlabel 'Tamaño del Problema (n)'
set ylabel 'Tiempo Promedio (segundos)'
set xtics (1000000, 2000000, 3000000, 4000000, 5000000, 6000000, 7000000, 8000000, 9000000, 10000000)
set grid
set style data linespoints

plot '$RESULTS_DIR/${algo}_times.txt' using 1:2 with linespoints pt 7 ps 1.5 title '$name_pretty'
EOF
    
    echo "✓ Gráfico: $GRAPHS_DIR/${algo}.png"
done

echo ""
echo "✓ Todos los gráficos generados en: $GRAPHS_DIR"
ls -lh "$GRAPHS_DIR"
