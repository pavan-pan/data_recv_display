
/// @file app_drv_gpio.c
/// This file contains the source code for the GPIO peripheral.
/// Detailed file description.


#include "app_drv_gpio.h"
#include "nrf52_bitfields.h"

/**
  * @brief  Configures pin direction  
  * @param  pin: pin number 
  * @param  val: set to '0' for input\n
	*							 set to '1' for output
  */
void app_gpio_drv_configure_pin_direction(uint8_t pin, uint8_t val, NRF_GPIO_Type *NRF_GPIO_MODULE)
{
	NRF_GPIO_MODULE->PIN_CNF[pin] |= (val << PIN_DIR_POS);
}

/**
  * @brief  Configures the input buffer for the pin  
  * @param  pin: pin number 
  * @param  val: set to CONNECT_INPUT_BUFFER to connect to the input buffer\n
	*							 set to DISCONNECT_INPUT_BUFFER to disconnect from the input buffer
  */
void app_gpio_drv_configure_input_buffer (uint8_t pin, uint8_t val, NRF_GPIO_Type *NRF_GPIO_MODULE)
{
	if (val == CONNECT_INPUT_BUFFER)
	{
		NRF_GPIO_MODULE->PIN_CNF[pin] &= ~(1 << PIN_INPUT_BUFFER_POS);
	}
	else
	{
		NRF_GPIO_MODULE->PIN_CNF[pin] |= (1 << PIN_INPUT_BUFFER_POS);
	}
}

/**
  * @brief  Configures the pull configuration for the pin 
  * @param  pin: pin number 
  * @param  val: set to CONNECT_INPUT_BUFFER to connect to the input buffer\n
	*							 set to DISCONNECT_INPUT_BUFFER to disconnect from the input buffer
  */
void app_gpio_drv_configure_pull_configuration (uint8_t pin, uint8_t val, NRF_GPIO_Type *NRF_GPIO_MODULE)
{
	NRF_GPIO_MODULE->PIN_CNF[pin] |= (val << PIN_PULL_CONFIG_POS);
}

/**
  * @brief  Configures the drive configuration for the pin 
  * @param  pin: pin number 
  * @param  val: STANDARD_0_STANDARD_1  	- Standard '0', standard '1'\n
	*							 HIGH_0_STANDARD_1 				- High drive '0', standard '1'\n
	*	             STANDARD_0_HIGH_1 				- Standard '0', high drive'1'\n
	*							 HIGH_0_HIGH_1 						- High '0', high drive '1'\n
	*							 DISCONNECT_0_STANDARD_1 	- Disconnect '0', standard '1'\n
  *              DISCONNECT_0_HIGH_1 			- Disconnect '0', high drive '1'\n
  *              STANDARD_0_DISCONNECT_1 	- Standard '0', disconnect '1'\n
  *              HIGH_0_DISCONNECT_1 			- High drive '0', disconnect '1'\n							 
  */
void app_gpio_drv_configure_drive_configuration (uint8_t pin, uint8_t val, NRF_GPIO_Type *NRF_GPIO_MODULE)
{
	NRF_GPIO_MODULE->PIN_CNF[pin] |= (val << PIN_DRIVE_CONFIG_POS);
}

/**
  * @brief  Configures the sense for the pin 
  * @param  pin: pin number 
  * @param  val: DISABLE_SENSING - to disable sensing\n
	*							 HIGH_SENSE - to sense a high value	
	*							 LOW_SENSE - to sense a low value
  */
void app_gpio_drv_configure_pin_sensing (uint8_t pin, uint8_t val, NRF_GPIO_Type *NRF_GPIO_MODULE)
{
	NRF_GPIO_MODULE->PIN_CNF[pin] |= (val << PIN_SENSE_POS);
}

/**
  * @brief  Sets the output value of a pin to high 
  * @param  pin: pin number 
  * @param  val: SET_OUTPUT_HIGH to set the pin to high
  */
void app_gpio_drv_set_output_pin (uint8_t pin, NRF_GPIO_Type *NRF_GPIO_MODULE)
{
	NRF_GPIO_MODULE->OUT |= (1 << pin);
}

/**
  * @brief  Sets the output value of a pin to low 
  * @param  pin: pin number 
  * @param  val: SET_OUTPUT_LOW to set the pin to low
  */
void app_gpio_drv_clear_output_pin (uint8_t pin, NRF_GPIO_Type *NRF_GPIO_MODULE)
{
	NRF_GPIO_MODULE->OUT &= ~(1 << pin);
}
	
/**
  * @brief  Toggles the pin
  * @param  pin: pin number 
  */
void app_gpio_drv_pin_toggle (uint8_t pin, NRF_GPIO_Type *NRF_GPIO_MODULE)
{
	uint32_t val = 0;
	val = NRF_GPIO_MODULE->OUT;
	
	NRF_GPIO_MODULE->OUTSET = (~val & (1UL << pin));
	NRF_GPIO_MODULE->OUTCLR = (val & (1UL << pin));
}

/**
  * @brief  Configures a pin as output 
  * @param  pin: pin number 
  */
void app_gpio_drv_configure_pin_output (gpio_out_config_t *pin_config)
{
	app_gpio_drv_configure_pin_direction(pin_config->pin, CONFIGURE_PIN_OUTPUT, pin_config->NRF_GPIO_MODULE);
	app_gpio_drv_configure_input_buffer(pin_config->pin, pin_config->input, pin_config->NRF_GPIO_MODULE);
	app_gpio_drv_configure_pull_configuration(pin_config->pin, pin_config->pull, pin_config->NRF_GPIO_MODULE);
	app_gpio_drv_configure_drive_configuration(pin_config->pin, pin_config->drive, pin_config->NRF_GPIO_MODULE);
	app_gpio_drv_configure_pin_sensing(pin_config->pin, pin_config->sense, pin_config->NRF_GPIO_MODULE);
}

/**
  * @brief  Configures a pin as input 
  * @param  pin: pin number\n
						pullup: pullup or down the pin 
  */
void app_gpio_drv_configure_pin_input (gpio_in_config_t *pin_config)
{
	app_gpio_drv_configure_pin_direction(pin_config->pin, CONFIGURE_PIN_INPUT, pin_config->NRF_GPIO_MODULE);
	app_gpio_drv_configure_input_buffer(pin_config->pin, CONNECT_INPUT_BUFFER, pin_config->NRF_GPIO_MODULE);
	app_gpio_drv_configure_pull_configuration(pin_config->pin, pin_config->pull, pin_config->NRF_GPIO_MODULE);
	app_gpio_drv_configure_drive_configuration(pin_config->pin, pin_config->drive, pin_config->NRF_GPIO_MODULE);
	app_gpio_drv_configure_pin_sensing(pin_config->pin, pin_config->sense, pin_config->NRF_GPIO_MODULE);
}
