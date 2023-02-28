function FirstMoveIdx=GetFirstMoveIdx(X,Y, MoveDistPx)


len=length(X);
O = ones(1,len);
A = X(1)*O;
B = Y(1)*O;
S1 = A-X;
S2 = B-Y;
S = sqrt(S1.^2 + S2.^2);
cbt = find(S >= MoveDistPx);
FirstMoveIdx = cbt(1);

end
