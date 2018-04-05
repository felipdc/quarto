#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "play.h"
#include "board.h"

/**
    Range of options is from 0 to F, so it`s binary values can be
     easily stored in a small char pointer pointer
**/
char *binaryoptions[] = {"0000", "0001", "0010", "0011", "0100",
                                "0101", "0110", "0111", "1000", "1001",
                                "1010", "1011", "1100", "1101", "1110",
                                "1111"};


void play1 (gm *newGame) {
	char read_move, read_next_piece = ' '; /** Variables to be read by the user **/
	size_t move, next_p = 0;
	scanf ("%c", &read_move);
	getchar(); /** Prevents \n to be copied to the next scanf **/
	scanf ("%c", &read_next_piece);
	getchar();
	move = hexchar_touint (read_move);
	next_p = hexchar_touint (read_next_piece);
	while (newGame->boardStats[move] == filled) {
		printf ("Board position is already filled. Try another position. \n");
		scanf ("%c", &read_move);
		getchar();
		move = hexchar_touint (read_move);
	}
	while (newGame->pieceStats[next_p] == used) {
		printf ("Piece %lu is already in use. Try another piece. \n", next_p);
		scanf ("%c", &read_next_piece);
		getchar();
		next_p = hexchar_touint (read_next_piece);
	}
	newGame->board[move] = binaryoptions[newGame->next_piece];
	newGame->boardStats[move] = filled;
	newGame->next_piece = next_p;
	newGame->pieceStats[next_p] = used;
	print_board(newGame);
	/** Check if the move is a winning move **/
	if (checkBoard (newGame)) {
		printf("Game over! \nPlayer %d is the winner!\n", newGame->player + 1);
		return;
	}
	play1(newGame);
	return;
}


void firstPlay (gm *newGame) {
	char read_next_piece = ' ';
	scanf ("%c\n", &read_next_piece);
	newGame->next_piece = hexchar_touint (read_next_piece);
	newGame->pieceStats[newGame->next_piece] = used;
	newGame->player = player2;
}

