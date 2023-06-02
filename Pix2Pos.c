#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct BallInformation {
    unsigned int RedMin;
    unsigned int RedMax;
    unsigned int GreenMin;
    unsigned int GreenMax;
    unsigned int BlueMin;
    unsigned int BlueMax;
    int X_Coordinate;
    int Y_coordinate;
    int Score;
} RedBall, YellowBall, WhiteBall;

struct TableInformation {
    int RedMin;
    int RedMax;
    int GreenMin;
    int GreenMax;
    int BlueMin;
    int BlueMax;
    int FirstPixel;
    int LastPixel;
    int LeftBorder;
    int RightBorder;
    int TopBorder;
    int BottomBorder;
    int Width;
    int Height;
    int BallSize;
}Table;

struct ImageInformation{
    int Length;
    int Height;
    int NumberOfPixels;
}Image;

struct ErrorManagement {
	int DeBug;
    int RGBMin;
    int RGBMax;
    int NumberOfInputs;
    int BallSizeMin;
    int BallSizeMax;
    int PictureHeightMin;
    int PictureHeightMax;
    int PictureLengthMin;
    int PictureLengthMax;
    int TableHeightMin;
    int TableHeightMax;
    int TableLengthMin;
    int TableLengthMax;
    int LeftBorderMin;
    int LeftBorderMax;
    int RightBorderMin;
    int RightBorderMax;
    int TopBorderMin;
    int TopBorderMax;
    int BottomBorderMin;
    int BottomBorderMax;
    int BallMinScore;
}Error;

void IsColor(struct BallInformation RedBall, struct BallInformation YellowBall, struct BallInformation WhiteBall, struct TableInformation Table, unsigned int MyPM[]) {
	//INITIALISE LOCAL VARIABLES
	int RGBint, Blue, Green, Red, Out;

	//FOR LOOP TO CYCLE THROUGH ALL OF THE TABLE'S PIXELS 
	for (int i = Table.FirstPixel - 1; i < Table.LastPixel; i++) {
		//CONVERTING THE RGB VALUES FROM BINARY TO BASE 10
		RGBint = *(MyPM + i);
		Red = (RGBint & 0x00FF0000) >> 16;
		Green = (RGBint & 0x0000FF00) >> 8;
		Blue = (RGBint & 0x000000FF);
		//OUT IS THE NEW VALUE ASSIGNED TO THE ELEMENTS IN MyPM
		Out = 1;
		
		if (Red >= RedBall.RedMin && Red <= RedBall.RedMax && Green >= RedBall.GreenMin && Green <= RedBall.GreenMax && Blue >= RedBall.BlueMin && Blue <= RedBall.BlueMax) {
			Out = 2;
		}

		if (Red >= YellowBall.RedMin && Red <= YellowBall.RedMax && Green >= YellowBall.GreenMin && Green <= YellowBall.GreenMax && Blue >= YellowBall.BlueMin && Blue <= YellowBall.BlueMax) {
			Out = Out * 3;
		}

		if (Red >= WhiteBall.RedMin && Red <= WhiteBall.RedMax && Green >= WhiteBall.GreenMin && Green <= WhiteBall.GreenMax && Blue >= WhiteBall.BlueMin && Blue <= WhiteBall.BlueMax) {
			Out = Out * 5;
		}
		if (Red >= Table.RedMin && Red <= Table.RedMax && Green >= Table.GreenMin && Green <= Table.GreenMax && Blue >= Table.BlueMin && Blue <= Table.BlueMax) {
			Out = Out * 7;
		}
		if (Out == 1) {
			Out = 0;
		}
		MyPM[i] = Out;
	}
}

