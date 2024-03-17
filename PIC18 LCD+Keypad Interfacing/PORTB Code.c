//	LCD & KEYPAD INTERFACING

#pragma config OSC=HS, OSCS=OFF
#pragma config PWRT=OFF, BOR=ON, BORV=45
#pragma config WDT=OFF, LVP=OFF
#pragma config DEBUG=OFF, STVR=OFF

#include<P18F458.h>
#include<string.h>

#define ldata PORTD

#define rs PORTCbits.RC7
#define rw PORTCbits.RC6
#define en PORTCbits.RC5
#define busy PORTDbits.RD7

void kp_isr(void);
void lcdcmd(unsigned char);
void lcddata(unsigned char);
void delay(unsigned char);
void lcdready(void);

unsigned char i,j,k;

unsigned char keypad[4][3]={'3','2','1',
							'6','5','4',
							'9','8','7',
							'#','0','*'};

///////////////////////////////////////////////////////
#pragma interrupt check_hp_isr
void check_hp_isr(void)
{
	if(INTCONbits.RBIF==1)
	kp_isr();
}
#pragma code

#pragma code MY_HP_INT = 0x0008
void MY_HP_INT(void)
{
	_asm
	GOTO check_hp_isr
	_endasm
}
#pragma code
///////////////////////////////////////////////////////

void main(void)
{	
	TRISD=TRISC=TRISA=TRISE=0x00;
	PORTD=PORTC=PORTA=PORTE=0X00;

	INTCON2bits.RBPU=0;
	TRISB=0XF0;
	PORTB=0XF0;
	while(PORTB!=0XF0);
	INTCONbits.RBIE=1;
	INTCONbits.GIE=1;

	lcdcmd(0x38);
	lcdcmd(0x0C);
	lcdcmd(0x01);
	lcdcmd(0x06);
	lcdcmd(0x80);

	while(1)
	{	
		PORTC++;
		delay(200);
	}
}

void lcddata(unsigned char value)
{
	lcdready();	 
	ldata=value;
	rs=1;
	rw=0;
	en=1;
	delay(10);
	en=0;
	return;
}
void lcdready(void)
{
	TRISD=0xFF;
	rs=0;
	rw=1;
	do
	{
		en=1;
		delay(10);
		en=0;
	}	
	while(busy==1);
	TRISD=0x00;
	return;
}
void lcdcmd(unsigned char value)
{
	lcdready();
	ldata=value;
	rs=0;
	rw=0;
	en=1;
	delay(10);
	en=0;
	return;
}	
void delay(unsigned char a)
{
	for(j=1;j<=a;j++)
		for(k=1;k<=100;k++);
	return;
}

void kp_isr(void)
{
	if(PORTB!=0xF0)
	{
		unsigned char temp,COL=0,ROW=0;
		delay(15);
		temp=PORTB;
		temp^=0xF0;

		if(!temp)
			return;

		while(temp<<=1)
			COL++;
	
		PORTB=0xFE;
	
		if(PORTB!=0xFE)
			ROW=0;
		else
		{
			PORTB=0xFD;
		
			if(PORTB!=0xFD)
				ROW=1;
			else
			{
				PORTB=0xFB;
			
				if(PORTB!=0xFB)
					ROW=2;
				else
				{	
					PORTB=0xF7;
					
					if(PORTB!=0xF7)
						ROW=3;
				}
			}
		}
	
		if(ROW<4)
			lcddata(keypad[ROW][COL]);
		PORTB=0XF0;
		INTCONbits.RBIF=0;
	}
	else
	{
		INTCONbits.RBIF=0;
	}
}
