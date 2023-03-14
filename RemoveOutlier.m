function [X,Y]=RemoveOutlier(X,Y)

sugma = isoutlier(X,"movmedian",10);
IdOutlierX = find(sugma);

ligma = isoutlier(Y,"movmedian",10);
IdOutlierY = find(ligma);

IdOutlier = intersect(IdOutlierX, IdOutlierY);

if isempty(IdOutlier)
    
elseif IdOutlier(1) == 1
    IdOutlier(1) = [];
    PrevIdOutlier = IdOutlier - 1;
    X(IdOutlier)= X(PrevIdOutlier);
    Y(IdOutlier)= Y(PrevIdOutlier);
else 
    PrevIdOutlier = IdOutlier - 1;
    X(IdOutlier)= X(PrevIdOutlier);
    Y(IdOutlier)= Y(PrevIdOutlier);
end

end
