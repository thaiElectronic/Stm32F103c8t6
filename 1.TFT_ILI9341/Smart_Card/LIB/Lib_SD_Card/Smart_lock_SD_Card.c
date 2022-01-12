#include "Smart_lock_SD_Card.h"
#include "Smart_lock_Json.h"
#include "gui.h"

FATFS fs;         							/* Work area (file system object) for logical drive */
FIL fsrc, fdst;      						/* file objects */
FRESULT res;
UINT br,bw;
char path0[100]="0:";
unsigned char buffer1[11000];   /* file copy buffer */


void Read_Images_SD_Card(void){
	// Tat Timer de doc the nho
	int k;
	
	TIM_Cmd(TIM2, DISABLE);
	
	res = f_mount(0,&fs);
	if(res != FR_OK){
//		printf("mount filesystem 0 failed : %d\n\r",res);
	}
//	printf("read file test......\n\r");
	res = f_open(&fsrc,new_msv, FA_OPEN_EXISTING | FA_READ);
	if(res != FR_OK){
//		printf("open file error : %d\n\r",res);
	}
	else{
		
		// Doc 70 bytes dau
		res = f_read(&fsrc, buffer1,70, &br);     /* Read a chunk of src file */
		if(res==FR_OK){

//			printf("\n\r read data num : %d\n\r",br);
			for(k=0;k<sizeof(buffer1);k++) buffer1[k]=0;
		}
		else{
//			printf("read file error : %d\n\r",res);
		}	
		//**************************************************************************
		
		// Doc cac bytes con lai va hien thi len LCD
		res = f_read(&fsrc, buffer1,8000, &br);     /* Read a chunk of src file */
		if(res==FR_OK){

//			printf("\n\r read data num : %d\n\r",br);
			
			Gui_bmp16(10,57,80,50,buffer1);
	
			for(k=0;k<sizeof(buffer1);k++) buffer1[k]=0;
		}
		else{
//			printf("read file error : %d\n\r",res);
		}	
		//**************************************************************************		
		// Doc cac bytes con lai va hien thi len LCD
		res = f_read(&fsrc, buffer1,8000, &br);     /* Read a chunk of src file */
		if(res==FR_OK){

//			printf("\n\r read data num : %d\n\r",br);
			
			Gui_bmp16(10,107,80,50,buffer1);
	
			for(k=0;k<sizeof(buffer1);k++) buffer1[k]=0;
		}
		else{
//			printf("read file error : %d\n\r",res);
		}	
		//**************************************************************************		
	}
	
	f_close(&fsrc);
	
	// Bat timer de tiep tuc nhan the
	TIM_Cmd(TIM2, ENABLE);
}
