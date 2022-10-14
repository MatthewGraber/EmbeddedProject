/*
 * Matrix_Pong_Display.h
 *
 *  Created on: Oct 3, 2022
 *      Author: mkhudson17
 */

#ifndef INC_MATRIX_PONG_DISPLAY_H_
#define INC_MATRIX_PONG_DISPLAY_H_

void Matrix_LED_DISPLAY_PONG( const uint8_t L_PADDLE_Y_COORDINATE,const  uint8_t R_PADDLE_Y_COORDINATE, const uint8_t BALL_X_COORDINATE, const uint8_t BALL_Y_COORDINATE);
void Matrix_LED_DISPLAY_PLAYER_ONE_WIN();
void Matrix_LED_DISPLAY_PLAYER_TWO_WIN();
void Matrix_Initialize_Test();

#endif /* INC_MATRIX_PONG_DISPLAY_H_ */
