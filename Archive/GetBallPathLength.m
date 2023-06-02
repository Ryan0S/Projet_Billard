function PathLength=GetBallPathLength(X,Y)

%Compute the difference between each succesive value of X and Y
X1=diff(X);
Y1=diff(Y);

%Use Pythagorean theorem to find the distance the ball moved between each succesive frame
S=sqrt(X1.^2+Y1.^2);

%Sum all of the individual movement to find the total pathlength
PathLength=sum(S);

end
