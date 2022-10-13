/*
 * buzzer.c
 *
 *  Created on: Oct 9, 2022
 *      Author: rcsmith20
 */
#include "stm32g0xx.h"
#include "buzzer.h"

void buzzer(bool collision)
{

	if (collision)
	{
		if((1<<9) & (GPIOB->ODR))
		{
			GPIOB->ODR &= ~(1<<9);
		}
		else
		{
			GPIOB->ODR |= (1<<9);
		}



		//GPIOB_ODR ^= (1<<9);
	}
}

//set the buzzer_queue to 0 when there is no collision and 1 when you have a collision
//buzzer_queue->put(buzzer_queue,collision);
