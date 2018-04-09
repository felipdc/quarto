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

#ifndef BOARD_H_
#define BOARD_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "play.h"


void print_board (gm *newGame); /** Display current board on screen */
void init_board (gm *newGame);  /** Set all values to initialize a new game */
bool checkBoard (gm *newGame);	/** Check if pieces are at a winning position */
bool moveLeft (gm *newGame); /** Check if there is any position left */


#endif /* BOARD_H_ **/