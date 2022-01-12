#include "mcu-usart.h"
#include "mcu-gpio.h"
#include "mcu-delay.h"

int i;
int		Flag_rx; 			// bien danh dau trang thai. 

unsigned char	vrc_Res[4000]; 		//Mang kieu char vrc_Res[MAX]: mang luu tru tam thoi;

int main(){
	USARTx_Init(USART3, 9600);
	USARTx_Init(USART1, 9600);
	//printf("Thai MCU\n");
	while(1){	
		if(Flag_rx){
				Flag_rx = 0;	
				printf("%s",vrc_Res);
				//memcpy(vrc_Res,'\0',20);
				Delay_ms(1);
		}
	}
}

