/**
 * Copyright (c) 2014 - 2018, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
/** @file
 *
 * @defgroup ble_sdk_uart_over_ble_main main.c
 * @{
 * @ingroup  ble_sdk_app_nus_eval
 * @brief    UART over BLE application main file.
 *
 * This file contains the source code for a sample application that uses the Nordic UART service.
 * This application uses the @ref srvlib_conn_params module.
 */


#include <stdint.h>
#include <string.h>
#include "nordic_common.h"
#include "nrf.h"
#include "ble_hci.h"
#include "ble_advdata.h"
#include "ble_advertising.h"
#include "ble_conn_params.h"
#include "nrf_sdh.h"
#include "nrf_sdh_soc.h"
#include "nrf_sdh_ble.h"
#include "nrf_ble_gatt.h"
#include "nrf_ble_qwr.h"
#include "app_timer.h"

#include "app_dts_service.h"
#include "app_acc_service.h"
#include "app_util_platform.h"

#include "nrf_pwr_mgmt.h"

#include "nrf_drv_gpiote.h"
#include "nrf_sdh_freertos.h"
#include "app_helper.h"
#include "ads1292r.h"


#if defined (UART_PRESENT)
#include "nrf_uart.h"
#endif
#if defined (UARTE_PRESENT)
#include "nrf_uarte.h"
#endif

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "peer_manager.h"

#define APP_BLE_CONN_CFG_TAG            1                                           /**< A tag identifying the SoftDevice BLE configuration. */

#define DEVICE_NAME                     "MED-EL LP2"                                /**< Name of device. Will be included in the advertising data. */
#define LP2_DTS_SERVICE_UUID_TYPE       BLE_UUID_TYPE_VENDOR_BEGIN                  /**< UUID type for the Nordic UART Service (vendor specific). */

#define APP_BLE_OBSERVER_PRIO           3                                           /**< Application's BLE observer priority. You shouldn't need to modify this value. */

#define APP_ADV_INTERVAL                64                                          /**< The advertising interval (in units of 0.625 ms. This value corresponds to 40 ms). */

#define APP_ADV_DURATION                18000                                       /**< The advertising duration (180 seconds) in units of 10 milliseconds. */

#define MIN_CONN_INTERVAL               MSEC_TO_UNITS(7.5, UNIT_1_25_MS)             /**< Minimum acceptable connection interval (20 ms), Connection interval uses 1.25 ms units. */
#define MAX_CONN_INTERVAL               MSEC_TO_UNITS(30, UNIT_1_25_MS)             /**< Maximum acceptable connection interval (75 ms), Connection interval uses 1.25 ms units. */
#define SLAVE_LATENCY                   0                                           /**< Slave latency. */
#define CONN_SUP_TIMEOUT                MSEC_TO_UNITS(3200, UNIT_10_MS)             /**< Connection supervisory timeout (4 seconds), Supervision Timeout uses 10 ms units. */
#define FIRST_CONN_PARAMS_UPDATE_DELAY  5000                       /**< Time from initiating event (connect or start of notification) to first time sd_ble_gap_conn_param_update is called (5 seconds). */
#define NEXT_CONN_PARAMS_UPDATE_DELAY   30000                      /**< Time between each call to sd_ble_gap_conn_param_update after the first call (30 seconds). */
#define MAX_CONN_PARAMS_UPDATE_COUNT    3                                           /**< Number of attempts before giving up the connection parameter negotiation. */

#define DEAD_BEEF                       0xDEADBEEF                                  /**< Value used as error code on stack dump, can be used to identify stack location on stack unwind. */

#define UART_TX_BUF_SIZE                256                                         /**< UART TX buffer size. */
#define UART_RX_BUF_SIZE                256                                         /**< UART RX buffer size. */


