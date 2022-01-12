
/* Includes ------------------------------------------------------------------*/
// MicroSD - SPI1: File run oki!

#include "stm32f10x_conf.h"
#include "usart.h"
#include "ff.h"
#include "SPI_MSD1_Driver.h"
#include <string.h>
#include "lib_sd.h" 


int i,k;
const unsigned char data[20000] = { 
0X9A,0XCE,0X9A,0XCE,0X79,0XCE,0X79,0XCE,0X59,0XC6,0X59,0XC6,0X59,0XC6,0X38,0XC6,
0X38,0XC6,0X38,0XBE,0X17,0XB6,0XF7,0XB5,0XD7,0XB5,0XF7,0XB5,0XF7,0XB5,0XF7,0XB5,
0XF7,0XB5,0XF7,0XB5,0XF7,0XB5,0XF7,0XB5,0XD7,0XB5,0XD7,0XB5,0XD7,0XB5,0XD7,0XB5,
};
uint8_t textFilebuffer1[] = "DAU VUONG XXXXXXXX\n";		
uint8_t textFileBuffer[] = "Hoc Vien Cong Nghe Buu Chinh Vien Thong\n";		

FATFS fs, Fn;        		 /* Khu v?c làm vi?c (h? th?ng t?p) cho ? dia logic */

FIL fsrc, fdst;      /* file objects */
UINT br,bw, ba;
char path0[512]="";
unsigned 	char buffer[14100];   /* file copy buffer */

FRESULT res1,res2;

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
	
	// Vi?t ki?m tra t?p
	printf("write file test......\n\r");
  res = f_open(&fdst, "DAU_VUONG.txt", FA_CREATE_ALWAYS |FA_OPEN_APPEND| FA_WRITE);
    
    // Ghi lan 1 ----------------------------------------------------------------------
	if(res != FR_OK){
		printf("open file error : %d\n\r",res);
	}
	else{
	  //res = f_write(&fdst, data, sizeof(data), &bw);/* Ghi nó vào t?p dst */
		//f_printf(&fdst,"%s",textFilebuffer1);
		res = f_write(&fdst, textFilebuffer1, sizeof(textFilebuffer1), &bw);/* Ghi nó vào t?p dst */
		if(res == FR_OK){
			printf("write data ok! %d\n\r",bw);
		}
		else{
			printf("write data error : %d\n\r",res);
		}
	}
	//f_close(&fdst);
	//----------------------------------------------------------------------------------
	// Ghi lan 2 -----------------------------------------------------------------------
	//res = f_open(&fdst, "DAU_VUONG.txt", FA_OPEN_APPEND | FA_WRITE);
	if(res != FR_OK){
		printf("open file error : %d\n\r",res);
	}
	else{
	  res = f_write(&fdst, textFileBuffer, sizeof(textFileBuffer), &bw);/* Ghi nó vào t?p dst */
		//f_printf(&fdst,"%s",textFileBuffer);
		if(res == FR_OK){
			printf("write data ok! %d\n\r",bw);
		}
		else{
			printf("write data error : %d\n\r",res);
		}
		/*Ðóng t?p tin*/
		
	}
	//----------------------------------------------------------------------------------
	// Dong tep vua Ghi
	
	f_close(&fdst);
	//f_sync(&fdst);
	res1 = f_mount(0,&Fn);
	
	printf("read file test......\n\r");
	
    res1 = f_open(&fsrc, "DAU_VUONG.txt", FA_OPEN_EXISTING | FA_READ);
    if(res1 != FR_OK){
		printf("open file error : %d\n\r",res1);
	}else{
	    res1 = f_read(&fsrc, buffer, 70, &br);     /* Ð?c m?t do?n c?a t?p src */
	    
		if(res1==FR_OK){
			printf("read data num : %d\n\r",br);
			printf("%s\n\r",buffer);
		}else{
			printf("read file error : %d\n\r",res1);
		}

	}
	f_close(&fsrc);
	
	
	while(1){
//		for(i = 0; i<4; i++){
//			USART_SendData(USART1,Data[i]);
//			delay(500);
//		}
	}
}
