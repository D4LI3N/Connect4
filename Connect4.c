#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

/*################################################################################*\
  #   ASSIGNMENT:  Final Project - Connect 4 Game (two players game)             #
  #    PROFESSOR:  X                                                             #
  #     DUE DATE:  29.01.2020                                                    #
  #                                                                              # 
  #       AUTHOR:  Daniel Petrovich                                              #
  #        EMAIL:  danielthe@cyberdude.com                                       #
  #         DATE:  26.01.2020                                                    #
  # INDEX NUMBER:  2019/230364                                                   #
  #                                                                              #
  #  DESCRIPTION:  This is a game for two players, to win the game, one player   #
  #                will have to position his symbol('X' or 'O') in the           #
  #                horizontal,vertical or diagonal line of 4 symbols.            #
  #                If the board is fully loaded with symbols,                    #
  # 			   nobody has won and the game will show the main menu,          #
  # 			   from which the player can start a new game, load a saved game #
  # 			   or quit the game. (the game has more than one menu)           #
  #                                                                              #
  #   RECOMENDED                                                                 #
  #     COMPILER:  TDM-GCC 4.9.2 (C99-standard)                                  #
\*################################################################################*/


/* ++++++++++ PREPROCESSOR DIRECTIVES ++++++++++ */
#define P1 'X'
#define P2 'O'
#define MA 'Y'
#define EA '_'

#define ROWS 6
#define COLS 7
#define ONED 43 
#define WIN  4 
#define NAMS 50

#define SF "saved_games.csv"
#define DELI "!$!"
/* ---------- PREPROCESSOR DIRECTIVES ---------- */

/* ++++++++++ BANNERS AND SCREENS ++++++++++ */
const char mainBanner[] = "\n\
   			                        \033[91m     Final Project \033[0m    \n\
   \033[91mStudent: Daniel Petrovich				                                  Professor: X\033[0m \n\
\n\
   			            \033[94m   ______\033[0m       \033[34m2 Player Game\033[0m      \033[94m  __     __ __     \n\
   			              / ____/___  ____  ____  ___  _____/ /_   / // /     \n\
   			             / /   / __ \\/ __ \\/ __ \\/ _ \\/ ___/ __/  / // /_ \n\
   			            / /___/ /_/ / / / / / / /  __/ /__/ /_   /__  __/     \n\
   		        	    \\____/\\____/_/ /_/_/ /_/\\___/\\___/\\__/     /_/   \033[0m";

char menuP[] = "\n\
\n\
\n\
\n\
					       1.) Play a new game\n\
					       2.) Load already saved game\n\
					       3.) Exit the game\n\
\n\
\n\
\n\
						          [ ]\b\b";

char menuL[] = "\n\
\n\
\n\
\n\
					       1.) Play a new game\n\
					       2.) Go back to main menu\n\
					       3.) Exit the game\n\
\n\
\n\
\n\
						          [ ]\b\b";
						          
char menuT[] = "\n\
\n\
\n\
\n\
				       1.) List all saved games\n\
				       2.) List all saved games for a particular player\n\
				       3.) Show the board of one of the saved games\n\
				       4.) Load a game\n\
				       5.) Return to main menu \n\
\n\
\n\
\n\
						          [ ]\b\b";
						          
char screenX[] = "\n\
\n\
\n\
\n\
\n\
					       Player X Name: ";
char screenO[] = "\n\
\n\
\n\
\n\
\n\
					       Player O Name: ";

char screenU[] = "\n\
\n\
\n\
\n\
\n\
					       Player Name: ";

char screenID[] = "\n\
\n\
\n\
\n\
\n\
					    	       Game ID: ";
/* ---------- BANNERS AND SCREENS ---------- */

/* ++++++++++ FUNCTIONS ++++++++++ */
int hor_ok(int i){
	/*
	* Function:  Checks if the given column is valid
	*-----------------------------------------------
	* Arguments: -i = Column
	* Returns:   int
 	*/
	return (i<COLS && i>=0) ? 1 : 0;
}

