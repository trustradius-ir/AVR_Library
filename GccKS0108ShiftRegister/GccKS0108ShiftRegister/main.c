/*
 * KS0180.h
 *
 * Created: 28/08/1397 07:14:59 ق.ظ
 *  Author: a.nourbakhsh
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "KS0108.h"
#include "KS0108_Fonts.h"

int main(void)
{		
	GraphicLCD_KS0108_InitLCD();
	GraphicLCD_KS0108_BackLight(1);
	
	GraphicLCD_KS0108_SendByte(255,0,0);
	GraphicLCD_KS0108_SendByte(255,1,0);
	GraphicLCD_KS0108_SendByte(255,65,5);
	GraphicLCD_KS0108_SendByte(255,66,5);
	
	unsigned char PositionX = 0;
	
	PositionX = GraphicLCD_KS0108_SendString("Volt:",font5x7,0,0);
	
	float voltage = 31.22;
	GraphicLCD_KS0108_FloatNumber(voltage,font5x7,2,PositionX,0);
	
	
	PositionX = GraphicLCD_KS0108_SendString("Amper:",font5x7,0,4);

	GraphicLCD_KS0108_FloatNumber(voltage,font5x7,2,PositionX,4);	
	
	
	_delay_ms(100);
	for (char i =0;i<=100;i++)
	{
		GraphicLCD_KS0108_ProgressBar(i,100,128,0,5);
		_delay_ms(10);
	}
	
    while (1) 
    {
    }
}

