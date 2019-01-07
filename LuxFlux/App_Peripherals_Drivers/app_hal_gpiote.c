
/// @file app_hal_gpiote.c
/// This file contains the HAL for the GPIOTE peripheral.
/// Detailed file description.

#include "app_hal_gpiote.h"

void GPIOTE_IRQHandler(void)
{
		//execute_handler = true;
	  //in_pin_handler();	
		//NRF_LOG_INFO ("INTERRRUPT FROM BQ25120");
	  app_gpiote_hal_clear_pin_event(0);
}

void app_gpiote_hal_init(gpiote_config_t *pin_config)
{
	
	app_gpiote_hal_enable_gpiote_IRQ();
	
	//app_gpiote_hal_set_interrupt_priority(pin_config->interrupt_priority);
	app_gpiote_hal_clear_port_event();
	app_gpiote_hal_enable_interrupt(pin_config->channel, false);
	
	app_gpiote_hal_configure_event (pin_config->channel, pin_config->pin, pin_config->polarity);
}

void app_gpiote_hal_enable_gpiote_IRQ()
{
	app_gpiote_drv_enable_gpiote_IRQ();
}

void app_gpiote_hal_set_interrupt_priority(uint8_t val)
{
	app_gpiote_drv_set_interrupt_priority(val);
}

void app_gpiote_hal_configure_event(uint32_t channel, uint32_t pin, uint32_t polarity)
{
	app_gpiote_drv_configure_event(channel, pin, polarity);
}

void app_gpiote_hal_clear_pin_event (uint8_t channel)
{
	app_gpiote_drv_clear_pin_event (channel);
}

void app_gpiote_hal_clear_port_event()
{
	app_gpiote_drv_clear_port_event();
}

void app_gpiote_hal_enable_interrupt(uint8_t channel, bool port)
{
	app_gpiote_drv_enable_interrupt(channel, port);
}

void app_gpiote_hal_disable_interrupt(uint8_t channel, bool disable_port)
{
	app_gpiote_hal_disable_interrupt(channel, disable_port);
}
