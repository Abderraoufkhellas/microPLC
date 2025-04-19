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

#define MAX_MENU_SIZE 5


//Menu Item struct: Represents a single menu Item:

typedef struct MenuItem {
	char Title[16];
	struct MenuItem *SubMenu;
	void (*action)(void);
}MenuItem;

//declaring MenuItems
const MenuItem DataListItem;
const MenuItem ForceDataItem;
const MenuItem BackItem;


//declaring Menus
MenuItem MainMenu[];
MenuItem IOsubMenu[];



//Display task definition

void StartDISPLAY_Task(void *argument);


#endif /* INC_DISPLAY_H_ */
