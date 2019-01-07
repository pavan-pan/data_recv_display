
/// @file gpiote.h
/// This file is the header file for the GPIOTE peripheral.
/// Detailed file description.

#ifndef LP2_DRV_GPIOTE_H
#define LP2_DRV_GPIOTE_H

#include <stdbool.h>
#include "nrf52.h"
#include "core_cm4.h"


#define GPIOTE_CONFIG_PSEL_Pos (8UL) /*!< Position of PSEL field. */
#define GPIOTE_CONFIG_PSEL_Msk (0x1FUL << GPIOTE_CONFIG_PSEL_Pos) /*!< Bit mask of PSEL field. */

#define GPIOTE_CONFIG_POLARITY_Pos (16UL) /*!< Position of POLARITY field. */
#define GPIOTE_CONFIG_POLARITY_Msk (0x3UL << GPIOTE_CONFIG_POLARITY_Pos) /*!< Bit mask of POLARITY field. */
#define GPIOTE_CONFIG_POLARITY_None (0UL) /*!< Task mode: No effect on pin from OUT[n] task. Event mode: no IN[n] event generated on pin activity. */
#define GPIOTE_CONFIG_POLARITY_LoToHi (1UL) /*!< Task mode: Set pin from OUT[n] task. Event mode: Generate IN[n] event when rising edge on pin. */
#define GPIOTE_CONFIG_POLARITY_HiToLo (2UL) /*!< Task mode: Clear pin from OUT[n] task. Event mode: Generate IN[n] event when falling edge on pin. */
#define GPIOTE_CONFIG_POLARITY_Toggle (3UL) /*!< Task mode: Toggle pin from OUT[n]. Event mode: Generate IN[n] when any change on pin. */

/* When in task mode: Initial value of the output when the GPIOTE channel is configured. When in event mode: No effect. */
#define GPIOTE_CONFIG_OUTINIT_Pos (20UL) /*!< Position of OUTINIT field. */
#define GPIOTE_CONFIG_OUTINIT_Msk (0x1UL << GPIOTE_CONFIG_OUTINIT_Pos) /*!< Bit mask of OUTINIT field. */
#define GPIOTE_CONFIG_OUTINIT_Low (0UL) /*!< Task mode: Initial value of pin before task triggering is low */
#define GPIOTE_CONFIG_OUTINIT_High (1UL) /*!< Task mode: Initial value of pin before task triggering is high */


typedef struct
{
	uint8_t interrupt_priority;
	uint8_t channel;
	uint32_t pin;
	uint32_t polarity;
} gpiote_config_t;

/// @brief  Initializes the GPIOTE peripheral
/// @param  None 
/// @retval None
void app_gpiote_drv_init(gpiote_config_t *pin_config);

/// @brief  Configures a GPIOTE event 
/// @param  channel: GPIOTE channel 
/// @param  pin: GPIO pin number associated with the event
/// @param  polarity: Operation on input that shall trigger the event
/// @retval None
void app_gpiote_drv_configure_event(uint32_t channel, uint32_t pin, uint32_t polarity);

/// @brief  Clears an event associated with the pin
/// @param  channel: GPIOTE channel 
/// @param  None
/// @retval None
void app_gpiote_drv_clear_pin_event (uint8_t channel);

/// @brief  Clears the port event
/// @param  None
/// @retval None
void app_gpiote_drv_clear_port_event (void);

/// @brief  Enables interrupt on a particular channel or port
/// @param  channel : GPIOTE channel for which the interrupt has to be enabled
/// @param  enable_port : True, if the port interrupt has to be enabled 
/// @retval None
void app_gpiote_drv_enable_interrupt(uint8_t channel, bool enable_port);
	
/// @brief  Disables interrupt on a particular channel or port
/// @param  channel : GPIOTE channel for which the interrupt has to be enabled
/// @param  enable_port : True, if the port interrupt has to be enabled 
/// @retval None
void app_gpiote_drv_disable_interrupt(uint8_t channel, bool disable_port);

void app_gpiote_drv_enable_gpiote_IRQ(void);

void app_gpiote_drv_set_interrupt_priority(uint8_t val);

#endif
