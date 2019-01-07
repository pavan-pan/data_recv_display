
/// @file app_hal_spi.h
/// This is a HAL for the NRF52 SPI peripheral .

#ifndef LP2_HAL_SPI_H
#define LP2_HAL_SPI_H

#include "nrf52.h"
#include "app_hal_gpio.h"

#define SPI_MODE_0	0
#define SPI_MODE_1	1
#define SPI_MODE_2	2
#define SPI_MODE_3  3

#define SPI_FREQUENCY_125K	0
#define SPI_FREQUENCY_250K	1
#define SPI_FREQUENCY_500K	2
#define SPI_FREQUENCY_1M		3
#define SPI_FREQUENCY_2M		4
#define SPI_FREQUENCY_4M		5
#define SPI_FREQUENCY_8M		6

#define SPI_BIT_ORDER_MSB_FIRST	0
#define SPI_BIT_ORDER_LSB_FIRST 1

//INTENSET register
#define SPI_INTERRUPT_STOPPED_POS  1U
#define SPI_INTERRUPT_STOPPED_ENABLE  (1 << SPI_INTERRUPT_STOPPED_POS)
#define SPI_INTERRUPT_STOPPED_DISABLE  (0 << SPI_INTERRUPT_STOPPED_POS)

#define SPI_INTERRUPT_ENDRX_POS  4U
#define SPI_INTERRUPT_ENDRX_ENABLE  (1 << SPI_INTERRUPT_ENDRX_POS)
#define SPI_INTERRUPT_ENDRX_DISABLE  (0 << SPI_INTERRUPT_ENDRX_POS)

#define SPI_INTERRUPT_END_POS  6U
#define SPI_INTERRUPT_END_ENABLE  (1 << SPI_INTERRUPT_END_POS)
#define SPI_INTERRUPT_END_DISABLE  (0 << SPI_INTERRUPT_END_POS)

#define SPI_INTERRUPT_ENDTX_POS  8U
#define SPI_INTERRUPT_ENDTX_ENABLE  (1 << SPI_INTERRUPT_ENDTX_POS)
#define SPI_INTERRUPT_ENDTX_DISABLE  (0 << SPI_INTERRUPT_ENDTX_POS)

#define SPI_INTERRUPT_STARTED_POS  19U
#define SPI_INTERRUPT_STARTED_ENABLE  (1 << SPI_INTERRUPT_STARTED_POS)
#define SPI_INTERRUPT_STARTED_DISABLE  (0 << SPI_INTERRUPT_STARTED_POS)

/**@brief SPI Master configuration. */
typedef struct
{
	uint32_t miso;
	uint32_t mosi;
	uint32_t sclk;
	uint32_t cs;
	uint8_t spi_mode;
	uint8_t spi_frequency;
	uint8_t spi_bit_order;
	//uint32_t interrupt_enable_byte;
	//uint32_t interrupt_disable_byte;
	NRF_SPIM_Type *spi_module;
	NRF_GPIO_Type *NRF_GPIO_MODULE;
}spi_master_config_t;


/**
  * @brief  HAL function to configure SPI 
  * @param  spi_module: The SPI module which needs to be configured 
  */
void app_spi_hal_configure_spi(spi_master_config_t *spi_module);

/**
  * @brief  HAL function to configure the Master In Slave Out (MISO) pin 
  * @param  pin_miso: The pin which needs to be configured as MISO
  * @param  NRF_SPI_MODULE: SPI module whose miso needs to be configured
  */
void app_spi_hal_configure_miso(uint32_t pin_miso, NRF_SPIM_Type *NRF_SPI_MODULE);

/**
  * @brief  HAL function to configure the Master Out Slave In (MOSI) pin 
  * @param  pin_mosi: The pin which needs to be configured as MOSI
  * @param  NRF_SPI_MODULE: SPI module whose mosi needs to be configured
  */
void app_spi_hal_configure_mosi(uint32_t pin_mosi, NRF_SPIM_Type *NRF_SPI_MODULE);

/**
  * @brief  HAL function to configure the clock (SCLK) pin 
  * @param  pin_sclk: The pin which needs to be configured as SCLK
  * @param  NRF_SPI_MODULE: SPI module whose SCLK needs to be configured
  */
void app_spi_hal_configure_sclk(uint32_t pin_sclk, NRF_SPIM_Type *NRF_SPI_MODULE);

/**
  * @brief  HAL function to configure the clock select (cs) pin 
  * @param  pin_cs: The pin which needs to be configured as cs
  * @param  NRF_SPI_MODULE: SPI module whose cs needs to be configured
  */
void app_spi_hal_configure_cs(uint32_t pin_cs, NRF_SPIM_Type *NRF_SPI_MODULE);

/**
  * @brief  HAL function to configure the SPI mode 
  * @param  spi_mode: SPI_MODE to which the SPI module is set to
  * @param  NRF_SPI_MODULE: SPI module 
  */
void app_spi_hal_configure_spi_mode(uint8_t spi_mode, NRF_SPIM_Type *NRF_SPI_MODULE);

/**
  * @brief  HAL function to configure the bit order 
  * @param  bit_order: bit order to which the SPI module is set to
  * @param  NRF_SPI_MODULE: SPI module 
  */
void app_spi_hal_configure_spi_bit_order(uint8_t bit_order, NRF_SPIM_Type *NRF_SPI_MODULE);
/**
  * @brief  HAL function to enable the SPI
  * @param  spi_module: SPI module which has to be enabled
  */
void app_spi_hal_enable_spi_module(NRF_SPIM_Type *spi_module);

/**
  * @brief  HAL function to configure the frequency of the SPI module
  * @param  spi_frequency: frequency to which the SPI is set to
  * @param  NRF_SPI_MODULE: SPI module 
  */
void app_spi_hal_configure_spi_frequency(uint8_t spi_frequency, NRF_SPIM_Type *NRF_SPI_MODULE);

/**
  * @brief  HAL function to send data to a peripheral via SPI
  * @param  data: pointer to the data which has to be sent
  * @param  len: length of the data which has to be sent 
  */
void app_spi_hal_write_spi (uint8_t *data, uint8_t len, NRF_SPIM_Type *NRF_SPI_MODULE);

/**
  * @brief  HAL function to read data from a peripheral via SPI
  * @param  data: pointer to the data which has to be sent
  * @param  len: length of the data which has to be sent 
  */
void app_spi_hal_read_spi (uint8_t *data, uint8_t len, NRF_SPIM_Type *NRF_SPI_MODULE);

void app_spi_hal_enable_spi_interrupt(NRF_SPIM_Type *NRF_SPI_MODULE, uint32_t interrupt);
#endif
