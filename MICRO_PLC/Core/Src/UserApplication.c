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
	Valve= install_digital_output("Valve1", GPIO_PIN_12);
	Button= install_digital_input("Button",GPIO_PIN_0);
	TIMER1=add_TON(2000);

}

void loop(void) {

	Valve->value=Button->value;

}