char check_horizontally(char table[ROWS][COLS]){
	/*
	* Function:  Checks for 4-line horizontal matches
	*------------------------------------------------
	* Arguments: -table = Game table
	* Returns:   char
 	*/
	for(int a = 0; a < ROWS;a++){
		int countX = 0, countO = 0;
		for(int b = 0; b < COLS;b++){
			if(table[a][b] == P1){
				++countX;
				countO = 0;
			}
			if(table[a][b] == P2){
				++countO;
				countX = 0;
			}
			if(table[a][b] == EA){
				countX = 0;
				countO = 0;
			}
			if(countX==WIN){
				for(int i = 0;i<WIN;i++){
					table[a][b-i] = MA;
				}
				return P1;
			}
			if(countO==WIN){
				for(int i = 0;i<WIN;i++){
					table[a][b-i] = MA;
				}
				return P2;
			}
		}
	}
	return EA;
}

char check_vertically(char table[ROWS][COLS]){
	/*
	* Function:  Checks for 4-line vertical matches
	*----------------------------------------------
	* Arguments: -table = Game table
	* Returns:   char
 	*/
	for(int b = 0; b < COLS;b++){
		int countX = 0, countO = 0;
		for(int a = 0; a < ROWS;a++){
			if(table[a][b] == P1){
				++countX;
				countO = 0;
			}
			if(table[a][b] == P2){
				++countO;
				countX = 0;
			}
			if(table[a][b] == EA){
				countX = 0;
				countO = 0;
			}
			if(countX==WIN){
				for(int i = 0;i<WIN;i++){
					table[a-i][b] = MA;
				}
				return P1;
			}
			if(countO==WIN){
				for(int i = 0;i<WIN;i++){
					table[a-i][b] = MA;
				}
				return P2;
			}
		}
	}
	return EA;
}

char check_diagonally(char table[ROWS][COLS]){
	/*
	* Function:  Checks for 4-line diagonal matches
	*----------------------------------------------
	* Arguments: -table = Game table
	* Returns:   char
 	*/
	for(int a = 0; a < ROWS;a++){
		for(int b = 0; b < COLS;b++){
			if(table[a][b] == P1){
				int step = 1;
				while(hor_ok(b+step) && (step<WIN)){
					if(table[a+step][b+step] != P1){
						break;
					}
					++step;
					if(step==WIN){
						--step;
						for(;step>=0;step--){
							table[a+step][b+step] = MA;
						}
						return P1;
					}
				}
				step = 1;
				while(hor_ok(b-step) && (step<WIN)){
					if(table[a+step][b-step] != P1){
						break;
					}
					++step;
					if(step==WIN){
						--step;
						for(;step>=0;step--){
							table[a+step][b-step] = MA;
						}
						return P1;
					}
				}
			}
			if(table[a][b] == P2){
				int step = 1;
				while(hor_ok(b+step) && (step<WIN)){
					if(table[a+step][b+step] != P2){
						break;
					}
					++step;
					if(step==WIN){
						--step;
						for(;step>=0;step--){
							table[a+step][b+step] = MA;
						}
						return P2;
					}
				}
				step = 1;
				while(hor_ok(b-step) && (step<WIN)){
					if(table[a+step][b-step] != P2){
						break;
					}
					++step;
					if(step==WIN){
						--step;
						for(;step>=0;step--){
							table[a+step][b-step] = MA;
						}
						return P2;
					}
				}
			}
		}
	}
	return EA;
}

void pack_table(char *p,char table[ROWS][COLS]){
	/*
	* Function:  Transforms game table from 2D array to 1D
	*-----------------------------------------------------
	* Arguments: -p     = Variable to store 1D array
	*            -table = Game table (2D array)
	* Returns:   None
 	*/
	int c = 0;
	for(int a = 0; a < ROWS;a++){
		for(int b = 0; b < COLS;b++){
			p[c] = table[a][b];
			c++;
		}
	}
	p[c] = '\0';
}

