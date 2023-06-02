%% VARIABLE DECLARATION %%

%DEFINE THRESHOLD FOR EDGE CONTACT%
BallBorderDist=9;

%DEFINE THRESHHOLD FOR BALL MOVEMENT%
MoveDistPx=9;

%% DATA FILLTERING AND FORMATING %%

%CHANGE COORDINATE SYSTEM%
Yr=480-Yr;
Yy=480-Yy;
Yw=480-Yw;

%REPLACE ALL NAN VALUES WITH APPROPRIATE VALUE%
[Xr, Yr] = InterpolateNan(Xr,Yr);
[Xy, Yy] = InterpolateNan(Xy,Yy);
[Xw, Yw] = InterpolateNan(Xw,Yw);

%REMOVE ALL OUTLIERS%
[Xr, Yr] = RemoveOutlier(Xr,Yr);
[Xy, Yy] = RemoveOutlier(Xy,Yy);
[Xw, Yw] = RemoveOutlier(Xw,Yw);

%% COMPUTATION %%

%FIND THE BOUNDARY BOX%
[Xmin, Xmax, Ymin, Ymax] = GetFrame(Xr,Yr,Xy,Yy,Xw,Yw);

%COMPUTE PATH LENGTH%
PathLength_r = GetBallPathLength(Xr,Yr);
PathLength_y = GetBallPathLength(Xy,Yy);
PathLength_w = GetBallPathLength(Xw,Yw);

%FIND INSTANCES WHEN BALLS TOUCH EDGE%
[IdxTouch_r]=GetTouchIdx(Xr,Yr,Xmin, Xmax, Ymin, Ymax, BallBorderDist);
[IdxTouch_y]=GetTouchIdx(Xy,Yy,Xmin, Xmax, Ymin, Ymax, BallBorderDist);
[IdxTouch_w]=GetTouchIdx(Xw,Yw,Xmin, Xmax, Ymin, Ymax, BallBorderDist);

%FIND BALL MOVE ORDER%
[FirstBall,SecondBall,LastBall, NbBallsMoved] = GetBallMoveOrder(Xr, Yr, Xy, Yy, Xw, Yw, MoveDistPx);

%% VARIABLE DECLARATION %%

%DEFINE LENGTH AND WIDTH OF BOUNDARY BOX%
length_rectangle = Xmax-Xmin;
width_rectangle = Ymax-Ymin;

%DEFIN DATE FOR PLOT%
now_time = datetime('now');
date = datestr(now_time);

%DEFINE NAME OF SEQUENCE%
sequence='T1';


%% VICTORY DETECTION%%

%PLAYER DETECTION%
if FirstBall == 1
    band_touches = IdxTouch_r;
    FirstBall_color = 'red';
elseif FirstBall == 2
    band_touches = IdxTouch_y;
    FirstBall_color = 'yellow';
else
    band_touches = IdxTouch_w;
    FirstBall_color = 'white';
end

%VICTORY CONDITION%
if length(band_touches)>=3 
    result = '---WIN---';
else
    result = '---LOOSE---';
end


%% PLOTTING %%

%CREATE SCORE SHEET%
Scores_sheet = rectangle('Position',[Xmin Ymin length_rectangle width_rectangle],'EdgeColor','b');

%HOLD ON TO PLOT ON SCORE SHEET%
hold on

%PLOT ALL THREE BALLS%
plot(Xr,Yr,'r-*');
plot(Xy,Yy,'y-o');
plot(Xw,Yw,'b-+');

%CHANGE PLOT DESCRIPTION%
set(gca,'XColor', 'none','YColor','none');
axis([Xmin-20, Xmax+20, Ymin-130, Ymax+20]);
title(['Scores sheet - ' sequence ' - ' date]);
text(128, 70, ['Sheet score for the ' FirstBall_color ' ball :'], 'HorizontalAlignment', 'left','FontSize',8);
text(128, 50, result, 'HorizontalAlignment', 'left','FontSize',8);
text(600, 70, [ num2str(NbBallsMoved) ' ball(s) moved'],'HorizontalAlignment', 'left','FontSize',8);
text(600, 50, [ num2str(length(IdxTouch_y)) ' band(s) touched'],'HorizontalAlignment', 'left','FontSize',8);
text(128, 20, [ 'Red ball distance : ' num2str(PathLength_r) ' px'],'HorizontalAlignment', 'left','FontSize',8);
text(128, 0, [ 'Yellow ball distance : ' num2str(PathLength_y) ' px'],'HorizontalAlignment', 'left','FontSize',8);
text(128, -20, [ 'White ball distance : ' num2str(PathLength_w) ' px'],'HorizontalAlignment', 'left','FontSize',8);

