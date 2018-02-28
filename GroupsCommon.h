/*******************************************************************************
File name: GroupsCommon.h                                                   ****
File description:   Include EUSART P2P definition and parameters.           ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
****************************************************************************** */

#ifndef GROUPSCOMMON_H
#define	GROUPSCOMMON_H

#define MSG_MAGIC_A                 (0x24)    // 0x24 == '$'
#define DELAY_BETWEEN_MESSAGE_READ  (500)
#define MIN_RX_MSG_SIZE             (4)
#define MSG_RX_MAX_DATA_SIZE        (0x14)

// Locations
#define MSG_MAGIC_LOCATION          (0)
#define MSG_GROUP_LOCATION          (1)
#define MSG_REQUEST_LOCATION        (2)
#define MSG_DATA_SIZE_LOCATION      (3)
#define MSG_DATA_LOCATION           (0x4)
#define NUMBER_OF_MESSAGE_GROUPS    (6)

// Ack message
#define ACK_MESSAGE_PACKET_SIZE     (0x5)

typedef enum
{
    FLASH_RAW_DATA = 64,
}TX_MESSAGE_TYPE;

typedef enum
{
    CONTROL_MSG                 = 0x01,
    MCU_STATUS_VERSION_MSG      = 0x02,
    ADC_MSG                     = 0x03,
    SYNTH_MSG                   = 0x04,
    FLASH_MSG                   = 0x05,
    DAC_MSG                     = 0x06,
}MSG_GROUPS;

typedef enum
{
    // Control MCU:
    CONTROL_SYSTEM_START        = 0x10,
    CONTROL_RESET_MCU           = 0x11,
    CONTROL_RESET_CPLD          = 0x12,
    CONTROL_PA1_SET             = 0x13,
    CONTROL_PA2_SET             = 0x14,
    CONTROL_TEST_LEDS           = 0x15,
    CONTROL_KEEP_ALIVE          = 0x16,

    // MCU status and version:
    STATUS_MCU_RUN_TIME         = 0x21,
    STATUS_GET_MCU_FW_VERSION   = 0x22,
    STATUS_GET_CPLD_FW_VERSION  = 0x23,
    STATUS_SET_MCU_FW_VERSION   = 0x24,
    STATUS_SET_CPLD_FW_VERSION  = 0x25,

    // ADC
    ADC_OPERATION               = 0x31,
    ADC_CHANNEL_MODE            = 0x32,
    ADC_CONVERSION_MODE         = 0x33,
    
    // Synthesizer (Up / Down):
    SYNTH_TX_INIT_SET           = 0x40,
    SYNTH_RX_INIT_SET           = 0x41,
    SYNTH_DOWN_SET              = 0x42,
    SYNTH_UP_SET                = 0x43,

    // Flash memory
    FLASH_EREASE_MEMORY         = 0x51,
    FLASH_READ_CONDITION        = 0x52,
    FLASH_REQUEST_RAW_DATA      = 0x53,
    FLASH_SEND_RAW_DATA         = 0x54,
    FLASH_NO_SAMPLE_YET         = 0x55,

    //DAC
    DAC_SET_VALUE               = 0x61,
}MSG_REQUEST;

#endif	/* GROUPSCOMMON_H */

