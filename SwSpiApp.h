/*******************************************************************************
File name: SwSpiApp.h                                                       ****
File description:   Software SPI application manager.                       ****
MCU:                PIC18F45k22                                             ****
Date modified: 19/02/2018 11:31.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
*******************************************************************************/

#ifndef SWSPIAPP_H
#define	SWSPIAPP_H

#include "SystemCommon.h"

typedef enum
{
    SYNTH_TX = 0,
    SYNTH_RX,
    EXT_DAC
} SPI_PERIPHERAL;

void SWSPI_send_word (SPI_PERIPHERAL phrType, uint32_t data, uint8_t dataSize);
void SWSPI_send_bits(SPI_PERIPHERAL phrType, uint8_t data);

void SwSpiDataLow (SPI_PERIPHERAL type);
void SwSpiDataHigh (SPI_PERIPHERAL type);
void SwSpiClkLow (SPI_PERIPHERAL phrType);
void SwSpiClkHigh (SPI_PERIPHERAL phrType);
void SwSpiSetClock(SPI_PERIPHERAL phrType);

#endif	/* SWSPIAPP_H */

