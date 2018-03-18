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
bool SynthTxOper = true;
bool SynthRxOper = true;
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Init synthesizers">

void PLLInitialize()
{
    // Set RX Synthesizer latch interrupt on block B - port 7:   
    IOCB = 0b10000000;
//    StoreIntInEeprom(0x12344321, EEPROM_SYNTH_TX_REGS_ADDRESS_OFSEET | SYNTH_ADDRES[1], 4);
//    uint32_t dacInput = ReadIntFromEeprom(EEPROM_SYNTH_TX_REGS_ADDRESS_OFSEET | SYNTH_ADDRES[1], 4);
    InitTxSynth();
    InitRxSynth();
}

void PLLUartInitialize(char* data)
// For future use if needed.
{
    
}

void InitTxSynth(void)
{
    // Set TX chip-enable at high:
    SwSpi_Set_CE_Pin(SYNTH_TX, HIGH);
    
    
    // Update TX registers
    for(uint8_t idx = 0; idx < NUM_OF_REGISTERS; idx++)
    {
        SWSPI_send_word(SYNTH_TX, SYNTH_REGS[idx],3);
    }
}

void InitRxSynth(void)
{
    // Set RX chip-enable at high:
    SwSpi_Set_CE_Pin(SYNTH_RX, HIGH);
    
    // Update RX registers
    for(uint8_t idx = 0; idx < NUM_OF_REGISTERS; idx++)
    {
        SWSPI_send_word(SYNTH_RX, SYNTH_REGS[idx],3);
    }
}

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Update Synthesizer via EUSART">

void UpdateTxFreq(char* data)
{
    INT_VAL retVal;
    if(cntRegUpdate < NUM_OF_UPDATE_REGISTERS)
    {
        retVal = GetIntFromUartData(10, data);
        SWSPI_send_word(SYNTH_TX, retVal.num, 3);
        StoreIntInEeprom(retVal.num, EEPROM_SYNTH_TX_REGS_ADDRESS_OFSEET | SYNTH_ADDRES[retVal.con], 4);
        cntRegUpdate ++;
        SendAckMessage((MSG_GROUPS)SYNTH_MSG, (MSG_REQUEST)SYNTH_REQ_ANTHER_TX_REG);
    }
    
    else
    {
        cntRegUpdate = 0;
        SendAckMessage((MSG_GROUPS)SYNTH_MSG, (MSG_REQUEST)SYNTH_DOWN_SET);
    }
}

void UpdateRxFreq(char* data)
{
    if(cntRegUpdate < NUM_OF_UPDATE_REGISTERS)
    {
        
        //uint32_t regData = GetIntFromUartData(10, data);
        //SWSPI_send_word(SYNTH_RX, regData, 3);
        cntRegUpdate ++;

        SendAckMessage((MSG_GROUPS)SYNTH_MSG, (MSG_REQUEST)SYNTH_REQ_ANTHER_RX_REG);
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

// <editor-fold defaultstate="collapsed" desc="Synthesizers control and read data">

void SetSynthTxOper()
{
    SynthTxOper = !SynthTxOper;
    if(SynthTxOper)
    {
        InitTxSynth();
    }
    else
    {
        SwSpi_Set_CE_Pin(SYNTH_TX, LOW);
    }
    SendAckMessage((MSG_GROUPS)SYNTH_MSG, (MSG_REQUEST)SYNTH_DOWN_OPER);
}

void SetSynthRxOper()
{
    SynthRxOper = !SynthRxOper;
    if(SynthRxOper)
    {
        InitRxSynth();
    }
    else
    {
        SwSpi_Set_CE_Pin(SYNTH_RX, LOW);
    }
    SendAckMessage((MSG_GROUPS)SYNTH_MSG, (MSG_REQUEST)SYNTH_UP_OPER);
}

void SynthReadData(char* data)
{
    // Create TX packet and clear the memory:
    char TxMsg[SYNTH_READ_CONDITION_PACKET_SIZE + 1];
    ZeroArray(TxMsg, SYNTH_READ_CONDITION_PACKET_SIZE + 1);
    
    // Now fill it:
    TxMsg[MSG_MAGIC_LOCATION] =  MSG_MAGIC_A;
    TxMsg[MSG_GROUP_LOCATION] =  SYNTH_MSG;
    TxMsg[MSG_DATA_SIZE_LOCATION] = SYNTH_READ_CONDITION_MAX_DATA_SIZE;
    
    uint8_t indx = data[0]; 
    if(indx == 0x0)    // TX = 1
    {
        TxMsg[MSG_REQUEST_LOCATION] =  SYNTH_UP_READ_DATA;
        //TxMsg[MSG_DATA_LOCATION + 0] = 
    }
    else
    {
        TxMsg[MSG_REQUEST_LOCATION] =  SYNTH_DOWN_READ_DATA;

    }
    
    TxMsg[SYNTH_READ_CONDITION_PACKET_SIZE] = crc8(TxMsg, SYNTH_READ_CONDITION_PACKET_SIZE);
    WriteUartMessage(TxMsg, SYNTH_READ_CONDITION_PACKET_SIZE + 1);    
}


// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="synthesizers ISR">

void SYNTH_ISR(void)
{
    
}
// </editor-fold>
