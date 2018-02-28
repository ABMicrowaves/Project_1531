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

int GCD(int num1, int num2) 
{
  while (num2 != 0)  
  {
    int temp = num2;
    num2 = num1 % num2;
    num1 = temp;
  }
  return num1;
}

uint32_t GetIntFromUartData(char* data)
{
    char dataRegArr[MAX_UART_BYTES_SIZE];
    ZeroArray(dataRegArr, MAX_UART_BYTES_SIZE);
    
    for(int idx = 0; idx < MAX_UART_BYTES_SIZE; idx++)
    {
        char c = data[idx] + '0';
        if(c == END_UART_STREAM_CHAR)   // @ -> End of UART stream.
        {
            break;
        }
        else
        {
            dataRegArr[idx] = data[idx] + '0';
        }
        
    }
    
    return strtol(dataRegArr, NULL, 16);
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



void ResetMcu()
{
    // Before MCU system reset send ACK:
    SendAckMessage((MSG_GROUPS)CONTROL_MSG, (MSG_REQUEST)CONTROL_RESET_MCU);
    
    // Now reset MCU:
    Reset();
}

void ResetCpld()
{
    // Before MCU system reset send ACK:
    SendAckMessage((MSG_GROUPS)CONTROL_MSG, (MSG_REQUEST)CONTROL_RESET_CPLD);
   
    // Now reset CPLD unit:
    
}

void SendSystemStartAck()
{
    SendAckMessage((MSG_GROUPS)CONTROL_MSG, (MSG_REQUEST)CONTROL_SYSTEM_START);
}

