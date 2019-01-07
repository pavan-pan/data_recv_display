
/// @file app_drv_twi.h
/// This file contains the headers of the source code for the TWIM peripheral.
/// Detailed file description.

#ifndef DRV_TWI_H
#define DRV_TWI_H

#include "app_hal_twi.h"
#include "app_drv_gpio.h"

/**
  * @brief  Configures the SDA pin for the TWIM peripheral 
  * @param  sda : The pin which is configured as SDA
	* @param  TWIM_MODULE : pointer to the TWIM module
	* @param  GPIO_MODULE : pointer to the GPIO module
  */
void app_twim_drv_set_sda (uint32_t sda, NRF_TWIM_Type *TWIM_MODULE, NRF_GPIO_Type *GPIO_MODULE);

/**
  * @brief  Configures the SCLK pin for the TWIM peripheral 
  * @param  sclk : The pin which is configured as SCLK
	* @param  TWIM_MODULE : pointer to the TWIM module
	* @param  GPIO_MODULE : pointer to the GPIO module
  */
void app_twim_drv_set_sclk (uint32_t sclk, NRF_TWIM_Type *TWIM_MODULE, NRF_GPIO_Type *GPIO_MODULE);

/**
  * @brief  Sets the frequency with which the TWIM module communicates
  * @param  twim_frequency : frequency
	* @param  TWIM_MODULE : pointer to the TWIM module
  */
void app_twim_drv_set_frequency (uint32_t twim_frequency, NRF_TWIM_Type *TWIM_MODULE);

/**
  * @brief  Enables the TWIM module
	* @param  TWIM_MODULE : pointer to the TWIM module
  */
void app_twim_drv_enable_module (NRF_TWIM_Type *TWIM_MODULE);

/**
  * @brief  Writes the data to a device via TWIM peripheral
  * @param  data    : pointer to the data 
	* @param  address : address of the device
  * @param  len     : length of the data to be written
  */
void app_twim_drv_write_data (NRF_TWIM_Type *TWIM_MODULE, uint8_t *data, uint8_t address, uint8_t  len);

/**
  * @brief  Reads the data from a device via TWIM peripheral
  * @param  data    : pointer to the location where is data is read into 
	* @param  address : address of the device
  * @param  len     : length of the data to be read
  */
void app_twim_drv_read_data (NRF_TWIM_Type *TWIM_MODULE, uint8_t *data, uint8_t address, uint8_t  len);

#endif
