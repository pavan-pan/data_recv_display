
/// @file nrf_drv_uartee.c
/// This file contains the source code for the UART peripheral.
/// Detailed file description.

#include "app_hal_uarte.h"
#include "app_drv_uarte.h"

/**
  * @brief  Enables or Disables the UART module 
  * @param  NRF_UARTE : UART module
	* @param  val: set to ENABLE_UART to enable the module\n
	*							 set to DISABLE_UART to disable the module
  * @retval None
  */
void app_uarte_drv_enable_disable_uarte (NRF_UARTE_Type* NRF_UARTE, uint32_t val)
{
	if (val == ENABLE_UARTE)
	{
		NRF_UARTE->ENABLE = val;
	}
	else if (val == DISABLE_UARTE)
	{
		NRF_UARTE->ENABLE = val;
	}
	else
	{
		//error condition
	}
}

/**
  * @brief  Sets the RTS pin 
	* @param  NRF_UARTE : UART module
  * @param  pselrts: RTS data structure
  * @retval None
  */
void app_uarte_drv_set_pselrts (NRF_UARTE_Type* NRF_UARTE, nrf_pselrts_config_t pselrts)
{
	if (pselrts.pselrts_pin <= 31)
	{
		NRF_UARTE->PSEL.RTS = pselrts.pselrts_pin;
		if (pselrts.pselrts_enable_disable == UARTE_PSELRTS_CONNECTED)
		{
			NRF_UARTE->PSEL.RTS |= UARTE_PSELRTS_CONNECTED;
		}
		else if (pselrts.pselrts_enable_disable == UARTE_PSELRTS_DISCONNECTED)
		{
			NRF_UARTE->PSEL.RTS |= UARTE_PSELRTS_DISCONNECTED;
		}
		else
		{
			//error
		}
	}
	else
	{
		//error
	}
}

/**
  * @brief  Sets the TXD pin 
	* @param  NRF_UARTE : UART module
  * @param  pseltxd: TXD data structure
  * @retval None
  */
void app_uarte_drv_set_pseltxd (NRF_UARTE_Type* NRF_UARTE, nrf_pseltxd_config_t pseltxd)
{
	if (pseltxd.pseltxd_pin <= 31)
	{
		NRF_UARTE->PSEL.TXD = pseltxd.pseltxd_pin;
		if (pseltxd.pseltxd_enable_disable == UARTE_PSELTXD_CONNECTED)
		{
			NRF_UARTE->PSEL.TXD |= UARTE_PSELTXD_CONNECTED;
		}
		else if (pseltxd.pseltxd_enable_disable == UARTE_PSELTXD_DISCONNECTED)
		{
			NRF_UARTE->PSEL.TXD |= UARTE_PSELTXD_DISCONNECTED;
		}
		else
		{
			//error
		}
	}
	else
	{
		//error
	}
}

/**
  * @brief  Sets the CTS pin 
	* @param  NRF_UARTE : UART module
  * @param  pselcts: CTS data structure
  * @retval None
  */
void app_uarte_drv_set_pselcts (NRF_UARTE_Type* NRF_UARTE, nrf_pselcts_config_t pselcts)
{
	if (pselcts.pselcts_pin <= 31)
	{
		NRF_UARTE->PSEL.TXD = pselcts.pselcts_pin;
		if (pselcts.pselcts_enable_disable == UARTE_PSELCTS_CONNECTED)
		{
			NRF_UARTE->PSEL.CTS |= UARTE_PSELCTS_CONNECTED;
		}
		else if (pselcts.pselcts_enable_disable == UARTE_PSELCTS_DISCONNECTED)
		{
			NRF_UARTE->PSEL.TXD |= UARTE_PSELTXD_DISCONNECTED;
		}
		else
		{
			//error
		}
	}
	else
	{
		//error
	}
}

/**
  * @brief  Sets the RXD pin 
	* @param  NRF_UARTE : UART module
  * @param  pselrxd: RXD data structure
  * @retval None
  */
