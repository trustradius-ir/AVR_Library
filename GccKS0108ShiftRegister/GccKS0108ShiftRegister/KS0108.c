/*
 * KS0108.c
 *
 * Created: 28/08/1397 07:13:10 ق.ظ
 *  Author: a.nourbakhsh
 */ 



#include "KS0108.h"


#ifndef ReserveRegister
#define ReserveRegister 5
#endif

//ShiftRegisterData
uint16_t ShiftRegisterData;
#define ClearShiftRegisterData() ShiftRegisterData = 0
//SHCP
#define SetSHCP()	SHCP_PORT |= _BV(SHCP_PORT_BIT)
#define ClearSHCP()	SHCP_PORT &= ~_BV(SHCP_PORT_BIT)
//DS
#define SetDS()	DS_PORT |= _BV(DS_PORT_BIT)
#define ClearDS()	DS_PORT &= ~_BV(DS_PORT_BIT)
//STCP
#define SetSTCP()	STCP_PORT |= _BV(STCP_PORT_BIT)
#define ClearSTCP()	STCP_PORT &= ~_BV(STCP_PORT_BIT)
//MR
#define SetMR()	MR_PORT |= _BV(MR_PORT_BIT)
#define ClearMR()	MR_PORT &= ~_BV(MR_PORT_BIT)

int InitializeShiftRegister()
{	
	//Set ShiftRegiste Command Port as OUTPUT
	SHCP_PORT_DDR |= _BV(SHCP_PORT_BIT);
	DS_PORT_DDR |= _BV(DS_PORT_BIT);
	STCP_PORT_DDR |= _BV(STCP_PORT_BIT);
	MR_PORT_DDR |= _BV(MR_PORT_BIT);	
	
	//Reset ShiftRegister
	SetMR();
	ClearMR();
	SetMR();	
	return 0;
};

void ShiftRegisterUpdate()
{

	for (int8_t BitNum = 7 ; BitNum >= 0 ; BitNum--)
	{
		uint8_t BitValue =	(((uint8_t)(ShiftRegisterData >> 8)) & _BV(BitNum));
		if (BitValue == 0)
		{
			ClearDS();
			SetSHCP();
			ClearSHCP();
		}
		else
		{
			SetDS();
			SetSHCP();
			ClearSHCP();
			ClearDS();
		}
	}
	
	
	
	for (int8_t BitNum = 7 ; BitNum >= 0 ; BitNum--)
	{
		uint8_t BitValue =	(ShiftRegisterData & _BV(BitNum));
		if (BitValue == 0)
		{
			ClearDS();
			SetSHCP();
			ClearSHCP();
		}
		else
		{
			SetDS();
			SetSHCP();
			ClearSHCP();
			ClearDS();
		}
	}	
	SetSTCP();
	ClearSTCP();
}

void ShiftRegisterSet(uint16_t Bitumber,uint8_t BitStatus)
{
	if (BitStatus == 0)
		ShiftRegisterData &= ~( 1 << Bitumber );
	else
		ShiftRegisterData |= ( 1 << Bitumber );
}


void SetDATA(uint8_t LCDData)
{
	
	for (uint8_t BitNum = 0; BitNum <= 7 ; BitNum++)
	{
		uint8_t BitValue =	(LCDData & _BV(BitNum));
		uint8_t ShiftBitNum = 0;
		if (BitNum == 0) ShiftBitNum = PIN_Data0;
		if (BitNum == 1) ShiftBitNum = PIN_Data1;
		if (BitNum == 2) ShiftBitNum = PIN_Data2;
		if (BitNum == 3) ShiftBitNum = PIN_Data3;
		if (BitNum == 4) ShiftBitNum = PIN_Data4;
		if (BitNum == 5) ShiftBitNum = PIN_Data5;
		if (BitNum == 6) ShiftBitNum = PIN_Data6;
		if (BitNum == 7) ShiftBitNum = PIN_Data7;
		
		if (BitValue == 0)
			ShiftRegisterSet(ShiftBitNum,0);
		else
			ShiftRegisterSet(ShiftBitNum,1);
	}	
	
	ShiftRegisterUpdate();	
}

