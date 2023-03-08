function [Xmin, Xmax, Ymin, Ymax] = GetFrame(Xr,Yr,Xy,Yy,Xw,Yw)

    
Xr = fillmissing(Xr,'next');% fillmissing replaces NaN values
Yr = fillmissing(Yr,'next');% 'next' tells to replace with the next non-Nan value
Xy = fillmissing(Xy,'next');
Yy = fillmissing(Yy,'next');
Xw = fillmissing(Xw,'next');
Yw = fillmissing(Yw,'next');

% Invert of Y-values because of non-equivalence between
% 0-Matlab and 0-Labview

Yrinvert = Yr;
Yyinvert = Yy;
Ywinvert = Yw;

% Find the min. value of x

minXr = min(Xr);
minXy = min(Xy);
minXw = min(Xw);
minX = min([minXr minXy minXw]);

% Find the max. value of the x

maxXr = max(Xr);
maxXy = max(Xy);
maxXw = max(Xw);
maxX = max([maxXr maxXy maxXw]);

% Find the min. value of inverted y

minYrinvert = min(Yrinvert);
minYyinvert = min(Yyinvert);
minYwinvert = min(Ywinvert);
minYinvert = min([minYrinvert minYyinvert minYwinvert]);

% Find the max. value of inverted y

maxYrinvert = max(Yrinvert);
maxYyinvert = max(Yyinvert);
maxYwinvert = max(Ywinvert);
maxYinvert = max([maxYrinvert maxYyinvert maxYwinvert]);

Xmin=minX;
Xmax=maxX;
Ymin=minYinvert;
Ymax=maxYinvert;

end
