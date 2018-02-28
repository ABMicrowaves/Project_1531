/*******************************************************************************
File name: SytstemSettings.c                                                ****
File description:   Include functions relate to operation of MCU.           ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
****************************************************************************** */

#include "SytstemSettings.h"

void SetMcuSystem(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
}

void InitSystemApplicationManagers(void)
{
    // Start and set internal ADC
    InitAdcApplicationMgr();
    
    // Start main timer
    TMR0_StartTimer();
    
    // Initialize seven segment
    InitSevenSegment();
    
    // Initialize Synthesizers
    PLLInitialize();
    
    // Clear MCU run - time
    ClearMcuRunTime();
    
    // Initialize DAC
    DacInit();
}



