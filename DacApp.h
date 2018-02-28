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

// At system start: set all DACs to 1 VDC.
#define DAC_A_INIT_VAL      (0x2344)
#define DAC_B_INIT_VAL      (0x6344)
#define DAC_C_INIT_VAL      (0xA344)
#define DAC_D_INIT_VAL      (0xE344)

#define DAC_TEST_DELAY_MSEC 20

void DacInit(void);
void DacSetValue(char* data);

// Test functions
void DacTest(void);

#endif	/* DACAPP_H */