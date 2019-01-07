#include "app_pin_configuration.h"

gpio_out_config_t vtg_pin_1V8;
gpio_out_config_t vtg_pin_3V0;

gpio_out_config_t enable1_wireless_config;
gpio_out_config_t enable1_wireless_config1;

gpio_out_config_t ref_vol1;
gpio_out_config_t ref_vol2;

/**
  * @brief  Initializes the 1V8 voltage pin
  * @param  None
  * @retval None
  */
void init_1V8()
{
	vtg_pin_1V8.pin = VTG_1V8;
	vtg_pin_1V8.pull = NO_PULL;
	vtg_pin_1V8.drive = STANDARD_0_STANDARD_1;
	vtg_pin_1V8.sense = DISABLE_SENSING;
	vtg_pin_1V8.input = DISCONNECT_INPUT_BUFFER;
	vtg_pin_1V8.NRF_GPIO_MODULE = NRF_P0;
	
	app_gpio_hal_configure_pin_output(&vtg_pin_1V8);
}

/**
  * @brief  Turn on the 1V8 voltage pin
  * @param  None
  * @retval None
  */
void turnon_1V8()
{
	app_gpio_hal_set_output_pin(vtg_pin_1V8.pin, vtg_pin_1V8.NRF_GPIO_MODULE);
}

/**
  * @brief  Turn off the 1V8 voltage pin
  * @param  None
  * @retval None
  */
void turnoff_1V8()
{
	app_gpio_hal_clear_output_pin(vtg_pin_1V8.pin, vtg_pin_1V8.NRF_GPIO_MODULE);
}

/**
  * @brief  Initializes the 3V0 voltage pin
  * @param  None
  * @retval None
  */
void init_3V0()
{
	vtg_pin_3V0.pin = VTG_3V0;
	vtg_pin_3V0.pull = NO_PULL;
	vtg_pin_3V0.drive = STANDARD_0_STANDARD_1;
	vtg_pin_3V0.sense = DISABLE_SENSING;
	vtg_pin_3V0.input = DISCONNECT_INPUT_BUFFER;
	vtg_pin_3V0.NRF_GPIO_MODULE = NRF_P0;
	app_gpio_hal_configure_pin_output(&vtg_pin_3V0);
	 
}

/**
  * @brief  Turn on the 3V0 voltage pin
  * @param  None
  * @retval None
  */
void turnon_3V0()
{
	app_gpio_hal_set_output_pin(vtg_pin_3V0.pin, vtg_pin_3V0.NRF_GPIO_MODULE);
}

/**
  * @brief  Turn off the 3V0 voltage pin
  * @param  None
  * @retval None
  */
void turnoff_3V0()
{
	app_gpio_hal_clear_output_pin(vtg_pin_3V0.pin, vtg_pin_3V0.NRF_GPIO_MODULE);
}

/**
  * @brief  Initializes and turns on the voltage pins for the device
  * @param  None
  * @retval None
  */
void voltage_pins_init(void)
{
	  init_1V8();                  /* Initialize the 1V8 voltage pin */
	  turnon_1V8();                /* Turn on the 1V8 voltage pin*/
 
	  init_3V0();                  /* Initialize the 3V0 voltage pin */
	  turnon_3V0();                /* Turn on the 3V0 voltage pin*/
}

/**
  * @brief  Initializes the pins required for wireless charging
  * @param  None
  * @retval None
  */
void init_wireless_charging()
{
	enable1_wireless_config.pin = WIRELESS_CHARGING_1_PIN;
	enable1_wireless_config.pull = NO_PULL;
	enable1_wireless_config.drive = STANDARD_0_STANDARD_1;
	enable1_wireless_config.sense = DISABLE_SENSING;
	enable1_wireless_config.input = DISCONNECT_INPUT_BUFFER;
	enable1_wireless_config.NRF_GPIO_MODULE = NRF_P0;
	
	app_gpio_hal_configure_pin_output(&enable1_wireless_config);
	
	enable1_wireless_config1.pin = WIRELESS_CHARGING_2_PIN;
	enable1_wireless_config1.pull = NO_PULL;
	enable1_wireless_config1.drive = STANDARD_0_STANDARD_1;
	enable1_wireless_config1.sense = DISABLE_SENSING;
	enable1_wireless_config1.input = DISCONNECT_INPUT_BUFFER;
	enable1_wireless_config1.NRF_GPIO_MODULE = NRF_P0;
	app_gpio_hal_configure_pin_output(&enable1_wireless_config1);
}

