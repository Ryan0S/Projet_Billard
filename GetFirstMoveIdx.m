function [FirstMoveIdx, Dist]=GetFirstMoveIdx(X,Y, MoveDistPx)

%PARTIE 1

S1 = X(1)-X;%différence entre la première valeur de X et toutes les autres
S2 = Y(1)-Y;%différence entre la première valeur de Y et toutes les autres

S = sqrt(S1.^2 + S2.^2);%faire la norme de ces valeurs

cbt = find(S >= MoveDistPx);%matrice remplie des indices des frames auxquelles les boules bougent

FirstMoveIdx = cbt(1)%premier élément de cette matrice

%PARTIE 2

Dist = sqrt((X(FirstMoveIdx+1)-X(FirstMoveIdx))^2+(Y(FirstMoveIdx+1)-Y(FirstMoveIdx)^2);

end
