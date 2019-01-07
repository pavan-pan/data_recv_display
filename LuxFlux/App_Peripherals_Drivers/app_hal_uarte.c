#include "app_hal_uarte.h"
#include "app_drv_uarte.h"



/**
  * @brief  Initializes the UARTE module 
  * @param  config_uarte : Contains the configuration for various UARTE registers
  * @retval None
  */
void app_uarte_hal_uarte_init (nrf_drv_uarte_config_t * config_uarte)
{
	app_uarte_drv_enable_disable_uarte(config_uarte->module, config_uarte->enable);
	app_uarte_hal_set_pselrts(config_uarte->module, config_uarte->pselrts);
	app_uarte_hal_set_pselcts(config_uarte->module, config_uarte->pselcts);
	app_uarte_hal_set_pseltxd(config_uarte->module, config_uarte->pseltxd);
	app_uarte_hal_set_pselrxd(config_uarte->module, config_uarte->pselrxd);
	
	app_uarte_hal_set_hwfc(config_uarte->module, config_uarte->hwfc);
	app_uarte_hal_set_parity(config_uarte->module, config_uarte->parity);
	app_uarte_hal_set_baudrate(config_uarte->module, config_uarte->baudrate);
	app_uarte_hal_enable_uarte_interrupt(config_uarte->module, config_uarte->enable_interrupt);
	
	//app_uarte_hal_set_rxd(config_uarte->module, config_uarte->uarte_rxd);
	//app_uarte_hal_set_txd(config_uarte->module, config_uarte->uarte_txd);
	
}

/**
  * @brief  HAL layer function to enable or disable the UART module 
  * @param  NRF_UARTE : UART module
  * @param  val: set to ENABLE_UART to enable the module\n
	*							 set to DISABLE_UART to disable the module
  * @retval None
  */
void app_uarte_hal_enable_disable_uarte (NRF_UARTE_Type* NRF_UARTE, uint32_t val)
{
	app_uarte_drv_enable_disable_uarte(NRF_UARTE, val);
}

/**
  * @brief  HAL layer function to configure the RTS pin 
	* @param  NRF_UARTE : UART module
  * @param  val: set to UART_PSELRTS_DISCONNECTED to disconnect the pin\n
	*							 set to pin_num to configure the pin to act as RTS
  * @retval None
  */
void app_uarte_hal_set_pselrts (NRF_UARTE_Type* NRF_UARTE, nrf_pselrts_config_t pselrts)
{
	app_uarte_drv_set_pselrts(NRF_UARTE, pselrts);
}

/**
  * @brief  HAL layer function to configure the TXD pin 
	* @param  NRF_UARTE : UART module
  * @param  val: set to UART_PSELTXD_DISCONNECTED to disconnect the pin\n
	*							 set to pin_num to configure the pin to act as TXD
  * @retval None
  */
void app_uarte_hal_set_pseltxd (NRF_UARTE_Type* NRF_UARTE, nrf_pseltxd_config_t pseltxd)
{
	app_uarte_drv_set_pseltxd(NRF_UARTE, pseltxd);
}

/**
  * @brief  HAL layer function to configure the CTS pin 
	* @param  NRF_UARTE : UART module
  * @param  val: set to UART_PSELCTS_DISCONNECTED to disconnect the pin\n
	*							 set to pin_num to configure the pin to act as CTS
  * @retval None
  */
void app_uarte_hal_set_pselcts (NRF_UARTE_Type* NRF_UARTE, nrf_pselcts_config_t pselcts)
{
	app_uarte_drv_set_pselcts(NRF_UARTE, pselcts);
}

/**
  * @brief  HAL layer function to configure the RXD pin 
	* @param  NRF_UARTE : UART module
  * @param  val: set to UART_PSELRXD_DISCONNECTED to disconnect the pin\n
	*							 set to pin_num to configure the pin to act as RXD
  * @retval None
  */
void app_uarte_hal_set_pselrxd (NRF_UARTE_Type* NRF_UARTE, nrf_pselrxd_config_t pselrxd)
{
	app_uarte_drv_set_pselrxd(NRF_UARTE, pselrxd);
}

