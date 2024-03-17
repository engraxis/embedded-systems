//////////////////////////////////////////////////
///////////////// Abdullah Tahir /////////////////
////////////// Stepper Motor Program /////////////
//////////////////////////////////////////////////
												//Using step angle of 1.8 Degrees
#pragma config OSC=HS, OSCS=OFF					//High Speed XTAL/4 HS, Internal Clock Source OFF					
#pragma config PWRT=OFF, BOR=ON, BORV=27		//Power Up Timer OFF, Brown Out Reset Voltage 2.7
#pragma config WDT=OFF, LVP=OFF					//Watch Dog Timer OFF, Low Voltage ICSP OFF
#pragma config DEBUG=OFF, STVR=OFF				//DEBUG OFF, Stack Full Reset OFF

#include<P18F458.h>
////////////Declaring Functions///////////////////
void chk_isr(void);								//To check what caused interrupt
void INT0_isr(void);							//Interrupt Function
void delay(void);								//Delay function using Timer0 for 0.2 sec
void reset(void);								//Function for Resetting the Motor Position
void cw_cmove(void);							//Function for Continous CW Movement
void ccw_cmove(void);							//Function for Continous CCW Movement
void cw_move(void);								//Function for CW Movement
void ccw_move(void);							//Function for CCW Movement
///////////////Declaring Pins/////////////////////
#define res PORTDbits.RD3						//Defining RD3 for partial reset purpose
#define cwc PORTDbits.RD4						//Defining RD4 for Continous CW
#define ccwc PORTDbits.RD5						//Defining RD5 for Continous CCW
#define cw PORTDbits.RD6						//Defining RD6 for CW
#define ccw PORTDbits.RD7						//Defining RD7 for CCW
//////////////////////////////////////////////////
unsigned char steps;							//Counting up steps
unsigned char pos;								//Setting current position 
signed int rest;								//For resetting the position || -ve values are also involved
//////////////////////////////////////////////////
#pragma interrupt chk_isr						//Used for high priority interrupts
void chk_isr(void)
{												//What actually caused interrupt!
	if(INTCONbits.INT0IF==1)
	{
		INT0_isr();
	}
}
//////////////////////////////////////////////////
#pragma code superreset=0x0008					//High priority interrupt location
void superrest(void)
{
	_asm										//Using assembly language instruction
	GOTO chk_isr
	_endasm
}
#pragma code
//////////////////////////////////////////////////
void main(void)
{
	TRISBbits.TRISB0=1;							//Make RB0=1 for input signal of Super Reset
	INTCONbits.INT0IF=0;						//Initially clear Flag for satisfaction
	INTCONbits.INT0IE=1;						//Enable INT0
	INTCONbits.GIE=1;							//Enable all interrupts

	
	TRISD=0xFF;
	
	TRISC=0x00;									//Make PORTC output port for stepper motor control
	PORTC=0x00;									//Set it to zero

	steps=0;
	rest=0;
	pos='d';
	
	while(1)
	{
		if (res==1)
		{
			reset();
		}
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
void reset(void)
{
	if (rest<0)
	{
		while(rest<0)
		{
			if(pos=='d')
			{
				PORTC=0X08;
				pos='a';
				rest++;	
				delay();	
			}
			if(pos=='a')
			{
				PORTC=0X04;
				pos='b';
				rest++;	
				delay();	
			}
			if(pos=='b')
			{
				PORTC=0X02;
				pos='c';
				rest++;
				delay();	
			}
			if(pos=='c')
			{
				PORTC=0X01;
				pos='d';
				rest++;	
				delay();	
			}
		}
	}
	if(rest>0)
	{
		while(rest>0)
		{	
			if(pos=='a')
			{
				PORTC=0X01;
				pos='d';
				rest--;	
				delay();	
			}
			if(pos=='d')
			{
				PORTC=0X02;
				pos='c';
				rest--;	
				delay();	
			}
			if(pos=='c')
			{
				PORTC=0X04;
				pos='b';
				rest--;	
				delay();	
			}
			if(pos=='b')
			{
				PORTC=0X08;
				pos='a';
				rest--;	
				delay();	
			}	
		}
	}
	return;
}
//////////////////////////////////////////////////
void cw_cmove(void)
{
	while(cwc==1)
	{
		if(pos=='d')
		{
			PORTC=0X08;
			pos='a';
			rest++;	
			delay();	
		}
		if(pos=='a')
		{
			PORTC=0X04;
			pos='b';
			rest++;	
			delay();	
		}
		if(pos=='b')
		{
			PORTC=0X02;
			pos='c';
			rest++;
			delay();	
		}
		if(pos=='c')
		{
			PORTC=0X01;
			pos='d';
			rest++;	
			delay();	
		}
	}
	return;
}
//////////////////////////////////////////////////
void ccw_cmove(void)
{
	while(ccwc==1)
	{	
		if(pos=='a')
		{
			PORTC=0X01;
			pos='d';
			rest--;	
			delay();	
		}
		if(pos=='d')
		{
			PORTC=0X02;
			pos='c';
			rest--;	
			delay();	
		}
		if(pos=='c')
		{
			PORTC=0X04;
			pos='b';
			rest--;	
			delay();	
		}
		if(pos=='b')
		{
			PORTC=0X08;
			pos='a';
			rest--;	
			delay();	
		}	
	}
	return;
}
//////////////////////////////////////////////////
void cw_move(void)
{
	while(steps<=50)
	{
		if(pos=='d')
		{
			PORTC=0X08;
			pos='a';
			rest++;	
			delay();
			steps++;	
		}
		if(pos=='a')
		{
			PORTC=0X04;
			pos='b';
			rest++;	
			delay();
			steps++;	
		}
		if(pos=='b')
		{
			PORTC=0X02;
			pos='c';
			rest++;
			delay();
			steps++;	
		}
		if(pos=='c')
		{
			PORTC=0X01;
			pos='d';
			rest++;	
			delay();
			steps++;	
		}
	}
	steps=0;
	return;
}
//////////////////////////////////////////////////
void ccw_move(void)
{
	while(steps<=50)
	{	
		if(pos=='a')
		{
			PORTC=0X01;
			pos='d';
			rest--;	
			delay();
			steps++;	
		}
		if(pos=='d')
		{
			PORTC=0X02;
			pos='c';
			rest--;	
			delay();
			steps++;	
		}
		if(pos=='c')
		{
			PORTC=0X04;
			pos='b';
			rest--;	
			delay();
			steps++;	
		}
		if(pos=='b')
		{
			PORTC=0X08;
			pos='a';
			rest--;	
			delay();
			steps++;	
		}
	}
	steps=0;
	return;
}
//////////////////////////////////////////////////
void INT0_isr(void)
{
	if (rest<0)
	{
		while(rest<0)
		{
			if(pos=='d')
			{
				PORTC=0X08;
				pos='a';
				rest++;	
				delay();	
			}
			if(pos=='a')
			{
				PORTC=0X04;
				pos='b';
				rest++;	
				delay();	
			}
			if(pos=='b')
			{
				PORTC=0X02;
				pos='c';
				rest++;
				delay();	
			}
			if(pos=='c')
			{
				PORTC=0X01;
				pos='d';
				rest++;	
				delay();	
			}
		}
	}
	if(rest>0)
	{
		while(rest>0)
		{	
			if(pos=='a')
			{
				PORTC=0X01;
				pos='d';
				rest--;	
				delay();	
			}
			if(pos=='d')
			{
				PORTC=0X02;
				pos='c';
				rest--;	
				delay();	
			}
			if(pos=='c')
			{
				PORTC=0X04;
				pos='b';
				rest--;	
				delay();	
			}
			if(pos=='b')
			{
				PORTC=0X08;
				pos='a';
				rest--;	
				delay();	
			}	
		}
	}
	INTCONbits.INT0IF=0;
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
