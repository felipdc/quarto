#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "play.h"
#include "board.h"

/**
 *	Range of options is from 0 to F, so it`s binary values can be
 *	easily stored in a small char pointer pointer
 */
char *binaryoptions[] = {"0000", "0001", "0010", "0011", "0100",
                                "0101", "0110", "0111", "1000", "1001",
                                "1010", "1011", "1100", "1101", "1110",
                                "1111"};


/** Check if the user input is a valid input */
bool validInput (char user_input) {
	if (user_input > 64 && user_input < 71) return true;
	if (user_input > 96 && user_input < 103) return true;
	if (user_input > 47 && user_input < 58) return true;
	return false;
}

/** Read user input from terminal or cmd */
size_t readFromUser () {
	char read_from_user = ' ';
	scanf ("%c", &read_from_user);
	getchar();
	while (validInput (read_from_user) == false) {
		printf ("Invalid move!\n");
		scanf ("%c", &read_from_user);	
		getchar();
	}
	return (hexchar_touint (read_from_user));
}

/** Default play function */
void play1 (gm *newGame) {
	printf("Player %d: \n" 
			"Choose a position for the piece %04lx\n", newGame->player,
			 newGame->next_piece);
	size_t move = readFromUser ();
	printf("Choose a piece for the next player\n");
	size_t next_p = readFromUser ();
	while (newGame->boardStats[move] == filled) {
		printf ("Board position is already filled. Try another position. \n");
		move = readFromUser ();
	}
	while (newGame->pieceStats[next_p] == used) {
		printf ("Piece %lu is already in use. Try another piece. \n", next_p);
		next_p = readFromUser ();
	}
	updateGame (move, next_p, newGame);
	play1(newGame);
}


/** Update game after input move and piece are valid */
void updateGame (size_t move, size_t next_p, gm *newGame) {
	newGame->board[move] = binaryoptions[newGame->next_piece];
	newGame->boardStats[move] = filled;
	newGame->next_piece = next_p;
	newGame->pieceStats[next_p] = used;
	if (newGame->player == player1) newGame->player = player2;
	else newGame->player = player1;
	print_board(newGame);
	/** Check if the move is a winning move **/
	if (checkBoard (newGame)) {
		printf("Game over! \nPlayer %d is the winner!\n", newGame->player + 1);
		return;
	}
	return;
}

/** It will only be executed on the first move */
void firstPlay (gm *newGame) {
	char read_next_piece = ' ';
	scanf ("%c", &read_next_piece);
	getchar();
	newGame->next_piece = hexchar_touint (read_next_piece);
	newGame->pieceStats[newGame->next_piece] = used;
	newGame->player = player2;
}

