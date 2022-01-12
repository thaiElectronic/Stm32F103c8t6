#ifndef _DELAY_SYS_H_ 
#define _DELAY_SYS_H_
#include "stm32f10x.h"

void Delay_init(u8 SYSCLK);
void Delay_ms(u16 ms);
void Delay_us(u32 us);

#endif
