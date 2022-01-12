#ifndef __SYSTEM_H
#define __SYSTEM_H


#include "Smart_lock_Json.h"
#include "Smart_lock_SD_Card.h"
#include "mcu-gpio.h" 
#include "spi.h"
#include "Timer.h"

extern int Status_display;

void System_Init(void);
void Systen_Run(void);
void System_WatchDog_Init(void);
void System_WatchDog_clear(void);

#endif 
