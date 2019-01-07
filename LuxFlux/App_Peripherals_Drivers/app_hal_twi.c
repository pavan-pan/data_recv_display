#include "app_hal_twi.h"


void app_twim_hal_init(twim_config_t *TWIM_MODULE)
{
	app_twim_hal_set_sda(TWIM_MODULE->sda, TWIM_MODULE->twim_module, TWIM_MODULE->gpio_module);
	app_twim_hal_set_sclk(TWIM_MODULE->sclk, TWIM_MODULE->twim_module, TWIM_MODULE->gpio_module);
	app_twim_hal_set_frequency(TWIM_MODULE->twim_frequency, TWIM_MODULE->twim_module);
	app_twim_hal_enable_module(TWIM_MODULE->twim_module);
}

void app_twim_hal_set_sda (uint32_t sda, NRF_TWIM_Type *TWIM_MODULE, NRF_GPIO_Type *GPIO_MODULE)
{
	app_twim_drv_set_sda (sda, TWIM_MODULE, GPIO_MODULE);
}

void app_twim_hal_set_sclk (uint32_t sclk, NRF_TWIM_Type *TWIM_MODULE, NRF_GPIO_Type *GPIO_MODULE)
{
	app_twim_drv_set_sclk (sclk, TWIM_MODULE, GPIO_MODULE);
}

void app_twim_hal_set_frequency (uint32_t twim_frequency, NRF_TWIM_Type *TWIM_MODULE)
{
	app_twim_drv_set_frequency (twim_frequency, TWIM_MODULE);
}

void app_twim_hal_enable_module(NRF_TWIM_Type *TWIM_MODULE)
{
	app_twim_drv_enable_module(TWIM_MODULE);
}

/**
  * @brief  HAL layer to check for an event.
	* @param  NRF_UARTE : UART module.
  * @param  event : Events mentioned in nrf_uarte_event_t.
  * @retval None
  */	
bool app_twim_hal_check_event(NRF_TWIM_Type * NRF_TWIM, app_twim_event_t event)
{
    return (bool)*(volatile uint32_t *)((uint8_t *)NRF_TWIM + (uint32_t)event);
}

/**
  * @brief  HAL layer to clear an event.
	* @param  NRF_UARTE : UART module.
  * @param  event : Clear the events mentioned in nrf_uarte_event_t.
  * @retval None
  */	
void app_twim_hal_clear_event (NRF_TWIM_Type * NRF_TWIM, app_twim_event_t event)
{
	*((volatile uint32_t *)((uint8_t *)NRF_TWIM + (uint32_t)event)) = 0x0UL;
}

void app_twim_hal_write_data (NRF_TWIM_Type *TWIM_MODULE, uint8_t *data, uint8_t address, uint8_t len)
{
	app_twim_drv_write_data(TWIM_MODULE, data, address, len);
}

void app_twim_hal_read_data (NRF_TWIM_Type *TWIM_MODULE, uint8_t *data, uint8_t address, uint8_t len)
{
	app_twim_drv_read_data(TWIM_MODULE, data, address, len);
}

