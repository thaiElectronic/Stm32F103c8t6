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
// mang chua ma cua ki hieu nhiet do
unsigned char Character1[8]={0x07, 0x05, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00};
// mang chua ma %
unsigned char Character2[8]={0x00,0x00,0x19,0x1a,0x04,0x0b,0x13,0x00};
uint8_t u8Buff[4];
unsigned char temp[20];
unsigned char humi[20];

void Disp_LCD(void);
void Disp_Terminal(void);

int main(){
//	LCD_Init();
	DHT11_Init();
	USARTx_Init(USART1,9600);
	while(1){	
		Disp_Terminal();
	}
}

void Disp_LCD(void){
	if(DHT11_Read(u8Buff)){
	/*hien thi gia tri do am*/
		LCD_Gotoxy(0,0);
		sprintf(humi,"%d",u8Buff[0]);
		LCD_Puts("Do Am: ");
		LCD_Gotoxy(10,0);
		LCD_Puts(humi);
		LCD_Custom(1, Character2);
		LCD_Gotoxy(12,0);
		LCD_PutChar(1);
		
		/*hien thi gia tri nhiet do*/
		sprintf(temp,"%d",u8Buff[2]);
		LCD_Gotoxy(0,1);
		LCD_Puts("Nhiet Do: ");
		LCD_Gotoxy(10,1);
		LCD_Puts(temp);
		LCD_Custom(0, Character1);
		LCD_Gotoxy(12,1);		
		LCD_PutChar(0);
		LCD_PutChar('C');
		Delay_ms(1000);
	}	
}


void Disp_Terminal(void){
	if(DHT11_Read(u8Buff)){
	/*hien thi gia tri do am*/
		printf("Humi: %d\n",u8Buff[0]);
		printf("Temp: %d\n------------------\n",u8Buff[2]);
		Delay_ms(500);
	}	
}