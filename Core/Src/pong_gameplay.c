/*
 * pong_gameplay.c
 *
 *  Created on: Sep 27, 2022
 *      Author: mbgraber19
 */
#include "pong_gameplay.h"

void pong_init(pong_game* game) {

	// Initialize starting locations
	const XY_PT p1start = {0, 4};
	const XY_PT p2start = {7, 4};
	const XY_PT ballStart = {4, 4};

	game->p1.location = p1start;
	game->p2.location = p2start;
	game->ball.location = ballStart;

	//Initialize scores
	game->p1.score = 0;
	game->p2.score = 0;

	//Initialize ball parameters
	game->ball.goingRight = false;		//To the left, to the left
	game->ball.verticalVelocity = 0;	//No vertical movement initially

}

void pong_paddle_update(pong_game* game, Smc_queue* queue) {
	Q_data message;
	bool data_available;
	data_available = queue->get(queue, &message);
	if (data_available) {
		//
		// SUPER COOL CODE THAT CHECKS THE MESSAGE AND MOVES THE
		// PADDLES ACCORDINGLY
		//
	}
}

void pong_periodic_play(pong_game* game) {
	static int8_t board[CHECKS_WIDE][CHECKS_WIDE];
}
