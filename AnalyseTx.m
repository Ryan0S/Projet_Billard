%% INFORMATION
%{
AnalyseTx.m

TAKES RAW BALLS COORDINATES DATA FROM A FRENCH POOL
GAME TO DISPLAY ANALYTICS ABOUT THE ROUND

THE CODE USES 7 DIFFERENT FUNCTIONS : 

    - GetBallMoveOrder
    - GetFirstMoveIdx
    - GetBallPathLength
    - GetFrame
    - GetTouchIdx
    - InterpolateNan
    - RemoveOutlier

(INFORMATION ABOUT EACH OF THEM BELOW)

INPUT
    - BALL'S POSITION ARRAYS

OUTPUT
    - PDF WITH INFORMATION ABOUT THE ROUND

AUTHORS : ROMAIN LATTION & RYAN SVOBODA

NOTE : THIS VERSION IS AN ANALYSIS OF T1 SEQUENCE
%}

%% DEFINE BALLS' COORDINATES %%

close all;
clear all;

Xr=[667	667	667	651	619	559	531	499	471	419	400	379	361	323	304	287	267	235	219	203	187	154	137	129	143	168	181	192	NaN	224	233	243	252	271	279	287	297	314	323	331	341	357	367	375	383	401	410	419	426	443	451	461	469	487	495	503	511	529	537	545	555	571	579	587	595	611	619	628	635	648	655	661	667	679	685	691	699	711	718	722	722	715	712	709	705	699	696	692	689	683	679	677	674	668	665	661	659	653	650	646	644	639	635	633	629	624	621	618	616	610	607	604	601	596	594	591	588	583	580	577	576	570	568	565	563	558	555	552	550	545	543	540	538	533	532	529	527	522	519	517	515	511	508];
Yr=[269	269	269	259	235	191	167	147	129	105	123	139	155	187	199	211	227	251	263	275	287	307	319	331	341	363	375	381	NaN	375	367	360	353	341	335	329	323	311	305	299	295	282	275	270	265	253	247	241	235	223	219	213	207	195	189	185	179	167	161	155	151	139	135	129	123	111	107	101	101	111	113	115	119	123	125	127	131	136	139	141	143	145	145	147	147	149	149	151	151	153	154	155	155	157	159	159	160	162	163	163	163	165	167	167	168	169	170	171	172	173	174	175	175	177	177	179	179	181	181	181	183	185	185	185	185	187	189	189	189	191	191	193	193	195	195	196	197	197	199	199	199	201	201];
Xy=[718	NaN	NaN	682	692	712	721	722	716	704	698	691	682	664	656	647	637	620	612	604	596	579	571	562	554	537	529	520	513	496	488	480	471	455	NaN	NaN	435	424	419	414	409	398	392	387	381	370	365	360	355	344	339	334	328	318	313	307	302	292	287	282	277	267	262	256	252	241	236	231	227	217	212	207	202	192	187	182	178	168	163	158	154	145	140	135	131	128	131	134	137	141	143	146	148	153	158	159	157	159	160	161	162	163	164	165	166	168	168	169	170	170	171	172	172	174	174	175	176	177	178	178	179	180	181	181	182	183	184	184	185	186	186	187	187	188	188	189	190	190	191	191	192	193	193];
Yy=[355	NaN	NaN	267	248	213	196	178	159	124	108	101	116	143	155	167	180	201	210	220	229	247	256	265	274	292	301	310	319	337	346	355	363	381	NaN	NaN	381	369	364	359	355	347	343	338	334	326	322	318	314	306	302	298	293	286	282	277	274	266	262	257	254	246	242	238	234	227	223	219	215	207	203	199	195	188	184	181	177	170	166	162	159	151	147	144	140	134	132	129	127	122	120	117	115	110	108	105	103	101	102	103	105	108	109	110	111	115	116	117	118	121	122	123	124	126	127	129	130	132	134	134	135	137	138	140	141	142	143	145	145	147	148	149	150	152	153	153	154	155	156	157	158	159	160];
Xw=[169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	169	171	172	173	175	175	176	178	179	180	181	183	184	184	185	187	187	188	189	190	191	192	193	194	195	195	196	197	198	198	199	200	200	201	201	202	203	203	203	204	205	205	205	206	206	206	206	207	207];
Yw=[113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	113	112	112	112	112	112	112	112	112	112	112	112	112	112	112	112	112	113	113	113	113	113	114	114	114	114	114	114	114	114	115	115	115	115	115	115	115	115	115	115	115	115	116	116	116	116	116	116	116	117	117	117	117	117	117	117	117	117	118	118	118	118	118	118];


