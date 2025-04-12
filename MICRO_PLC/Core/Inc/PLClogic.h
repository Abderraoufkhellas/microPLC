/*
 * PLC_LOGIC.h
 *
 *  Created on: Apr 10, 2025
 *      Author: pc
 */

#ifndef INC_PLCLOGIC_H_
#define INC_PLCLOGIC_H_

#include "main.h"
#include "PLCdataTypes.h"
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "UserApplication.h"



extern uint8_t Digital_Inputs_count ;
extern uint8_t Digital_Outputs_count ;
extern uint8_t Analog_Inputs_count ;
extern uint8_t Digital_memory_count ;
extern uint8_t Register_memory_count;




// TO DO

/*implement datatypes HAL CONFIG functions */

/* to implement: functions will be something like:
 * install_digital_IO()
 * install_analog_IO()
 * install_mem()
 *
 */
//add more arguments later like modbus address

//INSTALL functions
PLC_IO_t* install_digital_input(const char *VarName,uint16_t pin);
PLC_IO_t* install_digital_output(const char *VarName,uint16_t pin);
PLC_IO_t* add_internal_bool(const char *VarName);
PLC_IO_t* add_internal_reg(const char *VarName);

//LOGIC functions
void set_digital_output(PLC_IO_t* io, uint32_t VALUE);
//PLC LOGIC task definition:
void StartPLC_LOGIC(void *argument);


#endif /* INC_PLCLOGIC_H_ */
