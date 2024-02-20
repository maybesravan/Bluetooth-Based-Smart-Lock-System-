// keypadmatrix_H header files 


#ifndef _KEYPAD_H_
#define _KEYPAD_H_

#include"types.h"

#define ROW0 16
#define ROW1 17
#define ROW2 18
#define ROW3 19
#define COL0 20
#define COL1 21
#define COL2 22
#define COL3 23
void INIT_KEYPAD(void);
u8 ROWSCAN(void);
u8 COLSCAN(void);
u8 COLCHECK(void);
u8 KEYPRESSED(void);
#endif

