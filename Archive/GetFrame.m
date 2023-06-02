function [Xmin, Xmax, Ymin, Ymax] = GetFrame(Xr,Yr,Xy,Yy,Xw,Yw)

%Find the smallest value of X
Xrmin = min(Xr);
Xymin = min(Xy);
Xwmin = min(Xw);
Xmin = min([Xrmin Xymin Xwmin]);

%find the biggest value of X
Xrmax = max(Xr);
Xymax= max(Xy);
Xwmax = max(Xw);
Xmax = max([Xrmax Xymax Xwmax]);

%Find the smallest value of Y
Yrmin = min(Yr);
Yymin = min(Yy);
Ywmin = min(Yw);
Ymin = min([Yrmin Yymin Ywmin]);

%find the biggest value of Y
Yrmax = max(Yr);
Yymax = max(Yy);
Ywmax = max(Yw);
Ymax = max([Yrmax Yymax Ywmax]);

end