void unpack_table(char *p,char table[ROWS][COLS]){
	/*
	* Function:  Transforms game table from 1D array to 2D
	*-----------------------------------------------------
	* Arguments: -p     = 1D array
	*            -table = Variable to store 2D array
	* Returns:   None
 	*/
	int c = 0;
	for(int a = 0; a < ROWS;a++){
		for(int b = 0; b < COLS;b++){
			table[a][b] = p[c];
			c++;
		}
	}
}

void change_table(char p,char table[ROWS][COLS]){
	/*
	* Function:  Fills up game table with single symbol
	*--------------------------------------------------
	* Arguments: -p     = Symbol
	*            -table = Game Table
	* Returns:   None
 	*/
	for(int a = 0; a < ROWS;a++){
		for(int b = 0; b < COLS;b++){
			table[a][b] = p;
		}
	}
}

int put(char what,int where,char table[ROWS][COLS]){
	/*
	* Function:  Puts players symbol to a right place in a game table
	*----------------------------------------------------------------
	* Arguments: -what  = Symbol
	*            -where = Column to put 'what'
	*            -table = Game Table
	* Returns:   int
 	*/
	int flag = 0;
	for(int a = ROWS; a >= 0;a--){
		if(table[a][where] == EA){
			table[a][where] = what;
			++flag;
			break;
		}
	}
	if(!flag){
		return 0;
	}else{
		return 1;
	}
}

char next_player(char table[ROWS][COLS]){
	/*
	* Function:  Decides who has the right to next move in the game
	*--------------------------------------------------------------
	* Arguments: -table = Game Table
	* Returns:   char
 	*/
	int x = 0, o = 0;
	for(int a = 0; a < ROWS;a++){
		for(int b = 0; b < COLS;b++){
			//printf("%c, ",p[c]);
			if(table[a][b]==P1){
				++x;
			}else if(table[a][b]==P2){
				++o;
			}
		}
	}
	if(x==o){
		return P1;
	}else if(x<o){
		return P1;
	}else if(x>o){
		return P2;
	}
}

void show_table(char *x,char *o,char table[ROWS][COLS]){
	/*
	* Function:  Prints the table and player names
	*---------------------------------------------
	* Arguments: -x     = P1 name
	*            -o     = P2 name
	*            -table = Game Table
	* Returns:   None
 	*/
	printf("\n\n			\033[92mX: %s\033[0m				 V S				\033[35mO: %s\033[0m\n", x,o);
	printf("\n					    | 1 | 2 | 3 | 4 | 5 | 6 | 7 |\n\n");
	int lr = 0;
	for(int a = 0; a < ROWS;a++){
		for(int b = 0; b < COLS;b++){
			if(b==0&&a==0){
				printf("					    | %s ",(table[a][b] == P1 ? "\033[92mX\033[0m" : (table[a][b] == P2 ? "\033[35mO\033[0m" : (table[a][b] == MA ? "\033[91mY\033[0m" : "_"))));//(aaa == 0 ? 0 : (aaa == 1 ? 1 : 2))
			}else if(a==(ROWS-1)){
				lr = 1;
				printf("\033[4m| %s \033[0m",(table[a][b] == P1 ? "\033[92mX\033[0m" : (table[a][b] == P2 ? "\033[35mO\033[0m" : (table[a][b] == MA ? "\033[91mY\033[0m" : "_"))));
			}else{
				printf("| %s ",(table[a][b] == P1 ? "\033[92mX\033[0m" : (table[a][b] == P2 ? "\033[35mO\033[0m" : (table[a][b] == MA ? "\033[91mY\033[0m" : "_"))));
			}
		}
		if(lr){
			printf("\033[4m|\033[0m\n					    ");
		}else{
			printf("|\n					    ");
		}
	}
}

