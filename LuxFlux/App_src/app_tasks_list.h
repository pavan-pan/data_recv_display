#ifndef TASKS_H
#define TASKS_H

#include <stdint.h>
#include "app_helper.h"
#include "ads1292r.h"
#include "BQ25120.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "app_queues.h"
#include "task.h"
#include "BQ25120.h"
#include "nrf_log.h"

#define MASK 0x0000000000FFFFFFUL

/**
  * @brief  Function to create tasks 
  * @param  None
  * @retval None
  */
void create_tasks(void);
	
void Bio_Impedence_receive_task_function (void * pvParameter);
void Bio_Impedence_display_task_function (void * pvParameter);
void charge_status_task_function (void * pvParameter);
void BQ25120_init_task_function (void * pvParameter);
#endif
