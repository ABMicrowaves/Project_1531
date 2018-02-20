/*******************************************************************************
File name: AdcApp.h                                                         ****
File description:   D2A driver application manager for AD5312 external chip ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
*******************************************************************************/

#ifndef DACAPP_H
#define	DACAPP_H

#include "SystemCommon.h"
#include <math.h>

#define DAC_BYTES_IN_VAL    5       // [X.YZW VDC]

#define VSOURCEPLUS         5500    // V referance in mili volts
#define VSOURCEMINUS        0
#define DAC_BITS            10
//#define RESOLUTION (VREF / pow(2,DAC_BITS))

#define DAC_TEST_DELAY_MSEC 20

void DacSetValue(char* data);

// Test functions
void DacTest(void);



#endif	/* DACAPP_H */

