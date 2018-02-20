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

#define FREQ_SIZE_BYTES 4
#define NUM_OF_REGISTERS 12

// Registers will be write on opposite direction.
const uint32_t PLL_REGISTERS[12] = 
{
    0x0B6002,   /* Ro0  */
    0x0,        /* R01  */
    0x21,       /* R02  */
    0x3,        /* R03  */
    0x48B80023, /* R04  */
    0x520008,   /* R05  */
    0x67021053, /* R06  */
    0x12345,    /* R07  */
    0x12345,    /* R08  */
    0x12345,    /* R09  */
    0x12345,    /* R10  */
    0x12345     /* R11  */
};  

void InitSynthesizers(void);
//void PLL_initialize(SPI_PERIPHERAL phrType);

void UpdateTxFreq(char* data);
void UpdateRxFreq(char* data);


void SYNTH_ISR(void);


#endif	/* SYNTAPP_H */

