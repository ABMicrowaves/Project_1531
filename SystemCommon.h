/*******************************************************************************
File name: SystemCommon.c                                                   ****
File description:   Include MCU run-time system common parameters           ****
 *                  and functions.                                          ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
****************************************************************************** */

#ifndef SYSTEMCOMMON_H
#define	SYSTEMCOMMON_H

#include "mcc_generated_files/mcc.h"
#include "MessageFunctions.h"
#include "FlashApp.h"
#include "AdcApp.h"
#include "DacApp.h"
#include "EusartApp.h"
#include "SevenSegmentApp.h"
#include "SyntApp.h"
#include "LedsApp.h"
#include "SyntApp.h"
#include "SwSpiApp.h"

// define special types
#define ULONG uint32_t
#define UCHAR uint8_t
#define MAX_UART_BYTES_SIZE 8
#define END_UART_STREAM_CHAR 0x40

// MCU Main program FSM:    
typedef enum
{
	START_SYSTEM = 0,
	ADC_DAC,
	FLASH,
	EUSART,
	FINISH_ROUND
}SYSTEM_STATE;

unsigned char crc8(char* dataArray, int dataSize);
uint8_t make8(uint32_t data, uint8_t dataLocation);
void ZeroArray(char* array, int size);
int GCD(int num1, int num2); 
uint32_t GetIntFromUartData(char* data);

// System common functions
void ResetMcu(void);
void ResetCpld(void);
void SendSystemStartAck(void);

#endif	/* SYSTEMCOMMON_H */

