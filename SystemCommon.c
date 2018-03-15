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

void ZeroBitsArray(bool* array)
{
    memset(array, 0x0, 32);
}

uint32_t GetIntFromUartData(int8_t num, char* data)
{
    uint32_t retVal = 0;
    char dataRegArr[MAX_UART_BYTES_SIZE];
    ZeroArray(dataRegArr, MAX_UART_BYTES_SIZE);
    
    for(int idx = 0; idx < MAX_UART_BYTES_SIZE; idx++)
    {
        char c = data[idx];
        if(c == END_UART_STREAM_CHAR)   // @ -> End of UART stream.
        {
            break;
        }
        else
        {
            dataRegArr[idx] = data[idx] + '0';
        }
        
    }
    retVal = strtol(dataRegArr, NULL, num);
    
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
    
    if(numOfByes == 2)
    {
        retVal = (EepromRead(address + 0) << 8) | (EepromRead(address + 1));
    }
    else if (numOfByes == 4)
    {
        
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

