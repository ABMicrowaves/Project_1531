/*******************************************************************************
File name: EusartApp.h                                                      ****
File description:   EUASRT driver application manager.                      ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
*******************************************************************************/

#ifndef EUSARTAPP_H
#define	EUSARTAPP_H

#include <string.h>
#include "SystemCommon.h"
#include <stdlib.h>

typedef enum
{
    START_RX_MESSAGE_READ = 0,
	FIND_MAGIC,
	READ_GROUP,
	READ_REQUEST,
	READ_DATA_SIZE,
	READ_DATA,
    CHECK_CRC,
    JUMP_FUNCTION
}UART_READ_STATE;

// RX routines:
void readUartMessage(void);
void InitRxMessageParams(void);

// TX routines:
void WriteUartMessage(char* dataBuf, int dataSize);
void SendAckMessage(MSG_GROUPS inGroup, MSG_REQUEST inRequest);

#endif	/* EUSARTAPP_H */

