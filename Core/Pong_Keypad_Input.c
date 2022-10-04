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
int paddle1; // -1 = down, 0 = still, 1 = up
int paddle2; // -1 = down, 0 = still, 1 = up
uint32_t first;
uint32_t second;

void keypad_Inputs(){
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
			paddle1 = 1;
		}
		if((first == 0x4000) && (second == 0x4030)){         //Button 7
			paddle1 = -1;
		}
		if((first == 0x4018) && (second == 0x4030)){        //Probably have to change this
				paddle1 = 0;
				paddle2 = 0;
			}

		if((first == 0x4018) && (second == 0x10)){         //Button 3
					paddle2 = 1;
			}
			if((first == 0x4018) && (second == 0x4000)){         //Button 9
				paddle2 = -1;
			}
			if((first == 0x4010) && (second == 0x4010)){   //Same as above probably wrong
				paddle1 = 0;
				paddle2 = 0;
			}
}
