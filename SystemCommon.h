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

typedef enum
{
    SYNTH_TX = 0,
    SYNTH_RX,
    EXT_DAC
} SPI_PERIPHERAL;


#include "mcc_generated_files/mcc.h"
#include "MessageFunctions.h"
#include "FlashApp.h"
#include "AdcApp.h"
#include "SyntApp.h"
#include "DacApp.h"
#include "EusartApp.h"
#include "SevenSegmentApp.h"
#include "SyntApp.h"
#include "LedsApp.h"
#include "SwSpiApp.h"


// define special types
#define ULONG uint32_t
#define UCHAR uint8_t
#define MAX_UART_BYTES_SIZE         17
#define UART_DATA_ARRAY_SIZE        0xA
#define END_UART_DATA_STREAM_CHAR   0x10    // @
#define END_UART_ALL_STREAM_CHAR    0x23    // #
#define NUM_OF_BITS_SYNTH_REG       32

// MCU Main program FSM:    
typedef enum
{
	START_SYSTEM = 0,
	ADC_DAC,
	FLASH,
	EUSART,
	FINISH_ROUND
}SYSTEM_STATE;

typedef struct
{
    uint32_t num;
    uint32_t con;
}INT_VAL;

unsigned char crc8(char* dataArray, int dataSize);
uint8_t make8(uint32_t data, uint8_t dataLocation);
void Make32bitsArray(bool* array, uint32_t data);
void ZeroArray(char* array, int size);
void FillArray(char* array, int size, uint8_t value);
void ZeroBitsArray(bool* array); 
INT_VAL GetIntFromUartData(int8_t num, char* data);
void StoreIntInEeprom(uint32_t data, uint8_t address, int numOfByes);
uint32_t ReadIntFromEeprom(uint8_t address, int numOfByes);
uint16_t GetUint16FromBitArray(bool* bitarray, int numOfBits);

// System common functions
void ResetMcu(void);
void ResetCpld(void);
void SendSystemStartAck(void);

#endif	/* SYSTEMCOMMON_H */

