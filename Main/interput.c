#include <lpc21xx.h>
#include "interrupt.h"
#include "defines.h"
#include "lcddefines.h"
#include "i2c.h"
#include "keypad.h"
#include <string.h>
#include "delay.h"

#define FUNC1 0
#define FUNC2 1
#define FUNC3 2
#define FUNC4 3
#define CFGPIN(WORD,PIN,FUNC)  WORD=((PIN<16)?((WORD&~(3<<(PIN*2)))|(FUNC<<(PIN*2))):((WORD&~(3<<((PIN-16)*2)))|(FUNC<<((PIN-16)*2))));
void eint0_isr(void) __irq;
void Enable_EINT0(void);
unsigned int count;
void READPASSWORD1(char *p)
{
	char readpassword[5];                                //,check;
	i2c_eeprom_seq_read(0X50,0X00,readpassword,4);
	readpassword[4]='\0';
	CMDLCD(0x01);
	STRLCD("pass");
	//DELAY_MS(100);
	CMDLCD(0xc0);
	STRLCD(readpassword);
	DELAY_MS(100);
	strcpy(p,readpassword);
}
void eint0_isr(void) __irq
{
	// CPLBIT(IOPIN1,EINT0_LED);                                                     //isr activity	
	int i=0;	
	char newpassword[5],reenter_password[5];
	u8 oldpassword[5],readpass[5];            	
	READPASSWORD1(readpass);
retry:
	CMDLCD(0x01);
	STRLCD("OLD PASSWORD");
	DELAY_MS(100);
	CMDLCD(0x38);
	CMDLCD(0x38);
	i=0;
	while(i!=4)
	{
		oldpassword[i]=KEYPRESSED();
		if(oldpassword[i]==10)
		{
			--i;
			DELAY_MS(100);
			CMDLCD(0x10);
			//CMDLCD(0x10);
		}
		else if(oldpassword[i]==8)
		{
			oldpassword[i]='\0';
			STRLCD("00");
			DELAY_MS(1000);
			break;
		}
		else
		{
		CHARLCD(oldpassword[i]);
			i++;
		}
		DELAY_MS(300);
	}
	oldpassword[4]='\0';
	//STRLCD("OLD PASSWORD");
		CMDLCD(0x01);
	//CMDLCD(0x38);
	DELAY_MS(500);
	STRLCD(oldpassword);
	if(strcmp(readpass,oldpassword)==0)
		{
			CMDLCD(0x01);
			STRLCD("22");
			DELAY_S(1);
			CMDLCD(0x01);
			STRLCD("NEW PASSWORD");
			DELAY_MS(1000);
			CMDLCD(0x01);
			for(i=0;i<4;i++)
			{
				newpassword[i]=KEYPRESSED();
				DELAY_MS(300);
				CHARLCD(newpassword[i]);
			}
			CMDLCD(0xc0);
			newpassword[4]='\0';
			CMDLCD(0x01);
			STRLCD("REENTER");
			CMDLCD(0xc0);
			for(i=0;i<4;i++)
			{
				reenter_password[i]=KEYPRESSED();
				DELAY_MS(300);
				CHARLCD(reenter_password[i]);
			}
			reenter_password[4]='\0';
			if(strcmp(newpassword,reenter_password)==0)
				{
					i2c_eeprom_page_write(0x50,0x00,newpassword,4);                                                                          // write the passwrord in the EEEprom
					CMDLCD(0X01);
					STRLCD("SUCESS FULL");                                                                                                          //sending the "ok" to lcd
					DELAY_S(2);
				}
				else
					{
						STRLCD("fail write");
					}
		}
		else
			{
				STRLCD("RETRY");
				CMDLCD(0xc0);
				goto retry;
			}
			SCLRBIT(EXTINT,3);                                                      //clear flag
			VICVectAddr=0;                                                          //dummy write;
}
void Enable_EINT0(void)
{

        CFGPIN(PINSEL1,20,FUNC4);                                                                                                                                                       //to enable the pin 20 //ext 3
        //SETBIT(IODIR1,EINT0_LED);                                                                                                                                                      //to turn on the led ^M
        SSETBIT(VICIntEnable,17);                                                                                                                                                                       // to enable the ext3 17^M
        VICVectCntl0=0x20|17;                                             // 1<<5|17
        VICVectAddr0=(unsigned)eint0_isr;                                 //EINT0 as EDGE_TRIG^M
        SETBIT(EXTMODE,0);
        //SETBIT(EXTPOLAR,3);
}

