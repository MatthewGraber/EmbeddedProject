/*
 *
 *
 *
 *
 *
 *
 *
 *
 */

#include <Pong_Keypad_Input.h>
#include "main.h"
//int paddle1; // -1 = down, 0 = still, 1 = up
//int paddle2; // -1 = down, 0 = still, 1 = up
uint32_t second;
uint32_t first;
uint16_t state;

void Pong_Keypad_Input_init(Pong_Keypad_Input *self){
	self->update = &keypad_Inputs;
	self->get = Pong_Keypad_Input_get;
	state = 0x0;
}


void keypad_Inputs(Pong_Keypad_Input *self){
	//Set column one to a pulled down output
		GPIOB->MODER |= (1<<10); //Sets PD5 to Output
		GPIOB->OSPEEDR |= (1 << 10);
		GPIOB->OSPEEDR |= (1 << 11);
		GPIOB->MODER &= ~(1<<6); //Sets PD3 to Input
		GPIOB->PUPDR |= (1<<11); //Sets PD5 to have pull down
		GPIOB->PUPDR &= ~(1<<10); //Sets PD5 to have pull down
		GPIOB->PUPDR |= (1<<6);  //Sets PD3 to have pull up
		GPIOB->PUPDR &= ~(1<<7);  //Sets PD3 to have pull up

		first = GPIOB->IDR;

		GPIOB->MODER |= (1<<6); //Sets PD3 to Output
		GPIOB->OSPEEDR |= (1 << 6);
		GPIOB->OSPEEDR |= (1 << 7);
		GPIOB->MODER &= ~(1<<10); //Sets PD5 to Input
		GPIOB->PUPDR |= (1<<7); //Sets PD3 to have pull down
		GPIOB->PUPDR &= ~(1<<6); //Sets PD3 to have pull down
		GPIOB->PUPDR |= (1<<10);  //Sets PD5 to have pull up
		GPIOB->PUPDR &= ~(1<<11); //Sets PD5 to have pull up

		second = GPIOB->IDR;

		if((first == 0x10) && (second == 0x4030)){         //Button 1
			state = 0x1;
		}
		if((first == 0x4000) && (second == 0x4030)){         //Button 7
			state = 0x2;
		}
		if((first == 0x4018) && (second == 0x4030)){
				state = 0x0;
			}

		if((first == 0x4018) && (second == 0x10)){         //Button 3
					state = 0x4;
			}
			if((first == 0x4018) && (second == 0x4000)){         //Button 9
				state = 0x8;
			}
			if((first == 0x4010) && (second == 0x4010)){
				state = 0x0;
			}
		self->push = state;

}

int Pong_Keypad_Input_get(const Pong_Keypad_Input *self){
	return self->push;
}



