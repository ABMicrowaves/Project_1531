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
    
    // <editor-fold defaultstate="collapsed" desc="Begin word data cycle">
    
    if(phrType == SYNTH_TX || phrType == SYNTH_RX)
    {
        SwSpi_Set_Synth_Le_Pin(phrType, LOW);
    }
    else if(phrType == EXT_DAC)
    {  
        SwSpi_Set_Dac_Sync_Pin(LOW);
    }
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="Send word (2 bytes)">
    
    for(int idx = dataSize + 1; idx > 0; idx--)
    {
        uint8_t datac = make8(data, idx - 1);
        SWSPI_send_bits(phrType, datac);
    }
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="End cycle">
    
    if(phrType == SYNTH_TX || phrType == SYNTH_RX)
    {
        SwSpi_Set_Synth_Le_Pin(phrType, HIGH);
    }
    else if(phrType == EXT_DAC)
    {
        SwSpi_Set_Dac_Sync_Pin(HIGH);
    }
    // </editor-fold>
    
    INTERRUPT_GlobalInterruptEnable();
}

void SWSPI_send_bits(SPI_PERIPHERAL phrType, uint8_t data)
{
    UCHAR count;
    for (count = 8; count ; count--, data <<= 1)
    {
        //if(phrType == EXT_DAC)
        {
            SwSpi_Clk_Pin(phrType, HIGH);
        }
        
        if (data & 0X80)
        {
            
            SwSpi_Data_Pin(phrType, HIGH);
        } 
        else
        {
            SwSpi_Data_Pin(phrType, LOW);
        }
        
        SwSpi_Clk_Pin(phrType, LOW);
        
//        if(phrType == SYNTH_TX || phrType == SYNTH_RX)
//        {
//            __delay_us(10);
//            SwSpi_Synth_Toggle_Clock(phrType);
//            __delay_us(25);
//        }
    }
    
    SwSpi_Data_Pin(phrType, LOW);
    SwSpi_Clk_Pin(phrType, LOW);
}
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="SW_SPI set GPIO">


void SwSpi_Data_Pin (SPI_PERIPHERAL phrType, bool cPinMode)
{
    switch(phrType)
    {
        case SYNTH_TX:
            if(cPinMode == HIGH)
            {
                TX_SYNT_DATA_SetHigh();
            }
            else if (cPinMode == LOW)
            {
                TX_SYNT_DATA_SetLow();
            }
            break;
            
        case SYNTH_RX:
            if(cPinMode == HIGH)
            {
                RX_SYNT_DATA_SetHigh();
            }
            else if (cPinMode == LOW)
            {
                RX_SYNT_DATA_SetLow();
            }
            break;
        
        case EXT_DAC:
            if(cPinMode == HIGH)
            {
                DAC_DATA_SetHigh();
            }
            else if (cPinMode == LOW)
            {
                DAC_DATA_SetLow();
            }
            break;
    }
}

void SwSpi_Clk_Pin (SPI_PERIPHERAL phrType, bool cPinMode)
{
    switch(phrType)
    {
        case SYNTH_TX:
            if(cPinMode == HIGH)
            {
                TX_SYNT_CLK_SetHigh();
            }
            else if (cPinMode == LOW)
            {
                TX_SYNT_CLK_SetLow();
            }
            break;
            
        case SYNTH_RX:
            if(cPinMode == HIGH)
            {
                RX_SYNT_CLK_SetHigh();
            }
            else if (cPinMode == LOW)
            {
                RX_SYNT_CLK_SetLow();
            }
            
            break;
        
        case EXT_DAC:
            if(cPinMode == HIGH)
            {
                DAC_CLK_SetHigh();
            }
            else if (cPinMode == LOW)
            {
                DAC_CLK_SetLow();
            }
            break;
    }
}

void SwSpi_Synth_Toggle_Clock(SPI_PERIPHERAL phrType)
{
    SwSpi_Clk_Pin(phrType, HIGH);
    
    switch(phrType)
    {
        case SYNTH_TX:
             __delay_us(500);
            break;
        case SYNTH_RX:
             __delay_us(500);
            break;       
        default:
            __delay_us(500);
    }
    
    SwSpi_Clk_Pin(phrType, LOW);
}

void SwSpi_Set_CE_Pin (SPI_PERIPHERAL phrType, bool cPinMode)
{
    switch(phrType)
    {
        case SYNTH_TX:
            if(cPinMode == HIGH)
            {
                TX_SYNT_CE_SetHigh();
            }
            else if(cPinMode == LOW)
            {
                TX_SYNT_CE_SetLow(); 
            }
            break;
            
        case SYNTH_RX:
            if(cPinMode == HIGH)
            {
                RX_SYNT_CE_SetHigh();
            }
            else if(cPinMode == LOW)
            {
                TX_SYNT_CE_SetLow(); 
            }
            break;
    }
}
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="SPI_DEVICES_FUNCTIONS">

void SwSpi_Set_Synth_Le_Pin(SPI_PERIPHERAL phrType, bool cPinMode)
{
    switch(phrType)
    {
        case SYNTH_TX:
            if(cPinMode == HIGH)
            {
                TX_SYNT_LE_SetHigh();
            }
            else if(cPinMode == LOW)
            {
                TX_SYNT_LE_SetLow(); 
            }
            break;
            
        case SYNTH_RX:
            if(cPinMode == HIGH)
            {
                RX_SYNT_LE_SetHigh();
            }
            else if(cPinMode == LOW)
            {
                RX_SYNT_LE_SetLow(); 
            }
            break;
    }
}

void SwSpi_Set_Dac_Sync_Pin(bool cPinMode)
{
    switch(cPinMode)
    {
        case LOW:
            DAC_SYNC_SetLow();
            break;
            
        case HIGH:
            DAC_SYNC_SetHigh();
            break;
    }
}

// </editor-fold>

