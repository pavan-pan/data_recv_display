
/// @file BQ27421.c
/// This file contains the source code for the BQ27421 device. BQ27421 fuel gauge provides system-side fuel 
/// gauging for single cell Li-ion batteries.

#include "BQ27421.h"

/**
  * @brief  Read various information from BQ27421 
	* @param  command: command to read various device information
  */
uint16_t BQ27421_read (uint8_t command)
{
	//Send the address of the device with which the TWIM wants to communicate and command to request information
	twim_write_data(&command, BQ27421_I2C_ADDRESS, 1);
	
	uint8_t data_read[2] = {0};
	
	//Start reading the data from the device
	twim_read_data(data_read, BQ27421_I2C_ADDRESS, 2);
	
	return data_read[1]<<8 | data_read[0];
}

/**
  * @brief  Set Battery factory capacity
	* @param  design_capacity: the value to which the design capacity is to be set
  */
void BQ27421_set_design_capacity(uint16_t design_capacity)
{
  volatile uint16_t OLD_Csum;
  volatile uint8_t OLD_DesCap_MSB;
  volatile uint8_t OLD_DesCap_LSB;
  volatile uint16_t temp;
  volatile uint8_t tempFuelGauge;
  volatile uint16_t NEW_Csum;
  volatile uint8_t NEW_DesCap_MSB;
  volatile uint8_t NEW_DesCap_LSB;
	
	uint8_t data[2] ={0};
  
  // 1) If the device has been previously SEALED, UNSEAL it by sending the
  // appropriate keys to Control() (0x00 and 0x01). Write the first 2 bytes
  // of the UNSEAL key using the Control(0x8000) command. Without writing any
  // other bytes to the device, write the second (identical) 2 bytes of the
  // UNSEAL key using the Control(0x8000) command.
	data[0] = 0x00;
	data[1] = 0x00;
	twim_write_data(data, BQ27421_I2C_ADDRESS, 2);
	
	data[0] = 0x01;
	data[1] = 0x80;
	twim_write_data(data, BQ27421_I2C_ADDRESS, 2);
	
	data[0] = 0x00;
	data[1] = 0x00;
	twim_write_data(data, BQ27421_I2C_ADDRESS, 2);
	
	data[0] = 0x01;
	data[1] = 0x80;
	twim_write_data(data, BQ27421_I2C_ADDRESS, 2);
	
  // 2) Send SET_CFGUPDATE subcommand, Control(0x0013)
	data[0] = 0x00;
	data[1] = 0x13;
	twim_write_data(data, BQ27421_I2C_ADDRESS, 2);
	
	data[0] = 0x01;
	data[1] = 0x00;
	twim_write_data(data, BQ27421_I2C_ADDRESS, 2);
  
  // 3) Confirm CFGUPDATE mode by polling Flags() register until bit 4 is set. May take up to 1 second.
	while(!(twim_read_from_address(0x55, 0x06, 1) & 0x10));
  tempFuelGauge = twim_read_from_address(0x55, 0x06, 1);
  
  // 4) Write 0x00 using BlockDataControl() command (0x61) to enable block data memory control.
	data[0] = 0x61;
	data[1] = 0x00;
	twim_write_data(data, BQ27421_I2C_ADDRESS, 2);
  
  // 5) Write 0x52 using the DataBlockClass() command (0x3E) to access the State
  // subclass (82 decimal, 0x52 hex) containing the Design Capacity parameter.
	data[0] = 0x3E;
	data[1] = 0x52;
	twim_write_data(data, BQ27421_I2C_ADDRESS, 2);
  
  // 6) Write the block offset location using DataBlock() command (0x3F).
	data[0] = 0x3F;
	data[1] = 0x00;
	twim_write_data(data, BQ27421_I2C_ADDRESS, 2);
  
  // 7) Read the 1-byte checksum using the BlockDataChecksum() command (0x60).
  OLD_Csum = twim_read_from_address(0x55, 0x60, 1);
  
  // 8) Read both Design Capacity bytes starting at 0x4A (offset = 10). Block
  // data starts at 0x40, so to read the data of a specific offset, use address
  // 0x40 + mod(offset, 32). Expect 0x03 0xE8 for -G1B for a 1000-mAh default value.
  OLD_DesCap_MSB = twim_read_from_address(0x55, 0x4A, 1);
  OLD_DesCap_LSB = twim_read_from_address(0x55, 0x4B, 1);

  // 9) Write both Design Capacity bytes starting at 0x4A (offset = 10).
  NEW_DesCap_MSB = (design_capacity >> 8) & 0xFF;
	data[0] = 0x4A;
	data[1] = NEW_DesCap_MSB;
	twim_write_data(data, BQ27421_I2C_ADDRESS, 2);
	
	
  NEW_DesCap_LSB = design_capacity & 0xFF;
 
	data[0] = 0x4B;
	data[1] = NEW_DesCap_LSB;
	twim_write_data(data, BQ27421_I2C_ADDRESS, 2);
  
  // 10) Compute the new block checksum. The checksum is (255 – x) where x is
  // the 8-bit summation of the BlockData() (0x40 to 0x5F) on a byte-by-byte basis.
  // A quick way to calculate the new checksum uses a data replacement method
  // with the old and new data summation bytes.
  temp = (255 - OLD_Csum - OLD_DesCap_MSB - OLD_DesCap_LSB) % 256;
  NEW_Csum = 255 - ((temp + NEW_DesCap_MSB + NEW_DesCap_LSB) % 256);
  
  // 11) Write new checksum. The data is actually transferred to the Data
  // Memory when the correct checksum for the whole block (0x40 to 0x5F) is
  // written to BlockDataChecksum() (0x60).
	data[0] = 0x60;
	data[1] = NEW_Csum;
	twim_write_data(data, BQ27421_I2C_ADDRESS, 2);
  
  // 12) Exit CFGUPDATE mode by sending SOFT_RESET subcommand, Control(0x0042)
	data[0] = 0x00;
	data[1] = 0x42;
	twim_write_data(data, BQ27421_I2C_ADDRESS, 2);
	
	data[0] = 0x01;
	data[1] = 0x00;
	twim_write_data(data, BQ27421_I2C_ADDRESS, 2);
  
  // 13) Confirm CFGUPDATE has been exited by polling Flags() register until bit
  // 4 is cleared. May take up to 1 second.
  while(twim_read_from_address(0x55, 0x06, 1) & 0x10);
  
  // 14) If the device was previously SEALED, return to SEALED mode by sending
  // the Control(0x0020) subcommand.
	data[0] = 0x00;
	data[1] = 0x20;
	twim_write_data(data, BQ27421_I2C_ADDRESS, 2);
	
	data[0] = 0x01;
	data[1] = 0x00;
	twim_write_data(data, BQ27421_I2C_ADDRESS, 2);
}
