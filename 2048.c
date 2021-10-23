#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#define SIZE 4
size_t i , j;
int score = 0;

void Rand( unsigned int line[][ SIZE ] ); // function for adding number two or four
void Print( unsigned int line[][ SIZE ]); // function for printig table
void Right ( unsigned int line[][ SIZE ] , unsigned int line_Check[][ SIZE ]  ); // actions for right arrow key
void Left ( unsigned int line[][ SIZE ] , unsigned int line_Check[][ SIZE ]  ); // actions for left arrow key
void Up( unsigned int line[][ SIZE ] , unsigned int line_Check[][ SIZE ]  ); // actions for up arrow key
void Down( unsigned int line[][ SIZE ] , unsigned int line_Check[][ SIZE ]  ); // actions for down arrow key
int WinnerCheck ( unsigned int line[][ SIZE ] ); // function for checking wining mode
int LoserCheck ( unsigned int line[][ SIZE ] ); // function for checking losing mode
void SetColorAndBackground(int ForgC, int BackC); //function declaration



int main(void)
{
	unsigned int line[ SIZE ][ SIZE ] = {};
	unsigned int line_Check[ SIZE ][ SIZE ] = {};
	char ch, check, Answer, Answer2;
	int Rand_Check = 0;
	int score_cp, size, highscore;

	FILE *fp = fopen( "Save.txt", "r" );
	FILE *SaveScore = fopen( "SaveScore.txt" , "r" );
	FILE *HighScore ;


	/*if(!fp)
	{
		printf("file is not opened");
		return 0;
	}*/
	if ( !(feof(fp)) ){
		printf("%s" , "Do you want to continue previous game?(Y/N): " );
		Answer = getch();
		if ( Answer == 'y' ){
			for ( int x = 0 ; x < 4 ; x++ ){
				for ( int y = 0 ; y < 4 ; y++ ){
					fscanf( fp, "%d-", &line[ x ][ y ] );
				} // end for
			} // end for
			fclose(fp);
			fscanf( SaveScore, "%d", &score );
			fclose(SaveScore);
			FILE *HighScore = fopen( "HighScore.txt" , "r" );
			fscanf( HighScore, "%d", &highscore );
			fclose( HighScore );
			Print(line);
			printf( "Highscore: %d", highscore );
		} // end if
		else if ( Answer == 'n' ) {
			Rand(line);	
			Rand(line);
			Print(line);
			FILE *HighScore = fopen( "HighScore.txt" , "r" );
			fscanf( HighScore, "%d", &highscore );
			fclose( HighScore );
			printf( "Highscore: %d", highscore );
		} // end else

	} // end if
	
	while ( 1 ){ // loop for doing game structure

		ch = getch();
		
		if ( ch == 24 )
		{
			while( 1 ){
				printf ( "\n%s" , "Are you sure you want to leave the game?(Y/N): " );
				Answer2 = getch();

				if ( Answer2 == 'y' ){
					//int x = 0, y = 0;
					fp = fopen( "Save.txt", "w" );
					SaveScore = fopen( "SaveScore.txt", "w" );
					for ( int x = 0 ; x < 4 ; x++){
						for ( int y = 0 ; y < 4 ; y++){
							fprintf( fp, "%d-", line[ x ][ y ] );
						} // end for
					} // end for
					fclose(fp);
					fprintf( SaveScore, "%d", score );
					fclose(SaveScore);
					if ( score > highscore ){
						HighScore = fopen( "HighScore.txt", "w" );
						fprintf( HighScore, "%d", score);
						fclose(HighScore);
					} // end if
					return 0;
				} // end if
				else if ( Answer2 == 'n' ){
					COORD c = { 0 , 0 };  
					SetConsoleCursorPosition(  GetStdHandle(STD_OUTPUT_HANDLE) , c);
					printf("\033[2J"); 
					Print(line);
					break;
				} // end else if
				else
					puts("");
			} // end while
		} // end if
		
		else if ( ch == 26 ){
			
			score = score_cp;
			
			Print ( line_Check );
			//printf("\n%d\n" , score_cp);
			for ( i = 0 ; i <= 3 ; i++ ){ // for repetition to copy table in another array
				for ( j = 0 ; j <= 3 ; j++ ){
					line[ i ][ j ] = line_Check[ i ][ j ];
				} // end second for
			} // end first for

		} // end if
		
		else if ( ch = -32 ){
			
			score_cp = score;
			ch = getch();

			switch ( ch ){ // switch for analysing movment

			case 77 : // actions for right arrow key
				Right(line , line_Check);
				for ( i = 0 ; i <= 3 ; i++ ){
					for ( j = 0 ; j <= 3 ; j++ ){
						if ( line_Check[ i ][ j ] != line[ i ][ j ] ){
							Rand_Check = 1;
							break;
						} // end if
					} // end second for
				} // end first for

				if ( Rand_Check == 1 ){
					Rand(line);
					Rand_Check = 0;
				} // end if
				Print(line);
				break;

			case 80:
				Down( line , line_Check );
				for ( i = 0 ; i <= 3 ; i++ ){
					for ( j = 0 ; j <= 3 ; j++ ){
						if ( line_Check[ i ][ j ] != line[ i ][ j ] ){
							Rand_Check = 1;
							break;
						} // end if
					} // end second for
				} // end first for

				if ( Rand_Check == 1 ){
					Rand(line);
					Rand_Check = 0;
				} // end if
				Print(line);
				break;

			case 75 :
				Left(line , line_Check );
					for ( i = 0 ; i <= 3 ; i++ ){
					for ( j = 0 ; j <= 3 ; j++ ){
						if ( line_Check[ i ][ j ] != line[ i ][ j ] ){
							Rand_Check = 1;
							break;
						} // end if
					} // end second for
				} // end first for

				if ( Rand_Check == 1 ){
					Rand(line);
					Rand_Check = 0;
				} // end if
				Print(line);
				break;

			case 72:
				Up( line , line_Check );
					for ( i = 0 ; i <= 3 ; i++ ){
					for ( j = 0 ; j <= 3 ; j++ ){
						if ( line_Check[ i ][ j ] != line[ i ][ j ] ){
							Rand_Check = 1;
							break;
						} // end if
					} // end second for
				} // end first for

				if ( Rand_Check == 1 ){
					Rand(line);
					Rand_Check = 0;
				} // end if
				Print(line);
				break;
			} // end switch
			
		} // end else if

		if( score >= highscore){
			HighScore = fopen( "HighScore.txt", "w" );
			fprintf( HighScore, "%d", score);
			fclose(HighScore);
			highscore = score;
		} // end if

		printf( "Highscore: %d", highscore );
		
		if ( WinnerCheck(line) == 1 ){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10 );
			puts ( " You Won ! " );
			break;
		} // end if
		else if ( LoserCheck(line) == 24 ){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			puts ( " Game Over ! " );
			break;
		}

	} // end while
} // end main function

