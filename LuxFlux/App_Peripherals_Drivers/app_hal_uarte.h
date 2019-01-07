
/// @file nrf_hal_uartE.h
/// This file is the header file for the HAL layer of the NRF UARTE driver module.
/// Detailed file description.

#ifndef NRF_HAL_UARTE_H
#define NRF_HAL_UARTE_H

#include "nrf52.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/*Enable UARTE register*/
#define ENABLE_UARTE				                          8UL
#define DISABLE_UARTE			                            0UL

/*Baudrate register*/
#define UARTE_BAUDRATE_1200			                      0x0004F000UL /*!< 1200 baud (actual rate: 1205) */
#define UARTE_BAUDRATE_2400			                      0x0009D000UL /*!< 2400 baud (actual rate: 2396) */
#define UARTE_BAUDRATE_4800			                      0x0013B000UL /*!< 4800 baud (actual rate: 4808) */
#define UARTE_BAUDRATE_9600			                      0x0004F000UL /*!< 9600 baud (actual rate: 9598) */
#define UARTE_BAUDRATE_14400		                      0x003B0000UL /*!< 14400 baud (actual rate: 14414) */
#define UARTE_BAUDRATE_19200		                      0x004EA000UL /*!< 19200 baud (actual rate: 19208) */
#define UARTE_BAUDRATE_28800		                      0x0075F000UL /*!< 28800 baud (actual rate: 28829) */
#define UARTE_BAUDRATE_38400		                      0x009D5000UL /*!< 38400 baud (actual rate: 38462) */
#define UARTE_BAUDRATE_57600		                      0x00EBF000UL /*!< 57600 baud (actual rate: 57762) */
#define UARTE_BAUDRATE_76800		                      0x013A9000UL /*!< 76800 baud (actual rate: 76923) */
#define UARTE_BAUDRATE_115200		                      0x01D7E000UL /*!< 115200 baud (actual rate: 115942) */
#define UARTE_BAUDRATE_230400		                      0x03AFB000UL /*!< 230400 baud (actual rate: 231884) */
#define UARTE_BAUDRATE_250000		                      0x04000000UL /*!< 250000 baud */
#define UARTE_BAUDRATE_460800		                      0x075F7000UL /*!< 460800 baud (actual rate: 470588) */
#define UARTE_BAUDRATE_921600		                      0x0EBED000UL /*!< 921600 baud (actual rate: 941176) */
#define UARTE_BAUDRATE_1M				                      0x10000000UL /*!< 1Mega baud */

/*Config register*/
#define UARTE_CONFIG_HARDWARE_FLOW_CONTROL_POS         0UL
#define UARTE_CONFIG_HARDWARE_FLOW_CONTROL_DISABLE     0UL /*!< Disable Hardware flow control */
#define UARTE_CONFIG_HARDWARE_FLOW_CONTROL_ENABLE      1UL /*!< Enable Hardware flow control */

/*Parity register*/
#define UARTE_CONFIG_PARITY_POS                        1UL
#define UARTE_CONFIG_PARITY_EXCLUDED                   0UL /*!< Exclude Parity bit */
#define UARTE_CONFIG_PARITY_INCLUDED                   7UL /*!< Include Parity bit */

/*PSELRTS register*/
#define UARTE_PSELRTS_DISCONNECTED                     (1UL << 31) /*!< PSELRTS disconnected */
#define UARTE_PSELRTS_CONNECTED                        (0UL << 31) /*!< PSELRTS connected */

/*PSELCTS register*/
#define UARTE_PSELCTS_DISCONNECTED                     (1UL << 31) /*!< PSELCTS disconnected */
#define UARTE_PSELCTS_CONNECTED                        (0UL << 31) /*!< PSELCTS connected */

/*PSELTXD register*/
#define UARTE_PSELTXD_DISCONNECTED                     (1UL << 31) /*!< PSELTXD disconnected */
#define UARTE_PSELTXD_CONNECTED                        (0UL << 31) /*!< PSELTXD connected */

