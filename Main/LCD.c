//LCD code 


#include "Headder_files.h"

void INITLCD()
{
        //cfg direction for LCD DATA,RS,RW,EN AS OUTPUT PIN
        WRITEBYTE(IODIR0,LCD_D0,0XFF);
        SETBIT(IODIR0,LCD_RS);
        SETBIT(IODIR0,LCD_RW);
        SETBIT(IODIR0,LCD_EN);
        DELAY_MS(1);
        CMDLCD(MODE_8BIT_1LINE);
				//CMDLCD(0x07);
        DELAY_MS(1);
        CMDLCD(MODE_8BIT_1LINE);
        DELAY_MS(1);
        CMDLCD(MODE_8BIT_2LINE);
        CMDLCD(DSP_ON_CUR_BLINK);
        CMDLCD(CLEAR_LCD);
        CMDLCD(SHIFT_DISP_RIGHT);
}

void BUILDCGRAM(u8 *p,u32 nBytes)
{
        u32 i;
        //point to CGram
        CMDLCD(GOTO_CGRAM_START);
        for(i=0;i<nBytes;i++)
        {
                //write to cgRam area via data
                CHARLCD(p[i]);
        }
        //poiint to back to DDram
        CMDLCD(GOTO_LINE1_pos0);
}




void WRITELCD(unsigned char  dat)
{
        //cfg for waiting to LCD
        SSETBIT(IOCLR0,LCD_RW);
        //WRITE TO DATA PINS ANY BUYTE
        WRITEBYTE(IOPIN0,LCD_D0,dat);
        //MAKE ENABLE PIN HIGH
        SSETBIT(IOSET0,LCD_EN);
        DELAY_US(1);
        SSETBIT(IOCLR0,LCD_EN);
        //almost 2ms consecutive writes for sync b/w cpu & lcd
        DELAY_MS(2);
}
void CMDLCD(unsigned char  cmd)
{
        //setlect command  register foe writing to      0
        SSETBIT(IOCLR0,LCD_RS);
        //WRITE TO COMMAND REGISTER
        WRITELCD(cmd);
}
void CHARLCD(u8 Dat)
{
        //select data register for the writing t
        SSETBIT(IOSET0,LCD_RS);
        //WRITE THE DATA REGISTER THEN TO DDRAM OR CGRAM FOR THE DISPLAY /BUILD CGRAM
        WRITELCD(Dat);
}

 void U32LCD(u32 n)
{
        u8 a[10];
        s32 i=0;
        if(n==0)
        {
                CHARLCD('0');
        }
        else
        {
                while(n)
                {
                        a[i++]=(n%10)+48;
                        n/=10;
                }
                for(--i;i>=0;i--)
                        CHARLCD(a[i]);
        }
}

void STRLCD( unsigned char *p)
{
        while(*p)
                CHARLCD(*p++);
}

void S32LCD(s32 n)
{
        if(n<0)
        {
                CHARLCD(' ');
                n=-n;
        }
        U32LCD(n);
}

void F32LCD(f32 n,u32 nDP)
{
        s32 t,i;
        if(n<0.0)
        {
                n=-n;
                CHARLCD(' ' );
        }
        t=n;
        U32LCD(t);
        CHARLCD(' ');
        for(i=0;i<nDP;i++)
        {
                n=(n-t)*10;
                t=n;
                CHARLCD(t+48);
        }
}

void BINLCD(u32 n ,u32 nBD)
{
        s32 i;
        for(i=(nBD-1);i>=0;i--)
                CHARLCD(((n>>i)&1)+48);

}
void HexLCD(u32 n)
{
        u8 a[8];
        s32 i=0;
        if(n==0)
                STRLCD("00000000");
        else
        {
                while(n)
                {
                        a[i++]=48;
                        n/=16;
                }
                for(--i;i>=0;i--)
                {
                        CHARLCD(a[i]);
                }
        }
}



