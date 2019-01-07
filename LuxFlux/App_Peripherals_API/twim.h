#ifndef TWIM_H
#define TWIM_H

#include "nrf52.h"
#include "app_hal_twi.h"
#include "BQ25120.h"

#define TWIM_SDA     8
#define TWIM_SCLK    12

/**
  * @brief  Initializes the TWIM peripheral
  */
void twim_init(void);

/**
  * @brief  Write the data to a device via TWIM 
  * @param  data    : pointer into which the data is read via TWIM
  * @param  address : address of the device from which the data read
  * @param  length  : length of the data
  */
void twim_write_data (uint8_t *data, uint8_t address, uint8_t length);

/**
  * @brief  Read the data from a device via TWIM 
  * @param  data    : pointer pointing to the data from which the data is written via TWIM
  * @param  address : address of the device to which the data is written
  * @param  length  : length of the data
  */
void twim_read_data (uint8_t *data, uint8_t address, uint8_t length);

/**
  * @brief  Read the data from a device via TWIM from a particular register
  * @param  address : address of the device to which the data is written
  * @param  length  : length of the data
  */
uint8_t twim_read_from_address (uint8_t device_address, uint8_t register_address, uint8_t length);

#endif
