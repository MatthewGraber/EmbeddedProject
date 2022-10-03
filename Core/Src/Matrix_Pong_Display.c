/*
 * Matrix_Pong_Display.c
 *
 *  Created on: Oct 3, 2022
 *      Author: michael Hudson
 */

/*GPIOC->ODR = 255; //SET GPIOC ENTIRE REGISTER HIGH
GPIOB->ODR = 0;	//SET GPIOB ENTIRE REGISTER LOW*/
#include "main.h"
void Matrix_LED_DISPLAY_PONG( int L_PADDLE_Y_COORDINATE, int R_PADDLE_Y_COORDINATE, int BALL_X_COORDINATE, int BALL_Y_COORDINATE)
{//Start Function
		  for (volatile int LED_MATRIX_COLUMN = 0; LED_MATRIX_COLUMN <= 7; LED_MATRIX_COLUMN++)
		  {		//Begin for LOOP
			GPIOC->ODR &=~(1<<LED_MATRIX_COLUMN); 			//ENABLE CURRENT LED COLUMN
			//if (LED_MATRIX_COLUMN == 0) // display left paddle
			//{//Begin if 1

				//	if (BALL_X_COORDINATE == 0) // Check to see if ball is on paddle coordinate
				//{//Begin if 1.2

				//}//End if 1.2

			//}//End if 1

			//if (LED_MATRIX_COLUMN !=0){
			//if (LED_MATRIX_COLUMN !=7){
			//if (LED_MATRIX_COLUMN == BALL_X_COORDINATE) // If the ball isnt in the same column as the paddle, display ball
			//{//Begin if 2

			//}}}//End if 2

			//if (LED_MATRIX_COLUMN == 7) // display right paddle
			//{//Begin if 3

				//	if (BALL_X_COORDINATE == 7) // Check to see if ball is on paddle coordinate
				//{//Begin if 3.2

				//}//End if 3.2

			//}//End if 3


			GPIOC->ODR |= (1<<LED_MATRIX_COLUMN); 		 //DISABLE CURRENT LED COLUMN
			GPIOB->ODR = 0;								 //RESET ROW
		  }  //END For Loop
}//End Function
