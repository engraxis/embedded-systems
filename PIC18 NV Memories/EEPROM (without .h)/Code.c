////////////////////////////////////////////////////////////////////
//////////// Robotic Arm Control v1 09-09-13 by abxLabs ////////////
////////////////////////////////////////////////////////////////////
#include<P18f452.h>
////////////////////////////////////////////////////////////////////
void init_serial(void);	//Initializing serial port
void Delay_100ms(unsigned char);//Timer0 with 100ms delay

void WriteEEPROM(void);
unsigned char ReadEEPROM(void);
////////////////////////////////////////////////////////////////////
unsigned char dummy[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned char sp_index,allbytes;
////////////////////////////////////////////////////////////////////
/*-- Interrupts: Serial(HPI) and External(LPI) 'Emergency Stop' --*/
////////////////////////////////////////////////////////////////////
void check_isr(void);
void check_low_isr(void);

#pragma code my_high_prio_int = 0x08
void my_high_prio_int(void)
{
	_asm
	GOTO check_isr
	_endasm
}
////////////////////////////////////////////////////////////////////
#pragma code my_low_prio_int = 0x18
void my_low_prio_int(void)
{
	_asm
	GOTO check_low_isr
	_endasm
}
#pragma code
////////////////////////////////////////////////////////////////////
#pragma interrupt check_isr
void check_isr(void)
{
	INTCONbits.GIE=0;

	if(PIR1bits.RCIF==1)
	{
		WriteEEPROM();
	}	
	if(PIR1bits.TXIF==1)
	{
	}

	INTCONbits.GIE=1;
}
////////////////////////////////////////////////////////////////////
#pragma interruptlow check_low_isr
void check_low_isr(void)
{
	
}
////////////////////////////////////////////////////////////////////
void WriteEEPROM(void)
{
	EEADR = sp_index;
	EEDATA = RCREG;
	EECON1bits.EEPGD=0;
	EECON1bits.CFGS=0;
	EECON1bits.WREN=1;
	EECON2=0X55;
	EECON2=0XAA;
	EECON1bits.WR=1;
	INTCONbits.GIE=1;
	while(!PIR2bits.EEIF);
	PIR2bits.EEIF=0;
	sp_index++;
	allbytes++;
	PORTB = ~PORTB;
}
////////////////////////////////////////////////////////////////////
//-- Interuupt Service Routine Ended --//
////////////////////////////////////////////////////////////////////
void main(void)
{
	TRISB = TRISD = 0x00;
	PORTB = 0xAA;
	PORTD = 0x00;

	sp_index=0;	
	allbytes=1;

	init_serial();


	while(1)
	{
		if(allbytes==14)
		{
			sp_index=0;
			while(1)
			{
				PORTB = ReadEEPROM();
				sp_index++;
				Delay_100ms(10);
				if(sp_index == 13) sp_index=0;	
			}
		}
	}
}
////////////////////////////////////////////////////////////////////
void init_serial(void)
{
	SPBRG=64;
	TRISCbits.RC7=1;	//rx pin set as input
	TRISCbits.RC6=0;	//tx pin set as output
	TXSTAbits.BRGH=1;	//High Baud rate is selected
	TXSTAbits.TXEN=1;	//Activating serial transmit	
	RCSTAbits.SPEN=1;	//Enabeling serial port
	RCSTAbits.CREN=1;	//Activating serial recieve
	INTCONbits.GIE=1;	//Enabeling global interrupts
	INTCONbits.PEIE=1;	//Enabeling peripheral interrupts
	PIE1bits.RCIE=1;	//Enabeling recieve interrupt
//	PIE1bits.TXIE=1;	//Enabeling transmit interrupt
	PIR1bits.RCIF=0;	//Lowering recieve interrupt flag
	PIR1bits.TXIF=0;	//Lowering transmit interrupt flag
	return;
}
////////////////////////////////////////////////////////////////////
void Delay_100ms(unsigned char DelayLoop)
{
	unsigned int Lvar;
	for(Lvar=0; Lvar<=DelayLoop; Lvar++)
	{
		T0CON=0X05;
		TMR0H=0XF0;
		TMR0L=0XBE;
		T0CONbits.TMR0ON=1;
		while(INTCONbits.TMR0IF==0);
		T0CONbits.TMR0ON=0;
		INTCONbits.TMR0IF=0;
	}
	return;
}
////////////////////////////////////////////////////////////////////
unsigned char ReadEEPROM(void)
{
	EEADR = sp_index;
	EECON1bits.EEPGD = 0;
	EECON1bits.CFGS = 0;
	EECON1bits.RD = 1;
	_asm NOP _endasm
	return(EEDATA);
}