%% VARIABLE DECLARATION 1 %%

%DEFINE THRESHOLD FOR EDGE CONTACT%
BallBorderDist=9;

%DEFINE THRESHHOLD FOR BALL MOVEMENT%
MoveDistPx=9;

%% DATA FILTERING AND FORMATING %%

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

%MAKE SURE WE HAVE AS MANY X VALUES AS Y VALUES%
if length(Xr) ~= length(Yr)
warning(length(Xr) ~= length(Yr))
end
if length(Xy) ~= length(Yy)
warning(length(Xy) ~= length(Yy))
end
if length(Xw) ~= length(Yw)
warning(length(Xw) ~= length(Yw))
end

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

FirstMoveIdxRed = GetFirstMoveIdx(Xr,Yr, MoveDistPx);
FirstMoveIdxYellow = GetFirstMoveIdx(Xy,Yy, MoveDistPx);
FirstMoveIdxWhite = GetFirstMoveIdx(Xw,Yw, MoveDistPx);

Sortedvalues = sort([FirstMoveIdxRed FirstMoveIdxYellow FirstMoveIdxWhite]);
Secondballmoving = Sortedvalues(2);
if length(Sortedvalues)==2
else
Thirdballmoving = Sortedvalues(3);
end

%% VARIABLE DECLARATION 2 %%

%DEFINE LENGTH AND WIDTH OF BOUNDARY BOX%
length_rectangle = Xmax-Xmin;
width_rectangle = Ymax-Ymin;

%DEFIN DATE FOR PLOT%
now_time = datetime('now');
date = datestr(now_time);

%DEFINE NAME OF SEQUENCE%
sequence='T1';


%% VICTORY DETECTION %%

%PLAYER DETECTION%

if FirstBall == 1
    band_touches = IdxTouch_r;
    if length(Sortedvalues)==2
    band_touches = band_touches(find(band_touches>=Secondballmoving));
    else
    band_touches = band_touches(find(band_touches>=Secondballmoving));
    band_touches = band_touches(find(band_touches<=Thirdballmoving));
    FirstBall_color = 'red';
    end

elseif FirstBall == 2
    band_touches = IdxTouch_y;

    if length(Sortedvalues)==2
    band_touches = band_touches(find(band_touches>=Secondballmoving));
    else
    band_touches = band_touches(find(band_touches>=Secondballmoving));
    band_touches = band_touches(find(band_touches<=Thirdballmoving));
    end
    FirstBall_color = 'yellow';

else
    band_touches = IdxTouch_w;
    if length(Sortedvalues)==2
    band_touches = band_touches(find(band_touches>=Secondballmoving));
    else
    band_touches = band_touches(find(band_touches>=Secondballmoving));
    band_touches = band_touches(find(band_touches<=Thirdballmoving));
    end
    FirstBall_color = 'white';

end

%VICTORY CONDITION : WIN%

if length(band_touches)>=3  && NbBallsMoved == 3
    result = '---WIN---';

%PLOTTING WIN %
Scores_sheet = rectangle('Position',[Xmin Ymin length_rectangle width_rectangle],'EdgeColor','b');

%HOLD ON TO PLOT ON SCORE SHEET%
hold on

%PLOT ALL THREE BALLS%
plot(Xr,Yr,'r-*');
plot(Xy,Yy,'y-*');
plot(Xw,Yw,'b-*');

