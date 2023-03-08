function [X,Y]=RemoveOutlier(X,Y)

sugma = isoutlier(X,"movmedian",10);
IdOutlierX = find(sugma);
if isempty(IdOutlierX)
    
elseif IdOutlierX(1) == 1
    IdOutlierX(1) = [];
    PrevIdOutlierX = IdOutlierX - 1;
    X(IdOutlierX)= X(PrevIdOutlierX);
else 
    PrevIdOutlierX = IdOutlierX - 1;
    X(IdOutlierX)= X(PrevIdOutlierX);
end


ligma = isoutlier(Y,"movmedian",10);
IdOutlierY = find(ligma);
if isempty(IdOutlierY)
    
elseif IdOutlierY(1) == 1
    IdOutlierY(1) = [];
    PrevIdOutlierY = IdOutlierY - 1;
    Y(IdOutlierY)= Y(PrevIdOutlierY);
else 
    PrevIdOutlierY = IdOutlierY - 1;
    Y(IdOutlierY)= Y(PrevIdOutlierY);
end

end
