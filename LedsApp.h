/*******************************************************************************
File name: LedsApp.h                                                        ****
File description:   Leds driver application manager.                        ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
*******************************************************************************/

#ifndef LEDSAPP_H
#define	LEDSAPP_H

#include "SystemCommon.h"

#define LEDS_TEST_NUM_TOGGLING 10
#define LEDS_TEST_DELAY_MSEC 50

#define LEDS_INDICATTION_DELAY_MSEC 100

#define RED_LED LATBbits.LATB4
#define GREEN_LED LATCbits.LATC0

typedef enum
// OK system operation state:
{    
    OK_START_SYSTEM             = 0x3,            
} LED_OK_INTICATION;

typedef enum
// Fail system operation state:
{
    FAIL_UART_ACK_NOT_RECIEVE   = 0x2,
    FAIL_FLASH_MORE_THEN_HELF   = 0x4,
    FAIL_SYNTH_UP_LATCH         = 0x8,
} LED_ERR_INTICATION;

void testLeds();
void BlinkErrorLeds(LED_OK_INTICATION state);
void BlinkOkLeds(LED_ERR_INTICATION state);
void keepAliveSignalLed(void);

#endif	/* LEDSAPP_H */

