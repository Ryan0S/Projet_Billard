function [IdxTouch]=GetTouchIdx(X,Y,Xmin, Xmax, Ymin, Ymax, BallBorderDist)

%%Xmax
len=length(X);
O = ones(1,len);
A = Xmax * O;
B = A-X;
cbt = find(B <= BallBorderDist);
if cbt(1) == 1
    cbt(:,1) = [];
end
Cons = diff(cbt);
IdCons = find(Cons == 1);
IdCons = IdCons + 1;
cbt(:,IdCons) = [];
IdxTouchXmax = cbt;

%%Xmin
len=length(X);
O = ones(1,len);
A = Xmin * O;
B = X-A;
cbt = find(B <= BallBorderDist);
if cbt(1) == 1
    cbt(:,1) = [];
end
Cons = diff(cbt);
IdCons = find(Cons == 1);
IdCons = IdCons + 1;
cbt(:,IdCons) = [];
IdxTouchXmin = cbt;

%%Ymax
len=length(Y);
O = ones(1,len);
A = Ymax * O;
B = A-Y;
cbt = find(B <= BallBorderDist);
if cbt(1) == 1
    cbt(:,1) = [];
end
Cons = diff(cbt);
IdCons = find(Cons == 1);
IdCons = IdCons + 1;
cbt(:,IdCons) = [];
IdxTouchYmax = cbt;

%%Ymin
len=length(Y);
O = ones(1,len);
A = Ymin * O;
B = Y - A;
cbt = find(B <= BallBorderDist);
if cbt(1) == 1
    cbt(:,1) = [];
end
Cons = diff(cbt);
IdCons = find(Cons == 1);
IdCons = IdCons + 1;
cbt(:,IdCons) = [];
IdxTouchYmin = cbt;

IdxTouch = sort([IdxTouchXmin IdxTouchXmax IdxTouchYmin IdxTouchYmax])


end
