//This Version of Pix2Pos uses additional smaller functions for readability but doubles execution times



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

struct PixelInformation{
	int RedValue;
	int GreenValue;
	int BlueValue;
} Pixel;

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
	unsigned int IdentificationNumber;
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
	int BallsMissing;
	int BluePercent;
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
    int ImageHeightMin;
    int ImageHeightMax;
    int ImageLengthMin;
    int ImageLengthMax;
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
	int MinBluePercent;
}Error;

struct DebugManagement{
	int Status;
	int BlueCount;
	int ColorCounter;
	int RedCount;
	int YellowCount;
	int WhiteCount;
	int NeitherCount;
	int ScanCount;
	int SkipCountType1;
	int SkipCountType2;
	clock_t TimerIsColor;
	double TimeTakenIsColor;
	clock_t TimerIsBall;
	double TimeTakenIsBall;
	clock_t TimerRGBConverter;
	double TimeTakenRGBConverter;
	clock_t Timer4;
	clock_t Timer5;
} Debug = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int BallColorMatcher (struct PixelInformation Pixel,struct BallInformation Ball, struct BallInformation RedBall, struct BallInformation YellowBall, struct BallInformation WhiteBall){
	if (Pixel.RedValue >= Ball.RedMin && Pixel.RedValue <= Ball.RedMax && Pixel.GreenValue >= Ball.GreenMin && Pixel.GreenValue <= Ball.GreenMax && Pixel.BlueValue >= Ball.BlueMin && Pixel.BlueValue <= Ball.BlueMax) {
			return Ball.IdentificationNumber;
		}
	else return 1;
}

int TableColorMatcher (struct PixelInformation Pixel,struct TableInformation Table, struct DebugManagement *DebugPointer){
	if (Pixel.RedValue >= Table.RedMin && Pixel.RedValue <= Table.RedMax && Pixel.GreenValue >= Table.GreenMin && Pixel.GreenValue <= Table.GreenMax && Pixel.BlueValue >= Table.BlueMin && Pixel.BlueValue <= Table.BlueMax) {
			(*DebugPointer).BlueCount++;
			return 7;
		}
	else return 1;
}

int ColorCounter (unsigned int Color, struct BallInformation Ball, struct BallInformation Ball2, struct BallInformation Ball3){
	if (Color == Ball.IdentificationNumber || Color == Ball.IdentificationNumber * Ball2.IdentificationNumber || Color == Ball.IdentificationNumber * Ball3.IdentificationNumber|| Color == Ball.IdentificationNumber * Ball2.IdentificationNumber * Ball3.IdentificationNumber){
		return 1;
		printf("found");
	}
	else return 0;
}

void RGBConverter (struct PixelInformation *Pixel, unsigned int HexRGB){
	//CONVERTING THE RGB VALUES FROM BINARY TO BASE 10
		(*Pixel).BlueValue = HexRGB & 255;
		(*Pixel).GreenValue = (HexRGB >> 8) & 255;
		(*Pixel).RedValue = (HexRGB >> 16) & 255;
}

int IsNumber(char number[]){
	//TLDR: CHECKS IF AN ARRAY OF CHARACTERS ARE ACTUALLY NUMBERS

	// INPUTS:  - ARRAY OF CHARACTERS(char number[])

	// OUTPUTS: - INT: 1 IF IT IS A NUMBER, 0 IF IT IS NOT A NUMBER
    int i = 0;
    if (number[0] == '-')
        i = 1;
    for (; number[i] != 0; i++)
    {
        if (isdigit(number[i]) != 1)
            return 0;
    }
    return 1;
}

