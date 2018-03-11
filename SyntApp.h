/*******************************************************************************
File name: SyntApp.c                                                        ****
File description:   TX and RX Synthesizers (ADF-5355) Application manager.  ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
*******************************************************************************/

#ifndef SYNTAPP_H
#define	SYNTAPP_H

#include "SystemCommon.h"

#define SYNTH_DELAY_BETWEEN_WORDS_MSEC 250

#define REG_DATA_BYTES_SIZE 6
#define NUM_OF_REGISTERS 13

// Registers will be write on opposite direction.
const uint32_t PLL_INIT_REGISTERS[13] = 
{
    0x0001041C,     /* R12  */
    0x0061300B,     /* R11  */
    0x00C0323A,     /* R10  */
    0x2221BCC9,     /* R09  */
    0x102D0428,     /* R08  */
    0x120000E7,     /* R07  */
    0x35012076,     /* R06  */
    0x00800025,     /* R05  */
    0x34009B84,     /* R04  */
    0x00000003,     /* R03  */
    0x00000012,     /* R02  */
    0x06000001,     /* R01  */
    0x00200340      /* R00  */
};  

const uint32_t TEST_PLL_REGISTERS[13] = 
{
    0x1041C,        /* R12  */
    0x61300B,       /* R11  */
    0xC026BA,       /* R10  */
    0x1A19FCC9,     /* R09  */
    0x102D0428,     /* R08  */
    0x120000E7,     /* R07  */
    0x35056076,     /* R06  */
    0x800025,       /* R05  */
    0x32008B84,     /* R04  */
    0x3,            /* R03  */
    0x80032,        /* R02  */
    0x1AAAAA1,      /* R01  */
    200410          /* R00  */
};




void PLLUartInitialize(char* data);
void PLLInitialize(void);

void UpdateTxFreq(char* data);
void UpdateRxFreq(char* data);

void SYNTH_ISR(void);

#endif	/* SYNTAPP_H */

