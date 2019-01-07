#ifndef BQ25120_H
#define BQ25120_H

//#include "gpio.h"
#include "app_drv_gpio.h"
#include "twim.h"
#include "app_hal_gpio.h"
#include "app_hal_twi.h"
// BQ25120 I2C Address
#define BQ25120_I2C_ADDRESS                                     0x6A
#define BQ25120_BATT_CONFIG_PIN                                 0x04

typedef struct
{
	gpio_out_config_t batt_pin_config;
} BQ25120_config_t;

// BQ25120 Register Address
#define BQ25120_STATUS_AND_SHIP_MODE_CONTROL_REGISTER           0x00
#define BQ25120_TS_CONTROL_REGISTER										          0x02
#define BQ25120_SYS_VOUT_CONTROL_REGISTER_ADDRESS               0x06
#define BQ25120_BATTERY_MONITOR_REGISTER_ADDRESS                0x0A
#define BQ25120_FAST_CHARGE_CONTROL_REGISTER_ADDRESS            0x03
#define BQ25120_ILIM_AND_BATTERY_UVLO_CONTROL_REGISTER_ADDRESS  0x09
#define BQ25120_BATTERY_VOLTAGE_CONTROL_REGISTER                0x05
#define BQ25120_TERMINATION_PRE_CHARGE_REGISTER                 0x04
#define BQ25120_LOAD_SWTCH_AND_LDO_CONTROL_REGISTER             0x07
#define BQ25120_PUSH_BUTTON_CONTROL_REGISTER										0x08

//Commands
#define WRITE_SYS_VOUT_CONTROL_REGISTER                         0xAA
#define WRITE_LOAD_SWITCH_AND_LDO_CONTROL_REGISTER              0xD8
#define WRITE_FAST_CHARGE_CONTROL_REGISTER                      0x84
#define WRITE_ILIM_BATTERY_UVLO_CONTROL_REGISTER                0x30
#define WRITE_BATTERY_VOLTAGE_CONTROL_REGISTER                  0x78
#define WRITE_TERMINATION_PRE_CHARGE_REGISTER                   0xE2
#define WRITE_STATUS_SHIP_MODE_CONTROL_REGISTER                 0x00
#define WRITE_PUSH_BUTTON_CONTROL_REGISTER                      0xE0
#define WRITE_TS_CONTROL_REGISTER                               0x88
#define WRITE_READ_BATTERY_MONITOR_REGISTER                     0x80

// Functions
/*BQ25120_config is private to this file and is not accessible outside the file.*/
static BQ25120_config_t BQ25120_config;

/**
  * @brief  Write data to BQ25120 device
	* @param  data: pointer to the data to be written to the BQ25120 device
	* @param  length: length of the data to be written
  */
void BQ25120_write_data (uint8_t *data, uint8_t length);

/**
  * @brief  Read data from BQ25120 device
	* @param  data: pointer to the variable to which data is read from BQ25120 device
	* @param  length: length of the data to be read
  */
void BQ25120_read_data (uint8_t *data, uint8_t length);

/**
  * @brief  Get the value of Battery Monitor register
  */
uint8_t BQ25120_read_battery_monitor_register(void);

/**
  * @brief  Enable TWIM and Disable charging
  */
void enable_i2c_disable_charging(void);

/**
  * @brief  Disable TWIM and Enable charging
  */
void disable_i2c_enable_charging(void);

/**
  * @brief  Initialize the BQ25120 device
  */
void BQ25120_init(void);


#endif
