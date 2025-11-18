#!/bin/bash
# Genera archivos de datos para los tamaños pedidos y el archivo search_values.txt
set -euo pipefail

OUTDIR="benchmark_data"
mkdir -p "$OUTDIR"

# tamaños de problema solicitados
SIZES=(1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000)

# Valores A[] a buscar (copiados de la imagen)
cat > "$OUTDIR/search_values.txt" <<'EOF'
322486
14700764
14700764
3128036
6337399
61396
10393545
2147445644
1295390003
450057883
187645041
1980098116
152503
5000
1493283650
214826
1843349527
1360839354
2109248666
2147470852
0
EOF

echo "Generando datos en $OUTDIR (esto puede tardar para los tamaños grandes)..."
for n in "${SIZES[@]}"; do
  sorted="$OUTDIR/data_sorted_${n}.txt"
  unsorted="$OUTDIR/data_unsorted_${n}.txt"

  if [ -f "$sorted" ] && [ -f "$unsorted" ]; then
    echo "  Saltando n=$n (archivos ya existen)"
    continue
  fi

  echo "  Creando n=$n ..."
  # Sorted: 0 .. n-1 (uno por línea)
  seq 0 $((n-1)) > "$sorted"

  # Unsorted: simple mezcla; shuf puede necesitar mucha memoria en n grande.
  # Si shuf falla por memoria, se deja el mismo archivo (no ordenado no garantizado).
  if command -v shuf >/dev/null 2>&1; then
    shuf "$sorted" -o "$unsorted" || cp "$sorted" "$unsorted"
  else
    # fallback: crear una permutación simple por mapeo modular
    awk -v N="$n" 'BEGIN{for(i=0;i<N;i++) print int((i*314159)%N)}' > "$unsorted"
  fi
done

echo "✓ Datos generados en: $OUTDIR"