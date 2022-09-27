int Matrix_Initialize_Test(void)
{
  GPIOC->ODR = 255; //SET GPIOC ENTIRE REGISTER HIGH
  GPIOB->ODR =	0;	//SET GPIOB ENTIRE REGISTER LOW


  

	  for (volatile uint8_t LED_MATRIX_ROW = 0; LED_MATRIX_ROW <= 7; LED_MATRIX_ROW++)
	  {		//BEGIN ROW FOR LOOP
		GPIOB->ODR |= (1<<LED_MATRIX_ROW); 		 //ENABLE CURRENT LED ROW
		
		for (volatile uint8_t LED_MATRIX_COLUMN = 0; LED_MATRIX_COLUMN <= 7; LED_MATRIX_COLUMN++)
		{		 //BEGIN COLUMN FOR LOOP
			GPIOC->ODR &=~(1<<LED_MATRIX_COLUMN); 					//ENABLE LED COLUMN
			for (volatile uint32_t n = 0; n < 212357; n++);			 //STALL FOR TIME
			
			GPIOC->ODR |= (1<<LED_MATRIX_COLUMN); 					//DISABLE LED COLUMN
			for (volatile uint32_t n = 0; n < 212357; n++); 		// STALL FOR TIME
		} 		//END COLUMN FOR LOOP
		GPIOB->ODR &=~(1<<LED_MATRIX_ROW); 			//DISABLE CURRENT LED ROW
	  } 		//END ROW FOR LOOP
}
