#!/bin/bash
# run_full_benchmark.sh
# Script maestro que ejecuta todo el pipeline de benchmark

set -e  # Salir si algo falla

echo "╔════════════════════════════════════════════════════════════╗"
echo "║   BENCHMARK COMPLETO DE ALGORITMOS DE BÚSQUEDA            ║"
echo "╚════════════════════════════════════════════════════════════╝"
echo ""

# Step 0: Validar setup
echo "PASO 0: Validando setup..."
echo "─────────────────────────"
bash check_setup.sh
echo ""

# Step 1: Generar datos
echo "PASO 1: Generando datos de prueba..."
echo "────────────────────────────────────"
bash generate_data.sh
echo ""

# Step 2: Compilar
echo "PASO 2: Compilando algoritmos..."
echo "────────────────────────────────"
bash compile.sh
echo ""

# Step 3: Ejecutar benchmark
echo "PASO 3: Ejecutando benchmark (esto puede tardar varios minutos)..."
echo "───────────────────────────────────────────────────────────────"
bash benchmark.sh
echo ""

# Step 4: Procesar resultados
echo "PASO 4: Procesando resultados..."
echo "────────────────────────────────"
bash process_results.sh
echo ""

# Step 5: Generar gráficos
echo "PASO 5: Generando gráficos..."
echo "──────────────────────────────"
bash graficos.sh
echo ""

echo "╔════════════════════════════════════════════════════════════╗"
echo "║   ✓ BENCHMARK COMPLETADO EXITOSAMENTE                     ║"
echo "╚════════════════════════════════════════════════════════════╝"
echo ""
echo "Archivos generados:"
echo "  • Datos: benchmark_data/"
echo "  • Tiempos: benchmark_results/*_times.txt"
echo "  • CSV: benchmark_results.csv"
echo "  • Gráficos: graphs/"
echo ""
