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
// </editor-fold>


// <editor-fold defaultstate="collapsed" desc="Init synthesizers">

void PLLInitialize()
{
    // Set RX Synthesizer latch interrupt on block B - port 7:   
    IOCB = 0b10000000;
    
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
        // Set TX chip-enable at high:
    SwSpi_Set_CE_Pin(SYNTH_RX, HIGH);
    
    // Update TX registers
    for(uint8_t idx = 0; idx < NUM_OF_REGISTERS; idx++)
    {
        SWSPI_send_word(SYNTH_RX, SYNTH_REGS[idx],3);
    }
}

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Update Synthesizer via EUSART">

void UpdateTxFreq(char* data)
{
    //uint32_t regsInputsArr[NUM_OF_UPDATE_REGISTERS];
    //ZeroArray(regsInputsArr, NUM_OF_UPDATE_REGISTERS);
    
    if(cntRegUpdate < NUM_OF_UPDATE_REGISTERS)
    {
        uint32_t regData = GetIntFromUartData(10, data);
        //regsInputsArr[cntRegUpdate] = regData; 
        SWSPI_send_word(SYNTH_TX, regData, 3);
        __delay_ms(200);
        cntRegUpdate ++;
        SendAckMessage((MSG_GROUPS)SYNTH_MSG, (MSG_REQUEST)SYNTH_REQ_ANTHER_REG);
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
    if(indx)    // TX = 1
    {
        TxMsg[MSG_REQUEST_LOCATION] =  SYNTH_DOWN_READ_DATA;

        // First write FLASH_SIZE:
        //TxMsg[MSG_DATA_LOCATION + 0] = make8(SAMPLE_END_ADDRESS - SAMPLE_START_ADDRESS,1);
        //TxMsg[MSG_DATA_LOCATION + 1] = make8(SAMPLE_END_ADDRESS - SAMPLE_START_ADDRESS,0);
        
        // Second write writeAddress pointer value:
        //TxMsg[MSG_DATA_LOCATION + 2] = make8(SAMPLE_END_ADDRESS - writeAddress,1);
        //TxMsg[MSG_DATA_LOCATION + 3] = make8(SAMPLE_END_ADDRESS - writeAddress,0);

        
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
