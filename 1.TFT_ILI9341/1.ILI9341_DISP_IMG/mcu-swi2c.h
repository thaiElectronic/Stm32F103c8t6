#ifndef MCU_SWI2C_H
#define MCU_SWI2C_H
#include "stm32f10x.h"

void SWI2C_Init(void);
void SWI2C_Start(void);
void SWI2C_Stop(void);
uint8_t SWI2C_Write(uint8_t u8Data);
uint8_t SWI2C_Read(uint8_t u8Ack);

uint8_t AT24C32_Read(uint16_t u16Address, uint16_t u16Num, uint8_t *pu8Data);
uint8_t AT24C32_Write(uint16_t u16Address, uint8_t u16Num, uint8_t *pu8Data);

#endif
