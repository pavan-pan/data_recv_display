
/// @file app_hal_spi.c
/// This is a HAL for the NRF52 SPI peripheral .

#include "app_hal_spi.h"
#include "app_drv_spi.h"

/**
  * @brief  HAL function to configure SPI 
  * @param  spi_module: The SPI module which needs to be configured 
  */
void app_spi_hal_configure_spi(spi_master_config_t *spi_module)
{
	app_spi_hal_configure_miso(spi_module->miso, spi_module->spi_module);
	app_spi_hal_configure_mosi(spi_module->mosi, spi_module->spi_module);
	app_spi_hal_configure_sclk(spi_module->sclk, spi_module->spi_module);
	app_spi_hal_configure_cs(spi_module->cs, spi_module->spi_module);
	
	app_spi_hal_configure_spi_mode(spi_module->spi_mode, spi_module->spi_module);
	app_spi_hal_configure_spi_bit_order(spi_module->spi_bit_order, spi_module->spi_module);
	app_spi_hal_configure_spi_frequency(spi_module->spi_frequency, spi_module->spi_module);
	app_spi_hal_enable_spi_module(spi_module->spi_module);
	
	//app_spi_hal_enable_spi_interrupt(spi_module->spi_module, interrupt);
	
}

/**
  * @brief  HAL function to configure the Master In Slave Out (MISO) pin 
  * @param  pin_miso: The pin which needs to be configured as MISO
  * @param  NRF_SPI_MODULE: SPI module whose miso needs to be configured
  */
void app_spi_hal_configure_miso(uint32_t pin_miso, NRF_SPIM_Type *NRF_SPI_MODULE)
{
	gpio_in_config_t miso;
	
	miso.pin = pin_miso;
	miso.pull = CONFIGURE_PULLUP;
	miso.drive = STANDARD_0_STANDARD_1;
	miso.sense = DISABLE_SENSING;
	miso.NRF_GPIO_MODULE = NRF_P0;
	
	app_gpio_hal_configure_pin_input(&miso);
	app_spi_drv_configure_miso (&miso.pin, NRF_SPI_MODULE);
}

/**
  * @brief  HAL function to configure the Master Out Slave In (MOSI) pin 
  * @param  pin_mosi: The pin which needs to be configured as MOSI
  * @param  NRF_SPI_MODULE: SPI module whose mosi needs to be configured
  */
void app_spi_hal_configure_mosi(uint32_t pin_mosi, NRF_SPIM_Type *NRF_SPI_MODULE)
{
	gpio_out_config_t mosi;
	
	mosi.pin = pin_mosi;
	mosi.input = DISCONNECT_INPUT_BUFFER;
	mosi.pull = NO_PULL;
	mosi.drive = STANDARD_0_STANDARD_1;
	mosi.sense = DISABLE_SENSING;
	mosi.NRF_GPIO_MODULE = NRF_P0;
	
	app_gpio_hal_configure_pin_output(&mosi);
	app_spi_drv_configure_mosi (&mosi.pin, NRF_SPI_MODULE);
}

/**
  * @brief  HAL function to configure the clock (SCLK) pin 
  * @param  pin_sclk: The pin which needs to be configured as SCLK
  * @param  NRF_SPI_MODULE: SPI module whose SCLK needs to be configured
  */
void app_spi_hal_configure_sclk(uint32_t pin_sclk, NRF_SPIM_Type *NRF_SPI_MODULE)
{
	gpio_out_config_t sclk;
	
	sclk.pin = pin_sclk;
	sclk.input = DISCONNECT_INPUT_BUFFER;
	sclk.pull = NO_PULL;
	sclk.drive = STANDARD_0_STANDARD_1;
	sclk.sense = DISABLE_SENSING;
	sclk.NRF_GPIO_MODULE = NRF_P0;
	
	app_gpio_hal_configure_pin_output(&sclk);
	app_spi_drv_configure_sclk (&sclk.pin, NRF_SPI_MODULE);
}

/**
  * @brief  HAL function to configure the clock select (cs) pin 
  * @param  pin_cs: The pin which needs to be configured as cs
  * @param  NRF_SPI_MODULE: SPI module whose cs needs to be configured
  */
void app_spi_hal_configure_cs(uint32_t pin_cs, NRF_SPIM_Type *NRF_SPI_MODULE)
{
	gpio_out_config_t cs;
	
	cs.pin = pin_cs;
	cs.input = DISCONNECT_INPUT_BUFFER;
	cs.pull = NO_PULL;
	cs.drive = STANDARD_0_STANDARD_1;
	cs.sense = DISABLE_SENSING;
	cs.NRF_GPIO_MODULE = NRF_P0;
	
	app_gpio_hal_configure_pin_output(&cs);
}

/**
  * @brief  HAL function to configure the SPI mode 
  * @param  spi_mode: SPI_MODE to which the SPI module is set to
  * @param  NRF_SPI_MODULE: SPI module 
  */
void app_spi_hal_configure_spi_mode(uint8_t spi_mode, NRF_SPIM_Type *NRF_SPI_MODULE)
{
	app_spi_drv_configure_spi_mode(spi_mode, NRF_SPI_MODULE);
}

/**
  * @brief  HAL function to configure the bit order 
  * @param  bit_order: bit order to which the SPI module is set to
  * @param  NRF_SPI_MODULE: SPI module 
  */
void app_spi_hal_configure_spi_bit_order(uint8_t bit_order, NRF_SPIM_Type *NRF_SPI_MODULE)
{
	app_spi_drv_configure_spi_bit_order(bit_order, NRF_SPI_MODULE);
}

/**
  * @brief  HAL function to enable the SPI
  * @param  spi_module: SPI module which has to be enabled
  */
void app_spi_hal_enable_spi_module(NRF_SPIM_Type *spi_module)
{
	app_spi_drv_enable_spi_module(spi_module);
}

/**
  * @brief  HAL function to configure the frequency of the SPI module
  * @param  spi_frequency: frequency to which the SPI is set to
  * @param  NRF_SPI_MODULE: SPI module 
  */
void app_spi_hal_configure_spi_frequency(uint8_t spi_frequency, NRF_SPIM_Type *NRF_SPI_MODULE)
{
	app_spi_drv_configure_spi_frequency(spi_frequency, NRF_SPI_MODULE);
}

/**
  * @brief  HAL function to send data to a peripheral via SPI
  * @param  data: pointer to the data which has to be sent
  * @param  len: length of the data which has to be sent 
  */
void app_spi_hal_write_spi (uint8_t *data, uint8_t len, NRF_SPIM_Type *NRF_SPI_MODULE)
{
	app_spi_drv_write_spi(data, len, NRF_SPI_MODULE);
}

/**
  * @brief  HAL function to read data from a peripheral via SPI
  * @param  data: pointer to the data which has to be sent
  * @param  len: length of the data which has to be sent 
  */
void app_spi_hal_read_spi (uint8_t *data, uint8_t len, NRF_SPIM_Type *NRF_SPI_MODULE)
{
	app_spi_drv_read_spi(data, len, NRF_SPI_MODULE);
}

//void app_spi_hal_enable_spi_interrupt(NRF_SPIM_Type *NRF_SPI_MODULE, uint32_t interrupt)
//{
//	app_spi_drv_enable_spi_interrupt (NRF_SPI_MODULE, interrupt);
//}