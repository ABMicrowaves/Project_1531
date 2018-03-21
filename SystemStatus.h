/*******************************************************************************
File name: SystemStatus.h                                                   ****
File description:   Include MCU run-time and status parameters              ****
                    and functions.                                          ****
MCU:                PIC18F45k22                                             ****
Date modified: 05/02/2018 16:34.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
****************************************************************************** */

#ifndef SYSTEMSTATUS_H
#define	SYSTEMSTATUS_H

#include "SystemCommon.h"

#define FW_VERSION_MAX_SIZE_BYTE    (13)
#define CPLD_FW_ADDR_OFFSET         (0x4)

#define RUN_TIME_MAX_SIZE_BYTE      (0x4)

#define NUM_5SEC_TICS_24_HOURS      (17280)
#define EEPROM_MCU_FW_ADDRESS       (0)

// EUSART TX packets size
#define STATUS_FW_PACKET_SIZE FW_VERSION_MAX_SIZE_BYTE + MSG_DATA_LOCATION
#define STATUS_RUN_TIME_PACKET_SIZE RUN_TIME_MAX_SIZE_BYTE + MSG_DATA_LOCATION

#define COMPUTE_BUILD_YEAR \
    ( \
        (__DATE__[ 7] - '0') * 1000 + \
        (__DATE__[ 8] - '0') *  100 + \
        (__DATE__[ 9] - '0') *   10 + \
        (__DATE__[10] - '0') \
    )

#define COMPUTE_BUILD_DAY \
    ( \
        ((__DATE__[4] >= '0') ? (__DATE__[4] - '0') * 10 : 0) + \
        (__DATE__[5] - '0') \
    )

#define COMPUTE_BUILD_HOUR ((__TIME__[0] - '0') * 10 + __TIME__[1] - '0')
#define COMPUTE_BUILD_MIN  ((__TIME__[3] - '0') * 10 + __TIME__[4] - '0')
#define COMPUTE_BUILD_SEC  ((__TIME__[6] - '0') * 10 + __TIME__[7] - '0')

void GetMcuFwVersion();;

void SetMcuRunTime();
void GetMcuRunTime();
void ClearMcuRunTime();
void keepAliveSignalUart(void);

#endif	/* SYSTEMSTATUS_H */

