
#include "app_startup.h"
#include "app_hal_gpiote.h"

typedef uint32_t ret_code_t;

/**@brief Function for initializing the nrf log module.
 */
static void log_init(void)
{
    ret_code_t err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);
//	  err_code = NRF_ERROR_INTERNAL;
//	  if (err_code != NRF_SUCCESS)
//		{
//			check_error_code (LP2_INIT, LP2_INIT_LOG_ERROR);
//		}

    //NRF_LOG_DEFAULT_BACKENDS_INIT();
}

#if NRF_LOG_ENABLED
/**@brief Thread for handling the logger.
 *
 * @details This thread is responsible for processing log entries if logs are deferred.
 *          Thread flushes all log entries and suspends. It is resumed by idle task hook.
 *
 * @param[in]   arg   Pointer used for passing some arbitrary information (context) from the
 *                    osThreadCreate() call to the thread.
 */
static void logger_thread(void * arg)
{
    UNUSED_PARAMETER(arg);

    while (1)
    {
        NRF_LOG_FLUSH();

        vTaskSuspend(NULL); // Suspend myself
    }
}
#endif //NRF_LOG_ENABLED

/**@brief Function for initializing the clock. The softdevice initiates the clock module 
  * so no need to initialize seperately
  */
static void clock_init(void)
{
	  //The softdevice initiates the clock module so no need to initialize seperately
	
    //ret_code_t err_code = nrf_drv_clock_init();
    //APP_ERROR_CHECK(err_code);
	
	  //NRF_CLOCK->LFCLKSRC =
    //    (uint32_t)((1 << CLOCK_LFCLKSRC_SRC_Pos) & CLOCK_LFCLKSRC_SRC_Msk);
	
}

gpio_in_config_t turn_on_off_app_config;
gpiote_config_t turn_on_off_gpiote_lp2;

/**
  * @brief  Function to Initialize all the modules
  */
void init_modules(void)
{
    uint8_t ads1292r_id = 0;
	
    // Monitor Debugging: Debug while holding Bluetooth Connection
    NVIC_SetPriority(DebugMonitor_IRQn, 7ul);
	
    // Initialize modules.
    log_init();                  /* Initialize the log module */
    clock_init();                /* Initialize the clocks */
	  gpio_nfc_to_gpio_1();        /*Change NFC-Pins to normal GPIOs*/
    bluetooth_init(); /* Initialize the Bluetooth */
    

    voltage_pins_init();         /*Initialize and turn on voltage pins */

    wireless_charging_init();    /* Initialize the wireless charging for the device */
    
	  led_init();                  /* Initializes the Led*/
		twim_init();                 /* Initializes the TWI interface*/
	  create_queues();             /* Create queues for the transfer of the Bio-Impedence data*/
    ads1292r_ref_voltage_init(); /* Initialize the reference voltage for ADS1292R*/
	 
    ads1292r_init();             /* Initialize the ADS1292R device*/
    ads1292r_id = ads1292r_read_id(); /* Get the ADS1292R ID */
	
		NRF_LOG_INFO ("End of initialization of modules\n");
    NRF_LOG_INFO ("");
    NRF_LOG_INFO ("ads id: %x", ads1292r_id);
		
    ads1292r_send_command(ADS_SDATAC); /* Stop data transfer from ADS1292R before reading the registers from ADS1292R*/
		
    NRF_LOG_INFO ("config1 register : %x", ads1292r_read_register(ADS_CONFIG1_READ, 1));
    NRF_LOG_INFO ("config2 register : %x", ads1292r_read_register(ADS_CONFIG2_READ, 1));
    NRF_LOG_INFO ("channel1 register: %x", ads1292r_read_register(ADS_CHANNEL1_READ, 1));
    NRF_LOG_INFO ("channel2 register: %x", ads1292r_read_register(ADS_CHANNEL2_READ, 1));

    NRF_LOG_INFO ("hello and welcome");
		
    SEGGER_SYSVIEW_Conf(); /*Configure the SYSVIEW */
}
