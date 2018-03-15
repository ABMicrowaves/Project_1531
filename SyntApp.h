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

#define SYNTH_DELAY_BETWEEN_WORDS_MSEC  250
#define NUM_OF_REGISTERS                13
#define NUM_OF_UPDATE_REGISTERS         7
#define NUM_SYNTH_FREQ_DATA_REGISTERS   4

#define SYNTH_READ_CONDITION_MAX_DATA_SIZE 22
#define SYNTH_READ_CONDITION_PACKET_SIZE SYNTH_READ_CONDITION_MAX_DATA_SIZE + MSG_DATA_LOCATION 
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
    0xC000001,       /* R01  */
    0x200680        /* R00  */
};

const uint8_t SYNTH_ADDRES[NUM_SYNTH_FREQ_DATA_REGISTERS] = 
{
    // SYNTH_TX + RX
    0x4,        // REG_0
    0x8,        // REG_1
    0xC,        // REG_2
    0xF,        // DAC-D address
};

void PLLUartInitialize(char* data);
void PLLInitialize(void);

void InitTxSynth(void);
void InitRxSynth(void);

void UpdateTxFreq(char* data);
void UpdateRxFreq(char* data);

void SetSynthTxOper();
void SetSynthRxOper();

void SynthReadData(char* data); 

void SYNTH_ISR(void);

#endif	/* SYNTAPP_H */

