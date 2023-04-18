#include <stdio.h>
#include <string.h>


int IsColor(int BallredRmin, int BallredRmax, int BallredGmin, int BallredGmax, int BallredBmin, int BallredBmax, int BallyellowRmin, int BallyellowRmax, int BallyellowGmin, int BallyellowGmax, int BallyellowBmin, int BallyellowBmax, int BallwhiteRmin, int BallwhiteRmax, int BallwhiteGmin, int BallwhiteGmax, int BallwhiteBmin, int BallwhiteBmax, int BallSize, int NumberOfPixels, int myPM[]) {

	int RGBint, Blue, Green, Red;
	int Out = 1;

	for (int i = 1; i <= NumberOfPixels; i++) {
		RGBint = myPM[i];
		Blue = RGBint & 255;
		Green = (RGBint >> 8) & 255;
		Red = (RGBint >> 16) & 255;


		if (Red >= BallredRmin && Red <= BallredRmax && Green >= BallredGmin && Green <= BallredGmax && Blue >= BallredBmin && Blue <= BallredBmax) {
			Out = 2;
		}

		if (Red >= BallyellowRmin && Red <= BallyellowRmax && Green >= BallyellowGmin && Green <= BallyellowGmax && Blue >= BallyellowBmin && Blue <= BallyellowBmax) {
			Out = Out * 3;
		}

		if (Red >= BallwhiteRmin && Red <= BallwhiteRmax && Green >= BallwhiteGmin && Green <= BallwhiteGmax && Blue >= BallwhiteBmin && Blue <= BallwhiteBmax) {
			Out = Out * 5;
		}

		if (Out = 1) {
			Out = 0;
		}

		myPM[i] = Out;

	}
	return myPM;
}

int IsBall(int BallSize, int NumberOfPixels, int myPM[], int myW, int myH) {

	int ScoreMaxR, ScoreMaxY, ScoreMaxW;
	int Xr, Yr, Xw, Yw, Xy, Yy;
	int cbt;
	int count;

	int PotBall[NumberOfPixels], ScoreR[NumberOfPixels], ScoreY[NumberOfPixels], ScoreW[NumberOfPixels], MaxR[2], MaxY[2], MaxW[2];

	for (int i = 0; i <= NumberOfPixels; i++) {

		PotBall[i] = myPM[i];
	}

	for (int i = 0; i <= NumberOfPixels; i++) {

		for (int t1 = 0; t1 <= BallSize; t1++) {
			for (int t2 = 0; t2 <= BallSize; t2++) {
				if (PotBall[i + t2 + t1 * myW] == 2) {
					ScoreR[i]++;
				}
				else if (PotBall[i + t2 + t1 * myW] == 6) {
					ScoreR[i]++;
					ScoreY[i]++;
				}
				else if (PotBall[i + t2 + t1 * myW] == 10) {
					ScoreR[i]++;
					ScoreW[i]++;
				}
				else if (PotBall[i + t2 + t1 * myW] == 3) {
					ScoreY[i]++;
				}
				else if (PotBall[i + t2 + t1 * myW] == 5) {
					ScoreW[i]++;
				}
				else if (PotBall[i + t2 + t1 * myW] == 15) {
					ScoreY[i]++;
					ScoreW[i]++;
				}
				else if (PotBall[i + t2 + t1 * myW] == 30) {
					ScoreY[i]++;
					ScoreW[i]++;
					ScoreR[i]++;
				}
				else if (PotBall[i + t2 + t1 * myW] == 0) {
					return;
				}
				else {
					printf("Error assigning Score");
				}
			}
		}
		if (MaxR[2] < ScoreR) {
			MaxR[1] = i;
			MaxR[2] = ScoreR;
		}

		else if (MaxW[2] < ScoreW) {
			MaxW[1] = i;
			MaxW[2] = ScoreW;
		}

		else if (MaxY[2] < ScoreY) {
			MaxY[1] = i;
			MaxY[2] = ScoreY;
		}

		else {
			return;
		}
	}

	cbt = BallSize / 2;

	Yr = MaxR[1] % myH;
	Xr = 0;
	do {
		MaxR[1] = MaxR[1] - myW;
		Xr = Xr + 1;
	} while (MaxR[1] >= 0);


	ScoreMaxR = MaxR[2];
	ScoreMaxY = MaxY[2];
	ScoreMaxW = MaxW[2];

	return MaxR, MaxY, MaxW;
}


