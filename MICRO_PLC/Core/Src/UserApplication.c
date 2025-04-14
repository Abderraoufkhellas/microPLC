/*
 * UserApplication.c
 *
 *  Created on: Apr 10, 2025
 *      Author: pc
 */
#include "UserApplication.h"
/* THIS FILE IS FOR THE USER TO PROGRAM*/


/* -----------------------------------------------------------------------
 1-DECLARE VARIABLES AND INSTALL THEM
 eg: IO Valve;
 	 void setup(void) {
 	 Valve= install_digital_output(your arguments)
 	 }

 2-DEFINE LOGIC in functions


 -------------------------------------------------------------------------*/
/*CODE STARTS HERE*/
IO Valve;
IO Valve2;
IO Button;

TIM TIMER1;
TIM TIMER2;


void setup (void ) {
	Valve =install_digital_output(GPIO_PIN_12);
	Valve2 =install_digital_output(GPIO_PIN_13);
	Button=install_digital_input(GPIO_PIN_0);
	TIMER1=add_TOFF(2000);

}

void loop(void) {

	if (NOT Button->value){
		Valve->value=1;
	}
	else {
		Valve->value=0;
	}
}
