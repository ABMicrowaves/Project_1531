/*******************************************************************************
File name: SyntApp.c                                                        ****
File description:   TX and RX Synthesizers (ADF-5355) Application manager.  ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
*******************************************************************************/

#include "SyntApp.h"
// <editor-fold defaultstate="collapsed" desc="Global verbs">

uint8_t cntRegUpdate = 0;
// </editor-fold>


// <editor-fold defaultstate="collapsed" desc="Init synthesizers">

void PLLInitialize()
{
    //StoreIntInEeprom(0x1110FCC9, EEPROM_SYNTH_TX_REGS_ADDRESS, 4);
    //uint32_t test = ReadIntFromEeprom(EEPROM_SYNTH_TX_REGS_ADDRESS, 4);
    
    
    // Set RX Synthesizer latch interrupt on block B - port 7:   
    IOCB = 0b10000000;
    
    // Set TX chip-enable at high:
    SwSpi_Set_CE_Pin(SYNTH_TX, HIGH);
    
    // Update TX registers
    for(uint8_t idx = 0; idx < NUM_OF_REGISTERS; idx++)
    {
        SWSPI_send_word(SYNTH_TX, SYNTH_REGS[idx],3);
    }
    //uint8_t dec = EepromRead(0x0);
//    if(dec == 0x34)
//    {
//        testLeds();
//    }
}

void PLLUartInitialize(char* data)
{
    
}

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Update Synthesizer via EUSART">

void UpdateTxFreq(char* data)
{
    if(cntRegUpdate < NUM_OF_UPDATE_REGISTERS)
    {
        uint32_t regData = GetIntFromUartData(10, data);
        SWSPI_send_word(SYNTH_TX, regData, 3);
        cntRegUpdate ++;
    }
    
    else
    {
        cntRegUpdate = 0;
        SendAckMessage((MSG_GROUPS)SYNTH_MSG, (MSG_REQUEST)SYNTH_DOWN_SET);
    }
    //EepromWrite(0x0, 0x1234);
}

void UpdateRxFreq(char* data)
{
    if(cntRegUpdate < NUM_OF_UPDATE_REGISTERS)
    {
        uint32_t regData = GetIntFromUartData(10, data);
        SWSPI_send_word(SYNTH_RX, regData, 3);
        cntRegUpdate ++;
    }
    
    else
    {
        cntRegUpdate = 0;
        SendAckMessage((MSG_GROUPS)SYNTH_MSG, (MSG_REQUEST)SYNTH_UP_SET);
    }
}
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Reset syntesizers">

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="synthesizers ISR">

void SYNTH_ISR(void)
{
    
}
// </editor-fold>
