/*******************************************************************************
File name: main.c                                                           ****
File description:   Main entry of the system flow. Impelemt sigle threaded  ****
 *                  system ("BERMETAL")                                     ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
****************************************************************************** */

#include "SytstemSettings.h"
#include "SystemCommon.h"

void main(void)
{
    // First initialize system settings:
    SetMcuSystem();
    
    // Second set application managers:
    InitSystemApplicationManagers();

    // Then send keep alive signal to PC host application:
    SendSystemStartAck();
    
    // Indicate by Green led that system start OK:
    BlinkOkLeds(OK_START_SYSTEM);
            
    while (1)
    {    
        readUartMessage();
        
        if (Timer0_OneSec == true)
        {   
            SetMcuRunTime();
            Timer0_OneSec = false; 
        }
        else if (Timer0_Sampling == true)
        {
            keepAliveSignalLed();
            
            if(true == CheckFlashPrecentage())
            {
                BlinkErrorLeds(FAIL_FLASH_MORE_THEN_HELF);
            }
            
            // Sampling is always occur even if Flash is full.
            AdcConvert();
            Timer0_Sampling = false;
        }
        else if (Timer0_KeepAlive == true)
        {
            keepAliveSignalUart();
            Timer0_KeepAlive = false; 
        }
        else if (Timer0_SynthLd == true)
        {
            SynthLdDetect();
            Timer0_SynthLd = false; 
        }
    }
}
