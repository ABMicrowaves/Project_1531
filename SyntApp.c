/*******************************************************************************
File name: SyntApp.c                                                        ****
File description:   TX and RX Synthesizers (ADF-5355) Application manager.  ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
*******************************************************************************/

#include "SyntApp.h"


// <editor-fold defaultstate="collapsed" desc="Init synthesizers">

void PLLInitialize()
{
    // Set RX Synthesizer latch interrupt on block B - port 7:   
    IOCB = 0b10000000;
    
    // Set TX chip-enable at high:
    SwSpi_Set_CE_Pin(SYNTH_TX, HIGH);

    
    // Set TX Synthesizer:
    for(int idx = 0; idx < NUM_OF_REGISTERS; idx++)
    {
        SWSPI_send_word(SYNTH_TX, PLL_INIT_REGISTERS[idx], 3);
    }
    
    // We use fPdf >= 75 MHz so send REG 4-0 again (according data sheet)
    SWSPI_send_word(SYNTH_TX, PLL_INIT_REGISTERS[4], 3);
    SWSPI_send_word(SYNTH_TX, PLL_INIT_REGISTERS[2], 3);
    SWSPI_send_word(SYNTH_TX, PLL_INIT_REGISTERS[1], 3);
    SWSPI_send_word(SYNTH_TX, PLL_INIT_REGISTERS[0], 3);
    
    // Set RX chip-enable at high:
    SwSpi_Set_CE_Pin(SYNTH_RX, HIGH);
    
    // Set RX Synthesizer:
    for(int idx = 0; idx < NUM_OF_REGISTERS; idx++)
    {
        SWSPI_send_word(SYNTH_RX, PLL_INIT_REGISTERS[idx], 3);
    }
    
    // We use fPdf >= 75 MHz so send REG 4-0 again (according data sheet)
    SWSPI_send_word(SYNTH_RX, PLL_INIT_REGISTERS[4], 3);
    SWSPI_send_word(SYNTH_RX, PLL_INIT_REGISTERS[2], 3);
    SWSPI_send_word(SYNTH_RX, PLL_INIT_REGISTERS[1], 3);
    SWSPI_send_word(SYNTH_RX, PLL_INIT_REGISTERS[0], 3);
}

void PLLUartInitialize(char* data)
{
    
}

// </editor-fold>


// <editor-fold defaultstate="collapsed" desc="Update Synthesizer via EUSART">

void UpdateTxFreq(char* data)
{
    uint32_t regData = GetIntFromUartData(data);
    SWSPI_send_word(SYNTH_TX, regData, 3);
    SendAckMessage((MSG_GROUPS)SYNTH_MSG, (MSG_REQUEST)SYNTH_DOWN_SET);
}

void UpdateRxFreq(char* data)
{
    uint32_t regData = GetIntFromUartData(data);
    SWSPI_send_word(SYNTH_RX, regData, 3);
    SendAckMessage((MSG_GROUPS)SYNTH_MSG, (MSG_REQUEST)SYNTH_UP_SET); 
}
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Reset syntesizers">

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="synthesizers ISR">

void SYNTH_ISR(void)
{
    
}
// </editor-fold>

