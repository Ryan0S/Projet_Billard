function [FirstBall,SecondBall,LastBall, NbBallsMoved] = GetBallMoveOrder(Xr, Yr, Xy, Yy, Xw, Yw, MoveDistPx)
  
%Fetching first move id and distance from GetForstMoveIdx function

[IdR, DistR] = GetFirstMoveIdx(Xr,Yr, MoveDistPx);
[IdY, DistY] = GetFirstMoveIdx(Xy,Yy, MoveDistPx);
[IdW, DistW] = GetFirstMoveIdx(Xw,Yw, MoveDistPx);

%Counts the number of balls that moved
Id = [IdR IdY IdW];
NbBallsMoved = length(Id)

%Create a temporary matrix with the first move Id, first move distance and ball id of each ball
TempMatrix = [IdR -DistR 1; IdY -DistY 2; IdW -DistW 3];

%sorts the first move ids of the temporary matrix if two ids have the same value the first move distances are compared
TempMatrix = sortrows(TempMatrix);
FirstBall = TempMatrix(1,3);
SecondBall = TempMatrix(2,3);
LastBall = TempMatrix(3,3);

end
