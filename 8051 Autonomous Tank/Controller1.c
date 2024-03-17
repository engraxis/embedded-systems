///////////////////////////////////////////////////////////////////////////
#include <REGX51.H>
#include <string.h>

#define lcd P0
#define row P1
#define col P2

sbit rs=P1^5;
sbit rw=P1^6;
sbit en=P1^7;
sbit lcdbusy=P0^7;

sbit m11=P3^2;
sbit m12=P3^3;
sbit m21=P3^6;
sbit m22=P3^7;

sbit us_l = P2^4; 
sbit us_r = P2^7;
sbit us_f = P2^5;
sbit us_b = P2^6;

////////////////////////////////// KEYPAD /////////////////////////////////
unsigned char keypad[4][3]={ '1', '2',  '3',
							 '4', '5', '6',
							 '7', '8', '9',
							 '*', '0', '#'  };
/////////////////////////// IMPORTANT FUNCTIONS ////////////////////////////
void lcdcmd(unsigned char);
void lcddata(unsigned char);
void lcdready(void);

char kpad(void);

void delay(unsigned int);

void initialization(void);
void coordinates(void);
void logic(unsigned char, unsigned char, unsigned char []);
void start(unsigned char, unsigned char, unsigned char, unsigned char);
void enter_coordinates(unsigned char);
void start_counters(void);
void stepper_fire(void);

