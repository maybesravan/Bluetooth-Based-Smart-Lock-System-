//Keypad.c file 


#include "Headder_files.h"


//scancodes for the keypad rows check
u8 scancodes[4]={14,13,11,7};

//the keypad values for the dispaly
u8 KEYPAD_MATRIX_VALUES[4][4]=
{'7','8','9','/','4','5','6','*','1','2','3','-',8,'0',10,'+'};

void INIT_KEYPAD(void)
{
        IODIR1|=0xf<<16;
}

u8 ROWSCAN(void)
{
        u32 row;

        //read the values of the rows
        for(row=0;row<=3;row++)
        {
                //check for the row pressed key
                // to that we need to write the ROws values
                WRITENIBBLE(IOPIN1,ROW0,scancodes[row]);
                if(!COLSCAN())
                {
                        break;
                }
        }

        //now we need to rewrite the row to the original status
        WRITENIBBLE(IOPIN1,ROW0,0);

        //return the row number is pressed
        return row;
}

u8 COLSCAN(void)
{
        //check for the kepressed inthe column
        //and also to return the value of the coloumn
        return READNIBBLE(IOPIN1,COL0)<15?0:1;

}
u8 COLCHECK(void)
{
        u32 col;
        //read the values of the rows
        for(col=0;col<=3;col++)
        {
                //check for the col pressed
                if(READNIBBLE(IOPIN1,COL0)==scancodes[col])
                {
                        break;
                }
        }
        return col;
}
u8 KEYPRESSED(void)
{
        u8 RNO,CNO,keyV;
				while(COLSCAN());
        RNO=ROWSCAN();
        CNO=COLCHECK();
        keyV= KEYPAD_MATRIX_VALUES[RNO][CNO];
        return keyV;
}




