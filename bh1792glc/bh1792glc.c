
#include "bh1792glc.h"


/**
 * @brief Generic Single Byte Write function
 *
 * @param reg_addr  Address where data be written
 * @param data_in  Data to be written
 *
 *
 * @description Function writes one byte to the register.
 */
void BH1792GLC_write_single_byte (uint8_t reg_addr, uint8_t data_in ){
    i2c_cmd_handle_t cmd_comm;
    cmd_comm = i2c_cmd_link_create();
    i2c_master_start(cmd_comm);
   	i2c_master_write_byte(cmd_comm, ( BH1792GLC_SLAVE_ADDR  << 1 ) | I2C_MASTER_WRITE, 1);
   	i2c_master_write_byte(cmd_comm, reg_addr, 1);
   	i2c_master_write_byte(cmd_comm, data_in, 1);
   	i2c_master_stop(cmd_comm);
   	i2c_master_cmd_begin(I2C_NUM_1, cmd_comm, portMAX_DELAY);
   	i2c_cmd_link_delete(cmd_comm);

}

/**
 * @brief Generic Read function
 *
 * @param start_addr  Address from which data reading be started
 * @param data_out  Memory where read data be stored
 * @param n_bytes  Number of bytes to be read
 *
 * @returns 0 - OK, != 0 - one byte data
 *
 * @description Function reads the desired number of bytes from the registers.
 */
uint16_t BH1792GLC_read_bytes ( uint8_t start_addr, uint8_t *data_out, uint8_t n_bytes ){
    uint8_t data[5];
    i2c_cmd_handle_t cmd_read;
    cmd_read = i2c_cmd_link_create();
    i2c_master_start(cmd_read);
    i2c_master_write_byte(cmd_read, ( BH1792GLC_SLAVE_ADDR  << 1 ) | I2C_MASTER_WRITE, 1);
    i2c_master_write_byte(cmd_read, start_addr , 1);
    i2c_master_start(cmd_read);
    i2c_master_write_byte(cmd_read, ( BH1792GLC_SLAVE_ADDR  << 1 ) | I2C_MASTER_READ, 1);
    i2c_master_read(cmd_read, data, n_bytes, I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd_read);
    i2c_master_cmd_begin(I2C_NUM_1, cmd_read, portMAX_DELAY);
    i2c_cmd_link_delete(cmd_read);

    if(n_bytes == 1){
    	return data[0];
    }

    else{
    	*data_out = data[0];
    	*(data_out+1) = data[1];
    	*(data_out+2) = data[2];
    	*(data_out+3) = data[3];
    	return 0;
    }
}

/**
 * @brief Measurement Start function
 *
 * @description Function starts one measurement cycle.
 */
void BH1792GLC_start_measure ( void ){
    BH1792GLC_write_single_byte(BH1792GLC_MEAS_START_REG, BH1792GLC_MEAS_START_CMD );
}

/**
 * @brief Reset function
 *
 * @description Function performs the device reset.
 * @note The device reset must be performed when configurations are changed.
 */
void BH1792GLC_reset ( void ){
    BH1792GLC_write_single_byte( BH1792GLC_RESET_REG, BH1792GLC_RESET_CMD );
    //vTaskDelay(10 / portTICK_PERIOD_MS);
}

/**
 * @brief Measurement Synchronization function
 *
 * @description Function performs the measurement synchronization.
 * @note In Synchronized Measurement Mode adjust LED emitting frequency and output data rate by synchronizing
 *       with MEAS_SYNC received interval. After receiving MEAS_SYNC, the measurements for a set number of times are performed.
 */
void BH1792GLC_meas_sync ( void ){
    BH1792GLC_write_single_byte( BH1792GLC_MEAS_SYNC_REG, BH1792GLC_MEAS_SYNC_CMD );
}

/**
 * @brief Interrupt Clear function
 *
 * @returns Byte from the INT_CLEAR register.
 *
 * @description Function clears interrupt flag on the INT pin.
 */
uint8_t BH1792GLC_int_clear ( void ){
    uint8_t int_byte;
    return BH1792GLC_read_bytes( BH1792GLC_INT_CLEAR_REG, &int_byte, 1 );
}


/**
 * @brief Click Default Configuration function.
 *
 *
 * @description This function executes default configuration for BH1792GLC click.
 */
void BH1792GLC_default_cfg ( void ){
    BH1792GLC_reset();
    BH1792GLC_write_single_byte( BH1792GLC_MEAS_CTRL1_REG, BH1792GLC_OSC_ACTIVE | BH1792GLC_GREEN_MEAS_MODE | BH1792GLC_SINGLE_MEAS_MODE );
    BH1792GLC_write_single_byte( BH1792GLC_MEAS_CTRL2_REG, BH1792GLC_LEDS_PULSED  | BH1792GLC_LED_CURR_CUSTOM);
    BH1792GLC_write_single_byte( BH1792GLC_MEAS_CTRL3_REG, BH1792GLC_LED3_OFF | BH1792GLC_LED_CURR_10MA );
    BH1792GLC_write_single_byte( BH1792GLC_MEAS_CTRL5_REG, BH1792GLC_INT_MEAS_COMPLET );
}

/**
 * @brief Data Get function
 *
 * @param data_select  Determines which data registers be read (0 - FIFO, 1 - IR, 2 - GREEN Data)
 * @param led_out_on  Memory where LED ON Data be stored
 * @param led_out_off  Memory where LED OFF Data be stored
 *
 * @returns data
 *
 * @description Function gets the selected data from the determined LED Data registers.
 */
uint16_t BH1792GLC_get_data ( uint8_t data_select){
    uint8_t temp_data[ 4 ];
    uint8_t register_addr;
    uint16_t l_on =0, l_off = 0;

    switch ( data_select )
    {
        case BH1792GLC_FIFO_DATA_GET :
        {
            register_addr = BH1792GLC_FIFO_DATA0_LSB_REG;
        break;
        }
        case BH1792GLC_IR_DATA_GET :
        {
            register_addr = BH1792GLC_IRDATA_LEDOFF_LSB_REG;
        break;
        }
        case BH1792GLC_GREEN_DATA_GET :
        {
            register_addr = BH1792GLC_GDATA_LEDOFF_LSB_REG;
        break;
        }
        default:
        	register_addr = BH1792GLC_GDATA_LEDOFF_LSB_REG;
        	break;

    }

    BH1792GLC_read_bytes( register_addr, temp_data, 4 );

    l_off = (temp_data[ 1 ] << 8) | temp_data[ 0 ];
    l_on = (temp_data[ 3 ] << 8) | temp_data[ 2 ];
    return l_off - l_on;
}
