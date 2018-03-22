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

// Lock detect
int8_t synthLdRxCnt = SYNTH_LD_TRIES;
int8_t synthLdTxCnt = SYNTH_LD_TRIES;

//volatile bool synthLdRxArray[14];
uint8_t synthLdRxArrayCnt = 0; 
uint8_t synthLdTxArrayCnt = 0;
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Init synthesizers">

void PLLInitialize()
{
    InitSynth(SYNTH_TX);
    InitSynth(SYNTH_RX);
    
    // Initialize LD array
    FillArray(synthLdRxArray, sizeof(synthLdRxArray), 0xFF);
}

void InitSynth(SPI_PERIPHERAL cType)
{
    SwSpi_Set_CE_Pin(cType, HIGH);
    
    uint8_t regNum = 0;
    uint32_t EepromVal = 0x0;
    
    // Update TX registers
    for(uint8_t idx = 0; idx < NUM_OF_TOTAL_REGISTERS; idx++)
    {
        regNum = NUM_OF_TOTAL_REGISTERS - idx - 1;
        if(regNum == 0x0 || regNum == 0x1 || regNum == 0x2 || regNum == 0x4 || regNum == 0x6 || regNum == 0xA)
        {
            if(cType == SYNTH_TX)
            {
                EepromVal = ReadIntFromEeprom(EEPROM_SYNTH_TX_REGS_ADDRESS_OFSEET | SYNTH_ADDRES[regNum], 4);
                if(EepromVal == 0xFFFFFFFF)
                {
                    SWSPI_send_word(cType, SYNTH_REGS[idx],3);
                    StoreIntInEeprom(SYNTH_REGS[idx], EEPROM_SYNTH_TX_REGS_ADDRESS_OFSEET | SYNTH_ADDRES[regNum], 4);
                }
                else
                {
                    SWSPI_send_word(cType, EepromVal,3);
                }
            }
            else if (cType == SYNTH_RX)
            {
                EepromVal = ReadIntFromEeprom(EEPROM_SYNTH_RX_REGS_ADDRESS_OFSEET | SYNTH_ADDRES[regNum], 4);
                if(EepromVal == 0xFFFFFFFF)
                {
                    SWSPI_send_word(cType, SYNTH_REGS[idx],3);
                    StoreIntInEeprom(SYNTH_REGS[idx], EEPROM_SYNTH_RX_REGS_ADDRESS_OFSEET | SYNTH_ADDRES[regNum], 4);
                }
                else
                {
                    SWSPI_send_word(cType, EepromVal,3);
                }
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
    uint8_t regNum = 0, byteNum = 0; 
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
    
    for(regNum = 0; regNum < NUM_OF_UART_TX_UPDATE_REGS; regNum++)
    {
        for(byteNum = 0; byteNum < (NUM_OF_BYTES_UART_TX_UPDATE_REGS); byteNum++)
        {
            uint8_t data = make8(eepromDataArray[regNum], byteNum);
            TxMsg[MSG_DATA_LOCATION + (NUM_OF_UART_TX_UPDATE_REGS + 1)*regNum + byteNum] = data; 
        }
    }
    
    TxMsg[IDX_SYNTH_OPER_STATE_PLACE] = 0x9;
    TxMsg[SYNTH_READ_CONDITION_PACKET_SIZE] = crc8(TxMsg, SYNTH_READ_CONDITION_PACKET_SIZE);
    WriteUartMessage(TxMsg, SYNTH_READ_CONDITION_PACKET_SIZE + 1);    
}


// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="synthesizers LD pins detection">

void SynthLdDetect(void)
{
    // <editor-fold defaultstate="collapsed" desc="Synth Rx lock detect">
    
    if(RX_SYNT_LD_GetValue() == LOW)
    {
        if(synthLdRxCnt > 0)
        {
            InitSynth(SYNTH_RX);
            synthLdRxCnt--;
        }
        else
        {
            BlinkErrorLeds(FAIL_SYNTH_RX_LATCH);
        }
        synthLdRxArray[synthLdRxArrayCnt++ % SYNTH_LD_NUM_BITS] = UNLOCK;
    }
    else
    {
        synthLdRxCnt = SYNTH_LD_TRIES;
        synthLdRxArray[synthLdRxArrayCnt++ % SYNTH_LD_NUM_BITS] = LOCK;
    }
    // </editor-fold>

    // <editor-fold defaultstate="collapsed" desc="Synth Tx lock detect">
    
    if(TX_SYNT_LD_GetValue() == LOW)
    {
        if(synthLdTxCnt > 0)
        {
            InitSynth(SYNTH_TX);
            synthLdTxCnt--;
        }
        else
        {
            BlinkErrorLeds(FAIL_SYNTH_TX_LATCH);
        }
        synthLdTxArray[synthLdTxArrayCnt++ % SYNTH_LD_NUM_BITS] = UNLOCK;
    }
    else
    {
        synthLdTxCnt = SYNTH_LD_TRIES;
        synthLdTxArray[synthLdTxArrayCnt++ % SYNTH_LD_NUM_BITS] = LOCK;
    }
    // </editor-fold>
}
// </editor-fold>
