
/// @file app_drv_gpio.h
/// This file contains the headers of the source code for the GPIO peripheral.
/// Detailed file description.

#ifndef NRF_DRV_GPIO_H
#define NRF_DRV_GPIO_H

#include <stdint.h>
#include "nrf52.h"

/*Pin Direction*/
#define PIN_DIR_POS									0UL
#define CONFIGURE_PIN_INPUT					0UL        //Configure pin as an input pin
#define CONFIGURE_PIN_OUTPUT				1UL				 //Configure pin as an output pin

/*Connect or Disconnect Input Buffer*/
#define PIN_INPUT_BUFFER_POS			  1UL
#define CONNECT_INPUT_BUFFER				0UL 			 //Connect Input buffer
#define DISCONNECT_INPUT_BUFFER			1UL 			 //Disconnect Input buffer	

/*Pull Configuration*/
#define PIN_PULL_CONFIG_POS					2UL
#define NO_PULL											0UL 			 //No Pull	
#define CONFIGURE_PULLDOWN					1UL 			 //Pull down on pin	
#define CONFIGURE_PULLUP						3UL 			 //Pull up on pin

/*Drive Configuration*/
#define PIN_DRIVE_CONFIG_POS				8UL
#define	STANDARD_0_STANDARD_1				0UL 			 //S0S1 - Standard '0', standard '1'
#define HIGH_0_STANDARD_1						1UL 			 //H0S1 - High drive '0', standard '1'
#define STANDARD_0_HIGH_1						2UL 			 //S0H1 - Standard '0', high drive'1'
#define HIGH_0_HIGH_1								3UL 			 //H0H1 - High '0', high drive '1'
#define DISCONNECT_0_STANDARD_1			4UL 			 //D0S1 - Disconnect '0', standard '1'
#define DISCONNECT_0_HIGH_1					5UL 			 //D0H1 - Disconnect '0', high drive '1'
#define STANDARD_0_DISCONNECT_1			6UL 			 //S0D1 - Standard '0', disconnect '1'
#define HIGH_0_DISCONNECT_1					7UL 			 //H0D1 - High drive '0', disconnect '1'

/*Pin sensing mechanism*/
#define PIN_SENSE_POS								16UL
#define DISABLE_SENSING							0UL 			 //Disable Sensing
#define HIGH_SENSE									2UL 			 //Sense for high level
#define LOW_SENSE										3UL  			 //Sense for low level

/*Set output pin high or low*/
#define SET_OUTPUT_HIGH							1UL
#define SET_OUTPUT_LOW							1UL

/* Bits 1..0 : Program memory access mode. It is strongly recommended to only activate erase and write modes when they are actively used. Enabling write or erase will invalidate the cache and keep it invalidated. */
#define NVMC_CONFIG_WEN_Pos (0UL) /*!< Position of WEN field. */
#define NVMC_CONFIG_WEN_Msk (0x3UL << NVMC_CONFIG_WEN_Pos) /*!< Bit mask of WEN field. */
#define NVMC_CONFIG_WEN_Ren (0UL) /*!< Read only access */
#define NVMC_CONFIG_WEN_Wen (1UL) /*!< Write Enabled */
#define NVMC_CONFIG_WEN_Een (2UL) /*!< Erase enabled */

/* Bit 0 : Setting of pins dedicated to NFC functionality */
#define UICR_NFCPINS_PROTECT_Pos (0UL) /*!< Position of PROTECT field. */
#define UICR_NFCPINS_PROTECT_Msk (0x1UL << UICR_NFCPINS_PROTECT_Pos) /*!< Bit mask of PROTECT field. */
#define UICR_NFCPINS_PROTECT_Disabled (0UL) /*!< Operation as GPIO pins. Same protection as normal GPIO pins */
#define UICR_NFCPINS_PROTECT_NFC (1UL) /*!< Operation as NFC antenna pins. Configures the protection for NFC operation */

/**@brief Input pin configuration. */
typedef struct
{
	uint32_t pin;
	uint8_t pull;
	uint8_t drive;
	uint8_t sense;
	NRF_GPIO_Type *NRF_GPIO_MODULE;
}gpio_in_config_t;

/**@brief Output pin configuration. */
typedef struct
{
	uint32_t pin;
	uint8_t input;
	uint8_t pull;
	uint8_t drive;
	uint8_t sense;
	NRF_GPIO_Type *NRF_GPIO_MODULE;
}gpio_out_config_t;

/**
  * @brief  Configures pin direction  
  * @param  pin: pin number 
  * @param  val: set to '0' for input\n
	*							 set to '1' for output
  */
void app_gpio_drv_configure_pin_direction(uint8_t pin, uint8_t val, NRF_GPIO_Type *NRF_GPIO_MODULE);

/**
  * @brief  Configures the input buffer for the pin  
  * @param  pin: pin number 
  * @param  val: set to CONNECT_INPUT_BUFFER to connect to the input buffer\n
	*							 set to DISCONNECT_INPUT_BUFFER to disconnect from the input buffer
  */
void app_gpio_drv_configure_input_buffer (uint8_t pin, uint8_t val, NRF_GPIO_Type *NRF_GPIO_MODULE);

/**
  * @brief  Configures the pull configuration for the pin 
  * @param  pin: pin number 
  * @param  val: set to CONNECT_INPUT_BUFFER to connect to the input buffer\n
	*							 set to DISCONNECT_INPUT_BUFFER to disconnect from the input buffer
  */
void app_gpio_drv_configure_pull_configuration (uint8_t pin, uint8_t val, NRF_GPIO_Type *NRF_GPIO_MODULE);

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
void app_gpio_drv_configure_drive_configuration (uint8_t pin, uint8_t val, NRF_GPIO_Type *NRF_GPIO_MODULE);

/**
  * @brief  Configures the sense for the pin 
  * @param  pin: pin number 
  * @param  val: DISABLE_SENSING - to disable sensing\n
	*							 HIGH_SENSE - to sense a high value	
	*							 LOW_SENSE - to sense a low value
  */
void app_gpio_drv_configure_pin_sensing (uint8_t pin, uint8_t val, NRF_GPIO_Type *NRF_GPIO_MODULE);

/**
  * @brief  Sets the output value of a pin to high 
  * @param  pin: pin number 
  * @param  val: SET_OUTPUT_HIGH to set the pin to high
  */
void app_gpio_drv_set_output_pin (uint8_t pin, NRF_GPIO_Type *NRF_GPIO_MODULE);

/**
  * @brief  Sets the output value of a pin to low 
  * @param  pin: pin number 
  * @param  val: SET_OUTPUT_LOW to set the pin to low
  */
void app_gpio_drv_clear_output_pin (uint8_t pin, NRF_GPIO_Type *NRF_GPIO_MODULE);
	
/**
  * @brief  Toggles the pin
  * @param  pin: pin number 
  */
void app_gpio_drv_pin_toggle (uint8_t pin, NRF_GPIO_Type *NRF_GPIO_MODULE);

/**
  * @brief  Configures a pin as output 
  * @param  pin: pin number 
  */
void app_gpio_drv_configure_pin_output (gpio_out_config_t *pin_config);

/**
  * @brief  Configures a pin as input 
  * @param  pin: pin number\n
						pullup: pullup or down the pin 
  */
void app_gpio_drv_configure_pin_input (gpio_in_config_t *pin_config);

#endif
