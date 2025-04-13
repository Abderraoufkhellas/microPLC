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
IO Button;

void setup (void ) {
	Valve =install_digital_output("Valve", GPIO_PIN_12);
	Button=install_digital_input("Button", GPIO_PIN_0);

}

void loop(void) {
	if(Button->value==1) {
		Valve->value=1;
	}
	else {
		Valve->value=0;
	}


}
