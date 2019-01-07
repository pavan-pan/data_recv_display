
/// @file led.c
/// This file contains the functions to access the LED's present on the LP2.
/// Detailed file description.
#include "led.h"

/* GPIO configuration for different LED's*/
gpio_out_config_t red_led;
gpio_out_config_t green_led;
gpio_out_config_t blue_led;

/**
  * @brief  Function to Initialize LED's
  * @param  None
  * @retval None
  */
void led_init()
{
		red_led.pin = RED_LED;
		red_led.pull = NO_PULL;
		red_led.drive = STANDARD_0_STANDARD_1;
		red_led.sense = DISABLE_SENSING;
		red_led.input = DISCONNECT_INPUT_BUFFER;
	  red_led.NRF_GPIO_MODULE = NRF_P0;
		app_gpio_hal_configure_pin_output(&red_led);
	
		green_led.pin = GREEN_LED;
		green_led.pull = NO_PULL;
		green_led.drive = STANDARD_0_STANDARD_1;
		green_led.sense = DISABLE_SENSING;
		green_led.input = DISCONNECT_INPUT_BUFFER;
	  green_led.NRF_GPIO_MODULE = NRF_P0;
		app_gpio_hal_configure_pin_output(&green_led);
		//gpio_set_output_pin (green_led.pin, 1);
		
		blue_led.pin = BLUE_LED;
		blue_led.pull = NO_PULL;
		blue_led.drive = STANDARD_0_STANDARD_1;
		blue_led.sense = DISABLE_SENSING;
		blue_led.input = DISCONNECT_INPUT_BUFFER;
		blue_led.NRF_GPIO_MODULE = NRF_P0;
		app_gpio_hal_configure_pin_output(&blue_led);
}

/**
  * @brief  Function to turn on Red LED
  * @param  None
  * @retval None
  */
void led_red_on()
{
	app_gpio_hal_clear_output_pin(red_led.pin, red_led.NRF_GPIO_MODULE);
}

/**
  * @brief  Function to turn on Green LED
  * @param  None
  * @retval None
  */
void led_green_on()
{
	app_gpio_hal_clear_output_pin(green_led.pin, green_led.NRF_GPIO_MODULE);
}

/**
  * @brief  Function to turn on Blue LED
  * @param  None
  * @retval None
  */
void led_blue_on()
{
	app_gpio_hal_clear_output_pin(blue_led.pin, blue_led.NRF_GPIO_MODULE);
}

/**
  * @brief  Function to turn off Red LED
  * @param  None
  * @retval None
  */
void led_red_off()
{
	app_gpio_hal_set_output_pin(red_led.pin, red_led.NRF_GPIO_MODULE);
}

/**
  * @brief  Function to turn off Green LED
  * @param  None
  * @retval None
  */
void led_green_off()
{
	app_gpio_hal_set_output_pin(green_led.pin, green_led.NRF_GPIO_MODULE);
}

/**
  * @brief  Function to turn off Blue LED
  * @param  None
  * @retval None
  */
void led_blue_off()
{
	app_gpio_hal_set_output_pin(blue_led.pin, blue_led.NRF_GPIO_MODULE);
}

/**
  * @brief  Function to toggle Red LED
  * @param  None
  * @retval None
  */
void led_red_toggle()
{
	app_gpio_hal_pin_toggle(red_led.pin, red_led.NRF_GPIO_MODULE);
}

/**
  * @brief  Function to toggle Green LED
  * @param  None
  * @retval None
  */
void led_green_toggle()
{
	app_gpio_hal_pin_toggle(green_led.pin, green_led.NRF_GPIO_MODULE);
}

/**
  * @brief  Function to toggle Blue LED
  * @param  None
  * @retval None
  */
void led_blue_toggle()
{
	app_gpio_hal_pin_toggle(blue_led.pin, blue_led.NRF_GPIO_MODULE);
}
