
/// @file app_hal_gpiote.h
/// This file contains the HAL for the GPIOTE peripheral.
/// Detailed file description.

#ifndef LP2_HAL_GPIOTE_H
#define LP2_HAL_GPIOTE_H

#include <stdint.h>
#include "nrf52.h"
#include "app_drv_gpiote.h"

void app_gpiote_hal_init(gpiote_config_t *pin_config);

void app_gpiote_hal_enable_gpiote_IRQ(void);

void app_gpiote_hal_set_interrupt_priority(uint8_t val);

void app_gpiote_hal_configure_event(uint32_t channel, uint32_t pin, uint32_t polarity);
	
void app_gpiote_hal_clear_pin_event (uint8_t channel);
void app_gpiote_hal_clear_port_event(void);

void app_gpiote_hal_enable_interrupt(uint8_t channel, bool port);

#endif
