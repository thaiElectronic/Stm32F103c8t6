#include "Smart_lock_RFID.h"


// Cac biên su dung cho RFID
uint8_t CardID[MAX_LENGTH];
char szBuff[MAX_LENGTH];
int Flag_RFID_To_Json = 0;
char str_check[100];


void RFID_Init(void){
	MFRC522_Init();
}

void RFID_Check_Card(void){

	if(MFRC522_Check(CardID) == MI_OK){ 
		sprintf(szBuff, "%x%x%x%x%x", CardID[0], CardID[1], CardID[2], CardID[3], CardID[4]);	


		if(strcmp(szBuff, str_check)){
					
			
			memset(str_check, '\0', sizeof(str_check));
			strcpy(str_check, szBuff);
			Flag_RFID_To_Json = 1;
		}
		else{	
			Flag_RFID_To_Json = 0 ; 
		}	
	} 
	else if(MFRC522_Check(CardID) != MI_OK){
		memset(str_check, '\0', sizeof(str_check));
	}
}
