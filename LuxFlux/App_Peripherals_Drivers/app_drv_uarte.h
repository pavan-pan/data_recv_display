
/// @file nrf_drv_uarte.h
/// This file is the header file for the NRF UART driver module.
/// Detailed file description.

#ifndef NRF_DRV_UARTE_H
#define NRF_DRV_UARTE_H

#include "app_hal_uarte.h"

/**
  * @brief  Enables or Disables the UARTE module 
  * @param  NRF_UARTE : UART module
	* @param  val: set to ENABLE_UART to enable the module\n
	*							 set to DISABLE_UART to disable the module
  * @retval None
  */
void app_uarte_drv_enable_disable_uarte (NRF_UARTE_Type* NRF_UARTE, uint32_t val);

/**
  * @brief  Sets the RTS pin 
	* @param  NRF_UARTE : UART module
  * @param  pselrts: RTS data structure
  * @retval None
  */
void app_uarte_drv_set_pselrts (NRF_UARTE_Type* NRF_UARTE, nrf_pselrts_config_t pselrts);

/**
  * @brief  Sets the TXD pin 
	* @param  NRF_UARTE : UART module
  * @param  pseltxd: TXD data structure
  * @retval None
  */
void app_uarte_drv_set_pseltxd (NRF_UARTE_Type* NRF_UARTE, nrf_pseltxd_config_t pseltxd);

/**
  * @brief  Sets the CTS pin 
	* @param  NRF_UARTE : UART module
  * @param  pselcts: CTS data structure
  * @retval None
  */
void app_uarte_drv_set_pselcts (NRF_UARTE_Type* NRF_UARTE, nrf_pselcts_config_t pselcts);

/**
  * @brief  Sets the RXD pin 
	* @param  NRF_UARTE : UART module
  * @param  pselrxd: RXD data structure
  * @retval None
  */
void app_uarte_drv_set_pselrxd (NRF_UARTE_Type* NRF_UARTE, nrf_pselrxd_config_t pselrxd);

/**
  * @brief  Configures the Hardware Flow Control
	* @param  NRF_UARTE : UART module
  * @param  hwfc_val: set to UART_CONFIG_HARDWARE_FLOW_CONTROL_DISABLE to disable hardware flow control\n
	*							      set to UART_CONFIG_HARDWARE_FLOW_CONTROL_ENABLE to enable hardware flow control
  * @retval None
  */
void app_uarte_drv_set_hwfc (NRF_UARTE_Type* NRF_UARTE, uint32_t hwfc_val);

/**
  * @brief  Configures the parity for the UART module
	* @param  NRF_UARTE : UART module
  * @param  parity_val: set to UART_CONFIG_PARITY_EXCLUDED to exclude the parity bit\n
	*							        set to UART_CONFIG_PARITY_INCLUDED to include the parity bit
  * @retval None
  */
void app_uarte_drv_set_parity (NRF_UARTE_Type* NRF_UARTE, uint32_t parity_val);

/**
  * @brief  Configures the baudrate for the UART module
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
void app_uarte_drv_set_baudrate (NRF_UARTE_Type* NRF_UARTE, uint32_t baudrate);

/**
  * @brief  Initiates the receiving of UART data
	* @param  NRF_UARTE : UART module
  * @retval None
  */
void app_uarte_drv_start_receiving (NRF_UARTE_Type* NRF_UARTE);

/**
  * @brief  Stops the receiving of UART data
	* @param  NRF_UARTE : UART module
  * @retval None
  */
void app_uarte_drv_stop_receiving (NRF_UARTE_Type* NRF_UARTE);

/**
  * @brief  Initiates the transmitting of UART data
	* @param  NRF_UARTE : UART module
  * @retval None
  */
void app_uarte_drv_start_transmitting (NRF_UARTE_Type* NRF_UARTE);

/**
  * @brief  Stops the transmitting of UART data
	* @param  NRF_UARTE : UART module
  * @retval None
  */
void app_uarte_drv_stop_transmitting (NRF_UARTE_Type* NRF_UARTE);

/**
  * @brief  Configures the INTENSET register, to generate interrupt for specific exceptions
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
void app_uarte_drv_set_intenset(NRF_UARTE_Type* NRF_UARTE, uint32_t val);

/**
  * @brief  Configures the INTENCLR register, to disable interrupts for specific exceptions
	* @param  NRF_UARTE : UART module
  * @param  val : Events for which the interrupt needs to be generated 
  *               UART_ENABLE_INTERRUPT_CTS_DISABLE - Disable interrupt for CTS event
  *               UART_ENABLE_INTERRUPT_NCTS_DISABLE - Disable interrupt for NCTS event 
  *               UART_ENABLE_INTERRUPT_RXDRDY_DISABLE - Disable interrupt for RXRDY interrupt
  *               UART_ENABLE_INTERRUPT_TXDRDY_DISABLE - Disable interrupt for TXRDY interrupt
  *               UART_ENABLE_INTERRUPT_ERROR_DISABLE - Disable interrupt for ERROR interrupt
  *               UART_ENABLE_INTERRUPT_RXTO_DISABLE - Disable interrupt for RXTO interrupt
  * @retval None
  */
void app_uarte_drv_set_intenclr(NRF_UARTE_Type* NRF_UARTE, uint32_t val);

void app_uarte_drv_set_rxd (NRF_UARTE_Type* NRF_UARTE, uint8_t *rxd_buff, uint8_t num_bytes);
void app_uarte_drv_set_txd (NRF_UARTE_Type* NRF_UARTE, uint8_t *txd_buff, uint8_t num_bytes);
	
#endif
