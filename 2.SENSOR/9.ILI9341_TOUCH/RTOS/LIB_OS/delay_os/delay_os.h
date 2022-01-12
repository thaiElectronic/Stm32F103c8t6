#ifndef __DELAY_OS_H
#define __DELAY_OS_H 			   
#include "sys_os.h"  
//////////////////////////////////////////////////////////////////////////////////	 

//********************************************************************************

////////////////////////////////////////////////////////////////////////////////// 
	 
void Delay_OS_Init(void);
void Delay_OS_ms(u16 nms);
void Delay_OS_us(u32 nus);

uint32_t millis( void );
uint32_t micros( void );

#endif





























