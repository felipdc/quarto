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
#include "play.h"
#include "board.h"
#include "ai.h"
#include "options.h"


size_t hexchar_touint (char moveRead) {
    char *ptr; /** Next character in moveRead after the numerical value */
    long ret = strtol (&moveRead, &ptr, 16);  /** Converts initial part of moveRead to a long initialt of base 16 */
    return (size_t)ret; /** Explicit cast not necessary but will be kept here */
}


bool set_flags (int argc, char *argv[]) {
	// Set all flags to false
	for (int i = 0; i < 16; ++i) {
		g_flags[i] = false;	
	}
	if (argc > 3) {
		printf ("Invalid options. See -help for a "
				"list of avaliable commands");
		return false;
	}
	if (argc > 1 && strcmp (argv[1], "-ai") == 0) {
		g_flags[PLAYER_VS_AI] = true;
		if (argc == 3 && strcmp (argv[2], "-aib") == 0) {
			g_flags[AI_BEGINS] = true;	

		}
		return true;
	}

    if (argc > 1 && strcmp (argv[1], "-test") == 0) {
        g_flags[TEST_GAME] = true;
        return true;
    }
}


// Great game to AI think about

void setTestBoard (gm *newGame) {
    newGame->board[0] = "0000";
    newGame->boardStats[0] = filled;
    newGame->pieceStats[0] = used;

    newGame->board[1] = "0001";
    newGame->boardStats[1] = filled;
    newGame->pieceStats[1] = used;

    newGame->board[4] = "0010";
    newGame->boardStats[4] = filled;
    newGame->pieceStats[2] = used;

    newGame->board[5] = "1111";
    newGame->boardStats[5] = filled;
    newGame->pieceStats[15] = used;

    newGame->board[14] = "1100";
    newGame->boardStats[14] = filled;
    newGame->pieceStats[12] = used;

    newGame->board[11] = "1010";
    newGame->boardStats[11] = filled;
    newGame->pieceStats[10] = used;

    newGame->pieceStats[3] = used;
    newGame->next_piece = 3;

}


int main (int argc, char *argv[]) {
    gm *newGame;
    newGame = malloc (sizeof(gm));
    set_flags (argc, argv);
    init_board (newGame);
    print_board (newGame);
    if (g_flags[PLAYER_VS_AI] == true) {
    	if (g_flags[AI_BEGINS] == true) {
    		g_first_play = true;
    		moveUsingHeuristic (newGame);
    	}else {
    		firstPlay (newGame);
    	}
    }
    else if (g_flags[TEST_GAME] == true) {
        g_flags[PLAYER_VS_AI] = true;
        setTestBoard (newGame);
        print_board (newGame);
        moveUsingHeuristic (newGame);
        free (newGame);
        return 0;
    }
    else {
    	firstPlay (newGame);
        free (newGame);
        return 0;
    }
    free (newGame);
    return 0;
}
