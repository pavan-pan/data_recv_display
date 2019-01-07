
/// @file app_hal_spi.c
/// This is a driver for the NRF52 SPI peripheral .

#include "app_drv_spi.h"

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
void app_spi_drv_configure_spi_mode(uint8_t spi_mode, NRF_SPIM_Type *NRF_SPI_MODULE)
{
	if (spi_mode == 0)
	{
		NRF_SPI_MODULE->CONFIG &= ~(1 << 1);
		NRF_SPI_MODULE->CONFIG &= ~(1 << 2);
	}
	else if (spi_mode == 1)
	{
		NRF_SPI_MODULE->CONFIG |= (1 << 1);
		NRF_SPI_MODULE->CONFIG &= ~(1 << 2);
	}
	else if (spi_mode == 2)
	{
		NRF_SPI_MODULE->CONFIG &= ~(1 << 1);
		NRF_SPI_MODULE->CONFIG |= (1 << 2);
	}
	else if (spi_mode == 3)
	{
		NRF_SPI_MODULE->CONFIG |= (1 << 1);
		NRF_SPI_MODULE->CONFIG |= (1 << 2);
	}
	else
	{
		//error
	}
}

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
void app_spi_drv_configure_spi_bit_order(uint8_t bit_order, NRF_SPIM_Type *NRF_SPI_MODULE)
{
	if (bit_order == 0)
	{
		NRF_SPI_MODULE->CONFIG &= ~(1 << 0);
	}
	else if (bit_order == 1)
	{
		NRF_SPI_MODULE->CONFIG |= (1 << 0);
	}
	else
	{
		//error
	}
		
}

/**
  * @brief  Enable the SPI module 
  * @param  NRF_SPI_MODULE: Module which needs to be enabled
  * @retval None
  */
void app_spi_drv_enable_spi_module(NRF_SPIM_Type *NRF_SPI_MODULE)
{
	NRF_SPI_MODULE->ENABLE = SPI_ENABLE << 0;
}

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
void app_spi_drv_configure_spi_frequency(uint8_t spi_frequency, NRF_SPIM_Type *NRF_SPI_MODULE)
{
	
	if (spi_frequency == SPI_FREQUENCY_125K)
	{
		NRF_SPI_MODULE->FREQUENCY = 0x02000000;
	}
	else if (spi_frequency == SPI_FREQUENCY_250K)
	{
		NRF_SPI_MODULE->FREQUENCY = 0x04000000;
	}
	else if (spi_frequency == SPI_FREQUENCY_500K)
	{
		NRF_SPI_MODULE->FREQUENCY = 0x08000000;
	}
	else if (spi_frequency == SPI_FREQUENCY_1M)
	{
		NRF_SPI_MODULE->FREQUENCY = 0x10000000;
	}
	else if (spi_frequency == SPI_FREQUENCY_2M)
	{
		NRF_SPI_MODULE->FREQUENCY = 0x20000000;
	}
	else if (spi_frequency == SPI_FREQUENCY_4M)
	{
		NRF_SPI_MODULE->FREQUENCY = 0x40000000;
	}
	else if (spi_frequency == SPI_FREQUENCY_8M)
	{
		NRF_SPI_MODULE->FREQUENCY = 0x80000000;
	}
}

/**
  * @brief  Select the MISO pin for the SPI communication
  * @param  miso: MISO pin \n
	* @param  NRF_SPI_MODULE: Module which needs to be enabled
  * @retval None
  */
void app_spi_drv_configure_miso (uint32_t *miso, NRF_SPIM_Type * NRF_SPI_MODULE)
{
	NRF_SPI_MODULE->PSEL.MISO = *miso;
}

/**
  * @brief  Select the MOSI pin for the SPI communication
  * @param  mosi: MOSI pin \n
	* @param  NRF_SPI_MODULE: Module which needs to be enabled
  * @retval None
  */
void app_spi_drv_configure_mosi (uint32_t *mosi, NRF_SPIM_Type * NRF_SPI_MODULE)
{
	NRF_SPI_MODULE->PSEL.MOSI = *mosi;
}

/**
  * @brief  Select the clock pin for the SPI communication
  * @param  sclk: SCLK pin \n
	* @param  NRF_SPI_MODULE: Module which needs to be enabled
  * @retval None
  */
void app_spi_drv_configure_sclk (uint32_t *sclk, NRF_SPIM_Type * NRF_SPI_MODULE)
{
	NRF_SPI_MODULE->PSEL.SCK = *sclk;
}

void app_spi_drv_write_spi(uint8_t *data, uint8_t len, NRF_SPIM_Type * NRF_SPI_MODULE)
{
	uint8_t p_rx_buffer[len];

  NRF_SPI_MODULE->TXD.PTR = (uint32_t)data;
  NRF_SPI_MODULE->RXD.PTR = (uint32_t)p_rx_buffer;
  NRF_SPI_MODULE->TXD.MAXCNT = len; //buffer_length;
  NRF_SPI_MODULE->RXD.MAXCNT = 0x0; //buffer_length;
	
  NRF_SPI_MODULE->EVENTS_ENDTX = 0;
	NRF_SPI_MODULE->EVENTS_STOPPED = 0;
	
  NRF_SPI_MODULE->TASKS_START = 1;

	while (!NRF_SPI_MODULE->EVENTS_ENDTX);
}

void app_spi_drv_read_spi(uint8_t *data, uint8_t length, NRF_SPIM_Type * NRF_SPI_MODULE)
{
	uint8_t p_tx_buffer[length];
	
  NRF_SPI_MODULE->RXD.PTR = (uint32_t)data;
  NRF_SPI_MODULE->TXD.PTR = (uint32_t)p_tx_buffer;
  NRF_SPI_MODULE->RXD.MAXCNT = length; //buffer_length;
	NRF_SPI_MODULE->TXD.MAXCNT = 0;
  
	NRF_SPI_MODULE->EVENTS_ENDRX = 0;
	NRF_SPI_MODULE->EVENTS_STOPPED = 0;
	
  NRF_SPI_MODULE->TASKS_START = 1;
	while (!NRF_SPI_MODULE->EVENTS_ENDRX);
}

//void app_spi_drv_enable_spi_interrupt(NRF_SPIM_Type *NRF_SPI_MODULE, uint32_t interrupt)
//{
//	NRF_SPI_MODULE->INTENSET |= interrupt;
//}