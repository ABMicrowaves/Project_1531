/*******************************************************************************
File name: SwSpiApp.h                                                        ****
File description:   Software SPI application manager.                       ****
MCU:                PIC18F45k22                                             ****
Date modified: 19/02/2018 11:31.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
****************************************************************************** */

#include "SwSpiApp.h"

// <editor-fold defaultstate="collapsed" desc="Global verbs">

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="SW_SPI send data">

void SWSPI_send_word (SPI_PERIPHERAL phrType, uint32_t data, uint8_t dataSize)
{
    INTERRUPT_GlobalInterruptDisable();
    
    for(int idx = dataSize + 1; idx > 0; idx--)
    {
        SWSPI_send_bits(phrType, make8(data, idx - 1));
    }
    INTERRUPT_GlobalInterruptEnable();
}

void SWSPI_send_bits(SPI_PERIPHERAL phrType, uint8_t data)
{
    UCHAR count;
    for (count = 8; count ; count--, data <<= 1)
    {
        if (data & 0X80)
        {
            SwSpiDataHigh(phrType);
        } 
        else
        {
            SwSpiDataLow(phrType);
        }
        
       __delay_us(10);
       SwSpiSetClock(phrType);
       __delay_us(25);
    }
    SwSpiDataLow(phrType);
    SwSpiClkLow(phrType);
}
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="SW_SPI set GPIO">

void SwSpiDataHigh (SPI_PERIPHERAL phrType)
{
    switch(phrType)
    {
        case SYNTH_TX:
            TX_SYNT_DATA_SetHigh();
            break;
            
        case SYNTH_RX:
            RX_SYNT_DATA_SetHigh();
            break;
        
        case EXT_DAC:
            break;
    }
}

void SwSpiDataLow (SPI_PERIPHERAL phrType)
{
    switch(phrType)
    {
        case SYNTH_TX:
            TX_SYNT_DATA_SetLow();
            break;
            
        case SYNTH_RX:
            RX_SYNT_DATA_SetLow();
            break;
        
        case EXT_DAC:
            break;
    }
}

void SwSpiClkHigh (SPI_PERIPHERAL phrType)
{
    switch(phrType)
    {
        case SYNTH_TX:
            TX_SYNT_CLK_SetHigh();
            break;
            
        case SYNTH_RX:
            RX_SYNT_CLK_SetHigh();
            break;
        
        case EXT_DAC:
            break;
    }
}


void SwSpiClkLow (SPI_PERIPHERAL phrType)
{
    switch(phrType)
    {
        case SYNTH_TX:
            TX_SYNT_CLK_SetLow();
            break;
            
        case SYNTH_RX:
            RX_SYNT_CLK_SetLow();
            break;
        
        case EXT_DAC:
            break;
    }
}
// </editor-fold>

void SwSpiSetClock(SPI_PERIPHERAL phrType)
{
    SwSpiClkHigh(phrType);
    
    switch(phrType)
    {
        case SYNTH_TX:
             __delay_us(500);
            break;
        case SYNTH_RX:
             __delay_us(500);
            break;       
        case EXT_DAC:
             __delay_us(500);
            break;
        default:
            __delay_us(500);
    }
    SwSpiClkLow(phrType);

}