%CHANGE PLOT DESCRIPTION%
set(gca,'XColor', 'none','YColor','none');
axis([Xmin-20, Xmax+20, Ymin-130, Ymax+20]);%change white zone around the plot
title(['Scores sheet - ' sequence ' - ' date]);
text(128, 70, ['Sheet score for the ' FirstBall_color ' ball :'], 'HorizontalAlignment', 'left','FontSize',8);
text(128, 50, result, 'HorizontalAlignment', 'left','FontSize',8);
text(600, 70, [ num2str(NbBallsMoved) ' ball(s) moved'],'HorizontalAlignment', 'left','FontSize',8);
text(600, 50, [ num2str(length(band_touches)) ' band(s) touched'],'HorizontalAlignment', 'left','FontSize',8);
text(128, 20, [ 'Red ball distance : ' num2str(PathLength_r) ' px'],'HorizontalAlignment', 'left','FontSize',8);
text(128, 0, [ 'Yellow ball distance : ' num2str(PathLength_y) ' px'],'HorizontalAlignment', 'left','FontSize',8);
text(128, -20, [ 'White ball distance : ' num2str(PathLength_w) ' px'],'HorizontalAlignment', 'left','FontSize',8);

%MARK THE BALLS' INITIAL POSTION%
Fr = plot(Xr(1), Yr(1), "hexagram",'Color','r');
Fr.MarkerSize = 15;
Fy = plot(Xy(1), Yy(1), "hexagram",'Color','y');
Fy.MarkerSize = 15;
Fw = plot(Xw(1), Yw(1), "hexagram",'Color','b');
Fw.MarkerSize = 15;

%MARK BAND CONTACTS%
if FirstBall == 1
rb = plot(Xr(band_touches), Yr(band_touches), "o", 'Color','#00FF00');
rb.MarkerSize = 15;
elseif FirstBall == 2
rb = plot(Xy(band_touches), Yy(band_touches), "o", 'Color','#00FF00');
rb.MarkerSize = 15;
else FirstBall == 3
rb = plot(Xw(band_touches), Yw(band_touches), "o", 'Color','#00FF00');
rb.MarkerSize = 15;
end
saveas(gcf,'ScoresheetT11.pdf')
%END PLOT%
hold off;


%VICTORY CONDITION : LOOSE%
else
    result = '---LOOSE---';

%PLOTTING LOOSE %
Scores_sheet = rectangle('Position',[Xmin Ymin length_rectangle width_rectangle],'EdgeColor','b');

%HOLD ON TO PLOT ON SCORE SHEET%
hold on

%PLOT ALL THREE BALLS%
plot(Xr,Yr,'r-*');
plot(Xy,Yy,'y-*');
plot(Xw,Yw,'b-*');

%CHANGE PLOT DESCRIPTION%
set(gca,'XColor', 'none','YColor','none');
axis([Xmin-20, Xmax+20, Ymin-130, Ymax+20]);%change white zone around the plot
title(['Scores sheet - ' sequence ' - ' date]);
text(128, 70, ['Sheet score for the ' FirstBall_color ' ball :'], 'HorizontalAlignment', 'left','FontSize',8);
text(128, 50, result, 'HorizontalAlignment', 'left','FontSize',8);
text(600, 70, [ num2str(NbBallsMoved) ' ball(s) moved'],'HorizontalAlignment', 'left','FontSize',8);
text(600, 50, [ num2str(length(band_touches)) ' band(s) touched'],'HorizontalAlignment', 'left','FontSize',8);
text(128, 20, [ 'Red ball distance : ' num2str(PathLength_r) ' px'],'HorizontalAlignment', 'left','FontSize',8);
text(128, 0, [ 'Yellow ball distance : ' num2str(PathLength_y) ' px'],'HorizontalAlignment', 'left','FontSize',8);
text(128, -20, [ 'White ball distance : ' num2str(PathLength_w) ' px'],'HorizontalAlignment', 'left','FontSize',8);

%MARK THE BALLS' INITIAL POSTION%
Fr = plot(Xr(1), Yr(1), "hexagram",'Color','r');
Fr.MarkerSize = 15;
Fy = plot(Xy(1), Yy(1), "hexagram",'Color','y');
Fy.MarkerSize = 15;
Fw = plot(Xw(1), Yw(1), "hexagram",'Color','b');
Fw.MarkerSize = 15;

