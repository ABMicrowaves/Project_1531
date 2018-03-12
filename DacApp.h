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

#define DAC_TEST_DELAY_MSEC (20)
#define NUM_OF_DACS         (4)

const uint8_t DAC_ADDRES[NUM_OF_DACS] = 
{
    0x0,        // DAC-A address
    0x2,        // DAC-B address
    0x4,        // DAC-C address
    0x8,        // DAC-D address
};

const uint16_t DAC_DEFAULT_INIT_VALUES[NUM_OF_DACS] = 
{
    0x2344,        // DAC-A address
    0x6344,        // DAC-B address
    0xA344,        // DAC-C address
    0xE344,        // DAC-D address
};

void DacInit(void);
void DacSetValue(char* data);

// Test functions
void DacTest(void);

#endif	/* DACAPP_H */