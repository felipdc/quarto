#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "play.h"
#include "board.h"


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
					printf("digit %d of line %d is equal\n", i, j);
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
