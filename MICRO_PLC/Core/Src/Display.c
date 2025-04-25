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
#include "stdio.h"



CURRENT_STATE Current_Display_State=DISP_MENU;


//RT fields array
static FieldDesc fields[MAX_FIELDS];
static uint8_t fieldCount;


//defining leaf functions

void switch_RT(void){
	Current_Display_State=DISP_RT_VIEW;
}

void enter_Force_mode(void){
	Current_Display_State=DISP_FORCE_VIEW;
	forceEnabled=1;
}

void exit_Force_mode(void){
	Current_Display_State=DISP_MENU;
	//forceEnabled=0;
}

//defining menus and items
MenuItem DataMenu[]={{"REAL TIME DATA",NULL,0,switch_RT},{"FORCE DATA",NULL,0,enter_Force_mode}};
MenuItem MainMenu[]={{"PLC STATUS",NULL,0,NULL},{"DATA",DataMenu,2,NULL},{"COMM STATUS",NULL,0,NULL}};



void display_init(void) {
	ILI9341_Init();
	ILI9341_SetRotation(SCREEN_VERTICAL_2);
	ILI9341_FillScreen(COLOR_BG_NORMAL);
	ILI9341_DrawText("STARTING...", FONT4, 50, 130, GREEN, COLOR_BG_NORMAL);


	Current_Display_State=DISP_MENU;
}
void BuildFieldList(void) {
	fieldCount=0;
	for (int i=0;i<Digital_Inputs_count &&fieldCount <MAX_FIELDS;i++) {
		fields[fieldCount++]= (FieldDesc) {
			.type= FDIGITAL,
			.ptr=&PLC_Data_map.DIGITAL_INPUTS[i],
			.name= PLC_Data_map.DIGITAL_INPUTS[i].handle,
			.min=0, .max =1, .step=1
		};
	}
	for (int j=0;j<Digital_Outputs_count &&fieldCount <MAX_FIELDS;j++) {
			fields[fieldCount++]= (FieldDesc) {
				.type= FDIGITAL,
				.ptr=&PLC_Data_map.DIGITAL_OUTPUTS[j],
				.name= PLC_Data_map.DIGITAL_OUTPUTS[j].handle,
				.min=0, .max =1, .step=1
			};
		}
	for (int k=0;k<Analog_Inputs_count &&fieldCount <MAX_FIELDS;k++) {
				fields[fieldCount++]= (FieldDesc) {
					.type= FANALOG,
					.ptr=&PLC_Data_map.ANALOG_INPUTS[k],
					.name= PLC_Data_map.ANALOG_INPUTS[k].handle,
					.min=0, .max =65536, .step=10000
				};
			}
	for (int l=0; l<Digital_memory_count &&fieldCount <MAX_FIELDS;l++) {
				fields[fieldCount++]= (FieldDesc) {
					.type= FMEM_BOOL,
					.ptr=&PLC_Data_map.INTERNAL_DIGITAL_MEM[l],
					.name= PLC_Data_map.INTERNAL_DIGITAL_MEM[l].handle,
					.min=0, .max =1, .step=1
				};
			}
	for (int m=0; m<Register_memory_count&&fieldCount <MAX_FIELDS;m++) {
					fields[fieldCount++]= (FieldDesc) {
						.type= FMEM_REG,
						.ptr=&PLC_Data_map.INTERNAL_REGISTER_MEM[m],
						.name= PLC_Data_map.INTERNAL_REGISTER_MEM[m].handle,
						.min=0, .max =65536, .step=10000
					};
				}
}

