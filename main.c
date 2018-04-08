/**
    NOME: FELIPE TIAGO DE CARLI
    N USP: 10525686
    GITHUB: https://github.com/felipdc
     _   _ ___________
    | | | /  ___| ___ \
    | | | \ `--.| |_/ /
    | | | |`--. \  __/
    | |_| /\__/ / |
     \___/\____/\_|

**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "play.h"
#include "board.h"


size_t hexchar_touint (char moveRead) {
    char *ptr; /** Next character in moveRead after the numerical value **/
    long ret = strtol (&moveRead, &ptr, 16);  /** Converts initial part of moveRead to a long int of base 16 **/
    return (size_t)ret; /** Explicit cast not necessary but will be kept here **/
}


int main (int argc, char *argv[]) {
    gm *newGame;
    newGame = malloc (sizeof(gm));
    init_board (newGame); 
    print_board (newGame);
    firstPlay (newGame);
    play1(newGame);
    free (newGame);
    return 0;
}
