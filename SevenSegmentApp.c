/*******************************************************************************
File name: SevenSegmentApp.c                                                ****
File description:   7 Segment display application manager                   ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
****************************************************************************** */

#include "SevenSegmentApp.h"

unsigned int cnt;


void InitSevenSegment()
{
    ANSELA = 0;                    // Configure PORTA pins as digital
    ANSELD = 0;                    // Configure PORTD pins as digital

    TRISA = 0;                     // Configure PORTA as output
    LATA  = 0;                     // Clear PORTA
    TRISD = 0;                     // Configure PORTD as output
    LATD  = 0;                     // Clear PORTD
    
    cnt = 1;
}

unsigned short mask(unsigned short num) 
{
  switch (num) 
  {
    case 0 : return 0x3F;                                
    case 1 : return 0x06;
    case 2 : return 0x5B;
    case 3 : return 0x4F;
    case 4 : return 0x66;
    case 5 : return 0x6D;
    case 6 : return 0x7D;
    case 7 : return 0x07;
    case 8 : return 0x7F;
    case 9 : return 0x6F;
  } //case end
}

void segmentCounter()
{
    cnt++;
    cnt %= 10;
    
    LATA = SegOne;
    PORTD = mask(cnt);  
}