void  SetBackLight()	{ShiftRegisterSet(PIN_BLIGHT,1); ShiftRegisterUpdate();}
void  SetRST()			{ShiftRegisterSet(PIN_RST,1); ShiftRegisterUpdate();}
void  SetE()			{ShiftRegisterSet(PIN_E,1); ShiftRegisterUpdate();}	
void  SetRS()			{ShiftRegisterSet(PIN_RS,1); ShiftRegisterUpdate();}
void  SetRW()			{ShiftRegisterSet(PIN_RW,1); ShiftRegisterUpdate();}	
void  SetCS1()			{ShiftRegisterSet(PIN_CS1,1); ShiftRegisterUpdate();}
void  SetCS2()			{ShiftRegisterSet(PIN_CS2,1); ShiftRegisterUpdate();}

void  ClrBackLight()	{ShiftRegisterSet(PIN_BLIGHT,0); ShiftRegisterUpdate();}		
void  ClrRST()			{ShiftRegisterSet(PIN_RST,0); ShiftRegisterUpdate();}
void  ClrE()			{ShiftRegisterSet(PIN_E,0); ShiftRegisterUpdate();}
void  ClrRS()			{ShiftRegisterSet(PIN_RS,0); ShiftRegisterUpdate();}
void  ClrRW()			{ShiftRegisterSet(PIN_RW,0); ShiftRegisterUpdate();}
void  ClrCS1()			{ShiftRegisterSet(PIN_CS1,0); ShiftRegisterUpdate();}
void  ClrCS2()			{ShiftRegisterSet(PIN_CS2,0); ShiftRegisterUpdate();}	

// Chips
#define CHIP1				0x00
#define CHIP2				0x01

// Commands
#define LCD_ON				0x3F
#define LCD_OFF				0x3E
#define LCD_SET_ADD			0x40
#define LCD_SET_PAGE		0xB8
#define LCD_DISP_START		0xC0

#define KS0108_SCREEN_HOR_SIZE    128
#define KS0108_SCREEN_VER_SIZE    64

void Latch(void)
{
	_delay_us(10);
	SetE();
	_delay_us(10);
	ClrE();
}

void GraphicLCD_KS0108_InitLCD(void)
{
	InitializeShiftRegister();
	
	ShiftRegisterUpdate();
		
	SetDATA(0);
	SetRST();
	SetE();
	SetRS();
	SetRW();
	SetCS1();
	SetCS2();
	
	ClrRST();
	_delay_ms(10);
	SetRST();
	_delay_ms(100);
	ClrRS();

	ClrCS1();
	SetCS2();
	SetDATA(LCD_OFF);
	Latch();
	SetDATA(LCD_SET_ADD);
	Latch();
	SetDATA(LCD_SET_PAGE);
	Latch();
	SetDATA(LCD_DISP_START);
	Latch();
	SetDATA(LCD_ON);
	Latch();

	SetCS1();
	ClrCS2();
	SetDATA(LCD_OFF);
	Latch();
	SetDATA(LCD_SET_ADD);
	Latch();
	SetDATA(LCD_SET_PAGE);
	Latch();
	SetDATA(LCD_DISP_START);
	Latch();
	SetDATA(LCD_ON);
	Latch();	
}


void GraphicLCD_KS0108_BackLight(uint8_t OnOff)
{
	if (OnOff == 0)
		ClrBackLight();
	else
		SetBackLight();
}
	


void GraphicLCD_KS0108_SendCMD(unsigned char Command)
{
	ClrRS();
	ClrRW();
	SetDATA(Command);
	Latch();
}

void GraphicLCD_KS0108_GotoXY(unsigned char PositionX , unsigned char PositionY)
{
	if ( PositionX >= 64 )
	{
		ClrCS1();
		SetCS2();
	}
	else
	{
		SetCS1();
		ClrCS2();
	}
	
	GraphicLCD_KS0108_SendCMD(LCD_SET_PAGE|PositionY);
	
	GraphicLCD_KS0108_SendCMD(LCD_SET_ADD|PositionX);

}

void GraphicLCD_KS0108_SendData(unsigned char Value)
{
	SetRS();
	ClrRW();
	SetDATA(Value);
	Latch();
}

void GraphicLCD_KS0108_SendByte(unsigned char Data , unsigned char PositionX , unsigned char PositionY )
{
	GraphicLCD_KS0108_GotoXY(PositionX,PositionY);
	GraphicLCD_KS0108_SendData(Data);
		
}


