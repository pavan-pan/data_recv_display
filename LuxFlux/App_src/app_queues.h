
#ifndef LP2_QUEUES_H__
#define LP2_QUEUES_H__

#include "FreeRTOS.h"
#include "queue.h"

#define BIO_IMPEDENCE_QUEUE_LENGTH 5

extern QueueHandle_t xQueue_Bio_Impedence;

/** @brief  Function for creating queues. These Queues are used to store and transfer the values received from 
  *         Bio-Impedence Sensor via Bluetooth
	* @param  None
  * @retval None
  */
void create_queues(void);

#endif