int main() {

	const char* nom_fichier = argv[0];
	const unsigned int rectint1 = atoi(argv[1]);
	const unsigned int rectint2 = atoi(argv[2]);
	const unsigned int rectint3 = atoi(argv[3]);
	const unsigned int rectint4 = atoi(argv[4]);
	const unsigned int BallredRmin = atoi(argv[5]);
	const unsigned int BallredRmax = atoi(argv[6]);
	const unsigned int BallredGmin = atoi(argv[7]);
	const unsigned int BallredGmax = atoi(argv[8]);
	const unsigned int BallredBmin = atoi(argv[9]);
	const unsigned int BallredBmax = atoi(argv[10]);
	const unsigned int BallyellowRmin = atoi(argv[11]);
	const unsigned int  BallyellowRmax = atoi(argv[12]);
	const unsigned int BallyellowGmin = atoi(argv[13]);
	const unsigned int BallyellowGmax = atoi(argv[14]);
	const unsigned int BallyellowBmin = atoi(argv[15]);
	const unsigned int BallyellowBmax = atoi(argv[16]);
	const unsigned int BallwhiteRmin = atoi(argv[17]);
	const unsigned int BallwhiteRmax = atoi(argv[18]);
	const unsigned int BallwhiteGmin = atoi(argv[19]);
	const unsigned int BallwhiteGmax = atoi(argv[20]);
	const unsigned int BallwhiteBmin = atoi(argv[21]);
	const unsigned int BallwhiteBmax = atoi(argv[22]);
	const unsigned int BGBlueRmin = atoi(argv[23]);
	const unsigned int BGBlueRmax = atoi(argv[24]);
	const unsigned int BGBlueGmin = atoi(argv[25]);
	const unsigned int BGBlueGmax = atoi(argv[26]);
	const unsigned int BGBlueBmin = atoi(argv[27]);
	const unsigned int BGBlueBmax = atoi(argv[28]);
	const unsigned int DiamBoule = atoi(argv[29]);

	FILE *f_in = fopen("Pixmap(218).bin", "rb");
	if (f_in == NULL) {
		perror("Erreur ouverture du fichier, will exit");
		exit(EXIT_FAILURE);
	}

	//ERROR_TEST : Tester si le diamètre de la boule est dans la zone [5,20]
	if (Diamboule < 5 || Diamboule > 20)
	{
		printf("Le diamètre de la boule n'est pas dans la zone [5,20]");
		exit(EXIT_FAILURE);
	}


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


	int Width = rectext1 + rectext3;
	int Height = rectext2 + rectext4;

	//ERROR_TEST: Check si la hauteur ou la largeur de la table est en dehors de la zone [100,1000]

	if (Width < 100 || Width >1000 || Height < 100 || Height>1000)
	{
		printf("Les dimensions de la table sont en dehors de la zone [100,1000]");
		exit(EXIT_FAILURE);
	}

	//ERROR_TEST : Check si les valeurs entrées correspondent aux valeurs données pour la taille de la table de billard

	if (myW != Width || myH != Height)
	{
		printf("Les contours entres ne correspondent pas aux contours attendus! Relancer!\n\n");
		exit(0);
	}

	else
		printf("\nLes contours entres correspondent aux contours attendus !\n\n");

	//ERROR_TEST : Check si le nombre de pixels correspond au nombre de valeurs de myPM

	size_t Numberofvalues = sizeof(myPM) / sizeof(myPM[0]);
	int NumberOfPixels = myW * myH;

	printf("La hauteur de la table est de %d pixels", myW);
	printf("\n\nLa largeur de la table est de %d pixels", myH);

	if (Numberofvalues == NumberOfPixels)
		printf("\n\nil y a %d pixels !", NumberOfPixels);
	else
	{
		printf("\n\nLe nombre de donnees ne correspond pas aux nombre de pixels !\n");
		printf("\nIl y a %d pixels manquants !\n", NumberOfpixels-Numberofvalues);
		exit(EXIT_FAILURE);
	}

	IsColor(BallredRmin, BallredRmax, BallredGmin, BallredGmax, BallredBmin, BallredBmax,
		BallyellowRmin, BallyellowRmax, BallyellowGmin, BallyellowGmax, BallyellowBmin, BallyellowBmax
		BallwhiteRmin, BallwhiteRmax, BallwhiteGmin, BallwhiteGmax, BallwhiteBmin, BallwhiteBmax,
		BallSize, NumberOfPixels, myPM[]);

	IsBall(BallSize, NumberOfPixels, myPM[])


	//Ecris le fichier Pos.txt

	FILE *f_out = NULL;

	f_out = fopen("Pos.txt", "w");

	//ERROR_TEST : Check s'il est possible de créer un fichier en sortie

	if()
	{
		exit(EXIT_FAILURE);
	}

	fprintf(f_out, "Red: %d, %d, %d", Xr, Yr, ScoremaxR);
	fprintf(f_out, "\nYellow: %d, %d, %d", Xy, Yy, ScoremaxY);
	fprintf(f_out, "\nWhite: %d, %d, %d", Xw, Yw, ScoremaxW);

	if(fclose(f_out));
	perror("Erreur fermeture fichier de sortie");
	if(fclose(f_in))
	perror("Erreur fermeture fichier d'entree");


}
