/*
 * cricle_queue.c
 *
 *  Created on: Sep 29, 2022
 *      Author: rcsmith20
 */

#include "circle_queue.h"
#include "snake_enums.h"

Smc_queue* smc_queue_init(Smc_queue* Q) {
	Q->head = 0;
	Q->tail = 0;
	Q->cap = SMC_Q_BUFSIZE;
	Q->burden = 0;
	Q->put = &(smc_queue_put);
	Q->get = &(smc_queue_get);
	Q->peek = &(smc_queue_peek);

	return Q;
}

bool smc_queue_put(Smc_queue *q, const Q_data *msg)
{
    //have to initialize success
    bool success = false;
    //if there is no room in the queue then return false
    if (q->burden>=(q->cap))
    {
        success = false;
    }
    else
    {

        //since we are adding elements need to add to burden

         //puts the message in the array
		 q->buffer[q->tail] = *msg;

		 //if the tail is out of range of the array then i set the tail back to zero
		 if (q->tail == (q->cap)-1)
		 {
		     q->tail =0;
		 }
		 else
		 {
		     q->tail += 1;
		 }
		 //burden is the amount of elements in the array
		 //and i moved it from the top of the else statement if the file stops working
		 q-> burden += 1;
		 success = true;
    }
    return success;
}

//gets message out of the queue

bool smc_queue_get(Smc_queue *q, Q_data  *msg){
	bool success = false;
	// if there is no value in the queue then return false
	if (q->burden == 0)
	{
	    success= false;
    }
	else
	{
	    *msg = q->buffer[q->head];
	    q-> burden -= 1;
		if(q->head >= (q->cap)-1)
		{
		    //the head is set to -1 because i add one right after if statement
		    //and it doesn't work
		    q->head = -1;
		}
		// shift the head to the right
		q-> head += 1;


		success = true;
	}
	return success;
}

bool smc_queue_peek(const Smc_queue *q, Q_data  *msg){
	bool success = false;
	// FIRST check if there is data in the queue
	if (q->burden == 0) success = false;
	// If YES - copy data but do not modify anything.
	else {
		*msg = q->buffer[0];
		success = true;
	}
	return success;
}
