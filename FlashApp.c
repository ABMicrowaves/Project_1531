/*******************************************************************************
File name: FlashApp.c                                                         ****
File description:   Flash driver application manager.                       ****
MCU:                PIC18F45k22                                             ****
Date modified: 29/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
****************************************************************************** */

#include "FlashApp.h"

// <editor-fold defaultstate="collapsed" desc="Global verbs">

uint32_t writeAddress = SAMPLE_START_ADDRESS;
uint32_t readAddress = SAMPLE_START_ADDRESS;


uint32_t numOfValidateSamples = 0;
uint32_t numOfReadSamples = 0;
bool isReWriteDone = false;

adc_result_t sampleArray[WRITE_FLASH_BLOCKSIZE/sizeof(adc_result_t)]; // Since each sample consist 2 bytes.
static int sampleCount = 0;
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Flash read / write">

// <editor-fold defaultstate="collapsed" desc="Flash samples write">

void FlashSampleWrite(adc_result_t sampleData, uint8_t channelNum)
// Each sample data consist 2 bytes, we split it to 2 bytes (low + high).
{
    uint16_t rotateLeft = (channelNum << 12);
    sampleData |= rotateLeft;
    sampleArray[sampleCount] = sampleData;
    sampleCount ++;

    if(((sampleCount*sizeof(adc_result_t)) >= WRITE_FLASH_BLOCKSIZE) && FLASH_IsWriteDone())
    {
        FLASH_WriteBlock(writeAddress, (uint8_t *)sampleArray);
        writeAddress += WRITE_FLASH_BLOCKSIZE;
        if (writeAddress >= SAMPLE_END_ADDRESS)
        {
            writeAddress = SAMPLE_START_ADDRESS;
            isReWriteDone = true;
            if (readAddress == SAMPLE_START_ADDRESS)
            {
                readAddress += WRITE_FLASH_BLOCKSIZE;
            }
        }
        
        if (numOfValidateSamples < ((SAMPLE_START_ADDRESS-SAMPLE_END_ADDRESS)/WRITE_FLASH_BLOCKSIZE))
        {
            numOfValidateSamples++;  
        }
        sampleCount = 0;
    }
}
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Flash samples read via EUSART">

void FlashReadUart(int numOfSampleToRead)
{
    // Create TX packet and clear the memory:
    int j=0;
    int offset = 0;
    char TxMsg[FLASH_TX_PACKET_SIZE + 1];
    ZeroArray(TxMsg, FLASH_TX_PACKET_SIZE + 1);
    
    // No valid samples in flash
    if (FLASH_IsWriteDone() == false)
    {
        return;
    }
    
    if (numOfReadSamples)
    {
        if (numOfValidateSamples)
        {
            offset = numOfValidateSamples - (numOfValidateSamples > numOfSampleToRead)? numOfValidateSamples : numOfSampleToRead;
            if(offset < 0)
            {
                if (abs(offset) > numOfReadSamples)
                {
                    numOfSampleToRead += offset + numOfReadSamples;
                    offset = numOfReadSamples * (-1);

                }

                readAddress += offset * WRITE_FLASH_BLOCKSIZE;
            }
        }
        else
        {
            numOfSampleToRead = (numOfReadSamples > numOfSampleToRead)? numOfSampleToRead : numOfReadSamples;
            readAddress -= numOfSampleToRead * WRITE_FLASH_BLOCKSIZE;
        }

        if (readAddress <= SAMPLE_START_ADDRESS)
        {
            readAddress = SAMPLE_START_ADDRESS;
        }
    }
    else
    {
        if ((isReWriteDone) && (readAddress <= writeAddress))
        {
            readAddress = writeAddress + WRITE_FLASH_BLOCKSIZE;
            if (readAddress >= SAMPLE_END_ADDRESS)
            {
                readAddress = SAMPLE_START_ADDRESS;
            }
            //isReWriteDone = false;
        }
        else
        {
            if(numOfValidateSamples == 0)
            {
                SendAckMessage((MSG_GROUPS)FLASH_MSG, (MSG_REQUEST)FLASH_NO_SAMPLE_YET);
                return;
            }
                
        }
    }

    // Now fill it:
    TxMsg[MSG_MAGIC_LOCATION] =  MSG_MAGIC_A;
    TxMsg[MSG_GROUP_LOCATION] =  FLASH_MSG;
    TxMsg[MSG_REQUEST_LOCATION] =  FLASH_SEND_RAW_DATA;
    TxMsg[MSG_DATA_SIZE_LOCATION] = WRITE_FLASH_BLOCKSIZE;
    
    for (j=0; j<numOfSampleToRead; j++)
    {
        // Fill TX array with data:
        for(int idx = 0; idx < WRITE_FLASH_BLOCKSIZE; idx++)
        {
            TxMsg[MSG_DATA_LOCATION + idx] = FLASH_ReadByte(readAddress + idx); 
        }

        readAddress += WRITE_FLASH_BLOCKSIZE;
        if (readAddress >= SAMPLE_END_ADDRESS)
        {
            readAddress = SAMPLE_START_ADDRESS;
        }
        TxMsg[FLASH_TX_PACKET_SIZE] = crc8(TxMsg, FLASH_TX_PACKET_SIZE);

        WriteUartMessage(TxMsg, FLASH_TX_PACKET_SIZE + 1);
        
        if(numOfValidateSamples)
        {
            if (numOfReadSamples < ((SAMPLE_START_ADDRESS-SAMPLE_END_ADDRESS)/WRITE_FLASH_BLOCKSIZE))
            {
                numOfReadSamples++;
            }
            if (numOfValidateSamples > 0)
            {
                numOfValidateSamples--;  
            }
        }
    }
}
// </editor-fold>

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Flash utilites">

