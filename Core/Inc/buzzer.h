/*
 * buzzer.h
 *
 *  Created on: Oct 9, 2022
 *      Author: rcsmith20
 */

#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include <stdint.h>
#include <stdbool.h>
#include "snake_enums.h"

//initilize the queue for it
Smc_queue* buzzer_queue;
smc_queue_init(buzzer_queue);


#endif /* INC_BUZZER_H_ */
