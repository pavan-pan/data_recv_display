#ifndef LP2_HAL_TWI_H
#define LP2_HAL_TWI_H

#include <stddef.h>
#include <stdbool.h>
#include "nrf52.h"
#include "app_drv_twi.h"

#define TWI_ENABLE   5

/* TWI Frequencies */
#define TWIM_FREQUENCY_100K    0x01980000
#define TWIM_FREQUENCY_250K    0x04000000
#define TWIM_FREQUENCY_400K    0x06680000

/*PSDA Disconnect*/
#define TWIM_PSDA_DISCONNECT        0xFFFFFFFF

/*PSCL Disconnect*/
#define TWIM_PSCL_DISCONNECT        0xFFFFFFFF

/*ERRORSRC - Error Definitions */
/*OVERRUN ERROR*/
#define TWIM_OVERRUN_ERROR_POS      0
#define TWIM_OVERRUN_NOT_PRESENT    0
#define TWIM_OVERRUN_PRESENT        1
#define TWIM_OVERRUN_CLEAR          1

/*ADDRESS NACK ERROR*/
#define TWIM_ANACK_ERROR_POS        1  
#define TWIM_ANACK_NOT_PRESENT      0
#define TWIM_ANACK_PRESENT          1
#define TWIM_ANACK_CLEAR            1

/*DATA NACK ERROR*/
#define TWIM_DACK_ERROR_POS         2
#define TWIM_DACK_NOT_PRESENT       0
#define TWIM_DACK_PRESENT           1
#define TWIM_DACK_CLEAR             1

/**@brief TWIM configuration. */
typedef struct
{
	uint32_t sda;
	uint32_t sclk;
	uint8_t address;
	uint32_t twim_frequency;
	NRF_TWIM_Type *twim_module;
	NRF_GPIO_Type *gpio_module;
}twim_config_t;

/**
 * @enum  nrf_uarte_task_t
 * @brief UARTE tasks.
 */
typedef enum
{
    NRF_TWIM_TASKS_STARTRX    = offsetof(NRF_TWIM_Type, TASKS_STARTRX),    ///< Start TWI receive sequence.
    NRF_TWIM_TASKS_STARTTX    = offsetof(NRF_TWIM_Type, TASKS_STARTTX),     ///< Start TWI transmit sequence.
    NRF_TWIM_TASKS_STOP    		= offsetof(NRF_TWIM_Type, TASKS_STOP),       ///< Stop TWI transaction.
    NRF_TWIM_TASKS_SUSPEND    = offsetof(NRF_TWIM_Type, TASKS_SUSPEND),    ///< Suspend TWI transaction.
    NRF_TWIM_TASKS_RESUME     = offsetof(NRF_TWIM_Type, TASKS_RESUME),     ///< Resume TWI transaction.
} app_twim_task_t;

typedef enum
{
   
    NRF_TWIM_EVENT_STOPPED   = offsetof(NRF_TWIM_Type, EVENTS_STOPPED),   ///< TWI stopped.
    NRF_TWIM_EVENT_ERROR     = offsetof(NRF_TWIM_Type, EVENTS_ERROR),     ///< TWI error.
    NRF_TWIM_EVENT_SUSPENDED = 0x148,                                     ///< TWI suspended.
    NRF_TWIM_EVENT_RXSTARTED = offsetof(NRF_TWIM_Type, EVENTS_RXSTARTED), ///< Receive sequence started.
    NRF_TWIM_EVENT_TXSTARTED = offsetof(NRF_TWIM_Type, EVENTS_TXSTARTED), ///< Transmit sequence started.
    NRF_TWIM_EVENT_LASTRX    = offsetof(NRF_TWIM_Type, EVENTS_LASTRX),    ///< Byte boundary, starting to receive the last byte.
    NRF_TWIM_EVENT_LASTTX    = offsetof(NRF_TWIM_Type, EVENTS_LASTTX)     ///< Byte boundary, starting to transmit the last byte.
    
} app_twim_event_t;


void app_twim_hal_set_sda (uint32_t sda, NRF_TWIM_Type *TWIM_MODULE, NRF_GPIO_Type *GPIO_MODULE);
void app_twim_hal_set_sclk (uint32_t sclk, NRF_TWIM_Type *TWIM_MODULE, NRF_GPIO_Type *GPIO_MODULE);

void app_twim_hal_set_frequency (uint32_t twim_frequency, NRF_TWIM_Type *TWIM_MODULE);
void app_twim_hal_enable_module(NRF_TWIM_Type *TWIM_MODULE);

void app_twim_hal_init(twim_config_t *TWIM_MODULE);


void app_twim_hal_set_frequency (uint32_t twim_frequency, NRF_TWIM_Type *TWIM_MODULE);

void app_twim_hal_enable_module(NRF_TWIM_Type *TWIM_MODULE);

/**
  * @brief  HAL layer to check for an event.
	* @param  NRF_UARTE : UART module.
  * @param  event : Events mentioned in nrf_uarte_event_t.
  * @retval None
  */	
bool app_twim_hal_check_event(NRF_TWIM_Type * NRF_TWIM, app_twim_event_t event);

/**
  * @brief  HAL layer to clear an event.
	* @param  NRF_UARTE : UART module.
  * @param  event : Clear the events mentioned in nrf_uarte_event_t.
  * @retval None
  */	
void app_twim_hal_clear_event (NRF_TWIM_Type * NRF_TWIM, app_twim_event_t event);

void app_twim_hal_write_data (NRF_TWIM_Type *TWIM_MODULE, uint8_t *data, uint8_t address, uint8_t len);

void app_twim_hal_read_data (NRF_TWIM_Type *TWIM_MODULE, uint8_t *data, uint8_t address, uint8_t len);


#endif