/*PSELRXD register*/
#define UARTE_PSELRXD_DISCONNECTED                     (1UL << 31) /*!< PSELRXD disconnected */
#define UARTE_PSELRXD_CONNECTED                        (0UL << 31) /*!< PSELRXD connected */

/*UARTE pin configuration*/
#define UARTE_CTS_PIN_NUMBER                           7UL                                      
#define UARTE_RTS_PIN_NUMBER                           5UL
#define UARTE_TXD_PIN_NUMBER                           23UL
#define UARTE_RXD_PIN_NUMBER                           24UL

/*Interrupt configuration */
#define UARTE_ENABLE_INTERRUPT_CTS_POS                 0UL
#define UARTE_ENABLE_INTERRUPT_CTS_DISABLE             (0UL << UARTE_ENABLE_INTERRUPT_CTS_POS)
#define UARTE_ENABLE_INTERRUPT_CTS_ENABLE              (1UL << UARTE_ENABLE_INTERRUPT_CTS_POS)

#define UARTE_ENABLE_INTERRUPT_NCTS_POS                1UL
#define UARTE_ENABLE_INTERRUPT_NCTS_DISABLE            (0UL << UARTE_ENABLE_INTERRUPT_NCTS_POS)
#define UARTE_ENABLE_INTERRUPT_NCTS_ENABLE             (1UL << UARTE_ENABLE_INTERRUPT_NCTS_POS)

#define UARTE_ENABLE_INTERRUPT_RXDRDY_POS              2UL
#define UARTE_ENABLE_INTERRUPT_RXDRDY_DISABLE          (0UL << UARTE_ENABLE_INTERRUPT_RXDRDY_POS)
#define UARTE_ENABLE_INTERRUPT_RXDRDY_ENABLE           (1UL << UARTE_ENABLE_INTERRUPT_RXDRDY_POS)

#define UARTE_ENABLE_INTERRUPT_ENDRX_POS               4UL
#define UARTE_ENABLE_INTERRUPT_ENDRX_DISABLE           (0UL << UARTE_ENABLE_INTERRUPT_ENDRX_POS)
#define UARTE_ENABLE_INTERRUPT_ENDRX_ENABLE            (1UL << UARTE_ENABLE_INTERRUPT_ENDRX_POS)

#define UARTE_ENABLE_INTERRUPT_TXDRDY_POS              7UL
#define UARTE_ENABLE_INTERRUPT_TXDRDY_DISABLE          (0UL << UARTE_ENABLE_INTERRUPT_TXDRDY_POS)
#define UARTE_ENABLE_INTERRUPT_TXDRDY_ENABLE           (1UL << UARTE_ENABLE_INTERRUPT_TXDRDY_POS)

#define UARTE_ENABLE_INTERRUPT_ENDTX_POS               8UL
#define UARTE_ENABLE_INTERRUPT_ENDTX_DISABLE           (0UL << UARTE_ENABLE_INTERRUPT_ENDTX_POS)
#define UARTE_ENABLE_INTERRUPT_ENDTX_ENABLE            (1UL << UARTE_ENABLE_INTERRUPT_ENDTX_POS)

#define UARTE_ENABLE_INTERRUPT_ERROR_POS               9UL
#define UARTE_ENABLE_INTERRUPT_ERROR_DISABLE           (0UL << UARTE_ENABLE_INTERRUPT_ERROR_POS)
#define UARTE_ENABLE_INTERRUPT_ERROR_ENABLE            (1UL << UARTE_ENABLE_INTERRUPT_ERROR_POS)

#define UARTE_ENABLE_INTERRUPT_RXTO_POS                17UL
#define UARTE_ENABLE_INTERRUPT_RXTO_DISABLE            (0UL << UARTE_ENABLE_INTERRUPT_RXTO_POS)
#define UARTE_ENABLE_INTERRUPT_RXTO_ENABLE             (1UL << UARTE_ENABLE_INTERRUPT_RXTO_POS)

#define UARTE_ENABLE_INTERRUPT_RXSTARTED_POS           19UL
#define UARTE_ENABLE_INTERRUPT_RXSTARTED_DISABLE       (0UL << UARTE_ENABLE_INTERRUPT_RXSTARTED_POS)
#define UARTE_ENABLE_INTERRUPT_RXSTARTED_ENABLE        (1UL << UARTE_ENABLE_INTERRUPT_RXSTARTED_POS)

