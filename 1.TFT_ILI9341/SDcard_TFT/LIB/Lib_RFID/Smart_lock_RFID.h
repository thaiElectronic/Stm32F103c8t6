#ifndef __SMART_LOCK_RFID_H
#define __SMART_LOCK_RFID_H

#include "mcu-mfrc522.h"
#include "spi.h"
#include "Smart_lock_TFT.h"
#include "stdio.h"

#define MAX_LENGTH  100 

extern int Flag_RFID_To_Json;
extern char szBuff[MAX_LENGTH];

void RFID_Init(void);
void RFID_Check_Card(void);

#endif 