int save_game(char *nameA,char *nameB, char *table){
	/*
	* Function:  Saves the current game to a file (each game is saved with unique random 4-digit ID)
	*-----------------------------------------------------------------------------------------------
	* Arguments: -nameA = P1 name
	*            -nameB = P2 name
	*            -table = Game Table
	* Returns:   int
 	*/
	char done[255],blank[2];
	srand(time(0));
	int rint;
	char rstr[4];

	char cbuff,rbuff[255];
	char *tok;
	FILE *fp;
	fp = fopen(SF, "a+");
	
	while(1==1){
		int duplicate = 0;
		rint = rand() % (9999 + 1 - 1000) + 1000;
		sprintf(rstr,"%d",rint);
		while(fgets(rbuff, 255, fp)) {
   		 	if(!strcmp(strtok(rbuff,DELI), rstr)){
				++duplicate;
			}
		}
		if(duplicate==0){
			break;
		}else{
			rewind(fp);
		}
	}
	strcpy(done,rstr);strcat(done,DELI);strcat(done,nameA);strcat(done,DELI);strcat(done,nameB);strcat(done,DELI);strcat(done,table);strcat(done,"\n");
	fputs(done, fp);
	fclose(fp);
	return rint;
}

int count_games(){
	/*
	* Function:  Counts and returns number of saved games directlly from a file
	*--------------------------------------------------------------------------
	* Arguments: None
	* Returns:   int
 	*/
	FILE *fp;
    if ((fp = fopen(SF, "r")))
    {
    	char cbuff;
    	int count_rows = 0;
		while((cbuff = getc(fp)) != EOF) {if(cbuff == '\n'){++count_rows;}}
        fclose(fp);
        return count_rows;
    }
    return 0;
}


void get_games(char data[][4][255],int m){
	/*
	* Function:  Retreves saved games
	*--------------------------------
	* Arguments: -data  = Variable to store saved games
	*            -m     = Counted games
	* Returns:   None
 	*/
	char cbuff,rbuff[255];
	FILE *fp;
	fp = fopen(SF, "r");
	
	int rows = 0;
	while(fgets(rbuff, 255, fp)){
		strtok(rbuff, "\n");
    	//printf("%s-\n", strtok(rbuff,DELI));
    	strcpy(data[rows][0], strtok(rbuff,DELI));
    	for(int i = 1;i<4;i++){
    		strcpy(data[rows][i], strtok(NULL,DELI));
    		//printf("%s-\n", strtok(NULL,DELI));
		}
		rows++;
	}
	fclose(fp);
}

char menuScreen(char text[]){
	/*
	* Function:  Shows the banner and the text, and lets user to choose the next operation
	*-------------------------------------------------------------------------------------
	* Arguments: -text = Some text
	* Returns:   char
 	*/
	char choice;
	system("cls");
	printf(mainBanner);
	printf(text);
	choice = getche();
	return choice;
}

void show(char *nameX, char *nameO, char table[ROWS][COLS]){
	/*
	* Function:  Shows the banner and a table
	*----------------------------------------
	* Arguments: -nameX = P1 name
	             -nameO = P2 name
	             -table = Game table
	* Returns:   None
 	*/
	char choice;
	system("cls");
	printf(mainBanner);
	show_table(nameX,nameO,table);
	printf("\n					          Player Turn: [%c]\n\n					>                                   <\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b",next_player(table));
}

void get_input(char text[],char *dest){
	/*
	* Function:  Scans for user input
	*--------------------------------
	* Arguments: -text = Text
	*            -dest = Destination variable
	* Returns:   None
 	*/
	system("cls");
	printf(mainBanner);
	printf(text);
	scanf("%s",dest);
}

int count_EA(char table[]){
	/*
	* Function:  Counts the empty areas(EA) in a game table
	*------------------------------------------------------
	* Arguments: -table = Game table
	* Returns:   int
 	*/
	int num = 0;
	for(int i=0;i<ONED;i++){
		if(table[i] == EA){
			num++;
		}
	}
	return num;
}

char check(char table[ROWS][COLS]){
	/*
	* Function:  Checks all three types of matches
	*---------------------------------------------
	* Arguments: -table = Game table
	* Returns:   char
 	*/
	char a,b,c;
	int not_full = 0;
	for(int a = 0; a < ROWS;a++){
		for(int b = 0; b < COLS;b++){
			if(table[a][b] == EA){
				++not_full;
			}
		}
	}
	if(not_full!=0){
		a = check_horizontally(table);
		b = check_vertically(table);
		c = check_diagonally(table);
		if(a!=EA){
			return a;
		}else if(b!=EA){
			return b;
		}else if(c!=EA){
			return c;
		}else{
			return EA;
		}
	}else{
		return MA;
	}
}
/* ---------- FUNCTIONS ---------- */

