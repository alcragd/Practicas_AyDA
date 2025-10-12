%%VALORES DE X 
x=[1000
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
2000000
];
 
%%VALORES DE Y = F(x) en Milisegundos
y=[0.000178814
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
0.702052832
];

%%GRADOS DEL POLINOMIO DE AJUSTE
grados = [1, 2, 3, 6]; % Grados a considerar
colors = ['r', 'g', 'b', 'm']; % Colores para las diferentes curvas

%%SE CREA UN ESPACIO PARA REALIZAR UNA GRAFICA EN 
%%DONDE SE COMPARA LA CURVA AJUSTADA CONTRA LOS 
%%VALORES EXPERIMENTALES
xi=linspace(0,2000000,10000); % Espacio de puntos para Xi

%%SE REALIZA LA FIGURA CORRESPONDIENTE
figure(1);
hold on; % Mantener la gráfica para superponer

% Graficar los puntos experimentales
plot(x, y, 'ko', 'MarkerFaceColor', 'k', 'DisplayName', 'Datos Experimentales TreeSort');

% Ajustar y graficar polinomios de diferentes grados
for i = 1:length(grados)
    grado = grados(i);
    p = polyfit(x, y, grado); % Función que realiza el ajuste polinomial
    z = polyval(p, xi); % Evaluación del polinomio P en el espacio Xi
    plot(xi, z, colors(i), 'DisplayName', sprintf('Ajuste Grado %d', grado));
    
    % Mostrar la función aproximada en la gráfica
    func_str = sprintf('Ajuste Grado %d: ', grado);
    for j = 1:length(p)
        if j == 1
            func_str = [func_str, sprintf('%.6f', p(j))];
        else
            func_str = [func_str, sprintf(' + %.6f*x^%d', p(j), j-1)];
        end
    end
    text(0.1, 0.9 - (i-1)*0.05, func_str, 'Units', 'normalized', 'Color', colors(i));
end

grid;
ylabel('Tempo (s)');
xlabel('Tamaño del arreglo');
title('Ajuste polinomial');
legend show; % Mostrar leyenda
hold off; % Liberar la gráfica