#define UARTE_ENABLE_INTERRUPT_TXSTARTED_POS           20UL
#define UARTE_ENABLE_INTERRUPT_TXSTARTED_DISABLE       (0UL << UARTE_ENABLE_INTERRUPT_TXSTARTED_POS)
#define UARTE_ENABLE_INTERRUPT_TXSTARTED_ENABLE        (1UL << UARTE_ENABLE_INTERRUPT_TXSTARTED_POS)

#define UARTE_ENABLE_INTERRUPT_TXSTOPPED_POS           22UL
#define UARTE_ENABLE_INTERRUPT_TXSTOPPED_DISABLE       (0UL << UARTE_ENABLE_INTERRUPT_TXSTOPPED_POS)
#define UARTE_ENABLE_INTERRUPT_TXSTOPPED_ENABLE        (1UL << UARTE_ENABLE_INTERRUPT_TXSTOPPED_POS)

/**
 * @enum  nrf_uarte_task_t
 * @brief UARTE tasks.
 */
typedef enum
{
    NRF_UARTE_TASKS_STARTRX    = offsetof(NRF_UARTE_Type, TASKS_STARTRX),    ///< Start the Receiving task.
    NRF_UARTE_TASKS_STOPRX     = offsetof(NRF_UARTE_Type, TASKS_STOPRX),     ///< Stop the Receiving task.
    NRF_UARTE_TASKS_STARTTX    = offsetof(NRF_UARTE_Type, TASKS_STARTTX),    ///< Start the Transmitting task.
    NRF_UARTE_TASKS_STOPTX     = offsetof(NRF_UARTE_Type, TASKS_STOPTX),     ///< Stop the Transmitting task.
    NRF_UARTE_TASKS_FLUSHRX    = offsetof(NRF_UARTE_Type, TASKS_FLUSHRX),    ///< Flush RX FIFO in RX buffer.
} nrf_uarte_task_t;

/**
 * @enum  nrf_uarte_event_t
 * @brief UARTE events.
 */
typedef enum
{
    NRF_UARTE_EVENT_CTS       = offsetof(NRF_UARTE_Type, EVENTS_CTS),       ///< CTS is activated.
    NRF_UARTE_EVENT_NCTS      = offsetof(NRF_UARTE_Type, EVENTS_NCTS),      ///< CTS is deactivated.
    NRF_UARTE_EVENT_RXDRDY    = offsetof(NRF_UARTE_Type, EVENTS_RXDRDY),    ///< Data received in RXD (but potentially not yet transferred to Data RAM).
    NRF_UARTE_EVENT_ENDRX     = offsetof(NRF_UARTE_Type, EVENTS_ENDRX),     ///< Receive buffer is filled up.
    NRF_UARTE_EVENT_TXDDY     = offsetof(NRF_UARTE_Type, EVENTS_TXDRDY),    ///< Data sent from TXD.
    NRF_UARTE_EVENT_ENDTX     = offsetof(NRF_UARTE_Type, EVENTS_ENDTX),     ///< Last TX byte transmitted.
    NRF_UARTE_EVENT_ERROR     = offsetof(NRF_UARTE_Type, EVENTS_ERROR),     ///< Error detected.
    NRF_UARTE_EVENT_RXTO      = offsetof(NRF_UARTE_Type, EVENTS_RXTO),      ///< Receiver timeout.
    NRF_UARTE_EVENT_RXSTARTED = offsetof(NRF_UARTE_Type, EVENTS_RXSTARTED), ///< Receiver has started.
    NRF_UARTE_EVENT_TXSTARTED = offsetof(NRF_UARTE_Type, EVENTS_TXSTARTED), ///< Transmitter has started.
    NRF_UARTE_EVENT_TXSTOPPED = offsetof(NRF_UARTE_Type, EVENTS_TXSTOPPED)  ///< Transmitted stopped.
} nrf_uarte_event_t;

