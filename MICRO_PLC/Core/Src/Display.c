/*
 * Display.c
 *
 *  Created on: Apr 10, 2025
 *      Author: pc
 */

#include "Display.h"
#include "ILI9341_GFX.h"
#include "ILI9341_STM32_Driver.h"


//defining menus and items



const MenuItem DataListItem={"DATA LIST",IOsubMenu,NULL};
const MenuItem ForceDataItem={"FORCE DATA",NULL,NULL};
const MenuItem BackItem={"BACK",NULL,NULL};

MenuItem MainMenu[]={DataListItem,ForceDataItem,BackItem};
MenuItem IOsubMenu[3];
//Display task implementation


void display_init(void) {
	ILI9341_Init();
	ILI9341_SetRotation(SCREEN_HORIZONTAL_2);
	ILI9341_FillScreen(BLACK);
}

// change task priority later
void StartDISPLAY_Task(void *argument)
{
  /* USER CODE BEGIN StartDISPLAY_Task */
	MenuItem* currentMenu=MainMenu;
	display_init();
  /* Infinite loop */
  for(;;)
  {
	for(int i=0;i<MAX_MENU_SIZE;i++){
		ILI9341_DrawText(currentMenu->Title, FONT4, 20, 10+i*20, WHITE, BLACK);
	}
    vTaskDelay(pdMS_TO_TICKS(2));
  }
  /* USER CODE END StartDISPLAY_Task */
}
