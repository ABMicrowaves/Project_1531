/*******************************************************************************
File name: MessageFunctions.h                                               ****
File description:   Include EUSART P2P groups functions definitions.        ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
****************************************************************************** */

#ifndef MESSAGEFUNCTIONS_H
#define	MESSAGEFUNCTIONS_H

#include "GroupsCommon.h"
#include "SystemStatus.h"
#include "LedsApp.h"
#include "AdcApp.h"
#include "FlashApp.h"

void GroupControlMcu(MSG_REQUEST request, char* data);
void GroupStatusAndVersion(MSG_REQUEST request, char* data);
void GroupAdc(MSG_REQUEST request, char* data);
void GroupSynthesizers(MSG_REQUEST request, char* data);
void GroupFlashMemory(MSG_REQUEST request, char* data);
void GroupDAC(MSG_REQUEST request, char* data);

// Message groups array;
void (*groupsArray[NUMBER_OF_MESSAGE_GROUPS])() = 
{
    GroupControlMcu,
    GroupStatusAndVersion,
    GroupAdc,
    GroupSynthesizers,
    GroupFlashMemory,
    GroupDAC,
};

#endif	/* MESSAGEFUNCTIONS_H */

