#include "heartrate_7.h"

/**
 * @brief Write data function
 *
 * @param reg_adr  8-bit data that defines register's address
 * @param wr_data  32-bit used defined data to be written into register
 *
 * @description Function is used to write 32-bit data into register.
**/
void heartrate_write_data ( uint8_t reg_adr, uint32_t wr_data ){
	i2c_cmd_handle_t cmd_comm;
	cmd_comm = i2c_cmd_link_create();
	i2c_master_start(cmd_comm);
	i2c_master_write_byte(cmd_comm, ( HEARTRATE_SLAVE_ADDR << 1 ) | I2C_MASTER_WRITE, 1);
	i2c_master_write_byte(cmd_comm, reg_adr , 1);
	i2c_master_write_byte(cmd_comm, (wr_data >> 16), 1);
	i2c_master_write_byte(cmd_comm, (wr_data >> 8) & 0xFF, 1);
	i2c_master_write_byte(cmd_comm, (wr_data & 0xFF), 1);
	i2c_master_stop(cmd_comm);
	i2c_master_cmd_begin(I2C_NUM_1, cmd_comm, portMAX_DELAY);
	i2c_cmd_link_delete(cmd_comm);
}

/**
 * @brief Click Default Configuration function.
 *
 *
 * @description This function executes default configuration for 
 * HEARTRATE click.
 */
void heartrate_default_cfg (void){
    // Click default configuration
    heartrate_write_data( HEARTRATE_CONTROL0, HEARTRATE_CONTROL0_CMD );
    heartrate_write_data( HEARTRATE_LED2STC,   HEARTRATE_LED2STC_CMD );
    heartrate_write_data( HEARTRATE_LED2ENDC,  HEARTRATE_LED2ENDC_CMD );
    heartrate_write_data( HEARTRATE_LED1LEDSTC,  HEARTRATE_LED1LEDSTC_CMD );
    heartrate_write_data( HEARTRATE_LED1LEDENDC,  HEARTRATE_LED1LEDENDC_CMD );
    heartrate_write_data( HEARTRATE_ALED2STC,   HEARTRATE_ALED2STC_CMD );
    heartrate_write_data( HEARTRATE_ALED2ENDC, HEARTRATE_ALED2ENDC_CMD );
    heartrate_write_data( HEARTRATE_LED1STC, HEARTRATE_LED1STC_CMD );
    heartrate_write_data( HEARTRATE_LED1ENDC,  HEARTRATE_LED1ENDC_CMD );
    heartrate_write_data( HEARTRATE_LED2LEDSTC,  HEARTRATE_LED2LEDSTC_CMD );

    heartrate_write_data( HEARTRATE_LED2LEDENDC,  HEARTRATE_LED2LEDENDC_CMD );
    heartrate_write_data( HEARTRATE_ALED1STC,   HEARTRATE_ALED1STC_CMD );
    heartrate_write_data( HEARTRATE_ALED1ENDC, HEARTRATE_ALED1ENDC_CMD );
    heartrate_write_data( HEARTRATE_LED2CONVST, HEARTRATE_LED2CONVST_CMD );
    heartrate_write_data( HEARTRATE_LED2CONVEND, HEARTRATE_LED2CONVEND_CMD );
    heartrate_write_data( HEARTRATE_ALED2CONVST, HEARTRATE_ALED2CONVST_CMD );
    heartrate_write_data( HEARTRATE_ALED2CONVEND,  HEARTRATE_ALED2CONVEND_CMD );
    heartrate_write_data( HEARTRATE_LED1CONVST,  HEARTRATE_LED1CONVST_CMD );
    heartrate_write_data( HEARTRATE_LED1CONVEND,  HEARTRATE_LED1CONVEND_CMD );
    heartrate_write_data( HEARTRATE_ALED1CONVST,  HEARTRATE_ALED1CONVST_CMD );

    heartrate_write_data( HEARTRATE_ALED1CONVEND,  HEARTRATE_ALED1CONVEND_CMD );
    heartrate_write_data( HEARTRATE_ADCRSTSTCT0,  HEARTRATE_ADCRSTSTCT0_CMD );
    heartrate_write_data( HEARTRATE_ADCRSTENDCT0, HEARTRATE_ADCRSTENDCT0_CMD );
    heartrate_write_data( HEARTRATE_ADCRSTSTCT1, HEARTRATE_ADCRSTSTCT1_CMD );
    heartrate_write_data( HEARTRATE_ADCRSTENDCT1,  HEARTRATE_ADCRSTENDCT1_CMD );
    heartrate_write_data( HEARTRATE_ADCRSTSTCT2, HEARTRATE_ADCRSTSTCT2_CMD );
    heartrate_write_data( HEARTRATE_ADCRSTENDCT2,  HEARTRATE_ADCRSTENDCT2_CMD );
    heartrate_write_data( HEARTRATE_ADCRSTSTCT3,  HEARTRATE_ADCRSTSTCT3_CMD );
    heartrate_write_data( HEARTRATE_ADCRSTENDCT3, HEARTRATE_ADCRSTENDCT3_CMD );
    heartrate_write_data( HEARTRATE_PRPCOUNT,  HEARTRATE_PRPCOUNT_CMD );

    heartrate_write_data( HEARTRATE_CONTROL1,  HEARTRATE_CONTROL1_CMD );
    heartrate_write_data( HEARTRATE_TIA_GAIN_SEP, HEARTRATE_TIA_GAIN_SEP_CMD );
    heartrate_write_data( HEARTRATE_TIA_GAIN, HEARTRATE_TIA_GAIN_CMD );
    heartrate_write_data( HEARTRATE_LEDCNTRL, HEARTRATE_LEDCNTRL_CMD );
    heartrate_write_data( HEARTRATE_CONTROL2,  HEARTRATE_CONTROL2_CMD );
    heartrate_write_data( HEARTRATE_ALARM,  HEARTRATE_ALARM_CMD );
    heartrate_write_data( HEARTRATE_CONTROL3,  HEARTRATE_CONTROL3_CMD );
    heartrate_write_data( HEARTRATE_PDNCYCLESTC,  HEARTRATE_PDNCYCLESTC_CMD  );
    heartrate_write_data( HEARTRATE_PDNCYCLEENDC,  HEARTRATE_PDNCYCLEENDC_CMD );
    heartrate_write_data( HEARTRATE_PROG_TG_STC,  HEARTRATE_PROG_TG_STC_CMD  );

    heartrate_write_data( HEARTRATE_PROG_TG_ENDC,  HEARTRATE_PROG_TG_ENDC_CMD );
    heartrate_write_data( HEARTRATE_LED3LEDSTC,  HEARTRATE_LED3LEDSTC_CMD );
    heartrate_write_data( HEARTRATE_LED3LEDENDC,  HEARTRATE_LED3LEDENDC_CMD );
    heartrate_write_data( HEARTRATE_CLKDIV_PRF,  HEARTRATE_CLKDIV_PRF_CMD );
    heartrate_write_data( HEARTRATE_OFFDAC,    HEARTRATE_OFFDAC_CMD );
}