void app_uarte_drv_set_pselrxd (NRF_UARTE_Type* NRF_UARTE, nrf_pselrxd_config_t pselrxd)
{
	if (pselrxd.pselrxd_pin <= 31)
	{
		NRF_UARTE->PSEL.RXD = pselrxd.pselrxd_pin;
		if (pselrxd.pselrxd_enable_disable == UARTE_PSELRXD_CONNECTED)
		{
			NRF_UARTE->PSEL.CTS |= UARTE_PSELCTS_CONNECTED;
		}
		else if (pselrxd.pselrxd_enable_disable == UARTE_PSELRXD_DISCONNECTED)
		{
			NRF_UARTE->PSEL.RXD |= UARTE_PSELRXD_DISCONNECTED;
		}
		else
		{
			//error
		}
	}
	else
	{
		//error
	}
}

/**
  * @brief  Configures the Hardware Flow Control
	* @param  NRF_UARTE : UART module
  * @param  hwfc_val: set to UART_CONFIG_HARDWARE_FLOW_CONTROL_DISABLE to disable hardware flow control\n
	*							      set to UART_CONFIG_HARDWARE_FLOW_CONTROL_ENABLE to enable hardware flow control
  * @retval None
  */
void app_uarte_drv_set_hwfc (NRF_UARTE_Type* NRF_UARTE, uint32_t hwfc_val)
{
	if (hwfc_val == UARTE_CONFIG_HARDWARE_FLOW_CONTROL_DISABLE)
	{
		NRF_UARTE->CONFIG |= (UARTE_CONFIG_HARDWARE_FLOW_CONTROL_DISABLE << UARTE_CONFIG_HARDWARE_FLOW_CONTROL_POS);
	}
	else if (hwfc_val == UARTE_CONFIG_HARDWARE_FLOW_CONTROL_ENABLE)
	{
		NRF_UARTE->CONFIG |= (UARTE_CONFIG_HARDWARE_FLOW_CONTROL_ENABLE << UARTE_CONFIG_HARDWARE_FLOW_CONTROL_POS);
	}
	else
	{
		//error
	}
}

/**
  * @brief  Configures the parity for the UART module
	* @param  NRF_UARTE : UART module
  * @param  parity_val: set to UART_CONFIG_PARITY_EXCLUDED to exclude the parity bit\n
	*							        set to UART_CONFIG_PARITY_INCLUDED to include the parity bit
  * @retval None
  */
void app_uarte_drv_set_parity (NRF_UARTE_Type* NRF_UARTE, uint32_t parity_val)
{
	if (parity_val == UARTE_CONFIG_PARITY_EXCLUDED)
	{
		NRF_UARTE->CONFIG |= (UARTE_CONFIG_PARITY_EXCLUDED << UARTE_CONFIG_PARITY_POS);
	}
	else if (parity_val == UARTE_CONFIG_PARITY_INCLUDED)
	{
		NRF_UARTE->CONFIG |= (UARTE_CONFIG_PARITY_INCLUDED << UARTE_CONFIG_PARITY_POS);
	}
	else
	{
		//error
	}
}

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
void app_uarte_drv_set_baudrate (NRF_UARTE_Type* NRF_UARTE, uint32_t baudrate)
{
	if (baudrate == UARTE_BAUDRATE_1200)
	{
		NRF_UARTE->BAUDRATE = UARTE_BAUDRATE_1200;
	}
	else if (baudrate == UARTE_BAUDRATE_2400)
	{
		NRF_UARTE->BAUDRATE = UARTE_BAUDRATE_2400;
	}
	else if (baudrate == UARTE_BAUDRATE_4800)
	{
		NRF_UARTE->BAUDRATE = UARTE_BAUDRATE_4800;
	}
	else if (baudrate == UARTE_BAUDRATE_9600)
	{
		NRF_UARTE->BAUDRATE = UARTE_BAUDRATE_9600;
	}
	else if (baudrate == UARTE_BAUDRATE_14400)
	{
		NRF_UARTE->BAUDRATE = UARTE_BAUDRATE_14400;
	}
	else if (baudrate == UARTE_BAUDRATE_19200)
	{
		NRF_UARTE->BAUDRATE = UARTE_BAUDRATE_19200;
	}
	else if (baudrate == UARTE_BAUDRATE_28800)
	{
		NRF_UARTE->BAUDRATE = UARTE_BAUDRATE_28800;
	}
	else if (baudrate == UARTE_BAUDRATE_38400)
	{
		NRF_UARTE->BAUDRATE = UARTE_BAUDRATE_38400;
	}
	else if (baudrate == UARTE_BAUDRATE_57600)
	{
		NRF_UARTE->BAUDRATE = UARTE_BAUDRATE_57600;
	}
	else if (baudrate == UARTE_BAUDRATE_76800)
	{
		NRF_UARTE->BAUDRATE = UARTE_BAUDRATE_76800;
	}
	else if (baudrate == UARTE_BAUDRATE_115200)
	{
		NRF_UARTE->BAUDRATE = UARTE_BAUDRATE_115200;
	}
	else if (baudrate == UARTE_BAUDRATE_230400)
	{
		NRF_UARTE->BAUDRATE = UARTE_BAUDRATE_230400;
	}
	else if (baudrate == UARTE_BAUDRATE_250000)
	{
		NRF_UARTE->BAUDRATE = UARTE_BAUDRATE_250000;
	}
	else if (baudrate == UARTE_BAUDRATE_460800)
	{
		NRF_UARTE->BAUDRATE = UARTE_BAUDRATE_460800;
	}
	else if (baudrate == UARTE_BAUDRATE_921600)
	{
		NRF_UARTE->BAUDRATE = UARTE_BAUDRATE_921600;
	}
	else if (baudrate == UARTE_BAUDRATE_1M)
	{
		NRF_UARTE->BAUDRATE = UARTE_BAUDRATE_1M;
	}
	else
	{
		//error
	}
}

