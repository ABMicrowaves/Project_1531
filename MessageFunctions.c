/*******************************************************************************
File name: MessageFunctions.c                                               ****
File description:   Include EUSART P2P groups functions definitions.        ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
****************************************************************************** */

#include "MessageFunctions.h"

void GroupControlMcu(MSG_REQUEST request, char* data)
{
    switch (request)
    {
        case CONTROL_TEST_LEDS:
            testLeds();
            break;
            
        case CONTROL_RESET_MCU:
            ResetMcu();
            break;
            
        case CONTROL_PA1_SET:
            break;
            
        case CONTROL_PA2_SET:
            break;
            
        default:
            break;
    }
}

void GroupStatusAndVersion(MSG_REQUEST request, char* data)
{
    switch (request)
    {
        case STATUS_GET_MCU_FW_VERSION:
            GetMcuFwVersion();
            break;
            
        case STATUS_MCU_RUN_TIME:
            GetMcuRunTime();
            break;
        
        default:
            break;
    }
}

void GroupAdc(MSG_REQUEST request, char* data)
{
    switch (request)
    {
        case ADC_CHANNEL_MODE:
            SetChannelMode(data);
            break;
            
        default:
            break;
    }
}
void GroupSynthesizers(MSG_REQUEST request, char* data)
{
    switch (request)
    {
        case SYNTH_TX_INIT_SET:
            //PLLUartInitialize(data);
            break;
        
        case SYNTH_RX_INIT_SET:
            //PLLUartInitialize(data);
            break;
            
        case SYNTH_DOWN_SET:
            UpdateSynthFreq(SYNTH_TX, data);
            break;

        case SYNTH_UP_SET:
            UpdateSynthFreq(SYNTH_RX, data);
            break;
        
        case SYNTH_UP_OPER:
            SetSynthOper(SYNTH_RX);
            break;
            
        case SYNTH_DOWN_OPER:
            SetSynthOper(SYNTH_TX);
            break;
            
        case SYNTH_UP_READ_DATA:
            SynthReadData(SYNTH_RX, data);
            break;
        
        case SYNTH_DOWN_READ_DATA:
            SynthReadData(SYNTH_TX, data);
            break;
            
        default:
            break;
    } 
}

void GroupFlashMemory(MSG_REQUEST request, char* data)
{
    switch (request)
    {
        case FLASH_EREASE_MEMORY:
            FlashEreaseMem();
            break;

        case FLASH_READ_CONDITION:
            FlashReadCondition();
            break;

        case FLASH_REQUEST_RAW_DATA:
            FlashReadUart(data);
            break;
            
        default:
            break;
    }
}

void GroupDAC(MSG_REQUEST request, char* data)
{
    switch (request)
    {
        case DAC_SET_VALUE:
            DacSetValue(data);
            break;
            
        case DAC_READ_VALUE:
            DacReadValue(data);
            break;
            
        default:
            break;
    }
}


