#include <REGX51.H>
sbit motor1=P2^0; 
sbit manual_move_motor1=P3^7;
sbit reset=P3^6;
void move_motor1(unsigned int);
void main(void)
{
    unsigned int a;
	unsigned char x;
	x=0;		  
	P3=0x00;
	motor1=0;
	// Initializing Timer for minimum delay
	TMOD = 0x02; //Timer0 Auto-reload
	TH0 = 0xFE; 
	TL0 = 0xFE;

	// Auto Cycle
    move_motor1(3);
	for(a=1;a<=60000;a++);
	move_motor1(4);
	for(a=1;a<=60000;a++);
	move_motor1(3);

	// Manual Cycle
	while(1)
	{
		if(reset==1)
		{
			move_motor1(0);
			x=0;
		}
		while(manual_move_motor1==1)
		{
			move_motor1(x);
			for(a=1;a<=8000;a++);
			x++;
		}
	}
}
void move_motor1(unsigned int loop)
{

	unsigned int lloop;
	loop = loop + 57;
	motor1=1;
	for(lloop=1;lloop<=loop;lloop++)
	{
		TR0=1;
		while(TF0==0);
		TR0=0;	
	} 
	motor1=0;
	return;
}