void IsColor(struct BallInformation RedBall, struct BallInformation YellowBall, struct BallInformation WhiteBall, struct TableInformation Table, unsigned int MyPM[], struct DebugManagement *Debug, struct PixelInformation Pixel) {
	//TLDR: TAKES A ARRAY OF HEX RGB VALUES AND COMPARES THE VALUES WITH GIVEN RGB RANGES

	// INPUTS:  - RGB RANGES OF ALL THREE BALLS(RedBall, YellowBall, WhiteBall)
	//          - TABLE INFORMATION (TABLE)
	//          - HEX ARRAY TO BE CONVERTED (MyPM[])
	//  		- DEBUGGING MANAGEMENT (DEBUG)

	// OUTPUTS: - NO OUTPUTS BUT CHANGES VALUES IN ORIGINAL ARRAY(MyPM[])


	//DECLARE LOCAL VARIABLES
	int k = 1;
	int temp = 1;

	//FOR LOOP TO CYCLE THROUGH ALL OF THE TABLE'S PIXELS 
	for (int i = Table.FirstPixel - 1; i < Table.LastPixel; i++) {
		temp = 1;
		//FILTER TO NOT LOOK AT LEFT AND RIGHT EDGES
		if (k == Table.RightBorder - Table.LeftBorder + 1) {
				k = 1;
				i = i - 1 + Image.Length - Table.RightBorder + Table.LeftBorder;
			}
		else k++;
		//CONVERTING THE RGB VALUES FROM BINARY TO BASE 10
		RGBConverter(&Pixel, *(MyPM + i));
		
		temp = BallColorMatcher (Pixel, RedBall, RedBall, YellowBall, WhiteBall) * BallColorMatcher (Pixel, YellowBall, RedBall, YellowBall, WhiteBall)* BallColorMatcher (Pixel, WhiteBall, RedBall, YellowBall, WhiteBall);;
		//MyPM[i] = BallColorMatcher (Pixel, RedBall, RedBall, YellowBall, WhiteBall);
		//MyPM[i] = MyPM[i] * BallColorMatcher (Pixel, YellowBall, RedBall, YellowBall, WhiteBall);
		//MyPM[i] = MyPM[i] * BallColorMatcher (Pixel, WhiteBall, RedBall, YellowBall, WhiteBall);

		MyPM[i] = temp;

		if (MyPM[i] == 1){
			MyPM[i] = TableColorMatcher(Pixel,Table, Debug);
		}
		
	}
}

