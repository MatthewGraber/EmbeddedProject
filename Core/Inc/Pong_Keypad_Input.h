/*
 * Quadknob.h
 *
 *  Created on: Oct 3, 2022
 *      Author: Zach Brickler
 *
 *   Contains DebouncedEdgeDetector and QuadKnob
 */

#ifndef INC_PONG_KEYPAD_INPUT_H_
#define INC_PONG_KEYPAD_INPUT_H_

#include "main.h"
enum Move {upPad1, downPad1, upPad2, downPad2, still1, still2};

typedef
		struct Pong_Keypad_Input_struct{
		int push;
		void (*update)(struct Pong_Keypad_Input_struct *self);
		int (*get)(const struct Pong_Keypad_Input_struct *self);
}Pong_Keypad_Input;


// Methods for Pong_Keypad_Input
void keypad_Inputs(Pong_Keypad_Input *self, Smc_queue *pass);
int Pong_Keypad_Input_get(const Pong_Keypad_Input *self);
void Pong_Keypad_Input_init(Pong_Keypad_Input *self);


///////////////////////////////////////////////////////////////////////////////


#endif /* INC_PONG_KEYPAD_INPUT_H_ */
