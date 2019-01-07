#ifndef SPI_H
#define SPI_H

#include "nrf52.h"
#include "app_hal_spi.h"

#define SPI_MISO   19
#define SPI_MOSI   18
#define SPI_SCLK   17
#define SPI_CS     16

/**
  * @brief  Initialize the SPI module used to communicate with ADS1292R device
  */
void spi_init_ads1292r(spi_master_config_t *spi_ads1292r);

/**
  * @brief  Enable the ADS1292R device
  */
void spi_enable_ads1292r(spi_master_config_t *spi_ads1292r);

/**
  * @brief  Disable the ADS1292R device
  */
void spi_disable_ads1292r(spi_master_config_t *spi_ads1292r);

/**
  * @brief  Write data to the ADS1292R device via SPI
  */
void spi_write_byte(uint8_t *data, uint8_t length);

/**
  * @brief  Read data from the ADS1292R device via SPI
  */
void spi_read_byte(uint8_t * data , uint8_t length);

#endif
