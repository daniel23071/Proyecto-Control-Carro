% Cargar datos para el primer gráfico
D = load("datos.txt");
T = D(:, 1);
U = D(:, 2);
Y = D(:, 3) / 14;
R = D(:, 4);

% Cargar datos para el segundo gráfico
D1 = load("datos3.txt");
T1 = D1(:, 1);
U1 = D1(:, 2);
Y1 = D1(:, 3) / 14;
R1 = D1(:, 4);

% Graficar en el primer gráfico
subplot(2, 1, 1);
plot(T, U);
hold on;
plot(T, Y);
%plot(T, R);
title('Primer Gráfico');
legend('U', 'Y', 'R');
hold off;

% Graficar en el segundo gráfico
subplot(2, 1, 2);
plot(T1, U1);
hold on;
plot(T1, Y1);
%plot(T1, R1);
title('Segundo Gráfico');
legend('U1', 'Y1', 'R1');
hold off;