/**
  * @brief  HAL layer function to configure the Hardware Flow Control
	* @param  NRF_UARTE : UART module
  * @param  hwfc_val: set to UART_CONFIG_HARDWARE_FLOW_CONTROL_DISABLE to disable hardware flow control\n
	*							      set to UART_CONFIG_HARDWARE_FLOW_CONTROL_ENABLE to enable hardware flow control
  * @retval None
  */
void app_uarte_hal_set_hwfc (NRF_UARTE_Type* NRF_UARTE, uint32_t hwfc_val)
{
	app_uarte_drv_set_hwfc(NRF_UARTE, hwfc_val);
}

/**
  * @brief  HAL layer function to configure the parity for the UART module
	* @param  NRF_UARTE : UART module
  * @param  parity_val: set to UART_CONFIG_PARITY_EXCLUDED to exclude the parity bit\n
	*							        set to UART_CONFIG_PARITY_INCLUDED to include the parity bit
  * @retval None
  */
void app_uarte_hal_set_parity (NRF_UARTE_Type* NRF_UARTE, uint32_t parity_val)
{
	app_uarte_drv_set_parity(NRF_UARTE, parity_val);
}

/**
  * @brief  HAL layer function to configures the baudrate for the UART module
	* @param  NRF_UARTE : UART module
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
void app_uarte_hal_set_baudrate (NRF_UARTE_Type* NRF_UARTE, uint32_t baudrate)
{
	app_uarte_drv_set_baudrate (NRF_UARTE, baudrate);
}

/**
  * @brief  HAL layer function to configure the interrupt for the UART module
	* @param  NRF_UARTE : UART module
  * @param  val: Combination of different events to generate interrupt
  * @retval None
  */
void app_uarte_hal_enable_uarte_interrupt(NRF_UARTE_Type* NRF_UARTE, uint32_t val)
{
	NVIC_DisableIRQ(UARTE0_UART0_IRQn);
	if (val != 0)
	{
		app_uarte_hal_set_intenset (NRF_UARTE, val);
		NVIC_EnableIRQ(UARTE0_UART0_IRQn);
	}
}

/**
  * @brief  HAL layer to configures the INTENSET register, to generate interrupt for specific exceptions
	* @param  NRF_UARTE : UART module
  * @param  val : Events for which the interrupt needs to be generated 
  *               UART_ENABLE_INTERRUPT_CTS_ENABLE - Enable interrupt for CTS event
  *               UART_ENABLE_INTERRUPT_NCTS_ENABLE - Enable interrupt for NCTS event 
  *               UART_ENABLE_INTERRUPT_RXDRDY_ENABLE - Enable interrupt for RXRDY interrupt
  *               UART_ENABLE_INTERRUPT_TXDRDY_ENABLE - Enable interrupt for TXRDY interrupt
  *               UART_ENABLE_INTERRUPT_ERROR_ENABLE - Enable interrupt for ERROR interrupt
  *               UART_ENABLE_INTERRUPT_RXTO_ENABLE - Enable interrupt for RXTO interrupt
  * @retval None
  */
void app_uarte_hal_set_intenset(NRF_UARTE_Type* NRF_UARTE, uint32_t val)
{
	app_uarte_drv_set_intenset(NRF_UARTE, val);
}

/**
  * @brief  HAL layer to configure the INTENCLR register, to disable interrupts for specific exceptions
	* @param  NRF_UARTE : UART module
  * @param  val : Events for which the interrupt needs to be generated 
  *               UART_ENABLE_INTERRUPT_CTS_DISABLE - Disable interrupt for CTS event.
  *               UART_ENABLE_INTERRUPT_NCTS_DISABLE - Disable interrupt for NCTS event.
  *               UART_ENABLE_INTERRUPT_RXDRDY_DISABLE - Disable interrupt for RXRDY interrupt.
  *               UART_ENABLE_INTERRUPT_TXDRDY_DISABLE - Disable interrupt for TXRDY interrupt.
  *               UART_ENABLE_INTERRUPT_ERROR_DISABLE - Disable interrupt for ERROR interrupt.
  *               UART_ENABLE_INTERRUPT_RXTO_DISABLE - Disable interrupt for RXTO interrupt.
  * @retval None
  */