%MARK THE BALLS' INITIAL POSTION%
Fr = plot(Xr(1), Yr(1), "hexagram");
Fr.MarkerSize = 30;
Fy = plot(Xy(1), Yy(1), "hexagram");
Fy.MarkerSize = 30;
Fw = plot(Xw(1), Yw(1), "hexagram");
Fw.MarkerSize = 30;

%MARK EDGE CONTACTS%
if FirstBall == 1
    rb = plot(Xr(IdxTouch_r), Yr(IdxTouch_r), "o");
rb.MarkerSize = 25;
elseif FirstBall == 2
    rb = plot(Xy(IdxTouch_y), Yy(IdxTouch_y), "o");
rb.MarkerSize = 25;
else FirstBall == 3
    rb = plot(Xw(IdxTouch_w), Yw(IdxTouch_w), "o");
rb.MarkerSize = 25;
end

%END PLOT%
hold off;


%% DECLARING FUNCSTIONS %%

function [FirstBall,SecondBall,LastBall, NbBallsMoved] = GetBallMoveOrder(Xr, Yr, Xy, Yy, Xw, Yw, MoveDistPx)
%TLDR: FIND IN WHICH ORDER THE BALLS MOVED%

% INPUTS:  - ALL OF THE BALLS' COORDINATES(Xr, Yr, Xy, Yy, Xw, Yw)
%          - THRESHOLD TO DETECT BALL MOVEMENT(MoveDistPx)%

% OUTPUTS: - ID OF THE FIRST BALL THAT MOVED (FirstBall)
%          - ID OF THE FIRST BALL THAT MOVED (SecondBall)
%          - ID OF THE FIRST BALL THAT MOVED (LastBall)
%          - A COUNT OF HOW MANY BALLS MOVED (NbBallsMoved)%
  
%FETCHING FIRST MOVE ID AND DISTANCE MOVED FROM GetForstMoveIdx%
[IdR, DistR] = GetFirstMoveIdx(Xr,Yr, MoveDistPx);
[IdY, DistY] = GetFirstMoveIdx(Xy,Yy, MoveDistPx);
[IdW, DistW] = GetFirstMoveIdx(Xw,Yw, MoveDistPx);

%COUNTS THE NUMBER OF BALLS THAT MOVED%
Id = [IdR IdY IdW];
NbBallsMoved = length(Id);

%CREATE A TEMPORARY MATRIX TO STORE THE FIRST MOVE ID, FIRST MOVE DISTANCE AND BALL ID OF EACH BALL%
TempMatrix = [IdR -DistR 1; IdY -DistY 2; IdW -DistW 3];

%SORTS TO FIND FIRST MOVE ID ORDER (USES FIRST MOVE DISTANCE IN CASE OF DRAW)%
TempMatrix = sortrows(TempMatrix);

%DEFINE OUTPUT VALUES%
FirstBall = TempMatrix(1,3);
SecondBall = TempMatrix(2,3);
LastBall = TempMatrix(3,3);
end

function PathLength=GetBallPathLength(X,Y)
%TLDR: FIND TOTAL PATH LENGTH%

% INPUTS:  - COORDINATES OF ONE BALL(X,Y)%

% OUTPUTS: - PATHLENGTH (PathLength)%

%COMPUTE THE DIFFENCE IN BETWEEN EACH SUCCESSIVE VALUE OF X AND THEN Y%
X1=diff(X);
Y1=diff(Y);

%USE PYTHAGOREAN THEOREM TO COMPUTE DISTANCE THE BALL MOVED BETWEEN EACH SUCCESIVE FRAME%
S=sqrt(X1.^2+Y1.^2);

%SUM ALL THE INDIVIDUAL MOVEMENTS TO FIND THE TOTAL PATHLENGTH%
PathLength=sum(S);
end

