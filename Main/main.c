// BLUETOOTH_module .c file 
#include "Headder_files.h"

#define PASSWORD 1234

extern void control(void);
extern void WRITEPASSWORDTOI2C(void);
extern void INIT_ALL_FUNCTION(void);
int main()
{
	INIT_ALL_FUNCTION();
	WRITEPASSWORDTOI2C();
	control();
}

