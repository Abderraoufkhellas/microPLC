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
#include "PLCdataTypes.h"
#include "PLClogic.h"



CURRENT_STATE Current_Display_State=DISP_MENU;




//defining leaf functions

void switch_RT(void){
	Current_Display_State=DISP_RT_VIEW;
}

void switch_Force(void){
	Current_Display_State=DISP_FORCE_VIEW;
}

//defining menus and items
MenuItem MainMenu[]={{"REAL TIME DATA",NULL,0,switch_RT},{"FORCE DATA",NULL,0,NULL}};



void display_init(void) {
	ILI9341_Init();
	ILI9341_SetRotation(SCREEN_VERTICAL_2);
	ILI9341_FillScreen(COLOR_BG_NORMAL);
	ILI9341_DrawText("Press a button...", FONT4, 55, 140, COLOR_TEXT, COLOR_BG_NORMAL);


	Current_Display_State=DISP_MENU;
}

void Display_PLC_DATA(void) {
	char buf[32];
	uint16_t y=10;
	ILI9341_FillScreen(BLACK);
	  for (int i = 0; i < Digital_Inputs_count; i++, y += MENU_LINE_HEIGHT) {
		  	osMutexAcquire(PLC_IO_DatabaseHandle,portMAX_DELAY);
	        PLC_IO_t *io = &PLC_Data_map.DIGITAL_INPUTS[i];
	        snprintf(buf, sizeof(buf), "%s: %u", io->handle, io->value);
	        ILI9341_DrawText(buf, FONT4, MENU_X, y, COLOR_TEXT, COLOR_BG_NORMAL);
	        osMutexRelease(PLC_IO_DatabaseHandle);
	    }
	  for (int j = 0; j < Digital_Outputs_count; j++, y += MENU_LINE_HEIGHT) {
		  	osMutexAcquire(PLC_IO_DatabaseHandle,portMAX_DELAY);
			PLC_IO_t *io = &PLC_Data_map.DIGITAL_OUTPUTS[j];
			snprintf(buf, sizeof(buf), "%s: %u", io->handle, io->value);
			ILI9341_DrawText(buf, FONT4, MENU_X, y, COLOR_TEXT, COLOR_BG_NORMAL);
	        osMutexRelease(PLC_IO_DatabaseHandle);
		}
	  for (int k = 0; k < Analog_Inputs_count; k++, y += MENU_LINE_HEIGHT) {
		  	osMutexAcquire(PLC_IO_DatabaseHandle,portMAX_DELAY);
			PLC_IO_t *io = &PLC_Data_map.ANALOG_INPUTS[k];
			snprintf(buf, sizeof(buf), "%s: %u", io->handle, io->value);
			ILI9341_DrawText(buf, FONT4, MENU_X, y, COLOR_TEXT, COLOR_BG_NORMAL);
	        osMutexRelease(PLC_IO_DatabaseHandle);

		}
	  for (int l = 0; l < Digital_memory_count; l++, y += MENU_LINE_HEIGHT) {
		  	osMutexAcquire(PLC_IO_DatabaseHandle,portMAX_DELAY);
			PLC_MEM_t *io = &PLC_Data_map.INTERNAL_DIGITAL_MEM[l];
			snprintf(buf, sizeof(buf), "%s: %u", io->handle, io->value);
			ILI9341_DrawText(buf, FONT4, MENU_X, y, COLOR_TEXT, COLOR_BG_NORMAL);
	        osMutexRelease(PLC_IO_DatabaseHandle);
		}
	  for (int m = 0; m < Register_memory_count; m++, y += MENU_LINE_HEIGHT) {
		  	osMutexAcquire(PLC_IO_DatabaseHandle,portMAX_DELAY);
			PLC_MEM_t *io = &PLC_Data_map.INTERNAL_REGISTER_MEM[m];
			snprintf(buf, sizeof(buf), "%s: %u", io->handle, io->value);
			ILI9341_DrawText(buf, FONT4, MENU_X, y, COLOR_TEXT, COLOR_BG_NORMAL);
	        osMutexRelease(PLC_IO_DatabaseHandle);

		}


}




//Display task implementation

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


	 switch(Current_Display_State) {
	 case DISP_MENU:

		 if(osMessageQueueGet(ButtonQueueHandle, &btn, NULL, SCREEN_AUTO_REFRESH_MS)==osOK){
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
		 ILI9341_FillScreen(BLACK);
		 MenuItem *cur= MenuStack[depth];
		 uint8_t cnt = sizeStack[depth];
		 for (uint8_t i=0; i<cnt; i++) {
			 uint16_t y= 20 +i*20;
			 if (i==idx){
				 //highlight selected row
				 ILI9341_DrawRectangle(10, y-2, 200, 22, WHITE);
				 ILI9341_DrawText(cur[i].Title, FONT4, 12, y, BLACK, WHITE);
			 }
			 else {
				 ILI9341_DrawText(cur[i].Title, FONT4, 12, y, WHITE, BLACK);

			 }
		 }
		 }

	 	 break;
	 case DISP_RT_VIEW:
		 if(osMessageQueueGet(ButtonQueueHandle, &btn, NULL, RT_VIEW_REFRESH)==osOK){
			switch(btn) {
				//add navigation later
			case BACK_BUTTON:
				Current_Display_State=DISP_MENU;
				idx=0;
				break;
			}

		}
		 Display_PLC_DATA();
		 break;
	 }





 }

}
