#ifndef _TIMER_H_
#define _TIMER_H_

#include "gpio.h"
#include "stm32f10x_tim.h"
extern unsigned int vrvc_SttBlink;
void TIMER4_Config(void);
void TIMER2_Config(void);
#endif