//***********************************************

void SetColorAndBackground(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}

//***********************************************

void Rand(unsigned int line[][ SIZE ] ) // function for adding number two or four
{
	int random;

	srand( time(NULL) );// seed random

	while( 1 ){
		i = rand() % 4;
		j = rand() % 4;
		if ( line[ i ][ j ] == 0 ){ 
			random = rand() % 3;
			if ( random == 0 || random == 1){
				line[ i ][ j ] = 2;
				break;
			} // end if
			else {
				line[ i ][ j ] = 4;
				break;
			} // end else
		} // end if
	} // end while
} // end Rand function

//***********************************************

void Print( unsigned int line[][ SIZE ]) // function for printig table
{
	COORD c = { 0 , 0 };  
	SetConsoleCursorPosition(  GetStdHandle(STD_OUTPUT_HANDLE) , c);
	printf("\033[2J"); 

	for ( i = 0 ; i <= 3 ; i++ ){ // loop through rows
		for ( j = 0 ; j <= 3 ; j++ ){ // loop through cloumns
			SetColorAndBackground(15,0);
			//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			if ( line[ i ][ j ] == 0 || line[ i ][ j ] == 2 ){
				SetColorAndBackground(0,15);
				//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				printf ( " %-3u" , line[ i ][ j ] );
				SetColorAndBackground(15,0);
				printf ( " " );
			}
			else if ( line[ i ][ j ] == 4 ){
				//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				SetColorAndBackground(0,7);
				printf ( " %-3u" , line[ i ][ j ] );
				SetColorAndBackground(15,0);
				printf (" ");
			} // end esle if
			else if ( line[ i ][ j ] == 8 ){
				//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
				SetColorAndBackground(0,8);
				printf ( " %-3u" , line[ i ][ j ] );
				SetColorAndBackground(15,0);
				printf (" ");
			} // end else if
			else if ( line[ i ][ j ] == 16 ){
				//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
				SetColorAndBackground(0,2);
				printf ( " %-3u" , line[ i ][ j ] );
				SetColorAndBackground(15,0);
				printf(" ");
			} // end else if
			else if ( line[ i ][ j ] == 32 ){
				//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10 );
				SetColorAndBackground(0,10);
				printf ( " %-3u" , line[ i ][ j ] );
				SetColorAndBackground(15,0);
				printf(" ");
			} // end else if
			else if ( line[ i ][ j ] == 64 ){
				//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3 );
				SetColorAndBackground(0,3);
				printf ( " %-3u" , line[ i ][ j ] );
				SetColorAndBackground(15,0);
				printf(" ");
			} // end else if
			else if ( line[ i ][ j ] == 128 ){
				//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9 );
				SetColorAndBackground(0,9);
				printf ( " %-3u" , line[ i ][ j ] );
				SetColorAndBackground(15,0);
				printf(" ");
			} // end else if
			else if ( line[ i ][ j ] == 256 ){
				//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5 );
				SetColorAndBackground(0,5);
				printf ( " %-3u" , line[ i ][ j ] );
				SetColorAndBackground(15,0);
				printf(" ");
			} // end esle if
			else if ( line[ i ][ j ] == 512 ){
				//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6 );
				SetColorAndBackground(0,6);
				printf ( " %-3u" , line[ i ][ j ] );
				SetColorAndBackground(15,0);
				printf(" ");
			} // end else if
			else if ( line[ i ][ j ] == 1024 ){
				//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14 );
				SetColorAndBackground(0,14);
				printf ( "%-3u" , line[ i ][ j ] );
				SetColorAndBackground(15,0);
				printf(" ");
			} // end else if
			else if ( line[ i ][ j ] == 2048 ){
				//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				SetColorAndBackground(0,4);
				printf ( "%-3u" , line[ i ][ j ] );
				printf("");
			} // end else if
		} // end for
		puts ( " " );
		puts ( " " );
	} // end for
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf ( "\nScore: %d\n" , score );
	puts ( " " );
} // end Print function

