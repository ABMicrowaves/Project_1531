/*******************************************************************************
File name: EusartApp.c                                                      ****
File description:   EUASRT driver application manager.                      ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
****************************************************************************** */

#include "EusartApp.h"

// <editor-fold defaultstate="collapsed" desc="Global verbs">

// Define global message parameters:

static UART_READ_STATE cState = START_RX_MESSAGE_READ;
MSG_GROUPS group = 0;
MSG_REQUEST request = 0;
uint8_t dataSize = 0;
char data = 0;
char crcCalc = 0, crcGiven = 0;
char rxMsgQueue[MSG_RX_MAX_DATA_SIZE];
char rxMsgData[MSG_RX_MAX_DATA_SIZE];
static uint8_t msgCount = 0;
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="EUSART read packet">

void readUartMessage(void)
// Since we read byte by byte from MCC UART driver we need to implement FSM
{    
    uint8_t chRec = NULL;
    switch(cState)
    {
        case START_RX_MESSAGE_READ:
            
            // Check to see if there is more or equal bytes of message size:
            if(eusart1RxCount > MIN_RX_MSG_SIZE)
            {
                cState = FIND_MAGIC;
            }
            return;
        
        case FIND_MAGIC:
            
            InitRxMessageParams();
            msgCount = 0;
            if(eusart1RxCount > 1)
            {
                chRec = EUSART1_Read();
                rxMsgQueue[MSG_MAGIC_LOCATION] = chRec; 
                if(chRec == MSG_MAGIC_A)
                {
                   cState = READ_GROUP;
                }
            }
            else
            {
                cState = START_RX_MESSAGE_READ;
            }
            
            break;
        
        case READ_GROUP:
            
            if(eusart1RxCount > 1)
            {
                group = EUSART1_Read();
                rxMsgQueue[MSG_GROUP_LOCATION] = group;
                cState = READ_REQUEST;
            }
            break;
        
        case READ_REQUEST:
            
            if(eusart1RxCount > 1)
            {
                request = EUSART1_Read();
                rxMsgQueue[MSG_REQUEST_LOCATION] = request;
                cState = READ_DATA_SIZE; 
            }
            break;
        
        case READ_DATA_SIZE:
            if(eusart1RxCount > 1)
            {
                dataSize = EUSART1_Read();
                rxMsgQueue[MSG_DATA_SIZE_LOCATION] = dataSize;
                if(dataSize == 0)
                {
                    cState = CHECK_CRC;
                }
                else
                {
                    cState = READ_DATA;
                }
                
            }

            break;
        
        case READ_DATA:

            if(eusart1RxCount >= dataSize)
            {
                ZeroArray(rxMsgData, MSG_RX_MAX_DATA_SIZE);
                
                for(int idx = 0; idx < dataSize; idx++)
                {
                    chRec = EUSART1_Read();
                    rxMsgQueue[MSG_DATA_LOCATION + msgCount++] = chRec;
                    rxMsgData[idx] = chRec;
                }
                
                cState = CHECK_CRC;
            }
            break;
            
        case CHECK_CRC:
            if(eusart1RxCount >= 1)
            {
                crcGiven = EUSART1_Read();
                crcCalc = crc8(rxMsgQueue, MSG_DATA_LOCATION + msgCount);

                if(crcGiven == crcCalc)
                {
                    cState = JUMP_FUNCTION;
                }
                else
                {
                    cState = START_RX_MESSAGE_READ;
                }
            }
            break;
        
        case JUMP_FUNCTION:
            groupsArray[group - 1](request, rxMsgData);
            cState = START_RX_MESSAGE_READ;
            break; 
    }
}

void InitRxMessageParams(void)
{
    //group = 0;
    //request = 0;
    dataSize = 0;
    crcCalc = 0; 
    crcGiven = 0;
    msgCount = 0;
    ZeroArray(rxMsgQueue, MSG_RX_MAX_DATA_SIZE);
}

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="EUSART write packet">


void WriteUartMessage(char* dataBuf, int dataSize)
{
    for(int idx = 0; idx < dataSize; idx++)
    {
        EUSART1_Write(dataBuf[idx]);
    }
}

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="EUSART send ACK / Simple message">

// Send ACK message
void SendAckMessage(MSG_GROUPS inGroup, MSG_REQUEST inRequest)
{
    // Create TX packet and clear the memory:
    char TxMsg[ACK_MESSAGE_PACKET_SIZE + 1];
    ZeroArray(TxMsg, ACK_MESSAGE_PACKET_SIZE + 1);
    
    // Now fill it:
    TxMsg[MSG_MAGIC_LOCATION] =  MSG_MAGIC_A;
    TxMsg[MSG_GROUP_LOCATION] =  inGroup;
    TxMsg[MSG_REQUEST_LOCATION] =  inRequest;
    TxMsg[MSG_DATA_SIZE_LOCATION] = 0;

    TxMsg[ACK_MESSAGE_PACKET_SIZE] = crc8(TxMsg, ACK_MESSAGE_PACKET_SIZE);
    
    WriteUartMessage(TxMsg, ACK_MESSAGE_PACKET_SIZE + 1);
}
// </editor-fold>