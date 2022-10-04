/*
 * pong_gameplay.h
 *
 *  Created on: Sep 27, 2022
 *      Author: mbgraber19
 */

#ifndef CORE_INC_PONG_GAMEPLAY_H_
#define CORE_INC_PONG_GAMEPLAY_H_

#define PADDLE_LENGTH 2

typedef struct {int16_t x; int16_t y;} XY_PT;

typedef struct {
	bool goingRight;
	int8_t verticalVelocity;
	XY_PT location;
} Ball;

typedef struct {
	XY_PT location;
	uint8_t score;
} Player;

typedef struct {
	Player p1;
	Player p2;
	Ball ball;
} pong_game;

void pong_init(pong_game*);
void pong_paddle_update(pong_game*, Smc_queue*);
void pong_perodic_play(pong_game*);


#endif /* CORE_INC_PONG_GAMEPLAY_H_ */
