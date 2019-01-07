#include "spi.h"

/**
  * @brief  Initialize the SPI module used to communicate with ADS1292R device
  */
void spi_init_ads1292r(spi_master_config_t *spi_ads1292r)
{
	spi_ads1292r->miso = SPI_MISO;
	spi_ads1292r->mosi = SPI_MOSI;
	spi_ads1292r->sclk = SPI_SCLK;
	spi_ads1292r->cs = SPI_CS;
	spi_ads1292r->spi_mode =  SPI_MODE_1;
	spi_ads1292r->spi_bit_order = SPI_BIT_ORDER_MSB_FIRST;
	spi_ads1292r->spi_module = NRF_SPIM0;
	spi_ads1292r->spi_frequency = SPI_FREQUENCY_1M;
	//spi_ads1292r->interrupt_enable_byte = SPI_INTERRUPT_ENDRX_ENABLE;
	
	app_spi_hal_configure_spi(spi_ads1292r);
}

/**
  * @brief  Enable the ADS1292R device
  */
void spi_enable_ads1292r(spi_master_config_t *spi_ads1292r)
{
	app_gpio_hal_clear_output_pin(spi_ads1292r->cs, spi_ads1292r->NRF_GPIO_MODULE);
}

/**
  * @brief  Disable the ADS1292R device
  */
void spi_disable_ads1292r(spi_master_config_t *spi_ads1292r)
{
	app_gpio_hal_set_output_pin(spi_ads1292r->cs, spi_ads1292r->NRF_GPIO_MODULE);
}

/**
  * @brief  Write data to the ADS1292R device via SPI
  */
void spi_write_byte(uint8_t *data, uint8_t length)
{
	app_spi_hal_write_spi (data, length, NRF_SPIM0);
  
}

/**
  * @brief  Read data from the ADS1292R device via SPI
  */
void spi_read_byte(uint8_t * data , uint8_t length)
{ 
	app_spi_hal_read_spi (data, length, NRF_SPIM0);
}
