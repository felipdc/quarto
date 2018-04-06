#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/**	---- 0000 */
typedef enum {false,
	true} bool;

typedef enum {loss = -1,
	draw, win} Score;

typedef enum {min,
	max} Player;


struct game {
	struct game **node;
	size_t possible_nodes;
	bool terminal;
	uint8_t field[4];
	Score score;
	Player player;
}; typedef struct game gm;	


bool gameWon (gm *gamenode) {
	if (gamenode->field[0] == gamenode->field[1] 
		&& gamenode->field[1] == gamenode->field[2]
		&& gamenode->field[2] == gamenode->field[3]){
			gamenode->terminal = true;
			return gamenode->terminal;
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
	scanf ("%zu", &play_input);
	getchar ();
	gamenode->field[play_input] = max;
}


void printBoard (gm *gamenode) {
	for (int i = 0; i < 4; ++i) {
		printf("%hu", gamenode->field[i]);
	}
	printf("\n");
}


Score minimax (gm *gamenode) {
	if (gameWon (gamenode)) {
		if (gamenode->player == min) return loss;
		if (gamenode->player == max) return win;
	} 
	if (numberOfNodes (gamenode) == 0) return draw;
	numberOfNodes(gamenode);
	int *a;
	a = malloc(sizeof(gamenode->possible_nodes));
	if (gamenode->player == max) {
		for (int i = 0; i < gamenode->possible_nodes; ++i) {
			a[i] = minimax (gamenode->node[i]);
		}
		return maxValue (a, gamenode->possible_nodes);
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
	free(newGame);

}