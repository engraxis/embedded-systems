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

#define in1 PORTCbits.RC0
#define in2 PORTCbits.RC1
#define en1 PORTCbits.RC2

void ch_kp_command(unsigned char);
void kp_isr(void);
void lcdcmd(unsigned char);
void lcddata(unsigned char);
void delay(unsigned char);
void lcdready(void);

unsigned char i,j,k,a;

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
	unsigned char fr[]="ABDULLAH TAHIR";
	unsigned char sr[]="UET LHR FSD CAMPUS";
	unsigned char tr[]="DC MOTOR CONTROL";
	unsigned char lr[]="CURRENT STATUS = 0";
	
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
	
	lcdcmd(0x83);
	for(a=0;a<=(strlen(fr)-1);a++)
		lcddata(fr[a]);

	lcdcmd(0xC1);
	for(a=0;a<=(strlen(sr)-1);a++)
		lcddata(sr[a]);

	lcdcmd(0x96);
	for(a=0;a<=(strlen(tr)-1);a++)
		lcddata(tr[a]);

	lcdcmd(0xD5);
	for(a=0;a<=(strlen(lr)-1);a++)
		lcddata(lr[a]);
////
	PR2=157; // Set frequency
	T2CON=0x03;
	CCPR1L=0x00;
	CCP1CON=0x2C;
	T2CONbits.TMR2ON=1;
////
	while(1);
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
	unsigned char iv[]="INVALID";

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
		lcdcmd(0xE6);
		if(ROW<4)
		{
			lcddata('K');
			lcddata(keypad[ROW][COL]);
			ch_kp_command(keypad[ROW][COL]);
		}
		PORTB=0XF0;
		INTCONbits.RBIF=0;
	}
	else
	{
		INTCONbits.RBIF=0;
	}
}
void ch_kp_command(unsigned char gv)
{	
	if(gv=='0')			// Inertial Stop, no movement
	{
		in1=in2=0;
		CCP1CON=0x00;
		en1=0;	
	}
	else if(gv=='1')	// Default is CW with 100% DC
	{
		in1=en1=1;
		in2=0;
		CCPR1L=0xFF;
		CCP1CON=0x0C;
	}
	else if(gv=='2')	// CCW
	{
		in1=en1=1;
		in2=0;
	}
	else if(gv=='3')	// CW
	{
		in1=0;
		in2=en1=1;
	}
	else if(gv=='4')	// Force Stop
	{
		CCPR1L=0xFF;
		in1=in2=en1=1;
	}
	else if(gv=='5')	// Level 1: 10% DC
	{
		CCPR1L=0x0F;
		CCP1CON=0x3C;
		en1=1;
	}	
	else if(gv=='6')	// Level 1: 30% DC
	{
		CCPR1L=0x2F;
		CCP1CON=0x0C;	
		en1=1;
	}
	else if(gv=='7')	// Level 1: 50% DC
	{	
		CCPR1L=0x4E;
		CCP1CON=0x2C;
		en1=1;
	}	
	else if(gv=='8')	// Level 1: 70% DC
	{
		CCPR1L=0x6E;
		CCP1CON=0x0C;
		en1=1;
	}	
	else if(gv=='9')	// Level 1: 90% DC
	{
		CCPR1L=0x8D;
		CCP1CON=0x1C;
		en1=1;
	}
	else
		return;
	return;
}