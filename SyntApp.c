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
    InitSynth(SYNTH_TX);
    InitSynth(SYNTH_RX);
}

void InitSynth(SPI_PERIPHERAL cType)
{
    SwSpi_Set_CE_Pin(cType, HIGH);
    
    uint8_t regNum = 0;
    uint32_t EepromVal = 0x0;
    
    // Update TX registers
    for(uint8_t idx = 0; idx < NUM_OF_REGISTERS; idx++)
    {
        regNum = NUM_OF_REGISTERS - idx - 1;
        if(regNum == 0x0 || regNum == 0x1 || regNum == 0x2 || regNum == 0x4 || regNum == 0x6 || regNum == 0xA)
        {
            if(cType == SYNTH_TX)
            {
                EepromVal = ReadIntFromEeprom(EEPROM_SYNTH_TX_REGS_ADDRESS_OFSEET | SYNTH_ADDRES[regNum], 4);
            }
            else if (cType == SYNTH_RX)
            {
                EepromVal = ReadIntFromEeprom(EEPROM_SYNTH_RX_REGS_ADDRESS_OFSEET | SYNTH_ADDRES[regNum], 4);
            }
            
            if(EepromVal == 0xFFFFFFFF)
            {
                SWSPI_send_word(cType, SYNTH_REGS[idx],3);
            }
            else
            {
                SWSPI_send_word(cType, EepromVal,3);
            }
        }
        else
        {
            SWSPI_send_word(cType, SYNTH_REGS[idx],3);
        }
    }
}
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Update Synthesizer via EUSART">

void UpdateSynthFreq(SPI_PERIPHERAL cType, char* data)
{
    INT_VAL retVal;
    if(cntRegUpdate < NUM_OF_UPDATE_REGISTERS)
    {
        retVal = GetIntFromUartData(10, data);
        SWSPI_send_word(cType, retVal.num, 3);
        if(cType == SYNTH_TX)
        {
            StoreIntInEeprom(retVal.num, EEPROM_SYNTH_TX_REGS_ADDRESS_OFSEET | SYNTH_ADDRES[retVal.con], 4);
            SendAckMessage((MSG_GROUPS)SYNTH_MSG, (MSG_REQUEST)SYNTH_REQ_ANTHER_TX_REG);
        }
        else if(cType == SYNTH_RX)
        {
            StoreIntInEeprom(retVal.num, EEPROM_SYNTH_RX_REGS_ADDRESS_OFSEET | SYNTH_ADDRES[retVal.con], 4);
            SendAckMessage((MSG_GROUPS)SYNTH_MSG, (MSG_REQUEST)SYNTH_REQ_ANTHER_RX_REG);
        }
        cntRegUpdate ++;
    }
    
    else
    {
        cntRegUpdate = 0;
        if(cType == SYNTH_TX)
        {
            SendAckMessage((MSG_GROUPS)SYNTH_MSG, (MSG_REQUEST)SYNTH_DOWN_SET);
        }
        else if(cType == SYNTH_RX)
        {
            SendAckMessage((MSG_GROUPS)SYNTH_MSG, (MSG_REQUEST)SYNTH_UP_SET);
        }
        
    }
}
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Synthesizers control and read data">

void SetSynthOper(SPI_PERIPHERAL cType)
{
    if(cType == SYNTH_TX)
    {
        SynthTxOper = !SynthTxOper;
        if(SynthTxOper)
        {
            InitSynth(cType);
        }
        else
        {
            SwSpi_Set_CE_Pin(cType, LOW);
        }
        SendAckMessage((MSG_GROUPS)SYNTH_MSG, (MSG_REQUEST)SYNTH_DOWN_OPER);
    }
    else if (cType == SYNTH_RX)
    {
        SynthRxOper = !SynthRxOper;
        if(SynthRxOper)
        {
            InitSynth(cType);
        }
        else
        {
            SwSpi_Set_CE_Pin(cType, LOW);
        }
        SendAckMessage((MSG_GROUPS)SYNTH_MSG, (MSG_REQUEST)SYNTH_UP_OPER);
    }
}


void SynthReadData(SPI_PERIPHERAL cType, char* data)
{
    uint32_t eepromDataArray[3];
    char TxMsg[SYNTH_READ_CONDITION_PACKET_SIZE + 1];
    ZeroArray(TxMsg, SYNTH_READ_CONDITION_PACKET_SIZE + 1);
    
    // Now fill it:
    TxMsg[MSG_MAGIC_LOCATION] =  MSG_MAGIC_A;
    TxMsg[MSG_GROUP_LOCATION] =  SYNTH_MSG;
    TxMsg[MSG_DATA_SIZE_LOCATION] = SYNTH_READ_CONDITION_MAX_DATA_SIZE;
     
    if(cType == SYNTH_TX)
    {
        TxMsg[MSG_REQUEST_LOCATION] =  SYNTH_DOWN_READ_DATA;
        eepromDataArray[0] = ReadIntFromEeprom(EEPROM_SYNTH_TX_REGS_ADDRESS_OFSEET | SYNTH_ADDRES[0], 4);
        eepromDataArray[1] = ReadIntFromEeprom(EEPROM_SYNTH_TX_REGS_ADDRESS_OFSEET | SYNTH_ADDRES[1], 4);
        eepromDataArray[2] = ReadIntFromEeprom(EEPROM_SYNTH_TX_REGS_ADDRESS_OFSEET | SYNTH_ADDRES[2], 4);
    }
    else if (cType == SYNTH_RX)
    {
        TxMsg[MSG_REQUEST_LOCATION] =  SYNTH_UP_READ_DATA;
        eepromDataArray[0] = ReadIntFromEeprom(EEPROM_SYNTH_RX_REGS_ADDRESS_OFSEET | SYNTH_ADDRES[0], 4);
        eepromDataArray[1] = ReadIntFromEeprom(EEPROM_SYNTH_RX_REGS_ADDRESS_OFSEET | SYNTH_ADDRES[1], 4);
        eepromDataArray[2] = ReadIntFromEeprom(EEPROM_SYNTH_RX_REGS_ADDRESS_OFSEET | SYNTH_ADDRES[2], 4);
    }
    
    for(int regNum = 0; regNum < 4; regNum++)
    {
        for(int byteNum = 0; byteNum < 4; byteNum++)
        {
            TxMsg[MSG_DATA_LOCATION + regNum + byteNum] = make8(eepromDataArray[regNum], byteNum); 
        }
    }
    
    TxMsg[SYNTH_READ_CONDITION_PACKET_SIZE] = crc8(TxMsg, SYNTH_READ_CONDITION_PACKET_SIZE);
    WriteUartMessage(TxMsg, SYNTH_READ_CONDITION_PACKET_SIZE + 1);    
}


// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="synthesizers LD pins detection">

void SynthLdDetect(void)
{
    bool synthLdTxPrevState = false, synthLdTxCurrentState = false; 
}
// </editor-fold>
