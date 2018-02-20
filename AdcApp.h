/*******************************************************************************
File name: AdcApp.h                                                         ****
File description:   A2D driver application manager.                         ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
*******************************************************************************/

#ifndef ADCAPP_H
#define	ADCAPP_H

#include "SystemCommon.h"

#define ADC_NUM_CHANNELS (7)
#define VDD             (3340)
#define ADC_BIT_SIZE    (10)

#ifdef	__cplusplus
extern "C" {
#endif
    
typedef enum
{
	CONVERSION_LEFT_FORAMT = 0,
	CONVERSION_RIGHT_FORAMT,
}ADC_CONVERSION_FORMAT;

typedef enum
{
	CIRCULAR = 0x0,
    SINGLE_CHANNEL = 0x1,
}ADC_SAMPLE_MODE;


const adc_channel_t channelArr[ADC_NUM_CHANNELS]  = 
{
    0x7,        // ADC_RE2
    0x6,        // ADC_RE1
    0x5,        // ADC_RE0
    0x4,        // ADC_RA5
    0x19,       // ADC_RD5
    0xA,        // ADC_RB1
    0xD,        // ADC_RB5
};

void SetAdcOperationMode(char* data);
void SetConversionResultFormat(char* data);
void SetChannelMode(char* data);
void InitAdcApplicationMgr();
void AdcConvert();

#ifdef	__cplusplus
}
#endif

#endif	/* ADCAPP_H */

