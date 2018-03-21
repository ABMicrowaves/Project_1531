/*******************************************************************************
File name: AdcApp.h                                                         ****
File description:   D2A driver application manager for AD5312 external chip ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
*******************************************************************************/

#include "DacApp.h"

void DacInit(void)
{
    for(int8_t idx = 0; idx < NUM_OF_DACS; idx++)
    {
        uint16_t dacInput = ReadIntFromEeprom(EEPROM_DAC_REGS_ADDRESS_OFSEET | DAC_ADDRES[idx], 2);
        if(dacInput == 0xFFFF)
        {
            SWSPI_send_word(EXT_DAC, DAC_DEFAULT_INIT_VALUES[idx], 1);
            StoreIntInEeprom(DAC_DEFAULT_INIT_VALUES[idx], EEPROM_DAC_REGS_ADDRESS_OFSEET | DAC_ADDRES[idx], 2);
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
    INT_VAL retVal;
    retVal = GetIntFromUartData(16, data);
    SWSPI_send_word(EXT_DAC, retVal.num, 1);
    
    // Store DAC value in EEPROM
    int8_t dacIndex = (retVal.num >> 14); 
    StoreIntInEeprom(retVal.num, EEPROM_DAC_REGS_ADDRESS_OFSEET | DAC_ADDRES[dacIndex], 2);

    // Transmit ACK signal to serial:
    SendAckMessage((MSG_GROUPS)DAC_MSG, (MSG_REQUEST)DAC_SET_VALUE);
}

void DacReadValue(char* data)
{
    uint16_t readVal;
    uint8_t regNum = 0, byteNum = 0; 
    char TxMsg[DAC_READ_CONDITION_PACKET_SIZE + 1];
    ZeroArray(TxMsg, DAC_READ_CONDITION_PACKET_SIZE + 1);
    
    // Now fill it:
    TxMsg[MSG_MAGIC_LOCATION] =  MSG_MAGIC_A;
    TxMsg[MSG_GROUP_LOCATION] =  DAC_MSG;
    TxMsg[MSG_REQUEST_LOCATION] =  DAC_READ_VALUE;
    TxMsg[MSG_DATA_SIZE_LOCATION] = DAC_NUM_BYTES_PRESENT_VALUE;
    
    uint8_t dacIndex = data[0];
    uint16_t readVal = ReadIntFromEeprom(EEPROM_DAC_REGS_ADDRESS_OFSEET | DAC_ADDRES[dacIndex], 2);
    
    for(int byteIdx = 0; byteIdx < DAC_NUM_BYTES_PRESENT_VALUE; byteIdx++)
    {
        TxMsg[MSG_DATA_LOCATION + byteIdx] = make8(readVal, byteIdx);
    }
    TxMsg[DAC_READ_CONDITION_PACKET_SIZE] = crc8(TxMsg, DAC_READ_CONDITION_PACKET_SIZE);
    WriteUartMessage(TxMsg, DAC_READ_CONDITION_PACKET_SIZE + 1);  
    
}
// </editor-fold>

