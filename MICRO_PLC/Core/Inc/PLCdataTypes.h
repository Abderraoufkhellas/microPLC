/*
 * PLCdataTypes.h
 *
 *  Created on: Apr 10, 2025
 *      Author: pc
 */

#ifndef INC_PLCDATATYPES_H_
#define INC_PLCDATATYPES_H_


#include "main.h"
#include <stdbool.h>
//DATA SIZE DEFINES
#define MAX_DIGITAL_IO_VARIABLES 4
#define MAX_ANALOG_IO_VARIABLE 2
#define MAX_DIGITAL_MEMORY_VARIABLES 20
#define MAX_REGISTER_MEMORY_VARIABLES 20
#define MAX_TIMERS_CAPACITY 4

//Setting a macro to make data definition easier for the user
#define IO PLC_IO_t*
#define MEM PLC_MEM_t*
#define TIM PLC_Timer_t*
/*DATA TYPE ENUM
 EXPLANATION : these are the types the user can use
*/




typedef enum PLC_data_t {
	DIGITAL_IN_t,
	DIGITAL_OUT_t,
	ANALOG_IN_t,
	ANALOG_OUT_t,
	INTERNAL_BOOL_t,
	INTERNAL_REGISTER_t

}PLC_data_t;




/*PLC IO PINS ENUM
 * THIS IS TEMPORARY (Can change later) !!!!!!!!!!!!!!!!!!!!!

 */
typedef enum {
	DIN1,				//temporarely
	DIN2,
	DIN3,
	DIN4,
	AIN1,
	AIN2,
	RTD,
	ENCODER,
}PLC_Pin;


/* PLC DATA TYPES */

typedef struct {
	char handle[16];
	PLC_data_t type;
    uint16_t pinNumber;
    uint32_t value;  // HERE ALL values are uint32_t (even digital) Search for better solution!!!
} PLC_IO_t;

typedef struct {
	char handle[16];
	PLC_data_t type;
	uint32_t value; // HERE ALL values are uint32_t (even digital) Search for better solution!!!
} PLC_MEM_t;




typedef enum {
	TON,
	TOFF
}TIMER_TYPE;


//adding timer datatype
typedef struct {
	TIMER_TYPE type;
	char handle[16];
	bool IN;
	bool Q;
	uint32_t ET;
	uint32_t PT;
}PLC_Timer_t;

/* PLC data map*/
//useful for accessing data from other tasks such as modbus or display task


typedef struct {
	PLC_IO_t DIGITAL_INPUTS[MAX_DIGITAL_IO_VARIABLES];
	PLC_IO_t DIGITAL_OUTPUTS[MAX_DIGITAL_IO_VARIABLES];
	PLC_IO_t ANALOG_INPUTS[MAX_ANALOG_IO_VARIABLE ];
	PLC_IO_t ANALOG_OUTPUTS[MAX_ANALOG_IO_VARIABLE ];
	PLC_MEM_t INTERNAL_DIGITAL_MEM[MAX_DIGITAL_MEMORY_VARIABLES];
	PLC_MEM_t INTERNAL_REGISTER_MEM[MAX_REGISTER_MEMORY_VARIABLES];
	PLC_Timer_t PLC_TIMERS[MAX_TIMERS_CAPACITY];

} PLC_IO_map;

//declare a global data map across all files
extern PLC_IO_map PLC_Data_map;


typedef enum {
	INPUT,
	OUTPUT
}Direction_t;




#endif /* INC_PLCDATATYPES_H_ */
