///////////////////////////////////////////////////////////////////////////
#include <REGX51.H>

#define lcd P0
#define row P1
#define col P2

sbit rs=P1^5;
sbit rw=P1^6;
sbit en=P1^7;
sbit lcdbusy=P0^7;

////////////////////////////////// KEYPAD /////////////////////////////////
unsigned char keypad[4][3]={ '1', '2', '3',
							 '4', '5', '6',
							 '7', '8', '9',
							 '*', '0', '#' };
/////////////////////////// IMPORTANT FUNCTIONS ////////////////////////////
void lcdcmd(unsigned char);
void lcddata(unsigned char);
void lcdready(void);

char kpad(void);

void delay(unsigned int);
void time_delay(void);

unsigned int i;									// Global looping variable

//////////////////////////////////////////////////////
void main(void)
{	
	P0=P1=P3=0x00;
	P2=0xFF;
	lcdcmd(0x38);
	lcdcmd(0x0C);
	lcdcmd(0x01);
	lcdcmd(0x06);
	lcdcmd(0x80);
	lcddata('A');lcddata('B');lcddata('Z');					  				
	while(1)
	{
		time_delay();
		lcdcmd(0x01);
		lcddata(kpad()); 
	}
}
/////////////////////////////////////////////////////////////////////////
void lcdcmd(unsigned char value)	// Sending Commands to LCD
{
	lcdready();
	lcd=value;
	rs=0;
	rw=0;
	en=1;
	delay(50);
	en=0;
	return;
}
/////////////////////////////////////////////////////////////////////////
void lcddata(unsigned char value)	// Sending Data to LCD
{
	lcdready();	 
	lcd=value;
	rs=1;
	rw=0;
	en=1;
	delay(50);
	en=0;
	return;
}
/////////////////////////////////////////////////////////////////////////
void lcdready(void)					// Checking wether LCD is busy, if yes wait!
{
	lcdbusy=1;
	rs=0;
	rw=1;
	while(lcdbusy==1)
	{
		en=0;
		delay(50);
		en=1;
	}	
	return;
}
/////////////////////////////////////////////////////////////////////////
char kpad(void)						// Keypad Subroutine
{		
	   	

	unsigned char c,r,x;
	P0=P1=P3=0x00;
	P2=0xFF;
		
		do
		{
			row=0x00;
			c=col;
			c&=0x0F;
		}		
		while(c!=0x0F);		// See until all keys are open
			
		do
		{
			do
			{
				delay(20);
				c=col;
				c&=0x0F;
			}
			while(c==0x0F); // Keep checking for key press
			
			delay(20);
			c=col;
			c&=0x0F;		
		}
		while(c==0x0F);		// Is really any key pressed?

		while(1)
		{
			row=0xFE;		// Ground only first row and then check, if ALL columns are not HIGH means key does belong here
			c=col;
			c&=0x0F;
			if(c!=0x0F)
			{
				r=0;
				break;
			}

			row=0xFD;
			c=col;
			c&=0x0F;//
			if(c!=0x0F)//
			{
				r=1;
				break;
			}

			row=0xFB;
			c=col;
			c&=0x0F;//
			if(c!=0x0F)//
			{
				r=2;
				break;
			}

			row=0xF7;
			c=col;
			c&=0x0F;//
			r=3;
			break;
		}
	
		if(c==0x0E)
		{
			x=keypad[r][0];
		}
		else if(c==0x0D)
		{
			x=keypad[r][1];	
		}
		else if(c==0x0B)
		{
			x=keypad[r][2];
		}
		else
		{
			x=keypad[r][3];
		}		
	return x;
}
/////////////////////////////////////////////////////////////////////////
void delay(unsigned int z)
{	
	for(z=1;z<=2000;z++);
	return;
}
void time_delay(void)
{
	unsigned int a;
	for(a=1;a<=60000;a++);
	return;
}
