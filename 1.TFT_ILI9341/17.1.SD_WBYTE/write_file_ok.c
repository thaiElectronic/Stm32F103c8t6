
/* Includes ------------------------------------------------------------------*/
// MicroSD - SPI1: File run oki!

#include "stm32f10x_conf.h"
#include "usart.h"
#include "ff.h"
#include "SPI_MSD1_Driver.h"
#include <string.h>
#include "lib_sd.h" 
#include "image.h"

int i,k;
unsigned char data1[]="LAB AI - PHOTONICS\n";
unsigned char data2[]="Hoc Vien Cong Nghe Buu Chinh Vien Thong";
FATFS fs, Fn;        		 /* Khu v?c làm vi?c (h? th?ng t?p) cho ? dia logic */

FIL fsrc, fdst;      /* file objects */
UINT br,bw;
char path0[512]="";
char buffer[4000];   /* file copy buffer */

FRESULT res1;

void delay(u16 Time){
	u16 i,j;
	for(i = 0; i<Time; i++){
		for(j = 0; j< 0x2aff; j++){}
	}
}

int main(void){
	SystemInit();											// Kh?i t?o Clock h? th?ng
	USART_Configuration();						// Kh?i t?o b? USART 1	
	MSD0_SPI_Configuration();					// Ð?nh c?u hình giao di?n SPI 1

	res = f_mount(0,&fs);							// G?n k?t h? th?ng t?p
	
	if(res != FR_OK){
		printf("mount filesystem 0 failed : %d\n\r",res);
	}
	
	for(i = 0; i < 10; i++){
		
		res = f_open(&fdst, "DAU_VUONG1.txt", FA_OPEN_ALWAYS | FA_WRITE);
		res = f_lseek(&fdst,i*strlen(data1));
		if(res != FR_OK){
			printf("open file error : %d\n\r",res);
		}
		else{
			res = f_write(&fdst, data1, sizeof(data1), &bw);/* Ghi nó vào t?p dst */
			if(res == FR_OK){
				printf("write data ok! %d\n\r",bw);
			}
			else{
				printf("write data error : %d\n\r",res);
			}
		}
		f_close(&fdst);
	}
	
		printf("read file test......\n\r");
  res = f_open(&fsrc, "DAU_VUONG1.txt", FA_OPEN_EXISTING | FA_READ);
	
    if(res != FR_OK){
		printf("open file error : %d\n\r",res);
	}else{
	    res = f_read(&fsrc, buffer, 4000, &br);     /* Ð?c m?t do?n c?a t?p src */
	    
		if(res==FR_OK){
			printf("read data num : %d\n\r",br);
			printf("%s\n\r",buffer);
		}else{
			printf("read file error : %d\n\r",res);
		}
		
	}
	f_close(&fsrc);
	
	
	while(1){
		
	}
}


