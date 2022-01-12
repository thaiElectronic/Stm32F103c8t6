#ifndef __TIMER_H
#define __TIMER_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "Smart_lock_RFID.h"

void Timer2_Register(void);
void Timer2_StandardLibrary(void);
void GPIO_Config(void);
void NVIC_Config(void);
void TIM2_IRQHandler(void);
void Delay_ms(uint16_t time);



#endif
