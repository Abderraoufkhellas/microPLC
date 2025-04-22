/*
 * Display.c
 *
 *  Created on: Apr 10, 2025
 *      Author: pc
 */

#include "Display.h"
#include "ILI9341_GFX.h"
#include "ILI9341_STM32_Driver.h"
#include "main.h"
//defining menus and items



MenuItem IOsubMenu[3];
MenuItem MainMenu[]={{"REAL TIME DATA",IOsubMenu,NULL},{"FORCE DATA",NULL,NULL},{"BACK",NULL,NULL}};

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
	uint8_t sizeStack[MAX_MENU_DEPTH];
	uint8_t depth=0;
	uint8_t idx=0;
	MenuItem* MenuStack[MAX_MENU_DEPTH];
	BUTTON_INPUT btn;

	MenuStack[0]=MainMenu;
	sizeStack[0]=MAIN_MENU_COUNT;

	display_init();
  /* Infinite loop */
  for(;;)
  {
	 osStatus_t st=osMessageQueueGet(ButtonQueueHandle, &btn, NULL, SCREEN_AUTO_REFRESH_MS);
	 if (st==osOK) {
		 MenuItem *curMenu = MenuStack[depth];
		 uint8_t curSize= sizeStack[depth];
		 switch (btn) {
		 case UP_BUTTON:
			 idx= (idx==0) ? (curSize-1) : (idx - 1);
			 break;
		 case DOWN_BUTTON:
			 idx= (idx + 1) % curSize;
			 break;
		 case SELECT_BUTTON:
			 MenuItem *sel= &curMenu[idx];
			 if (sel->SubMenu !=NULL && depth <MAX_MENU_DEPTH -1)
			 {
				 depth++;
				 MenuStack[depth]=sel->SubMenu;
				 sizeStack[depth]=sel->subSize;
				 idx=0;
			 }
			 else if(sel->action){
				 sel->action();
			 }
			 break;
		 case BACK_BUTTON:
			 if (depth >0) {
				 depth--;
				 idx=0;
			 }
			 break;
		 }

	 }
	 ILI9341_FillScreen(BLACK);
	 MenuItem *cur= MenuStack[depth];
	 uint8_t cnt = sizeStack[depth];
	 for (uint8_t i=0; i<cnt; i++) {
		 uint16_t y= 20 +i*20;
		 if (i==idx){
			 //highlight selected row
			 ILI9341_DrawRectangle(10, y-2, 220, 20, WHITE);
			 ILI9341_DrawText(cur[i].Title, FONT4, 12, y, BLACK, WHITE);
		 }
		 else {
			 ILI9341_DrawText(cur[i].Title, FONT4, 12, y, WHITE, BLACK);

		 }
	 }




//	for(int i=0;i<MAX_MENU_SIZE;i++){
//		ILI9341_DrawText(currentMenu[i].Title, FONT4, 20, 10+i*20, WHITE, BLACK);
//	}
  }
  /* USER CODE END StartDISPLAY_Task */
}
