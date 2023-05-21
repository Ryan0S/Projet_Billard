#include <stdio.h>
int main(){

int rectint1, rectint2, rectint3, rectint4;
int BallredRmin, BallredRmax, BallredGmin, BallredGmax, BallredBmin, BallredBmax;
int BallyellowRmin, BallyellowRmax, BallyellowGmin, BallyellowGmax, BallyellowBmin, BallyellowBmax;
int BallwhiteRmin, BallwhiteRmax, BallwhiteGmin, BallwhiteGmax, BallwhiteBmin, BallwhiteBmax;
int BGBlueRmin, BGBlueRmax, BGBlueGmin, BGBlueGmax, BGBlueBmin, BGBlueBmax;
int DiamBoule;


scanf("%d %d %d %d", &rectint1, &rectint2, &rectint3, &rectint4);
scanf("%d %d %d %d %d %d", &BallredRmin, &BallredRmax, &BallredGmin, &BallredGmax, &BallredBmin, &BallredBmax);
scanf("%d %d %d %d %d %d", &BallyellowRmin, &BallyellowRmax, &BallyellowGmin, &BallyellowGmax, &BallyellowBmin, &BallyellowBmax);
scanf("%d %d %d %d %d %d", &BallwhiteRmin, &BallwhiteRmax, &BallwhiteGmin, &BallwhiteGmax, &BallwhiteBmin, &BallwhiteBmax);
scanf("%d %d %d %d %d %d", &BGBlueRmin, &BGBlueRmax, &BGBlueGmin, &BGBlueGmax, &BGBlueBmin, &BGBlueBmax);
scanf("%d", &DiamBoule);

int rectext1 = rectint1 - 5;
int rectext2 = rectint2 - 5;
int rectext3 = rectint3 + 5;
int rectext4 = rectint4 + 5;

printf("Les ranges de couleurs sont\n");
printf("             Rmin.. max     Gmin.. max     Bmin.. max\n");
printf("Ballred      %d..%d          %d..%d         %d..%d\n", BallredRmin, BallredRmax, BallredGmin, BallredGmax, BallredBmin, BallredBmax);
printf("Ballyellow   %d..%d          %d..%d         %d..%d\n", BallyellowRmin, BallyellowRmax, BallyellowGmin, BallyellowGmax, BallyellowBmin, BallyellowBmax);
printf("Ballwhite    %d..%d          %d..%d         %d..%d\n", BallwhiteRmin, BallwhiteRmax, BallwhiteGmin, BallwhiteGmax, BallwhiteBmin, BallwhiteBmax);
printf("BG Blue      %d..%d          %d..%d         %d..%d\n\n\n\n\n", BGBlueRmin, BGBlueRmax, BGBlueGmin, BGBlueGmax, BGBlueBmin, BGBlueBmax);


printf("Rect Extérieur du billard est {%d,%d, %d, %d} \n", rectext1, rectext2, rectext3, rectext4);
printf("Rect Intérieur du billard est {%d,%d, %d, %d} \n\n\n", rectint1, rectint2, rectint3, rectint4);


printf("Les boules ont un diamètre de %d pixels", DiamBoule);



};




//  Les boules ont un diamètre de 11 pixels
//  Les coordonnées (top, left, score) des boules sont
//
//      Red: 40,50,101;  Yellow: 60,40,121;  White: 20,30,101
//
//  Les ranges de couleurs sont
//               Rmin.. max     Gmin.. max     Bmin.. max
//  Ballred      160..255          0..160         0..160
//  Ballyellow   140..255        140..255         0..175
//  Ballwhite    100..255        100..255       100..255
//  BG Blue       39.. 62         91..116       202..255
//
//  La ligne de commande devrait être
//       15 15 85 65    160 255 0 160 0 160 140 255 140 255 0 175 100 255 100 255 100 255    39 62 91 116 202 255    11
//
//  Le pixmap a une taille de (100x80) unsigned int
//  Rect extérieur du billard est {10,10, 90, 70}
//  Rect Intérieur du billard est {15,15, 85, 65}
