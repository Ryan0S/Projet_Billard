function [X,Y]=InterpolateNan(X,Y)

X=fillmissing(X,'next');
Y=fillmissing(Y,'next');
X=fillmissing(X,'previous');
Y=fillmissing(Y,'previous');

end
