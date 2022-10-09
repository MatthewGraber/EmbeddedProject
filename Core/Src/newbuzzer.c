/*
 * buzzer.c
 *
 *  Created on: Oct 9, 2022
 *      Author: rcsmith20
 */


Smc_queue* buzzer_queue;
smc_queue_init(buzzer_queue);
void buzzer(int collision)
{
	bool error = false;
	//need a certain queue for the data
	error = buzzer_queue->get(buzzer_queue,collision);

	if (collision == 1)
	{
		GPIOx_ODR ^= (1<<5);
	}
}

//set the buzzer_queue to 0 when there is no collision and 1 when you have a collision
//buzzer_queue->put(buzzer_queue,collision);
