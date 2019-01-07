
/// @file BQ27421.c
/// This file contains the API for the TWIM peripheral. 
#include "twim.h"

static twim_config_t TWI_BATT;

/**
  * @brief  Initializes the TWIM peripheral
  */
void twim_init(void)
{
	TWI_BATT.twim_frequency = TWIM_FREQUENCY_100K;
	TWI_BATT.sclk = TWIM_SCLK;
	TWI_BATT.sda = TWIM_SDA;
	TWI_BATT.twim_module = NRF_TWIM1;
	TWI_BATT.gpio_module = NRF_P0;
	
	app_twim_hal_init(&TWI_BATT);
}

/**
  * @brief  Write the data to a device via TWIM 
  * @param  data    : pointer into which the data is read via TWIM
  * @param  address : address of the device from which the data read
  * @param  length  : length of the data
  */
void twim_write_data (uint8_t *data, uint8_t address, uint8_t length)
{
	app_twim_hal_write_data(TWI_BATT.twim_module, data, address, length);
}

/**
  * @brief  Read the data from a device via TWIM 
  * @param  data    : pointer pointing to the data from which the data is written via TWIM
  * @param  address : address of the device to which the data is written
  * @param  length  : length of the data
  */
void twim_read_data (uint8_t *data, uint8_t address, uint8_t length)
{
	app_twim_hal_read_data(TWI_BATT.twim_module, data, address, length);
}

/**
  * @brief  Read the data from a device via TWIM from a particular register
  * @param  address : address of the device to which the data is written
  * @param  length  : length of the data
  */
uint8_t twim_read_from_address (uint8_t device_address, uint8_t register_address, uint8_t length)
{
	twim_write_data(&register_address, device_address, length);
	
	uint8_t data_read = 0;
	twim_read_data(&data_read, device_address, length);
	
	return data_read;
}