void app_uarte_hal_set_intenclr(NRF_UARTE_Type* NRF_UARTE, uint32_t val)
{
	app_uarte_drv_set_intenclr(NRF_UARTE, val);
}

/**
  * @brief  HAL layer to initiate the receiving of UART data.
	* @param  NRF_UARTE : UART module.
  * @retval None.
  */
void app_uarte_hal_start_receiving (NRF_UARTE_Type* NRF_UARTE)
{
	app_uarte_drv_start_receiving(NRF_UARTE);
}

/**
  * @brief  HAL layer to stop the receiving of UART data.
	* @param  NRF_UARTE : UART module.
  * @retval None.
  */
void app_uarte_hal_stop_receiving (NRF_UARTE_Type* NRF_UARTE)
{
	app_uarte_drv_stop_receiving(NRF_UARTE);
}

/**
  * @brief  HAL layer to start the transmission of UART data.
	* @param  NRF_UARTE : UART module.
  * @retval None.
  */
void app_uarte_hal_start_transmitting (NRF_UARTE_Type* NRF_UARTE)
{
	app_uarte_drv_start_transmitting(NRF_UARTE);
}

/**
  * @brief  HAL layer to stop the transmission of UART data.
	* @param  NRF_UARTE : UART module.
  * @retval None.
  */
void app_uarte_hal_stop_transmitting (NRF_UARTE_Type* NRF_UARTE)
{
	app_uarte_drv_stop_transmitting(NRF_UARTE);
}

/**
  * @brief  HAL layer to set the receiver parameters.
	* @param  NRF_UARTE : UART module.
  * @param  *rxd_buff : pointer to the receiver buffer.
  * @param  num_bytes : Number of bytes to be received.
  * @retval None
  */	
void app_uarte_hal_set_rxd (NRF_UARTE_Type* NRF_UARTE, uint8_t *rxd_buff , uint8_t num_bytes)
{
	app_uarte_drv_set_rxd (NRF_UARTE, rxd_buff, num_bytes);
}

/**
  * @brief  HAL layer to set the transmitter parameters.
	* @param  NRF_UARTE : UART module.
  * @param  *txd_buff : pointer to the transmitter buffer.
  * @param  num_bytes : Number of bytes to be transmitted.
  * @retval None
  */	
void app_uarte_hal_set_txd (NRF_UARTE_Type* NRF_UARTE, uint8_t *txd_buff, uint8_t num_bytes)
{
	app_uarte_drv_set_txd (NRF_UARTE, txd_buff, num_bytes);
}

/**
  * @brief  HAL layer to check for an event.
	* @param  NRF_UARTE : UART module.
  * @param  event : Events mentioned in nrf_uarte_event_t.
  * @retval None
  */	
bool app_uarte_hal_check_event(NRF_UARTE_Type * NRF_UARTE, nrf_uarte_event_t event)
{
    return (bool)*(volatile uint32_t *)((uint8_t *)NRF_UARTE + (uint32_t)event);
}

/**
  * @brief  HAL layer to clear an event.
	* @param  NRF_UARTE : UART module.
  * @param  event : Clear the events mentioned in nrf_uarte_event_t.
  * @retval None
  */	
void app_uarte_hal_clear_event (NRF_UARTE_Type * NRF_UARTE, nrf_uarte_event_t event)
{
	*((volatile uint32_t *)((uint8_t *)NRF_UARTE + (uint32_t)event)) = 0x0UL;
}

/**
  * @brief  HAL layer to set a task
	* @param  NRF_UARTE : UART module
  * @param  event : Start a particular task. The tasks are mentioned in nrf_uarte_task_t.
  * @retval None
  */
void app_uarte_hal_set_task (NRF_UARTE_Type * NRF_UARTE, nrf_uarte_task_t task)
{
	*((volatile uint32_t *)((uint8_t *)NRF_UARTE + (uint32_t)task)) = 0x1UL;
}
