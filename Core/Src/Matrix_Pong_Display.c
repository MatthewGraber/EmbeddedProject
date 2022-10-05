/*
 * Matrix_Pong_Display.c
 *
 *  Created on: Oct 3, 2022
 *      Author: michael Hudson
 */
#include "main.h"


//Both paddles should never change their x coordinates
//A ball should never have the same y and x coordinate as a paddle, and a  y+1 and x coordinate as a paddle
//Both paddle coordinates should be greater than negative one, and less than 7

/* Assumed initial states of register for working function
 * GPIOC->ODR = 255; //SET GPIOC ENTIRE REGISTER HIGH
GPIOB->ODR = 0;	//SET GPIOB ENTIRE REGISTER LOW*/

void Matrix_LED_DISPLAY_PONG( int L_PADDLE_Y_COORDINATE, int R_PADDLE_Y_COORDINATE, int BALL_X_COORDINATE, int BALL_Y_COORDINATE)
{//Start Function
		  for (volatile int LED_MATRIX_COLUMN = 0; LED_MATRIX_COLUMN <= 7; LED_MATRIX_COLUMN++)
		  {		//Begin for LOOP
			GPIOC->ODR &=~(1<<LED_MATRIX_COLUMN); 			//ENABLE CURRENT LED COLUMN
			if (LED_MATRIX_COLUMN == 0) // display left paddle if statement
			{//Begin if 1
				if (BALL_X_COORDINATE == 0) // Check to see if ball is on paddle coordinate
					{//Begin if 1.2
					GPIOB->ODR |= (1<<BALL_Y_COORDINATE);// Display Ball
					}//End if 1.2
			GPIOB->ODR |= (3<<L_PADDLE_Y_COORDINATE);
			}//End if 1

			if (LED_MATRIX_COLUMN !=0){
				if (LED_MATRIX_COLUMN !=7){
					if (LED_MATRIX_COLUMN == BALL_X_COORDINATE) // If the ball isn't in the same column as a paddle, display ball
						{//Begin if 2
						GPIOB->ODR |= (1<<BALL_Y_COORDINATE);// Display Ball
						}}}//End if 2

			if (LED_MATRIX_COLUMN == 7) // display right paddle if statement
			{//Begin if 3

				if (BALL_X_COORDINATE == 7) // Check to see if ball is on paddle coordinate
				{//Begin if 3.2
				GPIOB->ODR |= (1<<BALL_Y_COORDINATE);// Display Ball
				}//End if 3.2
			GPIOB->ODR |= (3<<R_PADDLE_Y_COORDINATE);// Display Right Paddle
			}//End if 3


			GPIOC->ODR |= (1<<LED_MATRIX_COLUMN); 		 //DISABLE CURRENT LED COLUMN
			GPIOB->ODR = 0;								 //RESET ROW
		  }  //END For Loop
}//End Function


void Matrix_LED_DISPLAY_PLAYER_ONE_WIN() // Display P1
{//Start Function
	for (volatile int LED_MATRIX_COLUMN = 0; LED_MATRIX_COLUMN <= 7; LED_MATRIX_COLUMN++)
	{//Begin for LOOP
		GPIOC->ODR &=~(1<<LED_MATRIX_COLUMN); 		//ENABLE CURRENT LED COLUMN
		int LED_PLAYER_WIN_ROW_VALUE[8]={126,10,14,0,126,0,0,0};
		GPIOB->ODR =LED_PLAYER_WIN_ROW_VALUE[LED_MATRIX_COLUMN];
		GPIOC->ODR =255;							// RESET COLUMN
		GPIOB->ODR = 0;								 //RESET ROW
	} //END For Loop
}//End Function


void Matrix_LED_DISPLAY_PLAYER_TWO_WIN() // Display P2
{//Start Function
	for (volatile int LED_MATRIX_COLUMN = 0; LED_MATRIX_COLUMN <= 7; LED_MATRIX_COLUMN++)
	{//Begin for LOOP
		GPIOC->ODR &=~(1<<LED_MATRIX_COLUMN); 		//ENABLE CURRENT LED COLUMN
		int LED_PLAYER_WIN_ROW_VALUE[8]={126,10,14,0,114,82,94,0};  // Register values for propper row lights
		GPIOB->ODR =LED_PLAYER_WIN_ROW_VALUE[LED_MATRIX_COLUMN];  // Enable Row
		GPIOC->ODR =255;							// RESET COLUMN
		GPIOB->ODR = 0;								 //RESET ROW
	} //END For Loop
}//End Function
















