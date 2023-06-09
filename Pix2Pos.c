/*
Pix2Pos.c

TAKES BINARY FILE OF AN IMAGE OF A FRENCH POOL TABLE GAME AND OUTPUTS COORDINATES FOR ALL THREE BALLS IN A TEXT FILE

THE CODE USES 3 DIFFERENT FUNCTIONS : 

    - IsColor
    - IsBall
    - IsNumber

(INFORMATION ABOUT EACH OF THEM BELOW)

INPUT
    - Binary Pixmap of image: (pixmap.bin)
	- Command line (see line 351 for additional information)

OUTPUT
    - Text file with coordinates for all three balls (pos.txt)

AUTHORS : ROMAIN LATTION & RYAN SVOBODA
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

//BallInformation IS A STRUCTURE USED TO STORE ALL USEFUL INFORMATION ABOUT A BALL
struct BallInformation {
	int IdentificationNumber;
    unsigned int RedMin; //THE 6 FIRST VARIABLES ARE USED TO DEFINE THE RGB RANGE FOR A GIVEN BALL COLOR
    unsigned int RedMax;
    unsigned int GreenMin;
    unsigned int GreenMax;
    unsigned int BlueMin;
    unsigned int BlueMax;
    int X_Coordinate; //COORDINATES OF A BALL
    int Y_coordinate;
    int Score; //THE SCORE REPRESENTS THE NUMBER OF PIXELS IN A BallSize x BallSize SQUARE WHICH BELONG TO THE PREVIOUSLY DEFINED RGB RANGE
} RedBall, YellowBall, WhiteBall; //DECLARING ALL THREE BALLS

//TableInformation IS A STRUCTURE USED TO STORE ALL USEFUL INFORMATION ABOUT THE POOL TABLE
struct TableInformation {
    int RedMin; //THE 6 FIRST VARIABLES ARE USED TO DEFINE THE RGB RANGE FOR THE BILLIARD CLOTH
    int RedMax;
    int GreenMin;
    int GreenMax;
    int BlueMin;
    int BlueMax;
    int FirstPixel; //FIRST AND LAST PIXELS OF THE TABLE
    int LastPixel;
    int LeftBorder; //ALL 4 EDGES OF THE POOL TABLE
    int RightBorder;
    int TopBorder;
    int BottomBorder;
    int Width; //WIDTH AND HEIGHT OF THE POOL TABLE
    int Height;
    int BallSize; //BallSize DEFINES THE DIAMETER OF THE BALL
	int BluePercent; //NUMBER OF BLUE PIXELS IN THE TABLE AREA EXPRESSED AS A PERCENT OVER THE ENTIRE IMAGE
}Table;

//ImageInformation IS A STRUCTURE USED TO STORE ALL USEFUL INFORMATION ABOUT THE POOL TABLE
struct ImageInformation{
    int Width; //WIDTH AND HEIGHT OF THE IMAGE 
    int Height;
    int NumberOfPixels; //NUMBER OF PIXELS IN THE IMAGE
}Image;

//ErrorManagement IS A STRUCTURE USED TO STORE ALL THE ERROR BOUNDARIES
struct ErrorManagement {
    int RGBMin; //MINIMUM AND MAXIMUM RGB RANGE VALUE
    int RGBMax;
    int NumberOfInputs; //NUMBER OF EXPECTED INPUTS
    int BallSizeMin; //ALL THE OTHER VARIABLES ARE SELF EXPLANATORY
    int BallSizeMax;
    int ImageHeightMin;
    int ImageHeightMax;
    int ImageWidthMin;
    int ImageWidthMax;
    int TableHeightMin;
    int TableHeightMax;
    int TableWidthMin;
    int TableWidthMax;
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

//DebugManagement IS A STRUCTURE USED TO STORE ALL THE STATISTICS SHOWN IN debug.txt
struct DebugManagement{
	int Status; //USED TO ACTIVATE DEBUGGER MODE, ON = 1, OFF = 0
	int BlueCount;	//COUNT OF ALL X PIXELS
	int RedCount; 
	int YellowCount;
	int WhiteCount;
	int NeitherCount;
	int ScanCount; //NUMBER OF TIMES A PIXEL WAS COMPARED TO RGB VALUES
	int NonOptimisedScanCount;
	int SkipCountType1; //NUMBER OF TIMES TYPE 1 OPTIMISATION WAS USED
	int SkipCountType2; //NUMBER OF TIME TYPE 2 OPTIMISATION WAS USED
	clock_t Timer; //TIMER FOR THE ENTIRE MAIN FUNCTION
	double TimeTaken;
} Debug;

int IsNumber(char Number[]){
	//TLDR: CHECKS IF AN ARRAY OF CHARACTERS ARE ACTUALLY NUMBERS

	// INPUTS:  - ARRAY OF CHARACTERS (char Number[])

	// OUTPUTS: - INT: 1 IF IT IS A NUMBER, 0 IF IT IS NOT A NUMBER
    int i = 0;
    if (Number[0] == '-'){
        i = 1;
	}
    for (; Number[i] != 0; i++){
        if (isdigit(Number[i]) != 1)//isdigit IS A FUNCTION FROM THE ctype.h LIBRARY
            return 0;
    }
    return 1;
}

void IsColor( unsigned int MyPM[]) {
	//TLDR: TAKES A ARRAY OF HEX RGB VALUES AND COMPARES THE VALUES WITH GIVEN RGB RANGES

	// INPUTS:  - HEX ARRAY TO BE CONVERTED (MyPM[])
	//
	//   USES:  - RGB RANGES OF ALL THREE BALLS(RedBall, YellowBall, WhiteBall)
	//          - TABLE INFORMATION (TABLE)
	//  		- DEBUGGING MANAGEMENT (DEBUG)
	//
	// OUTPUTS: - NO OUTPUTS BUT CHANGES VALUES IN ORIGINAL ARRAY(MyPM[])


	//DECLARE LOCAL VARIABLES
	int HexRGB, Blue, Green, Red, Out;
	int k = 1;

	//FOR LOOP TO CYCLE THROUGH ALL OF THE TABLE'S PIXELS 
	for (int i = Table.FirstPixel - 1; i < Table.LastPixel; i++) {

		//FILTER TO NOT LOOK AT LEFT AND RIGHT EDGES
		if (k == Table.RightBorder - Table.LeftBorder + 1) {
				k = 1;
				i = i - 1 + Image.Width - Table.RightBorder + Table.LeftBorder;
			}
		else k++;

		//CONVERTING THE RGB VALUES FROM BINARY TO BASE 10
		HexRGB = *(MyPM + i);
		Blue = HexRGB & 255;
		Green = (HexRGB >> 8) & 255;
		Red = (HexRGB >> 16) & 255;

		//OUT IS THE NEW VALUE ASSIGNED TO THE ELEMENTS IN MyPM
			// IF OUT IS A MULTIPLE OF 2 IT IS IN THE RED BALL RGB RANGE
			// IF OUT IS A MULTIPLE OF 3 IT IS IN THE YELLOW BALL RGB RANGE
			// IF OUT IS A MULTIPLE OF 5 IT IS IN THE WHITE BALL RGB RANGE
			// IF OUT IS A MULTIPLE OF 7 IT IS IN THE BLUE POOL TABLE RGB RANGE
		Out = 1;

		//CHECKS IF PIXELS ARE IN A GIVEN RGB RANGE AND CHANGES OUT ACCORDINGLY
		if (Red >= RedBall.RedMin && Red <= RedBall.RedMax && Green >= RedBall.GreenMin && Green <= RedBall.GreenMax && Blue >= RedBall.BlueMin && Blue <= RedBall.BlueMax) {
			Out = Out * RedBall.IdentificationNumber;
			Debug.RedCount++;
		}
		if (Red >= YellowBall.RedMin && Red <= YellowBall.RedMax && Green >= YellowBall.GreenMin && Green <= YellowBall.GreenMax && Blue >= YellowBall.BlueMin && Blue <= YellowBall.BlueMax) {
			Out = Out * YellowBall.IdentificationNumber;
			Debug.YellowCount++;
		}
		if (Red >= WhiteBall.RedMin && Red <= WhiteBall.RedMax && Green >= WhiteBall.GreenMin && Green <= WhiteBall.GreenMax && Blue >= WhiteBall.BlueMin && Blue <= WhiteBall.BlueMax) {
			Out = Out * WhiteBall.IdentificationNumber;
			Debug.WhiteCount++;
		}
		if(Out == 1){
			if (Red >= Table.RedMin && Red <= Table.RedMax && Green >= Table.GreenMin && Green <= Table.GreenMax && Blue >= Table.BlueMin && Blue <= Table.BlueMax) {
				Out = Out * 7;
				Debug.BlueCount++;
			}
		}
		if (Out == 1) {
			Out = 0;
			Debug.NeitherCount++;
		}
		//REPLACES MyPM[] RGB VALUES WITH OUT VALUES
		MyPM[i] = Out;
	}
}

void IsBall(unsigned int MyPM[]) {
	//TLDR: TAKES AN ARRAY OF INTEGERS WHICH REPRESENT SPECIAL COLORS AND FINDS THE BOX WHICH CONTAINS THE LARGEST AMOUNT OF A GIVEN COLOR

	// INPUTS:  - ARRAY OF INTEGERS WHICH REPRESENT SPECIAL COLORS (MyPM[])
	//
	//   USES: 	- ACCESS TO VARIABLES WHICH DEFINES ALL THREE BALLS' MAXIMUM SCORE(RedBall, YellowBall, WhiteBall)
	//			- IMAGE INFORMATION (IMAGE)
	//          - TABLE INFORMATION (TABLE)
	//  		- DEBUGGING MANAGEMENT (DEBUG)
	//
	// OUTPUTS: - NO OUTPUTS BUT CHANGES VALUES FOR ALL THREE BALLS(RedBall, YellowBall, WhiteBall)

	//DECLARE LOCAL VARIABLES
	int ScoreR = 0, ScoreY = 0, ScoreW = 0, MaxR[2] = { 0,0 }, MaxY[2] = { 0,0 }, MaxW[2] = { 0,0 }, k = 1, State, Position;
	int LocalRedID = RedBall.IdentificationNumber; //DECLARE LOCAL VARIABLE FOR CODE SPEED;
	int LocalWhiteID = WhiteBall.IdentificationNumber;
	int LocalYellowID = YellowBall.IdentificationNumber;

	int LocalRedWhiteID = LocalRedID * LocalWhiteID; //DO CALCULATION ONCE FOR SPEED;
	int LocalYellowWhiteID = LocalYellowID * LocalWhiteID;
	int LocalRedYellowID = LocalRedID * LocalWhiteID;
	int LocalRedYellowWhiteID = LocalRedID * LocalWhiteID * LocalYellowID;
	int LocalBallSize = Table.BallSize;

	int LocalImageWidth = Image.Width;//DECLARE LOCAL VARIABLE FOR CODE SPEED;

	//FOR LOOP TO MOVE THE BOX YOUR LOOKING AT
	for (int i = Table.FirstPixel - 1; i < Table.LastPixel - (LocalBallSize * Image.Width); i++) {
		ScoreR = 0;
		ScoreW = 0;
		ScoreY = 0;
		State = 12; //CONDITION FOR TYPE 2 OPTIMISATION, IF STATE == 0 -> SKIP CURRENT BALL SCAN
		
			//FILTER TO NOT LOOK AT LEFT AND RIGHT EDGES
			if (k == Table.RightBorder - Table.LeftBorder - LocalBallSize + 1) {
				k = 1;
				i = i + LocalBallSize - 1 + Image.Width - Table.RightBorder + Table.LeftBorder;
			}
			else k++;

			//OPTIMISATION TYPE 1: IF THE 3 PIXELS (L SHAPE) IN THE MIDDLE OF THE BallSize BOX IS THE SAME COLOR AS THE TABLE DO NOT SCAN THE CURRENT BOX AND CONTINUE TO NEXT SQUARE 
				if(MyPM[i + (LocalBallSize/2) + (Image.Width * (LocalBallSize/2))] == 7 || MyPM[i + (LocalBallSize/2) + (Image.Width * (LocalBallSize/2)) + 1] == 7|| MyPM[i + (LocalBallSize/2) + (Image.Width * (LocalBallSize/2) + 1)] == 7){
					Debug.SkipCountType1++;
					continue;
				}
		//FOR LOOP GO FROM TOP TO BOTTOM IN A SQUARE
		for (int line = 0; line < LocalBallSize; line++) {
			//OPTIMISATION TYPE 2: IF THE AMOUNT OF PIXELS LEFT TO LOOK AT IN A SQUARE IS SMALLER THAN THE DIFFERENCE BETWEEN THE MAX SCORE AND CURRENT SCORE CONTINUE TO NEXT SQUARE
			if(State != 10 && State != 7 && State != 3 && State != 0 && ((LocalBallSize * LocalBallSize) - ( line * LocalBallSize)) < MaxR[1]-ScoreR){
				State = State - 2;
			}
			if(State != 5 && State != 3 && State != 2 && State != 0 && ((LocalBallSize * LocalBallSize) - ( line * LocalBallSize)) < MaxW[1]-ScoreW){
				State = State - 7;
			}
			if(State != 9 && State != 7 && State != 2 && State != 0 && ((LocalBallSize * LocalBallSize) - ( line * LocalBallSize)) < MaxY[1]-ScoreY){
				State = State - 3;
			}
			//FOR LOOP GO FROM LEFT TO RIGHT IN A SQUARE
			for (int row = 0; row < LocalBallSize; row++) {
				Debug.ScanCount++;
				Position = i + row + line * LocalImageWidth;
				//SWITCH TO ONLY LOOK FOR BALLS THAT CAN BE IN A GIVEN SQUARE
					if(State != 0){
						if(MyPM[Position] == LocalYellowID) {
							ScoreY++;
						}
						else if(MyPM[Position] == LocalRedYellowID) {
							ScoreR++;
							ScoreY++;
						}
						else if(MyPM[Position] == LocalRedWhiteID) {
							ScoreR++;
							ScoreW++;
						}
						else if(MyPM[Position] == LocalRedID) {
							ScoreR++;
						}
						else if(MyPM[Position] == LocalWhiteID) {
							ScoreW++;
						}
						else if(MyPM[Position] == LocalYellowWhiteID) {
							ScoreY++;
							ScoreW++;
						}
						else if(MyPM[Position] == LocalRedYellowWhiteID) {
							ScoreY++;
							ScoreW++;
							ScoreR++;
						}
					}
					else{
						line = LocalBallSize;
						Debug.SkipCountType2++;
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
	RedBall.Y_coordinate = MaxR[0] / Image.Width;
	RedBall.X_Coordinate = MaxR[0] % Image.Width - 2;
	WhiteBall.Y_coordinate = MaxW[0] / Image.Width;
	WhiteBall.X_Coordinate = MaxW[0] % Image.Width - 2;
	YellowBall.Y_coordinate = MaxY[0] / Image.Width;
	YellowBall.X_Coordinate = MaxY[0] % Image.Width - 2;
	RedBall.Score = MaxR[1];
	YellowBall.Score = MaxY[1];
	WhiteBall.Score = MaxW[1];
	#pragma endregion
}

int main(int argc, char *argv[]) {

Debug.Timer = clock(); //START TIMER FOR THE MAIN FUNCTION

#pragma region //INITIALISATION OF ERROR VALUES
Error.BallSizeMin = 5;
Error.BallSizeMax = 20;
Error.BallMinScore = 15;
Error.NumberOfInputs = 29;
Error.TableHeightMax = 1000;
Error.TableHeightMin = 100;
Error.TableWidthMax = 1000;
Error.TableWidthMin = 100;
Error.ImageHeightMin = 100;
Error.ImageHeightMax = 1000;
Error.ImageWidthMin = 100;
Error.ImageWidthMax = 1000;
Error.RGBMin = 0;
Error.RGBMax = 255;
Error.MinBluePercent = 35;
Debug.Status = 1;
#pragma endregion

#pragma region //ASSIGNS COMMAND LINE INPUTS TO APPROPRIATE VARIABLES
//ERROR_TEST: CHECKS IF THE NUMBER OF ARGUMENTS RECEIVED IS EQUAL TO THE NUMBER OF ARGUMENTS EXPECTED
if(argc != Error.NumberOfInputs + 1){
    fprintf(stderr,"Too many or not enough inputs.");
    return 1;
}

//ERROR_TEST: CHECKS THAT ALL VALUES ARE NUMBERS
for(int j=1; j <= Error.NumberOfInputs; j++){
	int Res;
	Res = IsNumber(argv[j]);
	if (Res != 1){
		fprintf(stderr,"Inputs must be numbers.");
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
		fprintf(stderr,"The ball diameter/size is not in the appropriate range.");
		return 1;
	}

    //COMPUTE TABLE HEIGHT AND WIDTH
    Table.Width = Table.RightBorder - Table.LeftBorder;
    Table.Height = Table.TopBorder - Table.BottomBorder;

	//ERROR_TEST:CHECKS THAT THE TABLE Width AND HEIGHT IS IN THE APPROPRIATE RANGE
	if (Table.Width < Error.TableWidthMin || Table.Width >Error.TableWidthMax || Table.Height < Error.TableHeightMin || Table.Height > Error.TableHeightMax){
		fprintf(stderr,"The table dimensions are not in the appropriate range.");
		return 1;
    }
	//ERROR_TEST:CHECKS THAT RGB VALUES ARE IN RGB RANGE: 0-255
	for(int j = 5; j<=28; j++){
		if(atoi(argv[j])< Error.RGBMin || atoi(argv[j])> Error.RGBMax){
			fprintf(stderr,"Input 5-28 must be RGB values.");
		}
	}
	#pragma endregion

#pragma region //OPEN pixmap.bin AND STORES IT IN MyPM
    //OPEN pixmap.bin FOR READING
	FILE *file = fopen("Pixmap217.bin", "rb");

    //ERROR_TEST: CHECK IF FILE WAS OPENED
	if (file == NULL) {
		fprintf(stderr,"Error opening pixmap.bin");
		return 1;
	}

	//FIND THE SIZE OF THE FILE
	fseek(file, 0L, SEEK_END);
	long int file_size = ftell(file);
	fseek(file, 0L, SEEK_SET);

    //COMPUTE THE NUMBER OF INTEGERS IN pixmap.bin
    size_t num_integers = file_size / sizeof(unsigned int);

	//ALLOCATE MEMORY FOR MyPM
	unsigned int* MyPM = (unsigned int*)malloc(file_size);

    //ERROR_TEST: CHECK IF MEMORY WAS ALLOCATED FOR MyPM
	if (MyPM == NULL) {
		fprintf(stderr,"Error allocating memory for MyPM.");
		fclose(file);
		return 1;
	}

    //READ THE CONTENTS OF pixmap.bin INTO MyPM
	size_t elements_read = fread(MyPM, sizeof(unsigned int), num_integers , file);

    //ERROR_TEST: MAKES SURE THAT THE NUMBER OF ELEMENTS READ IS EQUAL TO THE NUMBER OF ELEMENTS COMPUTED
	if (elements_read != num_integers) {
		if (ferror(file)) {
			fprintf(stderr,"Error reading file");
		}
		else {
			fprintf(stderr,"Unexpected end of file");
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

    //EXTRACT Width AND HEIGHT FROM MyPM
	Image.Width = MyPM[0];
	Image.Height = MyPM[1];
	Image.NumberOfPixels = Image.Width * Image.Height;

	//ERROR_TEST:CHECKS THAT THE IMAGE Width AND HEIGHT IS IN THE APPROPRIATE RANGE
	if (Image.Height < Error.ImageHeightMin || Image.Height >Error.ImageHeightMax || Image.Width < Error.ImageWidthMin || Image.Width > Error.ImageWidthMax){
		fprintf(stderr,"The image dimensions are not in the appropriate range.");
		return 1;
    }

    //ERROR_TEST: CHECKS IF NUMBER OF PIXELS IN pixmap.bin IS EQUAL TO THE Width TIMES THE HEIGHT GIVEN IN pixmap.bin
    if(Image.Width * Image.Height > num_integers - 2){
        fprintf(stderr,"Not enough pixels");
        return 1;
    }
    if(Image.Width * Image.Height < num_integers - 2){
        fprintf(stderr,"Too many pixels");
    }

    //COMPUTE FIRST AND LAST PIXEL OF TABLE
    Table.FirstPixel = Table.BottomBorder * Image.Width + Table.LeftBorder;
    Table.LastPixel = Table.TopBorder *Image.Width + Table.RightBorder - Table.BallSize;

    //INITIALIZE DEFAULT VALUES FOR THE BALLS' SCORE AND COORDINATES
	RedBall.IdentificationNumber = 2;
    RedBall.Score = 0;
    RedBall.X_Coordinate = 0;
    RedBall.Y_coordinate = 0;
	YellowBall.IdentificationNumber = 3;
    YellowBall.Score = 0;
    YellowBall.X_Coordinate = 0;
    YellowBall.Y_coordinate = 0;
	WhiteBall.IdentificationNumber = 5;
    WhiteBall.Score = 0;
    WhiteBall.X_Coordinate = 0;
    WhiteBall.Y_coordinate = 0;

	//INITIALISE DEFAULT DEBUG VALUES
	Debug.BlueCount = 0;
	Debug.RedCount = 0;
	Debug.WhiteCount = 0;
	Debug.YellowCount = 0;
	Debug.ScanCount = 0;
#pragma endregion

#pragma region //FUNCTION CALLING
	IsColor(MyPM);

	//ERROR_TEST: CHECKS THAT THE TABLE AREA OF THE IMAGE HAS AT LEAST Error.MinBluePercent NUMBER 
	Table.BluePercent = (Debug.BlueCount * 100) / Image.NumberOfPixels;
	if (Table.BluePercent < Error.MinBluePercent){
		fprintf(stderr,"Wrong image inserted.");
		return 1;
	}

    IsBall(MyPM);
#pragma endregion

#pragma region //CREATE POX.TXT FILE
    //OPENS pos.txt IN WRITE MODE
	FILE *f_out = fopen("pos.txt", "w");

	//ERROR_TEST: CHECKS IF pos.txt WAS OPENED
	if (f_out == NULL)
	{
        fprintf(stderr,"Error opening pos.txt");
		return 1;
	}

    //CHECKS IF ALL BALLS WERE FOUND
    if(RedBall.Score < Error.BallMinScore){
        RedBall.Score = 0;
        RedBall.X_Coordinate = -1;
        RedBall.Y_coordinate = -1;
        fprintf(stderr,"The red ball was not found.");
    };
    if(YellowBall.Score < Error.BallMinScore){
        YellowBall.Score = 0;
        YellowBall.X_Coordinate = -1;
        YellowBall.Y_coordinate = -1;
        fprintf(stderr,"The yellow ball was not found.");
    };
    if(WhiteBall.Score < Error.BallMinScore){
        WhiteBall.Score = 0;
        WhiteBall.X_Coordinate = -1;
        WhiteBall.Y_coordinate = -1;
        fprintf(stderr,"The white ball was not found.");
    };

    //WRITES COORDINATES AND SCORE TO pos.txt
    fprintf(f_out, "Red: %d, %d, %d\n", RedBall.X_Coordinate, RedBall.Y_coordinate, RedBall.Score);
	fprintf(f_out,"Yellow: %d, %d, %d\n", YellowBall.X_Coordinate, YellowBall.Y_coordinate, YellowBall.Score);
	fprintf(f_out,"White: %d, %d, %d", WhiteBall.X_Coordinate, WhiteBall.Y_coordinate, WhiteBall.Score);
#pragma endregion

#pragma region //FREE THE MEMORY ALLOCATED TO MyPM
	free(MyPM);
#pragma endregion

#pragma region //DEBUG
	Debug.Timer = clock() - Debug.Timer; //STOP TIMER
	Debug.TimeTaken = ((double)Debug.Timer)/CLOCKS_PER_SEC; //CONVERT TIMER TO SECONDS
	Debug.NonOptimisedScanCount = (Table.BallSize * Table.BallSize)*((Table.Width - (2 * Table.BallSize)) * (Table.Height - (2 * Table.BallSize))) + (2 * Table.Width * 13) + (2 * Table.Height * 13) - (8 * 13);
	if(Debug.Status == 1){ //CHECK IF DEBUGGER MODE ACTIVATED
		//OPENS Debug.txt IN WRITE MODE
		FILE *DebugFile = fopen("Debug.txt", "w");

		//ERROR_TEST: CHECKS IF Debug.txt WAS OPENED
		if (DebugFile == NULL)
		{
			fprintf(stderr,"Error Opening Debug.txt");
			return 1;
		}
		time_t tr;
		time(&tr);
		fprintf(DebugFile,"%s\n", ctime(&tr)); //Prints the current date and time
		fprintf(DebugFile,"Main took: %lf seconds to execute \n\n", Debug.TimeTaken);
		fprintf(DebugFile,"Skip Type 1 Count: %d \n", Debug.SkipCountType1);
		fprintf(DebugFile,"Skip Type 2 Count: %d \n\n", Debug.SkipCountType2);
		fprintf(DebugFile,"Scan Count: %d \n", Debug.ScanCount);
		fprintf(DebugFile,"Non Optimised Scan Count: %d \n\n", Debug.NonOptimisedScanCount);
		fprintf(DebugFile,"Blue Percent: %d %% \n\n", Table.BluePercent);
		fprintf(DebugFile,"Blue Count: %d \n", Debug.BlueCount);
		fprintf(DebugFile,"Red Count: %d \n", Debug.RedCount);
		fprintf(DebugFile,"Yellow Count: %d \n", Debug.YellowCount);
		fprintf(DebugFile,"White Count: %d \n", Debug.WhiteCount);
		fprintf(DebugFile,"Neither Count: %d", Debug.NeitherCount);
	}
#pragma endregion

	return 0;
}
