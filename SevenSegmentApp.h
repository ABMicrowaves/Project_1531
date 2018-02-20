/*******************************************************************************
File name: SevenSegmentApp.h                                                ****
File description:   7 Segment display application manager                   ****
MCU:                PIC18F45k22                                             ****
Date modified: 06/02/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
*******************************************************************************/

#ifndef SEVENSEGMENTAPP_H
#define	SEVENSEGMENTAPP_H

#include "SystemCommon.h"

#define SegOne   0x01
#define SegTwo   0x02
#define SegThree 0x04
#define SegFour  0x08

void segmentCounter(void);
unsigned short mask(unsigned short num); 
void InitSevenSegment(void);

#endif	/* SEVENSEGMENTAPP_H */