%MARK BAND CONTACTS%
if FirstBall == 1
if isempty(Xr(band_touches))
else
rb = plot(Xr(band_touches), Yr(band_touches), "o", 'Color','#FF0000');
rb.MarkerSize = 15;
end
elseif FirstBall == 2
if isempty(Xy(band_touches))
else
rb = plot(Xy(band_touches), Yy(band_touches), "o", 'Color','#FF0000');
rb.MarkerSize = 15;
end
else FirstBall == 3
if isempty(Xw(band_touches))
else
rb = plot(Xw(band_touches), Yw(band_touches), "o", 'Color','#FF0000');
rb.MarkerSize = 15;
end
end
saveas(gcf,'ScoresheetTx(T11).pdf')
hold off;
end

%% DECLARING FUNCTIONS %%

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

if NbBallsMoved == 3
%CREATE A TEMPORARY MATRIX TO STORE THE FIRST MOVE ID, FIRST MOVE DISTANCE AND BALL ID OF EACH BALL%
TempMatrix = [IdR -DistR 1; IdY -DistY 2; IdW -DistW 3];

%SORTS TO FIND FIRST MOVE ID ORDER (USES FIRST MOVE DISTANCE IN CASE OF DRAW)%
TempMatrix = sortrows(TempMatrix);

%DEFINE OUTPUT VALUES%
FirstBall = TempMatrix(1,3);
SecondBall = TempMatrix(2,3);
LastBall = TempMatrix(3,3);

elseif NbBallsMoved == 2

if DistR == 0

%CREATE A TEMPORARY MATRIX TO STORE THE FIRST MOVE ID, FIRST MOVE DISTANCE AND BALL ID OF EACH BALL%
TempMatrix = [IdY -DistY 2; IdW -DistW 3];

%SORTS TO FIND FIRST MOVE ID ORDER (USES FIRST MOVE DISTANCE IN CASE OF DRAW)%
TempMatrix = sortrows(TempMatrix);

FirstBall = TempMatrix(1,3);
SecondBall = TempMatrix(2,3);
LastBall = 1;

elseif DistW == 0

%CREATE A TEMPORARY MATRIX TO STORE THE FIRST MOVE ID, FIRST MOVE DISTANCE AND BALL ID OF EACH BALL%
TempMatrix = [IdR -DistR 1; IdY -DistY 2];

%SORTS TO FIND FIRST MOVE ID ORDER (USES FIRST MOVE DISTANCE IN CASE OF DRAW)%
TempMatrix = sortrows(TempMatrix);

FirstBall = TempMatrix(1,3);
SecondBall = TempMatrix(2,3);
LastBall = 3;

else

%CREATE A TEMPORARY MATRIX TO STORE THE FIRST MOVE ID, FIRST MOVE DISTANCE AND BALL ID OF EACH BALL%
TempMatrix = [IdR -DistR 1; IdW -DistW 3];

%SORTS TO FIND FIRST MOVE ID ORDER (USES FIRST MOVE DISTANCE IN CASE OF DRAW)%
TempMatrix = sortrows(TempMatrix);

FirstBall = TempMatrix(1,3);
SecondBall = TempMatrix(2,3);
LastBall = 2;
end

end

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
if PathLength <= 9
    PathLength = 0;
end
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
if isempty(TempMatrix)
Dist = 0;  
FirstMoveIdx = [];
else
FirstMoveIdx = TempMatrix(1);
%COMPUTE INNITIAL MOVE DISTANCE%
Dist = sqrt((X(FirstMoveIdx)-X(FirstMoveIdx-1))^2+(Y(FirstMoveIdx)-Y(FirstMoveIdx-1))^2);
end
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

% OUTPUTS: - ALL FRAMES WHEN BALL TOUCHED EDGE (IdxTouch)%

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

%CHECKS IF THERE IS ANY OUTLIER
if isempty(IdOutlier)

%REMOVES FIRST FRAME FROM OUTLIERS%
else

    if IdOutlier(1) == 1
    IdOutlier(1) = [];
    end

%REPLACE OUTLIERS WITH PREVIOUS NON OUTLIER VALUE%
PrevIdOutlier = IdOutlier - 1;
X(IdOutlier)= X(PrevIdOutlier);
Y(IdOutlier)= Y(PrevIdOutlier);
end
end
