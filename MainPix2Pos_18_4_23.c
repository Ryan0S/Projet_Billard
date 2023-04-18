#include <stdio.h>
#include <string.h>
#include </Users/ryan/Desktop/Tidy/EPFL/Mirror/EPFL/Prog/PM_2023.h>

int Commande(){

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

    return rectint1, rectint2, rectint3, rectint4, BallredRmin, BallredRmax, BallredGmin, BallredGmax, BallredBmin, BallredBmax, BallyellowRmin, BallyellowRmax, BallyellowGmin, BallyellowGmax, BallyellowBmin, BallyellowBmax, BallwhiteRmin, BallwhiteRmax, BallwhiteGmin, BallwhiteGmax, BallwhiteBmin, BallwhiteBmax, BGBlueRmin, BGBlueRmax, BGBlueGmin, BGBlueGmax, BGBlueBmin, BGBlueBmax, DiamBoule;

}

int IsColor(int BallredRmin,int BallredRmax, int BallredGmin, int BallredGmax, int BallredBmin, int BallredBmax,
    int BallyellowRmin, int BallyellowRmax, int BallyellowGmin, int BallyellowGmax, int BallyellowBmin, int BallyellowBmax
    int BallwhiteRmin, int BallwhiteRmax, int BallwhiteGmin, int BallwhiteGmax, int BallwhiteBmin, int BallwhiteBmax,
    int BallSize, int NumberOfPixels, int myPM[]){
    
    int RGBint, Blue, Green, Red;
    int Out = 1;

    for(int i = 1; i <= NumberOfPixels; i++){
        RGBint = myPM[i];
        Blue = RGBint & 255;
        Green = (RGBint >> 8) & 255;
        Red = (RGBint >> 16) & 255;


        if (Red >= BallredRmin && Red <= BallredRmax && Green >= BallredGmin && Green <= BallredGmax && Blue >= BallredBmin && Blue <= BallredBmax){
            Out = 2;
        }

        if (Red >= BallyellowRmin && Red <= BallyellowRmax && Green >= BallyellowGmin && Green <= BallyellowGmax && Blue >= BallyellowBmin && Blue <= BallyellowBmax){
            Out = Out * 3;
        }

        if (Red >= BallwhiteRmin && Red <= BallwhiteRmax && Green >= BallwhiteGmin && Green <= BallwhiteGmax && Blue >= BallwhiteBmin && Blue <= BallwhiteBmax){
            Out = Out * 5;
        }

        if (Out = 1) {
            Out = 0;
        }

        myPM[i] = Out;

    }
    return myPM[];    
}

int IsBall(int BallSize, int NumberOfPixels, int myPM[]){

    int ScoreMaxR, ScoreMaxY, ScoreMaxW;
    int Xr,Yr,Xw,Yw,Xy,Yy;
    int cbt;
    int count;

    int PotBall[NumberOfPixels], ScoreR[NumberOfPixels], ScoreY[NumberOfPixels], ScoreW[NumberOfPixels], MaxR[2] ,MaxY[2], MaxW[2];

    for (int i = 0; i <= NumberOfPixels; i++){

        PotBall[i] = myPM[i];
    }

    for (int j = 0; j <= NumberOfPixels; j++){

        for(int t1 = 0; t1 <= BallSize; t1++){
            for(int t2 = 0; t2 <= BallSize; t2++){
                if(PotBall[i + t2 + t1 * myW] == 2){
                    ScoreR[i]++; 
                }
                else if(PotBall[i + t2 + t1 * myW] == 6){
                    ScoreR[i]++;
                    ScoreY[i]++;
                }
                else if(PotBall[i + t2 + t1 * myW] == 10){
                    ScoreR[i]++; 
                    ScoreW[i]++;
                }
                else if(PotBall[i + t2 + t1 * myW] == 3){
                    ScoreY[i]++; 
                }
                else if(PotBall[i + t2 + t1 * myW] == 5){
                    ScoreW[i]++;
                }
                else if(PotBall[i + t2 + t1 * myW] == 15){
                    ScoreY[i]++;
                    ScoreW[i]++;
                }
                else if(PotBall[i + t2 + t1 * myW] == 30){
                    ScoreY[i]++;
                    ScoreW[i]++;
                    ScoreR[i]++;
                }
                else if(PotBall[i + t2 + t1 * myW] == 0){
                    return;
                }
                else{
                    printf("Error assigning Score");
                }
            }
        }
        if(MaxR[2]< ScoreR){
            MaxR[1] = j;
            MaxR[2] = ScoreR;
        }

        else if(MaxW[2]< ScoreW){
            MaxW[1] = j;
            MaxW[2] = ScoreW;
        }

        else if(MaxY[2]< ScoreY){
            MaxY[1] = j;
            MaxY[2] = ScoreY;
        }

        else{
            return;
        }
    }

    cbt = BallSize/2;

    Yr = MaxR[1] % myH;
    Xr = 0;
    do{
        MaxR[1] = MaxR[1] - myW;
        Xr = Xr + 1;
    }
    while (MaxR[1] >= 0);


    ScoreMaxR = MaxR[2];
    ScoreMaxY = MaxY[2];
    ScoreMaxW = MaxW[2];

    return MaxR,MaxY,MaxW;
}


int main(){

    Commnande();


	int Width = rectext1 + rectext3;
	int Height = rectext2 + rectext4;

	//check si les valeurs entrées correspondent aux valeurs données pour la taille de la table de billard

	if (myW != Width || myH != Height)
		printf("Les contours entres ne correspondent pas aux contours attendus! Relancer!\n\n");

	else
		printf("\nLes contours entres correspondent aux contours attendus !\n\n");

	//Check si le nombre de pixels correspond au nombre de valeurs de myPM
	
	size_t numberofvalues = sizeof(myPM) / sizeof(myPM[0]);
	int NumberOfPixels = myW*myH;

	printf("La hauteur de la table est de %d pixels", myW);
	printf("\n\nLa largeur de la table est de %d pixels", myH);

	if (numberofvalues == NumberOfPixels)
		printf("\n\nil y a %d pixels !", NumberOfPixels);
	else
		printf("\n\nLe nombre de donnees ne correspond pas aux nombre de pixels !\n");


    IsColor(BallredRmin, BallredRmax,  BallredGmin,  BallredGmax,  BallredBmin,  BallredBmax,
        BallyellowRmin,  BallyellowRmax,  BallyellowGmin,  BallyellowGmax,  BallyellowBmin,  BallyellowBmax
        BallwhiteRmin,  BallwhiteRmax,  BallwhiteGmin,  BallwhiteGmax,  BallwhiteBmin,  BallwhiteBmax,
        BallSize,  NumberOfPixels,  myPM[]);

    IsBall( BallSize,  NumberOfPixels,  myPM[])


	//Ecris le fichier Pos.txt

	FILE *fp = NULL;

	fp = fopen("Pos.txt", "w");
	
	fprintf(fp, "Red: %d, %d, %d", Xr, Yr, ScoremaxR);
	fprintf(fp, "\nYellow: %d, %d, %d", Xy, Yy, ScoremaxY);
	fprintf(fp, "\nWhite: %d, %d, %d", Xw, Yw, ScoremaxW);

	fclose(fp);
	

}