//************************************************

void Right ( unsigned int line[][ SIZE ] , unsigned int line_Check[][ SIZE ]  ) // actions for right arrow key
{
	int check = 1; // Variable for checking next array element
	int check_2 = 0; // Variable for checking array element
	int sum_check = 0 , sum_check2 = 0;;

	for ( i = 0 ; i <= 3 ; i++ ){ // for repetition to copy table in another array
		for ( j = 0 ; j <= 3 ; j++ ){
			line_Check[ i ][ j ] = line[ i ][ j ];
		} // end second for
	} // end first for

	for (  int m = 0 ; m <= 3 ; m++ ){ // loop through rows
					for (   int  n = 2 ; n >= 0 ; n-- ){ // loop through clomuns
						if ( line [ m ][ n ] != 0 ){
						while ( 1 ){
						
							  if  ( line [ m ][ n + check ] == 0 ){
								line [ m ][ n + check ] = line [ m ][ n + check_2 ];
								line [ m ][ n + check_2 ] = 0;
								check++;
								check_2++;
							} // end else if
							else if ( line [ m ][ n + check_2 ] == line [ m ][ n + check ] ){
								if ( sum_check == 0 && sum_check2 == 0 ){
								line [ m ][ n + check ] += line [ m ][ n+ check_2 ];
								line [ m ][ n + check_2 ] = 0;
								score += line [ m ][ n + check ];
								check = 1;
								check_2 = 0;
								sum_check = 1;
								sum_check2 = 1;
								//break;
								} // end if
								else if ( sum_check2 != 0) {
									sum_check2 = 0;
									break;
								} // end else
								else
									break;
							} // end else if
							if ( ( n + check_2 ) == 3 ){
								check = 1;
								check_2 = 0;
								break;
							} // end if
							else if ( line[ m ][ n + check ] != 0 && line [ m ][ n + check_2 ] != line [ m ][ n + check ]){
										check = 1;
										check_2 = 0;
										break;
									} // end else if
						} // end while
						} // end if
						sum_check = 0;
					} // end for
					sum_check2 = 0;
				} // end for
} // end Right function

