#ifndef BLE_LP2_HELPER
#define BLE_LP2_HELPER

#include <stdint.h>


#define BATT_CONFIG                    4
#define TWI_SDA                        8
#define TWI_SCLK                       12


/*Bluetooth Commands*/
#define STOP_TRANSFER                        0X01
#define START_TRANSFER                       0X02
#define READ_ADS_DATA                        0X03

#define SAMPLING_RATE_125SPS                 0X04
#define SAMPLING_RATE_250SPS                 0X05
#define SAMPLING_RATE_500SPS                 0X06
#define SAMPLING_RATE_1KSPS                  0X07
#define SAMPLING_RATE_2KSPS                  0X08
#define SAMPLING_RATE_4KSPS                  0X09
#define SAMPLING_RATE_8KSPS                  0x0A



void bluetooth_init(void);
uint32_t send_data_ble (uint8_t *input_ptr, uint16_t *data_len);
uint32_t send_acc_data_ble (uint8_t *input_ptr, uint16_t *data_len);

void int_BQ25120_init(void);
void sleep(void);
//void data_rdy_init();
#endif
