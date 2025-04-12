/*
 * PLC_LOGIC.c
 *
 *  Created on: Apr 10, 2025
 *      Author: pc
 */
#include "PLClogic.h"

//to check for available pins
static uint8_t Digital_Inputs_count =0;
static uint8_t Digital_Outputs_count =0;
static uint8_t Analog_Inputs_count =0;
static uint8_t Digital_memory_count =0;
static uint8_t Register_memory_count =0;

/*PLC DATA INSTALL FUNCTIONS IMPLEMENTATION */


PLC_IO_t* install_digital_input(const char *VarName,uint16_t pin){
	if (Digital_Inputs_count >= MAX_DIGITAL_IO_VARIABLES) {
		Error_Handler(); //implement error checks later// check if limit is passed
	}
	PLC_IO_t* New= &PLC_Data_map.DIGITAL_INPUTS[Digital_Inputs_count++];
	/* fill a spot in the data map with a pointer*/
	strncpy(New->name,VarName,sizeof(New->name));
	New->name[sizeof(New->name)-1]='\0';
	New->type=DIGITAL_IN_t;
	New->pinNumber=pin;
	New->value=0; //recheck this value init later
    /*configure the pin */
	GPIO_InitTypeDef GPIO_cfg = {0};
	GPIO_cfg.Pin = New->pinNumber;
	GPIO_cfg.Mode = GPIO_MODE_INPUT;
	GPIO_cfg.Pull = GPIO_NOPULL;
	GPIO_cfg.Speed = GPIO_SPEED_FREQ_LOW;
	if (pin== DIN1 || pin== DIN2 ||pin== DIN3 ||pin == DIN4 || pin == GPIO_PIN_12){
		HAL_GPIO_Init(GPIOD, &GPIO_cfg); // port is hard coded -> change later
	}
	return New;

}



PLC_IO_t* install_digital_output(const char *VarName,uint16_t pin){
	if (Digital_Outputs_count >= MAX_DIGITAL_IO_VARIABLES) {
		Error_Handler(); //implement error checks later// check if limit is passed
	}
	PLC_IO_t* New= &PLC_Data_map.DIGITAL_OUTPUTS[Digital_Outputs_count++];
	/* fill a spot in the data map with a pointer*/
	strncpy(New->name,VarName,sizeof(New->name));
	New->name[sizeof(New->name)-1]='\0';
	New->type=DIGITAL_OUT_t;
	New->pinNumber=pin;
	New->value=0; //recheck this value init later
    /*configure the pin */
	GPIO_InitTypeDef GPIO_cfg = {0};
	GPIO_cfg.Pin = New->pinNumber;
	GPIO_cfg.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_cfg.Pull = GPIO_NOPULL;
	GPIO_cfg.Speed = GPIO_SPEED_FREQ_LOW;
	if (pin== DIN1 || pin== DIN2 ||pin== DIN3 ||pin == DIN4 || pin == GPIO_PIN_12){
		HAL_GPIO_Init(GPIOD, &GPIO_cfg); // port is hard coded -> change later
	}
	return New;

}

PLC_IO_t* add_internal_bool(const char *VarName) {
	if (Digital_memory_count >= MAX_DIGITAL_MEMORY_VARIABLES) {
		Error_Handler();
	}
	PLC_IO_t* New= &PLC_Data_map.INTERNAL_DIGITAL_MEM[Digital_memory_count++];
	strncpy(New->name,VarName,sizeof(New->name));
	New->name[sizeof(New->name)-1]='\0';
	New->type=INTERNAL_BOOL_t;
	New->value=0; //recheck this value init later
	return New;
}


PLC_IO_t* add_internal_reg(const char *VarName) {
	if (Register_memory_count >= MAX_REGISTER_MEMORY_VARIABLES) {
		Error_Handler();
	}
	PLC_IO_t* New= &PLC_Data_map.INTERNAL_DIGITAL_MEM[Digital_memory_count++];
	strncpy(New->name,VarName,sizeof(New->name));
	New->name[sizeof(New->name)-1]='\0';
	New->type=INTERNAL_REGISTER_t;
	New->value=0; //recheck this value init later
	return New;
}











void set_digital_output(PLC_IO_t* io, uint32_t VALUE){
	io->value= VALUE;
	HAL_GPIO_WritePin(GPIOD, io->pinNumber, VALUE);
}















//PLC logic task implemntation
void StartPLC_LOGIC(void *argument)
{

  for(;;)
  {
	  loop();
	  vTaskDelay(pdMS_TO_TICKS(100));
  }
}





