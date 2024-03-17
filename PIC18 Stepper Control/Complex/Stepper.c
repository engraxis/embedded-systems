//////////////////////////////////////////////////
///////////////// Abdullah Tahir /////////////////
////////////// Stepper Motor Program /////////////
//////////////////////////////////////////////////

#pragma config OSC=HS, OSCS=OFF					//High Speed XTAL/4 HS, Internal Clock Source OFF					
#pragma config PWRT=OFF, BOR=ON, BORV=27		//Power Up Timer OFF, Brown Out Reset Voltage 2.7
#pragma config WDT=OFF, LVP=OFF					//Watch Dog Timer OFF, Low Voltage ICSP OFF
#pragma config DEBUG=OFF, STVR=OFF				//DEBUG OFF, Stack Full Reset OFF

#include<P18F458.h>
////////////Declaring Functions///////////////////
void delay(void);								//Delay function using Timer0 for 0.2 sec
void cw_cmove(void);							//Function for Continous CW Movement
void ccw_cmove(void);							//Function for Continous CCW Movement
void cw_move(void);								//Function for CW Movement
void ccw_move(void);							//Function for CCW Movement
///////////////Declaring Pins/////////////////////
#define cwc PORTDbits.RD4						//Defining RD4 for Continous CW
#define ccwc PORTDbits.RD5						//Defining RD5 for Continous CCW
#define cw PORTDbits.RD6						//Defining RD6 for CW
#define ccw PORTDbits.RD7						//Defining RD7 for CCW
//////////////////////////////////////////////////
unsigned char steps;							//Counting up steps
unsigned char pos;								//Setting current position 
//////////////////////////////////////////////////
void main(void)
{
	TRISD=0x0F;
	
	TRISC=0x00;									//Make PORTC output port for stepper motor control
	PORTC=0x00;									//Set it to zero

	steps=0;
	pos='a';
	
	while(1)
	{
		if (cwc==1)
		{
			cw_cmove();
		}
		if (ccwc==1)
		{
			ccw_cmove();
		}
		if (cw==1)
		{
			cw_move();
		}
		if (ccw==1)
		{
			ccw_move();
		}
	}
}
//////////////////////////////////////////////////
void cw_move(void)
{
	if(pos=='a')
	{
		while(steps<=50)
		{
			delay();
			steps++;
			pos='d';
			PORTC=0x04;
			
			delay();
			steps++;
			pos='c';
			PORTC=0x02;
			
			delay();
			steps++;
			pos='b';
			PORTC=0x01;
		
			delay();
			steps++;
			pos='a';
			PORTC=0x08;			
		}	
	}
	
	if(pos=='b')
	{
		while(steps<=50)
		{
			delay();
			steps++;
			pos='a';
			PORTC=0x08;
			
			delay();
			steps++;
			pos='d';
			PORTC=0x04;
			
			delay();
			steps++;
			pos='c';
			PORTC=0x02;

			delay();
			steps++;
			pos='b';
			PORTC=0x01;		
		}	
	}
		
	if(pos=='c')
	{
		while(steps<=50)
		{
			delay();
			steps++;
			pos='b';
			PORTC=0x01;
		
			delay();
			steps++;
			pos='a';
			PORTC=0x08;	
	
			delay();
			steps++;
			pos='d';
			PORTC=0x04;
			
			delay();
			steps++;
			pos='c';
			PORTC=0x02;					
		}	
	}
	
	if(pos=='d')
	{
		while(steps<=50)
		{
			delay();
			steps++;
			pos='c';
			PORTC=0x02;
			
			delay();
			steps++;
			pos='b';
			PORTC=0x01;
			
			delay();
			steps++;
			pos='a';
			PORTC=0x08;	
			
			delay();
			steps++;
			pos='d';
			PORTC=0x04;						
		}	
	}
	
	steps=0;
	return;	
}
//////////////////////////////////////////////////
void ccw_move(void)
{
	if(pos=='a')
	{
		while(steps<=50)
		{
			delay();
			steps++;
			pos='b';
			PORTC=0x01;
		
			delay();
			steps++;
			pos='c';
			PORTC=0x02;
		
			delay();
			steps++;
			pos='d';
			PORTC=0x04;
		
			delay();
			steps++;
			pos='a';
			PORTC=0x08;			
		}	
	}
	
	if(pos=='b')
	{
		while(steps<=50)
		{
			delay();
			steps++;
			pos='c';
			PORTC=0x02;
		
			delay();
			steps++;
			pos='d';
			PORTC=0x04;
		
			delay();
			steps++;
			pos='a';
			PORTC=0x08;	
			
			delay();
			steps++;
			pos='b';
			PORTC=0x01;		
		}	
	}
		
	if(pos=='c')
	{
		while(steps<=50)
		{
			delay();
			steps++;
			pos='d';
			PORTC=0x04;
		
			delay();
			steps++;
			pos='a';
			PORTC=0x08;	
			
			delay();
			steps++;
			pos='b';
			PORTC=0x01;	
			
			delay();
			steps++;
			pos='c';
			PORTC=0x02;					
		}	
	}
	
	if(pos=='d')
	{
		while(steps<=50)
		{
			delay();
			steps++;
			pos='a';
			PORTC=0x08;	
			
			delay();
			steps++;
			pos='b';
			PORTC=0x01;
			
			delay();
			steps++;
			pos='c';
			PORTC=0x02;
		
			delay();
			steps++;
			pos='d';
			PORTC=0x04;						
		}	
	}
	
	steps=0;
	return;
}
//////////////////////////////////////////////////
void ccw_cmove(void)
{
	while(ccwc==1)
	{
		if(pos=='a')
		{
			delay();
			pos='b';
			PORTC=0x01;
		
			delay();
			pos='c';
			PORTC=0x02;
		
			delay();
			pos='d';
			PORTC=0x04;
		
			delay();
			pos='a';
			PORTC=0x08;			
		}	
	
		if(pos=='b')
		{
			delay();
			pos='c';
			PORTC=0x02;
		
			delay();
			pos='d';
			PORTC=0x04;
		
			delay();
			pos='a';
			PORTC=0x08;	
			
			delay();
			pos='b';
			PORTC=0x01;		
		}	
	
		
		if(pos=='c')
		{
			delay();
			pos='d';
			PORTC=0x04;
		
			delay();
			pos='a';
			PORTC=0x08;	
			
			delay();
			pos='b';
			PORTC=0x01;	
			
			delay();
			pos='c';
			PORTC=0x02;					
		}	
	
	
		if(pos=='d')
		{
			delay();
			pos='a';
			PORTC=0x08;	
			
			delay();
			pos='b';
			PORTC=0x01;
			
			delay();
			pos='c';
			PORTC=0x02;
		
			delay();
			pos='d';
			PORTC=0x04;						
		}	
	}	
	return;
}
//////////////////////////////////////////////////
void cw_cmove(void)
{
	while(cwc==1)
	{
		if(pos=='a')
		{
			delay();
			pos='d';
			PORTC=0x04;
			
			delay();
			pos='c';
			PORTC=0x02;
			
			delay();
			pos='b';
			PORTC=0x01;
		
			delay();
			pos='a';
			PORTC=0x08;			
		}	
	
	
		if(pos=='b')
		{
			delay();
			pos='a';
			PORTC=0x08;
			
			delay();
			pos='d';
			PORTC=0x04;
			
			delay();
			pos='c';
			PORTC=0x02;

			delay();
			pos='b';
			PORTC=0x01;		
		}	
		
		if(pos=='c')
		{
			delay();
			pos='b';
			PORTC=0x01;
		
			delay();
			pos='a';
			PORTC=0x08;	
	
			delay();
			pos='d';
			PORTC=0x04;
			
			delay();
			pos='c';
			PORTC=0x02;					
		}	
	
		if(pos=='d')
		{
			delay();
			pos='c';
			PORTC=0x02;
			
			delay();
			pos='b';
			PORTC=0x01;
			
			delay();
			pos='a';
			PORTC=0x08;	
			
			delay();
			pos='d';
			PORTC=0x04;						
		}	
	}
	
	return;	
}
//////////////////////////////////////////////////
void delay(void)
{
	T0CON=0x04;								//timerstart off, 16bit timer, internal clock,increment on 
	TMR0H=0xEC;								//L to H transition, prescaler enable, 1 0 0 for 32
	TMR0L=0xED;
	T0CONbits.TMR0ON=1;
	while(INTCONbits.TMR0IF==0);
	T0CONbits.TMR0ON=0;
	INTCONbits.TMR0IF=0;
	return;
}
