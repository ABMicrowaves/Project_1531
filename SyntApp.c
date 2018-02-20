/*******************************************************************************
File name: SyntApp.c                                                        ****
File description:   TX and RX Synthesizers (ADF-5355) Application manager.  ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
*******************************************************************************/

#include "SyntApp.h"

// <editor-fold defaultstate="collapsed" desc="Init synthesizers">

void InitSynthesizers()
{
    // Set RX Synthesizer latch interrupt on block B - port 7:   
    IOCB = 0b10000000;
    
    // Set RX Synthesizer:
    //PLL_initialize(SYNTH_RX);
    
    // Set TX Synthesizer:
    //PLL_initialize(SYNTH_TX);

}

//void PLL_initialize(SPI_PERIPHERAL phrType)
//{
//    ULONG prog;
//    UCHAR idx, count;
//    for (count = 0, idx = 5; count < NUM_OF_REGISTERS; count++, idx--)
//    {
//        prog = PLL_REGISTERS[idx];
//        prog |= (ULONG)idx;
//        SWSPI_send_word(phrType, prog, 0);
//    }
//    __delay_ms(250);
//    SWSPI_send_word(prog);
//    __delay_ms(250);
//}

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Set TX synthesizer">

void UpdateTxFreq(char* data)
{
    // <editor-fold defaultstate="collapsed" desc="Prepere FREQ data">
    
    uint32_t freqVal = 0;
    
    for(uint8_t idx = 0; idx < FREQ_SIZE_BYTES; idx++)
    {
        freqVal += data[idx]*pow(10,FREQ_SIZE_BYTES - idx - 1);
    }
    
    //registersArray[1] = 0x1234;
   
    // </editor-fold>
   
    // <editor-fold defaultstate="collapsed" desc="Send word to SPI">
   
    SWSPI_send_word(SYNTH_TX, 0x78, 0);
    //PLL_send_bits(make8(prog, 3));
   
   // Wait for Latch PIN signal to be latched:
    
    
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="Send ACK message">
    
       SendAckMessage((MSG_GROUPS)SYNTH_MSG, (MSG_REQUEST)SYNTH_DOWN_SET);
    // </editor-fold>
}

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Set RX synthesizer">

void UpdateRxFreq(char* data)
{
    uint32_t send = 0x87654321;
    //SPI1_Exchange8bitBuffer(&send,4,NULL);
    
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

