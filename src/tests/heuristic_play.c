/**
 *   NOME: FELIPE TIAGO DE CARLI
 *   N USP: 10525686
 *   GITHUB: https://github.com/felipdc
 *    _   _ ___________
 *   | | | /  ___| ___ \
 *   | | | \ `--.| |_/ /
 *   | | | |`--. \  __/
 *   | |_| /\__/ / |
 *    \___/\____/\_|
 *
 *********************************************   
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


/** 
 *
 *	AI will play in a board position which has the most
 * odd positions and the less even positions avaliable in 
 * colums and rows. Using this method, AI will increase the 
 * probability of being the last one to fill an empty
 * column or row, winning the game.
 *
 *	AI will be playing using this function until the board
 * achieves a certain depht. Then, AI will use the minimax
 * algorithm to decide it`s move.
 *
 */

 /**
	0 1 2 3
	4 5 6 7
	8 9 A B
	C D E F
	
  */


typedef enum {player1 = 1,
	player2} Whoplays;

typedef enum {false,
	true} bool;

typedef enum {empty,
	filled} Boardst;

typedef enum {unused,
	used} Piecest;
    

struct game {
    char *board[16];	/** Game field */	
    Boardst boardStats[16]; /** Wheter the position on the board is empty or filled */
    Piecest pieceStats[16]; /** Wheter the number is already used or not */
    Whoplays player; /** Whose turn it is to play */
    size_t next_piece; /** Next piece to be put in the board by the following player */
}; typedef struct game gm;


uint8_t emptyRow (size_t pos, Boardst boardStats[]);
uint8_t emptyColumn (size_t pos, Boardst boardStats[]);	

int heuristicFunction (gm *newGame) {
	int i, j = 0;
	uint8_t emptyInColums, emptyInRows, max = 0;
	int bestPos = -1;
	// Iterate throught the board to find empty positions
	for (i = 0; i < 16; ++i) {
		if (newGame->boardStats[i] == empty) {
			emptyInColums = emptyColumn (i, newGame->boardStats);
			emptyInRows = emptyRow (i, newGame->boardStats);
			if (emptyInRows % 2 != 0 && emptyInColums % 2 != 0) {
				if (emptyInRows + emptyInColums > max) {
					max = emptyInRows + emptyInColums;
					bestPos = i;
				}
			}
		}
	}
	/** 
	 * In case of no combination of odd empty column and row, the position
	 * will be chosen by the first avalaible position on board.
	 */
	if (bestPos == -1) {
		for (i = 0; i < 16; ++i) {
			if (newGame->boardStats[i] == empty) {
				bestPos = i;
				return bestPos;
			}
		}
	} else {
		return bestPos;
	}
}


uint8_t emptyRow (size_t pos, Boardst boardStats[]) {
	int i = 0;
	uint8_t num_of_empty = 0;
	for (int j = 0; j < 4; ++j) {
		if (pos == 0 + (4 * j) || pos == 1 + (4 * j) 
			|| pos == 2 + (4 * j) || pos == 3 + (4 * j)) { // Row ?
				for (i = 0; i < 4; ++i) {
					if (boardStats[i + (4 * j)] == empty) ++num_of_empty;
				}
				return num_of_empty;
		}
	}
}


uint8_t emptyColumn (size_t pos, Boardst boardStats[]) {
	int i = 0;
	uint8_t num_of_empty = 0;
	for (int j = 0; j < 4; ++j) {
		if (pos == 0 + j || pos == 4 + j 
			|| pos == 8 + j || pos == 12 + j) { // Row ?
				for (i = 0 + j; i < 12 + j; i += 4) {
					if (boardStats[i] == empty) ++num_of_empty;
				}
				return num_of_empty;
		}
	}
}


void init_board (gm *newGame) {
    int i = 0;
    for (i = 0; i < 16; ++i) {
        newGame->board[i] = "free";
        newGame->boardStats[i] = empty;
        newGame->pieceStats[i] = unused;
    }
    newGame->player = player1; /** first player will be player1 by default */
}

int main (void) {
	gm *newGame;
	newGame = malloc (sizeof(gm));
	init_board(newGame);
	newGame->boardStats[15] = filled;
	printf ("%d\n", heuristicFunction(newGame));
	free(newGame);
}