# 🚀 BENCHMARK DE ALGORITMOS DE BÚSQUEDA

## Inicio Rápido

Desde la carpeta `Practica 2/`:

```bash
# Haz ejecutables los scripts
chmod +x *.sh

# Ejecuta TODO automáticamente:
bash run_full_benchmark.sh
```

**Eso es todo.** Los scripts harán:
1. Validar setup
2. Generar datos (1M a 10M desde Ordenado.txt)
3. Compilar algoritmos
4. Ejecutar benchmark
5. Generar CSV + gráficos PNG

## Requisitos

- **Linux/WSL** (bash)
- **gcc** (compilador C)
- **gnuplot** (opcional, para gráficos)
- **Archivo de datos**: `../NumerosOrdenados/Ordenado.txt`

## Estructura de Carpetas

```
Practicas_AyDA/
├── NumerosOrdenados/
│   └── Ordenado.txt              ← Tu archivo 10M números
└── Practica 2/
    ├── *.c                        ← Archivos búsqueda (con tiempos)
    ├── abb/                       ← Árbol binario
    ├── tiempo/                    ← Librería de tiempos
    ├── check_setup.sh             ← Valida setup
    ├── generate_data.sh           ← Prepara datos 1M-10M
    ├── compile.sh                 ← Compila
    ├── benchmark.sh               ← Ejecuta pruebas
    ├── process_results.sh         ← Genera CSV
    ├── graficos.sh                ← Crea gráficos
    └── run_full_benchmark.sh      ← EJECUTA TODO
```

## Salida Esperada

```
benchmark_data/                    ← Datos (1M-10M elementos)
benchmark_results/                 ← Tiempos por algoritmo
benchmark_results.csv              ← Tabla resumen
graphs/
├── comparacion_algoritmos.png     ← Gráfico comparativo
├── busqueda_lineal.png
├── busqueda_binaria.png
├── busqueda_exponencial.png
├── busqueda_fibonacci.png
└── busqueda_abb.png
```

## Valores de Búsqueda (20)

```
322486, 14700764, 3128036, 6337399, 61396,
10393545, 2147445644, 1295390003, 450057883, 187645041,
1980098116, 152503, 5000, 1493283650, 214826,
1843349527, 1360839354, 2109248666, 2147470852, 0
```

## Tamaños de Problema

1M, 2M, 3M, 4M, 5M, 6M, 7M, 8M, 9M, 10M elementos

## Algoritmos Evaluados

1. **Búsqueda Lineal** - O(n)
2. **Búsqueda Binaria** - O(log n)
3. **Búsqueda Exponencial** - O(log n)
4. **Búsqueda Fibonacci** - O(log n)
5. **ABB** - O(log n) promedio

## Formato CSV

```csv
Tamaño_n,Búsqueda_Lineal,Búsqueda_Binaria,Búsqueda_Exponencial,Búsqueda_Fibonacci,ABB
1000000,1.23e-02,4.56e-03,5.67e-03,3.45e-03,2.34e-03
2000000,2.34e-02,5.67e-03,6.78e-03,4.56e-03,3.45e-03
...
10000000,1.23e-01,1.23e-02,1.34e-02,1.05e-02,8.90e-03
```

## Paso a Paso (Manual)

```bash
bash check_setup.sh       # Verifica requisitos
bash generate_data.sh     # Crea archivos 1M-10M
bash compile.sh           # Compila ejecutables
bash benchmark.sh         # Ejecuta pruebas (~20-30 min)
bash process_results.sh   # Genera CSV
bash graficos.sh          # Crea gráficos PNG
```

## Troubleshooting

**"Archivo no encontrado: ../NumerosOrdenados/Ordenado.txt"**
→ Verifica que el archivo existe en la ruta correcta

**"gnuplot not found"**
→ Instala: `sudo apt-get install gnuplot` (opcional)

**Benchmark muy lento**
→ Normal: procesa 20 búsquedas × 10 tamaños × 5 algoritmos = 1000 ejecuciones

**Resultado "N/A" en CSV**
→ Revisa benchmark_results/*_times.txt
→ Compila manualmente: `bash compile.sh`

## Archivos C Modificados

- `busqueda_lineal.c` ✓ Medición tiempos
- `busqueda_binaria.c` ✓ Medición tiempos
- `busqueda_exponencial.c` ✓ Medición tiempos
- `busqueda_fibonacci.c` ✓ Medición tiempos
- `busqueda_abb.c` ✓ Medición tiempos

Todos simplificados para capturar correctamente:
- Línea 1: Resultado (-1 o índice)
- Línea 2: Tiempo en formato científico (%.10e)

---

**Listo para ejecutar 🚀**