void IsBall(struct BallInformation *RedBallPointer, struct BallInformation *YellowBallPointer, struct BallInformation *WhiteBallPointer, struct TableInformation Table, struct ImageInformation Image, unsigned int MyPM[],  struct PixelInformation *PixelPointer) {
	//TLDR: TAKES AN ARRAY OF INTEGERS WHICH REPRESENT SPECIAL COLORS AND FINDS THE BOX WHICH CONTAINS THE LARGEST AMOUNT OF A GIVEN COLOR

	// INPUTS:  - ACCES TO VARIABLES WHICH DEFINES ALL THREE BALLS' MAXIMUM SCORE(RedBall, YellowBall, WhiteBall)
	//			- IMAGE INFORMATION (IMAGE)
	//          - TABLE INFORMATION (TABLE)
	//          - ARRAY OF INTEGERS WHICH REPRESENT SPECIAL COLORS (MyPM[])
	//  		- DEBUGGING MANAGEMENT (DEBUG)

	// OUTPUTS: - NO OUTPUTS BUT CHANGES VALUES FOR ALL THREE BALLS(RedBall, YellowBall, WhiteBall)

	//DECLARE LOCAL VARIABLES
	int ScoreR = 0, ScoreY = 0, ScoreW = 0, MaxR[2] = { 0,0 }, MaxY[2] = { 0,0 }, MaxW[2] = { 0,0 }, k = 1, State;

	//FOR LOOP TO MOVE THE BOX YOUR LOOKING AT
	for (int i = Table.FirstPixel - 1; i < Table.LastPixel; i++) {
		ScoreR = 0;
		ScoreW = 0;
		ScoreY = 0;
		State = 12;
		
			//FILTER TO NOT LOOK AT LEFT AND RIGHT EDGES
			if (k == Table.RightBorder - Table.LeftBorder - Table.BallSize + 1) {
				k = 1;
				i = i + Table.BallSize - 1 + Image.Length - Table.RightBorder + Table.LeftBorder;
			}
			else k++;
			if(MyPM[i + (Table.BallSize/2) + (Image.Length * (Table.BallSize/2))] == 7 || MyPM[i + (Table.BallSize/2) + (Image.Length * (Table.BallSize/2)) + 1] == 7|| MyPM[i + (Table.BallSize/2) + (Image.Length * (Table.BallSize/2) + 1)] == 7){
			continue;
				}
		//FOR LOOP GO FROM TOP TO BOTTOM IN A SQUARE
		for (int t1 = 0; t1 < Table.BallSize; t1++) {
			//OPTIMISATION: IF THE AMOUNT OF PIXELS LEFT TO LOOK AT IN A SQUARE IS SMALLER THAN THE DIFFERENCE BETWEEN THE MAX SCORE AND CURRENT SCORE CONTINUE TO NEXT SQUARE
			if(State != 3 && State != 7 && State != 10 && State != 0 && ((Table.BallSize * Table.BallSize) - ( t1 * Table.BallSize)) < MaxR[1]-ScoreR){
				State = State - 2;
			}
			if(State != 3 && State != 2 && State != 5 && State != 0 && ((Table.BallSize * Table.BallSize) - ( t1 * Table.BallSize)) < MaxW[1]-ScoreW){
				State = State - 7;
			}
			if(State != 2 && State != 7 && State != 9 && State != 0 && ((Table.BallSize * Table.BallSize) - ( t1 * Table.BallSize)) < MaxY[1]-ScoreY){
				State = State - 3;
			}

			//FOR LOOP GO FROM LEFT TO RIGHT IN A SQUARE
			for (int t2 = 0; t2 < Table.BallSize; t2++) {
				//(*DebugPointer).ScanCount++;
				int sugma = MyPM[i + t2 + t1 * Image.Length];
					if(State != 0){
						if (ColorCounter(MyPM[i + t2 + t1 * Image.Length], *RedBallPointer, *YellowBallPointer, *WhiteBallPointer) == 1){
							ScoreR++;
						}
						if (ColorCounter(MyPM[i + t2 + t1 * Image.Length], *YellowBallPointer,  *RedBallPointer, *WhiteBallPointer) == 1){
							ScoreY++;
						}
						if (ColorCounter(MyPM[i + t2 + t1 * Image.Length], *WhiteBallPointer, *YellowBallPointer,  *RedBallPointer) == 1){
							ScoreW++;
						}
					}
					else {
						t1 = Table.BallSize;
						//(*DebugPointer).SkipCountType2++;
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
	(*RedBallPointer).Y_coordinate = MaxR[0] / Image.Length;
	(*RedBallPointer).X_Coordinate = MaxR[0] % Image.Length - 2;
	(*WhiteBallPointer).Y_coordinate = MaxW[0] / Image.Length;
	(*WhiteBallPointer).X_Coordinate = MaxW[0] % Image.Length - 2;
	(*YellowBallPointer).Y_coordinate = MaxY[0] / Image.Length;
	(*YellowBallPointer).X_Coordinate = MaxY[0] % Image.Length - 2;
	(*RedBallPointer).Score = MaxR[1];
	(*YellowBallPointer).Score = MaxY[1];
	(*WhiteBallPointer).Score = MaxW[1];
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
Error.ImageHeightMin = 100;
Error.ImageHeightMax = 1000;
Error.ImageLengthMin = 100;
Error.ImageLengthMax = 1000;
Error.RGBMin = 0;
Error.RGBMax = 255;
Table.BallsMissing = 0;
Error.MinBluePercent = 40;
Debug.Status = 1;

#pragma endregion

#pragma region //ASSIGNS COMMAND LINE INPUTS TO APPROPRIATE VARIABLES
//ERROR_TEST: CHECKS IF THE NUMBER OF ARGUMENTS RECEIVED IS EQUAL TO THE NUMBER OF ARGUMENTS EXPECTED
if(argc != Error.NumberOfInputs + 1){
    fprintf(stderr,"Pas le bon nombre de paramètres dans la ligne de commande.");
    return 1;
}

//ERROR_TEST: CHECKS THAT ALL VALUES ARE NUMBERS
for(int j=1; j <= Error.NumberOfInputs; j++){
	int Res;
	Res = IsNumber(argv[j]);
	if (Res != 1){
		fprintf(stderr,"Inputs must be numbers");
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
	WhiteBall.GreenMin = atoi(argv[19]);
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
		fprintf(stderr,"Le diamètre de la boule est en dehors des valeurs acceptable");
		return 1;
	}

    //COMPUTE TABLE HEIGHT AND WIDTH
    Table.Width = Table.RightBorder - Table.LeftBorder;
    Table.Height = Table.TopBorder - Table.BottomBorder;

	//ERROR_TEST:CHECKS THAT THE TABLE LENGTH AND HEIGHT IS IN THE APPROPRIATE RANGE
	if (Table.Width < Error.TableLengthMin || Table.Width >Error.TableLengthMax || Table.Height < Error.TableHeightMin || Table.Height > Error.TableHeightMax){
		fprintf(stderr,"La longueur et/ou la hauteur de la table est en dehors de la zone acceptable");
		return 1;
    }
	//ERROR_TEST:CHECKS THAT RGB VALUES ARE IN RGB RANGE: 0-255
	for(int j = 5; j<=28; j++){
		if(atoi(argv[j])< Error.RGBMin || atoi(argv[j])> Error.RGBMax){
			fprintf(stderr,"Values 5-28 must be RGB values");
		}
	}
	#pragma endregion

#pragma region //OPEN Pixmap.bin AND STORES IT IN MyPM
    //OPEN Pixmap.bin FOR READING
	FILE *file = fopen("Pixmap217.bin", "rb");

    //ERROR_TEST: CHECK IF FILE WAS OPENED
	if (file == NULL) {
		fprintf(stderr,"Error opening file");
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
		fprintf(stderr,"Error allocating memory");
		fclose(file);
		return 1;
	}

    //READ THE CONTENTS OF Pixmap.bin INTO MyPM
	size_t elements_read = fread(MyPM, sizeof(unsigned int), num_integers , file);

    //ERROR_TEST: MAKES SURE THAT THE NUMBER OF ELEMENTS READ IS EQUAL TO THE NUMBER OF ELEMENTS COMPUTED
	if (elements_read != num_integers) {
		if (ferror(file)) {
			fprintf(stderr,"Error reading file");
		}
		else {
			fprintf(stderr,"Unexpected end of file\n");
		}
		free(MyPM);
		fclose(file);
		return 1;
	}

	// Close the file
	if (fclose(file) != 0) {
		fprintf(stderr,"Error closing file");
		free(MyPM);
		return 1;
	}
    
#pragma endregion

#pragma region //INITIALISATION OF VALUES

    //EXTRACT LENGTH AND HEIGHT FROM MyPM
	Image.Length = MyPM[0];
	Image.Height = MyPM[1];
	Image.NumberOfPixels = Image.Length * Image.Height;

	//ERROR_TEST:CHECKS THAT THE IMAGE LENGTH AND HEIGHT IS IN THE APPROPRIATE RANGE
	if (Image.Height < Error.ImageHeightMin || Image.Height >Error.ImageHeightMax || Image.Length < Error.ImageLengthMin || Image.Length > Error.ImageLengthMax){
		fprintf(stderr,"La longueur et/ou la hauteur de l'image est en dehors de la zone acceptable");
		return 1;
    }

    //ERROR_TEST: CHECKS IF NUMBER OF PIXELS IN Pixmap.bin IS EQUAL TO THE LENGTH TIMES THE HEIGHT GIVEN IN Pixmap.bin
    if(Image.Length * Image.Height > num_integers - 2){
        fprintf(stderr,"Pas assez de pixels");
        return 1;
    }
    if(Image.Length * Image.Height < num_integers - 2){
        fprintf(stderr,"Trop de pixels\n");
    }

    //COMPUTE FIRST AND LAST PIXEL OF TABLE
    Table.FirstPixel = Table.BottomBorder * Image.Length + Table.LeftBorder;
    Table.LastPixel = (Table.TopBorder - Table.BallSize)*Image.Length + Table.RightBorder - Table.BallSize;

    //INITIALISE DEFAULT VALUES FOR THE BALLS' SCORE AND COORDINATES
    RedBall.Score = 0;
    RedBall.X_Coordinate = 0;
    RedBall.Y_coordinate = 0;
	RedBall.IdentificationNumber = 2;
    YellowBall.Score = 0;
    YellowBall.X_Coordinate = 0;
    YellowBall.Y_coordinate = 0;
	YellowBall.IdentificationNumber = 3;
    WhiteBall.Score = 0;
    WhiteBall.X_Coordinate = 0;
    WhiteBall.Y_coordinate = 0;
	WhiteBall.IdentificationNumber = 5;

	//INITIALISE DEFAULT DEBUG VALUES
	Debug.BlueCount = 0;
	Debug.RedCount = 0;
	Debug.WhiteCount = 0;
	Debug.YellowCount = 0;
	Debug.ScanCount = 0;
	Debug.ColorCounter = 0;
#pragma endregion

#pragma region //FUNCTION CALLING
	Debug.TimerIsColor = clock();
	IsColor(RedBall, YellowBall, WhiteBall, Table, MyPM, &Debug, Pixel);
	Debug.TimerIsColor = clock() - Debug.TimerIsColor;
	Debug.TimerIsBall = clock();
    IsBall(&RedBall, &YellowBall, &WhiteBall, Table, Image, MyPM, &Pixel);
	Debug.TimerIsBall = clock() - Debug.TimerIsBall; 
	Debug.TimeTakenIsColor = ((double)Debug.TimerIsColor)/CLOCKS_PER_SEC;
	Debug.TimeTakenIsBall = ((double)Debug.TimerIsBall)/CLOCKS_PER_SEC;

	//CHECKS IF ALL BALLS WERE FOUND
    if(Table.BallsMissing == 0 && (RedBall.Score < Error.BallMinScore || YellowBall.Score < Error.BallMinScore ||WhiteBall.Score < Error.BallMinScore)){
		Table.BallsMissing = 1;
		IsBall(&RedBall, &YellowBall, &WhiteBall, Table, Image, MyPM, &Pixel);
    };

#pragma endregion

#pragma region //CREATE POX.TXT FILE
    //OPENS Pos.txt IN WRITE MODE
	FILE *f_out = fopen("Pos.txt", "w");

	//ERROR_TEST: CHECKS IF Pos.txt WAS OPENED
	if (f_out == NULL)
	{
        fprintf(stderr,"Error Opening Pos.txt");
		return 1;
	}

    //CHECKS IF ALL BALLS WERE FOUND
    if(RedBall.Score < Error.BallMinScore){
        RedBall.Score = 0;
        RedBall.X_Coordinate = -1;
        RedBall.Y_coordinate = -1;
        fprintf(stderr,"La boule rouge n'a pas était trouvée");
    };
    if(YellowBall.Score < Error.BallMinScore){
        YellowBall.Score = 0;
        YellowBall.X_Coordinate = -1;
        YellowBall.Y_coordinate = -1;
        fprintf(stderr,"La boule jaune n'a pas était trouvée");
    };
    if(WhiteBall.Score < Error.BallMinScore){
        WhiteBall.Score = 0;
        WhiteBall.X_Coordinate = -1;
        WhiteBall.Y_coordinate = -1;
        fprintf(stderr,"La boule blanche n'a pas était trouvée");
    };
	

    //WRITES COORDINATES AND SCORE TO pos.txt
    fprintf(f_out, "Red: %d, %d, %d\n", RedBall.X_Coordinate, RedBall.Y_coordinate, RedBall.Score);
	fprintf(f_out,"Yellow: %d, %d, %d\n", YellowBall.X_Coordinate, YellowBall.Y_coordinate, YellowBall.Score);
	fprintf(f_out,"White: %d, %d, %d", WhiteBall.X_Coordinate, WhiteBall.Y_coordinate, WhiteBall.Score);
#pragma endregion

#pragma region //DEBUG

	Table.BluePercent = (Debug.BlueCount * 100) / Image.NumberOfPixels;
	if (Table.BluePercent < Error.MinBluePercent){
		fprintf(stderr,"Wrong Image inserted");
	}
	

	if(Debug.Status == 1){
		//OPENS Pos.txt IN WRITE MODE
		FILE *DebugFile = fopen("Debug.txt", "w");

		//ERROR_TEST: CHECKS IF Pos.txt WAS OPENED
		if (DebugFile == NULL)
		{
			fprintf(stderr,"Error Opening Pos.txt");
			return 1;
		}

		time_t tr;   // not a primitive datatype
    	time(&tr);
		fprintf(DebugFile,"%s\n\n", ctime(&tr));

		fprintf(DebugFile,"Red: 203, 275, 104\n");
		fprintf(DebugFile,"Yellow: 604, 220, 61\n");
		fprintf(DebugFile,"White: 169, 113, 116\n\n\n");
		fprintf(DebugFile,"IsBall took %lf seconds to execute \n", Debug.TimeTakenIsBall);
		fprintf(DebugFile,"IsColor took %lf seconds to execute \n", Debug.TimeTakenIsColor);
		//fprintf(DebugFile,"Color Count: %d \n", Debug.ColorCounter);
		//fprintf(DebugFile,"BallSize %d \n", Table.BallSize);
		//fprintf(DebugFile,"Table.BlueMin: %d \n", Table.BlueMin);
		//fprintf(DebugFile,"Table.BlueMax: %d \n", Table.BlueMax);
		//fprintf(DebugFile,"Table.GreenMin: %d \n", Table.GreenMin);
		//fprintf(DebugFile,"Table.GreenMax: %d \n", Table.GreenMax);
		//fprintf(DebugFile,"Table.RedMin: %d \n", Table.RedMin);
		//fprintf(DebugFile,"Table.RedMax: %d \n", Table.RedMax);
		//fprintf(DebugFile,"Blue Count: %d \n", Debug.BlueCount);
		//fprintf(DebugFile,"Red Count: %d \n", Debug.RedCount);
		//fprintf(DebugFile,"Yellow Count: %d \n", Debug.YellowCount);
		//fprintf(DebugFile,"White Count: %d \n", Debug.WhiteCount);
		//fprintf(DebugFile,"Neither Count: %d \n", Debug.NeitherCount);
		fprintf(DebugFile,"Blue Percent: %d \n", Table.BluePercent);
		fprintf(DebugFile,"Skip Type 1 Count: %d \n", Debug.SkipCountType1);
		fprintf(DebugFile,"Skip Type 2 Count: %d \n", Debug.SkipCountType2);
		fprintf(DebugFile,"Scan Count: %d \n", Debug.ScanCount);
		fprintf(DebugFile,"Blue Percent: %d %% \n", Table.BluePercent);

	}
#pragma endregion

#pragma region //FREE THE MEMORY ALLOCATED TO MyPM
	free(MyPM);
	return 0;
#pragma endregion
}
