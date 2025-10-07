#!/bin/bash

# Elimina ejecutables generados
rm -f ./out/*.out

# Elimina archivos temporales
rm -f ./salida.txt

# Elimina logs y CSVs
rm -f ./logs/*.csv
rm -f ./logs/*.gnuplot

rm -f ./out/csv/*.csv
rm -f ./out/graficas/*.png
rm -f ./out/graficas/*.gnuplot

# Elimina todas las gráficas generadas
rm -f ./logs/*.png

echo "Archivos generados por medir_tiempos.sh y pruebas.sh eliminados."