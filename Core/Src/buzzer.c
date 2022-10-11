/*
 * buzzer.c
 *
 *  Created on: Oct 9, 2022
 *      Author: rcsmith20
 */
#include "stm32g0xx.h"
#include "buzzer.h"

void buzzer(int collision)
{
	bool error = false;
	Q_data q;
	q.int_val = collision;
	//need a certain queue for the data
	error = buzzer_queue->get(buzzer_queue, &q);

	if (collision == 1)
	{
		if((1<<6) & (GPIOA->BSRR))
		{
			GPIOA->BSRR |= (1<<6);
		}
		else
		{
			GPIOA->BSRR &= ~(1<<6);
		}



		//GPIOA_ODR ^= (1<<6);
	}
}

//set the buzzer_queue to 0 when there is no collision and 1 when you have a collision
//buzzer_queue->put(buzzer_queue,collision);