BLE_LP2_DTS_DEF(m_app_dts, NRF_SDH_BLE_TOTAL_LINK_COUNT);                                   /**< BLE NUS service instance. */
BLE_LP2_ACC_DEF(m_acc_dts, NRF_SDH_BLE_TOTAL_LINK_COUNT);                                   /**< BLE NUS service instance. */

//BLE_LP2_DTS_DEF(m_app_dts);  
NRF_BLE_GATT_DEF(m_gatt);                                                           /**< GATT module instance. */
NRF_BLE_QWR_DEF(m_qwr);                                                             /**< Context for the Queued Write module.*/
BLE_ADVERTISING_DEF(m_advertising);                                                 /**< Advertising module instance. */

static uint16_t   m_conn_handle          = BLE_CONN_HANDLE_INVALID;                 /**< Handle of the current connection. */
static uint16_t   m_ble_app_dts_max_data_len = BLE_GATT_ATT_MTU_DEFAULT - 3;            /**< Maximum length of data (in bytes) that can be transmitted to the peer by the Nordic UART service module. */
static ble_uuid_t m_adv_uuids[]          =                                          /**< Universally unique service identifier. */
{
    {BLE_UUID_LP2_DTS_SERVICE, LP2_DTS_SERVICE_UUID_TYPE}
};


/**@brief Function for assert macro callback.
 *
 * @details This function will be called in case of an assert in the SoftDevice.
 *
 * @warning This handler is an example only and does not fit a final product. You need to analyse
 *          how your product is supposed to react in case of Assert.
 * @warning On assert from the SoftDevice, the system can only recover on reset.
 *
 * @param[in] line_num    Line number of the failing ASSERT call.
 * @param[in] p_file_name File name of the failing ASSERT call.
 */
void assert_nrf_callback(uint16_t line_num, const uint8_t * p_file_name)
{
    app_error_handler(DEAD_BEEF, line_num, p_file_name);
}

/**@brief Function for initializing the timer module.
 */
static void timers_init(void)
{
    ret_code_t err_code = app_timer_init();
    APP_ERROR_CHECK(err_code);
}

/**@brief Function for the GAP initialization.
 *
 * @details This function will set up all the necessary GAP (Generic Access Profile) parameters of
 *          the device. It also sets the permissions and appearance.
 */
static void gap_params_init(void)
{
    uint32_t                err_code;
    ble_gap_conn_params_t   gap_conn_params;
    ble_gap_conn_sec_mode_t sec_mode;

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&sec_mode);

    err_code = sd_ble_gap_device_name_set(&sec_mode,
                                          (const uint8_t *) DEVICE_NAME,
                                          strlen(DEVICE_NAME));
    APP_ERROR_CHECK(err_code);

    memset(&gap_conn_params, 0, sizeof(gap_conn_params));

    gap_conn_params.min_conn_interval = MIN_CONN_INTERVAL;
    gap_conn_params.max_conn_interval = MAX_CONN_INTERVAL;
    gap_conn_params.slave_latency     = SLAVE_LATENCY;
    gap_conn_params.conn_sup_timeout  = CONN_SUP_TIMEOUT;

    err_code = sd_ble_gap_ppcp_set(&gap_conn_params);
    APP_ERROR_CHECK(err_code);
}


/**@brief Function for handling Queued Write Module errors.
 *
 * @details A pointer to this function will be passed to each service which may need to inform the
 *          application about an error.
 *
 * @param[in]   nrf_error   Error code containing information about what went wrong.
 */
static void nrf_qwr_error_handler(uint32_t nrf_error)
{
    APP_ERROR_HANDLER(nrf_error);
}

/**@brief Function for handling the data from the Nordic UART Service.
 *
 * @details This function will process the data received from the Nordic UART BLE Service and send
 *          it to the UART module.
 *
 * @param[in] p_evt       Nordic UART Service event.
 */
