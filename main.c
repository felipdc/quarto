/**
    FELIPE TIAGO DE CARLI
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
    Whoplays player;
    size_t next_piece;
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

void play1 (gm *newGame) {
	char read_move, read_next_piece = ' ';
	size_t move = 0;
	scanf ("%c %c\n", &read_move, &read_next_piece);
	move = hexchar_touint (read_move);
	newGame->board[move] = binaryoptions[newGame->next_piece];
	newGame->boardStats[move] = filled;
	newGame->next_piece = hexchar_touint (read_next_piece);
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
    free (newGame);
    return 0;
}
