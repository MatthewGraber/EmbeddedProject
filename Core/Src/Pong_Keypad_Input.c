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
#include "circle_queue.h"
//int paddle1; // -1 = down, 0 = still, 1 = up
//int paddle2; // -1 = down, 0 = still, 1 = up
uint32_t second;
uint32_t first;
Q_data state;

void Pong_Keypad_Input_init(Pong_Keypad_Input *self){
	self->update = &keypad_Inputs;
	self->get = Pong_Keypad_Input_get;
	state.int_val = 0x0;
}


void keypad_Inputs(Pong_Keypad_Input *self, Smc_queue *pass){
	//Set column one to a pulled down output
		GPIOA->MODER |= (1<<10); //Sets PD5 to Output
		GPIOA->OSPEEDR |= (1 << 10);
		GPIOA->OSPEEDR |= (1 << 11);
		GPIOA->MODER &= ~(1<<6); //Sets PD3 to Input
		GPIOA->PUPDR |= (1<<11); //Sets PD5 to have pull down
		GPIOA->PUPDR &= ~(1<<10); //Sets PD5 to have pull down
		GPIOA->PUPDR |= (1<<6);  //Sets PD3 to have pull up
		GPIOA->PUPDR &= ~(1<<7);  //Sets PD3 to have pull up

		first = GPIOA->IDR;

		GPIOA->MODER |= (1<<6); //Sets PD3 to Output
		GPIOA->OSPEEDR |= (1 << 6);
		GPIOA->OSPEEDR |= (1 << 7);
		GPIOA->MODER &= ~(1<<10); //Sets PD5 to Input
		GPIOA->PUPDR |= (1<<7); //Sets PD3 to have pull down
		GPIOA->PUPDR &= ~(1<<6); //Sets PD3 to have pull down
		GPIOA->PUPDR |= (1<<10);  //Sets PD5 to have pull up
		GPIOA->PUPDR &= ~(1<<11); //Sets PD5 to have pull up

		second = GPIOA->IDR;

		state.int_val = 0x0;

		if((first == 0x10) && (second == 0x4030)){         //Button 1
			state.int_val += 0x1;
		}
		if((first == 0x4000) && (second == 0x4030)){         //Button 7
			state.int_val += 0x2;
		}


		if((first == 0x4018) && (second == 0x10)){         //Button 3
					state.int_val += 0x4;
			}
			if((first == 0x4018) && (second == 0x4000)){         //Button 9
				state.int_val += 0x8;
			}

		self->push = state.int_val;
		const Q_data *data = &state;
		pass->put(&pass, data);

}

int Pong_Keypad_Input_get(const Pong_Keypad_Input *self){
	return self->push;
}