/**@snippet [Handling the data received over BLE] */
static void app_acc_data_handler(ble_app_acc_evt_t * p_evt)
{

    if (p_evt->type == BLE_LP2_ACC_EVT_RX_DATA)
    {
        //uint32_t err_code;

        //NRF_LOG_DEBUG("Received data from BLE NUS. Writing data on UART.");
        //NRF_LOG_HEXDUMP_DEBUG(p_evt->params.rx_data.p_data, p_evt->params.rx_data.length);

//        for (uint32_t i = 0; i < p_evt->params.rx_data.length; i++)
//        {
//            do
//            {
//                err_code = app_uart_put(p_evt->params.rx_data.p_data[i]);
//                if ((err_code != NRF_SUCCESS) && (err_code != NRF_ERROR_BUSY))
//                {
//                    NRF_LOG_ERROR("Failed receiving NUS message. Error 0x%x. ", err_code);
//                    APP_ERROR_CHECK(err_code);
//                }
//            } while (err_code == NRF_ERROR_BUSY);
//        }
//        if (p_evt->params.rx_data.p_data[p_evt->params.rx_data.length - 1] == '\r')
//        {
//            while (app_uart_put('\n') == NRF_ERROR_BUSY);
//        }
    }

}
/**@brief Function for handling the data from the Nordic UART Service.
 *
 * @details This function will process the data received from the Nordic UART BLE Service and send
 *          it to the UART module.
 *
 * @param[in] p_evt       Nordic UART Service event.
 */
