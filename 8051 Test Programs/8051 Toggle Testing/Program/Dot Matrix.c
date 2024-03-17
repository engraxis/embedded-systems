#include <REGX51.H>
void delay (void);
unsigned int i,j;
void main (void)
{
	P1=P2=P3=P0=0x00;
	while(1)
	{
		P0=P1=P2=P3=0x55;
		delay();
		P0=P1=P2=P3=0xAA;
		delay();
	}				  
}
void delay (void)
{
	for(i=1;i<=12075;i++);
	return;
}