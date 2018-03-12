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

#define NUM_OF_REGISTERS 13

#define NUM_OF_UPDATE_REGISTERS 7

// Registers will be write on opposite direction.


const uint32_t SYNTH_REGS[NUM_OF_REGISTERS] = 
{
    0x1041C,        /* R12  */
    0x61300B,       /* R11  */
    0xC0193A,       /* R10  */
    0x1110FCC9,     /* R09  */
    0x102D0428,     /* R08  */
    0x120000E7,     /* R07  */
    0x35006076,     /* R06  */
    0x800025,       /* R05  */
    0x30008384,     /* R04  */
    0x3,            /* R03  */
    0x12,           /* R02  */
    0x1,            /* R01  */
    0x200640        /* R00  */
};

void PLLUartInitialize(char* data);
void PLLInitialize(void);

void UpdateTxFreq(char* data);
void UpdateRxFreq(char* data);

void SYNTH_ISR(void);

#endif	/* SYNTAPP_H */

