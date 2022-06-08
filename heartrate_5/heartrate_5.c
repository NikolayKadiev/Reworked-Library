#include "heartrate_5.h"


void heartrate5_default_cfg ( void ) 
{

//    heartrate5_hw_reset( ctx );
    
    heartrate5_write_reg( HEARTRATE5_REG0H, HEARTRATE5_REG0H_CMD );
    heartrate5_write_reg( HEARTRATE5_REG1H, HEARTRATE5_REG1H_CMD );
    heartrate5_write_reg( HEARTRATE5_REG2H, HEARTRATE5_REG2H_CMD );
    heartrate5_write_reg( HEARTRATE5_REG3H, HEARTRATE5_REG3H_CMD );
    heartrate5_write_reg( HEARTRATE5_REG4H, HEARTRATE5_REG4H_CMD );
    heartrate5_write_reg( HEARTRATE5_REG5H, HEARTRATE5_REG5H_CMD );
    heartrate5_write_reg( HEARTRATE5_REG6H, HEARTRATE5_REG6H_CMD );
    heartrate5_write_reg( HEARTRATE5_REG7H, HEARTRATE5_REG7H_CMD );
    heartrate5_write_reg( HEARTRATE5_REG8H, HEARTRATE5_REG8H_CMD );
    heartrate5_write_reg( HEARTRATE5_REG9H, HEARTRATE5_REG9H_CMD );
    heartrate5_write_reg( HEARTRATE5_REGAH, HEARTRATE5_REGAH_CMD );
    heartrate5_write_reg( HEARTRATE5_REGBH, HEARTRATE5_REGBH_CMD );
    heartrate5_write_reg( HEARTRATE5_REGCH, HEARTRATE5_REGCH_CMD );
    heartrate5_write_reg( HEARTRATE5_REGDH, HEARTRATE5_REGDH_CMD );
    heartrate5_write_reg( HEARTRATE5_REGEH, HEARTRATE5_REGEH_CMD );
    heartrate5_write_reg( HEARTRATE5_REGFH, HEARTRATE5_REGFH_CMD );
    heartrate5_write_reg( HEARTRATE5_REG10H, HEARTRATE5_REG10H_CMD );
    heartrate5_write_reg( HEARTRATE5_REG11H, HEARTRATE5_REG11H_CMD );
    heartrate5_write_reg( HEARTRATE5_REG12H, HEARTRATE5_REG12H_CMD );
    heartrate5_write_reg( HEARTRATE5_REG13H, HEARTRATE5_REG13H_CMD );
    heartrate5_write_reg( HEARTRATE5_REG14H, HEARTRATE5_REG14H_CMD );
    heartrate5_write_reg( HEARTRATE5_REG15H, HEARTRATE5_REG15H_CMD );
    heartrate5_write_reg( HEARTRATE5_REG16H, HEARTRATE5_REG16H_CMD );
    heartrate5_write_reg( HEARTRATE5_REG17H, HEARTRATE5_REG17H_CMD );
    heartrate5_write_reg( HEARTRATE5_REG18H, HEARTRATE5_REG18H_CMD );
    heartrate5_write_reg( HEARTRATE5_REG19H, HEARTRATE5_REG19H_CMD );
    heartrate5_write_reg( HEARTRATE5_REG1AH, HEARTRATE5_REG1AH_CMD );
    heartrate5_write_reg( HEARTRATE5_REG1BH, HEARTRATE5_REG1BH_CMD );
    heartrate5_write_reg( HEARTRATE5_REG1CH, HEARTRATE5_REG1CH_CMD );
    heartrate5_write_reg( HEARTRATE5_REG1DH, HEARTRATE5_REG1DH_CMD );
    heartrate5_write_reg( HEARTRATE5_REG1EH, HEARTRATE5_REG1EH_CMD ); 
    heartrate5_write_reg( HEARTRATE5_REG20H, HEARTRATE5_REG20H_CMD ); 
    heartrate5_write_reg( HEARTRATE5_REG21H, HEARTRATE5_REG21H_CMD ); 
    heartrate5_write_reg( HEARTRATE5_REG22H, HEARTRATE5_REG22H_CMD ); 
    heartrate5_write_reg( HEARTRATE5_REG23H, HEARTRATE5_REG23H_CMD ); 
    heartrate5_write_reg( HEARTRATE5_REG29H, HEARTRATE5_REG29H_CMD ); 
    heartrate5_write_reg( HEARTRATE5_REG31H, HEARTRATE5_REG31H_CMD ); 
    heartrate5_write_reg( HEARTRATE5_REG32H, HEARTRATE5_REG32H_CMD ); 
    heartrate5_write_reg( HEARTRATE5_REG33H, HEARTRATE5_REG33H_CMD ); 
    heartrate5_write_reg( HEARTRATE5_REG34H, HEARTRATE5_REG34H_CMD );
    heartrate5_write_reg( HEARTRATE5_REG35H, HEARTRATE5_REG35H_CMD ); 
    heartrate5_write_reg( HEARTRATE5_REG36H, HEARTRATE5_REG36H_CMD ); 
    heartrate5_write_reg( HEARTRATE5_REG37H, HEARTRATE5_REG37H_CMD ); 
    heartrate5_write_reg( HEARTRATE5_REG39H, HEARTRATE5_REG39H_CMD ); 
    heartrate5_write_reg( HEARTRATE5_REG3AH, HEARTRATE5_REG3AH_CMD );

}


