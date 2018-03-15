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
    for(int8_t idx = 0; idx < NUM_OF_DACS; idx++)
    {
        uint16_t dacInput = ReadIntFromEeprom(EEPROM_DAC_REGS_ADDRESS_OFSEET | DAC_ADDRES[idx], 2);
        if(dacInput == 0xFFFF)
        {
            SWSPI_send_word(EXT_DAC, DAC_DEFAULT_INIT_VALUES[idx], 1);
        }
        else
        {
            SWSPI_send_word(EXT_DAC, dacInput, 1);
        }
    }
}

// <editor-fold defaultstate="collapsed" desc="DAC Convert">

void DacSetValue(char* data)
{
    uint16_t regData = GetIntFromUartData(16, data);
    SWSPI_send_word(EXT_DAC, regData, 1);
    
    // Store DAC value in EEPROM
    int8_t dacIndex = (regData >> 14); 
    StoreIntInEeprom(regData, EEPROM_DAC_REGS_ADDRESS_OFSEET | DAC_ADDRES[dacIndex], 2);

    // Transmit ACK signal to serial:
    SendAckMessage((MSG_GROUPS)DAC_MSG, (MSG_REQUEST)DAC_SET_VALUE);
}
// </editor-fold>

