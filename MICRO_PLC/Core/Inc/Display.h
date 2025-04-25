/*
 * Display.h
 *
 *  Created on: Apr 10, 2025
 *      Author: pc
 */
/*DISPLAY HEADER FILE   */



#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "PLCdataTypes.h"


#define SCREEN_AUTO_REFRESH_MS 2000
#define RT_VIEW_REFRESH 50
#define MAIN_MENU_COUNT 3
#define MAX_MENU_DEPTH 5
#define MAX_FIELDS 20

#define MENU_X             10
#define MENU_Y             20
#define MENU_LINE_HEIGHT   20
#define MENU_WIDTH        (240 - 2*MENU_X)  // e.g. full-width on a 240×320
#define COLOR_TEXT        WHITE
#define COLOR_HIGHLIGHT   BLACK
#define COLOR_BG_NORMAL   BLACK
//Menu Item struct: Represents a single menu Item:

typedef struct MenuItem {
	char Title[16];
	struct MenuItem *SubMenu;
	uint8_t subSize;
	void (*action)(void);
}MenuItem;

//RT data display fields
typedef enum {
	FDIGITAL,
	FANALOG,
	FMEM_BOOL,
	FMEM_REG,
	FTIMER
} FIELD_t;



//field struct

typedef struct {
	FIELD_t type;
	void *ptr;
	const char *name;
	uint32_t min,max,step;
} FieldDesc;


//DISPLAY STATE MACHINE
typedef enum {
	DISP_MENU,
	DISP_RT_VIEW,
	DISP_FORCE_VIEW
}CURRENT_STATE;


typedef enum {
	FORCE_LIST,
	FORCE_EDIT
}ForceSubState;
extern CURRENT_STATE Current_Display_State;



//Adding buttons
typedef enum {
	UP_BUTTON,
	DOWN_BUTTON,
	SELECT_BUTTON,
	BACK_BUTTON
}BUTTON_INPUT;

//Display task definition

void StartDISPLAY_Task(void *argument);


#endif /* INC_DISPLAY_H_ */
