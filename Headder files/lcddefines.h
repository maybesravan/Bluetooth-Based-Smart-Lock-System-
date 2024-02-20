// keypad _matrix_.H
#include"types.h"

#define         LCD_D0          8
#define         LCD_D1          9
#define         LCD_D2          10
#define         LCD_D3          11
#define         LCD_D4          12
#define         LCD_D5          13
#define         LCD_D6          14
#define         LCD_D7          15
#define         LCD_RS          17
#define         LCD_RW          16
#define         LCD_EN          18

//HD44780 COMMANDS
#define   CLEAR_LCD             0X01
#define   RET_CUR_HOME          0X02
#define   SHIFT_DISP_RIGHT      0X06
#define   SHIFT_DISP_LEFT   		0X07
#define   DIPS_OFF              0X08
#define   DSP_ON_CUR_OFF        0X0C
#define   DSP_ON_CUR_ON         0X0E
#define   DSP_ON_CUR_BLINK      0X0F


#define         MODE_8BIT_1LINE         0X30
#define         MODE_4BIT_1LINE         0X20
#define         MODE_8BIT_2LINE         0X38
#define         MODE_4BIT_2LINE         0X28


#define         GOTO_LINE1_pos0         0x80
#define         GOTO_LINE2_pos0         0xc0
#define         GOTO_LINE3_pos0         0x94
#define         GOTO_LINE4_pos0         0xD4

#define         GOTO_CGRAM_START        0x40
#define         SHIFT_CUR_LEFT          0x10
#define         SHIFT_CUR_RIGHT         0x14



void INITLCD(void);
void BUILDCGRAM(u8 *p,u32 nBytes);
void WRITELCD(unsigned char  dat);
void BINLCD(u32 n ,u32 nBD);
void CMDLCD(unsigned char  cmd);
void CHARLCD(u8 Dat);
void U32LCD(u32 n);
void STRLCD( unsigned char *p);
void S32LCD(s32 n);
void F32LCD(f32 n,u32 nDP);
void BINLCD(u32 n, u32 nBD);
void HEXLCD(u32 n);


