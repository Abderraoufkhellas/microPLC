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


//Menu Item struct: Represents a single menu Item:

typedef struct MenuItem {
	char Title[16];
	struct MenuItem *SubMenu;
	void (*action)(void);
}MenuItem;

//declaring MenuItems
MenuItem IOlistItem;
MenuItem ForceDataItem;
MenuItem BackItem;


//declaring Menus
MenuItem MainMenu[];
MenuItem IOsubMenu[];



//Display task definition

void StartDISPLAY_Task(void *argument);


#endif /* INC_DISPLAY_H_ */
