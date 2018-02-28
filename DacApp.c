/*******************************************************************************
File name: AdcApp.h                                                         ****
File description:   D2A driver application manager for AD5312 external chip ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
*******************************************************************************/

#include "DacApp.h"

// <editor-fold defaultstate="collapsed" desc="DAC test">

void DacTest(void)
{
    int count = 0;
    for(count=0; count<=25; count++)
    {
        //DAC_SetOutput(count);
        __delay_ms(DAC_TEST_DELAY_MSEC);
    }
}
// </editor-fold>

void DacInit(void)
{
    SWSPI_send_word(EXT_DAC, DAC_A_INIT_VAL, 1);
    SWSPI_send_word(EXT_DAC, DAC_B_INIT_VAL, 1);
    SWSPI_send_word(EXT_DAC, DAC_C_INIT_VAL, 1);
    SWSPI_send_word(EXT_DAC, DAC_D_INIT_VAL, 1);
}
// <editor-fold defaultstate="collapsed" desc="DAC Convert">

void DacSetValue(char* data)
{
    uint16_t regData = GetIntFromUartData(data);
    SWSPI_send_word(EXT_DAC, regData, 1);
    
    // Transmit ACK signal to serial:
    SendAckMessage((MSG_GROUPS)DAC_MSG, (MSG_REQUEST)DAC_SET_VALUE);
}
// </editor-fold>

