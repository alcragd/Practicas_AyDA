#!/bin/bash
# Ejecuta benchmark y guarda tiempos promedios en benchmark_results/
set -euo pipefail

OUTPUT_DIR="benchmark_data"
RESULTS_DIR="benchmark_results"
BIN_DIR="bin"
mkdir -p "$RESULTS_DIR"

ALGORITHMS=(busqueda_lineal busqueda_binaria busqueda_exponencial busqueda_fibonacci busqueda_abb)
SIZES=(1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000)

SEARCH_FILE="$OUTPUT_DIR/search_values.txt"
if [ ! -f "$SEARCH_FILE" ]; then
  echo "ERROR: $SEARCH_FILE no existe. Ejecuta generate_data.sh"
  exit 1
fi

mapfile -t SEARCH_VALUES < <(tr -d '\r' < "$SEARCH_FILE")
if [ ${#SEARCH_VALUES[@]} -eq 0 ]; then
  echo "ERROR: no hay valores en $SEARCH_FILE"
  exit 1
fi

num_re='^[+-]?[0-9]+(\.[0-9]+)?([eE][+-]?[0-9]+)?$'

for algo in "${ALGORITHMS[@]}"; do
  echo "======================================="
  echo "Algo: $algo"
  echo "======================================="

  # buscar ejecutable en bin/ o en cwd
  if [ -x "$BIN_DIR/$algo" ]; then
    exe="$BIN_DIR/$algo"
  elif [ -x "./$algo" ]; then
    exe="./$algo"
  else
    echo "  ERROR: ejecutable no encontrado para $algo. Omitiendo."
    continue
  fi

  out="$RESULTS_DIR/${algo}_times.txt"
  : > "$out"

  for n in "${SIZES[@]}"; do
    if [[ "$algo" == "busqueda_lineal" || "$algo" == "busqueda_abb" ]]; then
      data="$OUTPUT_DIR/data_unsorted_${n}.txt"
    else
      data="$OUTPUT_DIR/data_sorted_${n}.txt"
    fi

    if [ ! -f "$data" ]; then
      echo "  WARN: archivo de datos $data no encontrado, omitiendo n=$n"
      continue
    fi

    echo "  n=$n ..."

    times=()
    for v in "${SEARCH_VALUES[@]}"; do
      # pasar valor y luego todo el array por stdin, el ejecutable debe imprimir resultado en la 1ª línea y tiempo al final
      if ! output=$((printf '%s\n' "$v"; cat "$data") | "$exe" "$n" 2>&1); then
        echo "    WARN: ejecución falló para valor=$v (ver salida parcial)"
        echo "    -> $(echo "$output" | head -n1)"
        continue
      fi

      res=$(echo "$output" | head -n1 | tr -d '\r' | sed -e 's/^[[:space:]]*//;s/[[:space:]]*$//')
      t=$(echo "$output" | tail -n1 | tr -d '\r' | sed -e 's/^[[:space:]]*//;s/[[:space:]]*$//')

      if [[ $t =~ $num_re ]]; then
        times+=("$t")
      else
        echo "    WARN: tiempo no válido para n=$n valor=$v -> '$t'"
      fi
    done

    if [ ${#times[@]} -gt 0 ]; then
      # sumar y sacar promedio con awk (gestiona notación científica)
      avg=$(printf '%s\n' "${times[@]}" | awk '{sum+=$1; c++} END{ if(c>0) printf "%.10f", sum/c; else print "NaN"}')
      echo "$n $avg" >> "$out"
      echo "    promedio = $avg s"
    else
      echo "    ERROR: no se obtuvieron tiempos válidos para n=$n"
    fi
  done

  echo "  Resultados -> $out"
done

echo "✓ Benchmark completo. Resultados en $RESULTS_DIR"