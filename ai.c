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
#include "board.h"
#include "play.h"


/**
 *	
 *	Until the game reaches a certain depht, AI will choose
 * the next piece based simply on wheter the piece will let
 * the player win or not on the next move.
 *
 */ 

 int chooseAiNextPiece (gm *newGame) {
 	int i, j = 0;
 	// Iterate throught all unused pieces
 	for (i = 0; i < 16; ++i) {
 		if (newGame->pieceStats[i] == unused) {
 			// Try this piece
 			newGame->boardStats[i] = filled;
 			// Iterate throught all empty positions
 			for (j = 0; j < 16; ++j) {
 				// Try this position
 				newGame->board[j] = binaryoptions[i];
 				if (checkBoard(newGame) == false) {
 					// Piece will not result in a winning position.
 					// Undo the changes and return piece
 					newGame->boardStats[i] = empty;
 					newGame->board[j] = "free";
 					return i;
 				} else {
 					// Undo the changes
 					newGame->boardStats[i] = empty;
 					newGame->board[j] = "free";
 				}
 			}
 		}
 	}
 	/**
 	 *
 	 *	If there is no possible piece to escape a loosing position,
 	 * AI will return the first unused piece.
 	 *
 	 */
 	 for (i = 0; i < 16; ++i) {
 	 	if (newGame->pieceStats[i] == unused) {
 	 		return i;
 	 	}
 	 }
 }


/** 
 *
 *	AI will play a board position which has the most
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

int chooseAiMove (gm *newGame) {
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
		if (pos == 0 + j) || pos == 4 + j) 
			|| pos == 8 + j) || pos == 12 + j)) { // Row ?
				for (i = 0 + j; i < 12 + j; i += 4) {
					if (boardStats[i)] == empty) ++num_of_empty;
				}
				return num_of_empty;
		}
	}
}
