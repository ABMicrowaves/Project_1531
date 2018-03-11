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
    
    // Testing:
    //SWSPI_send_word(SYNTH_TX, 0x3, 3);
    //SWSPI_send_word(SYNTH_TX, 0x800025, 3);
    
    
//    __delay_ms(10);
    SWSPI_send_word(SYNTH_TX, 0x1041C, 3);          // R12
    SWSPI_send_word(SYNTH_TX, 0x61300B, 3);         // R11
    SWSPI_send_word(SYNTH_TX, 0xC0323A, 3);         // R10

    SWSPI_send_word(SYNTH_TX, 0x2221BCC9, 3);       // R09

    SWSPI_send_word(SYNTH_TX, 0x102D0428, 3);       // R08

    SWSPI_send_word(SYNTH_TX, 0x120000E7, 3);       // R07

    SWSPI_send_word(SYNTH_TX, 0x35010076, 3);       // R06

    SWSPI_send_word(SYNTH_TX, 0x800025, 3);         // R05

    SWSPI_send_word(SYNTH_TX, 0x34008B84, 3);       // R04

    SWSPI_send_word(SYNTH_TX, 0x3, 3);              // R03

    SWSPI_send_word(SYNTH_TX, 0x12, 3);             // R02

    SWSPI_send_word(SYNTH_TX, 0x1, 3);              // R01

    SWSPI_send_word(SYNTH_TX, 0x2007D0, 3);            // R00
    
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
//    uint32_t regData = GetIntFromUartData(data);
//    SWSPI_send_word(SYNTH_TX, regData, 3);
//    SendAckMessage((MSG_GROUPS)SYNTH_MSG, (MSG_REQUEST)SYNTH_DOWN_SET);
    
    SwSpi_Set_Synth_Le_Pin(SYNTH_TX, HIGH);
    
    SWSPI_send_word(SYNTH_TX, 0x3, 3);                  // R10
//    SWSPI_send_word(SYNTH_TX, 0x3501E076, 3);         // R4
//    SWSPI_send_word(SYNTH_TX, 0x34008B84, 3);         // R2
//    SWSPI_send_word(SYNTH_TX, 0x12, 3);               // R1
//    SWSPI_send_word(SYNTH_TX, 0x8000001, 3);          // R0
//    SWSPI_send_word(SYNTH_TX, 3E0, 3);                // R4
//    SWSPI_send_word(SYNTH_TX, 0x34008B84, 3);         // R0
//    SWSPI_send_word(SYNTH_TX, 0x3E0, 3);              // R1
//    SWSPI_send_word(SYNTH_TX, 0x34008B84, 3);         // R0
//    SWSPI_send_word(SYNTH_TX, 0x12, 3);               // R4
//    SWSPI_send_word(SYNTH_TX, 0x8000001, 3);          // R0
//    SWSPI_send_word(SYNTH_TX, 0x3E0, 3);              // R1
    //SendAckMessage((MSG_GROUPS)SYNTH_MSG, (MSG_REQUEST)SYNTH_DOWN_SET);
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

