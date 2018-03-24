/*******************************************************************************
File name: SystemCommon.c                                                   ****
File description:   Include MCU run-time system common parameters           ****
 *                  and functions.                                          ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
****************************************************************************** */

#include "SystemCommon.h"
#include <string.h>

unsigned char crc8(char* dataArray, int dataSize)
{
    int crc = 0;
    for (int i = 0; i < dataSize; i++)
    {
        crc += dataArray[i];
    }
    crc &= 0xff;
    return crc;
}

void ZeroArray(char* array, int size)
{
    memset(array, 0x0, size);
}

void FillArray(char* array, int size, uint8_t value)
{
    memset(array, value, size);
}

uint16_t GetUint16FromBitArray(bool* bitarray, int numOfBits)
{
    uint16_t res = 0;
    for (int i = 0 ; i < numOfBits ; i++) 
    {
        if (bitarray[i]) 
        {
            res |= (uint16_t)(1 << i);
        }
    }
    return res;
}

INT_VAL GetIntFromUartData(int8_t num, char* data)
{
    INT_VAL retVal;
    retVal.num = 0;
    retVal.con = 0;
    uint8_t idxData = 0;
    char recVal = NULL;
    
    char dataRegArr[UART_DATA_ARRAY_SIZE];
    ZeroArray(dataRegArr, UART_DATA_ARRAY_SIZE);
    
    for(idxData = 0; idxData < UART_DATA_ARRAY_SIZE; idxData++)
    {
        recVal = data[idxData];
        if(recVal == END_UART_DATA_STREAM_CHAR)   // @ -> End of UART DATA stream.
        {
            idxData++;
            break;
        }
        else
        {
            dataRegArr[idxData] = recVal + '0';
        }
    }
    retVal.num = strtol(dataRegArr, NULL, num);
    
    ZeroArray(dataRegArr, UART_DATA_ARRAY_SIZE);
    
    for(int idxCon = 0; idxCon < UART_DATA_ARRAY_SIZE; idxCon++)
    {
        recVal = data[idxData + idxCon];
        if(recVal == END_UART_ALL_STREAM_CHAR)   // $ -> End of all UART stream.
        {
            break;
        }
        else
        {
            dataRegArr[idxCon] = data[idxCon + idxData] + '0';
        }
    }
    retVal.con = strtol(dataRegArr, NULL, num);
    
    return retVal;
}

uint8_t make8(uint32_t data, uint8_t dataLocation)
{
    switch(dataLocation)
    {
        case 0:
            return (data & 0x000000ff);
        
        case 1:
            return (data & 0x0000ff00) >> 8;
            
        case 2:
            return (data & 0x00ff0000) >> 16;
            
        case 3:
            return (data & 0xff000000) >> 24;
        
        default:
            return NULL;
    }
}

void Make32bitsArray(bool* array, uint32_t data)
{
    for(int idx = 0; idx <= NUM_OF_BITS_SYNTH_REG; idx++)
    {
        array[NUM_OF_BITS_SYNTH_REG - idx - 1] = data % 2;
        data /= 2;
    }
}

void StoreIntInEeprom(uint32_t data, uint8_t address, int numOfByes)
{
    for(uint8_t idx = numOfByes; idx; idx--)
    {
        uint8_t val = make8(data, idx - 1);
        EepromWrite(address - idx, val);
    }
}

uint32_t ReadIntFromEeprom(uint8_t address, int numOfByes)
{
    uint32_t retVal = 0x00;
    address -= numOfByes;
    
    for(uint8_t idx = 0; idx < numOfByes; idx++)
    {
        uint32_t base = pow(2,8*(numOfByes - 1 - idx));
        retVal = retVal | EepromRead(address + idx) * base;
    }
    return retVal;
}

void ResetMcu()
{
    // Before MCU system reset send ACK:
    SendAckMessage((MSG_GROUPS)CONTROL_MSG, (MSG_REQUEST)CONTROL_RESET_MCU);
    
    // Now reset MCU:
    Reset();
}

void SendSystemStartAck()
{
    SendAckMessage((MSG_GROUPS)CONTROL_MSG, (MSG_REQUEST)CONTROL_SYSTEM_START);
}

