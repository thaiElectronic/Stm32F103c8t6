#include "mcu-swi2c.h"
#include "mcu-delay.h"

#define PIN_SDA 					 GPIO_Pin_0
#define PIN_SCL						 GPIO_Pin_1
#define PORT_SWI2C				 GPIOB
#define RCC_PORT_SWI2C		 RCC_APB2Periph_GPIOB

#define SDA_0 						 GPIO_ResetBits(PORT_SWI2C, PIN_SDA)
#define SDA_1 						 GPIO_SetBits(PORT_SWI2C, PIN_SDA)
#define SCL_0 						 GPIO_ResetBits(PORT_SWI2C, PIN_SCL)
#define SCL_1 						 GPIO_SetBits(PORT_SWI2C, PIN_SCL)
#define SDA_VAL 					 (GPIO_ReadInputDataBit(PORT_SWI2C, PIN_SDA))


void SWI2C_Init(void){
	GPIO_InitTypeDef gpioInit;
	
	RCC_APB2PeriphClockCmd(RCC_PORT_SWI2C, ENABLE);
	gpioInit.GPIO_Mode = GPIO_Mode_Out_OD;
	gpioInit.GPIO_Pin = PIN_SDA | PIN_SCL;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_SWI2C, &gpioInit);
	
	SDA_1;
	SCL_1;
}

void SWI2C_Start(void){
	SCL_1;
	Delay_us(3);
	SDA_1;
	Delay_us(3);
	SDA_0;
	Delay_us(3);
	SCL_0;
	Delay_us(3);
}

void SWI2C_Stop(void){	
	SDA_0;
	Delay_us(3);
	SCL_1;
	Delay_us(3);
	SDA_1;
	Delay_us(3);
}

uint8_t SWI2C_Write(uint8_t u8Data){ // send data
	uint8_t i;
	uint8_t u8Ret;
	
	for (i = 0; i < 8; ++i) {
		if(u8Data & 0x80){
			SDA_1;
		} 
		else {
			SDA_0;
		}
		Delay_us(3);
		SCL_1;
		Delay_us(5);
		SCL_0;
		Delay_us(2);
		u8Data <<= 1;
	}
	
	SDA_1;
	Delay_us(3);
	SCL_1;
	Delay_us(3);
	if(SDA_VAL){ // check bit thu 9 tren duong truyen SDA
		u8Ret = 0; 
	} 
	else{
		u8Ret = 1;
	}
	Delay_us(2);
	SCL_0;
	Delay_us(5);
	
	return u8Ret;
}

uint8_t SWI2C_Read(uint8_t u8Ack){
	uint8_t i;
	uint8_t u8Ret;
	
	SDA_1;
	Delay_us(3);
	
	for (i = 0; i < 8; ++i) {
		u8Ret <<= 1;
		SCL_1;
		Delay_us(3);
		if(SDA_VAL){
			u8Ret |= 0x01;
		}
		Delay_us(2);
		SCL_0;
		Delay_us(5);
	}
	
	if(u8Ack){
		SDA_0;
	} 
	else{
		SDA_1;
	}
	Delay_us(3);
	
	SCL_1;
	Delay_us(5);
	SCL_0;
	Delay_us(5);
	
	return u8Ret;
}

uint8_t AT24C32_Read(uint16_t u16Address, uint16_t u16Num, uint8_t *pu8Data)
{
	uint16_t i;
	
	SWI2C_Start();
	if (SWI2C_Write(0xa0) == 0) {
		SWI2C_Stop();
		return 0;
	}
	
	if (SWI2C_Write(u16Address >> 8) == 0) {
		SWI2C_Stop();
		return 0;
	}
	
	if (SWI2C_Write(u16Address) == 0) {
		SWI2C_Stop();
		return 0;
	}
	
	SWI2C_Start();
	
	if (SWI2C_Write(0xa1) == 0) {
		SWI2C_Stop();
		return 0;
	}
	
	for (i = 0; i < u16Num - 1; ++i) {
		pu8Data[i] = SWI2C_Read(1);
	}
	
	pu8Data[i] = SWI2C_Read(0);
	
	SWI2C_Stop();
	
	return 1;
}

uint8_t AT24C32_Write(uint16_t u16Address, uint8_t u16Num, uint8_t *pu8Data)
{
	uint16_t i;
	
	for (i = 0; i < u16Num; ++i) {
		SWI2C_Start();
		if (SWI2C_Write(0xa0) == 0) {
			SWI2C_Stop();
			return 0;
		}
		if (SWI2C_Write((u16Address + i) >> 8) == 0) {
			SWI2C_Stop();
			return 0;
		}
		
		if (SWI2C_Write(u16Address + i) == 0) {
			SWI2C_Stop();
			return 0;
		}
		if (SWI2C_Write(pu8Data[i]) == 0) {
			SWI2C_Stop();
			return 0;
		}
		SWI2C_Stop();
		Delay_ms(10);
	}
	
	return 1;
}