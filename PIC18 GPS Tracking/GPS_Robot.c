////////////////////////////////////////////////////////
//                GPS Tracking Robot                  //
//                    FYP 2013                        //
//       Mechatronics and Control Engineering         //
//  University of Engineering and Technology, Lahore  //
//  F  A  I  S  A  L  A  B  A  D    C  A  M  P  U  S  //
////////////////////////////////////////////////////////

#define PB1 PORTD.F1
#define PB2 PORTD.F2

#define rb PORTC.F0
#define rf PORTC.F1
#define lf PORTC.F2
#define lb PORTC.F3

unsigned long north;
unsigned long east;
unsigned long north1;
unsigned long east1;
unsigned long north2;
unsigned long east2;
unsigned long north3;
unsigned long east3;

unsigned char raw_data[37];
unsigned char loop;
unsigned char x;
unsigned char gps_status;

void GPS (void)
{
  // Reading only $GPRMC data
  if(Usart_Data_Ready() );  {  if ( Usart_Read() == '$'){
  while(!Usart_Data_Ready() ); if ( Usart_Read() == 'G'){
  while(!Usart_Data_Ready() ); if ( Usart_Read() == 'P'){
  while(!Usart_Data_Ready() ); if ( Usart_Read() == 'R'){
  while(!Usart_Data_Ready() ); if ( Usart_Read() == 'M'){
  while(!Usart_Data_Ready() ); if ( Usart_Read() == 'C'){
  ///////////////////////////////////////////////////////
  // Storing only interested data in an array
  for(loop=0; loop<=37; loop++)
  {
   while(!Usart_Data_Ready() );
   raw_data[loop] = Usart_Read();
  }
  Lcd_Cmd(LCD_CLEAR);
  // Extracting and displaying North
  Lcd_Cmd(LCD_FIRST_ROW);
  for(loop=14; loop<=24; loop++)
  {
   Lcd_Chr_Cp( raw_data[loop] );
  }
  // Extracting and displaying East
  Lcd_Cmd(LCD_SECOND_ROW);
  for(loop=26; loop<=37; loop++)
  {
   Lcd_Chr_Cp( raw_data[loop] );
  }
  ///////////////////////////////////////////////////////
  gps_status=1;                                   }}}}}}}
}

void extraction(void)
{
 if(!PB1)
 {
  unsigned long cons;
  // Extracting North in Decimal Format
  north = 0;
  cons  = 10000000;
  for(loop=14; loop<=(24-2); loop++)
  {
   if(raw_data[loop]!='.')
   {
    raw_data[loop] = raw_data[loop] & 0x0F; // Changing to binary
    raw_data[loop] = raw_data[loop] * cons; // Multiply with specific weight
    north = north + raw_data[loop];         // Storing North
    cons /= 10;                             // Decreasing weight
   }
   else
    cons /= 10;
  }
  // Extracting South in Decimal Format
  east = 0;
  cons  = 100000000;
  for(loop=26; loop<=(37-2); loop++)
  {
   if(raw_data[loop]!='.')
   {
    raw_data[loop] = raw_data[loop] & 0x0F; // Changing to binary
    raw_data[loop] = raw_data[loop] * cons; // Multiply with specific weight
    east = east + raw_data[loop];           // Storing North
    cons /= 10;                             // Decreasing weight
   }
   else
    cons /= 10;
  }
  //////////////////////////////////////////////////////////////////////
   if(!PB1 && x==0)
   {
    x++;
    north1 = north;
    east1 = north;
    while(!PB1);
   }
   if(!PB1 && x==1)
   {
    x++;
    north2 = north;
    east2 = east;
    while(!PB1);
   }
   if(!PB1 && x==2)
   {
    x++;
    north3 = north;
    east3 = east;
    while(!PB1);
   }
  }
  /////////////////////////////////////////////////////////////////////////////////
}

void main(void)
{
 unsigned long error_north;
 unsigned long error_east;
 TRISB=0X00;
 TRISC=0X80;
 TRISD=0xFF;
 rb = rf = lb = lf = 1;
 x=0;
 gps_status=0;
 Usart_Init(4800);
 Lcd_Init(&PORTB);
 Lcd_Cmd(LCD_CURSOR_OFF);
 Lcd_Out(1,4,"GPS  ROBOT");
 Lcd_Out(2,3,"UET LHR, FSD");
 Delay_1sec();Delay_1sec();Delay_1sec();
 Lcd_Cmd(LCD_CLEAR);
 while(1)
 {
  while(1)
  {
   while(gps_status==0)
   {
    GPS();
   }
   gps_status=0;
   extraction();
   if (x==3)
   {
    break;
   }
  }
  x=0;
  while(PB2);
  Lcd_Cmd(LCD_CLEAR);
  while(1)
  {
   Lcd_Out(1,1,"STARTED MOVING");
   // Tracking: Point1 -> Point2
   while(gps_status==0)
   {
    GPS();
   }
   gps_status=0;
   extraction();
   error_north = north1 - north;
   error_east = east1 - east;
   lf=0;
   rf=0;
   if (error_north <= 20 || error_east <= 20)
   {
    lf=rf=1;
    break;
   }
  }
  // Tracking: Point2 -> Point1
  while(1);
 }
}