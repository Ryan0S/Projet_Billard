function [Xmin, Xmax, Ymin, Ymax] = GetFrame(Xr,Yr,Xy,Yy,Xw,Yw)

% trouver le min de X
Xrmin = min(Xr);
Xymin = min(Xy);
Xwmin = min(Xw);
Xmin = min([Xrmin Xymin Xwmin]);

% trouver le max de X
Xrmax = max(Xr);
Xymax= max(Xy);
Xwmax = max(Xw);
Xmax = max([Xrmax Xymax Xwmax]);

% Trouver le min de Y
Yrmin = min(Yr);
Yymin = min(Yy);
Ywmin = min(Yw);
Ymin = min([Yrmin Yymin Ywmin]);

% trouver le max de Y
Yrmax = max(Yr);
Yymax = max(Yy);
Ywmax = max(Yw);
Ymax = max([Yrmax Yymax Ywmax]);

end
