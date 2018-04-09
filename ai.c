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
#include "board.h"
#include "play.h"

 #define LOSS -10
 #define WIN 10
 #define DRAW 0

struct move {
	size_t move, next_piece;
};

int chooseAiNextPiece (gm *newGame);
int chooseAiMove (gm *newGame);
int minimax (bool is_max, gm *game_node, struct move *mv);
int getScore (gm *newGame, bool is_max);
uint8_t emptyRow (size_t pos, Boardst boardStats[]);
uint8_t emptyColumn (size_t pos, Boardst boardStats[]);

char *binaryoption[] = {"0000", "0001", "0010", "0011", "0100",
                                "0101", "0110", "0111", "1000", "1001",
                                "1010", "1011", "1100", "1101", "1110",
                                "1111"};


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
 				newGame->board[j] = binaryoption[i];
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
	 * will be chosen by the first avaliable position on board.
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

/**
 *
 * 	AI will play using minimax algorithm when 60% of all position are used, i.e.,
 * when 6 positions are left on board.
 *
 */

int minimax (bool is_max, gm *game_node, struct move *mv) {
	int current_score = getScore (game_node, is_max);

	// If game is won or lost
	if (current_score == 10 || current_score == -10) {
		return current_score;
	}
	// If game position is a draw
	if (moveLeft (game_node) == false) {
		return current_score;
	}

	int best_value;
	int current_value = 0;
	size_t last_piece = game_node->next_piece; // Will be used when undo changes is needed 
	if (is_max) {
		int best_value = -100;
		// Iterate throught all avaliable positions
		for (int i = 0; i < 16; ++i) {
			if (game_node->boardStats[i] == empty) {
				// Iterate throught all avaliable pieces
				for (int j = 0; j < 16; ++j) {
					if (game_node->pieceStats[j] == unused) {
						// Try this position
						game_node->board[i] = binaryoption[game_node->next_piece];
						game_node->boardStats[i] = filled;
						// Try this piece
						game_node->next_piece = j;
						game_node->pieceStats[j] = used;
						// Call minimax again
						current_value = minimax (false, game_node, mv);
						// Undo changes
						game_node->board[i] = "free";
						game_node->boardStats[i] = empty;
						game_node->next_piece = last_piece;
						game_node->pieceStats[j] = unused;
						// Check if it is a winning node
						if (current_value == WIN) {
							mv->move = i;
							mv->next_piece = j;
							return current_value;
						}
						if (current_value > best_value) {
							best_value = current_value;
							mv->move = i;
							mv->next_piece = j;
						}
					}
				}
			}
		}
	}
	return best_value;

	if (!is_max) {
		int best_value = 100;
		// Iterate throught all avaliable positions
		for (int i = 0; i < 16; ++i) {
			if (game_node->boardStats[i] == empty) {
				// Iterate throught all avaliable pieces
				for (int j = 0; j < 16; ++j) {
					if (game_node->pieceStats[j] == unused) {
						// Try this position
						game_node->board[i] = binaryoption[game_node->next_piece];
						game_node->boardStats[i] = filled;
						// Try this piece
						game_node->next_piece = j;
						game_node->pieceStats[j] = used;
						// Call minimax again
						current_value = minimax (true, game_node, mv);
						// Undo changes
						game_node->board[i] = "free";
						game_node->boardStats[i] = empty;
						game_node->next_piece = last_piece;
						game_node->pieceStats[j] = unused;
						// Check if it is a winning node
						if (current_value < best_value) {
							best_value = current_value;
						}
					}
				}
			}
		}
	}
	return best_value;
}


int getScore (gm *newGame, bool is_max) {
	if (checkBoard(newGame) == true) {
		if (is_max) return WIN;
		return LOSS;
	}
	return DRAW;
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
