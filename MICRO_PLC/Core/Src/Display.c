/*
 * Display.c
 *
 *  Created on: Apr 10, 2025
 *      Author: pc
 */

#include "Display.h"
//Display task implementation

void StartDISPLAY_Task(void *argument)
{
  /* USER CODE BEGIN StartDISPLAY_Task */
  /* Infinite loop */
  for(;;)
  {
    vTaskDelay(pdMS_TO_TICKS(1));
  }
  /* USER CODE END StartDISPLAY_Task */
}