function [FirstMoveIdx, Dist]=GetFirstMoveIdx(X,Y, MoveDistPx)
%TLDR: FIND THE THE FRAME AT WHICH A BALL FIRST MOVES%

% INPUTS:  - COORDINATES OF ONE BALL(X,Y)
%          - THRESHOLD TO DETECT BALL MOVEMENT(MoveDistPx)%

% OUTPUTS: - FRAME AT WHICH THE BALL MOVED (FirstMoveIdx)
%          - DISTANCE THE BALL MOVED INTIALLY MOVED (Dist)%

%DIFFERENCE IN BETWEEN THE FIRST VALUE OF X AND ALL THE OTHER VALUES OF X%
dx = X(1)-X;

%DIFFERENCE IN BETWEEN THE FIRST VALUE OF Y AND ALL THE OTHER VALUES OF Y%
dy = Y(1)-Y;

%COMPUTE THE MOVE DISTANCE IN BETWEEN THE FIRST FRAME AND EVERY OTHER FRAME%
S = sqrt(dx.^2 + dy.^2);

%CREATE TEMPORARY MATRIX WHICH STORES EVERY FRAME WHERE THE BALL MOVEMENT PASSED THE THRESHHOLD%
TempMatrix = find(S > MoveDistPx);

%FINDS THE FIRST FRAME WHERE THE BALL MOVED%
FirstMoveIdx = TempMatrix(1);

%COMPUTE INNITIAL MOVE DISTANCE%
Dist = sqrt(X(FirstMoveIdx)-X(FirstMoveIdx-1))^2+(Y(FirstMoveIdx)-Y(FirstMoveIdx-1)^2);
end

function [Xmin, Xmax, Ymin, Ymax] = GetFrame(Xr,Yr,Xy,Yy,Xw,Yw)
%TLDR: FIND THE OUTLINE OF THE TABLE%

% INPUTS:  - ALL OF THE BALLS' COORDINATES(Xr, Yr, Xy, Yy, Xw, Yw)%

% OUTPUTS: - ALL OF THE EDGES OF THE TABLE (Xmin, Xmax, Ymin, Ymax)%

%FIND THE SMALLEST VALUES OF X%
Xrmin = min(Xr);
Xymin = min(Xy);
Xwmin = min(Xw);
Xmin = min([Xrmin Xymin Xwmin]);

%FIND THE BIGGEST VALUES OF X%
Xrmax = max(Xr);
Xymax= max(Xy);
Xwmax = max(Xw);
Xmax = max([Xrmax Xymax Xwmax]);

%FIND THE SMALLEST VALUES OF Y%
Yrmin = min(Yr);
Yymin = min(Yy);
Ywmin = min(Yw);
Ymin = min([Yrmin Yymin Ywmin]);

%FIND THE BIGGEST VALUES OF Y%
Yrmax = max(Yr);
Yymax = max(Yy);
Ywmax = max(Yw);
Ymax = max([Yrmax Yymax Ywmax]);
end

function [IdxTouch]=GetTouchIdx(X,Y,Xmin, Xmax, Ymin, Ymax, BallBorderDist)
%TLDR: FIND FRAMES WHEN BALLS MAKE CONTACT WITH EDGE%

% INPUTS:  - COORDINATES OF ONE BALL(X,Y)
%          - THRESHOLD TO DETECT CONTACT (BallBorderDist)
%          - ALL OF THE EDGES OF THE TABLE (Xmin, Xmax, Ymin, Ymax)%

% OUTPUTS: - ALL FRAMES WHEN BALL TOUCHED EDGE (FirstBall)%

%RIGHT EDGE
%FIND ALL FRAMES WHERE BALL IS BESIDE EDGE%
DiffXmax = Xmax-X;
cbt = find(DiffXmax <= BallBorderDist);

%CHECKS IF BALL DID NOT MAKE CONTACT%
if isempty(cbt)
    IdxTouchXmax = [];

else
    %REMOVES FIRST FRAME FROM IDS WHEN BALL MAKES CONTACT%
    if cbt(1) == 1
        cbt(1) = []; 
    end

    %REMOVE SUCCESSIVE FRAMES%
    Cons = diff(cbt);
    IdCons = find(Cons == 1);
    IdCons = IdCons + 1;
    cbt(:,IdCons) = [];

    %STORE IDS%
    IdxTouchXmax = cbt;%matrice des index où la boule touche Xmax
