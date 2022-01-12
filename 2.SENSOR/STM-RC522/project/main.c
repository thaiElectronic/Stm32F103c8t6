#include "stm32f10x.h"
#include "mcu-delay.h"
#include "mcu-usart.h"
#include "mcu-mfrc522.h"
#include "mcu-gpio.h"
#include "mcu-tim.h"
#include "mcu-adc.h"
#include "mcu-dht11.h"
#include "stdio.h"
#include "string.h"


unsigned int vrui_CountDelay = 0, vruc_SttCountDelay = 0;
uint8_t CardID[5];
char szBuff[100];
char CardID1[]="0x4487d94a50";

void OpenTheDoor(){
if(MFRC522_Check(CardID) == MI_OK){
		sprintf(szBuff, "0x%x%x%x%x%x", CardID[0], CardID[1], CardID[2], CardID[3], CardID[4]);
		printf("ID: %s\n",szBuff);
		if(strcmp(szBuff,CardID1)==0){
			TIM2->CCR4 = 950;// cua trai
			TIM3->CCR1 = 2300;// cua phai
			Delay_ms(10);
			TIM2->CCR4 = 2300;
			TIM3->CCR1 = 950;
			Delay_ms(3000);
			TIM2->CCR4 = 950;
			TIM3->CCR1 = 2300;
			//delay(500);			
		}
	}
}
void blink(){
	digitalWrite(PC13,LOW);
		while(vrui_CountDelay<200){
				Delay_1ms();
				vrui_CountDelay++;
				if(vrui_CountDelay >= 200){
					vrui_CountDelay = 0;
					break;
				}
			}	
		digitalWrite(PC13,HIGH);
		while(vrui_CountDelay<200){
				Delay_1ms();
				vrui_CountDelay++;
				if(vrui_CountDelay >= 200){
					vrui_CountDelay = 0;
					break;
				}
			}	
}


int main() {
	USARTx_Init(USART1,9600);
	MFRC522_Init();
	PWM_Init(TIM2, Channel_4, 20000,72);//A3 - canh trai
	PWM_Init(TIM3, Channel_1, 20000,72);//A6 - canh phai
	pinMode(PC13,OUTPUT);
	while(1){	
		
		OpenTheDoor();
	}
}
