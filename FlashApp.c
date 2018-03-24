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
        if (writeAddress >= SAMPLE_END_ADDRESS) // Treat cycle operation when flash space end.
        {
            writeAddress = SAMPLE_START_ADDRESS;
            isReWriteDone = true;
            if (readAddress == SAMPLE_START_ADDRESS)
            {
                readAddress += WRITE_FLASH_BLOCKSIZE;
            }
        }
        
        // Treat normal operation when we are in middle of flash size.
        if (numOfValidateSamples < ((SAMPLE_START_ADDRESS-SAMPLE_END_ADDRESS)/WRITE_FLASH_BLOCKSIZE))
        {
            numOfValidateSamples++;  
        }
        sampleCount = 0;
    }
}
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Flash samples read via EUSART">

void FlashReadUart(char* data)
// numOfReadSamples = Count how many samples had been read.
// numOfSampleToRead = Indicate how many samples user request.
// numOfValidateSamples = How many samples there is to read.
// FLASH_IsWriteDone - Check if currently there is no write operation on flash.
{
    int16_t numOfSampleToRead = 0x0;
    INT_VAL val = GetIntFromUartData(10, data);

    int numOfSampleToRead = val.num;
    
    char TxMsg[FLASH_TX_PACKET_SIZE + 1];
    
    if (FLASH_IsWriteDone() == false)
    // Check we are in middle of writing to flash
    {
        return;
    }
    
    if(numOfValidateSamples == 0)
    {
        SendAckMessage((MSG_GROUPS)FLASH_MSG, (MSG_REQUEST)FLASH_NO_SAMPLE_YET);
    }
    
    // Get lowest of {User request samples, valid samples}
    numOfSampleToRead = numOfSampleToRead >=  numOfValidateSamples ? numOfValidateSamples : numOfSampleToRead;
    
    // Set readAddress
    readAddress = writeAddress;
    
    for (int j=0; j<numOfSampleToRead; j++)
    {
        // set readAddress
        if(readAddress > 0)
        {
            readAddress -= WRITE_FLASH_BLOCKSIZE;
        }
        else
        {
            readAddress = SAMPLE_END_ADDRESS - WRITE_FLASH_BLOCKSIZE;
        }
        
        // Fill TX EUSART packet with data:
        ZeroArray(TxMsg, FLASH_TX_PACKET_SIZE + 1);
        TxMsg[MSG_MAGIC_LOCATION] =  MSG_MAGIC_A;
        TxMsg[MSG_GROUP_LOCATION] =  FLASH_MSG;
        TxMsg[MSG_REQUEST_LOCATION] =  FLASH_SEND_RAW_DATA;
        TxMsg[MSG_DATA_SIZE_LOCATION] = WRITE_FLASH_BLOCKSIZE;
        
        for(int idx = 0; idx < WRITE_FLASH_BLOCKSIZE; idx++)
        {
            TxMsg[MSG_DATA_LOCATION + idx] = FLASH_ReadByte(readAddress + idx); 
        }
        
        TxMsg[FLASH_TX_PACKET_SIZE] = crc8(TxMsg, FLASH_TX_PACKET_SIZE);

        WriteUartMessage(TxMsg, FLASH_TX_PACKET_SIZE + 1);
        __delay_ms(200);
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