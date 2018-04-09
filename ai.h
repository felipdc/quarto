#ifndef AI_H_
#define AI_H_

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
#include <stdint.h>
#include "play.h"
#include "board.h"

#define LOSS -10
#define WIN 10
#define DRAW 0

struct move {
	size_t move, next_piece;
};

int chooseAiNextPiece (gm *newGame);
int chooseAiMove (gm *newGame);
void moveUsingHeuristic(gm *newGame);
int minimax (bool is_max, gm *game_node, struct move *mv);
int getScore (gm *newGame, bool is_max);
uint8_t emptyRow (size_t pos, Boardst boardStats[]);
uint8_t emptyColumn (size_t pos, Boardst boardStats[]);

#endif /** AI_H_ */