/* ++++++++++ MAIN ++++++++++ */
int main(){
	int exitFlag = 0, loadFlag = 1, gameFlag = 0, askFlag = 1, newgame=0, ID;
	char nameX[NAMS], nameO[NAMS], temp[255] = "", choice, choice2, choice3, choice4, ID2[5], winner;
	char table[ROWS][COLS], stable[ROWS][COLS];
	change_table(EA,table);
	
	while(!exitFlag){
		if(newgame){
			choice = '1';
		}else{
			choice = menuScreen(menuP);
		}
		switch(choice){
			case '1':
				get_input(screenX,nameX);
				get_input(screenO,nameO);
				change_table(EA,table);
				gameFlag = 1;
				break;
			case '2':
				while(loadFlag){
					choice2 = menuScreen(menuT);
					if(choice2=='1'){
						char data[count_games()][4][255];
						get_games(data, count_games());
						printf("\n				\033[95mID  	-	P1(X)	-	P2(O)	-	FREE_FIELDS\033[0m\n");
						for(int a = 0; a < count_games();a++){
							for(int b = 0; b < 4;b++){
								if(b==0){
									printf("				%s	-	", data[a][b]);
								}else if(b==3){
									printf("%d", count_EA(data[a][b]));
								}else{
									printf("%s	-	", data[a][b]);
								}
							}
							printf("\n");
						}
						getch();
						loadFlag = 1;
						gameFlag = 0;
					}else if(choice2=='2'){
						char data[count_games()][4][255];
						char name[255];
						int unknown = 1;
						get_input(screenU,name);
						get_games(data, count_games());
						printf("\n				\033[95mID  	-	P1(X)	-	P2(O)	-	FREE_FIELDS\033[0m\n");
						for(int a = 0; a < count_games();a++){
							if((!strcmp(data[a][1],name))|(!strcmp(data[a][2],name))){
								unknown = 0;
								for(int b = 0; b < 4;b++){
									if(b==0){
										printf("				%s	-	", data[a][b]);
									}else if(b==3){
										printf("%d", count_EA(data[a][b]));
									}else{
										printf("%s	-	", data[a][b]);
									}
								}
								printf("\n");
							}
						}
						if(unknown){printf("				Player name You entered does not exist! (0 games found)");}
						getch();
						loadFlag = 1;
						gameFlag = 0;
					}else if(choice2=='3'){
						char data[count_games()][4][255];
						char ID[255];
						int unknown = 1;
						get_input(screenID,ID);
						get_games(data, count_games());
						for(int a = 0; a < count_games();a++){
							if(!strcmp(data[a][0],ID)){
								unknown = 0;
								printf("\n						\033[92mX:%s\033[0m			\033[35mO:%s\033[0m\n", data[a][1],data[a][2]);
								printf("\n						| 1 | 2 | 3 | 4 | 5 | 6 | 7 |\n\n");
								unpack_table(data[a][3],stable);
								int lr = 0;
								for(int a = 0; a < ROWS;a++){
									for(int b = 0; b < COLS;b++){
										if(b==0&&a==0){
											printf("						| %s ",(stable[a][b] == P1 ? "\033[92mX\033[0m" : (stable[a][b] == P2 ? "\033[35mO\033[0m" : "_")));//(aaa == 0 ? 0 : (aaa == 1 ? 1 : 2))
										}else if(a==(ROWS-1)){
											lr = 1;
											printf("\033[4m| %s \033[0m",(stable[a][b] == P1 ? "\033[92mX\033[0m" : (stable[a][b] == P2 ? "\033[35mO\033[0m" : "_")));
										}else{
											printf("| %s ",(stable[a][b] == P1 ? "\033[92mX\033[0m" : (stable[a][b] == P2 ? "\033[35mO\033[0m" : "_")));
										}
									}
									if(lr){
										printf("\033[4m|\033[0m\n						");
									}else{
										printf("|\n						");
									}
								}
							}
						}
						if(unknown){printf("					    	      Unknown ID!");}
						getch();
						loadFlag = 1;
						gameFlag = 0;
					}else if(choice2=='4'){
						char data[count_games()][4][255];
						char ID[255];
						int unknown = 1;
						get_input(screenID,ID);
						get_games(data, count_games());
						for(int a = 0; a < count_games();a++){
							if(!strcmp(data[a][0],ID)){
								unknown = 0;
								strcpy(nameX,data[a][1]);
								strcpy(nameO,data[a][2]);
								unpack_table(data[a][3],table);
							}
						}
						if(unknown){
							printf("					    	      Unknown ID!");
							loadFlag = 1;
							gameFlag = 0;
							getch();
						}else{
							loadFlag = 0;
							gameFlag = 1;
						}
					}else if(choice2=='5'){
						loadFlag = 0;
						gameFlag = 0;
					}else{
						printf("\n						    Invalid option!");
						loadFlag = 1;
						gameFlag = 0;
					}
					//getch
				}
				loadFlag = 1;
				break;
			case '3':
				exitFlag++;
				loadFlag = 0;
				gameFlag = 0;
				break;

			default:
				printf("\n						    Invalid option!");
				loadFlag = 0;
				gameFlag = 0;
				break;
		}
		while(gameFlag){
			show(nameX,nameO,table);
			printf("%s",temp);
			choice3 = getch();
			strcpy(temp,"");
			if((choice3-'0')>=1 && (choice3-'0')<=COLS){
				int operation = put(next_player(table),((choice3-'0')-1),table);
				if(!operation){
					strcpy(temp,"Illegal move! (ROW FULL)");
				}
			}else if(choice3 == '0'){
				char packed[ONED], message[] = "Game saved with ID: ";
				pack_table(packed,table);
				ID = save_game(nameX,nameO,packed);
				sprintf(ID2, "%d", ID);
				strcat(message,ID2);
				strcpy(temp,message);
			}else{
				strcpy(temp,"Invalid input!");
			}
			winner = check(table);
			if(winner==MA){
				show(nameX,nameO,table);
				printf("GAME OVER! (no Winner)\n\n					    Press any key to continue!");
				getch();
				while(askFlag){
					choice4 = menuScreen(menuL);
					switch(choice4){
						case '1'://new game
							askFlag = 0;
							gameFlag = 0;
							loadFlag = 1;
							exitFlag = 0;
							newgame = 1;
							break;
						case '2'://1st menu
							askFlag = 0;
							gameFlag = 0;
							loadFlag = 1;
							exitFlag = 0;
							newgame = 0;
							break;
						case '3'://exit
							askFlag = 0;
							gameFlag = 0;
							loadFlag = 0;
							exitFlag = 1;
							break;
						default:
							printf("\n						    Invalid option!");
							break;
					}
				}
				askFlag = 1;
			}else if(winner==EA){;}else{
				show(nameX,nameO,table);
				printf("Player %c is the WINNER!\n\n					    Press any key to continue!",winner);
				getch();
				while(askFlag){
					choice4 = menuScreen(menuL);
					switch(choice4){
						case '1'://new game
							askFlag = 0;
							gameFlag = 0;
							loadFlag = 1;
							exitFlag = 0;
							newgame = 1;
							break;
						case '2'://1st menu
							askFlag = 0;
							gameFlag = 0;
							loadFlag = 1;
							exitFlag = 0;
							newgame = 0;
							break;
						case '3'://exit
							askFlag = 0;
							gameFlag = 0;
							loadFlag = 0;
							exitFlag = 1;
							break;
						default:
							printf("\n						    Invalid option!");
							break;
					}
				}
				askFlag = 1;
			}
		}
	}
	printf("\n						        Goodbye!");
	return 0;
}
/* ---------- MAIN ---------- */
