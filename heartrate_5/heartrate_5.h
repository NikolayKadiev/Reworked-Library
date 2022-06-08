#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c.h"

/**
 * @brief Heart Rate 5 device address setting.
 * @details Specified setting for device slave address selection of
 * Heart Rate 5 Click driver.
 */
#define HEARTRATE_SLAVE_ADDR  0x58

/**
 * @brief Heart Rate 5 Timing control registers.
 * @details Specified register for description of timing control of Heart Rate 5 Click driver.
 */
#define HEARTRATE5_REG0H                       0x00
#define HEARTRATE5_REG1H                       0x01
#define HEARTRATE5_REG2H                       0x02
#define HEARTRATE5_REG3H                       0x03
#define HEARTRATE5_REG4H                       0x04
#define HEARTRATE5_REG5H                       0x05
#define HEARTRATE5_REG6H                       0x06
#define HEARTRATE5_REG7H                       0x07
#define HEARTRATE5_REG8H                       0x08
#define HEARTRATE5_REG9H                       0x09
#define HEARTRATE5_REGAH                       0x0A
#define HEARTRATE5_REGBH                       0x0B
#define HEARTRATE5_REGCH                       0x0C
#define HEARTRATE5_REGDH                       0x0D
#define HEARTRATE5_REGEH                       0x0E
#define HEARTRATE5_REGFH                       0x0F
#define HEARTRATE5_REG10H                      0x10
#define HEARTRATE5_REG11H                      0x11
#define HEARTRATE5_REG12H                      0x12
#define HEARTRATE5_REG13H                      0x13
#define HEARTRATE5_REG14H                      0x14
#define HEARTRATE5_REG15H                      0x15
#define HEARTRATE5_REG16H                      0x16
#define HEARTRATE5_REG17H                      0x17
#define HEARTRATE5_REG18H                      0x18
#define HEARTRATE5_REG19H                      0x19
#define HEARTRATE5_REG1AH                      0x1A
#define HEARTRATE5_REG1BH                      0x1B
#define HEARTRATE5_REG1CH                      0x1C
#define HEARTRATE5_REG1DH                      0x1D
#define HEARTRATE5_REG1EH                      0x1E
#define HEARTRATE5_REG20H                      0x20
#define HEARTRATE5_REG21H                      0x21
#define HEARTRATE5_REG22H                      0x22
#define HEARTRATE5_REG23H                      0x23
#define HEARTRATE5_REG29H                      0x29
#define HEARTRATE5_REG2AH                      0x2A
#define HEARTRATE5_REG2BH                      0x2B
#define HEARTRATE5_REG2CH                      0x2C
#define HEARTRATE5_REG2DH                      0x2D
#define HEARTRATE5_REG2EH                      0x2E
#define HEARTRATE5_REG2FH                      0x2F
#define HEARTRATE5_REG31H                      0x31
#define HEARTRATE5_REG32H                      0x32
#define HEARTRATE5_REG33H                      0x33
#define HEARTRATE5_REG34H                      0x34
#define HEARTRATE5_REG35H                      0x35
#define HEARTRATE5_REG36H                      0x36
#define HEARTRATE5_REG37H                      0x37
#define HEARTRATE5_REG39H                      0x39
#define HEARTRATE5_REG3AH                      0x3A
#define HEARTRATE5_REG3DH                      0x3D
#define HEARTRATE5_REG3FH                      0x3F
#define HEARTRATE5_REG40H                      0x40




