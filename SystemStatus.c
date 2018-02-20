/*******************************************************************************
File name: SystemStatus.c                                                   ****
File description:   Include MCU run-time and status parameters              ****
                    and functions.                                          ****
MCU:                PIC18F45k22                                             ****
Date modified: 05/02/2018 16:34.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
****************************************************************************** */

#include "SystemStatus.h"

static uint32_t mcuRunTimeIn5SecTicks = 0;   // Max Time to store = 24 hours


void SetMcuFwVersion(char* data)
{
    for(uint8_t idx = 0; idx < FW_VERSION_MAX_SIZE_BYTE; idx++)
    {
        EepromWrite(idx, data[idx]);
    }
    
    // Now send ACK message via serial:        
    SendAckMessage((MSG_GROUPS)MCU_STATUS_VERSION_MSG, (MSG_REQUEST)STATUS_SET_MCU_FW_VERSION);
}

void GetMcuFwVersion()
{
    // Create TX packet and clear the memory:
    char TxMsg[STATUS_FW_PACKET_SIZE + 1];
    ZeroArray(TxMsg, STATUS_FW_PACKET_SIZE + 1);
    
    // Now fill it:
    TxMsg[MSG_MAGIC_LOCATION] =  MSG_MAGIC_A;
    TxMsg[MSG_GROUP_LOCATION] =  MCU_STATUS_VERSION_MSG;
    TxMsg[MSG_REQUEST_LOCATION] =  STATUS_GET_MCU_FW_VERSION;
    TxMsg[MSG_DATA_SIZE_LOCATION] = FW_VERSION_MAX_SIZE_BYTE;

    // Fill TX array with data:
    for(uint8_t idx = 0; idx < FW_VERSION_MAX_SIZE_BYTE; idx++)
    {
        TxMsg[MSG_DATA_LOCATION + idx] = EepromRead(idx);
    }
    
    TxMsg[STATUS_FW_PACKET_SIZE] = crc8(TxMsg, STATUS_FW_PACKET_SIZE);
    
    WriteUartMessage(TxMsg, STATUS_FW_PACKET_SIZE + 1);
}

void SetCpldFwVersion(char* data)
{
    for(int idx = 0; idx < FW_VERSION_MAX_SIZE_BYTE; idx++)
    {
        EepromWrite(CPLD_FW_ADDR_OFFSET + idx, data[idx]);
    }
    SendAckMessage((MSG_GROUPS)MCU_STATUS_VERSION_MSG, (MSG_REQUEST)STATUS_SET_CPLD_FW_VERSION);
}

void GetCpldFwVersion()
{
    // Create TX packet and clear the memory:
    char TxMsg[STATUS_FW_PACKET_SIZE + 1];
    ZeroArray(TxMsg, STATUS_FW_PACKET_SIZE + 1);
    
    // Now fill it:
    TxMsg[MSG_MAGIC_LOCATION] =  MSG_MAGIC_A;
    TxMsg[MSG_GROUP_LOCATION] =  MCU_STATUS_VERSION_MSG;
    TxMsg[MSG_REQUEST_LOCATION] =  STATUS_GET_CPLD_FW_VERSION;
    TxMsg[MSG_DATA_SIZE_LOCATION] = FW_VERSION_MAX_SIZE_BYTE;

    // Fill TX array with data:
    for(int idx = 0; idx < FW_VERSION_MAX_SIZE_BYTE; idx++)
    {
        TxMsg[MSG_DATA_LOCATION + idx] = EepromRead(CPLD_FW_ADDR_OFFSET + idx);
    }
    
    TxMsg[STATUS_FW_PACKET_SIZE] = crc8(TxMsg, STATUS_FW_PACKET_SIZE);
    
    WriteUartMessage(TxMsg, STATUS_FW_PACKET_SIZE + 1);
}

void SetMcuRunTime()
{
    mcuRunTimeIn5SecTicks++;
    mcuRunTimeIn5SecTicks %= NUM_5SEC_TICS_24_HOURS;
}

void ClearMcuRunTime()
{
    mcuRunTimeIn5SecTicks = 0;
}

void GetMcuRunTime()
{
    // Create TX packet and send it:
    char TxMsg[STATUS_RUN_TIME_PACKET_SIZE + 1];
        
    // Now fill it:
    TxMsg[MSG_MAGIC_LOCATION] =  MSG_MAGIC_A;
    TxMsg[MSG_GROUP_LOCATION] =  MCU_STATUS_VERSION_MSG;
    TxMsg[MSG_REQUEST_LOCATION] =  STATUS_MCU_RUN_TIME;
    TxMsg[MSG_DATA_SIZE_LOCATION] = RUN_TIME_MAX_SIZE_BYTE;

    uint32_t tempRunTime = mcuRunTimeIn5SecTicks;
    
    // Fill TX array with data:
    for(int idx = 0; idx < RUN_TIME_MAX_SIZE_BYTE; idx++)
    {
        TxMsg[MSG_DATA_LOCATION + idx] = tempRunTime % 10;
        tempRunTime /= 10;
    }
    
    TxMsg[STATUS_RUN_TIME_PACKET_SIZE] = crc8(TxMsg, STATUS_RUN_TIME_PACKET_SIZE);
    
    WriteUartMessage(TxMsg, STATUS_RUN_TIME_PACKET_SIZE + 1);
}

void keepAliveSignalUart(void)
{
    SendAckMessage((MSG_GROUPS)CONTROL_MSG, (MSG_REQUEST)CONTROL_KEEP_ALIVE);
}