/**@snippet [Handling the data received over BLE] */
static void app_dts_data_handler(ble_app_dts_evt_t * p_evt)
{

    if (p_evt->type == BLE_LP2_DTS_EVT_RX_DATA)
    {
			NRF_LOG_INFO("Data Received 0x%x. ", p_evt->params.rx_data.p_data[0]);
			if (p_evt->params.rx_data.p_data[0] == STOP_TRANSFER)
			{
				NRF_LOG_INFO("Stop Data Transfer");
				
			}
			else if (p_evt->params.rx_data.p_data[0] == START_TRANSFER)
			{
				NRF_LOG_INFO("Start Data Transfer");
		
			}
			else if (p_evt->params.rx_data.p_data[0] == READ_ADS_DATA)
			{
				//gpiote_disable_interrupt(0, false);
				NRF_LOG_INFO ("");
				NRF_LOG_INFO ("ads id: 0x%x", ads1292r_read_register(0x20, 0));
		
				NRF_LOG_INFO ("config1 register : 0x%x", ads1292r_read_register(ADS_CONFIG1_READ, 1));
				NRF_LOG_INFO ("config2 register : 0x%x", ads1292r_read_register(ADS_CONFIG2_READ, 1));
				NRF_LOG_INFO ("channel1 register: 0x%x", ads1292r_read_register(ADS_CHANNEL1_READ, 1));
				NRF_LOG_INFO ("channel2 register: 0x%x", ads1292r_read_register(ADS_CHANNEL2_READ, 1));
				//gpiote_enable_interrupt(0, false);
			}
			else if (p_evt->params.rx_data.p_data[0] == SAMPLING_RATE_125SPS)
			{
				ads1292r_send_command(ADS_SDATAC);
				ads1292r_set_register(0x41, 1, 00);
				NRF_LOG_INFO ("");
				NRF_LOG_INFO ("Changing the sampling rate to 125SPS");
				NRF_LOG_INFO ("ads id: 0x%x", ads1292r_read_register(0x20, 0));
		
				NRF_LOG_INFO ("config1 register :0x%x", ads1292r_read_register(ADS_CONFIG1_READ, 1));
				NRF_LOG_INFO ("config2 register : 0x%x", ads1292r_read_register(ADS_CONFIG2_READ, 1));
				NRF_LOG_INFO ("channel1 register: 0x%x", ads1292r_read_register(ADS_CHANNEL1_READ, 1));
				NRF_LOG_INFO ("channel2 register: 0x%x", ads1292r_read_register(ADS_CHANNEL2_READ, 1));
			}
			else if (p_evt->params.rx_data.p_data[0] == SAMPLING_RATE_250SPS)
			{
				ads1292r_send_command(ADS_SDATAC);
				ads1292r_set_register(0x41, 1, 01);
				NRF_LOG_INFO ("");
				NRF_LOG_INFO ("Changing the sampling rate to 250SPS");
				NRF_LOG_INFO ("ads id: 0x%x", ads1292r_read_register(0x20, 0));
		
				NRF_LOG_INFO ("config1 register : 0x%x", ads1292r_read_register(ADS_CONFIG1_READ, 1));
				NRF_LOG_INFO ("config2 register : 0x%x", ads1292r_read_register(ADS_CONFIG2_READ, 1));
				NRF_LOG_INFO ("channel1 register: 0x%x", ads1292r_read_register(ADS_CHANNEL1_READ, 1));
				NRF_LOG_INFO ("channel2 register: 0x%x", ads1292r_read_register(ADS_CHANNEL2_READ, 1));
			}
			else if (p_evt->params.rx_data.p_data[0] == SAMPLING_RATE_500SPS)
			{
				ads1292r_send_command(ADS_SDATAC);
				ads1292r_set_register(0x41, 1, 02);
				NRF_LOG_INFO ("");
				NRF_LOG_INFO ("Changing the sampling rate to 500SPS");
				NRF_LOG_INFO ("ads id: 0x%x", ads1292r_read_register(0x20, 0));
		
				NRF_LOG_INFO ("config1 register : 0x%x", ads1292r_read_register(ADS_CONFIG1_READ, 1));
				NRF_LOG_INFO ("config2 register : 0x%x", ads1292r_read_register(ADS_CONFIG2_READ, 1));
				NRF_LOG_INFO ("channel1 register: 0x%x", ads1292r_read_register(ADS_CHANNEL1_READ, 1));
				NRF_LOG_INFO ("channel2 register: 0x%x", ads1292r_read_register(ADS_CHANNEL2_READ, 1));
			}
			else if (p_evt->params.rx_data.p_data[0] == SAMPLING_RATE_1KSPS)
			{
				ads1292r_send_command(ADS_SDATAC);
				ads1292r_set_register(0x41, 1, 03);
				NRF_LOG_INFO ("");
				NRF_LOG_INFO ("Changing the sampling rate to 1KSPS");
				NRF_LOG_INFO ("ads id: 0x%x", ads1292r_read_register(0x20, 0));
		
				NRF_LOG_INFO ("config1 register : 0x%x", ads1292r_read_register(ADS_CONFIG1_READ, 1));
				NRF_LOG_INFO ("config2 register : 0x%x", ads1292r_read_register(ADS_CONFIG2_READ, 1));
				NRF_LOG_INFO ("channel1 register: 0x%x", ads1292r_read_register(ADS_CHANNEL1_READ, 1));
				NRF_LOG_INFO ("channel2 register: 0x%x", ads1292r_read_register(ADS_CHANNEL2_READ, 1));
			}
			else if (p_evt->params.rx_data.p_data[0] == SAMPLING_RATE_2KSPS)
			{
				ads1292r_send_command(ADS_SDATAC);
				ads1292r_set_register(0x41, 1, 04);
				NRF_LOG_INFO ("");
				NRF_LOG_INFO ("Changing the sampling rate to 2KSPS");
				NRF_LOG_INFO ("ads id: 0x%x", ads1292r_read_register(0x20, 0));
		
				NRF_LOG_INFO ("config1 register : 0x%x", ads1292r_read_register(ADS_CONFIG1_READ, 1));
				NRF_LOG_INFO ("config2 register : 0x%x", ads1292r_read_register(ADS_CONFIG2_READ, 1));
				NRF_LOG_INFO ("channel1 register: 0x%x", ads1292r_read_register(ADS_CHANNEL1_READ, 1));
				NRF_LOG_INFO ("channel2 register: 0x%x", ads1292r_read_register(ADS_CHANNEL2_READ, 1));
			}
			else if (p_evt->params.rx_data.p_data[0] == SAMPLING_RATE_4KSPS)
			{
				ads1292r_send_command(ADS_SDATAC);
				ads1292r_set_register(0x41, 1, 05);
				NRF_LOG_INFO ("");
				NRF_LOG_INFO ("Changing the sampling rate to 4KSPS");
				NRF_LOG_INFO ("ads id: 0x%x", ads1292r_read_register(0x20, 0));
		
				NRF_LOG_INFO ("config1 register : 0x%x", ads1292r_read_register(ADS_CONFIG1_READ, 1));
				NRF_LOG_INFO ("config2 register : 0x%x", ads1292r_read_register(ADS_CONFIG2_READ, 1));
				NRF_LOG_INFO ("channel1 register: 0x%x", ads1292r_read_register(ADS_CHANNEL1_READ, 1));
				NRF_LOG_INFO ("channel2 register: 0x%x", ads1292r_read_register(ADS_CHANNEL2_READ, 1));
			}
			else if (p_evt->params.rx_data.p_data[0] == SAMPLING_RATE_8KSPS)
			{
				ads1292r_send_command(ADS_SDATAC);
				ads1292r_set_register(0x41, 1, 06);
				NRF_LOG_INFO ("");
				NRF_LOG_INFO ("Changing the sampling rate to 8KSPS");
				NRF_LOG_INFO ("ads id: %x", ads1292r_read_register(0x20, 0));
		
				NRF_LOG_INFO ("config1 register : 0x%x", ads1292r_read_register(ADS_CONFIG1_READ, 1));
				NRF_LOG_INFO ("config2 register : 0x%x", ads1292r_read_register(ADS_CONFIG2_READ, 1));
				NRF_LOG_INFO ("channel1 register: 0x%x", ads1292r_read_register(ADS_CHANNEL1_READ, 1));
				NRF_LOG_INFO ("channel2 register: 0x%x", ads1292r_read_register(ADS_CHANNEL2_READ, 1));
			}
			else
			{
					NRF_LOG_INFO ("Invalid data");
			}
			
    }
}
/**@snippet [Handling the data received over BLE] */


