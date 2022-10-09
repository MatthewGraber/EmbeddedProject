/*
 * buzzer.c
 *
 *  Created on: Oct 4, 2022
 *      Author: rcsmith20
 */

//this buzzes pin a5 at a certain frequency
void buzzFreq()
{
	for(uint16_t i = 0; i<500;i++){}
	GPIOA->ODR |= 1<<5;
	for(uint16_t i = 0; i<500;i++){}
	GPIOA->ODR &= (1<<5);
}