unsigned int i;									// Global looping variable
code unsigned char info2[] = "#: Next"; 		// Will be used in many screens
//////////////////////////////////////////////////////
void main(void)
{						
	P0=P1=P2=0x00;	
	P2=0xF0;	
	TMOD=0x26;
	SCON=0x50;
	TH1=0xFD;
	TI=0;
	RI=0;
	TR1=1;


	initialization();
	coordinates();

	while(1);
}
/////////////////////////////////////////////////////////////////////////
void initialization(void)
{
	code unsigned char disp1[] = "W E L C O M E"; 

	m11=m12=m21=m22=0; 	
	P2 = P2 & 0x0F;
	lcdcmd(0x38);
	lcdcmd(0x0C);
	lcdcmd(0x01);
	lcdcmd(0x06);
/////////////////////////////////////////////////////////////
	lcdcmd(0x81);	
	for (i=0;i<=(strlen(disp1)-1);i++)
	{
		lcddata(disp1[i]);					// Welcome 
	}
	lcdcmd(0xC0);
	for (i=0;i<=(strlen(info2)-1);i++)
	{
		lcddata(info2[i]);					// #: Next 
	}
/////////////////////////////////////////////////////////////
	while(1)
	{
		if (kpad() == '#')
		{
			lcdcmd(0x01);
			break;
		}
	}

}
/////////////////////////////////////////////////////////////
void coordinates(void)
{
	code unsigned char info1[] = "Points = 4"; 
	unsigned char total;
	lcdcmd(0x80);	
	for (i=0;i<=(strlen(info1)-1);i++)
	{
		lcddata(info1[i]);					// Get total number of coordinates
	}
	lcdcmd(0xC0);
	for (i=0;i<=(strlen(info2)-1);i++)
	{
		lcddata(info2[i]);					// #: Next 
	}

/*	total = kpad();
	lcdcmd(0x89);
	lcddata(total);
	total = total & 0x0F;  					// From ASCII -> binary
*/
	total=0x04;
	while(1)
	{
		if (kpad() == '#')
		{
			lcdcmd(0x01);
			break;
		}
	}
	enter_coordinates(total);
	return;
}
void enter_coordinates(unsigned char total)
{
	code unsigned char disp2[]="X,Y:  =  ,  ";
	unsigned char xy_coordinates[20];
	unsigned char total_loop, total_disp, xy_increment, a;
	xy_increment=0;
	xy_coordinates[0]=' ';

	for(total_loop=1; total_loop<=total; total_loop++)	
	{
		// Enter Points
		for (i=0;i<=(strlen(disp2)-1);i++)
		{
			lcddata(disp2[i]);			
		}
		total_disp = total_loop & 0x0F;
		total_disp = total_loop | 0x30;
		lcdcmd(0x84);
		lcddata(total_disp);
	
		lcdcmd(0xC0);
		for (i=0;i<=(strlen(info2)-1);i++)
		{
			lcddata(info2[i]);			   // #: Next 
		}

		a = kpad();
		lcdcmd(0x88);
		lcddata(a);
		xy_coordinates[xy_increment++] = a;// & 0x0F;
		a = kpad();
		lcdcmd(0x8A);
		lcddata(a);
		xy_coordinates[xy_increment++] = a;// & 0x0F;
		
		while(1)
		{
			if (kpad() == '#')
			{
				lcdcmd(0x01);
				break;
			}
		}
	}
	logic(total, total_loop, xy_coordinates);
	return;
}
void logic(unsigned char total, unsigned char total_loop, unsigned char xy_coordinates[20])
{
	unsigned char side1, side2, side3, side4;	

	// By default robot will be moving clockwise
	// By default considering four points
	
	// Converting ASCII to Binary
	lcdcmd(0x01);
	for (total_loop=0; total_loop<=((2*total)-1); total_loop++)
	{
		xy_coordinates[total_loop] = xy_coordinates[total_loop] & 0x0F; 												  
	}

	// Now calculating pulses to run motors
	side1 = xy_coordinates[3] - xy_coordinates[1]; 
	side2 = xy_coordinates[4] - xy_coordinates[2];
	side3 = xy_coordinates[5] - xy_coordinates[7];
	side4 = xy_coordinates[6] - xy_coordinates[0];
	
	// Relation between pulses and feet
	side1 = side1/1;
	side2 = side2/1;
	side3 = side3/1;
	side4 = side4/1;

	start(side1, side2, side3, side4);

	return;
}
void start(unsigned char side1, unsigned char side2, unsigned char side3, unsigned char side4)
{
	code unsigned char info1[] = "Status:"; 
	code unsigned char info2[] = "MOVING";
	lcdcmd(0x80);	
	for (i=0;i<=(strlen(info1)-1);i++)
	{
		lcddata(info1[i]);				
	}
	lcdcmd(0xC2);
	for (i=0;i<=(strlen(info2)-1);i++)
	{
		lcddata(info2[i]);				
	}
//	P3=0x30;

	while(1)
	{
// Driving side 1		
	m11=m12=m21=m22=0;
	start_counters();
	while(1)  		
	{
		m11=m22=1;
		m12=m21=0;
		if(us_l == 1 || us_r == 1 || us_f == 1 || us_b == 1)
		{
			m11=m21=m12=m22=0;
			stepper_fire();
		}
	
		if(TL0 >= side1)
		{
	 		m11=m12=m21=m22=0;
	 		TR0=0;
	 		break;
		}
	}
// Turn 90* CW
		m11=m12=m21=m22=0;
		start_counters();
		while(1)	
		{
			m11=1;
			m12=m21=m22=0;
			if ( TL0>= 6)
			{
				m11=m12=m21=m22=0;
				TR0=0;
				break;	
			}		
		}

// Driving side2
		m11=m12=m21=m22=0;
		start_counters();
		while(1)	
		{
			m11=m22=1;
			m12=m21=0;
			
			if(us_l == 1 || us_r == 1 || us_f == 1 || us_b == 1)
			{
				m11=m21=m12=m22=0;
				stepper_fire();
			}

			if(TL0 >= side2)
			{
				m11=m12=m21=m22=0;
				TR0=0;
				break;
			}
		}
// Trun 90* CW
		m11=m12=m21=m22=0;
		start_counters();
		while(1)		// Turn
		{
			m11=1;
			m12=m21=m22=0;
			if ( TL0>= 6)
			{
				m11=m12=m21=m22=0;
				TR0=0;
				break;	
			}		
		}
 // Driving side3
		m11=m12=m21=m22=0;
		start_counters();
		while(1)		
		{
			m11=m22=1;
			m12=m21=0;
			
			if(us_l == 1 || us_r == 1 || us_f == 1 || us_b == 1)
			{
				m11=m21=m12=m22=0;
				stepper_fire();
			}

			if(TL0 >= side3)
			{
				m11=m12=m21=m22=0;
				TR0=0;
				break;
			}
		}
// Turn 90* CW
		m11=m12=m21=m22=0;
		start_counters();
		while(1)		// Turn
		{
			m11=1;
			m12=m21=m22=0;
			if ( TL0>= 6)
			{
				m11=m12=m21=m22=0;
				TR0=0;
				break;	
			}		
		}
 // Driving side4
		m11=m12=m21=m22=0;
		start_counters();
		while(1)		
		{
			m11=m22=1;
			m12=m21=0;
			
			if(us_l == 1 || us_r == 1 || us_f == 1 || us_b == 1)
			{
				m11=m21=m12=m22=0;
				stepper_fire();
			}

			if(TL0 >= side4)
			{
				m11=m12=m21=m22=0;
				TR0=0;
				break;
			}
		}
		
// Turn 90* CW
		m11=m12=m21=m22=0;
		start_counters();
		while(1)		// Turn
		{
			m11=1;
			m12=m21=m22=0;
			if ( TL0>= 6)
			{
				m11=m12=m21=m22=0;
				TR0=0;
				break;	
			}		
		}
	}
	return;
}


