#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

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
    int LightBlueRedMin;
    int LightBlueRedMax;
    int LightBlueGreenMin;
    int LightBlueGreenMax;
    int LightBlueBlueMin;
    int LightBlueBlueMax;
	int DarkBlueRedMin;
    int DarkBlueRedMax;
    int DarkBlueGreenMin;
    int DarkBlueGreenMax;
    int DarkBlueBlueMin;
    int DarkBlueBlueMax;
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

struct DebugManagement{
	int Status;
	int LightBlueCount;
	int DarkBlueCount;
	int RedCount;
	int YellowCount;
	int WhiteCount;
	int NeitherCount;
	int ScanCount;
	int SkipCountType1;
	int SkipCountType2;
} Debug = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int isNumber(char number[])
{
    int i = 0;
    //checking for negative numbers
    if (number[0] == '-')
        i = 1;
    for (; number[i] != 0; i++)
    {
        //if (number[i] > '9' || number[i] < '0')
        if (isdigit(number[i]) != 1)
            return 0;
    }
    return 1;
}

void IsColor(struct BallInformation RedBall, struct BallInformation YellowBall, struct BallInformation WhiteBall, struct TableInformation Table, unsigned int MyPM[], struct DebugManagement *Debug) {
	//INITIALISE LOCAL VARIABLES
	int RGBint, Blue, Green, Red, Out;
	int k = 1;


	//FOR LOOP TO CYCLE THROUGH ALL OF THE TABLE'S PIXELS 
	for (int i = Table.FirstPixel - 1; i < Table.LastPixel + (Image.Length * Table.BallSize); i++) {

		if (k == Table.RightBorder - Table.LeftBorder + 1) {
				k = 1;
				i = i - 1 + Image.Length - Table.RightBorder + Table.LeftBorder;
			}
			else k++;

		//CONVERTING THE RGB VALUES FROM BINARY TO BASE 10
		RGBint = *(MyPM + i);
		Blue = RGBint & 255;
		Green = (RGBint >> 8) & 255;
		Red = (RGBint >> 16) & 255;

		//OUT IS THE NEW VALUE ASSIGNED TO THE ELEMENTS IN MyPM
		Out = 1;
		if (Red >= RedBall.RedMin && Red <= RedBall.RedMax && Green >= RedBall.GreenMin && Green <= RedBall.GreenMax && Blue >= RedBall.BlueMin && Blue <= RedBall.BlueMax) {
			Out = Out * 2;
			(*Debug).RedCount++;
		}
		if (Red >= YellowBall.RedMin && Red <= YellowBall.RedMax && Green >= YellowBall.GreenMin && Green <= YellowBall.GreenMax && Blue >= YellowBall.BlueMin && Blue <= YellowBall.BlueMax) {
			Out = Out * 3;
			(*Debug).YellowCount++;
		}
		if (Red >= WhiteBall.RedMin && Red <= WhiteBall.RedMax && Green >= WhiteBall.GreenMin && Green <= WhiteBall.GreenMax && Blue >= WhiteBall.BlueMin && Blue <= WhiteBall.BlueMax) {
			Out = Out * 5;
			(*Debug).WhiteCount++;
		}
		if (Red >= Table.LightBlueRedMin && Red <= Table.LightBlueRedMax && Green >= Table.LightBlueGreenMin && Green <= Table.LightBlueGreenMax && Blue >= Table.LightBlueBlueMin && Blue <= Table.LightBlueBlueMax) {
			(*Debug).LightBlueCount++;
		}
		if (Red >= Table.DarkBlueRedMin && Red <= Table.DarkBlueRedMax && Green >= Table.DarkBlueGreenMin && Green <= Table.DarkBlueGreenMax && Blue >= Table.DarkBlueBlueMin && Blue <= Table.DarkBlueBlueMax) {
			Out = Out * 7;
			(*Debug).DarkBlueCount++;
		}
		if (Out == 1) {
			Out = 0;
			(*Debug).NeitherCount++;
		}
		MyPM[i] = Out;
	}
}

