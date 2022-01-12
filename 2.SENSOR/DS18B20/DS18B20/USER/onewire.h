#ifndef __ONE_WIRE_H
#define __ONE_WIRE_H
#include "stm32f10x.h"
void OneWire_Reset(void);
void OneWire_Write(uint8_t data);
void GPIO_SetState(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode);
uint8_t OneWire_Read(void);
#endif
