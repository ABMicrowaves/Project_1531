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

void SWSPI_send_word (SPI_PERIPHERAL phrType, uint32_t data, uint8_t dataSize);
void SwSpi_Data_Pin (SPI_PERIPHERAL phrType, bool cPinMode);
void SwSpi_Clk_Pin (SPI_PERIPHERAL phrType, bool cPinMode);
void SwSpi_Set_CE_Pin (SPI_PERIPHERAL phrType, bool cPinMode);

// SYNTH:
void SWSPI_Synth_send_bits(SPI_PERIPHERAL phrType, uint32_t data);
void SwSpi_Synth_Toggle_Clock(SPI_PERIPHERAL phrType);
void SwSpi_Set_Synth_Le_Pin(SPI_PERIPHERAL phrType, bool cPinMode);

// External DAC:
void SWSPI_DAC_send_bits(SPI_PERIPHERAL phrType, uint8_t data);
void SwSpi_Set_Dac_Sync_Pin(bool cPinMode);
#endif	/* SWSPIAPP_H */

