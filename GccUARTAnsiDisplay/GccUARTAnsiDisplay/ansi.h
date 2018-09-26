/*
Title:    ANSI library For UART
Author:   Alireza Nourbakhsh <a.nourbakhsh@iaus.ac.ir>   https://github.com/sasharadius
File:     $Id: ansi.h,v 1.0 2018/09/25 $
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


#ifndef ANSI_H_
#define ANSI_H_

#define ANSI_ATR_NORMAL 0
#define ANSI_ATR_BOLD 1
#define ANSI_ATR_UNDERLINE 4
#define ANSI_ATR_BLINKON 5
#define ANSI_ATR_REVVIDEO 6
#define ANSI_ATR_NONDISP 7

#define ANSI_FC_BLACK 30
#define ANSI_FC_RED 31
#define ANSI_FC_GREEN 32
#define ANSI_FC_YELLOW 33
#define ANSI_FC_BLUE 34
#define ANSI_FC_MAGENTA 35
#define ANSI_FC_CYAN 36
#define ANSI_FC_WHITE 37

#define ANSI_BC_BLACK 40
#define ANSI_BC_RED 41
#define ANSI_BC_GREEN 42
#define ANSI_BC_YELLOW 43
#define ANSI_BC_BLUE 44
#define ANSI_BC_MAGENTA 45
#define ANSI_BC_CYAN 46
#define ANSI_BC_WHITE 47

#define ANSI_CT_FILL1 0
#define ANSI_CT_FILL2 1
#define ANSI_CT_FILL3 2
#define ANSI_CT_SINGLE 3
#define ANSI_CT_DOUBLE 4

/**
 *  @brief   Put string to ringbuffer for transmitting via UART
 *
 *  The string is buffered by the uart library in a circular buffer
 *  and one character at a time is transmitted to the UART using interrupts.
 *  Blocks if it can not write the whole string into the circular buffer.
 * 
 *  @param   s string to be transmitted
 *  @return  none
 */
extern void ansi_setscreenmode(int8_t mode);
extern void ansi_clearscreen(void);
extern void ansi_clearendofline(void);
extern void ansi_movescursor_to(int8_t x,int8_t y);
extern void ansi_movescursor_up(int8_t line);
extern void ansi_movescursor_down(int8_t line);
extern void ansi_movescursor_right(int8_t space);
extern void ansi_movescursor_left(int8_t space);
extern void ansi_savecursor_position(void);
extern void ansi_restorecursor_position(void);
extern void ansi_set_attrcolor(int8_t attribute,int8_t color);
extern void ansi_set_attrcolorbc(int8_t attribute,int8_t fcolor,int8_t bcolor);
extern void ansi_write_xcenter(int8_t y,char data[]);
extern void ansi_write_ycenter(int8_t x,char data[]);
extern void ansi_write_pos(int8_t x,int8_t y,char data[]);
extern void ansi_write(char data[]);
extern void ansi_writeloop(char data[],int8_t loop);
extern void ansi_draw_box(int8_t chartype,int8_t x1,int8_t y1,int8_t x2,int8_t y2);

#endif /* ANSI_H_ */