void IsBall(struct BallInformation *RedBall, struct BallInformation *YellowBall, struct BallInformation *WhiteBall, struct TableInformation Table, struct ImageInformation Image, unsigned int MyPM[], struct DebugManagement *Debug) {

	int ScoreR = 0, ScoreY = 0, ScoreW = 0, MaxR[2] = { 0,0 }, MaxY[2] = { 0,0 }, MaxW[2] = { 0,0 }, k = 1;;

	for (int i = Table.FirstPixel - 1; i < Table.LastPixel - (Table.BallSize * Image.Length); i++) {
		ScoreR = 0;
		ScoreW = 0;
		ScoreY = 0;
		int State = 12;
		
			if (k == Table.RightBorder - Table.LeftBorder - Table.BallSize + 1) {
				k = 1;
				i = i + Table.BallSize - 1 + Image.Length - Table.RightBorder + Table.LeftBorder;
			}
			else k++;

			if(MyPM[i + (Table.BallSize/2) + Image.Length * (Table.BallSize/2)] == 7 ||MyPM[i + (Table.BallSize/2) + Image.Length * (Table.BallSize/2 )+1] == 7 ||MyPM[i + (Table.BallSize/2) + Image.Length * (Table.BallSize/2)-1] == 7 ||MyPM[i + (Table.BallSize/2) + Image.Length * (Table.BallSize/2)+Image.Length] == 7){
				(*Debug).SkipCountType1++;
				continue;
			}

		for (int t1 = 0; t1 < Table.BallSize; t1++) {
			if(State != 3 && State != 7 && State != 10 && State != 0 && (Table.BallSize * Table.BallSize) - (t1 * Table.BallSize) < MaxR[1]-ScoreR){
				(*Debug).SkipCountType2++;
				State = State - 2;
			}

			//if(State != 3 && State != 2 && State != 5 && State != 0 && (Table.BallSize * Table.BallSize) - (t1 * Table.BallSize) < MaxW[1]-ScoreW){
			//	(*Debug).SkipCountType2++;
			//	State = State - 7;
			//}

			if(State != 2 && State != 7 && State != 9 && State != 0 && (Table.BallSize * Table.BallSize) - (t1 * Table.BallSize) < MaxY[1]-ScoreY){
				(*Debug).SkipCountType2++;
				State = State - 3;
			}

			for (int t2 = 0; t2 < Table.BallSize; t2++) {
				(*Debug).ScanCount++;
				switch(State){
					case 2:
						if (MyPM[i + t2 + t1 * Image.Length] == 2 || MyPM[i + t2 + t1 * Image.Length] == 14){
							ScoreR++;
						}
						break;
					case 3:
						if (MyPM[i + t2 + t1 * Image.Length] == 3|| MyPM[i + t2 + t1 * Image.Length] == 21) {
							ScoreY++;
						}
						break;
					case 7:
						if (MyPM[i + t2 + t1 * Image.Length] == 5|| MyPM[i + t2 + t1 * Image.Length] == 35) {
							ScoreW++;
						}
						break;
					case 5:
						if (MyPM[i + t2 + t1 * Image.Length] == 2|| MyPM[i + t2 + t1 * Image.Length] == 14) {
							ScoreR++;
						}
						else if (MyPM[i + t2 + t1 * Image.Length] == 3|| MyPM[i + t2 + t1 * Image.Length] == 21) {
							ScoreY++;
						}
						else if (MyPM[i + t2 + t1 * Image.Length] == 6|| MyPM[i + t2 + t1 * Image.Length] == 42) {
							ScoreR++;
							ScoreY++;
						}
						break;
					case 9:
						if (MyPM[i + t2 + t1 * Image.Length] == 2|| MyPM[i + t2 + t1 * Image.Length] == 14) {
							ScoreR++;
						}
						else if (MyPM[i + t2 + t1 * Image.Length] == 5|| MyPM[i + t2 + t1 * Image.Length] == 35) {
							ScoreW++;
						}
						else if (MyPM[i + t2 + t1 * Image.Length] == 10|| MyPM[i + t2 + t1 * Image.Length] == 70) {
							ScoreR++;
							ScoreW++;
						}
						break;
					case 10:
						if (MyPM[i + t2 + t1 * Image.Length] == 3|| MyPM[i + t2 + t1 * Image.Length] == 21) {
							ScoreY++;
						}
						else if (MyPM[i + t2 + t1 * Image.Length] == 5|| MyPM[i + t2 + t1 * Image.Length] == 35) {
							ScoreW++;
						}
						else if (MyPM[i + t2 + t1 * Image.Length] == 15|| MyPM[i + t2 + t1 * Image.Length] == 105) {
							ScoreY++;
							ScoreW++;
						}
						break;
					case 12:
						if (MyPM[i + t2 + t1 * Image.Length] == 3|| MyPM[i + t2 + t1 * Image.Length] == 21) {
							ScoreY++;
						}
						else if (MyPM[i + t2 + t1 * Image.Length] == 6|| MyPM[i + t2 + t1 * Image.Length] == 42) {
							ScoreR++;
							ScoreY++;
						}
						else if (MyPM[i + t2 + t1 * Image.Length] == 10|| MyPM[i + t2 + t1 * Image.Length] == 70) {
							ScoreR++;
							ScoreW++;
						}
						else if (MyPM[i + t2 + t1 * Image.Length] == 2|| MyPM[i + t2 + t1 * Image.Length] == 14) {
							ScoreR++;
						}
						else if (MyPM[i + t2 + t1 * Image.Length] == 5|| MyPM[i + t2 + t1 * Image.Length] == 35) {
							ScoreW++;
						}
						else if (MyPM[i + t2 + t1 * Image.Length] == 15|| MyPM[i + t2 + t1 * Image.Length] == 105) {
							ScoreY++;
							ScoreW++;
						}
						else if (MyPM[i + t2 + t1 * Image.Length] == 30|| MyPM[i + t2 + t1 * Image.Length] == 210) {
							ScoreY++;
							ScoreW++;
							ScoreR++;
						}
						break;
					case 0:
						continue;
						break;
				}
			}
		}
		
	#pragma region //CHECK IF MAX SCORE CHANGED
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
	#pragma endregion
	}

#pragma region //SAVE OUTPUT VALUES
	(*RedBall).Y_coordinate = MaxR[0] / Image.Length;
	(*RedBall).X_Coordinate = MaxR[0] % Image.Length - 2;
	(*WhiteBall).Y_coordinate = MaxW[0] / Image.Length;
	(*WhiteBall).X_Coordinate = MaxW[0] % Image.Length - 2;
	(*YellowBall).Y_coordinate = MaxY[0] / Image.Length;
	(*YellowBall).X_Coordinate = MaxY[0] % Image.Length - 2;

	(*RedBall).Score = MaxR[1];
	(*YellowBall).Score = MaxY[1];
	(*WhiteBall).Score = MaxW[1];
#pragma endregion
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
Debug.Status = 1;
Error.RGBMin = 0;
Error.RGBMax = 255;

#pragma endregion

#pragma region //ASSIGNS COMMAND LINE INPUTS TO APPROPRIATE VARIABLES
//ERROR_TEST: CHECKS IF THE NUMBER OF ARGUMENTS RECEIVED IS EQUAL TO THE NUMBER OF ARGUMENTS EXPECTED
if(argc != Error.NumberOfInputs + 1){
    perror("Pas le bon nombre de paramètres dans la ligne de commande.");
    return 1;
}

//ERROR_TEST: CHECKS THAT ALL VALUES ARE NUMBERS
for(int j=1; j <= Error.NumberOfInputs; j++){
	int Res;
	Res = isNumber(argv[j]);
	if (Res != 1){
		perror("Inputs must be numbers");
	}
}

//ASSIGNS COMMAND LINE INPUTS TO APPROPRIATE VARIABLES
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
	WhiteBall.RedMin = atoi(argv[19])-6;
	WhiteBall.GreenMax = atoi(argv[20]);
	WhiteBall.BlueMin = atoi(argv[21]);
	WhiteBall.BlueMax = atoi(argv[22]);
    Table.LightBlueRedMin = atoi(argv[23]);
    Table.LightBlueRedMax = atoi(argv[24]);
    Table.LightBlueGreenMin = atoi(argv[25]);
    Table.LightBlueGreenMax = atoi(argv[26]);
    Table.LightBlueBlueMin = atoi(argv[27]);
    Table.LightBlueBlueMax = atoi(argv[28]);
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
	//ERROR_TEST:CHECKS THAT RGB VALUES ARE IN RGB RANGE: 0-255
	for(int j = 5; j<=28; j++){
		if(atoi(argv[j])< Error.RGBMin || atoi(argv[j])> Error.RGBMax){
			perror("Values 5-28 must be RGB values");
		}
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
    Table.FirstPixel = (Image.Height - Table.TopBorder) * Image.Length + Table.LeftBorder;
    Table.LastPixel = Image.Length * (Image.Height - Table.BottomBorder) - (Image.Length - Table.RightBorder);

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

	Table.LightBlueRedMax = Table.LightBlueRedMax + 15;
	Table.LightBlueBlueMin = Table.LightBlueBlueMin - 20;

	Table.DarkBlueRedMin = 0;
    Table.DarkBlueRedMax = 140;
    Table.DarkBlueGreenMin = 0;
    Table.DarkBlueGreenMax = 140;
    Table.DarkBlueBlueMin = 85;
    Table.DarkBlueBlueMax = 255;

	//INITIALISE DEFAULT DEBUG VALUES
	Debug.LightBlueCount = 0;
	Debug.DarkBlueCount = 0;
	Debug.RedCount = 0;
	Debug.WhiteCount = 0;
	Debug.YellowCount = 0;
	Debug.ScanCount = 0;
#pragma endregion

#pragma region //FUNCTION CALLING
    clock_t t;
	t = clock();
	IsColor(RedBall, YellowBall, WhiteBall, Table, MyPM, &Debug);
    IsBall(&RedBall, &YellowBall, &WhiteBall, Table, Image, MyPM, &Debug);
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
	if(Debug.Status == 1){
		//OPENS Pos.txt IN WRITE MODE
		FILE *DebugFile = fopen("Debug.txt", "w");

		//ERROR_TEST: CHECKS IF Pos.txt WAS OPENED
		if (DebugFile == NULL)
		{
			perror("Error Opening Pos.txt");
			return 1;
		}
		fprintf(DebugFile,"\n\nIsBall took %lf seconds to execute \n", time_taken);
		fprintf(DebugFile,"Table.LightBlueBlueMin: %d \n", Table.LightBlueBlueMin);
		fprintf(DebugFile,"Table.LightBlueBlueMax: %d \n", Table.LightBlueBlueMax);
		fprintf(DebugFile,"Table.LightBlueGreenMin: %d \n", Table.LightBlueGreenMin);
		fprintf(DebugFile,"Table.LightBlueGreenMax: %d \n", Table.LightBlueGreenMax);
		fprintf(DebugFile,"Table.LightBlueRedMin: %d \n", Table.LightBlueRedMin);
		fprintf(DebugFile,"Table.LightBlueRedMax: %d \n", Table.LightBlueRedMax);
		fprintf(DebugFile,"Light Blue Count: %d \n", Debug.LightBlueCount);
		fprintf(DebugFile,"Dark Blue Count: %d \n", Debug.DarkBlueCount);
		fprintf(DebugFile,"Red Count: %d \n", Debug.RedCount);
		fprintf(DebugFile,"Yellow Count: %d \n", Debug.YellowCount);
		fprintf(DebugFile,"White Count: %d \n", Debug.WhiteCount);
		fprintf(DebugFile,"Neither Count: %d \n", Debug.NeitherCount);
		fprintf(DebugFile,"Skip Type 1 Count: %d \n", Debug.SkipCountType1);
		fprintf(DebugFile,"Skip Type 2 Count: %d \n", Debug.SkipCountType2);
		fprintf(DebugFile,"Scan Count: %d \n", Debug.ScanCount);
	}
#pragma endregion

#pragma region //FREE THE MEMORY ALLOCATED TO MyPM
	free(MyPM);
	return 0;
#pragma endregion
}
