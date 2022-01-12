#ifndef _SYS_H_
#define _SYS_H_

#include "stm32f10x.h"                  
#include "delay.h"
#include "lcd.h"
#include "ds18b20.h"
#include "onewire.h"
#include "gpio.h"
#include "uart.h"
#include "rtc.h"
#include <stdio.h>
#include "timer.h"
#include "mcu-keypad.h"

void Sys_Init(void);
void RTC_Setup00(u16 Hourx, u16 Minx, u16 Secx);
void RTC_Disp(char* Hourx, char* Minx, char* Secx);
void Sys_run(void);
void Display_Time(void);
void Display_Temp(void);
//char Press_key(void);
#endif