/**
  * @brief  Turn on the Wireless charging functionality
  * @param  None
  * @retval None
  */
void turnon_wireless_charging()
{
	app_gpio_hal_clear_output_pin(enable1_wireless_config.pin, enable1_wireless_config.NRF_GPIO_MODULE);
	app_gpio_hal_clear_output_pin(enable1_wireless_config1.pin, enable1_wireless_config.NRF_GPIO_MODULE);
}

/**
  * @brief  Turn off the Wireless charging functionality
  * @param  None
  * @retval None
  */
void turnoff_wireless_charging()
{
	app_gpio_hal_set_output_pin(enable1_wireless_config.pin, enable1_wireless_config.NRF_GPIO_MODULE);
	app_gpio_hal_set_output_pin(enable1_wireless_config1.pin, enable1_wireless_config.NRF_GPIO_MODULE);
}

/**
  * @brief  Initializes and turns on the Wireless Charging functionality for the device
  * @param  None
  * @retval None
  */
void wireless_charging_init(void)
{
	init_wireless_charging();    /* Initialize the Wireless charging pins */
	turnon_wireless_charging();  /* Turnon Wireless charging */
}

/**
  * @brief  Initializes the pins that provide the reference voltages for ADS1292R
  * @param  None
  * @retval None
  */
void init_ref_vtg_ads1292r()
{
	ref_vol1.pin = REF_VTG_1_ADS1292R;
	ref_vol1.pull = NO_PULL;
	ref_vol1.drive = STANDARD_0_STANDARD_1;
	ref_vol1.sense = DISABLE_SENSING;
	ref_vol1.input = DISCONNECT_INPUT_BUFFER;
	ref_vol1.NRF_GPIO_MODULE = NRF_P0;
	app_gpio_hal_configure_pin_output(&ref_vol1);
	
	
	ref_vol2.pin = REF_VTG_2_ADS1292R;
	ref_vol2.pull = NO_PULL;
	ref_vol2.drive = STANDARD_0_STANDARD_1;
	ref_vol2.sense = DISABLE_SENSING;
	ref_vol2.input = DISCONNECT_INPUT_BUFFER;
	ref_vol2.NRF_GPIO_MODULE = NRF_P0;
	app_gpio_hal_configure_pin_output(&ref_vol2);
	
}

/**
  * @brief  Turn on the reference voltage for ADS1292R
  * @param  None
  * @retval None
  */
void turnon_ref_vtg_ads1292r()
{
	app_gpio_hal_set_output_pin(ref_vol1.pin, ref_vol1.NRF_GPIO_MODULE);
	app_gpio_hal_set_output_pin(ref_vol2.pin, ref_vol2.NRF_GPIO_MODULE);
}

/**
  * @brief  Turn off the reference voltage for ADS1292R
  * @param  None
  * @retval None
  */
void turnoff_ref_vtg_ads1292r()
{
	app_gpio_hal_clear_output_pin(ref_vol1.pin, ref_vol1.NRF_GPIO_MODULE);
	app_gpio_hal_clear_output_pin(ref_vol2.pin, ref_vol2.NRF_GPIO_MODULE);
}

/**
  * @brief  Initializes and turns on the reference voltage for the ADS1292R
  * @param  None
  * @retval None
  */
void ads1292r_ref_voltage_init()
{
	init_ref_vtg_ads1292r();     /* Initialize the reference voltage for ADS1292R*/   
	turnon_ref_vtg_ads1292r();   /* Turn on the the reference voltage for ADS1292R*/
}

/**
  * @brief  Changes the NFC-Pins to normal GPIO's
  * @param  None
  * @retval None
  */
void gpio_nfc_to_gpio_1(void)
{
  // Turn on NVMC
  NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen << NVMC_CONFIG_WEN_Pos;
  // Change NFC Pins to normal GPIOs
  NRF_UICR->NFCPINS = UICR_NFCPINS_PROTECT_Disabled << UICR_NFCPINS_PROTECT_Pos;
  // Turn off NVMC
  NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos;
}