//************************************************

void Left ( unsigned int line[][ SIZE ] , unsigned int line_Check[][ SIZE ]  ) // actions for left arrow key
{
	int check = -1 , check_2 = 0 , sum_check = 0 , sum_check2 = 0;

	for ( i = 0 ; i <= 3 ; i++ ){ // for repetition to copy table in another array
		for ( j = 0 ; j <= 3 ; j++ ){
			line_Check[ i ][ j ] = line[ i ][ j ];
		} // end second for
	} // end first for

	for (  int m = 0 ; m <= 3 ; m++ ){ // loop through rows
					for (   int  n = 1 ; n <= 3 ; n++ ){ // loop through clomuns
						if ( line [ m ][ n ] != 0 ){
						while ( 1 ){
							
							    if ( line [ m ][ n + check ] == 0 ){
								line [ m ][ n + check ] = line [ m ][ n + check_2 ];
								line [ m ][ n + check_2 ] = 0;
								check--;
								check_2--;
							} // end else if
							else if ( line [ m ][ n + check_2 ] == line [ m ][ n + check ] ){
								if ( sum_check == 0 && sum_check2 == 0){
								line [ m ][ n + check ] += line [ m ][ n+ check_2 ];
								line [ m ][ n + check_2 ] = 0;
								score += line [ m ][ n + check ];
								check = -1;
								check_2 = 0;
								sum_check = 1;
								sum_check2 = 1;
								//break;
								} // end if
								else if ( sum_check2 != 0) {
									sum_check2 = 0;
									break;
								} // end else if
								else
									break;
							} // end else if
							if ( ( n + check_2 ) == 0 ){
								check = -1;
								check_2 = 0;
								break;
							} // end if
							else if ( line[ m ][ n + check ] != 0 && line [ m ][ n + check_2 ] != line [ m ][ n + check ]){
										check = -1;
										check_2 = 0;
										break;
									} // end else if
						} // end while
						} // end if
						sum_check = 0;
					} // end for
					sum_check2 = 0;
				} // end for
} // end Left function

//************************************************
void Down( unsigned int line[][ SIZE ] , unsigned int line_Check[][ SIZE ]  ) // actions for down arrow key
{
	
	int check = 1 , check_2 = 0 , sum_check = 0 , sum_check2 = 0;

	for ( i = 0 ; i <= 3 ; i++ ){ // for repetition to copy table in another array
		for ( j = 0 ; j <= 3 ; j++ ){
			line_Check[ i ][ j ] = line[ i ][ j ];
		} // end second for
	} // end first for

	for (  int n = 0 ; n <= 3 ; n++ ){ // loop through clomuns
					for (   int  m = 2 ; m >= 0 ; m-- ){ // loop through rows
						if ( line [ m ][ n ] != 0 ){
						while ( 1 ){
							
							    if ( line [ m + check ][ n ] == 0 ){
									line [ m + check ][ n ] = line [ m + check_2 ][ n ];
									line [ m + check_2 ][ n ] = 0;
									check++;
									check_2++;
								} // end if
							else if ( line [ m + check_2 ][ n ] == line [ m + check ][ n ] ){
								if ( sum_check == 0 && sum_check2 == 0 ){
								line [ m + check ][ n ] += line [ m + check_2 ][ n ];
								line [ m + check_2 ][ n ] = 0;
								score += line [ m + check ][ n ];
								check = 1;
								check_2 = 0;
								sum_check = 1;
								sum_check2 = 1;
								//break;
								} // end if
								else if ( sum_check2 != 0 ) {
									sum_check2 = 0;
									break;
								} // end else
								else
									break;
							} // end else if
							if ( ( m + check_2 ) == 3 ){
								check = 1;
								check_2 = 0;
								break;
							} // end if
							else if ( line[ m + check ][ n ] != 0 && line [ m + check_2 ][ n ] != line [ m + check ][ n ]){
										check = 1;
										check_2 = 0;
										break;
									} // end else if
						} // end while
						} // end if
						sum_check = 0;
					} // end for
					sum_check2 = 0;
				} // end for
} // end Down function
//************************************************

