#!/bin/bash
# check_setup.sh
# Verifica que todos los requisitos están listos antes de ejecutar benchmark

echo "╔════════════════════════════════════════════════════════════╗"
echo "║        VALIDACIÓN DE SETUP PARA BENCHMARK                 ║"
echo "╚════════════════════════════════════════════════════════════╝"
echo ""

ERRORS=0
WARNINGS=0

# 1. Verificar archivo de datos
echo "1. Verificando archivo de datos..."
if [ -f "../NumerosOrdenados/Ordenado.txt" ]; then
    LINE_COUNT=$(wc -l < "../NumerosOrdenados/Ordenado.txt")
    FILE_SIZE=$(ls -lh "../NumerosOrdenados/Ordenado.txt" | awk '{print $5}')
    echo "   ✓ Archivo encontrado"
    echo "   • Tamaño: $FILE_SIZE"
    echo "   • Líneas: $LINE_COUNT"
    if [ "$LINE_COUNT" -lt 10000000 ]; then
        echo "   ⚠ ADVERTENCIA: Se esperaban 10M líneas, se encontraron $LINE_COUNT"
        ((WARNINGS++))
    fi
else
    echo "   ✗ ERROR: Archivo no encontrado: ../NumerosOrdenados/Ordenado.txt"
    ((ERRORS++))
fi
echo ""

# 2. Verificar compilador gcc
echo "2. Verificando compilador gcc..."
if command -v gcc &> /dev/null; then
    GCC_VERSION=$(gcc --version | head -n1)
    echo "   ✓ gcc encontrado: $GCC_VERSION"
else
    echo "   ✗ ERROR: gcc no encontrado. Instala: sudo apt-get install build-essential"
    ((ERRORS++))
fi
echo ""

# 3. Verificar gnuplot
echo "3. Verificando gnuplot..."
if command -v gnuplot &> /dev/null; then
    GNUPLOT_VERSION=$(gnuplot --version)
    echo "   ✓ gnuplot encontrado: $GNUPLOT_VERSION"
else
    echo "   ⚠ ADVERTENCIA: gnuplot no encontrado. Instala: sudo apt-get install gnuplot"
    echo "   (Sin gnuplot no se generarán gráficos, pero el benchmark sí se ejecutará)"
    ((WARNINGS++))
fi
echo ""

# 4. Verificar scripts necesarios
echo "4. Verificando scripts..."
SCRIPTS=("generate_data.sh" "compile.sh" "benchmark.sh" "process_results.sh" "graficos.sh" "run_full_benchmark.sh")
for script in "${SCRIPTS[@]}"; do
    if [ -f "$script" ]; then
        if [ -x "$script" ]; then
            echo "   ✓ $script (ejecutable)"
        else
            echo "   ⚠ $script (no es ejecutable, haciendo chmod +x)"
            chmod +x "$script"
        fi
    else
        echo "   ✗ ERROR: $script no encontrado"
        ((ERRORS++))
    fi
done
echo ""

# 5. Verificar archivos fuente C
echo "5. Verificando archivos fuente C..."
C_FILES=("busqueda_lineal.c" "busqueda_binaria.c" "busqueda_exponencial.c" "busqueda_fibonacci.c" "busqueda_abb.c" "abb/abb.c" "abb/abb.h" "tiempo/tiempo.h" "tiempo/tiempo.c")
for cfile in "${C_FILES[@]}"; do
    if [ -f "$cfile" ]; then
        echo "   ✓ $cfile"
    else
        echo "   ✗ ERROR: $cfile no encontrado"
        ((ERRORS++))
    fi
done
echo ""

# Resumen
echo "╔════════════════════════════════════════════════════════════╗"
if [ "$ERRORS" -eq 0 ] && [ "$WARNINGS" -eq 0 ]; then
    echo "║   ✓ TODO ESTÁ LISTO - PUEDES EJECUTAR BENCHMARK              ║"
elif [ "$ERRORS" -eq 0 ]; then
    echo "║   ⚠ HAY $WARNINGS ADVERTENCIA(S) PERO PUEDES CONTINUAR        ║"
else
    echo "║   ✗ HAY $ERRORS ERROR(ES) - RESUELVE ANTES DE CONTINUAR      ║"
fi
echo "╚════════════════════════════════════════════════════════════╝"
echo ""

if [ "$ERRORS" -eq 0 ]; then
    echo "Para ejecutar el benchmark completo:"
    echo "  bash run_full_benchmark.sh"
    echo ""
    echo "O paso a paso:"
    echo "  bash generate_data.sh"
    echo "  bash compile.sh"
    echo "  bash benchmark.sh"
    echo "  bash process_results.sh"
    echo "  bash graficos.sh"
    exit 0
else
    echo "❌ Hay errores que resolver. Por favor revisa arriba."
    exit 1
fi
