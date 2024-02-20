#include<lpc21xx.h>
#include"delay.h"
#include"types.h"

void DELAY_US(u32 dlyus)
{
dlyus*=12; //@cclk=60mhz ~1us
while(dlyus--);
}
void DELAY_MS(u32 dlyms)
{
dlyms*=12000;//@cclk=60hz ~1ms

while(dlyms--);
}
void DELAY_S(u32 dlys)
{
dlys*=12000000; //@cclk=60mhz  ~1s
while(dlys--);
}