void Display_RT_DATA(void) {
	char buf[32];
	char val[32];
	uint16_t y=10;
	ILI9341_FillScreen(BLACK);
	  for (int i = 0; i < fieldCount; i++, y += MENU_LINE_HEIGHT) {
		  	osMutexAcquire(PLC_IO_DatabaseHandle,portMAX_DELAY);
	        snprintf(buf, sizeof(buf), "%s:", fields[i].name);
	        if (fields[i].type==FMEM_BOOL || fields[i].type==FMEM_REG) {
		        snprintf(val, sizeof(val),"%lu",((PLC_MEM_t*)fields[i].ptr)->value);
	        }
	        else {
	        	snprintf(val, sizeof(val),"%lu",((PLC_IO_t*)fields[i].ptr)->value);
	        }
	        osMutexRelease(PLC_IO_DatabaseHandle);
	        ILI9341_DrawText(buf, FONT4, MENU_X, y, COLOR_TEXT, COLOR_BG_NORMAL);
	        ILI9341_DrawText(val, FONT4, MENU_X+150, y, COLOR_TEXT, COLOR_HIGHLIGHT);

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
	BuildFieldList();

	static ForceSubState fstate=FORCE_LIST;
	static uint8_t forceidx=0;
	static uint32_t editValue=0;

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
		 default :
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
				 ILI9341_DrawRectangle(10, y-2, 200, 22, WHITE);
				 ILI9341_DrawText(cur[i].Title, FONT4, 12, y, BLACK, WHITE);
			 }
			 else {
				 ILI9341_DrawText(cur[i].Title, FONT4, 12, y, WHITE, BLACK);

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
			default:
				break;
			}

		}
		 Display_RT_DATA();
		 break;
	 case DISP_FORCE_VIEW:
		 if(osMessageQueueGet(ButtonQueueHandle, &btn, NULL, 1000)==osOK){
			if (fstate==FORCE_LIST){
				switch(btn) {
				case UP_BUTTON:
					forceidx=(forceidx +fieldCount-1) % fieldCount;
					break;
				case DOWN_BUTTON:
					forceidx=(forceidx +1 ) % fieldCount;
					break;
				case SELECT_BUTTON:
					if (fields[forceidx].type==FMEM_BOOL || fields[forceidx].type==FMEM_REG) {
						editValue=((PLC_MEM_t*)fields[forceidx].ptr)->value;

					}
					else {
						editValue=((PLC_IO_t*)fields[forceidx].ptr)->value;

					}
					fstate= FORCE_EDIT;
					break;
				case BACK_BUTTON:
					exit_Force_mode();
					idx=0;
					break;

				}
			}
			else if (fstate==FORCE_EDIT) {
				FieldDesc *f=&fields[forceidx];


				switch(btn) {
				case UP_BUTTON:
					if (editValue +(f->step) <= f->max)
						editValue += f->step;
					break;
				case DOWN_BUTTON:
					if (editValue-(f->step) >= f->min)
						editValue -= f->step;
					break;
				case SELECT_BUTTON:
					if (f->type==FMEM_BOOL || f->type==FMEM_REG) {
						PLC_MEM_t *io= (PLC_MEM_t*)f->ptr;
				        if (io->force) {
				            // Already forced → toggle it off
				            io->force = false;
				            fstate = FORCE_LIST;
				            break;
				        }
				    	io->force = 1;
						io->forceValue = editValue;
					}

					else {
				        PLC_IO_t *io = (PLC_IO_t*)f->ptr;
				        if (io->force) {
				            io->force = 0;
				            fstate = FORCE_LIST;
				            break;
				        }
				        io->force = 1;
				        io->forceValue = editValue;
					}
					break;

				case BACK_BUTTON:
					fstate=FORCE_LIST;

					break;
				}
			}
		 }
		 ILI9341_FillScreen(COLOR_BG_NORMAL);
		 if (fstate==FORCE_LIST&& forceEnabled==1){
			 char Lbuf[30];
			 for (uint8_t i = 0, y = 20; i < fieldCount; i++, y += MENU_LINE_HEIGHT)
				{
					uint8_t sel = (i == forceidx);
					if (sel==1 && ((PLC_IO_t*)fields[i].ptr)->force==1) {
						ILI9341_DrawRectangle(MENU_X, y-2, 220, MENU_LINE_HEIGHT, WHITE);
				        snprintf(Lbuf, sizeof(Lbuf),"*f*  %s",fields[i].name);
						ILI9341_DrawText(Lbuf, FONT4, MENU_X+4, y, BLACK, WHITE);
					}
					else if(sel==0 && ((PLC_IO_t*)fields[i].ptr)->force==1 ) {

						snprintf(Lbuf, sizeof(Lbuf),"*f*  %s",fields[i].name);
						ILI9341_DrawText(Lbuf, FONT4, MENU_X+4, y, WHITE, BLACK);
					}
					else if (sel==1 && ((PLC_IO_t*)fields[i].ptr)->force==0 ){
						ILI9341_DrawRectangle(MENU_X, y-2, 220, MENU_LINE_HEIGHT, WHITE);
						snprintf(Lbuf, sizeof(Lbuf),"    %s",fields[i].name);
						ILI9341_DrawText(Lbuf, FONT4, MENU_X+4, y, BLACK, WHITE);
					}
					else {
						snprintf(Lbuf, sizeof(Lbuf),"    %s",fields[i].name);
						ILI9341_DrawText(Lbuf, FONT4, MENU_X+4, y, WHITE, BLACK);
					}
				}
		 }
		 else if (fstate==FORCE_EDIT && forceEnabled==1){
			FieldDesc *f = &fields[forceidx];
			char buf[16];
			uint16_t y = 40;

			ILI9341_DrawText("Forcing:", FONT4, MENU_X, y, GREEN, BLACK);
			ILI9341_DrawText(f->name,    FONT4, MENU_X, y+20, WHITE, BLACK);

			// value box
			snprintf(buf, sizeof(buf), "%lu", editValue);
			ILI9341_DrawText(buf, FONT4, MENU_X+4, y+50, GREEN, BLACK);

			// instructions
			ILI9341_DrawText("UP/DOWN: change value", FONT3, MENU_X, y+90, GREEN, BLACK);
			ILI9341_DrawText("SEL: commit/ cancel force",FONT3, MENU_X, y+110, GREEN, BLACK);
			ILI9341_DrawText("BACK: quit",       FONT3, MENU_X, y+130, GREEN, BLACK);
		 }


	 default :
		 break;
	 }


	 }
  }