/**
  * @brief  Initiates the receiving of UART data
	* @param  NRF_UARTE : UART module
  * @retval None
  */
void app_uarte_drv_start_receiving (NRF_UARTE_Type* NRF_UARTE)
{
	NRF_UARTE->TASKS_STARTRX = 1;
}

/**
  * @brief  Stops the receiving of UART data
	* @param  NRF_UARTE : UART module
  * @retval None
  */
void app_uarte_drv_stop_receiving (NRF_UARTE_Type* NRF_UARTE)
{
	NRF_UARTE->TASKS_STOPRX = 1;
}

/**
  * @brief  Initiates the transmitting of UART data
	* @param  NRF_UARTE : UART module
  * @retval None
  */
void app_uarte_drv_start_transmitting (NRF_UARTE_Type* NRF_UARTE)
{
	NRF_UARTE->TASKS_STARTTX = 1;
}

/**
  * @brief  Stops the transmitting of UART data
	* @param  NRF_UARTE : UART module
  * @retval None
  */
void app_uarte_drv_stop_transmitting (NRF_UARTE_Type* NRF_UARTE)
{
	NRF_UARTE->TASKS_STOPTX = 1;
}

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
void app_uarte_drv_set_intenset(NRF_UARTE_Type* NRF_UARTE, uint32_t val)
{
	NRF_UARTE->INTENSET = val;
}

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
void app_uarte_drv_set_intenclr(NRF_UARTE_Type* NRF_UARTE, uint32_t val)
{
	NRF_UARTE->INTENSET = val;
}

/**
  * @brief  Sets the receiver parameters : receiver buffer and the number of bytes to be received
	* @param  NRF_UARTE : UART module \n
  * @param  rxd_buff : Pointer to the receiver buffer \n
  * @param  num_bytes : Number of bytes to be received
  * @retval None
  */
void app_uarte_drv_set_rxd (NRF_UARTE_Type* NRF_UARTE, uint8_t *rxd_buff, uint8_t num_bytes)
{
	NRF_UARTE->RXD.PTR = (uint32_t) rxd_buff;
	NRF_UARTE->RXD.MAXCNT = num_bytes;
}

/**
  * @brief  Sets the transmission parameters : Transmit buffer and the number of bytes to be transmitted
	* @param  NRF_UARTE : UART module
  * @param  txd_buff : Pointer to the transmitter buffer 
  * @param  num_bytes : Number of bytes to be transmitted
  * @retval None
  */
void app_uarte_drv_set_txd (NRF_UARTE_Type* NRF_UARTE, uint8_t *txd_buff, uint8_t num_bytes)
{
	NRF_UARTE->TXD.PTR = (uint32_t) txd_buff;
	NRF_UARTE->TXD.MAXCNT = num_bytes;
}
