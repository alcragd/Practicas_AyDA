% Ajustes comparativos: ln(x) vs. x*ln(x)
clear; clc; close all;

% --- Datos experimentales (Heapsort)
x = [ 1000
2000
3000
4000
5000
8000
10000
50000
100000
150000
200000
300000
400000
500000
600000
700000
800000
900000
1000000
1500000
2000000 ];

y = [ 0.000178814
0.000409842
0.000693083
0.000687838
0.001119137
0.00169301
0.00248003
0.012633085
0.02760005
0.038229942
0.050174952
0.096535921
0.134675026
0.145029068
0.187092066
0.225758076
0.262390137
0.284281015
0.289803982
0.494340181
0.702052832 ];

% --- Modelo 1: y = a*ln(x) + c
p1 = polyfit(log(x), y, 1);
a = p1(1);
c = p1(2);

% --- Modelo 2: y = b*(x*ln(x)) + d
p2 = polyfit(x .* log(x), y, 1);
b = p2(1);
d = p2(2);

% --- Mostrar las ecuaciones obtenidas
fprintf('Modelo logarítmico:   f(x) = %.6e * ln(x) + %.6e\n', a, c);
fprintf('Modelo n·ln(n):       f(x) = %.6e * x·ln(x) + %.6e\n', b, d);

% --- Crear espacio de evaluación
xi = linspace(min(x), max(x), 2000);
z1 = polyval(p1, log(xi));        % Evaluación del modelo ln(x)
z2 = polyval(p2, xi .* log(xi));  % Evaluación del modelo n·ln(n)

% --- Gráfica comparativa
figure('Units','normalized','Position',[0.1 0.1 0.7 0.6]);
plot(x, y, 'ko', 'MarkerFaceColor', 'k', 'MarkerSize', 6); hold on;
plot(xi, z1, '-', 'LineWidth', 1.8);
plot(xi, z2, '--', 'LineWidth', 1.8);

grid on;
set(gca, 'XScale', 'log');  % Escala logarítmica en eje X (opcional)
xlabel('x (tamaño del arreglo)');
ylabel('Tiempo (ms)');
legend({'Datos experimentales', 'Ajuste a·ln(x)+c', 'Ajuste b·x·ln(x)+d'}, 'Location', 'northwest');
title('Comparación de ajustes para Heapsort');