/**@brief Function for initializing services that will be used by the application.
 */
static void services_init(void)
{
    uint32_t           err_code;
		
    ble_app_dts_init_t     app_dts_init;
	ble_app_acc_init_t     app_acc_init;
    nrf_ble_qwr_init_t qwr_init = {0};

    // Initialize Queued Write Module.
    qwr_init.error_handler = nrf_qwr_error_handler;

    err_code = nrf_ble_qwr_init(&m_qwr, &qwr_init);
    APP_ERROR_CHECK(err_code);

    // Initialize NUS.
    memset(&app_dts_init, 0, sizeof(app_dts_init));

    app_dts_init.data_handler = app_dts_data_handler;

    err_code = ble_app_dts_init(&m_app_dts, &app_dts_init);
    APP_ERROR_CHECK(err_code);
		
		// Initialize Acc.
    memset(&app_acc_init, 0, sizeof(app_dts_init));

    app_acc_init.data_handler = app_acc_data_handler;

    err_code = ble_app_acc_init(&m_acc_dts, &app_acc_init);
    APP_ERROR_CHECK(err_code);
		
		// Initialize Battery Service.
//    memset(&bas_init, 0, sizeof(bas_init));

//    // Here the sec level for the Battery Service can be changed/increased.
//    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&bas_init.battery_level_char_attr_md.cccd_write_perm);
//    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&bas_init.battery_level_char_attr_md.read_perm);
//    BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&bas_init.battery_level_char_attr_md.write_perm);

//    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&bas_init.battery_level_report_read_perm);

//    bas_init.evt_handler          = NULL;
//    bas_init.support_notification = true;
//    bas_init.p_report_ref         = NULL;
//    bas_init.initial_batt_level   = 100;

//    err_code = ble_bas_init(&m_bas, &bas_init);
//    APP_ERROR_CHECK(err_code);
		
		
}