void heartrate5_write_reg( uint8_t reg_addr, uint32_t write_data )
{
	i2c_cmd_handle_t cmd_comm;
	cmd_comm = i2c_cmd_link_create();
	i2c_master_start(cmd_comm);
	i2c_master_write_byte(cmd_comm, ( HEARTRATE_SLAVE_ADDR << 1 ) | I2C_MASTER_WRITE, 1);
	i2c_master_write_byte(cmd_comm, reg_addr , 1);
	i2c_master_write_byte(cmd_comm, (write_data >> 16), 1);
	i2c_master_write_byte(cmd_comm, (write_data >> 8) & 0xFF, 1);
	i2c_master_write_byte(cmd_comm, (write_data & 0xFF), 1);
	i2c_master_stop(cmd_comm);
	i2c_master_cmd_begin(I2C_NUM_1, cmd_comm, portMAX_DELAY);
	i2c_cmd_link_delete(cmd_comm);
}

uint32_t heartrate5_read_reg( uint8_t reg_addr )
{
	uint8_t data[3];
	i2c_cmd_handle_t cmd_read;
	cmd_read = i2c_cmd_link_create();
	i2c_master_start(cmd_read);
	i2c_master_write_byte(cmd_read, ( HEARTRATE_SLAVE_ADDR << 1 ) | I2C_MASTER_WRITE, 1);
	i2c_master_write_byte(cmd_read, reg_addr , 1);
	i2c_master_start(cmd_read);
	i2c_master_write_byte(cmd_read, ( HEARTRATE_SLAVE_ADDR << 1 ) | I2C_MASTER_READ, 1);
	i2c_master_read(cmd_read, data, 3, I2C_MASTER_LAST_NACK);
	i2c_master_stop(cmd_read);
	i2c_master_cmd_begin(I2C_NUM_1, cmd_read, portMAX_DELAY);
	i2c_cmd_link_delete(cmd_read);
	return (data[0]<<16) | (data[1]<<8) | data[2];
}


uint32_t heartrate5_get_led2_val( void )
{
    uint32_t reg_data;
    reg_data=heartrate5_read_reg( HEARTRATE5_REG2AH );
    return reg_data;
}

uint32_t heartrate5_get_aled2_val_led3_val( void )
{
    uint32_t reg_data;
    reg_data = heartrate5_read_reg( HEARTRATE5_REG2BH );
    return reg_data;
}

uint32_t heartrate5_get_led1_val( void )
{
    uint32_t reg_data;
    reg_data = heartrate5_read_reg( HEARTRATE5_REG2CH );
    return reg_data;
}

uint32_t heartrate5_get_aled1_val( void )
{
    uint32_t reg_data;
    reg_data = heartrate5_read_reg( HEARTRATE5_REG2DH );
    return reg_data;
}

uint32_t heartrate5_get_led2_aled2_val( void )
{
    uint32_t reg_data;
    reg_data = heartrate5_read_reg( HEARTRATE5_REG2EH );
    return reg_data;
}

uint32_t heartrate5_get_led1_aled1_val( void )
{
    uint32_t reg_data;
    reg_data = heartrate5_read_reg( HEARTRATE5_REG2FH );
    return reg_data;
}


