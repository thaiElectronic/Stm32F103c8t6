#include "stm32f10x.h"
#include "mcu-delay.h"
#include "mcu-lcd.h"
#include "mcu-usart.h"
#include "mcu-mfrc522.h"
#include "mcu-gpio.h"
#include "mcu-tim.h"
#include "mcu-adc.h"
#include "mcu-dht11.h"
#include "stdio.h"
#include "string.h"


void delay(unsigned int time){
	int i,j;
	for(i = 0; i< time; i++){
		for(j = 0; j<0x2aff; j++){};
	}
}

////////////////////////////////////////////////////////////////////
// mang chua ma cua ki hieu nhiet do
//unsigned char Character1[8]={0x07, 0x05, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00};
//// mang chua ma %
//unsigned char Character2[8]={0x00, 0x00, 0x19, 0x1a, 0x04, 0x0b, 0x13, 0x00};
//void DHT11(void){
//	uint8_t u8Buff[4];
//	unsigned char temp[25];
//	unsigned char humi[25];
//	if(DHT11_Read(u8Buff)){
//		/*hien thi gia tri do am*/
//		LCD_Gotoxy(0,0);
//		sprintf(humi,"%d",u8Buff[0]);
//		LCD_Puts("Do Am: ");
//		LCD_Gotoxy(10,0);
//		LCD_Puts(humi);
//		LCD_Custom(1, Character2);
//		LCD_Gotoxy(12,0);
//		LCD_PutChar(1);
//		
//		/*hien thi gia tri nhiet do*/
//		sprintf(temp,"%d",u8Buff[2]);
//		LCD_Gotoxy(0,1);
//		LCD_Puts("Nhiet Do: ");
//		LCD_Gotoxy(10,1);
//		LCD_Puts(temp);
//		LCD_Custom(0, Character1);
//		LCD_Gotoxy(12,1);		
//		LCD_PutChar(0);
//		LCD_PutChar('C');
//		Delay_ms(1000);
//	}
//}

////////////////////////////////////////////////////////////////////////////////
uint8_t CardID[5];
char szBuff[100];
char CardID1[]="0x4487d94a50";

void OpenTHeDoor(void){
	if(MFRC522_Check(CardID) == MI_OK){
		sprintf(szBuff, "0x%x%x%x%x%x", CardID[0], CardID[1], CardID[2], CardID[3], CardID[4]);
		printf("ID: %s\n",szBuff);
//		if(strcmp(szBuff,CardID1)==0){
//			TIM2->CCR4 = (float)7.5;
//			delay(1000);
//			TIM2->CCR4 = (float)2.5;
//			delay(1000);
//		}
	}
}

int main(){
	
//	USARTx_Init(USART1,9600);
//	MFRC522_Init();
//	pinMode(PC13,OUTPUT);
//	LCD_Init();
//	DHT11_Init();
//	DHT11();
//	printf("welcome to smart home!");
	PWM_Init(TIM2, Channel_4, 20000,72);
	
	while(1){
//		printf("welcome to smart home!\n");
//		if(MFRC522_Check(CardID) == MI_OK){
//			sprintf(szBuff, "0x%x%x%x%x%x", CardID[0], CardID[1], CardID[2], CardID[3], CardID[4]);
//			printf("ID: %s\n",szBuff);
//			Delay_ms(200);
//		}
//		Delay_ms(200);
		
		TIM2->CCR4 = (float)7.5;
		Delay_ms(1000);
		TIM2->CCR4 = (float)2.5;
		Delay_ms(1000);
	}
}


