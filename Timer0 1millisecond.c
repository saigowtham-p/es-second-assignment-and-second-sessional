#include<lpc214x.h>

void delay(unsigned int z);		   

void pll();

int main(void)
{
	IO0DIR=0xffffffff;
	pll();									
	while(1) {
		IO0SET |=1<<1;
		delay(100);			   
		IO0CLR |=1<<1;
		delay(100);			   
	}
}


void pll()							
{
	PLL0CON=0x01;
	PLL0CFG=0x24;
	PLL0FEED=0xaa;
	PLL0FEED=0x55;
	while(!(PLL0STAT&(1<<10)));
	PLL0CON=0x03;
	PLL0FEED=0xaa;
	PLL0FEED=0x55;
	VPBDIV=0x01;
}


void delay(unsigned int z)
{
	T0CTCR=0x0;       	
	T0TCR=0x00;					
	T0PR=59999;					
	T0TCR=0x02;					
	T0TCR=0x01;					
	while(T0TC<z);			
	T0TCR=0x00;				
	T0TC=0;				
}