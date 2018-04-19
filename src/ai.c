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
#include "ai.h"
#include "options.h"


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
 	int counter = 0;
 	// Iterate throught all unused pieces
 	for (i = 0; i < 16; ++i) {
 		if (newGame->pieceStats[i] == unused) {
 			// Iterate throught all empty positions
 			for (j = 0; j < 16; ++j) {
 				// Check if a position is empty
 				if (newGame->boardStats[j] == empty) {
 					// Try this position
 					newGame->board[j] = binaryoption[i];
 					newGame->boardStats[j] = filled;
 					if (checkBoard(newGame) == true) {
 					// Piece will result in a winning position for the player
 					// Undo the changes and try next piece
 						newGame->boardStats[j] = empty;
 						newGame->board[j] = "free";
 						break;
 					} 
 				 	else {
 						// Undo the changes
 						newGame->boardStats[j] = empty;
 						newGame->board[j] = "free";
 						++counter;
 						// Check if all positions were iterated
 						if (getEmptyPositions(newGame) == counter) {
 							return i;
 						}
 					}
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
 	 		return i; // Return next piece
 	 	}
 	 }
 }


/** 
 *	
 *	AI will, in it`s first attempt, try to find winning positions.
 * 
 *	If there is no winning position, AI will play a board 
 * position which has the most odd positions and the less 
 * even positions avaliable in colums and rows. Using this
 * method, AI will increase the probability of being the 
 * last one to fill an empty column or row, winning the game.
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
		// If position is empty
		if (newGame->boardStats[i] == empty) {
			// Try this position
			newGame->board[i] = binaryoption[newGame->next_piece];
			newGame->boardStats[i] = filled;
			// If the position is a winning position, return
			if (checkBoard (newGame) == true) {
				// Undo changes
				newGame->board[i] = "free";
				newGame->boardStats[i] = empty;
				// Return winning position
				return i;
			}
			// Undo the changes anyway
			newGame->board[i] = "free";
			newGame->boardStats[i] = empty;
		}
	}

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


void moveUsingHeuristic (gm *newGame) {
	size_t aiMove = 0;
	size_t aiNextP = 0;
	// Check if AI has to do the first move
	if (g_first_play == true) {
		g_first_play = false;
		aiNextP = chooseAiNextPiece(newGame);
		newGame->next_piece = aiNextP;
		newGame->pieceStats[aiNextP] = used;
		play1 (newGame);
		return;
	}
	// Play using minimax when 66% of all positions are empty
	if (getEmptyPositions(newGame) < 11 ) {
		moveUsingMinimax (newGame);
		return;
	}
	aiMove = chooseAiMove(newGame);
	newGame->board[aiMove] = binaryoption[newGame->next_piece];
	newGame->boardStats[aiMove] = filled;
	aiNextP = chooseAiNextPiece(newGame);
	newGame->next_piece = aiNextP;
	newGame->pieceStats[aiNextP] = used;
	print_board(newGame);
	if (checkBoard (newGame) == true) {
		printf ("AI won the game ! \n");
		return;
	}
	play1(newGame);
}


/**
 *
 * 	AI will play using minimax algorithm when 66% of all position are empty, i.e.,
 * when 10 positions are left on board. By this way, we avoid intese computation
 * power that could last days for the first moves.
 *
 */

int moveUsingMinimax (gm *newGame) {
	int s = -999; // Score to get by calling minimax function
	struct move *best_move;
	best_move = malloc (sizeof(struct move));

	best_move->move, best_move->next_piece = 0;
	printf("Thinking... This can take a while depending on your processor\n\n\n");
	s = minimax (true, newGame, best_move);
	/** Make the move returned by minimax */
	newGame->board[best_move->move] = binaryoption[newGame->next_piece];
	newGame->boardStats[best_move->move] = filled;
	newGame->next_piece = best_move->next_piece;
	newGame->pieceStats[best_move->next_piece] = used;

	/** Check score to see if game is won or lost */
	s = getScore (newGame, false);
	if (s == WIN) {
		printf ("Game finished, AI won!\n");
		return 0;
	}
	if (s == LOSS) {
		printf ("Game finished, Player won!\n");
		return 0;
	}
	if (s == DRAW && moveLeft(newGame) == false) {
		printf ("Game draw!\n");
		return 0;
	}
	print_board(newGame);
	play1(newGame);
}


int minimax (bool is_max, gm *game_node, struct move *mv) {
	int current_score = getScore (game_node, is_max);

	// If game is won or lost
	if (current_score == WIN || current_score == LOSS) {
		return current_score;
	}
	// If game position is a draw
	if (moveLeft (game_node) == false) {
		printf ("%d\n", current_score);
		return DRAW;
	}
	int best_value = 0;
	int current_value = 0;
	size_t last_piece = game_node->next_piece; // Will be used when undo changes is needed 
	if (is_max == true) {
		best_value = -100;
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
		return best_value;
	}

	if (is_max == false) {
		best_value = 100;
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

// Return WIN if AI is at a winning position
int getScore (gm *newGame, bool is_max) {
	if (checkBoard(newGame) == true) {
		if (is_max == false) return WIN;
		return LOSS;
	}
	return DRAW;
}

// Return num of empty Rows
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

// Return num of empty Colums 
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
