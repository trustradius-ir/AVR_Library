/*
 * KS0108.h
 *
 * Created: 28/08/1397 07:14:59 ق.ظ
 *  Author: a.nourbakhsh
 */ 


#ifndef KS0180_H_
#define KS0180_H_

#ifndef F_CPU
# warning "F_CPU not defined for <util/delay.h>"
# define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>


//LCD PinOut
//Q0 = BackLightOn/Off
//Q1 = RS
//Q2 = RW
//Q3 = E
//Q4 = DB0
//Q5 = DB1
//Q6 = DB2
//Q7 = DB3

//Q0 = NotUsed
//Q1 = DB4
//Q2 = DB5
//Q3 = DB6
//Q4 = DB7
//Q5 = CS1
//Q6 = CS2
//Q7 = RST

#define SHCP_PORT_DDR DDRB
#define SHCP_PORT     PORTB
#define SHCP_PORT_BIT PORTB0

#define DS_PORT_DDR DDRB
#define DS_PORT     PORTB
#define DS_PORT_BIT PORTB1

#define STCP_PORT_DDR DDRB
#define STCP_PORT     PORTB
#define STCP_PORT_BIT PORTB2

#define MR_PORT_DDR DDRB
#define MR_PORT     PORTB
#define MR_PORT_BIT PORTB3

#define PIN_BLIGHT 0
#define PIN_RS 1
#define PIN_RW 2
#define PIN_E 3
#define PIN_Data0 4
#define PIN_Data1 5
#define PIN_Data2 6
#define PIN_Data3 7
#define PIN_Data4 9
#define PIN_Data5 10
#define PIN_Data6 11
#define PIN_Data7 12
#define PIN_CS1 13
#define PIN_CS2 14
#define PIN_RST 15


void GraphicLCD_KS0108_InitLCD(void);
void GraphicLCD_KS0108_BackLight(uint8_t OnOff);
void GraphicLCD_KS0108_GotoXY(unsigned char PositionX , unsigned char PositionY);
void GraphicLCD_KS0108_SendData(unsigned char Value);
void GraphicLCD_KS0108_SendByte(unsigned char Data , unsigned char PositionX , unsigned char PositionY );
void GraphicLCD_KS0108_Clr(void);
void GraphicLCD_KS0108_ProgressBar(unsigned char progress, unsigned char maxprogress, unsigned char length,unsigned char x, unsigned char y);
unsigned char GraphicLCD_KS0108_SendChar(unsigned int Character , const unsigned char *Font , unsigned int PositionX, unsigned int PositionY );
unsigned char GraphicLCD_KS0108_SendString(char *String , const unsigned char *Font , unsigned char PositionX, unsigned int PositionY );
unsigned char GraphicLCD_KS0108_SendCharRight(unsigned int Character , const unsigned char *Font , unsigned char PositionX, unsigned char PositionY );
unsigned char GraphicLCD_KS0108_SendStringRight(unsigned char String[] , const unsigned char *Font , unsigned char PositionX, unsigned char PositionY );
unsigned int GraphicLCD_KS0108_VariableDec(uint32_t Number , const unsigned char *Font , unsigned char length, unsigned char X, unsigned char Y );
unsigned int GraphicLCD_KS0108_FloatNumber(float v_floatNumber_f32 , const unsigned char *Font ,unsigned char length, unsigned int X, unsigned int Y);



#endif /* KS0180_H_ */