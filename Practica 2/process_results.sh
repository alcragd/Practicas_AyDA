#!/bin/bash
# Convierte resultados a CSV (columnas: n, cada algoritmo)
set -euo pipefail

RESULTS_DIR="benchmark_results"
OUTCSV="benchmark_results.csv"
ALGORITHMS=(busqueda_lineal busqueda_binaria busqueda_exponencial busqueda_fibonacci busqueda_abb)
SIZES=(1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000)

if [ ! -d "$RESULTS_DIR" ]; then
  echo "ERROR: $RESULTS_DIR no existe. Ejecuta benchmark.sh"
  exit 1
fi

# header
printf "n" > "$OUTCSV"
for a in "${ALGORITHMS[@]}"; do
  printf ",%s" "$a" >> "$OUTCSV"
done
printf "\n" >> "$OUTCSV"

for n in "${SIZES[@]}"; do
  line="$n"
  for a in "${ALGORITHMS[@]}"; do
    f="$RESULTS_DIR/${a}_times.txt"
    if [ -f "$f" ]; then
      val=$(grep -E "^${n}[[:space:]]" "$f" 2>/dev/null | awk '{print $2}' | tr -d '\r' | head -n1 || true)
      [ -z "$val" ] && val="N/A"
    else
      val="N/A"
    fi
    line="$line,$val"
  done
  echo "$line" >> "$OUTCSV"
done

echo "✓ CSV generado: $OUTCSV"
echo ""
echo "Vista previa del CSV:"
head -n 6 "$OUTCSV" | column -t -s','

echo ""
echo "Estadísticas del archivo:"
wc -l "$OUTCSV"