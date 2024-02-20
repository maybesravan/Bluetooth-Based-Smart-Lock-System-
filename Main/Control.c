//Control Function linked to main 

#include "Headder_files.h"


void INIT_OUTPUT_LED()
{
        SETBIT(IODIR1,27);                                              //SETTING THE OUTPUT_FUNCTION PIN AS 31^M
}
void INIT_ALL_FUNCTION()
{
      init_i2c();
			INIT_KEYPAD();                                                  //ENABLE THE KEYPAD_MATRIX^M
			INITLCD();	//ENABLE THE LCD^M
			Enable_EINT0(); 
			INIT_UART0();
			INIT_OUTPUT_LED();
}
void WRITEPASSWORDTOI2C()
{
	u8 data[5]="1234";
  i2c_eeprom_page_write(0x50,0x00,data,4);
  DELAY_S(1);
}

void TURNONLED()
{
        if(READBIT(IOPIN1,27)==1)
				{	
					CPLBIT(IOPIN1,27);
					STRLCD("LED IS OFF");
				}
				else
				{
					CPLBIT(IOPIN1,27);
					STRLCD("LED IS ON");
				}
}
void TURNONBEDLED()
{
	if(READBIT(IOPIN1,28)==1)
		{
			CPLBIT(IOPIN1,28);
			STRLCD("BEDLED IS OFF");
		}
	else
		{
			CPLBIT(IOPIN1,27);
			STRLCD("BEDLED IS ON");
		}
}
void READPASSWORD(char *p)
{
	i2c_eeprom_seq_read(0X50,0X00,p,4);
	p[4]='\0'; 
	CMDLCD(0x01);
	STRLCD("pass");
	STRLCD("10");
	DELAY_MS(1000);
}
void control(void)
{
	int i;
  CMDLCD(0x01);
	DELAY_MS(100);                         
	STRLCD("welcome");
	DELAY_MS(100);
	while(1)
		{
			u8 c[5];
			char dataread,RECHECK_TEST[5];
			CMDLCD(0x01);
			DELAY_MS(100);
			STRLCD("ENTER THE PASSWORD");
			DELAY_MS(200);
			CMDLCD(0xc0);
			for(i=0;i<4;i++)
			{
				c[i]=UART0_Rx_char();
			}
			c[4]='\0';  																						//check this once 
			DELAY_MS(1000);
			CMDLCD(0xc0);
			STRLCD(c);
			STRLCD("OK");
			READPASSWORD(RECHECK_TEST);
			STRLCD("READ PASSWORD");
			RECHECK_TEST[i]='\0';
			CMDLCD(0x38);
			STRLCD(RECHECK_TEST);
			DELAY_MS(3);
			if(strcmp(c,RECHECK_TEST)==0)																			//check this				
				{
					CMDLCD(0x01);
					STRLCD("password is correct");
					DELAY_MS(1000);
					CMDLCD(0x01);
					STRLCD("1.LED 2.BEDLED");
					DELAY_S(1);
					CMDLCD(0xc0);
					DELAY_MS(2000);
					dataread=UART0_Rx_char();
					switch(dataread)
					{
							case '1':
								TURNONLED();
								STRLCD("1 ON");
								DELAY_S(2);
								break;
							case '2':
								TURNONBEDLED();
								STRLCD("2 ON");
								DELAY_S(2);
								break;
							default:
								STRLCD("TRY AGAIN");
					}
				}
		}
}




