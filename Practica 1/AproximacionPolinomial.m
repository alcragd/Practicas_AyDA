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
y=[0.000185013
0.000440121
0.001019001
0.001244068
0.001913071
0.002369881
0.003829002
0.026273966
0.055223942
0.086506128
0.14190197
0.232756138
0.38499403
0.504781008
0.579200029
0.689131975
0.81227088
0.967460871
1.16125679
2.525167942
3.377446175];

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
end

grid;
ylabel('F(x)');
xlabel('x');
title('Ajuste polinomial');
legend show; % Mostrar leyenda
hold off; % Liberar la gráfica