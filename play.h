#ifndef PLAY_H_
#define PLAY_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum {player1,
	player2} Whoplays;

typedef enum {false,
	true} bool;

typedef enum {empty,
	filled} Boardst;

typedef enum {unused,
	used} Piecest;

/**
    Range of options is from 0 to F, so it`s binary values can be
     easily stored in a small char pointer pointer
**/

struct game {
    char *board[16];	/** game field **/	
    Boardst boardStats[16]; /** wheter the position on the board is empty or filled **/
    Piecest pieceStats[16]; /** wheter the number is already used or not **/
    Whoplays player; /** Whose turn it is to play **/
    size_t next_piece; /** Next piece to be put in the board by the following player **/
}; typedef struct game gm;	


size_t hexchar_touint (char moveRead);
void play1 (gm *newGame);
void firstPlay (gm *newGame);


#endif 