/**@brief Structure for Transmit data pin. */
typedef struct
{
	uint32_t pseltxd_pin;
	uint32_t  pseltxd_enable_disable;
} nrf_pseltxd_config_t;

/**@brief Structure for Receive data pin. */
typedef struct
{
	uint32_t pselrxd_pin;
	uint32_t  pselrxd_enable_disable;
} nrf_pselrxd_config_t;

/**@brief Structure for CTS data pin. */
typedef struct
{
	uint32_t pselcts_pin;
	uint32_t  pselcts_enable_disable;
} nrf_pselcts_config_t;

/**@brief Structure for RTS data pin. */
typedef struct
{
	uint32_t pselrts_pin;
	uint32_t  pselrts_enable_disable;
} nrf_pselrts_config_t;

/**@brief Structure for Receiving configuration. */
typedef struct
{
	uint8_t  *ptr_rxd;    ///<Pointer to the receiving buffer.
	uint8_t  rxd_maxcnt;  ///<Maximum number of bytes in receive buffer.
  uint8_t  rxd_amount;	///<Amount of bytes received in the previous reception.
} nrf_rxd_config_t;

/**@brief Structure for Transmission configuration. */
typedef struct
{
	uint8_t  *ptr_txd;    ///<Pointer to the transmission buffer.
	uint8_t  txd_maxcnt;  ///<Maximum number of bytes in receive buffer.
  uint8_t  txd_amount;	///<Amount of bytes transmitted in the previous transmission.
} nrf_txd_config_t;

/**@brief Structure for UARTE configuration. */
typedef struct
{
		NRF_UARTE_Type*     						module;             ///< UARTE module.
	  uint32_t                        enable;
    nrf_pseltxd_config_t            pseltxd;            ///< TXD pin configuration.
    nrf_pselrxd_config_t            pselrxd;            ///< RXD pin configuration.
    nrf_pselcts_config_t            pselcts;            ///< CTS pin configuration.
    nrf_pselrts_config_t            pselrts;            ///< RTS pin configuration.
    uint32_t     				            hwfc;               ///< Flow control configuration.
    uint32_t   					            parity;             ///< Parity configuration.
    uint32_t 						            baudrate;           ///< Baudrate.
		uint32_t                        enable_interrupt;    ///< Enable Interrupt.
		nrf_rxd_config_t                uarte_rxd;          ///<Receiver data structure
    nrf_txd_config_t                uarte_txd;          ///<Transmission data structure   	
} nrf_drv_uarte_config_t;

/**
  * @brief  Initializes the UARTE module 
  * @param  config_uart : Contains the configuration for various UARTE registers
  * @retval None
  */
void app_uarte_hal_uarte_init (nrf_drv_uarte_config_t * config_uarte);

/**
  * @brief  HAL layer function to enable or disable the UARTE module 
  * @param  NRF_UARTE : UARTE module
  * @param  val: set to ENABLE_UART to enable the module\n
	*							 set to DISABLE_UART to disable the module
  * @retval None
  */
void app_uarte_hal_enable_disable_uart (NRF_UARTE_Type* NRF_UARTE, uint32_t val);

/**
  * @brief  HAL layer function to configure the RTS pin 
	* @param  NRF_UARTE : UARTE module
  * @param  val: set to UART_PSELRTS_DISCONNECTED to disconnect the pin\n
	*							 set to pin_num to configure the pin to act as RTS
  * @retval None
  */
void app_uarte_hal_set_pselrts (NRF_UARTE_Type* NRF_UARTE, nrf_pselrts_config_t pselrts);

/**
  * @brief  HAL layer function to configure the TXD pin 
	* @param  NRF_UARTE : UARTE module
  * @param  val: set to UART_PSELTXD_DISCONNECTED to disconnect the pin\n
	*							 set to pin_num to configure the pin to act as TXD
  * @retval None
  */
void app_uarte_hal_set_pseltxd (NRF_UARTE_Type* NRF_UARTE, nrf_pseltxd_config_t pseltxd);

