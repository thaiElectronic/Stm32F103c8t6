#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include "stm32f10x_gpio.h" 

#define MAX 200

void delay_Tms(u16 _time);

void SEG_Config(void);
void Button_Init(void);
void Timer1_Init(void);
void Timer2_Init(void);
void Timer3_Init(void);

void Button_Run(void);

int Time_InterchangeSort(void);
int Time_SelectionSort(void);
int Time_BubbleSort(void);

void TIM3_Disp_LED(int value);

void _stop_timer(void);
void _start_timer(void);

void Sys_Init(void);
void Sys_Run(void);

#endif