void FlashEreaseMem(void)
{
    writeAddress = SAMPLE_START_ADDRESS;
    readAddress = SAMPLE_START_ADDRESS;
    numOfValidateSamples = 0;
    ZeroArray(sampleArray, WRITE_FLASH_BLOCKSIZE/sizeof(adc_result_t));
    SendAckMessage((MSG_GROUPS)FLASH_MSG, (MSG_REQUEST)FLASH_EREASE_MEMORY);
}


void FlashReadCondition(void)
{
    // Create TX packet and clear the memory:
    char TxMsg[FLASH_READ_CONDITION_PACKET_SIZE + 1];
    ZeroArray(TxMsg, FLASH_READ_CONDITION_PACKET_SIZE + 1);
    
    // Now fill it:
    TxMsg[MSG_MAGIC_LOCATION] =  MSG_MAGIC_A;
    TxMsg[MSG_GROUP_LOCATION] =  FLASH_MSG;
    TxMsg[MSG_REQUEST_LOCATION] =  FLASH_READ_CONDITION;
    TxMsg[MSG_DATA_SIZE_LOCATION] = FLASH_READ_CONDITION_MAX_DATA_SIZE;

    // Fill TX array with data:
    
    // First write FLASH_SIZE:
    TxMsg[MSG_DATA_LOCATION + 0] = make8(SAMPLE_END_ADDRESS - SAMPLE_START_ADDRESS,1);
    TxMsg[MSG_DATA_LOCATION + 1] = make8(SAMPLE_END_ADDRESS - SAMPLE_START_ADDRESS,0);
    
    // Second write writeAddress pointer value:
    TxMsg[MSG_DATA_LOCATION + 2] = make8(SAMPLE_END_ADDRESS - writeAddress,1);
    TxMsg[MSG_DATA_LOCATION + 3] = make8(SAMPLE_END_ADDRESS - writeAddress,0);
    
    TxMsg[FLASH_READ_CONDITION_PACKET_SIZE] = crc8(TxMsg, FLASH_READ_CONDITION_PACKET_SIZE);
    
    WriteUartMessage(TxMsg, FLASH_READ_CONDITION_PACKET_SIZE + 1);
}

bool CheckFlashPrecentage(void)
{
    double precentage = ((double)(SAMPLE_END_ADDRESS - writeAddress) / SAMPLE_END_ADDRESS) * 100;
    return (precentage > FLASH_FREE_SPACE_THRESHOLD) ? true : false;
}

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="EEPROM functions">

uint8_t EepromRead(uint8_t address)
{
    return DATAEE_ReadByte(address);
}

void EepromWrite(uint8_t address, uint8_t data)
{
    DATAEE_WriteByte(address, data);
}

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Tests Flash / EEPROM">

bool FlashTest(int startAddress, int numOfSamples)
{
    if(numOfSamples > MAX_NUMBER_BYTES_IN_TEST)
    {
        return false;
    }
    uint8_t buff[MAX_NUMBER_BYTES_IN_TEST];
    for(uint8_t idx = 0; idx < numOfSamples; idx++)
    {       
        buff[idx] = idx;
    }
    
    FLASH_WriteBlock(startAddress, buff);
    
    for(uint8_t idx = 0; idx < numOfSamples; idx++)
    {
        uint8_t FlashData = FLASH_ReadByte(startAddress + idx);
        if(FlashData != idx)
        {
            return false;
        }
    }
    
    return true;
}

bool EepromTest(int startAddress, int numOfSamples)
{
    if(numOfSamples > MAX_NUMBER_BYTES_IN_TEST)
    {
        return false;
    }
    
    for(uint8_t idx = 0; idx < numOfSamples; idx++)
    {       
        DATAEE_WriteByte(startAddress + idx, idx);
    }
    
    for(uint8_t idx = 0; idx < 256; idx++)
    {
        uint8_t EEdata = DATAEE_ReadByte(startAddress + idx);
        if(EEdata != idx)
        {
            return false;
        }
    }
    return true;
}

// </editor-fold>
