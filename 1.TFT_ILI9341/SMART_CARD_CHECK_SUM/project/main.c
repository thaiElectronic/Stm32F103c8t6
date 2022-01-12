#include "mcu-usart.h"
#include "mcu-gpio.h"
#include "mcu-delay.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int i;
int	Flag_rx; 			// bien danh dau trang thai. 

unsigned char	vrc_Res[4000]; 		//Mang kieu char vrc_Res[MAX]: mang luu tru tam thoi;

struct frame{
	unsigned char StudentCode[16];
	unsigned char SizeX;
	unsigned char SizeY;
	unsigned char Couter;
	unsigned char Data[16];
	unsigned char Stop;
};
struct frame fr;

unsigned int farme_std, farme_x, farme_y, farme_cnt, farme_data, farme_sp;

void strTObyte(){
	unsigned char *buffer;
	strcpy(fr.StudentCode,"B18DCDT230");
	fr.SizeX = 70;
	fr.SizeY = 100;
	fr.Couter = 10;
	fr.Stop = 0;
	buffer = (char*)malloc(sizeof(fr));
	memcpy(buffer,(const unsigned char*)&fr,sizeof(fr));
	for(i=0;i<sizeof(fr);i++){
		printf("%x ",buffer[i]);
	}
	printf("\n");
	farme_std = sizeof(fr.StudentCode);
	farme_x = sizeof(fr.StudentCode) + sizeof(fr.SizeX);
	farme_y = sizeof(fr.StudentCode) + sizeof(fr.SizeX) + sizeof(fr.SizeY);
	farme_cnt = sizeof(fr.StudentCode) + sizeof(fr.SizeX) + sizeof(fr.SizeY) + sizeof(fr.Couter);
	farme_data = sizeof(fr.StudentCode) + sizeof(fr.SizeX) + sizeof(fr.SizeY) + sizeof(fr.Couter) + sizeof(fr.Data);
	farme_sp = sizeof(fr.StudentCode) + sizeof(fr.SizeX) + sizeof(fr.SizeY) + sizeof(fr.Couter) + sizeof(fr.Data) + sizeof(fr.Stop);
	printf("Student Code: ");
	for(i = 0; i < farme_std; i++){
		printf("%c",buffer[i]);
	}
	for(i = farme_std; i < farme_x; i++){
		printf("\nSize X: = %d\n",buffer[i]);
	}
	for(i = farme_x; i < farme_y; i++){
		printf("Size Y: %d\n",buffer[i]);
	}
	
	for(i = farme_y; i < farme_cnt; i++){
		printf("Counter = %d\n",buffer[i]);
	}
	for(i = farme_cnt; i < farme_sp; i++){
		printf("Stop = %d\n",buffer[i]);
	}
	
	free(buffer);
}

int main(){
	USARTx_Init(USART3, 9600);
	USARTx_Init(USART1, 9600);
	//strTObyte(); -- Ham oki
	//printf("Thai MCU\n");
	while(1){	
		if(Flag_rx){
			Flag_rx = 0;
			printf("%s\n",vrc_Res);
			if(strcmp(vrc_Res,"Do Van Thai")==0){
				USART_SendData(USART1,'Y');
			}
			else{
				USART_SendData(USART1,'N');
			}
		}		
	}
}

