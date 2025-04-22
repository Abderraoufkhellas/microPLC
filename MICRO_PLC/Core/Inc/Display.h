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
#define SCREEN_AUTO_REFRESH_MS 5000
#define MAIN_MENU_COUNT 3
#define MAX_MENU_DEPTH 5

//Menu Item struct: Represents a single menu Item:

typedef struct MenuItem {
	char Title[16];
	struct MenuItem *SubMenu;
	uint8_t subSize;
	void (*action)(void);
}MenuItem;

//declaring MenuItems



//declaring Menus


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