/**
  * @brief  HAL layer function to configure the CTS pin 
	* @param  NRF_UARTE : UARTE module
  * @param  val: set to UART_PSELCTS_DISCONNECTED to disconnect the pin\n
	*							 set to pin_num to configure the pin to act as CTS
  * @retval None
  */
void app_uarte_hal_set_pselcts (NRF_UARTE_Type* NRF_UARTE, nrf_pselcts_config_t pselcts);

/**
  * @brief  HAL layer function to configure the RXD pin 
	* @param  NRF_UARTE : UARTE module
  * @param  val: set to UART_PSELRXD_DISCONNECTED to disconnect the pin\n
	*							 set to pin_num to configure the pin to act as RXD
  * @retval None
  */
void app_uarte_hal_set_pselrxd (NRF_UARTE_Type* NRF_UARTE, nrf_pselrxd_config_t pselrxd);

/**
  * @brief  HAL layer function to configure the Hardware Flow Control
	* @param  NRF_UARTE : UARTE module
  * @param  hwfc_val: set to UART_CONFIG_HARDWARE_FLOW_CONTROL_DISABLE to disable hardware flow control\n
	*							      set to UART_CONFIG_HARDWARE_FLOW_CONTROL_ENABLE to enable hardware flow control
  * @retval None
  */
void app_uarte_hal_set_hwfc (NRF_UARTE_Type* NRF_UARTE, uint32_t hwfc_val);

/**
  * @brief  HAL layer function to configure the parity for the UARTE module
	* @param  NRF_UARTE : UARTE module
  * @param  parity_val: set to UART_CONFIG_PARITY_EXCLUDED to exclude the parity bit\n
	*							        set to UART_CONFIG_PARITY_INCLUDED to include the parity bit
  * @retval None
  */
void app_uarte_hal_set_parity (NRF_UARTE_Type* NRF_UARTE, uint32_t parity_val);

/**
  * @brief  HAL layer function to configures the baudrate for the UARTE module
	* @param  NRF_UARTE : UARTE module
  * @param  baudrate : UART_BAUDRATE_1200   \n
  *                    UART_BAUDRATE_2400   \n 
  *                    UART_BAUDRATE_4800   \n
  *                    UART_BAUDRATE_9600   \n
  *                    UART_BAUDRATE_14400  \n
  *                    UART_BAUDRATE_19200  \n
  *                    UART_BAUDRATE_28800  \n
  *                    UART_BAUDRATE_38400  \n
  *                    UART_BAUDRATE_57600  \n
  *                    UART_BAUDRATE_76800  \n
  *                    UART_BAUDRATE_115200 \n
  *                    UART_BAUDRATE_230400 \n
  *                    UART_BAUDRATE_460800 \n
  *                    UART_BAUDRATE_921600 \n
  *                    UART_BAUDRATE_1M     \n
  * @retval None
  */
void app_uarte_hal_set_baudrate (NRF_UARTE_Type* NRF_UARTE, uint32_t baudrate);

/**
  * @brief  HAL layer function to configure the interrupt for the UARTE module
	* @param  NRF_UARTE : UARTE module
  * @param  val: Combination of different events to generate interrupt
  * @retval None
  */
void app_uarte_hal_enable_uarte_interrupt(NRF_UARTE_Type* NRF_UARTE, uint32_t val);

/**
  * @brief  HAL layer to configures the INTENSET register, to generate interrupt for specific exceptions
	* @param  NRF_UARTE : UARTE module
  * @param  val : Events for which the interrupt needs to be generated 
  *               UART_ENABLE_INTERRUPT_CTS_ENABLE - Enable interrupt for CTS event
  *               UART_ENABLE_INTERRUPT_NCTS_ENABLE - Enable interrupt for NCTS event 
  *               UART_ENABLE_INTERRUPT_RXDRDY_ENABLE - Enable interrupt for RXRDY interrupt
  *               UART_ENABLE_INTERRUPT_TXDRDY_ENABLE - Enable interrupt for TXRDY interrupt
  *               UART_ENABLE_INTERRUPT_ERROR_ENABLE - Enable interrupt for ERROR interrupt
  *               UART_ENABLE_INTERRUPT_RXTO_ENABLE - Enable interrupt for RXTO interrupt
  * @retval None
  */
