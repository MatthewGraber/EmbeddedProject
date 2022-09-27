/*
 * pong_gameplay.h
 *
 *  Created on: Sep 27, 2022
 *      Author: mbgraber19
 */

#ifndef CORE_INC_PONG_GAMEPLAY_H_
#define CORE_INC_PONG_GAMEPLAY_H_

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

void pong_init();
void pong_perodic();
void move_ball();


#endif /* CORE_INC_PONG_GAMEPLAY_H_ */
