
/// @file BQ25120..c
/// This file contains the source code for the BQ25120 device. BQ25120 is a Battery charge management IC.

#include "BQ25120.h"

/*BQ25120_config is private to this file and is not accessible outside the file.*/
static BQ25120_config_t BQ25120_config;

/**
  * @brief  Write data to BQ25120 device
	* @param  data: pointer to the data to be written to the BQ25120 device
	* @param  length: length of the data to be written
  */
void BQ25120_write_data (uint8_t *data, uint8_t length)
{
	twim_write_data (data, BQ25120_I2C_ADDRESS, length);
}

/**
  * @brief  Read data from BQ25120 device
	* @param  data: pointer to the variable to which data is read from BQ25120 device
	* @param  length: length of the data to be read
  */
void BQ25120_read_data (uint8_t *data, uint8_t length)
{
	twim_read_data (data, BQ25120_I2C_ADDRESS, length);
}

/**
  * @brief  Get the value of Battery Monitor register
  */
uint8_t BQ25120_read_battery_monitor_register(void)
{
  // Request Update of Battery Status
	uint16_t data_send = 0;
	uint8_t data_address = 0;
	uint8_t data_read = 0;
	
	data_send = (WRITE_READ_BATTERY_MONITOR_REGISTER << 8) | BQ25120_BATTERY_MONITOR_REGISTER_ADDRESS;
	BQ25120_write_data ((uint8_t *)&data_send, 2);
  for(int i = 0; i < 5000; i++)
  {
  }
  
  //Write Address, then read battery value  
	data_address = BQ25120_BATTERY_MONITOR_REGISTER_ADDRESS;
	BQ25120_write_data (&data_address, 1);

  for(int i = 0; i < 5000; i++)
  {
  }
  
	BQ25120_read_data ((uint8_t *)&data_read, 1);
  return data_read;
}

/**
  * @brief  Enable TWIM and Disable charging
  */
void enable_i2c_disable_charging()
{
	app_gpio_hal_set_output_pin(BQ25120_config.batt_pin_config.pin, BQ25120_config.batt_pin_config.NRF_GPIO_MODULE);
}

/**
  * @brief  Disable TWIM and Enable charging
  */
void disable_i2c_enable_charging()
{
	app_gpio_hal_clear_output_pin(BQ25120_config.batt_pin_config.pin, BQ25120_config.batt_pin_config.NRF_GPIO_MODULE);
}

/**
  * @brief  Initialize the BQ25120 device
  */
void BQ25120_init()
{
  //Set up the configuration of the battery config pin
	BQ25120_config.batt_pin_config.pin = BQ25120_BATT_CONFIG_PIN;
	BQ25120_config.batt_pin_config.pull = NO_PULL;
	BQ25120_config.batt_pin_config.drive = STANDARD_0_STANDARD_1;
	BQ25120_config.batt_pin_config.sense = DISABLE_SENSING;
	BQ25120_config.batt_pin_config.input = DISCONNECT_INPUT_BUFFER;
	BQ25120_config.batt_pin_config.NRF_GPIO_MODULE = NRF_P0;
	
	//Configure the battery config pin as output
	app_gpio_hal_configure_pin_output(&BQ25120_config.batt_pin_config);
	
	// Enable I2C, Disable Charging
	enable_i2c_disable_charging();

  for (int i = 0; i<500; i++)
  {
  }

	uint16_t data_write = 0;
	
	//Write Reset value to the Battery Voltage control register
	data_write = (WRITE_BATTERY_VOLTAGE_CONTROL_REGISTER << 8) | BQ25120_BATTERY_VOLTAGE_CONTROL_REGISTER;
  BQ25120_write_data ((uint8_t *)&data_write, 2);
	
  for (int i = 0; i<1000; i++)
  {
  }
	
	//Write Reset value to the sys vout control register
	data_write = (WRITE_SYS_VOUT_CONTROL_REGISTER << 8) | BQ25120_SYS_VOUT_CONTROL_REGISTER_ADDRESS;
	BQ25120_write_data ((uint8_t *)&data_write, 2);

  for (int i = 0; i<1000; i++)
  {
  }

	//Write Reset value to the fast charge control register
	data_write = (WRITE_FAST_CHARGE_CONTROL_REGISTER << 8) | BQ25120_FAST_CHARGE_CONTROL_REGISTER_ADDRESS;
	BQ25120_write_data ((uint8_t *)&data_write, 2);
  
  for (int i = 0; i<1000; i++)
  {
  }

	//Write Reset value to the ilim and battery uvlo control register
	data_write = (WRITE_ILIM_BATTERY_UVLO_CONTROL_REGISTER << 8) | BQ25120_ILIM_AND_BATTERY_UVLO_CONTROL_REGISTER_ADDRESS;
	BQ25120_write_data ((uint8_t *)&data_write, 2);
  
  for (int i = 0; i<1000; i++)
  {
  }

	//Write Reset value to the load switch and ldo control register
	data_write = (WRITE_LOAD_SWITCH_AND_LDO_CONTROL_REGISTER << 8) | BQ25120_LOAD_SWTCH_AND_LDO_CONTROL_REGISTER;
	BQ25120_write_data ((uint8_t *)&data_write, 2);
  
  for(int i = 0; i<1000; i++)
  {
  }

	//Write Reset value to the termination pre charge register
	data_write = (WRITE_TERMINATION_PRE_CHARGE_REGISTER << 8) | BQ25120_TERMINATION_PRE_CHARGE_REGISTER;
	BQ25120_write_data ((uint8_t *)&data_write, 2);
	
  for (int i = 0; i<1000; i++)
  {
  }

	//Write Reset value to the status and ship mode control register
	data_write = (WRITE_STATUS_SHIP_MODE_CONTROL_REGISTER << 8) | BQ25120_STATUS_AND_SHIP_MODE_CONTROL_REGISTER;
	BQ25120_write_data ((uint8_t *)&data_write, 2);
	
  for (int i = 0; i<1000; i++)
  {
  }
  
	//Write Reset value to the push button control register
	data_write = (WRITE_PUSH_BUTTON_CONTROL_REGISTER << 8) | BQ25120_PUSH_BUTTON_CONTROL_REGISTER;
	BQ25120_write_data ((uint8_t *)&data_write, 2);
	
	for (int i = 0; i<1000; i++)
  {
  }
	
	//Write Reset value to the TS control register
	data_write = (WRITE_TS_CONTROL_REGISTER << 8) | BQ25120_TS_CONTROL_REGISTER;
	BQ25120_write_data ((uint8_t *)&data_write, 2);
	
	for (int i = 0; i<1000; i++)
  {
  }
  
	//Read battery monitor register
	BQ25120_read_battery_monitor_register();
	
  // Enable Charging, Disable I2C
	disable_i2c_enable_charging();
}

