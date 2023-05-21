function [FirstBall,SecondBall,LastBall, NbBallsMoved] = GetBallMoveOrder(Xr, Yr, Xy, Yy, Xw, Yw, MoveDistPx)
  
[IdR, DistR] = GetFirstMoveIdx(Xr,Yr, MoveDistPx);
[IdY, DistY] = GetFirstMoveIdx(Xy,Yy, MoveDistPx);
[IdW, DistW] = GetFirstMoveIdx(Xw,Yw, MoveDistPx);

Id = [IdR IdY IdW];

TempMatrix = [IdR -DistR 1; IdY -DistY 2; IdW -DistW 3];
TempMatrix = sortrows(TempMatrix);
FirstBall = TempMatrix(1,3);
SecondBall = TempMatrix(2,3);
LastBall = TempMatrix(3,3);
NbBallsMoved = length(Id)

end
