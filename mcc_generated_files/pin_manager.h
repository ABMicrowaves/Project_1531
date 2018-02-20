/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB(c) Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.35
        Device            :  PIC18F45K22
        Version           :  1.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

    Microchip licenses to you the right to use, modify, copy and distribute
    Software only when embedded on a Microchip microcontroller or digital signal
    controller that is integrated into your product or third party product
    (pursuant to the sublicense terms in the accompanying license agreement).

    You should refer to the license agreement accompanying this Software for
    additional information regarding your rights and obligations.

    SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
    EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
    MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
    IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
    CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
    OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
    INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
    CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
    SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
    (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

*/


#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set DAC_LDAC aliases
#define DAC_LDAC_TRIS               TRISAbits.TRISA1
#define DAC_LDAC_LAT                LATAbits.LATA1
#define DAC_LDAC_PORT               PORTAbits.RA1
#define DAC_LDAC_ANS                ANSELAbits.ANSA1
#define DAC_LDAC_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define DAC_LDAC_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define DAC_LDAC_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define DAC_LDAC_GetValue()           PORTAbits.RA1
#define DAC_LDAC_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define DAC_LDAC_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define DAC_LDAC_SetAnalogMode()  do { ANSELAbits.ANSA1 = 1; } while(0)
#define DAC_LDAC_SetDigitalMode() do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set DAC_SYNC aliases
#define DAC_SYNC_TRIS               TRISAbits.TRISA2
#define DAC_SYNC_LAT                LATAbits.LATA2
#define DAC_SYNC_PORT               PORTAbits.RA2
#define DAC_SYNC_ANS                ANSELAbits.ANSA2
#define DAC_SYNC_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define DAC_SYNC_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define DAC_SYNC_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define DAC_SYNC_GetValue()           PORTAbits.RA2
#define DAC_SYNC_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define DAC_SYNC_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define DAC_SYNC_SetAnalogMode()  do { ANSELAbits.ANSA2 = 1; } while(0)
#define DAC_SYNC_SetDigitalMode() do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set DAC_CLK aliases
#define DAC_CLK_TRIS               TRISAbits.TRISA3
#define DAC_CLK_LAT                LATAbits.LATA3
#define DAC_CLK_PORT               PORTAbits.RA3
#define DAC_CLK_ANS                ANSELAbits.ANSA3
#define DAC_CLK_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define DAC_CLK_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define DAC_CLK_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define DAC_CLK_GetValue()           PORTAbits.RA3
#define DAC_CLK_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define DAC_CLK_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define DAC_CLK_SetAnalogMode()  do { ANSELAbits.ANSA3 = 1; } while(0)
#define DAC_CLK_SetDigitalMode() do { ANSELAbits.ANSA3 = 0; } while(0)

// get/set DAC_DATA aliases
#define DAC_DATA_TRIS               TRISAbits.TRISA4
#define DAC_DATA_LAT                LATAbits.LATA4
#define DAC_DATA_PORT               PORTAbits.RA4
#define DAC_DATA_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define DAC_DATA_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define DAC_DATA_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define DAC_DATA_GetValue()           PORTAbits.RA4
#define DAC_DATA_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define DAC_DATA_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)

// get/set ADC_RA5 aliases
#define ADC_RA5_TRIS               TRISAbits.TRISA5
#define ADC_RA5_LAT                LATAbits.LATA5
#define ADC_RA5_PORT               PORTAbits.RA5
#define ADC_RA5_ANS                ANSELAbits.ANSA5
#define ADC_RA5_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define ADC_RA5_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define ADC_RA5_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define ADC_RA5_GetValue()           PORTAbits.RA5
#define ADC_RA5_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define ADC_RA5_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define ADC_RA5_SetAnalogMode()  do { ANSELAbits.ANSA5 = 1; } while(0)
#define ADC_RA5_SetDigitalMode() do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set ADC_RB1 aliases
#define ADC_RB1_TRIS               TRISBbits.TRISB1
#define ADC_RB1_LAT                LATBbits.LATB1
#define ADC_RB1_PORT               PORTBbits.RB1
#define ADC_RB1_WPU                WPUBbits.WPUB1
#define ADC_RB1_ANS                ANSELBbits.ANSB1
#define ADC_RB1_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define ADC_RB1_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define ADC_RB1_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define ADC_RB1_GetValue()           PORTBbits.RB1
#define ADC_RB1_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define ADC_RB1_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define ADC_RB1_SetPullup()      do { WPUBbits.WPUB1 = 1; } while(0)
#define ADC_RB1_ResetPullup()    do { WPUBbits.WPUB1 = 0; } while(0)
#define ADC_RB1_SetAnalogMode()  do { ANSELBbits.ANSB1 = 1; } while(0)
#define ADC_RB1_SetDigitalMode() do { ANSELBbits.ANSB1 = 0; } while(0)

// get/set P7V_SENSE aliases
#define P7V_SENSE_TRIS               TRISBbits.TRISB2
#define P7V_SENSE_LAT                LATBbits.LATB2
#define P7V_SENSE_PORT               PORTBbits.RB2
#define P7V_SENSE_WPU                WPUBbits.WPUB2
#define P7V_SENSE_ANS                ANSELBbits.ANSB2
#define P7V_SENSE_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define P7V_SENSE_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define P7V_SENSE_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define P7V_SENSE_GetValue()           PORTBbits.RB2
#define P7V_SENSE_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define P7V_SENSE_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define P7V_SENSE_SetPullup()      do { WPUBbits.WPUB2 = 1; } while(0)
#define P7V_SENSE_ResetPullup()    do { WPUBbits.WPUB2 = 0; } while(0)
#define P7V_SENSE_SetAnalogMode()  do { ANSELBbits.ANSB2 = 1; } while(0)
#define P7V_SENSE_SetDigitalMode() do { ANSELBbits.ANSB2 = 0; } while(0)

// get/set V28_SNS aliases
#define V28_SNS_TRIS               TRISBbits.TRISB3
#define V28_SNS_LAT                LATBbits.LATB3
#define V28_SNS_PORT               PORTBbits.RB3
#define V28_SNS_WPU                WPUBbits.WPUB3
#define V28_SNS_ANS                ANSELBbits.ANSB3
#define V28_SNS_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define V28_SNS_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define V28_SNS_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define V28_SNS_GetValue()           PORTBbits.RB3
#define V28_SNS_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define V28_SNS_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define V28_SNS_SetPullup()      do { WPUBbits.WPUB3 = 1; } while(0)
#define V28_SNS_ResetPullup()    do { WPUBbits.WPUB3 = 0; } while(0)
#define V28_SNS_SetAnalogMode()  do { ANSELBbits.ANSB3 = 1; } while(0)
#define V28_SNS_SetDigitalMode() do { ANSELBbits.ANSB3 = 0; } while(0)

// get/set LED_S2 aliases
#define LED_S2_TRIS               TRISBbits.TRISB4
#define LED_S2_LAT                LATBbits.LATB4
#define LED_S2_PORT               PORTBbits.RB4
#define LED_S2_WPU                WPUBbits.WPUB4
#define LED_S2_ANS                ANSELBbits.ANSB4
#define LED_S2_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define LED_S2_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define LED_S2_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define LED_S2_GetValue()           PORTBbits.RB4
#define LED_S2_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define LED_S2_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define LED_S2_SetPullup()      do { WPUBbits.WPUB4 = 1; } while(0)
#define LED_S2_ResetPullup()    do { WPUBbits.WPUB4 = 0; } while(0)
#define LED_S2_SetAnalogMode()  do { ANSELBbits.ANSB4 = 1; } while(0)
#define LED_S2_SetDigitalMode() do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set ADC_RB5 aliases
#define ADC_RB5_TRIS               TRISBbits.TRISB5
#define ADC_RB5_LAT                LATBbits.LATB5
#define ADC_RB5_PORT               PORTBbits.RB5
#define ADC_RB5_WPU                WPUBbits.WPUB5
#define ADC_RB5_ANS                ANSELBbits.ANSB5
#define ADC_RB5_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define ADC_RB5_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define ADC_RB5_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define ADC_RB5_GetValue()           PORTBbits.RB5
#define ADC_RB5_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define ADC_RB5_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define ADC_RB5_SetPullup()      do { WPUBbits.WPUB5 = 1; } while(0)
#define ADC_RB5_ResetPullup()    do { WPUBbits.WPUB5 = 0; } while(0)
#define ADC_RB5_SetAnalogMode()  do { ANSELBbits.ANSB5 = 1; } while(0)
#define ADC_RB5_SetDigitalMode() do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set LED_S1 aliases
#define LED_S1_TRIS               TRISCbits.TRISC0
#define LED_S1_LAT                LATCbits.LATC0
#define LED_S1_PORT               PORTCbits.RC0
#define LED_S1_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define LED_S1_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define LED_S1_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define LED_S1_GetValue()           PORTCbits.RC0
#define LED_S1_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define LED_S1_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)

// get/set TX_SYNT_CE aliases
#define TX_SYNT_CE_TRIS               TRISCbits.TRISC1
#define TX_SYNT_CE_LAT                LATCbits.LATC1
#define TX_SYNT_CE_PORT               PORTCbits.RC1
#define TX_SYNT_CE_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define TX_SYNT_CE_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define TX_SYNT_CE_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define TX_SYNT_CE_GetValue()           PORTCbits.RC1
#define TX_SYNT_CE_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define TX_SYNT_CE_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)

// get/set TX_SYNT_LE aliases
#define TX_SYNT_LE_TRIS               TRISCbits.TRISC2
#define TX_SYNT_LE_LAT                LATCbits.LATC2
#define TX_SYNT_LE_PORT               PORTCbits.RC2
#define TX_SYNT_LE_ANS                ANSELCbits.ANSC2
#define TX_SYNT_LE_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define TX_SYNT_LE_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define TX_SYNT_LE_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define TX_SYNT_LE_GetValue()           PORTCbits.RC2
#define TX_SYNT_LE_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define TX_SYNT_LE_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define TX_SYNT_LE_SetAnalogMode()  do { ANSELCbits.ANSC2 = 1; } while(0)
#define TX_SYNT_LE_SetDigitalMode() do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set TX_SYNT_CLK aliases
#define TX_SYNT_CLK_TRIS               TRISCbits.TRISC3
#define TX_SYNT_CLK_LAT                LATCbits.LATC3
#define TX_SYNT_CLK_PORT               PORTCbits.RC3
#define TX_SYNT_CLK_ANS                ANSELCbits.ANSC3
#define TX_SYNT_CLK_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define TX_SYNT_CLK_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define TX_SYNT_CLK_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define TX_SYNT_CLK_GetValue()           PORTCbits.RC3
#define TX_SYNT_CLK_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define TX_SYNT_CLK_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define TX_SYNT_CLK_SetAnalogMode()  do { ANSELCbits.ANSC3 = 1; } while(0)
#define TX_SYNT_CLK_SetDigitalMode() do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set RX_SYNT_CLK aliases
#define RX_SYNT_CLK_TRIS               TRISCbits.TRISC4
#define RX_SYNT_CLK_LAT                LATCbits.LATC4
#define RX_SYNT_CLK_PORT               PORTCbits.RC4
#define RX_SYNT_CLK_ANS                ANSELCbits.ANSC4
#define RX_SYNT_CLK_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define RX_SYNT_CLK_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define RX_SYNT_CLK_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RX_SYNT_CLK_GetValue()           PORTCbits.RC4
#define RX_SYNT_CLK_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define RX_SYNT_CLK_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define RX_SYNT_CLK_SetAnalogMode()  do { ANSELCbits.ANSC4 = 1; } while(0)
#define RX_SYNT_CLK_SetDigitalMode() do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set RX_SYNT_DATA aliases
#define RX_SYNT_DATA_TRIS               TRISCbits.TRISC5
#define RX_SYNT_DATA_LAT                LATCbits.LATC5
#define RX_SYNT_DATA_PORT               PORTCbits.RC5
#define RX_SYNT_DATA_ANS                ANSELCbits.ANSC5
#define RX_SYNT_DATA_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define RX_SYNT_DATA_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define RX_SYNT_DATA_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define RX_SYNT_DATA_GetValue()           PORTCbits.RC5
#define RX_SYNT_DATA_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define RX_SYNT_DATA_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define RX_SYNT_DATA_SetAnalogMode()  do { ANSELCbits.ANSC5 = 1; } while(0)
#define RX_SYNT_DATA_SetDigitalMode() do { ANSELCbits.ANSC5 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()    do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()   do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()   do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()         PORTCbits.RC6
#define RC6_SetDigitalInput()   do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()  do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetAnalogMode() do { ANSELCbits.ANSC6 = 1; } while(0)
#define RC6_SetDigitalMode()do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()    do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()   do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()   do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()         PORTCbits.RC7
#define RC7_SetDigitalInput()   do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()  do { TRISCbits.TRISC7 = 0; } while(0)
#define RC7_SetAnalogMode() do { ANSELCbits.ANSC7 = 1; } while(0)
#define RC7_SetDigitalMode()do { ANSELCbits.ANSC7 = 0; } while(0)

// get/set TX_SYNT_DATA aliases
#define TX_SYNT_DATA_TRIS               TRISDbits.TRISD0
#define TX_SYNT_DATA_LAT                LATDbits.LATD0
#define TX_SYNT_DATA_PORT               PORTDbits.RD0
#define TX_SYNT_DATA_ANS                ANSELDbits.ANSD0
#define TX_SYNT_DATA_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define TX_SYNT_DATA_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define TX_SYNT_DATA_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define TX_SYNT_DATA_GetValue()           PORTDbits.RD0
#define TX_SYNT_DATA_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define TX_SYNT_DATA_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)
#define TX_SYNT_DATA_SetAnalogMode()  do { ANSELDbits.ANSD0 = 1; } while(0)
#define TX_SYNT_DATA_SetDigitalMode() do { ANSELDbits.ANSD0 = 0; } while(0)

// get/set TX_SYNT_LD aliases
#define TX_SYNT_LD_TRIS               TRISDbits.TRISD1
#define TX_SYNT_LD_LAT                LATDbits.LATD1
#define TX_SYNT_LD_PORT               PORTDbits.RD1
#define TX_SYNT_LD_ANS                ANSELDbits.ANSD1
#define TX_SYNT_LD_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define TX_SYNT_LD_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define TX_SYNT_LD_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define TX_SYNT_LD_GetValue()           PORTDbits.RD1
#define TX_SYNT_LD_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define TX_SYNT_LD_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)
#define TX_SYNT_LD_SetAnalogMode()  do { ANSELDbits.ANSD1 = 1; } while(0)
#define TX_SYNT_LD_SetDigitalMode() do { ANSELDbits.ANSD1 = 0; } while(0)

// get/set RX_SYNT_CE aliases
#define RX_SYNT_CE_TRIS               TRISDbits.TRISD2
#define RX_SYNT_CE_LAT                LATDbits.LATD2
#define RX_SYNT_CE_PORT               PORTDbits.RD2
#define RX_SYNT_CE_ANS                ANSELDbits.ANSD2
#define RX_SYNT_CE_SetHigh()            do { LATDbits.LATD2 = 1; } while(0)
#define RX_SYNT_CE_SetLow()             do { LATDbits.LATD2 = 0; } while(0)
#define RX_SYNT_CE_Toggle()             do { LATDbits.LATD2 = ~LATDbits.LATD2; } while(0)
#define RX_SYNT_CE_GetValue()           PORTDbits.RD2
#define RX_SYNT_CE_SetDigitalInput()    do { TRISDbits.TRISD2 = 1; } while(0)
#define RX_SYNT_CE_SetDigitalOutput()   do { TRISDbits.TRISD2 = 0; } while(0)
#define RX_SYNT_CE_SetAnalogMode()  do { ANSELDbits.ANSD2 = 1; } while(0)
#define RX_SYNT_CE_SetDigitalMode() do { ANSELDbits.ANSD2 = 0; } while(0)

// get/set RX_SYNT_LE aliases
#define RX_SYNT_LE_TRIS               TRISDbits.TRISD3
#define RX_SYNT_LE_LAT                LATDbits.LATD3
#define RX_SYNT_LE_PORT               PORTDbits.RD3
#define RX_SYNT_LE_ANS                ANSELDbits.ANSD3
#define RX_SYNT_LE_SetHigh()            do { LATDbits.LATD3 = 1; } while(0)
#define RX_SYNT_LE_SetLow()             do { LATDbits.LATD3 = 0; } while(0)
#define RX_SYNT_LE_Toggle()             do { LATDbits.LATD3 = ~LATDbits.LATD3; } while(0)
#define RX_SYNT_LE_GetValue()           PORTDbits.RD3
#define RX_SYNT_LE_SetDigitalInput()    do { TRISDbits.TRISD3 = 1; } while(0)
#define RX_SYNT_LE_SetDigitalOutput()   do { TRISDbits.TRISD3 = 0; } while(0)
#define RX_SYNT_LE_SetAnalogMode()  do { ANSELDbits.ANSD3 = 1; } while(0)
#define RX_SYNT_LE_SetDigitalMode() do { ANSELDbits.ANSD3 = 0; } while(0)

// get/set RX_SYNT_LD aliases
#define RX_SYNT_LD_TRIS               TRISDbits.TRISD4
#define RX_SYNT_LD_LAT                LATDbits.LATD4
#define RX_SYNT_LD_PORT               PORTDbits.RD4
#define RX_SYNT_LD_ANS                ANSELDbits.ANSD4
#define RX_SYNT_LD_SetHigh()            do { LATDbits.LATD4 = 1; } while(0)
#define RX_SYNT_LD_SetLow()             do { LATDbits.LATD4 = 0; } while(0)
#define RX_SYNT_LD_Toggle()             do { LATDbits.LATD4 = ~LATDbits.LATD4; } while(0)
#define RX_SYNT_LD_GetValue()           PORTDbits.RD4
#define RX_SYNT_LD_SetDigitalInput()    do { TRISDbits.TRISD4 = 1; } while(0)
#define RX_SYNT_LD_SetDigitalOutput()   do { TRISDbits.TRISD4 = 0; } while(0)
#define RX_SYNT_LD_SetAnalogMode()  do { ANSELDbits.ANSD4 = 1; } while(0)
#define RX_SYNT_LD_SetDigitalMode() do { ANSELDbits.ANSD4 = 0; } while(0)

// get/set ADC_RD5 aliases
#define ADC_RD5_TRIS               TRISDbits.TRISD5
#define ADC_RD5_LAT                LATDbits.LATD5
#define ADC_RD5_PORT               PORTDbits.RD5
#define ADC_RD5_ANS                ANSELDbits.ANSD5
#define ADC_RD5_SetHigh()            do { LATDbits.LATD5 = 1; } while(0)
#define ADC_RD5_SetLow()             do { LATDbits.LATD5 = 0; } while(0)
#define ADC_RD5_Toggle()             do { LATDbits.LATD5 = ~LATDbits.LATD5; } while(0)
#define ADC_RD5_GetValue()           PORTDbits.RD5
#define ADC_RD5_SetDigitalInput()    do { TRISDbits.TRISD5 = 1; } while(0)
#define ADC_RD5_SetDigitalOutput()   do { TRISDbits.TRISD5 = 0; } while(0)
#define ADC_RD5_SetAnalogMode()  do { ANSELDbits.ANSD5 = 1; } while(0)
#define ADC_RD5_SetDigitalMode() do { ANSELDbits.ANSD5 = 0; } while(0)

// get/set ADC_RE0 aliases
#define ADC_RE0_TRIS               TRISEbits.TRISE0
#define ADC_RE0_LAT                LATEbits.LATE0
#define ADC_RE0_PORT               PORTEbits.RE0
#define ADC_RE0_ANS                ANSELEbits.ANSE0
#define ADC_RE0_SetHigh()            do { LATEbits.LATE0 = 1; } while(0)
#define ADC_RE0_SetLow()             do { LATEbits.LATE0 = 0; } while(0)
#define ADC_RE0_Toggle()             do { LATEbits.LATE0 = ~LATEbits.LATE0; } while(0)
#define ADC_RE0_GetValue()           PORTEbits.RE0
#define ADC_RE0_SetDigitalInput()    do { TRISEbits.TRISE0 = 1; } while(0)
#define ADC_RE0_SetDigitalOutput()   do { TRISEbits.TRISE0 = 0; } while(0)
#define ADC_RE0_SetAnalogMode()  do { ANSELEbits.ANSE0 = 1; } while(0)
#define ADC_RE0_SetDigitalMode() do { ANSELEbits.ANSE0 = 0; } while(0)

// get/set ADC_RE1 aliases
#define ADC_RE1_TRIS               TRISEbits.TRISE1
#define ADC_RE1_LAT                LATEbits.LATE1
#define ADC_RE1_PORT               PORTEbits.RE1
#define ADC_RE1_ANS                ANSELEbits.ANSE1
#define ADC_RE1_SetHigh()            do { LATEbits.LATE1 = 1; } while(0)
#define ADC_RE1_SetLow()             do { LATEbits.LATE1 = 0; } while(0)
#define ADC_RE1_Toggle()             do { LATEbits.LATE1 = ~LATEbits.LATE1; } while(0)
#define ADC_RE1_GetValue()           PORTEbits.RE1
#define ADC_RE1_SetDigitalInput()    do { TRISEbits.TRISE1 = 1; } while(0)
#define ADC_RE1_SetDigitalOutput()   do { TRISEbits.TRISE1 = 0; } while(0)
#define ADC_RE1_SetAnalogMode()  do { ANSELEbits.ANSE1 = 1; } while(0)
#define ADC_RE1_SetDigitalMode() do { ANSELEbits.ANSE1 = 0; } while(0)

// get/set ADC_RE2 aliases
#define ADC_RE2_TRIS               TRISEbits.TRISE2
#define ADC_RE2_LAT                LATEbits.LATE2
#define ADC_RE2_PORT               PORTEbits.RE2
#define ADC_RE2_ANS                ANSELEbits.ANSE2
#define ADC_RE2_SetHigh()            do { LATEbits.LATE2 = 1; } while(0)
#define ADC_RE2_SetLow()             do { LATEbits.LATE2 = 0; } while(0)
#define ADC_RE2_Toggle()             do { LATEbits.LATE2 = ~LATEbits.LATE2; } while(0)
#define ADC_RE2_GetValue()           PORTEbits.RE2
#define ADC_RE2_SetDigitalInput()    do { TRISEbits.TRISE2 = 1; } while(0)
#define ADC_RE2_SetDigitalOutput()   do { TRISEbits.TRISE2 = 0; } while(0)
#define ADC_RE2_SetAnalogMode()  do { ANSELEbits.ANSE2 = 1; } while(0)
#define ADC_RE2_SetDigitalMode() do { ANSELEbits.ANSE2 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/