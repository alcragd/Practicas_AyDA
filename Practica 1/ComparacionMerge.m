%% COMPARACIÓN DE AJUSTES: POLINOMIAL, LOGARÍTMICO Y n·ln(n) CON ECUACIONES
clear; clc; close all;

%% VALORES DE X
x = [1000
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
2000000];

%% VALORES DE Y = F(x) EN SEGUNDOS
y = [0.000119925
0.00025487
0.000442028
0.000839949
0.001209974
0.001941919
0.002167225
0.01199913
0.022989988
0.029201984
0.038668156
0.05923295
0.086681128
0.107146025
0.125375986
0.15374589
0.177015066
0.221938133
0.224569082
0.351815939
0.446348906
];

%% CONFIGURACIÓN DE AJUSTES POLINOMIALES
grados = [1, 2, 3, 6];             % Grados polinomiales
colors = ['r', 'g', 'b', 'm'];     % Colores para polinomios
linewidths = 1.5;

%% ESPACIO DE EVALUACIÓN
xi = linspace(min(x), max(x), 10000);

%% FIGURA PRINCIPAL
figure('Units','normalized','Position',[0.1 0.1 0.7 0.6]);
hold on;

% PUNTOS EXPERIMENTALES
plot(x, y, 'ko', 'MarkerFaceColor', 'k', 'DisplayName', 'Datos Experimentales MergeSort');

% AJUSTES POLINOMIALES
for i = 1:length(grados)
    grado = grados(i);
    p = polyfit(x, y, grado);
    z = polyval(p, xi);
    
    plot(xi, z, colors(i), 'LineWidth', linewidths, 'DisplayName', sprintf('Polinomio grado %d', grado));
    
    % Mostrar ecuación sobre la gráfica
    func_str = sprintf('Grado %d: ', grado);
    for j = 1:length(p)
        exp = length(p) - j;
        if exp == 0
            func_str = [func_str, sprintf('+ %.3e', p(j))];
        elseif exp == 1
            func_str = [func_str, sprintf(' + %.3e*x', p(j))];
        else
            func_str = [func_str, sprintf(' + %.3e*x^%d', p(j), exp)];
        end
    end
    text(0.05, 0.9 - (i-1)*0.05, func_str, 'Units','normalized', 'Color', colors(i), 'FontSize',9);
end

% AJUSTE LOGARÍTMICO
p_log = polyfit(log(x), y, 1);
a = p_log(1); c = p_log(2);
z_log = polyval(p_log, log(xi));
plot(xi, z_log, '--', 'Color', [0 0.6 1], 'LineWidth', 1.8, 'DisplayName', 'Ajuste logarítmico');

% Ecuación logarítmica sobre la gráfica
text(0.05, 0.9 - length(grados)*0.05, ...
    sprintf('Log: %.3e*ln(x)+%.3e', a, c), 'Units','normalized', 'Color',[0 0.6 1], 'FontSize',9);

% AJUSTE n·ln(n)
p_nlogn = polyfit(x .* log(x), y, 1);
b = p_nlogn(1); d = p_nlogn(2);
z_nlogn = polyval(p_nlogn, xi .* log(xi));
plot(xi, z_nlogn, '-.', 'Color', [1 0.5 0], 'LineWidth', 1.8, 'DisplayName', 'Ajuste n·ln(n)');

% Ecuación n*ln(n) sobre la gráfica
text(0.05, 0.9 - (length(grados)+1)*0.05, ...
    sprintf('n*ln(n): %.3e*x*ln(x)+%.3e', b, d), 'Units','normalized', 'Color',[1 0.5 0], 'FontSize',9);

% CONFIGURACIÓN FINAL
grid on;
xlabel('Tamaño del arreglo');
ylabel('Tiempo (s)');
title('Comparación de ajustes para MergeSort: Polinomiales, Logarítmico y n·ln(n)');
legend('Location', 'northwest');
%set(gca, 'XScale', 'log');
hold off;