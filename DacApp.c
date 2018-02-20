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

// <editor-fold defaultstate="collapsed" desc="DAC Convert">

void DacSetValue(char* data)
{
    int digitalVal = 0, dataCnt = 0;
    uint8_t vout = 0;

    double dVout = 0;
    char tempArr[DAC_BYTES_IN_VAL];
    for(int idx = 0; idx < DAC_BYTES_IN_VAL; idx++)
    { 
        if(data[idx] != 0x2e)
        {
            tempArr[dataCnt++] = data[idx];
        }
    }
    
    for(int idx = 0; idx < DAC_BYTES_IN_VAL - 1; idx++)
    { 
        digitalVal += tempArr[DAC_BYTES_IN_VAL - 2 - idx]*pow(10,idx);
    }
  
    dVout =  (digitalVal - VSOURCEMINUS) * pow(2,DAC_BITS) / (VSOURCEPLUS - VSOURCEMINUS); 
    vout = (uint8_t)dVout;

    //digitalVal++;
    //DAC_SetOutput(vout);
    
    // Transmit ACK signal to serial:
    SendAckMessage((MSG_GROUPS)DAC_MSG, (MSG_REQUEST)DAC_SET_VALUE);
}
// </editor-fold>

