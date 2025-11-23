#!/bin/bash
# graficos.sh
# Genera gráficos PNG usando gnuplot
set -euo pipefail

RESULTS_DIR="benchmark_results"
OUTDIR="graphs"
mkdir -p "$OUTDIR"

ALGORITHMS=(busqueda_lineal busqueda_lineal_t busqueda_binaria busqueda_binaria_t busqueda_exponencial busqueda_exponencial_t busqueda_fibonacci busqueda_fibonacci_t busqueda_abb_t busqueda_abb)

# ALGORITHMS=(busqueda_lineal busqueda_binaria busqueda_exponencial busqueda_fibonacci busqueda_abb)
TICS="1000000,2000000,3000000,4000000,5000000,6000000,7000000,8000000,9000000,10000000"

# comparativo
plot_parts=()
for a in "${ALGORITHMS[@]}"; do
  f="$RESULTS_DIR/${a}_times.txt"
  if [ -f "$f" ]; then
    pretty=$(echo "$a" | sed 's/_/ /g')
    plot_parts+=("'$f' using 1:2 with lines lw 2 title '$pretty'")
  fi
done

if [ ${#plot_parts[@]} -gt 0 ]; then
  plot_expr=$(IFS=,; echo "${plot_parts[*]}")
  gnuplot <<-EOF
    set terminal png size 1200,700
    set output '${OUTDIR}/comparacion_algoritmos.png'
    set title 'Comparación: tiempo promedio de búsqueda vs n'
    set xlabel 'n'
    set ylabel 'Tiempo (s)'
    set grid
    set logscale y
    set xtics (${TICS})
    set key outside right top
    plot ${plot_expr}
EOF
  echo "✓ comparativo: ${OUTDIR}/comparacion_algoritmos.png"
else
  echo "WARN: no hay archivos para gráfico comparativo"
fi

# individuales
for a in "${ALGORITHMS[@]}"; do
  f="$RESULTS_DIR/${a}_times.txt"
  if [ -f "$f" ]; then
    pretty=$(echo "$a" | sed 's/_/ /g')
    gnuplot <<-EOF
      set terminal png size 800,600
      set output '${OUTDIR}/${a}.png'
      set title 'Tiempo promedio: ${pretty}'
      set xlabel 'n'
      set ylabel 'Tiempo (s)'
      set grid
      set style data linespoints
      set xtics (${TICS})
      plot '$f' using 1:2 with linespoints pt 7 ps 1.5 title '${pretty}'
EOF
    echo "✓ ${OUTDIR}/${a}.png"
  fi
done

echo "✓ Gráficos en: $OUTDIR"