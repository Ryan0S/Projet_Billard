Xr=[667 667 667 651 619 559 531 499 471 419 400 379 361 323 304 287 267 235 219 203 187 154 137 129 143 168 181 192 203 224 233 243 252 271 279 287 297 314 323 331 341 357 367 375 383 401 410 419 426 443 451 461 469 487 495 503 511 529 537 545 555 571 579 587 595 611 619 628 635 648 655 661 667 679 685 691 699 711 718 723 725 715 712 709 705 699 696 692 689 683 679 677 674 668 665 661 659 653 650 646 644 639 635 633 629 624 621 618 616 610 607 604 601 596 594 591 588 583 580 577 576 570 568 565 563 558 555 552 550 545 543 540 538 533 532 529 527 522 519 517 515 511 508
]; 
Yr=[269 269 269 259 235 191 167 147 129 105 123 139 155 187 199 211 227 251 263 275 287 307 319 331 341 363 375 386 393 375 367 360 353 341 335 329 323 311 305 299 295 282 275 270 265 253 247 241 235 223 219 213 207 195 189 185 179 167 161 155 151 139 135 129 123 111 107 101 101 111 113 115 119 123 125 127 131 136 139 141 143 145 145 147 147 149 149 151 151 153 154 155 155 157 159 159 160 162 163 163 163 165 167 167 168 169 170 171 172 173 174 175 175 177 177 179 179 181 181 181 183 185 185 185 185 187 189 189 189 191 191 193 193 195 195 196 197 197 199 199 199 201 201
]; 
Xy=[718 NaN NaN 682 692 712 721 723 716 704 698 691 682 664 656 647 637 620 612 604 596 579 571 562 554 537 529 520 513 496 488 480 471 455 447 440 435 424 419 414 409 398 392 387 381 370 365 360 355 344 339 334 328 318 313 307 302 292 287 282 277 267 262 256 252 241 236 231 227 217 212 207 202 192 187 182 178 168 163 158 154 145 140 135 131 128 131 134 137 141 143 146 148 153 158 159 157 159 160 161 162 163 164 165 166 168 168 169 170 170 171 172 172 174 174 175 176 177 178 178 179 180 181 181 182 183 184 184 185 186 186 187 187 188 188 189 190 190 191 191 192 193 193
]; 
Yy=[355 NaN NaN 267 248 213 196 178 159 124 108 101 116 143 155 167 180 201 210 220 229 247 256 265 274 292 301 310 319 337 346 355 363 382 390 389 381 369 364 359 355 347 343 338 334 326 322 318 314 306 302 298 293 286 282 277 274 266 262 257 254 246 242 238 234 227 223 219 215 207 203 199 195 188 184 181 177 170 166 162 159 151 147 144 140 134 132 129 127 122 120 117 115 110 108 105 103 101 102 103 105 108 109 110 111 115 116 117 118 121 122 123 124 126 127 129 130 132 134 134 135 137 138 140 141 142 143 145 145 147 148 149 150 152 153 153 154 155 156 157 158 159 160
]; 
Xw=[169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 169 170 169 171 172 173 175 176 176 178 179 180 181 183 184 185 185 187 188 188 189 191 191 192 193 194 195 196 196 197 198 198 199 200 201 201 201 202 203 203 203 204 205 205 205 206 206 206 206 207 207
]; 
Yw=[113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 113 112 112 112 112 112 112 112 112 112 112 112 112 112 112 112 112 113 113 114 114 114 114 114 114 115 115 115 115 115 115 115 115 115 115 115 115 115 115 116 116 116 116 116 116 116 117 117 117 117 117 117 117 117 117 118 118 118 118 118 118 118 118 118
];

%%Appelle des fonctions

Yr=480-Yr;
Yy=480-Yy;
Yw=480-Yw;

[Xr, Yr] = InterpolateNan(Xr,Yr);
[Xy, Yy] = InterpolateNan(Xy,Yy);
[Xw, Yw] = InterpolateNan(Xw,Yw);

[Xr, Yr] = RemoveOutlier(Xr,Yr);
[Xy, Yy] = RemoveOutlier(Xy,Yy);
[Xw, Yw] = RemoveOutlier(Xw,Yw);

[Xmin, Xmax, Ymin, Ymax] = GetFrame(Xr,Yr,Xy,Yy,Xw,Yw);

PathLength_r = GetBallPathLength(Xr,Yr);
PathLength_y = GetBallPathLength(Xy,Yy);
PathLength_w = GetBallPathLength(Xw,Yw);

BallBorderDist=9;

[IdxTouch_r]=GetTouchIdx(Xr,Yr,Xmin, Xmax, Ymin, Ymax, BallBorderDist);
[IdxTouch_y]=GetTouchIdx(Xy,Yy,Xmin, Xmax, Ymin, Ymax, BallBorderDist);
[IdxTouch_w]=GetTouchIdx(Xw,Yw,Xmin, Xmax, Ymin, Ymax, BallBorderDist);

MoveDistPx=9;

[FirstBall,SecondBall,LastBall, NbBallsMoved] = GetBallMoveOrder(Xr, Yr, Xy, Yy, Xw, Yw, MoveDistPx);

%%Divers

% Define the length and the width

length_rectangle = Xmax-Xmin;
width_rectangle = Ymax-Ymin;
now_time = datetime('now');
date = datestr(now_time);
sequence='T1';

%Condition de victoire

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


if length(band_touches)>=3 
    result = '---WIN---';
else
    result = '---LOOSE---';
end


%%Graph

Scores_sheet = rectangle('Position',[Xmin Ymin length_rectangle width_rectangle],'EdgeColor','b');

hold on %keep every next plot on the same plot

% Create 3 plots for the coordonates of r-y-w


plot(Xr,Yr,'r-*');
plot(Xy,Yy,'y-o');
plot(Xw,Yw,'b-+');

set(gca,'XColor', 'none','YColor','none');
axis([Xmin-20, Xmax+20, Ymin-130, Ymax+20]);%change white zone around the plot
title(['Scores sheet - ' sequence ' - ' date]);

text(128, 70, ['Sheet score for the ' FirstBall_color ' ball :'], 'HorizontalAlignment', 'left','FontSize',8);
text(128, 50, result, 'HorizontalAlignment', 'left','FontSize',8);
text(600, 70, [ num2str(NbBallsMoved) ' ball(s) moved'],'HorizontalAlignment', 'left','FontSize',8);
text(600, 50, [ num2str(length(IdxTouch_y)) ' band(s) touched'],'HorizontalAlignment', 'left','FontSize',8);

text(128, 20, [ 'Red ball distance : ' num2str(PathLength_r) ' px'],'HorizontalAlignment', 'left','FontSize',8);
text(128, 0, [ 'Yellow ball distance : ' num2str(PathLength_y) ' px'],'HorizontalAlignment', 'left','FontSize',8);
text(128, -20, [ 'White ball distance : ' num2str(PathLength_w) ' px'],'HorizontalAlignment', 'left','FontSize',8);

Fr = plot(Xr(1), Yr(1), "hexagram");
Fr.MarkerSize = 30;
Fy = plot(Xy(1), Yy(1), "hexagram");
Fy.MarkerSize = 30;
Fw = plot(Xw(1), Yw(1), "hexagram");
Fw.MarkerSize = 30;

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

hold off;