void GraphicLCD_KS0108_Clr(void)
{
	for(char i = 0 ; i < KS0108_SCREEN_HOR_SIZE ; i++ )
	for(char j = 0 ; j < KS0108_SCREEN_VER_SIZE/8 ; j++ )
	{
		GraphicLCD_KS0108_GotoXY(i,j);
		GraphicLCD_KS0108_SendData(0x00);
	}
}

		
void GraphicLCD_KS0108_ProgressBar(unsigned char progress, unsigned char maxprogress, unsigned char length,unsigned char x, unsigned char y)
{
	unsigned char i;
	unsigned int pixelprogress;
	GraphicLCD_KS0108_GotoXY(x,y);
	GraphicLCD_KS0108_SendData(0xff);
	GraphicLCD_KS0108_SendData(0x81);

	pixelprogress = ((progress*length)/maxprogress);
	for(i=2; i<length; i++)
	{
		GraphicLCD_KS0108_GotoXY(x+i,y);
		if ( i > pixelprogress )GraphicLCD_KS0108_SendData(0x81);
		if ( i < pixelprogress )GraphicLCD_KS0108_SendData(0xbd);
	}
	GraphicLCD_KS0108_GotoXY(length-2,y);
	GraphicLCD_KS0108_SendData(0x81);
	GraphicLCD_KS0108_SendData(0xff);
	_delay_ms(1);
}


unsigned char GraphicLCD_KS0108_SendChar(unsigned int Character , const unsigned char *Font , unsigned int PositionX, unsigned int PositionY )
{
	unsigned char X_Resolution_Font = pgm_read_byte(Font);
	unsigned char Y_Resolution_Font = pgm_read_byte(Font + 1);
	unsigned char Start_AsciiCode_Font = pgm_read_byte(Font + 2);
	unsigned char LengthFont ,i , j ,CursorPositionX,CursorPositionY;
			
	Character -= Start_AsciiCode_Font ;
	Character *= (( X_Resolution_Font * (( Y_Resolution_Font / 8 ) + 1 )) + 1 );
	Character += ( ReserveRegister + 0 );

	LengthFont = pgm_read_byte ( Font + Character ) ;
	Character ++ ;
	//////////////////////////////////////////////////////////////////////////

		CursorPositionX  = PositionX ;
		CursorPositionY  = PositionY ;
		
		if (( Y_Resolution_Font % 8 ) != 0)
		{
			for( i = 0 ; i < LengthFont ; i ++ )
			{
				for( j = 0 ; j <= ( Y_Resolution_Font / 8 ) ; j ++ )
				{
					PositionX = CursorPositionX ;
					PositionY = CursorPositionY + ( j );
					GraphicLCD_KS0108_SendByte(pgm_read_byte(Font + Character ),PositionX, PositionY);
					Character ++ ;
				}
				CursorPositionX ++ ;
			}
		}
		else
		{
			for( i = 0 ; i < LengthFont ; i ++ )
			{
				for( j = 0 ; j < ( Y_Resolution_Font / 8 ) ; j ++ )
				{				
					PositionX = CursorPositionX ;
					PositionY = CursorPositionY + ( j  );
					GraphicLCD_KS0108_SendByte(0x00, PositionX , PositionY );
					Character ++ ;
				}
				CursorPositionX ++ ;
			}
		}


		for( j = 0 ; j < (( Y_Resolution_Font / 8 ) + 1 ) ; j ++ )
		{

			
			PositionX = CursorPositionX ;
			PositionY = CursorPositionY + ( j );
			GraphicLCD_KS0108_SendByte(0, CursorPositionX , PositionY);
			Character ++ ;
		}
		CursorPositionX ++ ;
		return CursorPositionX ;
}

