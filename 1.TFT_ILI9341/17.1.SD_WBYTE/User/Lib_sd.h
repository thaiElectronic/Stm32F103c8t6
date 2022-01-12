#ifndef __LIB_SD_H
#define __LIB_SD_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_conf.h"
#include "usart.h"
#include "ff.h"
#include "SPI_MSD1_Driver.h"
#include <string.h>

extern FRESULT res;
/* Exported Functions --------------------------------------------------------*/

/* N�t b?t d?u du?c qu�t (c�n du?c s? d?ng nhu khu v?c l�m vi?c) */
FRESULT scan_files (char* path ); 
         	
int SD_TotalSize(char *path);
void  Delay (uint32_t nCount);


#endif/* __LID_SD_H */
