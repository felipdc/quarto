#ifndef BOARD_H_
#define BOARD_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void print_board (gm *newGame); /** Display current board on screen */
void init_board (gm *newGame);  /** Set all values to initialize a new game */
bool checkBoard (gm *newGame);	/** Check if pieces are at a winning position */


#endif /* BOARD_H_ **/