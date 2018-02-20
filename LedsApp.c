/*******************************************************************************
File name: LedsApp.c                                                        ****
File description:   Leds driver application manager.                        ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
****************************************************************************** */

#include "LedsApp.h"

// <editor-fold defaultstate="collapsed" desc="Leds system error / ok indications">

void BlinkErrorLeds (LED_ERR_INTICATION state)
{
       for(int idx = 0; idx < state; idx++)
    {
        RED_LED = 0;
        __delay_ms(LEDS_INDICATTION_DELAY_MSEC);
        RED_LED = 1;
        __delay_ms(LEDS_INDICATTION_DELAY_MSEC);
    } 
}

void BlinkOkLeds (LED_OK_INTICATION state)
{
    for(int idx = 0; idx < state; idx++)
    {
        GREEN_LED = 0;
        __delay_ms(LEDS_INDICATTION_DELAY_MSEC);
        GREEN_LED = 1;
        __delay_ms(LEDS_INDICATTION_DELAY_MSEC);
    }
}

void keepAliveSignalLed(void)
{
    GREEN_LED = !GREEN_LED;
}
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Leds EUSART test">

void testLeds(void)
{
    
    for(int idx = 0; idx < LEDS_TEST_NUM_TOGGLING; idx++)
    {
        
        GREEN_LED = 1;
        __delay_ms(LEDS_TEST_DELAY_MSEC);
        RED_LED = 1;
        __delay_ms(LEDS_TEST_DELAY_MSEC);
        GREEN_LED = 0;
        __delay_ms(LEDS_TEST_DELAY_MSEC);
        RED_LED = 0;
        __delay_ms(LEDS_TEST_DELAY_MSEC);
    }
    
    SendAckMessage((MSG_GROUPS)CONTROL_MSG, (MSG_REQUEST)CONTROL_TEST_LEDS);
    return;
}
// </editor-fold>
