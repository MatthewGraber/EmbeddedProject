/*
 * pong_gameplay.c
 *
 *  Created on: Sep 27, 2022
 *      Author: mbgraber19
 */
#include "pong_gameplay.h"
#include "main.h"
#include "pong_main.h"

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
	game->ball.verticalVelocity = 1;	//No vertical movement initially

}

void pong_paddle_update(pong_game* game, Smc_queue* queue) {
	Q_data message;
	bool data_available;
	data_available = queue->get(queue, &message);
	if (data_available) {

		// P1 controls
		if (message.int_val & (1<<0) && (game->p1.location.y > 0)) {
			game->p1.location.y--;
		}
		else if (message.int_val & (1<<1) && (game->p1.location.y < (CHECKS_WIDE-PADDLE_LENGTH))) {
			game->p1.location.y++;
		}

		// P2 controls
		if (message.int_val & (1<<2) && (game->p2.location.y > 0)) {
			game->p2.location.y--;
		}
		else if (message.int_val & (1<<3) && (game->p2.location.y < (CHECKS_WIDE-PADDLE_LENGTH))) {
			game->p2.location.y++;
		}

	}
}

// Will be called every 500ms
void pong_periodic_play(pong_game* game, bool* paddle_hit) {
	// Get a fresh plot of the board to check for legal & fruit moves:
	static int8_t board[CHECKS_WIDE][CHECKS_WIDE];
	// Always clear the board and redraw it.
	for (int x = 0; x < CHECKS_WIDE; x++){
		for (int y = 0; y < CHECKS_WIDE; y++){
			board[x][y] = 0;
		}
	}

	// Mark the location of the paddles with 1s
	board[game->p1.location.x][game->p1.location.y	] = 1;
	board[game->p1.location.x][game->p1.location.y+1] = 1;
	board[game->p2.location.x][game->p2.location.y	] = 1;
	board[game->p2.location.x][game->p2.location.y+1] = 1;

	// Mark the location of the ball with a -1
	board[game->ball.location.x][game->ball.location.y] = -1;

	// Determine the new location of the ball
	XY_PT ballNewLocation;
	ballNewLocation.x = game->ball.location.x;
	ballNewLocation.y = game->ball.location.y + game->ball.verticalVelocity;

	// If the new location is outside or on the edge of the border, bounce it
	if (ballNewLocation.y >= CHECKS_WIDE-1) {
		// Reverse ball velocity
		game->ball.verticalVelocity = -game->ball.verticalVelocity;
		ballNewLocation.y += (CHECKS_WIDE-1) - ballNewLocation.y;
	}
	else if (ballNewLocation.y <= 0) {
		game->ball.verticalVelocity = -game->ball.verticalVelocity;
		ballNewLocation.y -= ballNewLocation.y;
	}

	// Move the ball horizontally
	ballNewLocation.x += (game->ball.goingRight)?(1):(-1);

	// Check to see if the ball has collided with a paddle
	if (board[ballNewLocation.x][ballNewLocation.y] == 1) {
		game->ball.goingRight ^= 1;	// Reverse ball direction
		ballNewLocation.x += (game->ball.goingRight)?(2):(-2);	// Bounce it
		*paddle_hit = true;
	}
	
	// TODO: Decide if this should happen now, or later so the player can see the ball move into the space
	else if (ballNewLocation.x <= 0) {
		game->p1.score++;
		// TODO: Victory check function
		// TODO: Reset function
	}
	else if (ballNewLocation.x >= CHECKS_WIDE-1) {
		game->p2.score++;
		// TODO: Victory check function
		// TODO: Reset function
	}

	game->ball.location.x = ballNewLocation.x;
	game->ball.location.y = ballNewLocation.y;
}