void start_counters(void)
{
	TH0=0;
	TL0=0;
	TF0=0;
	TR0=1;

	return;
}

/////////////////////////////////////////////////////////////////////////
void lcdcmd(unsigned char value)	           // Sending Commands to LCD
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
void lcddata(unsigned char value)	               // Sending Data to LCD
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
void lcdready(void)	    	 // Checking wether LCD is busy, if yes wait!
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
	P1=0x00;
	col=col & 0xF0;
	col=col | 0x0F;
	while(1)
	{
		do
		{
			row=0x00;
			c=col;
			c&=0x0F;
		}		
		while(c!=0x0F);	//
		
		do
		{
			do
			{
				delay(20);
				c=col;
				c&=0x0F;//
			}
			while(c==0x0F);//
			
			delay(20);
			c=col;
			c&=0x0F;//
		}
		while(c==0x0F);//

		while(1)
		{
			row=0xfe;
			c=col;
			c&=0x0F;//
			if(c!=0x0F)//
			{
				r=0;
				break;
			}

			row=0xfd;
			c=col;
			c&=0x0F;//
			if(c!=0x0F)//
			{
				r=1;
				break;
			}

			row=0xfb;
			c=col;
			c&=0x0F;//
			if(c!=0x0F)//
			{
				r=2;
				break;
			}

			row=0xf7;
			c=col;
			c&=0x0F;//
			r=3;
			break;
		}
	
		if(c==0x0e)
		{
			x=keypad[r][0];
		}
		else if(c==0x0d)
		{
			x=keypad[r][1];
		}
		else if(c==0x0b)
		{
			x=keypad[r][2];
		}
		else
		{
			x=keypad[r][3];
		}
		return x;
	}
}
/////////////////////////////////////////////////////////////////////////
void delay(unsigned int z)
{	
	for(z=1;z<=900;z++);
	return;
}
/////////////////////////////////////////////////////////////////////////
void stepper_fire(void)
{
	if (us_l==1)
	{
  		SBUF = 3;
  		while(TI==0);
  		TI=0;

		while(1)
		{
  			while(RI==0);
  			RI=0;
			if(SBUF==9)
		 	break;
		}

  		while(us_l==1);
 	}

 	if (us_r==1)
 	{
  		SBUF = 1;
	 	while(TI==0);
  		TI=0;

		while(1)
		{
  			while(RI==0);
  			RI=0;
			if(SBUF==9)
		 	break;
		}

  		while(us_r==1);
 	}

 	if (us_f==1)
 	{
  		SBUF = 0;
  		while(TI==0);
  		TI=0;

		while(1)
		{
  			while(RI==0);
  			RI=0;
			if(SBUF==9)
		 	break;
		}

  		while(us_f==1);
 	}

 	if (us_b==1)
 	{
  		SBUF = 2;
  		while(TI==0);
  		TI=0;

		while(1)
		{
  			while(RI==0);
  			RI=0;
			if(SBUF==9)
		 	break;
		}

  		while(us_b==1);
 	}
	return;
}