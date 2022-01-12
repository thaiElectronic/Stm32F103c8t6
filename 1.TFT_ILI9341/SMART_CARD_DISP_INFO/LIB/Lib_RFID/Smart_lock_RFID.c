#include "Smart_lock_RFID.h"


// Cac biên su dung cho RFID
//uint8_t CardID[MAX_LENGTH];
//char szBuff[MAX_LENGTH];



void RFID_Init(void){
	MFRC522_Init();
}

//void RFID_Check_Card(void){

//	if(MFRC522_Check(CardID) == MI_OK){ 
//		sprintf(szBuff, "%x%x%x%x%x", CardID[0], CardID[1], CardID[2], CardID[3], CardID[4]);	
//		
//	}
//				
//}
