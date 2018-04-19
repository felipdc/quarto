#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/**
    Range of options is from 0 to F, so it`s binary values can be
     easily stored in a small char pointer pointer
**/
char *binaryoptions[] = {"0000", "0001", "0010", "0011", "0100",
                                "0101", "0110", "0111", "1000", "1001",
                                "1010", "1011", "1100", "1101", "1110",
                                "1111"};


/**
	winning coords:

		0 1 2 3
		4 5 6 7
		8 9 a b
		c d e f

		0 4 8 c
		1 5 9 d
		2 6 a e
		3 7 b f

		0 5 a f
		3 6 9 c
**/

int main (void) {

	char *board[] = {"1000", "1110", "1010", "1000","1101", "0110", "1010", "1000","1000", "1110", "1010", "1000","1000", "1110", "1010", "1000"};

	for (int j = 0; j < 15; j += 4){
		for (int i = 0; i < 4; ++i) {
			if (board[0+j][i] == board[1+j][i] && board[0+j][i] == 
				board[2+j][i] && board[1+j][i] == board[3+j][i]) {
					return win;
			}
		}
	}

	for (int j = 0; j < 4; ++j){
		for (int i = 0; i < 4; ++i) {
			if (board[0+j][i] == board[4+j][i] && board[0+j][i] == 
				board[8+j][i] && board[4+j][i] == board[12+j][i]) {
					printf("digit %d of column %d is equal\n", i, j);
					return win;
			}
		}
	}

	for (int i = 0; i < 4; ++i) {
		if (board[0][i] == board[5][i] && board[0][i] ==
			board[10][i] && board[5][i] == board[15][i]) {
				printf("digit %d in the first diagonal is equal\n", i);
				return win;
		}
	}

	for (int i = 0; i < 4; ++i) {
		if (board[3][i] == board[6][i] && board[3][i] ==
			board[9][i] && board[6][i] == board[12][i]) {
				printf("digit %d in the second diagonal is equal\n", i);
				return win;
		}
	}




		
}