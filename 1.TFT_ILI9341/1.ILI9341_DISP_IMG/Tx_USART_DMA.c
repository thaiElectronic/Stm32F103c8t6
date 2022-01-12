#include "stm32f10x.h"
#include "mcu-swi2c.h"
#include "mcu-delay.h"
#include "mcu-gpio.h"
#include "mcu-usart.h"
#include "mcu-tim.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_exti.h"
#include "stdio.h"
#include "string.h"

int main(){	
	char Tx_Buffer[100] = "Hello via USART with TX DMA"; // mang can truyen du lieu
	 
	char Rx_Buffer[300]; // mang de luu du lieu nhan ve
	
	USARTx_Init(USART1,9600);
	USARTx_Init_DMA(USART1); // cho phep ngat DMA truyen nhan du lieu
	while(1){
			USARTx_DMA_Send(USART1, Tx_Buffer, strlen(Tx_Buffer));
			Delay_ms(1000);
	}
}