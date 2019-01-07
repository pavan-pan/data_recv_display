#ifndef STARTUP_H
#define STARTUP_H

#include "app_hal_gpio.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_drv_clock.h"
#include "app_hal_spi.h"
#include "app_queues.h"
#include "app_helper.h"
#include "BQ25120.h"
#include "nrf_log.h"
#include "led.h"
#include "spi.h"
#include "ads1292r.h"
#include "task.h"
#include "app_pin_configuration.h"


/**
  * @brief  Function to Initialize all the modules
  * @param  None
  * @retval None
  */
void init_modules(void);

#endif