#define  HEARTRATE5_REG0H_CMD                      0x000000 
#define  HEARTRATE5_REG1H_CMD                      0x000050 
#define  HEARTRATE5_REG2H_CMD                      0x00018F 
#define  HEARTRATE5_REG3H_CMD                      0x000320 
#define  HEARTRATE5_REG4H_CMD                      0x0004AF 
#define  HEARTRATE5_REG5H_CMD                      0x0001E0 
#define  HEARTRATE5_REG6H_CMD                      0x00031F 
#define  HEARTRATE5_REG7H_CMD                      0x000370 
#define  HEARTRATE5_REG8H_CMD                      0x0004AF 
#define  HEARTRATE5_REG9H_CMD                      0x000000 
#define  HEARTRATE5_REGAH_CMD                      0x00018F 
#define  HEARTRATE5_REGBH_CMD                      0x0004FF 
#define  HEARTRATE5_REGCH_CMD                      0x00063E 
#define  HEARTRATE5_REGDH_CMD                      0x000198 
#define  HEARTRATE5_REGEH_CMD                      0x0005BB 
#define  HEARTRATE5_REGFH_CMD                      0x0005C4 
#define  HEARTRATE5_REG10H_CMD                     0x0009E7 
#define  HEARTRATE5_REG11H_CMD                     0x0009F0 
#define  HEARTRATE5_REG12H_CMD                     0x000E13 
#define  HEARTRATE5_REG13H_CMD                     0x000E1C 
#define  HEARTRATE5_REG14H_CMD                     0x00123F 
#define  HEARTRATE5_REG15H_CMD                     0x000191 
#define  HEARTRATE5_REG16H_CMD                     0x000197 
#define  HEARTRATE5_REG17H_CMD                     0x0005BD 
#define  HEARTRATE5_REG18H_CMD                     0x0005C3 
#define  HEARTRATE5_REG19H_CMD                     0x0009E9 
#define  HEARTRATE5_REG1AH_CMD                     0x0009EF 
#define  HEARTRATE5_REG1BH_CMD                     0x000E15 
#define  HEARTRATE5_REG1CH_CMD                     0x000E1B 
#define  HEARTRATE5_REG1DH_CMD                     0x003E7F
#define  HEARTRATE5_REG1EH_CMD                     0x000103  
#define  HEARTRATE5_REG20H_CMD                     0x008003  
#define  HEARTRATE5_REG21H_CMD                     0x000013
#define  HEARTRATE5_REG22H_CMD                     0x01B6D9
#define  HEARTRATE5_REG23H_CMD                     0x104218  
#define  HEARTRATE5_REG29H_CMD                     0x000000  
#define  HEARTRATE5_REG31H_CMD                     0x000000  
#define  HEARTRATE5_REG32H_CMD                     0x00155F  
#define  HEARTRATE5_REG33H_CMD                     0x003B5F  
#define  HEARTRATE5_REG34H_CMD                     0x000000 
#define  HEARTRATE5_REG35H_CMD                     0x00000f
#define  HEARTRATE5_REG36H_CMD                     0x000190  
#define  HEARTRATE5_REG37H_CMD                     0x00031F  
#define  HEARTRATE5_REG39H_CMD                     0x000000  
#define  HEARTRATE5_REG3AH_CMD                     0x000000 
/**
 * @brief Heart Rate 5 default configuration function.
 * @details This function executes a default configuration of Heart Rate 5
 * click board.
 * @param[in] ctx : Click context object.
 * See #heartrate5_t object definition for detailed explanation.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void heartrate5_default_cfg ( void );

/**
 * @brief Heart Rate 5 register write function.
 * @details This function writes a 24-bit data into
 * the selected register by using I2C serial interface.
 * See #heartrate5_t object definition for detailed explanation.
 * @param[in] reg_addr : Start register address.
 * @param[in] write_data : Data to be written.
 * @return Nothing.
 */
void heartrate5_write_reg( uint8_t reg_addr, uint32_t write_data ); 

/**
 * @brief Heart Rate 5 register reading function.
 * @details This function reads a 24-bit data from
 * the selected register by using I2C serial interface.
 * See #heartrate5_t object definition for detailed explanation.
 * @param[in] reg_addr : Start register address.
 * @return 24-bit read data.
 */
uint32_t heartrate5_read_reg( uint8_t reg_addr ); 

/**
 * @brief Heart Rate 5 get LED2 data function.
 * @details This function is used to read conversion data from the LED2.
 * See #heartrate5_t object definition for detailed explanation.
 * @return Returns the value of the conversion resoult.
 */
uint32_t heartrate5_get_led2_val( void );

/**
 * @brief Heart Rate 5 get ALED2 data function.
 * @details This function is used to read conversion data from the ALED2.
 * See #heartrate5_t object definition for detailed explanation.
 * @return Returns the value of the conversion resoult.
 */
uint32_t heartrate5_get_aled2_val_led3v_al( void );

/**
 * @brief Heart Rate 5 get LED1 data function.
 * @details This function is used to read conversion data from the LED1.
 * See #heartrate5_t object definition for detailed explanation.
 * @return Returns the value of the conversion resoult.
 */
uint32_t heartrate5_get_led1_val( void );

/**
 * @brief Heart Rate 5 get ALED1 data function.
 * @details This function is used to read conversion data from the ALED1.
 * See #heartrate5_t object definition for detailed explanation.
 * @return Returns the value of the conversion resoult.
 */
uint32_t heartrate5_get_aled1_val( void );

/**
 * @brief Heart Rate 5 get LED2_ALED2 data function.
 * @details This function is used to read conversion data from the LED2_ALED2.
 * See #heartrate5_t object definition for detailed explanation.
 * @return Returns the value of the conversion resoult.
 */
uint32_t heartrate5_get_led2_aled2_val( void );

/**
 * @brief Heart Rate 5 get LED1_ALED1 data function.
 * @details This function is used to read conversion data from the LED1_ALED1.
 * See #heartrate5_t object definition for detailed explanation.
 * @return Returns the value of the conversion resoult.
 */
uint32_t heartrate5_get_led1_aled1_val( void );