/**@brief Function for handling an event from the Connection Parameters Module.
 *
 * @details This function will be called for all events in the Connection Parameters Module
 *          which are passed to the application.
 *
 * @note All this function does is to disconnect. This could have been done by simply setting
 *       the disconnect_on_fail config parameter, but instead we use the event handler
 *       mechanism to demonstrate its use.
 *
 * @param[in] p_evt  Event received from the Connection Parameters Module.
 */
static void on_conn_params_evt(ble_conn_params_evt_t * p_evt)
{
    uint32_t err_code;

    if (p_evt->evt_type == BLE_CONN_PARAMS_EVT_FAILED)
    {
        err_code = sd_ble_gap_disconnect(m_conn_handle, BLE_HCI_CONN_INTERVAL_UNACCEPTABLE);
        APP_ERROR_CHECK(err_code);
    }
}


/**@brief Function for handling errors from the Connection Parameters module.
 *
 * @param[in] nrf_error  Error code containing information about what went wrong.
 */
static void conn_params_error_handler(uint32_t nrf_error)
{
    APP_ERROR_HANDLER(nrf_error);
}


/**@brief Function for initializing the Connection Parameters module.
 */
static void conn_params_init(void)
{
    volatile uint32_t               err_code;
    ble_conn_params_init_t cp_init;

    memset(&cp_init, 0, sizeof(cp_init));

    cp_init.p_conn_params                  = NULL;
    cp_init.first_conn_params_update_delay = FIRST_CONN_PARAMS_UPDATE_DELAY;
    cp_init.next_conn_params_update_delay  = NEXT_CONN_PARAMS_UPDATE_DELAY;
    cp_init.max_conn_params_update_count   = MAX_CONN_PARAMS_UPDATE_COUNT;
    cp_init.start_on_notify_cccd_handle    = BLE_GATT_HANDLE_INVALID;
    cp_init.disconnect_on_fail             = false;
    cp_init.evt_handler                    = on_conn_params_evt;
    cp_init.error_handler                  = conn_params_error_handler;

    err_code = ble_conn_params_init(&cp_init);
    APP_ERROR_CHECK(err_code);
}

/**@brief Function for handling advertising events.
 *
 * @details This function will be called for advertising events which are passed to the application.
 *
 * @param[in] ble_adv_evt  Advertising event.
 */
static void on_adv_evt(ble_adv_evt_t ble_adv_evt)
{
    uint32_t err_code;

    switch (ble_adv_evt)
    {
        case BLE_ADV_EVT_FAST:
           // err_code = bsp_indication_set(BSP_INDICATE_ADVERTISING);
            APP_ERROR_CHECK(err_code);
            break;
        case BLE_ADV_EVT_IDLE:
           // sleep_mode_enter();
            break;
        default:
            break;
    }
}

/**@brief Function for handling BLE events.
 *
 * @param[in]   p_ble_evt   Bluetooth stack event.
 * @param[in]   p_context   Unused.
 */
