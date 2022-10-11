#include <stdint.h>
#include <stdlib.h> // rand
#include <stdbool.h>
#include <cmsis_gcc.h>
#include "main.h"
#include "pong_main.h"
#include "pong_gameplay.h"
#include "display_DOGS_102.h"
#include "snake_enums.h"
#include "quadknob.h"
#include "circle_queue.h"
#include "Pong_Keypad_Input.h"

///////////////////////////
// Test -without input, the expected output = snake goes straight ahead every 1/2 second.
// Without_Input - Works!
//#define TEST_WITHOUT_INPUT

// Test - with input: ... (a) Slithering is OK!
// (b) Turning works - 1 or several detents turn correctly, reliably.
// (c) New fruit is visible.
// (d) The tail of the snake follows the head correctly.
// (e) the display sometimes flips to 12-o'clock position instead of
// 6 o'clock? SUSPICIOUS - wiring/ground at the knob... when I am gentle
// this does not happen. ACCEPTABLE.

extern volatile int32_t timer_isr_countdown; // Required to control timing
const int pong_board_size = CHECKS_WIDE; // Provided for extern

void ram_health(uint16_t dummy_var, uint16_t pattern){
	// DEBUGGING PHASE: LOCK UP THE PROGRAM if RAM is corrupted.
	if (dummy_var != pattern){
		while(1);
	}
}


void pong_main(void){
	const int32_t timer_isr_500ms_restart = 500;
	const int32_t timer_isr_2000ms_restart = 2000;

	// INITIALIZE THE GAME
	// Construct the model "game" object:
	pong_game my_game;
	volatile uint16_t ram_dummy_1 = MEMORY_BARRIER_1;
	pong_init(&my_game);

//	// Construct IPC
//	Smc_queue turn_q;
//	smc_queue_init(&turn_q);

	// Button queue
	Smc_queue button_queue;
	volatile uint16_t ram_dummy_2 = MEMORY_BARRIER_2;
	// smc_queue_init(&button_queue);

	// Input object
//	QuadKnob user_knob_1;
//	volatile uint16_t ram_dummy_3 = MEMORY_BARRIER_3;
//	quadknob_init(&user_knob_1);
	Pong_Keypad_Input input_1;
	volatile uint16_t ram_dummy_3 = MEMORY_BARRIER_3;
	Pong_Keypad_Input_init(&input_1);

	// Output object
	// Block all interrupts while initializing - initial protocol timing is critical.
	__disable_irq();
	display_init();
	__enable_irq();

	// Welcome screen = checkerboard for 2 seconds.
	timer_isr_countdown = timer_isr_2000ms_restart;
	Matrix_Initialize_Test();
	while (timer_isr_countdown > 0){}
	timer_isr_countdown = timer_isr_500ms_restart;
	// Confirm all the rules and paint the initial pong.
	display_blank();
	//pong_game_cleanup(&my_game);

	// OPERATE THE GAME
	int32_t prior_timer_countdown = timer_isr_countdown;

	while(1){
		ram_health(ram_dummy_1, MEMORY_BARRIER_1);
		ram_health(ram_dummy_2, MEMORY_BARRIER_2);
		ram_health(ram_dummy_3, MEMORY_BARRIER_3);

	// ASSERT TIMER COUNTDOWN IN RANGE
		if ((timer_isr_countdown > timer_isr_500ms_restart)||
				(timer_isr_countdown < 0)){
			display_checkerboard();
			while(1);
		}

#ifndef TEST_WITHOUT_INPUT

		// If a player has won, display their victory instead of doing other things
		if (my_game.p1.score >= 1) {
			Matrix_LED_DISPLAY_PLAYER_ONE_WIN();
		}
		else if (my_game.p2.score >= 1) {
			Matrix_LED_DISPLAY_PLAYER_TWO_WIN();
		}
		else {
			// Check for user input every 1 ms & paint one block of the display.
			if (prior_timer_countdown != timer_isr_countdown ){
				prior_timer_countdown = timer_isr_countdown;
				// If time changed, about 1 ms has elapsed.
				// Once each 1 ms, read input pins from user knob and then
				// update "knob" object (which debounces each input pin and
				// then calculates user command).

//				bool user_knob_1_pin_A = (GPIO_PIN_SET == HAL_GPIO_ReadPin(QuadKnobA_GPIO_Port, QuadKnobA_Pin));
//				bool user_knob_1_pin_B = (GPIO_PIN_SET == HAL_GPIO_ReadPin(QuadKnobB_GPIO_Port, QuadKnobB_Pin));
//				user_knob_1.update(&user_knob_1, user_knob_1_pin_A, user_knob_1_pin_B);
				keypad_Inputs(&input_1, &button_queue);

				// Get user command from "knob" - if any action, make it a queue packet and then mail it.
//				if (user_knob_1.get(&user_knob_1) != QUADKNOB_STILL){
//					Q_data command_packet;
//					command_packet.twist = user_knob_1.get(&user_knob_1);
//					turn_q.put(&turn_q, &command_packet);
//				}

				pong_paddle_update(&my_game, &button_queue);

				// ASSERT THAT THE PADDLES ARE IN THE RIGHT PLACE HORIZONTALLY
				while ((my_game.p1.location.x != 0) || (my_game.p2.location.x != (CHECKS_WIDE-1)));

				Matrix_LED_DISPLAY_PONG(my_game.p1.location.y, my_game.p2.location.y, my_game.ball.location.x, my_game.ball.location.y);
				//incremental_show_snake((const snake_game *)&my_game, false);	// TODO: replace this
			}
			if (timer_isr_countdown <= 0) {
				// Move and animate every 500 ms
				timer_isr_countdown = timer_isr_500ms_restart;
				pong_periodic_play(&my_game);
				//incremental_show_snake(&my_game, true);	// TODO: replace this
			}
		}


#endif
#ifdef TEST_WITHOUT_INPUT
		static int turns = 0;
		// Normally "check for user input every 1 ms & show" - here just update display
		if (prior_timer_countdown != timer_isr_countdown ){
			prior_timer_countdown = timer_isr_countdown;
			incremental_show_snake(&my_game, false);
		}
		if (timer_isr_countdown <= 0) {
			// Move and animate every 500 ms
			timer_isr_countdown = timer_isr_500ms_restart;
			if (turns < 3){
				turns ++;
				snake_periodic_play(&my_game);
			}
			else {
				turns = 0;
				Q_data command_packet = {.twist = QUADKNOB_CW};
				turn_q.put(&turn_q, &command_packet);
				snake_heading_update(&my_game, &turn_q);
				snake_periodic_play(&my_game);
			}
			incremental_show_snake(&my_game, true);
		}
#endif
	}
}

// Time-wasting counter as delay (about 2 seconds).
// for (uint32_t i = 0; i < 2345678; i++){;} // pause several sec b4 repeat all
