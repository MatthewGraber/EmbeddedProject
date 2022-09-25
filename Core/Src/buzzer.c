/*
 * buzzer.c
 *
 *  Created on: Sep 25, 2022
 *      Author: rcsmith20
 */
#include <stdint.h>
#include "main.h"
void buzzer1(void)
{
    for (volatile uint16_t n = 0; n < 500; n++);
    GPIOA->ODR |= (1<<5);
    for (volatile uint16_t n = 0; n < 500; n++);
    GPIOA->ODR &= ~(1<<5);
}
