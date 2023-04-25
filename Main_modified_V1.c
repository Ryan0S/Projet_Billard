#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>


int IsColor(int BallredRmin, int BallredRmax, int BallredGmin, int BallredGmax, int BallredBmin, int BallredBmax, int BallyellowRmin, int BallyellowRmax, int BallyellowGmin, int BallyellowGmax, int BallyellowBmin, int BallyellowBmax, int BallwhiteRmin, int BallwhiteRmax, int BallwhiteGmin, int BallwhiteGmax, int BallwhiteBmin, int BallwhiteBmax, int BallSize, int NumberOfPixels, int MyPM[]) {

	int RGBint, Blue, Green, Red;
	int Out = 1;

	for (int i = 1; i <= NumberOfPixels; i++) {
		RGBint = MyPM[i];
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

		if (Out == 1) {
			Out = 0;
		}

		MyPM[i] = Out;

	}
	return *MyPM;
}

void IsBall(int BallSize, int NumberOfPixels, int MyPM[], int Width, int Height, int* ScoreMaxR, int* ScoreMaxY, int* ScoreMaxW, int* Xr, int* Yr, int* Xw, int* Yw, int* Xy, int* Yy) {


	int count;

	int PotBall[NumberOfPixels], ScoreR[NumberOfPixels], ScoreY[NumberOfPixels], ScoreW[NumberOfPixels], MaxR[2], MaxY[2], MaxW[2];

	for (int i = 0; i <= NumberOfPixels; i++) {

		PotBall[i] = MyPM[i];
	}

	for (int i = 0; i <= NumberOfPixels; i++) {

		for (int t1 = 0; t1 <= BallSize; t1++) {
			for (int t2 = 0; t2 <= BallSize; t2++) {
				if (PotBall[i + t2 + t1 * Width] == 2) {
					ScoreR[i]++;
				}
				else if (PotBall[i + t2 + t1 * Width] == 6) {
					ScoreR[i]++;
					ScoreY[i]++;
				}
				else if (PotBall[i + t2 + t1 * Width] == 10) {
					ScoreR[i]++;
					ScoreW[i]++;
				}
				else if (PotBall[i + t2 + t1 * Width] == 3) {
					ScoreY[i]++;
				}
				else if (PotBall[i + t2 + t1 * Width] == 5) {
					ScoreW[i]++;
				}
				else if (PotBall[i + t2 + t1 * Width] == 15) {
					ScoreY[i]++;
					ScoreW[i]++;
				}
				else if (PotBall[i + t2 + t1 * Width] == 30) {
					ScoreY[i]++;
					ScoreW[i]++;
					ScoreR[i]++;
				}
				else if (PotBall[i + t2 + t1 * Width] == 0) {
					continue;
				}
				else {
					printf("Error assigning Score");
				}
			}
		}
		if (MaxR[1] < ScoreR[i]) {
			MaxR[0] = i;
			MaxR[1] = ScoreR[i];
		}

		else if (MaxW[1] < ScoreW[i]) {
			MaxW[0] = i;
			MaxW[1] = ScoreW[i];
		}

		else if (MaxY[1] < ScoreY[i]) {
			MaxY[0] = i;
			MaxY[1] = ScoreY[i];
		}

		else {
            continue;
		}
	}

	*Yr = MaxR[0] % Height;
	*Xr = 0;
	do {
		MaxR[0] = MaxR[0] - Width;
		*Xr = *Xr + 1;
	} while (MaxR[0] >= 0);

    *Xr = *Xr + BallSize/2;
    *Yr = *Yr + BallSize/2;

    *Yw = MaxW[0] % Height;
	*Xw = 0;
	do {
		MaxW[0] = MaxW[0] - Width;
		*Xw = *Xw + 1;
	} while (MaxW[0] >= 0);

    *Xw = *Xw + BallSize/2;
    *Yw = *Yw + BallSize/2;

    *Yy = MaxY[0] % Height;
	*Xy = 0;
	do {
		MaxY[0] = MaxY[0] - Width;
		*Xy = *Xy + 1;
	} while (MaxY[0] >= 0);

    *Xy = *Xy + BallSize/2;
    *Yy = *Yy + BallSize/2;

	*ScoreMaxR = MaxR[1];
	*ScoreMaxY = MaxY[1];
	*ScoreMaxW = MaxW[1];

}


