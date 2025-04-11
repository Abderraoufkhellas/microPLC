/*
 * PLCdataTypes.h
 *
 *  Created on: Apr 10, 2025
 *      Author: pc
 */

#ifndef INC_PLCDATATYPES_H_
#define INC_PLCDATATYPES_H_

#include "main.h"


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
typedef enum PLC_Pin {
	DIN1,
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
	PLC_data_t type;
    PLC_Pin pinNumber;
    uint32_t value;  // HERE ALL values are uint32_t (even digital) Search for better solution!!!
} PLC_IO_t;









// TO DO

/*implement datatypes HAL CONFIG functions */






#endif /* INC_PLCDATATYPES_H_ */
