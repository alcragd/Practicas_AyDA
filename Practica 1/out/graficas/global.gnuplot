set datafile separator ","
set terminal pngcairo size 1000,700 enhanced font 'Arial,10'
set output "./out/graficas/comparativa_tiempo_real.png"
set title "Comparativa Tiempo Real de Algoritmos"
set xlabel "Tamaño de problema (N)"
set ylabel "Tiempo Real (s)"
set grid
set key outside
stats './out/csv/HeapSort.csv' using 1 nooutput
min_x = STATS_min * 0.95
max_x = STATS_max * 1.05
set xrange [min_x:max_x]
stats './out/csv/HeapSort.csv' using 2 nooutput
min_y = STATS_min * 0.95
max_y = STATS_max * 1.10
set yrange [min_y:max_y]
plot "./out/csv/burbujaOptimizada1.csv" every ::1 using 1:2 with points pt 7 ps 2 title "burbujaOptimizada1", "./out/csv/burbujaOptimizada2.csv" every ::1 using 1:2 with points pt 7 ps 2 title "burbujaOptimizada2", "./out/csv/burbujaSimple.csv" every ::1 using 1:2 with points pt 7 ps 2 title "burbujaSimple", "./out/csv/HeapSort.csv" every ::1 using 1:2 with points pt 7 ps 2 title "HeapSort", "./out/csv/InsertionSort.csv" every ::1 using 1:2 with points pt 7 ps 2 title "InsertionSort", "./out/csv/MergeSort.csv" every ::1 using 1:2 with points pt 7 ps 2 title "MergeSort", "./out/csv/QuickSort.csv" every ::1 using 1:2 with points pt 7 ps 2 title "QuickSort", "./out/csv/SelectionSort.csv" every ::1 using 1:2 with points pt 7 ps 2 title "SelectionSort", "./out/csv/ShellSort.csv" every ::1 using 1:2 with points pt 7 ps 2 title "ShellSort", "./out/csv/TreeSort.csv" every ::1 using 1:2 with points pt 7 ps 2 title "TreeSort"