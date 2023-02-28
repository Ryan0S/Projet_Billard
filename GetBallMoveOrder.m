function [FirstBall,SecondBall,LastBall, NbBallsMoved] = GetBallMoveOrder(Xr, Yr, Xy, Yy, Xw, Yw, MoveDistPx)

[IdR, DistR] = GetFirstMoveIdx(Xr,Yr, MoveDistPx);
[IdY, DistY] = GetFirstMoveIdx(Xy,Yy, MoveDistPx);
[IdW, DistW] = GetFirstMoveIdx(Xw,Yw, MoveDistPx);

cbt = [IdR -DistR 1; IdY -DistY 2; IdW -DistW 3];
cock = sortrows(cbt);
FirstBall = cock(1,3);
SecondBall = cock(2,3);
LastBall = cock(3,3);
NbBallsMoved = length(Id)

end