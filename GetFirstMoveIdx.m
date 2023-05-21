function [FirstMoveIdx, Dist]=GetFirstMoveIdx(X,Y, MoveDistPx)

%difference inbetween the first value of X and all the other values of X
dx = X(1)-X;

%difference inbetween the first value of Y and all the other values of Y
dy = Y(1)-Y;

%Compute the actual move distance using Pythagorean theroem
S = sqrt(dx.^2 + dy.^2);

%Creates a temporary matrix with all of the frames where the ball is further than MoveDistPx from its initial postion
TempMatrix = find(S > MoveDistPx);

%Finds the first frame where the ball moved enough
FirstMoveIdx = TempMatrix(1);

%compute initial move distance
Dist = sqrt((X(FirstMoveIdx)-X(FirstMoveIdx-1))^2+(Y(FirstMoveIdx)-Y(FirstMoveIdx-1)^2);

end
