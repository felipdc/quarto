/**
    NOME: FELIPE TIAGO DE CARLI
    N USP: 10525686
    GITHUB: https://github.com/felipdc
     _   _ ___________
    | | | /  ___| ___ \
    | | | \ `--.| |_/ /
    | | | |`--. \  __/
    | |_| /\__/ / |
     \___/\____/\_|

**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {false,
	true} bool;

typedef enum {empty,
	filled} Boardst;

typedef enum {unused,
	used} Piecest;

typedef enum {player1,
	player2} Whoplays;


/**
    Range of options is from 0 to F, so it`s binary values can be
     easily stored in a small char pointer pointer
**/
char *binaryoptions[] = {"0000", "0001", "0010", "0011", "0100",
                                "0101", "0110", "0111", "1000", "1001",
                                "1010", "1011", "1100", "1101", "1110",
                                "1111"};


struct game {
    char *board[16];	/** game field **/
    Boardst boardStats[16]; /** wheter the position on the board is empty or filled **/
    Piecest pieceStats[16]; /** wheter the number is already used or not **/
    Whoplays player; /** Whose turn it is to play **/
    size_t next_piece; /** Next piece to be put in the board by the following player **/
}; typedef struct game gm;	


size_t hexchar_touint (char moveRead) {
    char *ptr; /** Next character in moveRead after the numerical value **/
    long ret = strtol (&moveRead, &ptr, 16);  /** Converts initial part of moveRead to a long int of base 16 **/
    return (size_t)ret; /** Explicit cast not necessary but will be kept here **/
}


void print_board (gm *newGame) {
    for (int i = 0; i < 15; ++i) {
        if (i == 3 || i == 7 || i == 11) {
            if (newGame->boardStats[i] == empty) {
                printf("    \n");
                continue;
            }
            printf("%s\n", newGame->board[i]);
            continue;
        }
        if (newGame->boardStats[i] == empty)
            printf ("    |");
        else
            printf ("%s|", newGame->board[i]);
    }
    if (newGame->boardStats[15] == empty)
        printf ("    \n\n");
    else
        printf ("%s\n\n", newGame->board[15]);
}


void init_board (gm *newGame) {
    int i = 0;
    for (i = 0; i < 16; ++i) {
        newGame->board[i] = "free";
        newGame->boardStats[i] = empty;
        newGame->pieceStats[i] = unused;
    }
    newGame->player = player1; /** first player will be player1 by default **/
}


/**
	winning coords:
		0 1 2 3 => lines
		4 5 6 7
		8 9 a b
		c d e f
		0 4 8 c => columns
		1 5 9 d
		2 6 a e
		3 7 b f
		0 5 a f => first diagonal
		3 6 9 c => second diagonal
**/


bool checkBoard (gm *newGame) {
	for (int j = 0; j < 15; j += 4){ /** iterate throught board position **/
		for (int i = 0; i < 4; ++i) { /** iterate throught string **/
			if (newGame->boardStats[0+j] == empty) continue; /** Check if one of the positions is still empty **/
			else if (newGame->board[0+j][i] == newGame->board[1+j][i] && newGame->board[0+j][i] == 
				newGame->board[2+j][i] && newGame->board[1+j][i] == newGame->board[3+j][i]) {
					return true;
			}
		}
	}
	for (int j = 0; j < 4; ++j){
		for (int i = 0; i < 4; ++i) {
			if (newGame->boardStats[0+j] == empty) continue;
			else if (newGame->board[0+j][i] == newGame->board[4+j][i] && newGame->board[0+j][i] == 
				newGame->board[8+j][i] && newGame->board[4+j][i] == newGame->board[12+j][i]) {
					printf("digit %d of column %d is equal\n", i, j);
					return true;
			}
		}
	}
	for (int i = 0; i < 4; ++i) {
		if (newGame->boardStats[0] == empty) continue;
		else if (newGame->board[0][i] == newGame->board[5][i] && newGame->board[0][i] ==
			newGame->board[10][i] && newGame->board[5][i] == newGame->board[15][i]) {
				printf("digit %d in the first diagonal is equal\n", i);
				return true;
		}
	}
	for (int i = 0; i < 4; ++i) {
		if (newGame->boardStats[3] == empty) continue;
		else if (newGame->board[3][i] == newGame->board[6][i] && newGame->board[3][i] ==
			newGame->board[9][i] && newGame->board[6][i] == newGame->board[12][i]) {
				printf("digit %d in the second diagonal is equal\n", i);
				return true;
		}
	}
	return false;
}


void play1 (gm *newGame) {
	char read_move, read_next_piece = ' '; /** Variables to be read by the user **/
	size_t move, next_p = 0;
	scanf ("%c", &read_move);
	getchar(); /** Prevents \n to be copied to the next scanf **/
	scanf ("%c", &read_next_piece);
	getchar();
	move = hexchar_touint (read_move);
	next_p = hexchar_touint (read_next_piece);
	while (newGame->boardStats[move] == filled) {
		printf ("Board position is already filled. Try another position. \n");
		scanf ("%c", &read_move);
		getchar();
		move = hexchar_touint (read_move);
	}
	while (newGame->pieceStats[next_p] == used) {
		printf ("Piece %lu is already in use. Try another piece. \n", next_p);
		scanf ("%c", &read_next_piece);
		getchar();
		next_p = hexchar_touint (read_next_piece);
	}
	newGame->board[move] = binaryoptions[newGame->next_piece];
	/** Check if the move is a winning move **/
	if (checkBoard (newGame)) {
		printf("Game over\n");
		return;
	}
	newGame->boardStats[move] = filled;
	newGame->next_piece = next_p;
	newGame->pieceStats[next_p] = used;
}


void firstPlay (gm *newGame) {
	char read_next_piece = ' ';
	scanf ("%c\n", &read_next_piece);
	newGame->next_piece = hexchar_touint (read_next_piece);
	newGame->pieceStats[newGame->next_piece] = used;
	newGame->player = player2;
}


int main (int argc, char *argv[]) {
    gm *newGame;
    newGame = malloc (sizeof(gm)); /** allocating memory for newGame struct **/
    init_board (newGame); /** initialize board and fill all positions with null values **/
    print_board (newGame);
    firstPlay (newGame);
    play1 (newGame);
    print_board (newGame);
    play1 (newGame);
    print_board (newGame);
    free (newGame);
    return 0;
}