static void ble_evt_handler(ble_evt_t const * p_ble_evt, void * p_context)
{
    uint32_t err_code;

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            //NRF_LOG_INFO("Connected");
           // err_code = bsp_indication_set(BSP_INDICATE_CONNECTED);
           // APP_ERROR_CHECK(err_code);
            m_conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
            err_code = nrf_ble_qwr_conn_handle_assign(&m_qwr, m_conn_handle);
            APP_ERROR_CHECK(err_code);
				   // data_rdy_init();
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            NRF_LOG_INFO("Disconnected");
            // LED indication will be changed when advertising starts.
            m_conn_handle = BLE_CONN_HANDLE_INVALID;
            break;

        case BLE_GAP_EVT_PHY_UPDATE_REQUEST:
        {
            NRF_LOG_DEBUG("PHY update request.");
            ble_gap_phys_t const phys =
            {
                .rx_phys = BLE_GAP_PHY_AUTO,
                .tx_phys = BLE_GAP_PHY_AUTO,
            };
            err_code = sd_ble_gap_phy_update(p_ble_evt->evt.gap_evt.conn_handle, &phys);
            APP_ERROR_CHECK(err_code);
        } break;

        case BLE_GAP_EVT_SEC_PARAMS_REQUEST:
            // Pairing not supported
            err_code = sd_ble_gap_sec_params_reply(m_conn_handle, BLE_GAP_SEC_STATUS_PAIRING_NOT_SUPP, NULL, NULL);
            APP_ERROR_CHECK(err_code);
            break;

        case BLE_GATTS_EVT_SYS_ATTR_MISSING:
            // No system attributes have been stored.
            err_code = sd_ble_gatts_sys_attr_set(m_conn_handle, NULL, 0, 0);
            APP_ERROR_CHECK(err_code);
            break;

        case BLE_GATTC_EVT_TIMEOUT:
            // Disconnect on GATT Client timeout event.
            err_code = sd_ble_gap_disconnect(p_ble_evt->evt.gattc_evt.conn_handle,
                                             BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION);
            APP_ERROR_CHECK(err_code);
            break;

        case BLE_GATTS_EVT_TIMEOUT:
            // Disconnect on GATT Server timeout event.
            err_code = sd_ble_gap_disconnect(p_ble_evt->evt.gatts_evt.conn_handle,
                                             BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION);
            APP_ERROR_CHECK(err_code);
            break;

        default:
            // No implementation needed.
            break;
    }
}


/**@brief Function for the SoftDevice initialization.
 *
 * @details This function initializes the SoftDevice and the BLE event interrupt.
 */
static void ble_stack_init(void)
{
    ret_code_t err_code;

    err_code = nrf_sdh_enable_request();
    APP_ERROR_CHECK(err_code);

    // Configure the BLE stack using the default settings.
    // Fetch the start address of the application RAM.
    uint32_t ram_start = 0;
    err_code = nrf_sdh_ble_default_cfg_set(APP_BLE_CONN_CFG_TAG, &ram_start);
    APP_ERROR_CHECK(err_code);

    // Enable BLE stack.
    err_code = nrf_sdh_ble_enable(&ram_start);
    APP_ERROR_CHECK(err_code);

    // Register a handler for BLE events.
    NRF_SDH_BLE_OBSERVER(m_ble_observer, APP_BLE_OBSERVER_PRIO, ble_evt_handler, NULL);
}


/**@brief Function for handling events from the GATT library. */
void gatt_evt_handler(nrf_ble_gatt_t * p_gatt, nrf_ble_gatt_evt_t const * p_evt)
{
    if ((m_conn_handle == p_evt->conn_handle) && (p_evt->evt_id == NRF_BLE_GATT_EVT_ATT_MTU_UPDATED))
    {
        m_ble_app_dts_max_data_len = p_evt->params.att_mtu_effective - OPCODE_LENGTH - HANDLE_LENGTH;
        NRF_LOG_INFO("Data len is set to 0x%X(%d)", m_ble_app_dts_max_data_len, m_ble_app_dts_max_data_len);
    }
    NRF_LOG_DEBUG("ATT MTU exchange completed. central 0x%x peripheral 0x%x",
                  p_gatt->att_mtu_desired_central,
                  p_gatt->att_mtu_desired_periph);
}


/**@brief Function for initializing the GATT library. */
void gatt_init(void)
{
    volatile ret_code_t err_code;

    err_code = nrf_ble_gatt_init(&m_gatt, gatt_evt_handler);
    APP_ERROR_CHECK(err_code);

    err_code = nrf_ble_gatt_att_mtu_periph_set(&m_gatt, NRF_SDH_BLE_GATT_MAX_MTU_SIZE);
    APP_ERROR_CHECK(err_code);
}

