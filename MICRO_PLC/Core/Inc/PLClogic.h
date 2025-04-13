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

#include "FreeRTOS.h"
#include "task.h"
#include "UserApplication.h"


#define PLC_SCAN_CYCLE 10 //ms
#define TIMERS_RESOLUTION 1 //update every 1 ms

extern uint8_t Digital_Inputs_count ;
extern uint8_t Digital_Outputs_count ;
extern uint8_t Analog_Inputs_count ;
extern uint8_t Digital_memory_count ;
extern uint8_t Register_memory_count;
extern uint8_t Timer_count;

//To check if Timers are used at all to not use ressources
extern uint8_t TIMERS_USED;

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
PLC_IO_t* install_digital_input(uint16_t pin);
PLC_IO_t* install_digital_output(uint16_t pin);
PLC_MEM_t* add_internal_bool(void);
PLC_MEM_t* add_internal_reg(void);
PLC_Timer_t* add_TOFF(uint32_t preset_time);
PLC_Timer_t* add_TON(uint32_t preset_time);
void PLC_Timer_Update(void);
//LOGIC functions
void set_digital_output(PLC_IO_t* io, uint32_t VALUE);

//PLC LOGIC task definition:
void StartPLC_LOGIC(void *argument);


#endif /* INC_PLCLOGIC_H_ */
