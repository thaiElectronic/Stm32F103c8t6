#ifndef __SMART_LOCK_RFID_H
#define __SMART_LOCK_RFID_H

#include "RFID.h"
#include "spi.h"
#include "Smart_lock_TFT.h"
#include "stdio.h"

#define MAX_LENGTH  100 

extern int Flag_RFID_To_Json;
extern char szBuff[MAX_LENGTH];

void RFID_Init(void);
void RFID_Check_Card(void);

#endif 
