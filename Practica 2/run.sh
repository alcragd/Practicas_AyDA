#!/bin/bash
# run.sh
# Ejecuta todo el pipeline: compilar, generar datos, benchmark, procesar resultados y graficar.
set -euo pipefail

WORKDIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$WORKDIR"

SCRIPTS=(compile.sh generate_data.sh benchmark.sh process_results.sh graficos.sh)
MISSING=()

# comprobación mínima de herramientas
for cmd in gcc gnuplot awk seq; do
  if ! command -v "$cmd" >/dev/null 2>&1; then
    echo "WARN: comando requerido no encontrado: $cmd"
  fi
done

echo "Ejecutando pipeline en: $WORKDIR"
echo ""

# Hacer ejecutables y ejecutar cada script en orden
for s in "${SCRIPTS[@]}"; do
  if [ -f "$s" ]; then
    chmod +x "$s"
    echo "------"
    echo "Ejecutando: $s"
    echo "------"
    if ! bash "./$s"; then
      echo "ERROR: el script $s falló. Abortando."
      exit 1
    fi
    echo ""
  else
    MISSING+=("$s")
    echo "WARN: script faltante, se omite: $s"
  fi
done

echo "✓ Pipeline completado."

echo ""
echo "Resumen de artefactos:"
[ -d "benchmark_data" ] && echo "  Datos: $(du -sh benchmark_data 2>/dev/null | cut -f1) -> benchmark_data/"
[ -d "benchmark_results" ] && echo "  Resultados: $(du -sh benchmark_results 2>/dev/null | cut -f1) -> benchmark_results/"
[ -f "benchmark_results.csv" ] && echo "  CSV: benchmark_results.csv ($(stat -c%s benchmark_results.csv) bytes)"
[ -d "graphs" ] && echo "  Gráficos: $(ls -1 graphs | wc -l) archivos -> graphs/"

if [ "${#MISSING[@]}" -gt 0 ]; then
  echo ""
  echo "Nota: faltaron scripts: ${MISSING[*]}. Revisa la carpeta y agrega los scripts faltantes si es necesario."
fi

exit 0