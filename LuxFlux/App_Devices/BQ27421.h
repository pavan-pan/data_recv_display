
/// @file BQ27421.c
/// This file contains the source code for the BQ27421 device. BQ27421 fuel gauge provides system-side fuel 
/// gauging for single cell Li-ion batteries.

#ifndef BQ27421_H
#define BQ27421_H

#include "twim.h"
#include "app_hal_twi.h"
#include "BQ25120.h"

// BQ27421 I2C Address
#define BQ27421_I2C_ADDRESS                     0x55

// BQ27421 Register Address
#define BQ27421_VOLTAGE                         0x04
#define BQ27421_CURRENT                         0x10
#define BQ27421_REMAINING_CAPACITY              0x0C
#define BQ27421_STATE_OF_CHARGE                 0x1C
#define BQ27421_STATE_OF_HEALTH                 0x20
#define BQ27421_DESIGN_CAPACITY                 0x3C
#define BQ27421_FULL_CAPACITY                   0x0A

/**
  * @brief  Read various information from BQ27421 
	* @param  command: command to read various device information
  */
uint16_t BQ27421_read (uint8_t command);

/**
  * @brief  Set Battery factory capacity
	* @param  design_capacity: the value to which the design capacity is to be set
  */
void BQ27421_set_design_capacity(uint16_t design_capacity);

#endif