void IsBall(struct BallInformation *RedBall, struct BallInformation *YellowBall, struct BallInformation *WhiteBall, struct TableInformation Table, struct ImageInformation Image, unsigned int MyPM[]) {

	int ScoreR = 0, ScoreY = 0, ScoreW = 0, MaxR[2] = { 0,0 }, MaxY[2] = { 0,0 }, MaxW[2] = { 0,0 };
	int k = 1;

	for (int i = Table.FirstPixel - 1; i < Table.LastPixel; i++) {
		ScoreR = 0;
		ScoreW = 0;
		ScoreY = 0;
		
			if (k == Table.RightBorder - Table.LeftBorder - Table.BallSize + 1) {
				k = 1;
				i = i + Table.BallSize - 1 + Image.Length - Table.RightBorder + Table.LeftBorder;
			}
			else k++;

			if(MyPM[i + Table.BallSize/2 + Image.Length * Table.BallSize/2] == 7){
				continue;
			}

		for (int t1 = 0; t1 < Table.BallSize; t1++) {
			for (int t2 = 0; t2 < Table.BallSize; t2++) {
				if (MyPM[i + t2 + t1 * Image.Length] == 3) {
					ScoreY++;
				}
				else if (MyPM[i + t2 + t1 * Image.Length] == 6) {
					ScoreR++;
					ScoreY++;
				}
				else if (MyPM[i + t2 + t1 * Image.Length] == 10) {
					ScoreR++;
					ScoreW++;
				}
				else if (MyPM[i + t2 + t1 * Image.Length] == 2) {
					ScoreR++;
				}
				else if (MyPM[i + t2 + t1 * Image.Length] == 5) {
					ScoreW++;
				}
				else if (MyPM[i + t2 + t1 * Image.Length] == 15) {
					ScoreY++;
					ScoreW++;
				}
				else if (MyPM[i + t2 + t1 * Image.Length] == 30) {
					ScoreY++;
					ScoreW++;
					ScoreR++;
				}
				else if (MyPM[i + t2 + t1 * Image.Length] == 0) {
					continue;
				}
			}
		}
		if (MaxR[1] < ScoreR) {
			MaxR[0] = i;
			MaxR[1] = ScoreR;
		}
		if (MaxW[1] < ScoreW) {
			MaxW[0] = i;
			MaxW[1] = ScoreW;
		}
		if (MaxY[1] < ScoreY) {
			MaxY[0] = i;
			MaxY[1] = ScoreY;
		}
	}

	(*RedBall).Y_coordinate = MaxR[0] / Image.Length;
	(*RedBall).X_Coordinate = MaxR[0] % Image.Length - 2;
	(*WhiteBall).Y_coordinate = MaxW[0] / Image.Length;
	(*WhiteBall).X_Coordinate = MaxW[0] % Image.Length - 2;
	(*YellowBall).Y_coordinate = MaxY[0] / Image.Length;
	(*YellowBall).X_Coordinate = MaxY[0] % Image.Length - 2;

	(*RedBall).Score = MaxR[1];
	(*YellowBall).Score = MaxY[1];
	(*WhiteBall).Score = MaxW[1];
}

