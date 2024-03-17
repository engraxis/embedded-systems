#include <REGX51.H>
void delay (void);
unsigned int i,j;
void main (void)
{
	P1=P2=P3=P0=0x00;
	while(1)
	{
		P2=0x01;
		P3=0xBB;
		delay();
		P2=0x02;
		P3=0xBB;
		delay();
		P2=0x04;
		P3=0x00;
		delay();
		P2=0x08;
		P3=0xBF;
		delay();
		P2=0x10;
		P3=0xBF;
		delay();
	}				  
}
void delay (void)
{
	for(i=1;i<=1275;i++);
	return;
}