/**@brief Function for initializing the Advertising functionality.
 */
static void advertising_init(void)
{
    volatile uint32_t               err_code;
    ble_advertising_init_t init;

    memset(&init, 0, sizeof(init));

    init.advdata.name_type          = BLE_ADVDATA_FULL_NAME;
    init.advdata.include_appearance = false;
    init.advdata.flags              = BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE;

    init.srdata.uuids_complete.uuid_cnt = sizeof(m_adv_uuids) / sizeof(m_adv_uuids[0]);
    init.srdata.uuids_complete.p_uuids  = m_adv_uuids;

    init.config.ble_adv_fast_enabled  = true;
    init.config.ble_adv_fast_interval = APP_ADV_INTERVAL;
    init.config.ble_adv_fast_timeout  = APP_ADV_DURATION;
    init.evt_handler = on_adv_evt;

    err_code = ble_advertising_init(&m_advertising, &init);
    APP_ERROR_CHECK(err_code);

    ble_advertising_conn_cfg_tag_set(&m_advertising, APP_BLE_CONN_CFG_TAG);
}

/**@brief Function for starting advertising.
 */
void advertising_start(void)
{
    uint32_t err_code = ble_advertising_start(&m_advertising, BLE_ADV_MODE_FAST);
    APP_ERROR_CHECK(err_code);
}

uint32_t send_acc_data_ble (uint8_t *input_ptr, uint16_t *data_len)
{
	
	uint32_t err_code = 0;
	err_code = ble_app_acc_data_send (&m_acc_dts, input_ptr, data_len, m_conn_handle);
	
	return err_code;
}

uint32_t send_data_ble (uint8_t *input_ptr, uint16_t *data_len)
{
	
	uint32_t err_code = 0;
	err_code = ble_app_dts_data_send (&m_app_dts, input_ptr, data_len, m_conn_handle);
	
	return err_code;
}

#define SEC_PARAM_BOND                      1                                       /**< Perform bonding. */
#define SEC_PARAM_MITM                      0                                       /**< Man In The Middle protection not required. */
#define SEC_PARAM_LESC                      0                                       /**< LE Secure Connections not enabled. */
#define SEC_PARAM_KEYPRESS                  0                                       /**< Keypress notifications not enabled. */
#define SEC_PARAM_IO_CAPABILITIES           BLE_GAP_IO_CAPS_NONE                    /**< No I/O capabilities. */
#define SEC_PARAM_OOB                       0                                       /**< Out Of Band data not available. */
#define SEC_PARAM_MIN_KEY_SIZE              7                                       /**< Minimum encryption key size. */
#define SEC_PARAM_MAX_KEY_SIZE              16                                      /**< Maximum encryption key size. */

void conn_evt_len_ext_set(bool status)
{
    ret_code_t err_code;
    ble_opt_t  opt;

    memset(&opt, 0x00, sizeof(opt));
    opt.common_opt.conn_evt_ext.enable = status ? 1 : 0;

    err_code = sd_ble_opt_set(BLE_COMMON_OPT_CONN_EVT_EXT, &opt);
    APP_ERROR_CHECK(err_code);

    //m_test_params.conn_evt_len_ext_enabled = status;
}

/**@brief Initialization of the nRF BLE
 */
void bluetooth_init(void)
{
    bool erase_bonds;

	  ble_stack_init();

    // Initialize modules required for Bluetooth.
    timers_init();
    gap_params_init();
    gatt_init();
		services_init();
    advertising_init();
    conn_params_init();
	  conn_evt_len_ext_set(true);
	
    // Create a FreeRTOS task for the BLE stack.
    // The task will run advertising_start() before entering its loop.
    nrf_sdh_freertos_init(advertising_start, &erase_bonds);
	
}


/**
 * @}
 */
