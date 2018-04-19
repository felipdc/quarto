#ifndef OPTIONS_H_
#define OPTIONS_H_

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
#include "play.h"

#define HELP 0 // -help
#define PLAYER_VS_AI 1 // -ai
#define AI_BEGINS 2 // -aib
#define TEST_GAME 3 // -test

bool g_flags[16];

#endif /** OPTIONS_H_ */