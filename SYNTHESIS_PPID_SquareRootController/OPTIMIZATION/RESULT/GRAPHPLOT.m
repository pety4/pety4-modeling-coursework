clear all;
%% Загрузка результатов моделирования
FX=importdata('OUT.ris');    % Состояние 
FJ=importdata('FJ.ris');    % Оценка состояния 
FX=FX.data;
FJ=FJ.data;

%% Извлечение данных
n=FJ(:,1);
% Состояние
T0  = FJ(:,2);
kP  = FJ(:,3);
kI  = FJ(:,4);
kD  = FJ(:,5);
J   = FJ(:,6);

T=FX(:,1);
U=FX(:,2);
XI=FX(:,3);
X=FX(:,4);
XD=FX(:,5);
XD2=FX(:,6);

% plot(n,J);
% xlabel('Iteration');
% ylabel('Cost function, J');

plot(T,X,'-b');
xlabel('Time, s');
ylabel('\Deltah, m');

% plot(T,XD2,'-b');
% xlabel('Time, s');
% ylabel('a_y, m/s^2');
% plot(T,U,'-b');
% xlabel('Time, s');
% ylabel('u_h, N');
grid on;
grid minor;
