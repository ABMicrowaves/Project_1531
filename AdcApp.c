/*******************************************************************************
File name: AdcApp.c                                                         ****
File description:   A2D driver application manager.                         ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
****************************************************************************** */

#include "AdcApp.h"

// <editor-fold defaultstate="collapsed" desc="Global verbs">

ADC_CONVERSION_FORMAT conversionFormat = CONVERSION_LEFT_FORAMT;
ADC_SAMPLE_MODE adcSampleMode = CIRCULAR;
char channel = 0;

uint16_t count = 0;
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="ADC application manager init">

void InitAdcApplicationMgr()
{
    conversionFormat = CONVERSION_LEFT_FORAMT;
    adcSampleMode = CIRCULAR;
    char channel = 0;
}

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Set ADC operation mode">

void SetAdcOperationMode(char* data)
{
    SendAckMessage((MSG_GROUPS)ADC_MSG, (MSG_REQUEST)ADC_OPERATION);
}

void SetConversionResultFormat(char* data)
{
    SendAckMessage((MSG_GROUPS)ADC_MSG, (MSG_REQUEST)ADC_CONVERSION_MODE);
}

void SetChannelMode(char* data)
{
    adcSampleMode = data[0];
    if (adcSampleMode == SINGLE_CHANNEL)
    {
        channel = data[1];
    }
    SendAckMessage((MSG_GROUPS)ADC_MSG, (MSG_REQUEST)ADC_CHANNEL_MODE);
}
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="ADC convert">

void AdcConvert()
// The samples will be stored in array of FLASH_BLOCK_SIZE = 64
// This is in order to minimize flash writes.
{
    
    uint16_t adcRes = 0; 
    
    if (adcSampleMode == CIRCULAR)
    {
        for(uint8_t idx = 0; idx < ADC_NUM_CHANNELS; idx++)
        {
            adc_result_t _adcResult = ADC_GetConversion(channelArr[idx]);
            adcRes = (_adcResult/pow(2,ADC_BIT_SIZE))*VDD;
            FlashSampleWrite(adcRes, idx + 1);
            __delay_ms(250);
        }
    }
    else if (adcSampleMode == SINGLE_CHANNEL)
    {
        adc_result_t _adcResult = ADC_GetConversion(channelArr[channel]);
        adcRes = (_adcResult/pow(2,ADC_BIT_SIZE))*VDD;
        FlashSampleWrite(adcRes, 1);
    }
}
// </editor-fold>