end

%LEFT EDGE
%FIND ALL FRAMES WHERE BALL IS BESIDE EDGE%
DiffXmin = X-Xmin;
cbt = find(DiffXmin <= BallBorderDist);

%CHECKS IF BALL DID NOT MAKE CONTACT%
if isempty(cbt)
    IdxTouchXmin = [];

else
    %REMOVES FIRST FRAME FROM IDS WHEN BALL MAKES CONTACT%
    if cbt(1) == 1
        cbt(1) = []; 
    end

    %REMOVE SUCCESSIVE FRAMES%
    Cons = diff(cbt);
    IdCons = find(Cons == 1);
    IdCons = IdCons + 1;
    cbt(:,IdCons) = [];

    %STORE IDS%
    IdxTouchXmin = cbt;%matrice des index où la boule touche Xmax
end

%TOP EDGE
%FIND ALL FRAMES WHERE BALL IS BESIDE EDGE%
DiffYmax = Ymax-Y;
cbt = find(DiffYmax <= BallBorderDist);

%CHECKS IF BALL DID NOT MAKE CONTACT%
if isempty(cbt)
    IdxTouchYmax = [];

else
    %REMOVES FIRST FRAME FROM IDS WHEN BALL MAKES CONTACT%
    if cbt(1) == 1
        cbt(1) = []; 
    end

    %REMOVE SUCCESSIVE FRAMES%
    Cons = diff(cbt);
    IdCons = find(Cons == 1);
    IdCons = IdCons + 1;
    cbt(:,IdCons) = [];

    %STORE IDS%
    IdxTouchYmax = cbt;%matrice des index où la boule touche Xmax
end

%BOTTOM EDGE
%FIND ALL FRAMES WHERE BALL IS BESIDE EDGE%
DiffYmin = Y-Ymin;
cbt = find(DiffYmin <= BallBorderDist);

%CHECKS IF BALL DID NOT MAKE CONTACT%
if isempty(cbt)
    IdxTouchYmin = [];

else
    %REMOVES FIRST FRAME FROM IDS WHEN BALL MAKES CONTACT%
    if cbt(1) == 1
        cbt(1) = []; 
    end

    %REMOVE SUCCESSIVE FRAMES%
    Cons = diff(cbt);
    IdCons = find(Cons == 1);
    IdCons = IdCons + 1;
    cbt(:,IdCons) = [];

    %STORE IDS%
    IdxTouchYmin = cbt;%matrice des index où la boule touche Xmax
end

IdxTouch = sort([IdxTouchXmin IdxTouchXmax IdxTouchYmin IdxTouchYmax]);

end

function [X,Y]=InterpolateNan(X,Y)
%TLDR: FILL MISSING VALUES WITH NEXT VALUE OR PREVIOUS VALUE IF LAST VALUE%

% INPUTS:  - COORDINATES OF ONE BALL(X,Y)%

% OUTPUTS: - COORDINATES OF ONE BALL(X,Y)%

X=fillmissing(X,'next');
Y=fillmissing(Y,'next');
X=fillmissing(X,'previous');
Y=fillmissing(Y,'previous');
end

function [X,Y]=RemoveOutlier(X,Y)
%TLDR: REMOVE OUTLIER BY WAY OF A MOVING MEDIAN%

% INPUTS:  - COORDINATES OF ONE BALL(X,Y)%

% OUTPUTS: - COORDINATES OF ONE BALL(X,Y)%

%FIND OUTLIERS%
XOutlier = isoutlier(X,"movmedian",10);
IdOutlierX = find(XOutlier);
YOutlier = isoutlier(Y,"movmedian",10);
IdOutlierY = find(YOutlier);
IdOutlier = intersect(IdOutlierX, IdOutlierY);
    
%REMOVES FIRST FRAME FROM OUTLIERS%
if IdOutlier(1) == 1
    IdOutlier(1) = [];
end

%REPLACE OUTLIERS WITH PREVIOUS NON OUTLIER VALUE%
PrevIdOutlier = IdOutlier - 1;
X(IdOutlier)= X(PrevIdOutlier);
Y(IdOutlier)= Y(PrevIdOutlier);
end
