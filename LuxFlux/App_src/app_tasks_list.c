#include "app_tasks_list.h"
#include "BQ27421.h"
#include "led.h"

/* Add task handles here */
static TaskHandle_t  Bio_Impedence_receive_task_handle;   /**< Reference to Bio_Impedence receive FreeRTOS task. */
static TaskHandle_t  Bio_Impedence_display_task_handle;   /**< Reference to Bio-Impedence Display FreeRTOS task. */
static TaskHandle_t  BQ25120_init_task_handle;            /**< Reference to BQ25120 init task. */

#if NRF_LOG_ENABLED
static TaskHandle_t m_logger_thread;                                /**< Definition of Logger thread. */
#endif

/**@brief A function which is hooked to idle task.
 * @note Idle hook must be enabled in FreeRTOS configuration (configUSE_IDLE_HOOK).
 */
void vApplicationIdleHook( void )
{
#if NRF_LOG_ENABLED
     vTaskResume(m_logger_thread);
#endif
}

/**
  * @brief  Function to create tasks 
  * @param  None
  * @retval None
  */
void create_tasks()
{
		BaseType_t xReturned;
/****************************************************************************************/
    //Create a task for getting the data from the Bio-Impedence Sensor and add it to the queue
		xReturned = xTaskCreate(Bio_Impedence_receive_task_function, "Receiving Bio-Impedence Data", 
														configMINIMAL_STACK_SIZE , NULL, 1, &Bio_Impedence_receive_task_handle);
		
		if (xReturned == pdPASS)
		{
			NRF_LOG_INFO ("Receiving Bio-Impedence Data task created successfully");
		}
		
		//Create a task for taking the data out of the queue and transmitting to the host via Bluetooth
		xReturned = xTaskCreate(Bio_Impedence_display_task_function, "Bio Impedence Display Task", 
														configMINIMAL_STACK_SIZE  , NULL, 1, &Bio_Impedence_display_task_handle);
		if (xReturned == pdPASS)
		{
			NRF_LOG_INFO ("Bio-Impedence display task created successfully");
		}
		
/****************************************************************************************/				
		xReturned = xTaskCreate(BQ25120_init_task_function, "BQ25120 init", 
														configMINIMAL_STACK_SIZE  , NULL, 1, &BQ25120_init_task_handle);
		if (xReturned == pdPASS)
		{
			NRF_LOG_INFO ("BQ25120_init_task_function task created successfully");
		}
/****************************************************************************************/	
}

/**
  * @brief  Task function to get the Bio-Impedence value and add it to the queue 
  * @param  pvParameter : parameter passed to the task when creating the task
  * @retval None
  */
void Bio_Impedence_receive_task_function (void * pvParameter)
{
	
	volatile uint64_t bioimpedance = 0;
	uint32_t bio_imp_32 = 0;
	uint8_t data_write =0;

	for(;;)
	{
		
		// Start Conversion
		data_write = 0x08;
		spi_write_byte (&data_write, 1);

	  data_write = 0x12;
	  spi_write_byte (&data_write, 1);
		bioimpedance = 0;
		
		bioimpedance = ads1292r_get_bioimpedance();
		
		bio_imp_32 = ((bioimpedance & MASK));
		
		//Send the value to the queue
		xQueueSendToBack(xQueue_Bio_Impedence, &bio_imp_32, 10);
		
		vTaskDelay(20);
	}
}

/**
  * @brief  Task function to retrieve the value from the queue and transmit it via Bluetooth 
  * @param  pvParameter : parameter passed to the task when creating the task
  * @retval None
  */
void Bio_Impedence_display_task_function (void * pvParameter)
{
	//char recv_data[10];
	uint32_t bio_imp_32 = 0;
	uint8_t *bio_imp_ptr;
	bio_imp_ptr = (uint8_t *)bio_imp_32;
	
	for (;;)
	{
		uint16_t data_len = 4;
		//BQ25120_init();
		if (xQueueReceive(xQueue_Bio_Impedence, &bio_imp_32, 0))
		{
			//bio_imp_32 = 0xffff;
			bio_imp_ptr = (uint8_t *)&bio_imp_32;
			uint32_t err_code = send_data_ble(bio_imp_ptr, &data_len);
	
			if ( (err_code != NRF_ERROR_INVALID_STATE) && (err_code != NRF_ERROR_BUSY) &&
												 (err_code != NRF_ERROR_NOT_FOUND)  && (err_code != NRF_SUCCESS))
			{
					APP_ERROR_CHECK(err_code);
			}
		}
		vTaskDelay(20);
	}
}

/**
  * @brief  Task function to initialize the BQ25120 module 
  * @param  pvParameter : parameter passed to the task when creating the task
  * @retval None
  */
void BQ25120_init_task_function (void * pvParameter)
{
	
	for (;;)
	{
		BQ25120_init();

		int16_t current = BQ27421_read(BQ27421_CURRENT);
		NRF_LOG_INFO( "current : %d, %x\n",current, current);

		if (current < 0)
		{
			led_green_off();
			led_blue_off();
			led_red_on();
		}
		else
		{
			led_red_off();
			led_blue_off();
			led_green_on();
		}
		
		vTaskDelay(100);
	}
}
