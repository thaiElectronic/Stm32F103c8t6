#include "Smart_lock_SD_Card.h"
#include "gui.h"
#include "string.h"
#include "Image.h"
FATFS fs;         							/* Work area (file system object) for logical drive */
FIL fsrc, fdst;      						/* file objects */
FRESULT res;
UINT br,bw;
char path0[100]="0:";
unsigned char buffer1[10000];   /* file copy buffer */
char Image_name[30];
int i;
void Read_Images_SD_Card(unsigned char* FIle_Name){
	int k;
	res = f_mount(0,&fs);

	if(res != FR_OK){
//		printf("mount filesystem 0 failed : %d\n\r",res);
	}

	res = f_open(&fsrc,FIle_Name, FA_OPEN_EXISTING | FA_READ);
	if(res != FR_OK){
//		printf("open file error : %d\n\r",res);
	}
	else{
		
		// Doc 70 bytes dau
		res = f_read(&fsrc, buffer1,70, &br);     /* Read a chunk of src file */
		if(res==FR_OK){;
			for(k=0;k<sizeof(buffer1);k++) buffer1[k]=0;
		}
		else{
//			printf("read file error : %d\n\r",res);
		}	
		//**************************************************************************
		
		for(i = 0; i < 32; i++){
			// Doc cac bytes con lai va hien thi len LCD
			res = f_read(&fsrc, buffer1,4800, &br);     /* Read a chunk of src file */
			if(res==FR_OK){
				Gui_DrawbmpUser(0,10*i,240,10,buffer1);
				for(k=0;k<sizeof(buffer1);k++) buffer1[k]=0;
			}
			else{
	//			printf("read file error : %d\n\r",res);
			}	
		}
		//**************************************************************************		
	}
	
	f_close(&fsrc);
}
