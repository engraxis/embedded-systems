/*****************************************************/
/*****************************************************/
// Line Follower Robot //
// PWM // Ultra Sonic // LCD // GPS // IR Sensors //
/*****************************************************/
/*****************************************************/

#pragma config OSC=HS, OSCS=OFF
#pragma config PWRT=OFF, BOR=ON, BORV=45
#pragma config WDT=OFF, LVP=OFF
#pragma config DEBUG=OFF, STVR=OFF

#include<P18F452.h>
// -------- USER DEFINED VARIABLES -------- //
unsigned char FLAG_CCP_UltraSonic_CaptureTime;
unsigned char FLAG_CCP_UltraSonic_Acquisition;
//////////////////////////////////////////////
// -------- USER DEFINED FUNCTIONS -------- //
void Prepare_CCP_UltraSonic(void);
void CCP_UltraSonic_CaptureTime(void);
void Prepare_CCP_ECCP_PWM_MotorControl(void);
void CCP_ECCP_MotorControl_TrackAdjustment(void);
//////////////////////////////////////////////
// --------------- INTERRUPT -------------- //
#pragma interrupt Check_Cause
void Check_Cause(void)
{
	if(PIR1bits.CCP1IF==1)
		CCP_UltraSonic_CaptureTime();
}
#pragma code High_Priority = 0x0008
void High_Priority (void)
{
	_asm
	GOTO Check_Cause
	_endasm
}
//////////////////////////////////////////////
// ------------- MAIN FUNCTION ------------ //
void main (void)
{
	FLAG_CCP_UltraSonic_CaptureTime = 0;
	FLAG_CCP_UltraSonic_Acquisition = 0;
	INTCONbits.GIE = 0;
	TRISD = TRISB = TRISE = 0X00;
	PORTD = PORTB = PORTE = 0X00;
	while(1)
	{
		Prepare_CCP_UltraSonic();					// Interrupts Enabled
		while(!FLAG_CCP_UltraSonic_Acquisition);
		FLAG_CCP_UltraSonic_Acquisition = 0;
		INTCONbits.PEIE = 0;						// Interrupts Disabled
		INTCONbits.GIE = 0;
// TODO: Perform Calculation for Distance according to TimeDelay/PulseDuration
		PORTE = 0xFF;
		PORTB = TMR1H;
		PORTD = TMR1L;
//
		Prepare_CCP_ECCP_PWM_MotorControl();
		CCP_ECCP_MotorControl_TrackAdjustment();
	}
}
//////////////////////////////////////////////
void Prepare_CCP_UltraSonic()
{
	CCP1CON = 0x05;
	T3CON = 0x00;
	T1CON = 0x00;
	TMR1H = 0x00;
	TMR1L = 0x00;
	TRISCbits.RC2 = 1;
	PIE1bits.CCP1IE = 1;
	INTCONbits.PEIE = 1;
	INTCONbits.GIE = 1;
	return;
}

void CCP_UltraSonic_CaptureTime()
{
	if(FLAG_CCP_UltraSonic_CaptureTime == 0) // Detecting rising edge
	{
		T1CONbits.TMR1ON = 1;
		FLAG_CCP_UltraSonic_CaptureTime = 1;
		CCP1CONbits.CCP1M0 = 0;
		PIR1bits.CCP1IF = 0;
		return;
	}
	if(FLAG_CCP_UltraSonic_CaptureTime == 1) // Detecting falling edge
	{
		T1CONbits.TMR1ON = 0;
		FLAG_CCP_UltraSonic_CaptureTime = 0;
		CCP1CONbits.CCP1M0 = 1;
		PIR1bits.CCP1IF = 0;
		FLAG_CCP_UltraSonic_Acquisition = 1;
		return;
	}
}

void Prepare_CCP_ECCP_PWM_MotorControl(void)
{
	return;
}

void CCP_ECCP_MotorControl_TrackAdjustment(void)
{
	return;
}