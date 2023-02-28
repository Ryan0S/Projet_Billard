function PathLength=GetBallPathLength(X,Y)
% Que faire ?
% Faire la somme des normes des veceturs entre chaque point 2 à 2

X1=diff(X);% diff : différence d'éléments successifs 2 à 2
Y1=diff(Y);% et les rend sous forme de matrice
S=sqrt(X1.^2+Y1.^2);
PathLength=sum(S);

end