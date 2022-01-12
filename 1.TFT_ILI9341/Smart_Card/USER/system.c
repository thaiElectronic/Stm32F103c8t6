#include "system.h"

int Count=0,k;
int Status_display = 0;

void System_Init(void){
	
	SystemInit();
	delay_init(72);	 
	LCD_Init();	
	RFID_Init();	
	GPIO_Config();
	Timer2_StandardLibrary();
	NVIC_Config();
	UART_Config(USART1,9600);
	UART_Config(USART3,9600);
	UART_Interrupt(USART3);
	UART_Receive_DMA(USART3,Str_Interrupt,500);
	LCD_Interface_Waiting();
//	Read_Images_SD_Card();
}

void Systen_Run(void){
	
	if(Flag_RFID_To_Json == 1){
		
		json_packing(szBuff);
		
	}
	
	if(strstr(Str_Interrupt,"}") != 0){

		Get_Info_Json(Str_Interrupt);
		
	}
	
	if(Flag_Json_To_TFT == 1){
		if(Status_display == 0){
			interface();
			
			LCD_Display_Information();
			Read_Images_SD_Card();
			Status_display = 1;
		}
		else{
			LCD_Delete_Information(); 			
			LCD_Display_Information();
			Read_Images_SD_Card();
			Json_Copy_Info(name);		
		}
		for(k=0;k<sizeof(Str_Interrupt);k++)Str_Interrupt[k]=0;
		UART_Receive_DMA(USART3,Str_Interrupt,500);
		Count=0;
	}
	
	if(Count == 5000){
		if(Status_display == 0) Count=0;
		
		else{
			LCD_Interface_Waiting();
			Status_display = 0;
			Count = 0;
		}
	}
	
	Count++;
	delay_ms(1);
	
}
