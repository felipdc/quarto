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
    long ret = strtol (&moveRead, &ptr, 16);  /** Converts initial part of moveRead to a long int of base 16 */
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
		if (argc == 3 && strcmp (argv[2], "-aib")) {
			g_flags[AI_BEGINS] = true;	

		}
		return true;
	}
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
    }else {
    	firstPlay (newGame);
    	play1 (newGame);
    }
    free (newGame);
    return 0;
}