void Up( unsigned int line[][ SIZE ] , unsigned int line_Check[][ SIZE ]  ) // actions for up arrow key
{
	
	int check = -1 , check_2 = 0 , sum_check = 0 , sum_check2 = 0;

	for ( i = 0 ; i <= 3 ; i++ ){ // for repetition to copy table in another array
		for ( j = 0 ; j <= 3 ; j++ ){
			line_Check[ i ][ j ] = line[ i ][ j ];
		} // end second for
	} // end first for

	for (  int n = 0 ; n <= 3 ; n++ ){ // loop through clomuns
					for (   int  m = 1 ; m <= 3 ; m++ ){ // loop through rows
						if ( line [ m ][ n ] != 0 ){
						while ( 1 ){
						
							 if ( line [ m + check ][ n ] == 0 ){
								line [ m + check ][ n ] = line [ m + check_2 ][ n ];
								line [ m + check_2 ][ n ] = 0;
								check--;
								check_2--;
							} // end if
							else if ( line [ m + check_2 ][ n ] == line [ m + check ][ n ] ){
								if ( sum_check == 0 && sum_check2 == 0){
								line [ m + check ][ n ] += line [ m + check_2 ][ n ];
								line [ m + check_2 ][ n ] = 0;
								score += line [ m + check ][ n ];
								check = -1;
								check_2 = 0;
								sum_check = 1;
								sum_check2 = 1;
								//break;
								} // end if
								else if ( sum_check2 != 0 ) {
									sum_check2 = 0;
									break;
								} // end else
								else 
									break;
							} // end else if
							if ( ( m + check_2 ) == 0 ){
								check = -1;
								check_2 = 0;
								break;
							} // end if
							else if ( line[ m + check ][ n ] != 0 && line [ m + check_2 ][ n ] != line [ m + check ][ n ]){
										check = -1;
										check_2 = 0;
										break;
									} // end else if
						} // end while
						} // end if
						sum_check = 0;
					} // end for
					sum_check2 = 0;
				} // end for
} // end Up function
//************************************************

int LoserCheck ( unsigned int line[][ SIZE ] ) // function for checking losing mode
{
	int counter = 0;

	for ( i = 0 ; i <= 3 ; i++ ){
		for ( j = 0 ; j <= 3 ; j++ ){

			if ( i == 3 ){
				if ( j != 3 ){
					if ( line[ i ][ j ] != line[ i ][ j + 1 ]  && line[ i ][ j ] != 0 )
					counter++;
				} // end if
			} // end if
			else if ( j == 3 ){

				if ( line[ i ][ j ] != line[ i + 1 ][ j ] && line[ i ][ j ] != 0  )
				counter++;

			} // end else if
			else{
				if ( line[ i ][ j ] != line[ i ][ j + 1 ] && line[ i ][ j ] != 0 )
					counter++;
				if ( line[ i ][ j ] != line[ i + 1 ][ j ] && line[ i ][ j ] != 0 )
					counter++;
			} // end else
		} // end second for
	} // end first for
	
	return counter;
} // end LoserCheck function

//************************************************

int WinnerCheck ( unsigned int line[][ SIZE ] ) // function for checking wining mode
{
	int check = 0;

	for ( i = 0 ; i <= 3 ; i++ ){
		for ( j = 0 ; j <= 3 ; j++ ){
			if ( line[ i ][ j ] == 2048 ){
				check = 1;
				break;
			} // end if
		} // end second for
	} // end first for

	return check;
} // end WinnerCheck function

//************************************************

