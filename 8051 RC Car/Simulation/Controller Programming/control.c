//***************************************************//
///////////////////////////////////////////////////////
//            COMPUTER CONTROLLED, RC CAR            //
///////////////////////////////////////////////////////
//***************************************************//

#include <REGX51.H>
//*************************************************** RESPECTIVE OUTPUT
sbit oforward=P0^0;
sbit oreverse=P0^1;
sbit oleft=P0^2;
sbit oright=P0^3;
//*************************************************** RESPECTIVE INPUT
sbit iforward=P3^2;
sbit ireverse=P3^3;
sbit ileft=P3^4;
sbit iright=P3^5;
//*************************************************** STORING CURRENT STARUS OF PORT, USED TO LET THE CONTREOLLER WAIT
unsigned char x;
/////////////////////////////////////////////////////
void main (void)
{
	P0=P1=P2=P3=0x00;

	if (iforward==1)
	{
		oforward=1;
	}
	if (ireverse==1)
	{
		oreverse=1;
	}
	if (ileft==1)
	{
		oleft=1;
	}
	if (iright==1)
	{
		oright=1;
	}
	x=P3;
	while(P3==x);
}