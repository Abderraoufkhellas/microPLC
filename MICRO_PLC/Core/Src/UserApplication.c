/*
 * UserApplication.c
 *
 *  Created on: Apr 10, 2025
 *      Author: pc
 */
#include "UserApplication.h"
/* THIS FILE IS FOR THE USER TO PROGRAM*/


/* -----------------------------------------------------------------------
 1-DEFINE VARIABLES with functions
 2-DEFINE LOGIC in functions
 3-REGISTER LOGIC functions

 -------------------------------------------------------------------------*/
/*CODE STARTS HERE*/
PLC_IO_t* Valve;
void setup (void ) {
	Valve =install_digital_output("Valve", GPIO_PIN_12);

}

void loop(void) {
	set_digital_output(Valve, GPIO_PIN_SET);
	vTaskDelay(pdMS_TO_TICKS(200));
	set_digital_output(Valve, GPIO_PIN_RESET);
	vTaskDelay(pdMS_TO_TICKS(200));


}
