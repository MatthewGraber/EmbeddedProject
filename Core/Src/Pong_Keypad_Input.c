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
//uint16_t flag = 1;
uint32_t second;
uint32_t first;
Q_data state;

void Pong_Keypad_Input_init(Pong_Keypad_Input *self){
	self->update = &keypad_Inputs;
	//self->get = Pong_Keypad_Input_get;
	state.int_val = 0x0;
}


void keypad_Inputs(Pong_Keypad_Input *self, Smc_queue *pass){
	//if(flag == 1){
	//	flag = 0;
	//}else{
	//	flag = 1;
	//}
	//Set column one to a pulled down output
		//GPIOD->MODER |= (1<<8); //Sets PA4 to Output
		//GPIOD->OSPEEDR |= (1 << 8);
		//GPIOD->OSPEEDR |= (1 << 9);
		//GPIOD->MODER &= ~(1<<12); //Sets PA6 to Input
		//GPIOD->PUPDR |= (1<<9); //Sets PA4 to have pull down
		//GPIOD->PUPDR &= ~(1<<8); //Sets PA4 to have pull down
		//GPIOD->PUPDR |= (1<<13);  //Sets PA6 to have pull up
		//GPIOD->PUPDR &= ~(1<<12);  //Sets PA6 to have pull up
		//GPIOD->PUPDR &= ~(1<<13);
		//GPIOD->PUPDR |= (1<<12);
	// for(int x = 0; x <=12345; x++){}
		first = GPIOD->IDR;

		GPIOD->MODER |= (1<<12); //Sets PD6 to Output
		GPIOD->OSPEEDR |= (1 << 12);
		GPIOD->OSPEEDR |= (1 << 13);
		GPIOD->MODER &= ~(1<<8); //Sets PD4 to Input
		GPIOD->PUPDR |= (1<<13); //Sets PD6 to have pull down
		GPIOD->PUPDR &= ~(1<<12); //Sets PD6 to have pull down
		GPIOD->PUPDR |= (1<<8);  //Sets PD4 to have pull up
		GPIOD->PUPDR &= ~(1<<9); //Sets PD4 to have pull up
	// for(int x = 0; x <=12345; x++){}
		//second = GPIOD->IDR;

		state.int_val = 0x0;
		//if(flag == 1){
			if((first == 0x42) && (second == 0x32)){         //Button 1
				state.int_val += 0x1;
			}
			if((first == 0x62) && (second == 0x22)){         //Button 7
				state.int_val += 0x2;
			}
		//}

		//if(flag == 0){
			if((first == 0x62) && (second == 0x12)){         //Button 3
				state.int_val += 0x4;
			}
			
			if((first == 0x22) && (second == 0x32)){         //Button 9
				state.int_val += 0x8;
			}
		//}
		self->push = state.int_val;
		//const Q_data *data = &state;
		pass->put(pass, &state);

		second = GPIOD->IDR;

				GPIOD->MODER |= (1<<8); //Sets PD4 to Output
				GPIOD->OSPEEDR |= (1 << 8);
				GPIOD->OSPEEDR |= (1 << 9);
				GPIOD->MODER &= ~(1<<12); //Sets PD6 to Input
				GPIOD->PUPDR |= (1<<9); //Sets PD4 to have pull down
				GPIOD->PUPDR &= ~(1<<8); //Sets PD4 to have pull down
				GPIOD->PUPDR |= (1<<13);  //Sets PD6 to have pull up
				GPIOD->PUPDR &= ~(1<<12);  //Sets PD6 to have pull up
				GPIOD->PUPDR &= ~(1<<13);
				GPIOD->PUPDR |= (1<<12);

}

//int Pong_Keypad_Input_get(const Pong_Keypad_Input *self){
//	return self->push;
//}




