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
	char Tx_Buffer[100] = "Hello via USART with TX DMA\n";
	 
	char Rx_Buffer[300];
	
	int i;
	USARTx_Init(USART1,9600);
	USARTx_Init_DMA(USART1);// ok
	USARTx_Receive_DMA(USART1,Rx_Buffer,sizeof(Rx_Buffer)); // cho phep nhan du lieu, luu vao mang Rx_Buffer
	while(1){
		
		if(strstr((char*)Rx_Buffer, "\n") != NULL){ // kiem tra chuoi nhan ve, neu co ki tu '\n' ...
				
				//USARTx_DMA_Send(USART1,Rx_Buffer,sizeof(Rx_Buffer));	
			printf("%s\n",Rx_Buffer);
				for(i=0;i<sizeof(Rx_Buffer);i++){// reset cac mang Rx_Bufer 
					Rx_Buffer[i]=0;
				}
				// cho phep tiep tuc nhan data;
				USARTx_Receive_DMA(USART1,Rx_Buffer,sizeof(Rx_Buffer)); // do khi truyen hoan tat data thi no se yeu cau ngat va bat co ngat, no se reset qua trinh nhan
		}
			Delay_ms(2000);
	}
}