int main(int argc, char *argv[]) {

	//const char* nom_fichier = argv[0];
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
	const unsigned int BallyellowRmax = atoi(argv[12]);
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
	const unsigned int BallSize = atoi(argv[29]);


    int ScoreMaxR, ScoreMaxY, ScoreMaxW;
	int Xr, Yr, Xw, Yw, Xy, Yy;

		FILE *file = fopen("/Users/ryan/Desktop/Tidy/EPFL/Mirror/EPFL/Prog/Pixmap217.bin", "rb"); // Open binary file for reading
	if (file == NULL) {
		perror("Error opening file");
		return 1;
	}

	// Determine the size of the file
	fseek(file, 0, SEEK_END);
	long int file_size = ftell(file);
	fseek(file, 0, SEEK_SET);

	// Allocate memory for the MyPM
	int *MyPM = malloc(file_size);
	if (MyPM == NULL) {
		perror("Error allocating memory");
		fclose(file);
		return 1;
	}

	// Read the contents of the file into the MyPM
	size_t bytes_read = fread(MyPM, 1, file_size, file);
	if (bytes_read != file_size) {
		if (ferror(file)) {
			perror("Error reading file");
		}
		else {
			printf("Unexpected end of file\n");
		}
		free(MyPM);
		fclose(file);
		return 1;
	}

	// Close the file
	if (fclose(file) != 0) {
		perror("Error closing file");
		free(MyPM);
		return 1;
	}


	//ERROR_TEST : Tester si le diamètre de la boule est dans la zone [5,20]
	if (BallSize < 5 || BallSize > 20)
	{
		printf("Le diamètre de la boule n'est pas dans la zone [5,20]");
		return -1 ;
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


	printf("Les boules ont un diamètre de %d pixels\n\n", BallSize);

    

	int Width = rectext2 - rectext1;
	int Height = rectext4 - rectext3;

	//ERROR_TEST: Check si la hauteur ou la largeur de la table est en dehors de la zone [100,1000]

	if (Width < 100 || Width >1000 || Height < 100 || Height>1000)
	{
		printf("Les dimensions de la table sont en dehors de la zone [100,1000]");
		return -1 ;
	}


	//ERROR_TEST : Check si le nombre de pixels correspond au nombre de valeurs de myPM

	size_t Numberofvalues = sizeof(*MyPM) / sizeof(MyPM[0]);
	int NumberOfPixels = Width * Height;

	printf("La hauteur de la table est de %d pixels", Width);
	printf("\n\nLa largeur de la table est de %d pixels", Height);

	if (Numberofvalues == NumberOfPixels)
		printf("\n\nil y a %d pixels !", NumberOfPixels);
	else
	{
        int diff = NumberOfPixels-Numberofvalues;
        printf("%d", Numberofvalues);
		printf("\n\nLe nombre de donnees ne correspond pas aux nombre de pixels !\n");
		printf("\nIl y a %d pixels manquants !\n", diff);
		return -1 ;
	}
    

	IsColor(BallredRmin, BallredRmax, BallredGmin, BallredGmax, BallredBmin, BallredBmax,
		BallyellowRmin, BallyellowRmax, BallyellowGmin, BallyellowGmax, BallyellowBmin, BallyellowBmax,
		BallwhiteRmin, BallwhiteRmax, BallwhiteGmin, BallwhiteGmax, BallwhiteBmin, BallwhiteBmax,
		BallSize, NumberOfPixels, MyPM);

	IsBall(BallSize, NumberOfPixels, MyPM, Width, Height, &ScoreMaxR, &ScoreMaxY, &ScoreMaxW, &Xr, &Yr, &Xw, &Yw, &Xy, &Yy);


	//Ecris le fichier Pos.txt

	FILE *f_out = NULL;

	f_out = fopen("Pos.txt", "w");

	//ERROR_TEST : Check s'il est possible de créer un fichier en sortie

	if(1 != 1)
	{
		return -1  ;
	}

	printf("Red: %d, %d, %d", Xr, Yr, ScoreMaxR);
	printf("\nYellow: %d, %d, %d", Xy, Yy, ScoreMaxY);
	printf("\nWhite: %d, %d, %d", Xw, Yw, ScoreMaxW);

	if(fclose(f_out))
	perror("Erreur fermeture fichier de sortie");


	// Free the memory allocated for the MyPM
	free(MyPM);

    return 0;
}