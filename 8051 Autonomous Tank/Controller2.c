/////////////////////////////////////////////////////////////////////////////////////////
// Controller is receiving data serially and then manipulating stepper motor
// Also receiving data through radio receiver and then commanding the shooting mechanism
/////////////////////////////////////////////////////////////////////////////////////////

#include <REGX51.H>

sbit shoot = P3^7;
sbit rf_in = P1^2;

void move_stepper(unsigned char);
void fire(void);
void stepper_pulses(unsigned char, unsigned char);

unsigned int i;
unsigned char loop;

void main(void)
{
 P0 = 0x00;
 P2 = 0x01;   // stepper motor 
 P1 = 0x0F;	  // radio receiver
// P3 = 0x01;
 TMOD = 0x20; // Setting serial port settings
 TH1 = 0xFD;
 SCON = 0x50;
 TR1 = 1;
 shoot=1;
 while(1)
 {
   move_stepper('f');
   fire(); 
 }
}

void move_stepper(unsigned char x)
{
	
 unsigned char rec;
 if(x=='f')
 {
  while(RI==0); 
  RI=0;
  rec = SBUF; 
  stepper_pulses(rec,'f');
 }
 if (x=='r')
 {
  stepper_pulses(rec,'r');
 }
 return;
}


void fire(void)
{
 	while (!rf_in);
 	shoot = 0;
 	for(i=1;i<=50000;i++);
 	shoot = 1;
 	move_stepper('r');

 	for(i=1;1<=30;i++)
 	{
 		SBUF=9;
 		while(TI==0);
 		TI=0;
 	}
 	return;
}

void stepper_pulses(unsigned char pul,unsigned char dir)
{
	unsigned char j;
	unsigned char k;
	if (dir=='f')
	{
	for(j=1;j<=pul;j++)
	{
		for(k=1;k<=12;k++)
		{
			P2=0x11;
			for(i=0;i<=10000;i++);
			P2=0x22;
			for(i=0;i<=10000;i++);
			P2=0x44;
			for(i=0;i<=10000;i++);
			P2=0x88;
			for(i=0;i<=10000;i++);
		}
	}
	}

	if (dir=='r')
	{
	for(j=1;j<=pul;j++)
	{
		for(k=1;k<=12;k++)
		{
			P2=0x88;
			for(i=0;i<=10000;i++);
			P2=0x44;
			for(i=0;i<=10000;i++);
			P2=0x22;
			for(i=0;i<=10000;i++);
			P2=0x11;
			for(i=0;i<=10000;i++);
		}
	}
	}

}






