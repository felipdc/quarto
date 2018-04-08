#ifndef PLAY_H_
#define PLAY_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef enum {player1 = 1,
	player2} Whoplays;

typedef enum {false,
	true} bool;

typedef enum {empty,
	filled} Boardst;

typedef enum {unused,
	used} Piecest;
    

struct game {
    char *board[16];	/** game field **/	
    Boardst boardStats[16]; /** wheter the position on the board is empty or filled **/
    Piecest pieceStats[16]; /** wheter the number is already used or not **/
    Whoplays player; /** Whose turn it is to play **/
    size_t next_piece; /** Next piece to be put in the board by the following player **/
}; typedef struct game gm;	


size_t hexchar_touint (char moveRead); /** Convert input char to unsigned int */
void play1 (gm *newGame); /** Default main play function */
void firstPlay (gm *newGame); /** Executed only on first move */
void updateGame (size_t move, size_t next_p, gm *newGame); /** Update board as soon as moves are considered valid */
size_t readFromUser (); /** Read input from user and return size_t value */
bool validInput (char user_input); /** Check if user input is a valid input */


#endif 