#ifndef PIN_CONFIGURATION_H
#define PIN_CONFIGURATION_H

#include "app_hal_gpio.h"

#define VTG_1V8    31
#define VTG_3V0    30

#define WIRELESS_CHARGING_1_PIN  10
#define WIRELESS_CHARGING_2_PIN  9

#define REF_VTG_1_ADS1292R  14 
#define REF_VTG_2_ADS1292R  11

/**
  * @brief  Initializes the 1V8 voltage pin
  * @param  None
  * @retval None
  */
void init_1V8(void);

/**
  * @brief  Turn on the 1V8 voltage pin
  * @param  None
  * @retval None
  */
void turnon_1V8(void);

/**
  * @brief  Turn off the 1V8 voltage pin
  * @param  None
  * @retval None
  */
void turnoff_1V8(void);

/**
  * @brief  Initializes the 3V0 voltage pin
  * @param  None
  * @retval None
  */
void init_3V0(void);

/**
  * @brief  Turn on the 3V0 voltage pin
  * @param  None
  * @retval None
  */
void turnon_3V0(void);

/**
  * @brief  Turn off the 3V0 voltage pin
  * @param  None
  * @retval None
  */
void turnoff_3V0(void);

/**
  * @brief  Initializes and turns on the voltage pins for the device
  * @param  None
  * @retval None
  */
void voltage_pins_init(void);

/**
  * @brief  Initializes the pins required for wireless charging
  * @param  None
  * @retval None
  */
void init_wireless_charging(void);

/**
  * @brief  Turn on the Wireless charging functionality
  * @param  None
  * @retval None
  */
void turnon_wireless_charging(void);

/**
  * @brief  Turn off the Wireless charging functionality
  * @param  None
  * @retval None
  */
void turnoff_wireless_charging(void);

/**
  * @brief  Initializes and turns on the Wireless Charging functionality for the device
  * @param  None
  * @retval None
  */
void wireless_charging_init(void);

/**
  * @brief  Initializes the pins that provide the reference voltages for ADS1292R
  * @param  None
  * @retval None
  */
void init_ref_vtg_ads1292r(void);

/**
  * @brief  Turn on the reference voltage for ADS1292R
  * @param  None
  * @retval None
  */
void turnon_ref_vtg_ads1292r(void);

/**
  * @brief  Turn off the reference voltage for ADS1292R
  * @param  None
  * @retval None
  */
void turnoff_ref_vtg_ads1292r(void);

/**
  * @brief  Initializes and turns on the reference voltage for the ADS1292R
  * @param  None
  * @retval None
  */
void ads1292r_ref_voltage_init(void);

/**
  * @brief  Changes the NFC-Pins to normal GPIO's
  * @param  None
  * @retval None
  */
void gpio_nfc_to_gpio_1(void);
#endif
