

% graficar datos de experimentos
% crear los vectores

% vector distancias
distancia = [0 10 20 30 40 50 60 70 80 90 100 110 120 130 140];


%************************************************************************************
% datos considerando led rojo como sensor 
RojoSensor = [4.23 3.99 3.91 3.86 3.81 3.7 3.41 3.02 3.06 2.97 2.68 2.37 2.68 2.47 2.27];
VerdeEnergiaRS = [0.95 0.27 0.15 0.063 0.03 0.018 0.013 0.010 0.011 0.008 0.005 0.003 0.003 0.00067 0];
AzulEnergiaRS = [0.27 0.13 0.066 0.026 0.016 0.008 0.005 0.00071 0 0 0 0 0 0 0];

%crear matriz con datos
datos=[RojoSensor;VerdeEnergiaRS;AzulEnergiaRS];

% llamar funcion 
createfigure(distancia, datos)


%************************************************************************************
% datos considerando led rojo como sensor 
RojoEnergia = [4.23 3.99 3.91 3.86 3.81 3.7 3.41 3.02 3.06 2.97 2.68 2.37 2.68 2.47 2.27];
VerdeSensor = [0.95 0.27 0.15 0.063 0.03 0.018 0.013 0.010 0.011 0.008 0.005 0.003 0.003 0.00067 0];
AzulEnergia = [0.27 0.13 0.066 0.026 0.016 0.008 0.005 0.00071 0 0 0 0 0 0 0];

%crear matriz con datos
datos=[RojoEnergia;VerdeSensor;AzulEnergia];

% llamar funcion 
createfigure(distancia, datos)


