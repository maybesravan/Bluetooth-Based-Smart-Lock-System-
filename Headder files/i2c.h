                         /* i3c_defines.h */
#include "types.h"


void init_i2c(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_restart(void);
void i2c_write(u8);
u8  i2c_read(void);
u8 i2c_ack(void);
u8 i2c_nack(void);
u8 i2c_masterack(void);
void i2c_eeprom_write(u8,u16,u8);
u8   i2c_eeprom_read(u8,u16);
void i2c_eeprom_page_write(u8 slaveAddr,u16 wBuffStartAddr,u8 *p,u8 nBytes);
void i2c_eeprom_seq_read(u8 slaveAddr,u16 rBuffStartAddr,u8 *p,u8 nBytes);
//defines for pin function selection
#define SCL_EN  0x00000010
#define SDA_EN  0x00000040
//defines for I2C_SPEED Configuration 
#define CCLK      60000000  //Hz
#define PCLK      CCLK/4    //Hz
#define I2C_SPEED 100000    //Hz
#define LOADVAL   ((PCLK/I2C_SPEED)/2)
//bit defines for I2CONSET sfr
#define   AA_BIT 2
#define   SI_BIT 3
#define  STO_BIT 4
#define  STA_BIT 5
#define I2EN_BIT 6





