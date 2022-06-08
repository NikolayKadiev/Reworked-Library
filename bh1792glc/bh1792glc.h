
// the header for BH1792GLC


#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c.h"


/**
 * \defgroup device_address Device address
 * \{
 */
#define BH1792GLC_SLAVE_ADDR                         0x5B
/** \} */

/**
 * \defgroup register_address Register addresses
 * \{
 */
#define BH1792GLC_MANUFACT_ID_REG                    0x0F
#define BH1792GLC_PART_ID_REG                        0x10
#define BH1792GLC_RESET_REG                          0x40
#define BH1792GLC_MEAS_CTRL1_REG                     0x41
#define BH1792GLC_MEAS_CTRL2_REG                     0x42
#define BH1792GLC_MEAS_CTRL3_REG                     0x43
#define BH1792GLC_MEAS_CTRL4_LSB_REG                 0x44
#define BH1792GLC_MEAS_CTRL4_MSB_REG                 0x45
#define BH1792GLC_MEAS_CTRL5_REG                     0x46
#define BH1792GLC_MEAS_START_REG                     0x47
#define BH1792GLC_MEAS_SYNC_REG                      0x48
#define BH1792GLC_FIFO_LEV_REG                       0x4B
#define BH1792GLC_FIFO_DATA0_LSB_REG                 0x4C
#define BH1792GLC_FIFO_DATA0_MSB_REG                 0x4D
#define BH1792GLC_FIFO_DATA1_LSB_REG                 0x4E
#define BH1792GLC_FIFO_DATA1_MSB_REG                 0x4F
#define BH1792GLC_IRDATA_LEDOFF_LSB_REG              0x50
#define BH1792GLC_IRDATA_LEDOFF_MSB_REG              0x51
#define BH1792GLC_IRDATA_LEDON_LSB_REG               0x52
#define BH1792GLC_IRDATA_LEDON_MSB_REG               0x53
#define BH1792GLC_GDATA_LEDOFF_LSB_REG               0x54
#define BH1792GLC_GDATA_LEDOFF_MSB_REG               0x55
#define BH1792GLC_GDATA_LEDON_LSB_REG                0x56
#define BH1792GLC_GDATA_LEDON_MSB_REG                0x57
#define BH1792GLC_INT_CLEAR_REG                      0x58
/** \} */

/**
 * \defgroup register_settings Register settings and commands
 * \{
 */
#define BH1792GLC_RESET_CMD                          0x80
#define BH1792GLC_OSC_ACTIVE                         0x80
#define BH1792GLC_GREEN_MEAS_MODE                    0x00
#define BH1792GLC_IR_MEAS_MODE                       0x10
#define BH1792GLC_32HZ_MEAS_MODE                     0x00
#define BH1792GLC_128HZ_MEAS_MODE                    0x01
#define BH1792GLC_64HZ_MEAS_MODE                     0x02
#define BH1792GLC_256HZ_MEAS_MODE                    0x03
#define BH1792GLC_1024HZ_MEAS_MODE                   0x05
#define BH1792GLC_NON_SYNC_MEAS_MODE                 0x06
#define BH1792GLC_SINGLE_MEAS_MODE                   0x07
#define BH1792GLC_LEDS_PULSED                        0x00
#define BH1792GLC_LED1_ON                            0x40
#define BH1792GLC_LED2_ON                            0x80
#define BH1792GLC_LEDS_ON                            0xC0
#define BH1792GLC_LED3_OFF                           0x00
#define BH1792GLC_LED3_ON                            0x80
#define BH1792GLC_STOP_EMISSION                      0x00
#define BH1792GLC_LED_CURR_1MA                       0x01
#define BH1792GLC_LED_CURR_2MA                       0x02
#define BH1792GLC_LED_CURR_5MA                       0x05
#define BH1792GLC_LED_CURR_10MA                      0x0A
#define BH1792GLC_LED_CURR_15MA                      0x0F
#define BH1792GLC_LED_CURR_20MA                      0x14
#define BH1792GLC_LED_CURR_25MA                      0x19
#define BH1792GLC_LED_CURR_30MA                      0x1E
#define BH1792GLC_LED_CURR_35MA                      0x23
#define BH1792GLC_LED_CURR_40MA                      0x28
#define BH1792GLC_LED_CURR_45MA                      0x2D
#define BH1792GLC_LED_CURR_50MA                      0x32
#define BH1792GLC_LED_CURR_55MA                      0x37
#define BH1792GLC_LED_CURR_60MA                      0x3C
#define BH1792GLC_LED_CURR_63MA                      0x3F
#define BH1792GLC_LED_CURR_CUSTOM                    0x01 // 1 bit = 1 mA
#define BH1792GLC_INT_DISABLE                        0x00
#define BH1792GLC_INT_WATER_MARK_FIFO                0x01
#define BH1792GLC_INT_IR_THRESH                      0x02
#define BH1792GLC_INT_MEAS_COMPLET                   0x03
#define BH1792GLC_MEAS_START_CMD                     0x01
#define BH1792GLC_MEAS_SYNC_CMD                      0x01
/** \} */

/**
 * \defgroup data_select Data selection for Get function
 * \{
 */
#define BH1792GLC_FIFO_DATA_GET                      0x00
#define BH1792GLC_IR_DATA_GET                        0x01
#define BH1792GLC_GREEN_DATA_GET                     0x02
/** \} */

void BH1792GLC_write_single_byte (uint8_t reg_addr, uint8_t data_in );
uint16_t BH1792GLC_read_bytes ( uint8_t start_addr, uint8_t *data_out, uint8_t n_bytes );
void BH1792GLC_start_measure ( void );
void BH1792GLC_reset ( void );
void BH1792GLC_meas_sync ( void );
uint8_t BH1792GLC_int_clear ( void );
void BH1792GLC_default_cfg ( void );
uint16_t BH1792GLC_get_data ( uint8_t data_select);
