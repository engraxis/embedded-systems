#include <REGX51.H>
void delay(unsigned int);
unsigned int i;
void main(void)
{
unsigned char abz[]="UETMechatronicsRobotics  Club106 127  157 159";
	TMOD=0X20;
	TH1=0XFD;
	SCON=0X50;
	TR1=1;
	delay(40);
	for(i=0;i<=46;i++)
	{
		delay(20);
		SBUF=abz[i];
		while(TI==0);
		TI=0;
	}
	while(1);
}
void delay(unsigned int itime)
{
	unsigned int i,j;
	for(i=0;i<itime;i++)
		for (j=0;j<1275;j++);
}
