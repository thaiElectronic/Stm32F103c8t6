/**************************************************************************************************/	

#include "GPIO.h" 

#ifndef _SPI_H_
#define _SPI_H_


u8 SPI_WriteByte(SPI_TypeDef* SPIx,u8 Byte);
void SPI2_Init(void);
void SPI1_Init(void);

#endif
