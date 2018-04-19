#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int maxValue (int *numbers, size_t len);
int minValue (int *numbers, size_t len);
/**	---- 0000 */
typedef enum {false,
	true} bool;

typedef enum {loss = -1,
	draw, win} Score;

typedef enum {min = 1,
	max} Player;


struct game {
	struct game **node;
	size_t possible_nodes;
	bool terminal;
	uint8_t field[4];
	Score score;
	Player player;
}; typedef struct game gm;	


void allocNodes (gm *gamenode) {
	for (int i = 0; i < gamenode->possible_nodes; ++i) {
		gamenode->node[i] = malloc (sizeof(gm));
	}
}


bool gameWon (gm *gamenode) {
	if (gamenode->field[0] == gamenode->field[1]) {
		if (gamenode->field[0] != 0) {
			return true;
		}
	}
	if (gamenode->field[1] == gamenode->field[2]) {
		if (gamenode->field[1] != 0) {
			return true;
		}
	}
	if (gamenode->field[2] == gamenode->field[3]) {
		if (gamenode->field[2] != 0) {
			return true;
		}
	}
	gamenode->terminal = false;
	return gamenode->terminal;
}


size_t numberOfNodes (gm *gamenode) {
	gamenode->possible_nodes = 0;
	for (int i = 0; i < 4; ++i) {
		if (gamenode->field[i] == 0) ++gamenode->possible_nodes;
	}
	return gamenode->possible_nodes;
}


size_t readInput (gm *gamenode) {
	size_t play_input = 0;
	scanf ("%u", &play_input);
	getchar ();
	gamenode->field[play_input] = max;
	gamenode->player = min;
}


void printBoard (gm *gamenode) {
	for (int i = 0; i < 4; ++i) {
		printf("%hu", gamenode->field[i]);
	}
	printf("\n");
}

void initBoard (gm *gamenode) {
	for (int i = 0; i < 4; ++i) {
		gamenode->field[i] = 0;
	}
	gamenode->player = max;
}


Score minimax (gm *gamenode) {
	if (gameWon (gamenode)) {
		printf("gamewon or lost");
		if (gamenode->player == min) return loss;
		if (gamenode->player == max) return win; 
	} 
	if (numberOfNodes (gamenode) == 0) {
		printf("empate\n");
		return draw;
	}
	numberOfNodes(gamenode);
	//allocNodes(gamenode);
	int *a;
	a = malloc(sizeof(gamenode->possible_nodes));
	if (gamenode->player == max) {
		//printf("1\n");
		for (int i = 0; i < gamenode->possible_nodes; ++i) {
			//printf("2\n");
			gamenode->node[i] = malloc(sizeof(gm));
			gamenode->node[i]->player = max;
			
			a[i] = minimax (gamenode->node[i]);
			printf("ta no max");
		}
		return maxValue (a, gamenode->possible_nodes);
	}
	if (gamenode->player == min) {
		//printf("1\n");
		for (int i = 0; i < gamenode->possible_nodes; ++i) {
			//printf("2\n");
			gamenode->node[i] = malloc(sizeof(gm));
			gamenode->node[i]->player = max;
			a[i] = minimax (gamenode->node[i]);
			printf("ta no min");
		}
		return minValue (a, gamenode->possible_nodes);
	}
}



int maxValue (int *numbers, size_t len) {
	int max = 0;
	for (int i = 0; i <= len; ++i) {
		if (numbers[i] > max)
		  max = numbers[i];
	}
	return max;
}

// 0020
// 1020 0120 0021
// 


int minValue (int *numbers, size_t len) {
	int min = 0;
	for (int i = 0; i >= len; ++i) {
		if (numbers[i] > min)
		  min = numbers[i];
	}
	return min;
}


int main (void) {

	gm *newGame;
	newGame = malloc(sizeof(gm));
	initBoard (newGame);
	printBoard (newGame);
	readInput (newGame);
	printf ("%d\n",minimax (newGame));
	printBoard (newGame);
	free(newGame);

}