void app_uarte_hal_set_intenset(NRF_UARTE_Type* NRF_UARTE, uint32_t val);

/**
  * @brief  HAL layer to configure the INTENCLR register, to disable interrupts for specific exceptions
	* @param  NRF_UARTE : UARTE module
  * @param  val : Events for which the interrupt needs to be generated 
  *               UART_ENABLE_INTERRUPT_CTS_DISABLE - Disable interrupt for CTS event
  *               UART_ENABLE_INTERRUPT_NCTS_DISABLE - Disable interrupt for NCTS event 
  *               UART_ENABLE_INTERRUPT_RXDRDY_DISABLE - Disable interrupt for RXRDY interrupt
  *               UART_ENABLE_INTERRUPT_TXDRDY_DISABLE - Disable interrupt for TXRDY interrupt
  *               UART_ENABLE_INTERRUPT_ERROR_DISABLE - Disable interrupt for ERROR interrupt
  *               UART_ENABLE_INTERRUPT_RXTO_DISABLE - Disable interrupt for RXTO interrupt
  * @retval None
  */
void app_uarte_hal_set_intenclr(NRF_UARTE_Type* NRF_UARTE, uint32_t val);

/**
  * @brief  HAL layer to initiate the receiving of UARTE data
	* @param  NRF_UARTE : UARTE module
  * @retval None
  */
void app_uarte_hal_start_receiving (NRF_UARTE_Type* NRF_UARTE);

/**
  * @brief  HAL layer to stop the receiving of UARTE data
	* @param  NRF_UARTE : UARTE module
  * @retval None
  */
void app_uarte_hal_stop_receiving (NRF_UARTE_Type* NRF_UARTE);

/**
  * @brief  HAL layer to start the transmission of UARTE data
	* @param  NRF_UARTE : UARTE module
  * @retval None
  */
void app_uarte_hal_start_transmitting (NRF_UARTE_Type* NRF_UARTE);

/**
  * @brief  HAL layer to stop the transmission of UARTE data
	* @param  NRF_UARTE : UARTE module
  * @retval None
  */
void app_uarte_hal_stop_transmitting (NRF_UARTE_Type* NRF_UARTE);

/**
  * @brief  HAL layer to set the receiver parameters.
	* @param  NRF_UARTE : UART module.
  * @param  *rxd_buff : pointer to the receiver buffer.
  * @param  num_bytes : Number of bytes to be received.
  * @retval None
  */	
void app_uarte_hal_set_rxd (NRF_UARTE_Type* NRF_UARTE, uint8_t *rxd_buff , uint8_t num_bytes);

/**
  * @brief  HAL layer to set the transmitter parameters.
	* @param  NRF_UARTE : UART module.
  * @param  *txd_buff : pointer to the transmitter buffer.
  * @param  num_bytes : Number of bytes to be transmitted.
  * @retval None
  */	
void app_uarte_hal_set_txd (NRF_UARTE_Type* NRF_UARTE, uint8_t *txd_buff, uint8_t num_bytes);

/**
  * @brief  HAL layer to check for an event.
	* @param  NRF_UARTE : UART module.
  * @param  event : Events mentioned in nrf_uarte_event_t.
  * @retval None
  */
bool app_uarte_hal_check_event(NRF_UARTE_Type * NRF_UARTE, nrf_uarte_event_t event);

/**
  * @brief  HAL layer to clear an event.
	* @param  NRF_UARTE : UART module.
  * @param  event : Clear the events mentioned in nrf_uarte_event_t.
  * @retval None
  */	
void app_uarte_hal_clear_event (NRF_UARTE_Type * NRF_UARTE, nrf_uarte_event_t event);

/**
  * @brief  HAL layer to set a task
	* @param  NRF_UARTE : UART module
  * @param  event : Start a particular task. The tasks are mentioned in nrf_uarte_task_t.
  * @retval None
  */
void app_uarte_hal_set_task (NRF_UARTE_Type * NRF_UARTE, nrf_uarte_task_t task);

#endif