int main(int argc, char *argv[]) {
#pragma region //INITIALISATION OF ERROR VALUES
Error.BallSizeMin = 5;
Error.BallSizeMax = 20;
Error.BallMinScore = 15;
Error.NumberOfInputs = 29;
Error.TableHeightMax = 1000;
Error.TableHeightMin = 100;
Error.TableLengthMax = 1000;
Error.TableLengthMin = 100;
Error.DeBug = 0;
#pragma endregion

#pragma region //ASSIGNS COMMAND LINE INPUTS TO APPROPRIATE VARIABLES
//ERROR_TEST: CHECKS IF THE NUMBER OF ARGUMENTS RECEIVED IS EQUAL TO THE NUMBER OF ARGUMENTS EXPECTED
if(argc != Error.NumberOfInputs + 1){
    perror("Pas le bon nombre de paramètres dans la ligne de commande.");
    return 1;
}

//ASSIGNS COMMAND LINE INPUTS TO APPROPRIATE VARIABLES
//const char* nom_fichier = argv[0];
	Table.BottomBorder = atoi(argv[1]);
	Table.TopBorder = atoi(argv[2]);
	Table.LeftBorder = atoi(argv[3]);
	Table.RightBorder = atoi(argv[4]);
    RedBall.RedMin = atoi(argv[5]);
    RedBall.RedMax = atoi(argv[6]);
    RedBall.GreenMin = atoi(argv[7]);
    RedBall.GreenMax = atoi(argv[8]);
    RedBall.BlueMin = atoi(argv[9]);
    RedBall.BlueMax = atoi(argv[10]);
    YellowBall.RedMin = atoi(argv[11]);
    YellowBall.RedMax = atoi(argv[12]);
    YellowBall.GreenMin = atoi(argv[13]);
    YellowBall.GreenMax = atoi(argv[14]);
    YellowBall.BlueMin = atoi(argv[15]);
    YellowBall.BlueMax = atoi(argv[16]);
    WhiteBall.RedMin = atoi(argv[17]);
    WhiteBall.RedMax = atoi(argv[18]);
	WhiteBall.RedMin = atoi(argv[19]);
	WhiteBall.GreenMax = atoi(argv[20]);
	WhiteBall.BlueMin = atoi(argv[21]);
	WhiteBall.BlueMax = atoi(argv[22]);
    Table.RedMin = atoi(argv[23]);
    Table.RedMax = atoi(argv[24]);
    Table.GreenMin = atoi(argv[25]);
    Table.GreenMax = atoi(argv[26]);
    Table.BlueMin = atoi(argv[27]);
    Table.BlueMax = atoi(argv[28]);
    Table.BallSize = atoi(argv[29]);
	#pragma endregion

#pragma region //CHECKING ERRORS RELATED TO VARIABLES INPUT
	//ERROR_TEST : CHECKS THAT THE BALL SIZE IS IN THE APPROPRIATE RANGE
	if (Table.BallSize < Error.BallSizeMin || Table.BallSize > Error.BallSizeMax){
		perror("Le diamètre de la boule est en dehors des valeurs acceptable");
		return 1;
	}

    //COMPUTE TABLE HEIGHT AND WIDTH
    Table.Width = Table.RightBorder - Table.LeftBorder;
    Table.Height = Table.TopBorder - Table.BottomBorder;

	//ERROR_TEST:CHECKS THAT THE TABLE LENGTH AND HEIGHT IS IN THE APPROPRIATE RANGE
	if (Table.Width < Error.TableLengthMin || Table.Width >Error.TableLengthMax || Table.Height < Error.TableHeightMin || Table.Height > Error.TableHeightMax){
		perror("La longueur et/ou la hauteur de la table est en dehors de la zone acceptable");
		return 1;
    }
	#pragma endregion

#pragma region //OPEN Pixmap.bin AND STORES IT IN MyPM
    //OPEN Pixmap.bin FOR READING
	FILE *file = fopen("Pixmap217.bin", "rb");

    //ERROR_TEST: CHECK IF FILE WAS OPENED
	if (file == NULL) {
		perror("Error opening file");
		return 1;
	}

	//FIND THE SIZE OF THE FILE
	fseek(file, 0L, SEEK_END);
	long int file_size = ftell(file);
	fseek(file, 0L, SEEK_SET);

    //COMPUTE THE NUMBER OF INTEGERS IN Pixmap.bin
    size_t num_integers = file_size / sizeof(unsigned int);

	//ALLOCATE MEMORY FOR MyPM
	unsigned int* MyPM = (unsigned int*)malloc(file_size);

    //ERROR_TEST: CHECK IF MEMORY WAS ALLOCATED FOR MyPM
	if (MyPM == NULL) {
		perror("Error allocating memory");
		fclose(file);
		return 1;
	}

    //READ THE CONTENTS OF Pixmap.bin INTO MyPM
	size_t elements_read = fread(MyPM, sizeof(unsigned int), num_integers , file);

    //ERROR_TEST: MAKES SURE THAT THE NUMBER OF ELEMENTS READ IS EQUAL TO THE NUMBER OF ELEMENTS COMPUTED
	if (elements_read != num_integers) {
		if (ferror(file)) {
			perror("Error reading file");
		}
		else {
			perror("Unexpected end of file\n");
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
    
#pragma endregion

#pragma region //INITIALISATION OF VALUES

    //EXTRACT LENGTH AND HEIGHT FROM MyPM
	Image.Length = MyPM[0];
	Image.Height = MyPM[1];

    //ERROR_TEST: CHECKS IF NUMBER OF PIXELS IN Pixmap.bin IS EQUAL TO THE LENGTH TIMES THE HEIGHT GIVEN IN Pixmap.bin
    if(Image.Length * Image.Height > num_integers - 2){
        perror("Pas assez de pixels");
        return 1;
    }
    if(Image.Length * Image.Height < num_integers - 2){
        perror("Trop de pixels\n");
    }

    //COMPUTE FIRST AND LAST PIXEL OF TABLE
    Table.FirstPixel = Table.BottomBorder * Image.Length + Table.LeftBorder;
    Table.LastPixel = (Table.TopBorder - Table.BallSize)*Image.Length + Table.RightBorder - Table.BallSize;

    //INITIALISE DEFAULT VALUES FOR THE BALLS' SCORE AND COORDINATES
    RedBall.Score = 0;
    RedBall.X_Coordinate = 0;
    RedBall.Y_coordinate = 0;
    YellowBall.Score = 0;
    YellowBall.X_Coordinate = 0;
    YellowBall.Y_coordinate = 0;
    WhiteBall.Score = 0;
    WhiteBall.X_Coordinate = 0;
    WhiteBall.Y_coordinate = 0;
#pragma endregion

#pragma region //FUNCTION CALLING
    clock_t t;
    t = clock();
	IsColor(RedBall, YellowBall, WhiteBall, Table, MyPM);
    IsBall(&RedBall, &YellowBall, &WhiteBall, Table, Image, MyPM);
    t = clock() - t;
    double time_taken; 
	time_taken = ((double)t)/CLOCKS_PER_SEC;// in seconds
#pragma endregion

#pragma region //CREATE POX.TXT FILE
    //OPENS Pos.txt IN WRITE MODE
	FILE *f_out = fopen("Pos.txt", "w");

	//ERROR_TEST: CHECKS IF Pos.txt WAS OPENED
	if (f_out == NULL)
	{
        perror("Error Opening Pos.txt");
		return 1;
	}

    //CHECKS IF ALL BALLS WERE FOUND
    if(RedBall.Score < Error.BallMinScore){
        RedBall.Score = 0;
        RedBall.X_Coordinate = -1;
        RedBall.Y_coordinate = -1;
        perror("La boule rouge n'a pas était trouvée");
    };
    if(YellowBall.Score < Error.BallMinScore){
        YellowBall.Score = 0;
        YellowBall.X_Coordinate = -1;
        YellowBall.Y_coordinate = -1;
        perror("La boule jaune n'a pas était trouvée");
    };
    if(WhiteBall.Score < Error.BallMinScore){
        WhiteBall.Score = 0;
        WhiteBall.X_Coordinate = -1;
        WhiteBall.Y_coordinate = -1;
        perror("La boule blanche n'a pas était trouvée");
    };
	

    //WRITES COORDINATES AND SCORE TO pos.txt
    fprintf(f_out, "Red: %d, %d, %d\n", RedBall.X_Coordinate, RedBall.Y_coordinate, RedBall.Score);
	fprintf(f_out,"Yellow: %d, %d, %d\n", YellowBall.X_Coordinate, YellowBall.Y_coordinate, YellowBall.Score);
	fprintf(f_out,"White: %d, %d, %d", WhiteBall.X_Coordinate, WhiteBall.Y_coordinate, WhiteBall.Score);
#pragma endregion

#pragma region //DEBUG
	if(Error.DeBug == 1){
		//OPENS Pos.txt IN WRITE MODE
		FILE *DebugFile = fopen("Debug.txt", "w");

		//ERROR_TEST: CHECKS IF Pos.txt WAS OPENED
		if (DebugFile == NULL)
		{
			perror("Error Opening Pos.txt");
			return 1;
		}
		fprintf(DebugFile,"\n\nIsBall took %lf seconds to execute \n", time_taken);
	}
#pragma endregion

#pragma region //FREE THE MEMORY ALLOCATED TO MyPM
	free(MyPM);
	return 0;
#pragma endregion
}
