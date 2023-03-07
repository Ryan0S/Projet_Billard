function [X,Y]=RemoveOutlier(X,Y)

sugma = isoutlier(X,"movmedian",10);
IdOutlierX = find(sugma == 1);
PrevIdOutlierX = IdOutlierX - 1;
X(IdOutlierX)=X(PrevIdOutlierX);

ligma = isoutlier(Y,"movmedian",10);
IdOutlierY = find(ligma == 1);
PrevIdOutlierY = IdOutlierY - 1;
Y(IdOutlierY)=Y(PrevIdOutlierY);
