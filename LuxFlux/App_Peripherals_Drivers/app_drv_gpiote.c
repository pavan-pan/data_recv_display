
/// @file app_drv_gpiote.c
/// This file contains the source code for the GPIOTE peripheral.
/// Detailed file description.

#include "nrf_drv_gpiote.h"


///// @brief  Initializes the GPIOTE peripheral
///// @param  None 
///// @retval None
//void app_gpiote_drv_init(gpiote_config_t *pin_config)
//{
//	//NVIC_EnableIRQ(GPIOTE_IRQn);
//	app_gpiote_drv_enable_gpiote_IRQ();
//	//NVIC_SetPriority(GPIOTE_IRQn, 6);
//	app_gpiote_drv_set_interrupt_priority(pin_config->interrupt_priority);
//	app_gpiote_drv_clear_port_event();
//	app_gpiote_drv_enable_interrupt(pin_config->channel, false);
//}

void app_gpiote_drv_enable_gpiote_IRQ()
{
	NVIC_EnableIRQ(GPIOTE_IRQn);
}

void app_gpiote_drv_set_interrupt_priority(uint8_t val)
{
	NVIC_SetPriority(GPIOTE_IRQn, val);
}

/// @brief  Configures a GPIOTE event 
/// @param  channel: GPIOTE channel 
/// @param  pin: GPIO pin number associated with the event
/// @param  polarity: Operation on input that shall trigger the event
/// @retval None
void app_gpiote_drv_configure_event(uint32_t channel, uint32_t pin, uint32_t polarity)
{
	NRF_GPIOTE->CONFIG[channel] &= ~(GPIOTE_CONFIG_PSEL_Msk | GPIOTE_CONFIG_POLARITY_Msk);
	NRF_GPIOTE->CONFIG[channel] |= ( (pin << GPIOTE_CONFIG_PSEL_Pos) & GPIOTE_CONFIG_PSEL_Msk) |
                              ((polarity << GPIOTE_CONFIG_POLARITY_Pos) & GPIOTE_CONFIG_POLARITY_Msk);
	NRF_GPIOTE->CONFIG[channel] |= 0x01;
}


/// @brief  Clears an event associated with the pin
/// @param  channel: GPIOTE channel 
/// @param  None
/// @retval None
void app_gpiote_drv_clear_pin_event (uint8_t channel)
{
	NRF_GPIOTE->EVENTS_IN[channel] &= ~(1 << channel);
}


/// @brief  Clears the port event
/// @param  None
/// @retval None
void app_gpiote_drv_clear_port_event (void)
{
	NRF_GPIOTE->EVENTS_PORT = 0;
}


/// @brief  Enables interrupt on a particular channel or port
/// @param  channel : GPIOTE channel for which the interrupt has to be enabled
/// @param  enable_port : True, if the port interrupt has to be enabled 
/// @retval None
void app_gpiote_drv_enable_interrupt(uint8_t channel, bool enable_port)
{
	if (enable_port)
	{
		NRF_GPIOTE->INTENSET |= (1UL << 31UL);
	}
	else
	{
		NRF_GPIOTE->INTENSET |= (1UL << channel);
	}
}


/// @brief  Disables interrupt on a particular channel or port
/// @param  channel : GPIOTE channel for which the interrupt has to be enabled
/// @param  enable_port : True, if the port interrupt has to be enabled 
/// @retval None
void app_gpiote_drv_disable_interrupt(uint8_t channel, bool disable_port)
{
	if (disable_port)
	{
		NRF_GPIOTE->INTENCLR |= (1UL << 31UL);
	}
	else
	{
		NRF_GPIOTE->INTENCLR |= (1UL << channel);
	}
}
	
