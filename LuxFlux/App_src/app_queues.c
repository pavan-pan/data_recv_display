
#include <stdint.h>
#include "app_queues.h"
#include "nrf_log.h"

QueueHandle_t xQueue_Bio_Impedence; /* Queue to transfer Bio-Impedence values via Bluetooth */

/** @brief  Function for creating queues. These Queues are used to store and transfer the values received from 
  *         Bio-Impedence Sensor via Bluetooth
	* @param  None
  * @retval None
  */
void create_queues()
{
	uint16_t uxQueueLength_Bio_Impedence_len = BIO_IMPEDENCE_QUEUE_LENGTH; //Length of the Bio-Impedence Queue
	
	xQueue_Bio_Impedence = xQueueCreate(uxQueueLength_Bio_Impedence_len, 4);
	
	if (xQueue_Bio_Impedence == 0)
	{
		NRF_LOG_INFO ("Error creating Bio_Impedence Queue\r\n");
		return;
	}
}
