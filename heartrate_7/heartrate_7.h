#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c.h"
/**
 * \defgroup dev_slave_adr Device slave address
 * \{
 */
#define HEARTRATE_SLAVE_ADDR          0x58
/** \} */
/**
 * \defgroup register_map Register map
 * \{
 */
#define HEARTRATE_CONTROL0            0x00
#define HEARTRATE_LED2STC             0x01
#define HEARTRATE_LED2ENDC            0x02
#define HEARTRATE_LED1LEDSTC          0x03
#define HEARTRATE_LED1LEDENDC         0x04
#define HEARTRATE_ALED2STC            0x05
#define HEARTRATE_ALED2ENDC           0x06
#define HEARTRATE_LED1STC             0x07
#define HEARTRATE_LED1ENDC            0x08
#define HEARTRATE_LED2LEDSTC          0x09
#define HEARTRATE_LED2LEDENDC         0x0A
#define HEARTRATE_ALED1STC            0x0B
#define HEARTRATE_ALED1ENDC           0x0C
#define HEARTRATE_LED2CONVST          0x0D
#define HEARTRATE_LED2CONVEND         0x0E
#define HEARTRATE_ALED2CONVST         0x0F
#define HEARTRATE_ALED2CONVEND        0x10
#define HEARTRATE_LED1CONVST          0x11
#define HEARTRATE_LED1CONVEND         0x12
#define HEARTRATE_ALED1CONVST         0x13
#define HEARTRATE_ALED1CONVEND        0x14
#define HEARTRATE_ADCRSTSTCT0         0x15
#define HEARTRATE_ADCRSTENDCT0        0x16
#define HEARTRATE_ADCRSTSTCT1         0x17
#define HEARTRATE_ADCRSTENDCT1        0x18
#define HEARTRATE_ADCRSTSTCT2         0x19
#define HEARTRATE_ADCRSTENDCT2        0x1A
#define HEARTRATE_ADCRSTSTCT3         0x1B
#define HEARTRATE_ADCRSTENDCT3        0x1C
#define HEARTRATE_PRPCOUNT            0x1D
#define HEARTRATE_CONTROL1            0x1E
#define HEARTRATE_TIA_GAIN_SEP        0x20
#define HEARTRATE_TIA_GAIN            0x21
#define HEARTRATE_LEDCNTRL            0x22
#define HEARTRATE_CONTROL2            0x23
#define HEARTRATE_ALARM               0x29
#define HEARTRATE_LED2VAL             0x2A
#define HEARTRATE_ALED2VAL            0x2B
#define HEARTRATE_LED1VAL             0x2C
#define HEARTRATE_ALED1VAL            0x2D
#define HEARTRATE_LED2_ALED2VAL       0x2E
#define HEARTRATE_LED1_ALED1VAL       0x2F
#define HEARTRATE_CONTROL3            0x31
#define HEARTRATE_PDNCYCLESTC         0x32
#define HEARTRATE_PDNCYCLEENDC        0x33
#define HEARTRATE_PROG_TG_STC         0x34
#define HEARTRATE_PROG_TG_ENDC        0x35
#define HEARTRATE_LED3LEDSTC          0x36
#define HEARTRATE_LED3LEDENDC         0x37
#define HEARTRATE_CLKDIV_PRF          0x39
#define HEARTRATE_OFFDAC              0x3A
#define HEARTRATE_DEC                 0x3D
#define HEARTRATE_AVG_LED2_ALED2VAL   0x3F
#define HEARTRATE_AVG_LED1_ALED1VAL   0x40
/** \} */

/**
 * \defgroup cmd_list Configuration commands list
 * \{
 */
#define HEARTRATE_CONTROL0_CMD           0x000000
#define HEARTRATE_LED2STC_CMD            0x000050
#define HEARTRATE_LED2ENDC_CMD           0x00018F
#define HEARTRATE_LED1LEDSTC_CMD         0x000320
#define HEARTRATE_LED1LEDENDC_CMD        0x0004AF
#define HEARTRATE_ALED2STC_CMD           0x0001E0
#define HEARTRATE_ALED2ENDC_CMD          0x00031F
#define HEARTRATE_LED1STC_CMD            0x000370
#define HEARTRATE_LED1ENDC_CMD           0x0004AF
#define HEARTRATE_LED2LEDSTC_CMD         0x000000
#define HEARTRATE_LED2LEDENDC_CMD        0x00018F
#define HEARTRATE_ALED1STC_CMD           0x0004FF
#define HEARTRATE_ALED1ENDC_CMD          0x00063E
#define HEARTRATE_LED2CONVST_CMD         0x000198
#define HEARTRATE_LED2CONVEND_CMD        0x0005BB
#define HEARTRATE_ALED2CONVST_CMD        0x0005C4
#define HEARTRATE_ALED2CONVEND_CMD       0x0009E7
#define HEARTRATE_LED1CONVST_CMD         0x0009F0
#define HEARTRATE_LED1CONVEND_CMD        0x000E13
#define HEARTRATE_ALED1CONVST_CMD        0x000E1C
#define HEARTRATE_ALED1CONVEND_CMD       0x00123F
#define HEARTRATE_ADCRSTSTCT0_CMD        0x000191
#define HEARTRATE_ADCRSTENDCT0_CMD       0x000197
#define HEARTRATE_ADCRSTSTCT1_CMD        0x0005BD
#define HEARTRATE_ADCRSTENDCT1_CMD       0x0005C3
#define HEARTRATE_ADCRSTSTCT2_CMD        0x0009E9
#define HEARTRATE_ADCRSTENDCT2_CMD       0x0009EF
#define HEARTRATE_ADCRSTSTCT3_CMD        0x000E15
#define HEARTRATE_ADCRSTENDCT3_CMD       0x000E1B
#define HEARTRATE_PRPCOUNT_CMD           0x003E7F 
#define HEARTRATE_CONTROL1_CMD           0x000103
#define HEARTRATE_TIA_GAIN_SEP_CMD       0x008003
#define HEARTRATE_TIA_GAIN_CMD           0x000003
#define HEARTRATE_LEDCNTRL_CMD           0x01B6D9
#define HEARTRATE_CONTROL2_CMD           0x104218
#define HEARTRATE_ALARM_CMD              0x000000
#define HEARTRATE_CONTROL3_CMD           0x000000
#define HEARTRATE_PDNCYCLESTC_CMD        0x00155F
#define HEARTRATE_PDNCYCLEENDC_CMD       0x003B5F 
#define HEARTRATE_PROG_TG_STC_CMD        0x000000
#define HEARTRATE_PROG_TG_ENDC_CMD       0x000000
#define HEARTRATE_LED3LEDSTC_CMD         0x000190
#define HEARTRATE_LED3LEDENDC_CMD        0x00031F
#define HEARTRATE_CLKDIV_PRF_CMD         0x000000
#define HEARTRATE_OFFDAC_CMD             0x000000
/** \} */

void heartrate_write_data ( uint8_t reg_adr, uint32_t wr_data );
uint32_t heartrate_read ( uint8_t reg_adr );
void heartrate_default_cfg (void);


