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

#define ADC_NUM_CHANNELS    (9)
#define VDD                 (3340)
#define ADC_BIT_SIZE        (10)

typedef enum
{
	CIRCULAR        = 0x0,
    SINGLE_CHANNEL  = 0x1,
}ADC_SAMPLE_MODE;


const adc_channel_t channelArr[ADC_NUM_CHANNELS]  = 
{
    0x4,     // RREV
    0x5,     // FFWR2
    0x6,     // FFWR1
    0x7,     // RF_INDET
    0x8,     // P7V_SENSE
    0x9,     // 28V_SNS
    0xA,     // UP_TEMP
    0xD,     // DOWN_TEMP
    0x19,    // PA_TEMP
};

    
void SetChannelMode(char* data);
void InitAdcApplicationMgr();
void AdcConvert();

#endif	/* ADCAPP_H */

