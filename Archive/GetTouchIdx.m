function [IdxTouch]=GetTouchIdx(X,Y,Xmin, Xmax, Ymin, Ymax, BallBorderDist)

%%Xmax
DiffXmax = Xmax-X;%diff. entre Xmax et la matrice X -> matrice
cbt = find(DiffXmax < BallBorderDist);%cbt est une matrice remplie des indices des éléments
                                        %de DiffXmax qui sont <= à BallBorderDist
if isempty(cbt)
    IdxTouchXmax = [];
elseif cbt(1) == 1%test si le premier élément de cbt est la position initiale de la balle.
    cbt(1) = [];%si c'est le cas, on a donc que la boule "touche" la bande 
end%sans avoir été jouée -> on ne compte pas comme rebond !


Cons = diff(cbt);%diff. des éléments de cbt 2à2
IdCons = find(Cons == 1);%trouver tous les indices de Cons ou les valeurs valent 1
                           %ce qui implique 2 éléments consécutifs proches
                           %de la bande
IdCons = IdCons + 1;%ajouer 1 à cela pour ne pas supprimer le premier élément
cbt(:,IdCons) = [];%supprimer les éléments aux positions IdCons
IdxTouchXmax = cbt;%matrice des index où la boule touche Xmax

%%Xmin
DiffXMin = X-Xmin;%...
cbt = find(DiffXMin < BallBorderDist);
if isempty(cbt)
    IdxTouchXmin = [];
elseif cbt(1) == 1
    cbt(1) = [];
end
Cons = diff(cbt);
IdCons = find(Cons == 1);
IdCons = IdCons + 1;
cbt(:,IdCons) = [];
IdxTouchXmin = cbt;

%%Ymax
DiffYmax = Ymax-Y;
cbt = find(DiffYmax < BallBorderDist);
if isempty(cbt)
    IdxTouchYmax = [];
elseif cbt(1) == 1
    cbt(1) = [];
end
Cons = diff(cbt);
IdCons = find(Cons == 1);
IdCons = IdCons + 1;
cbt(:,IdCons) = [];
IdxTouchYmax = cbt;

%%Ymin
DiffYmin = Y-Ymin;
cbt = find(DiffYmin < BallBorderDist);
if isempty(cbt)
    IdxTouchYmin = [];
elseif cbt(1) == 1
    cbt(1) = [];
end
Cons = diff(cbt);
IdCons = find(Cons == 1);
IdCons = IdCons + 1;
cbt(:,IdCons) = [];
IdxTouchYmin = cbt;

IdxTouch = sort([IdxTouchXmin IdxTouchXmax IdxTouchYmin IdxTouchYmax])

end