/**
 * @brief Read  data function
 *
 * @param reg_adr  8-bit data that defines register's address
 *
 * @returns value read from chosen register
 *
 * @description Function is used to read value from register.
**/
uint32_t heartrate_read ( uint8_t reg_adr )
{
	uint8_t data[3];
	i2c_cmd_handle_t cmd_read;
	cmd_read = i2c_cmd_link_create();
	i2c_master_start(cmd_read);
	i2c_master_write_byte(cmd_read, ( HEARTRATE_SLAVE_ADDR << 1 ) | I2C_MASTER_WRITE, 1);
	i2c_master_write_byte(cmd_read, reg_adr , 1);
	i2c_master_start(cmd_read);
	i2c_master_write_byte(cmd_read, ( HEARTRATE_SLAVE_ADDR << 1 ) | I2C_MASTER_READ, 1);
	i2c_master_read(cmd_read, data, 3, I2C_MASTER_LAST_NACK);
	i2c_master_stop(cmd_read);
	i2c_master_cmd_begin(I2C_NUM_1, cmd_read, portMAX_DELAY);
	i2c_cmd_link_delete(cmd_read);
	//return (0x1FFFF - (((data[0]<<16) + (data[1]<<8) + data[2]) & 0x1FFFF)) >> 1;
	return ((data[0]<<16) | (data[1]<<8) | data[2]);

}

