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

#define FW_VERSION_MAX_SIZE_BYTE    (0x4)
#define CPLD_FW_ADDR_OFFSET         (0x4)

#define RUN_TIME_MAX_SIZE_BYTE      (0x4)

#define NUM_5SEC_TICS_24_HOURS      (17280)
#define EEPROM_MCU_FW_ADDRESS       (0)

// EUSART TX packets size
#define STATUS_FW_PACKET_SIZE FW_VERSION_MAX_SIZE_BYTE + MSG_DATA_LOCATION
#define STATUS_RUN_TIME_PACKET_SIZE RUN_TIME_MAX_SIZE_BYTE + MSG_DATA_LOCATION

void SetMcuFwVersion(char* data);
void SetCpldFwVersion(char* data);

void GetMcuFwVersion();
void GetCpldFwVersion();

void SetMcuRunTime();
void GetMcuRunTime();
void ClearMcuRunTime();
void keepAliveSignalUart(void);

#endif	/* SYSTEMSTATUS_H */

