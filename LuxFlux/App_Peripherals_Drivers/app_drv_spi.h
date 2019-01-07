
/// @file app_hal_spi.h
/// This is a driver for the NRF52 SPI peripheral.

#ifndef DRV_SPI_H
#define DRV_SPI_H

#include "nrf52.h"
#include "app_hal_spi.h"

#define SPI_ENABLE			7

/**
  * @brief  Configures the SPI mode 
  * @param  spi_mode : SPI mode \n
	*					A SPI module can be configured into 4 different SPI modes based on CPHA and CPOL \n
	*					********************************************\n
	*					* Mode *      CPOL         *     CPHA      *\n
	*					********************************************\n
	*					*		0	 *  0 (Active High)  *  0 (Leading)  *\n
	*					*		1	 *  0 (Active High)  *  1 (Trailing) *\n
	*					*		2	 *  1 (Active Low)   *  0 (Leading)  *\n
	*					*		3	 *  1 (Active Low)   *  1 (Trailing) *\n
	*					********************************************\n
  * @param  NRF_SPI_MODULE: Module for which the SPI mode is configured
  * @retval None
  */
void app_spi_drv_configure_spi_mode(uint8_t spi_mode, NRF_SPIM_Type *NRF_SPI_MODULE);

/**
  * @brief  Configures the bit order for the SPI module 
  * @param  bit_order : Bit order \n
	*					*********************************************************\n
	*					* Bit Order *      Description                          *\n
	*					*********************************************************\n
	*					*		  0	    *   Most Significant bit shifted out first  *\n
	*					*		  1	    *   Least Significant bit shifted out first *\n
	*					*********************************************************\n
  * @param  NRF_SPI_MODULE: Module for which the bit order is configured
  * @retval None
  */
void app_spi_drv_configure_spi_bit_order(uint8_t bit_order, NRF_SPIM_Type *NRF_SPI_MODULE);

/**
  * @brief  Enable the SPI module 
  * @param  NRF_SPI_MODULE: Module which needs to be enabled
  * @retval None
  */
void app_spi_drv_enable_spi_module(NRF_SPIM_Type *NRF_SPI_MODULE);

/**
  * @brief  Configure the SPI speed
  * @param  spi_frequency: speed at which the SPI communication is to take place\n
  *         SPI_FREQUENCY_125K : 125kbps \n
	*         SPI_FREQUENCY_250K : 250kbps \n
	*         SPI_FREQUENCY_500K : 500kbps \n
	*         SPI_FREQUENCY_1M 	 : 1Mbps   \n
	*         SPI_FREQUENCY_2M   : 2Mbps   \n
	*         SPI_FREQUENCY_4M   : 4Mbps   \n
	*         SPI_FREQUENCY_8M   : 8Mbps   \n
	* @param  NRF_SPI_MODULE: Module which needs to be enabled
  * @retval None
  */
void app_spi_drv_configure_spi_frequency(uint8_t spi_frequency, NRF_SPIM_Type *NRF_SPI_MODULE);

/**
  * @brief  Select the MISO pin for the SPI communication
  * @param  miso: MISO pin \n
	* @param  NRF_SPI_MODULE: Module which needs to be enabled
  * @retval None
  */
void app_spi_drv_configure_miso (uint32_t *miso, NRF_SPIM_Type * NRF_SPI_MODULE);

/**
  * @brief  Select the MOSI pin for the SPI communication
  * @param  mosi: MOSI pin \n
	* @param  NRF_SPI_MODULE: Module which needs to be enabled
  * @retval None
  */
void app_spi_drv_configure_mosi (uint32_t *mosi, NRF_SPIM_Type * NRF_SPI_MODULE);

/**
  * @brief  Select the clock pin for the SPI communication
  * @param  sclk: SCLK pin \n
	* @param  NRF_SPI_MODULE: Module which needs to be enabled
  * @retval None
  */
void app_spi_drv_configure_sclk (uint32_t *sclk, NRF_SPIM_Type * NRF_SPI_MODULE);

void app_spi_drv_write_spi(uint8_t *data, uint8_t len, NRF_SPIM_Type * NRF_SPI_MODULE);

void app_spi_drv_read_spi(uint8_t *data, uint8_t length, NRF_SPIM_Type * NRF_SPI_MODULE);

#endif
