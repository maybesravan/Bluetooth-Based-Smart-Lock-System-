 /* i2c_eeprom.c */
 
 #include "Headder_files.h"

void init_i2c(void)
{
         //Configure I/O pin for SCL & SDA functions using PINSEL0
         PINSEL0|=SCL_EN|SDA_EN;
         //Configure Speed for I2C Serial Communication^M
         //Using I2CSCLL^M
         I2SCLL=LOADVAL;
				//& I2CSCLH
         I2SCLH=LOADVAL;
        //I2C Peripheral Enable for Communication^M
         I2CONSET=1<<I2EN_BIT; 
}       	
void i2c_start(void)
{
        // start condition
				I2CONSET=1<<STA_BIT;
				//wait for start bit status
        while(((I2CONSET>>SI_BIT)&1)==0);
        // clear start condition
        I2CONCLR=1<<STA_BIT;
}       
void i2c_restart(void)
{
        // start condition
        I2CONSET=1<<STA_BIT;
        //clr SI_BIT
        I2CONCLR=1<<SI_BIT;
        //wait for SI bit status
        while(((I2CONSET>>SI_BIT)&1)==0);
        // clear start condition
        I2CONCLR=1<<STA_BIT;
}       

void i2c_write(u8 dat)
{
        //put data into I2DAT
				I2DAT=dat;  
				//clr SI_BIT
        I2CONCLR = 1<<SI_BIT;
        //wait for SI bit status
        while(((I2CONSET>>SI_BIT)&1)==0);
}      
void i2c_stop(void)
{
        // issue stop condition
        I2CONSET=1<<STO_BIT;
				// clr SI bit status  
        I2CONCLR = 1<<SI_BIT;
        //stop will cleared automatically^
        //while(((I2CONSET>>STO_BIT)&1));
}
u8 i2c_nack(void)
{     
        I2CONSET = 0x00; //Assert Not of Ack
				I2CONCLR = 1<<SI_BIT;
        while(((I2CONSET>>SI_BIT)&1)==0);
        return I2DAT;

}

u8 i2c_masterack(void)
{       
        I2CONSET = 0x04; //Assert Ack
				I2CONCLR = 1<<SI_BIT;
        while(((I2CONSET>>SI_BIT)&1)==0);
        I2CONCLR = 0x04; //Clear Assert Ack
        return I2DAT;
}
void i2c_eeprom_write(u8 slaveAddr,u16 wBuffAddr,u8 dat)
{
  i2c_start();  
  i2c_write(slaveAddr<<1); 																										//slaveAddr + w^M
  i2c_write((wBuffAddr>>8)&0xFF);   																				 //wBuffAddr^M
  i2c_write((wBuffAddr&0xFF));
  i2c_write(dat);    																												//wBuffAddr^M
  i2c_stop();
	DELAY_MS(10);
}
u8 i2c_eeprom_read(u8 slaveAddr,u16 rBuffAddr)
{
        u8 dat;
        i2c_start();    
        i2c_write(slaveAddr<<1); //slaveAddr + w
        i2c_write((rBuffAddr>>8)&0xFF);    //rBuffAddr
        i2c_write((rBuffAddr&0xFF));
        i2c_restart();  
        i2c_write(slaveAddr<<1|1); //slaveAddr + r
        dat=i2c_nack(); 
        i2c_stop();
        return dat;
}
void i2c_eeprom_page_write( u8 slaveAddr,u16 wBuffStartAddr,u8 *p,u8 nBytes)
{
  u8 i;
  i2c_start();  
  i2c_write(slaveAddr<<1);    //slaveAddr + w
  i2c_write(wBuffStartAddr>>8);  //wBuffStartAddr
  i2c_write(wBuffStartAddr);
  for(i=0;i<nBytes;i++)
  {
           i2c_write(p[i]);             //wBuffAddr
  }
  i2c_stop();
  DELAY_MS(10);
}                        
void i2c_eeprom_seq_read(u8 slaveAddr,u16 rBuffStartAddr,u8 *p,u8 nBytes)
{
        u8 i;
        i2c_start();    
				i2c_write(slaveAddr<<1); //slaveAddr + w
        i2c_write(rBuffStartAddr>>8);    //rBuffAddr
        i2c_write(rBuffStartAddr);    //rBuffAddr
        i2c_restart();  
        i2c_write(slaveAddr<<1|1); //slaveAddr + r
        for(i=0;i<nBytes-1;i++)
        {
					p[i]=i2c_masterack();    
        }
        p[i]=i2c_nack();
        p[i+1]='\0';
        i2c_stop();
}
