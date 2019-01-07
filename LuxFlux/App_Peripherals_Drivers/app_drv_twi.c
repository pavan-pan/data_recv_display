
/// @file app_drv_twi.c
/// This file contains the source code for the TWIM peripheral.
/// Detailed file description.

#include "app_drv_twi.h"

/**
  * @brief  Configures the SDA pin for the TWIM peripheral 
  * @param  sda : The pin which is configured as SDA
	* @param  TWIM_MODULE : pointer to the TWIM module
	* @param  GPIO_MODULE : pointer to the GPIO module
  */
void app_twim_drv_set_sda (uint32_t sda, NRF_TWIM_Type *TWIM_MODULE, NRF_GPIO_Type *GPIO_MODULE)
{
	TWIM_MODULE->PSEL.SDA = sda;
	GPIO_MODULE->PIN_CNF[sda] |= ( (DISABLE_SENSING << PIN_SENSE_POS) \
                              | (STANDARD_0_DISCONNECT_1     << PIN_DRIVE_CONFIG_POS) \
                              | (CONFIGURE_PULLUP    << PIN_PULL_CONFIG_POS)  \
                              | (CONNECT_INPUT_BUFFER  << PIN_INPUT_BUFFER_POS) \
                              | (CONFIGURE_PIN_INPUT      << PIN_DIR_POS));
}

/**
  * @brief  Configures the SCLK pin for the TWIM peripheral 
  * @param  sclk : The pin which is configured as SCLK
	* @param  TWIM_MODULE : pointer to the TWIM module
	* @param  GPIO_MODULE : pointer to the GPIO module
  */
void app_twim_drv_set_sclk (uint32_t sclk, NRF_TWIM_Type *TWIM_MODULE, NRF_GPIO_Type *GPIO_MODULE)
{
	TWIM_MODULE->PSEL.SCL = sclk;
	
	GPIO_MODULE->PIN_CNF[sclk] |= ( (DISABLE_SENSING << PIN_SENSE_POS) \
                              | (STANDARD_0_DISCONNECT_1     << PIN_DRIVE_CONFIG_POS) \
                              | (CONFIGURE_PULLUP    << PIN_PULL_CONFIG_POS)  \
                              | (CONNECT_INPUT_BUFFER  << PIN_INPUT_BUFFER_POS) \
                              | (CONFIGURE_PIN_INPUT      << PIN_DIR_POS));
}

/**
  * @brief  Sets the frequency with which the TWIM module communicates
  * @param  twim_frequency : frequency
	* @param  TWIM_MODULE : pointer to the TWIM module
  */
void app_twim_drv_set_frequency (uint32_t twim_frequency, NRF_TWIM_Type *TWIM_MODULE)
{
	TWIM_MODULE->FREQUENCY = twim_frequency;
}

/**
  * @brief  Enables the TWIM module
	* @param  TWIM_MODULE : pointer to the TWIM module
  */
void app_twim_drv_enable_module (NRF_TWIM_Type *TWIM_MODULE)
{
	TWIM_MODULE->ENABLE = 6;
}

/**
  * @brief  Writes the data to a device via TWIM peripheral
  * @param  data    : pointer to the data 
	* @param  address : address of the device
  * @param  len     : length of the data to be written
  */
void app_twim_drv_write_data (NRF_TWIM_Type *TWIM_MODULE, uint8_t *data, uint8_t address, uint8_t  len)
{
	uint32_t errsrc = 0;
	
	TWIM_MODULE->TXD.PTR = (uint32_t) data;
	TWIM_MODULE->TXD.MAXCNT = len;
	TWIM_MODULE->ADDRESS = address;
	
	TWIM_MODULE->EVENTS_LASTTX = 0;
	TWIM_MODULE->TASKS_STARTTX = 1;
  
	TWIM_MODULE->SHORTS = (1 << 9);
	
	for (int i=0; i<10000; i++)
	{
	}
}

/**
  * @brief  Reads the data from a device via TWIM peripheral
  * @param  data    : pointer to the location where is data is read into 
	* @param  address : address of the device
  * @param  len     : length of the data to be read
  */
void app_twim_drv_read_data (NRF_TWIM_Type *TWIM_MODULE, uint8_t *data, uint8_t address, uint8_t  len)
{
	uint8_t p_rx_buffer[2] = {0};
	uint16_t value = 0;
  
  TWIM_MODULE->RXD.PTR = (uint32_t)p_rx_buffer;
  TWIM_MODULE->RXD.MAXCNT = len;
  TWIM_MODULE->ADDRESS = address << 0;
  
	TWIM_MODULE->EVENTS_LASTRX = 0;
  TWIM_MODULE->TASKS_STARTRX = 1;
  
	TWIM_MODULE->SHORTS = (1 << 12);

	for (int i=0; i<10000; i++)
	{
	}

	data[0] = p_rx_buffer[0];
	data[1] = p_rx_buffer[1];
}
