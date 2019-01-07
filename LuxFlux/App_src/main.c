/**
 *
 * @brief Application main file.
 *
 * This file contains the source code for the application using FreeRTOS and the
 * related Bluetooth services.
 */

#include "FreeRTOS.h"
#include "app_startup.h"
#include "app_tasks_list.h"
#include "SEGGER_RTT.h"

/**@brief Function for application main entry.
 */
int main(void)
{
	  /*Initialize different modules for the project*/
		init_modules();
	  
	  /*Create tasks for FreeRTOS*/
		create_tasks();
	  
	  /*Start the scheduler*/
		vTaskStartScheduler();

    for (;;)
    {
       
    }
}	
