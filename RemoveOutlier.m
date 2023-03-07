function [X,Y]=RemoveOutlier(X,Y)

sugma = isoutlier(X,"movmedian",10);
IdOutlierX = find(sugma);
if IdOutlierX(1) == 1
    IdOutlierX(1) = [];
end
PrevIdOutlierX = IdOutlierX - 1;
X(IdOutlierX)= X(PrevIdOutlierX);

ligma = isoutlier(Y,"movmedian",10);
IdOutlierY = find(ligma)
if IdOutlierY(1) == 1
    IdOutlierY(1) = [];
end
PrevIdOutlierY = IdOutlierY - 1;
Y(IdOutlierY)=Y(PrevIdOutlierY);

end