unsigned char GraphicLCD_KS0108_SendString(char *String , const unsigned char *Font , unsigned char PositionX, unsigned int PositionY )
{
	unsigned char CursorPositionX  = PositionX ;
	while(*String)
	{
			
		CursorPositionX =  GraphicLCD_KS0108_SendChar(*String++ , Font , PositionX, PositionY);
		PositionX = CursorPositionX ;
	}
	return PositionX;
}

	
unsigned char GraphicLCD_KS0108_SendCharRight(unsigned int Character , const unsigned char *Font , unsigned char PositionX, unsigned char PositionY )
{
	unsigned char X_Resolution_Font = pgm_read_byte(Font);
	unsigned char Y_Resolution_Font = pgm_read_byte(Font + 1);
	unsigned char Start_AsciiCode_Font = pgm_read_byte(Font + 2);
	unsigned char LengthFont ,i , j ,CursorPositionX,CursorPositionY;
			
	Character -= Start_AsciiCode_Font ;
	Character *= (( X_Resolution_Font * (( Y_Resolution_Font / 8 ) + 1 )) + 1 );
	Character += ( ReserveRegister + 0 );

	LengthFont = pgm_read_byte ( Font + Character ) ;
	Character ++ ;
	//////////////////////////////////////////////////////////////////////////

		CursorPositionX  = PositionX - LengthFont ;
		CursorPositionY  = PositionY ;
		
		if (( Y_Resolution_Font % 8 ) != 0)
		{
			for( i = 0 ; i < LengthFont ; i ++ )
			{
				for( j = 0 ; j <= ( Y_Resolution_Font / 8 ) ; j ++ )
				{
					PositionX = CursorPositionX ;
					PositionY = CursorPositionY + ( j );
					GraphicLCD_KS0108_SendByte(pgm_read_byte(Font + Character ),PositionX, PositionY);
					Character ++ ;
				}
				CursorPositionX ++ ;
			}
		}
		else
		{
			for( i = 0 ; i < LengthFont ; i ++ )
			{
				for( j = 0 ; j < ( Y_Resolution_Font / 8 ) ; j ++ )
				{
					PositionX = CursorPositionX ;
					PositionY = CursorPositionY + ( j  );
					GraphicLCD_KS0108_SendByte(0x00, PositionX , PositionY );
					Character ++ ;
				}
				CursorPositionX ++ ;
			}
		}
		return ( CursorPositionX - LengthFont ) ;
}

unsigned char GraphicLCD_KS0108_SendStringRight(unsigned char String[] , const unsigned char *Font , unsigned char PositionX, unsigned char PositionY )
{
	unsigned char CursorPositionX  = PositionX ;
	unsigned char i = 0 ;
	while(String[i])
	{
			
		CursorPositionX = GraphicLCD_KS0108_SendCharRight(String[i] , Font , PositionX, PositionY);
		PositionX = CursorPositionX ;
		i++;
	}
	return PositionX;
}

unsigned int GraphicLCD_KS0108_VariableDec(uint32_t Number , const unsigned char *Font , unsigned char length, unsigned char X, unsigned char Y )
{
	unsigned char i=0;
	unsigned char b;
	unsigned char k[16];
	unsigned int CursorPositionX = X ;
	while(i<16){k[i]=48;i++;}
	i=0;
	
	do
	{
		b=Number%10;
		k[i] = 48 +b;
		Number /= 10;
		i++;
	}
	while (Number != 0);
	i=length;
	while (i != 0 )
	{
		i--;
		CursorPositionX = GraphicLCD_KS0108_SendChar(k[i],Font,CursorPositionX,Y);
	}
	return CursorPositionX ;
}

unsigned int GraphicLCD_KS0108_FloatNumber(float v_floatNumber_f32 , const unsigned char *Font ,unsigned char length, unsigned int X, unsigned int Y)
{
	uint32_t v_tempNumber_u32;
	unsigned char CursorPositionX  = X ;

	v_tempNumber_u32 = (uint32_t) v_floatNumber_f32;
	CursorPositionX = GraphicLCD_KS0108_VariableDec(v_tempNumber_u32,Font,length,CursorPositionX,Y);

	CursorPositionX = GraphicLCD_KS0108_SendChar('.',Font,CursorPositionX,Y); 

	v_floatNumber_f32 = v_floatNumber_f32 - v_tempNumber_u32 ;
	
	v_tempNumber_u32 = (uint32_t)round(v_floatNumber_f32 * pow(10,length));
	
	CursorPositionX = GraphicLCD_KS0108_VariableDec(v_tempNumber_u32,Font,length,CursorPositionX,Y);
	return CursorPositionX ;
}
