/*
Title:    ANSI library For UART
Author:   Alireza Nourbakhsh <a.nourbakhsh@iaus.ac.ir>   https://github.com/sasharadius
File:     $Id: ansi.c,v 1.0 2018/09/25 $
Hardware: any AVR with built-in UART Console
License:  GNU General Public License 
          
DESCRIPTION:
    An interrupt is generated when the UART has finished transmitting or
    receiving a byte. The interrupt handling routines use circular buffers
    for buffering received and transmitted data.
    
    The UART_RX_BUFFER_SIZE and UART_TX_BUFFER_SIZE variables define
    the buffer size in bytes. Note that these variables must be a 
    power of 2.
    
USAGE:
    Refer to the header file uart.h for a description of the routines. 
    See also example test_uart.c.

NOTES:
    Based on Atmel Application Note AVR306
                    
LICENSE:
    Copyright (C) 2015 Alireza Nourbakhsh, GNU General Public License Version 3

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
                        
*************************************************************************/
#include <stdio.h>
#include <string.h>
#include "ansi.h"
#include "uart.h"

void ansi_setscreenmode(int8_t mode)
{
	char Buffer[10];
	sprintf(Buffer,"\e[=%i;7h",mode);
	uart_puts(Buffer);
}

void ansi_clearscreen(void)
{
	char Buffer[10];
	sprintf(Buffer,"\e[2J");
	uart_puts(Buffer);
}

void ansi_clearendofline(void)
{
	char Buffer[10];
	sprintf(Buffer,"\e[K");
	uart_puts(Buffer);
}


void ansi_movescursor_to(int8_t x,int8_t y)
{
	char Buffer[10];
	sprintf(Buffer,"\e[%i;%iH",y,x);
	uart_puts(Buffer);
}

void ansi_movescursor_up(int8_t line)
{
	char Buffer[10];
	sprintf(Buffer,"\e[%iA",line);
	uart_puts(Buffer);
}

void ansi_movescursor_down(int8_t line)
{
	char Buffer[10];
	sprintf(Buffer,"\e[%iB",line);
	uart_puts(Buffer);
}

void ansi_movescursor_right(int8_t space)
{
	char Buffer[10];
	sprintf(Buffer,"\e[%iC",space);
	uart_puts(Buffer);
}

void ansi_movescursor_left(int8_t space)
{
	char Buffer[10];
	sprintf(Buffer,"\e[%iD",space);
	uart_puts(Buffer);
}

void ansi_savecursor_position(void)
{
	char Buffer[10];
	sprintf(Buffer,"\e[s");
	uart_puts(Buffer);
}


void ansi_restorecursor_position(void)
{
	char Buffer[10];
	sprintf(Buffer,"\e[u");
	uart_puts(Buffer);
}

void ansi_set_attrcolor(int8_t attribute,int8_t color)
{
	char Buffer[10];
	sprintf(Buffer,"\e[%i;%im",attribute,color);
	uart_puts(Buffer);
}

void ansi_set_attrcolorbc(int8_t attribute,int8_t fcolor,int8_t bcolor)
{
	char Buffer[10];
	sprintf(Buffer,"\e[%i;%i;%im",attribute,fcolor,bcolor);
	uart_puts(Buffer);
}


void ansi_write_xcenter(int8_t y,char data[])
{
	int8_t x;
	x = (80 / 2) - (strlen(data) / 2);
	char Buffer[10];
	sprintf(Buffer,"\e[%i;%iH",y,x);
	uart_puts(Buffer);
	uart_puts(data);
}

void ansi_write_ycenter(int8_t x,char data[])
{
	int8_t y;
	y = (25 / 2) - (strlen(data) / 2);
	char Buffer[10];
	sprintf(Buffer,"\e[%i;%iH",y,x);
	uart_puts(Buffer);
	uart_puts(data);
}

void ansi_write_pos(int8_t x,int8_t y,char data[])
{
	char Buffer[10];
	sprintf(Buffer,"\e[%i;%iH",y,x);
	uart_puts(Buffer);
	uart_puts(data);
}

void ansi_write(char data[])
{
	uart_puts(data);
}

void ansi_writeloop(char data[],int8_t loop)
{
	for (int i = 0 ;i  < loop;i++)
		ansi_write(data);
		
}


void ansi_draw_box(int8_t chartype,int8_t x1,int8_t y1,int8_t x2,int8_t y2)
{
	char horiz[2] = {179,0};
	char vert[2] = {179,0};
	char up_right[2] = {179,0};
	char up_left[2] = {179,0};
	char dw_left[2] = {179,0};
	char dw_right[2] = {179,0};
	
	if (chartype == 0) 
	{
		horiz[0] = 0xb0;
		vert[0] = 0xb0;
		up_left[0] = 0xb0;
		up_right[0] = 0xb0;
		dw_left[0] = 0xb0;
		dw_right[0] = 0xb0;
	}
	
	if (chartype == 1)
	{
		horiz[0] = 0xb1;
		vert[0] = 0xb1;
		up_left[0] = 0xb1;
		up_right[0] = 0xb1;
		dw_left[0] = 0xb1;
		dw_right[0] = 0xb1;
	}	

	if (chartype == 2)
	{
		horiz[0] = 0xb2;
		vert[0] = 0xb2;
		up_left[0] = 0xb2;
		up_right[0] = 0xb2;
		dw_left[0] = 0xb2;
		dw_right[0] = 0xb2;
	}
	
	
	if (chartype == 3)
	{
		horiz[0] = 0xc4;
		vert[0] = 0xb3;
		up_left[0] = 0xda;
		up_right[0] = 0xbf;
		dw_left[0] = 0xc0;
		dw_right[0] = 0xd9;
	}	
	
	if (chartype == 4)
	{
		horiz[0] = 0xcd;
		vert[0] = 0xba;
		up_left[0] = 0xc9;
		up_right[0] = 0xbb;
		dw_left[0] = 0xc8;
		dw_right[0] = 0xbc;
	}
	

		
	
	int addchar = 0;
	if (y1 != y2 && x1 != x2)
	{
		ansi_movescursor_to(x1,y1);
		ansi_write(up_left);		
		addchar = 1;
	}
		
	ansi_movescursor_to(x1+addchar,y1);
	ansi_writeloop(horiz,x2-x1-addchar);
	
	if (y1 != y2 && x1 != x2)
	{	
		ansi_movescursor_to(x2,y1);
		ansi_write(up_right);
	}
	
	for (int y = y1 + 1 ;y  < y2;y++)
	{
		ansi_movescursor_to(x1,y);
		ansi_write(vert);
		ansi_movescursor_to(x2,y);
		ansi_write(vert);
	}
	
	if (y1 != y2 && x1 != x2)
	{	
		ansi_movescursor_to(x1,y2);
		ansi_write(dw_left);
	}
	
	ansi_movescursor_to(x1+addchar,y2);
	ansi_writeloop(horiz,x2-x1-addchar);
	
	if (y1 != y2 && x1 != x2)
	{	
		ansi_movescursor_to(x2,y2);
		ansi_write(dw_right);
	}
}