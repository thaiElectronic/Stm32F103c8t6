#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "stm32f10x_i2c.h"              // Keil::Device:StdPeriph Drivers:I2C
#include "mcu-i2c.h"
#include "sensor_pcf8574.h"
#include "sensor_ds1307.h"
#include "usart.h"
uint8_t data[5]={0x01,0x02,0x03,0x04,0x05};
u8 data1 = 0;
void DS1307_GetTimeUser(void);
void I2C_SendData_Normal(void);
void I2C_SendData_DS1307(void);
DS1307_Time_t time;
uint16_t time_second=0;
uint16_t time_minutes=0,time_hours = 0;

int main(){
	
	uart_Init();
	I2Cx_Init(I2C_USED, I2C1_B67, I2C_CLOCK_STANDARD);
	
	time.seconds = 40;
	time.minutes = 58;
	time.hours = 5;
	time.day = 5;
	time.date = 28;
	time.month = 6;
	time.year = 17;
	DS1307_SetTime(&time);

	while(1){
//		I2C_SendData_DS1307();	
		
//		printf("data: %x\n",I2Cx_ReadByte(I2C1, 0xD0));
//		Delay_ms(500);
		
		time_second 	= DS1307_GetSeconds();
		time_minutes 	= DS1307_GetMinutes();
		time_hours		= DS1307_GetHours();
		printf("thoi gian: %d:%d:%d\n",time_hours,time_minutes,time_second);
		Delay_ms(990);
	}
}

void DS1307_GetTimeUser(void){
	u8 month = 0;
		/* Send START condition */
  I2C_GenerateSTART(I2C1,ENABLE);
	/* Test on EV5 and clear it */
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	/* Send PCF8574A address for write */
  I2C_Send7bitAddress(I2C1, 0xD0, I2C_Direction_Transmitter);
	/* Test on EV6 and clear it */
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	/* Send the data byte to be written */
  I2C_SendData(I2C1,0x00);
	/* Test on EV8 and clear it */
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
		
	/* Send START condition */
  I2C_GenerateSTART(I2C1,ENABLE);
	/* Test on EV5 and clear it */
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));	
	I2C_Send7bitAddress(I2C1, 0xD0, I2C_Direction_Receiver);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
	month = I2C_ReceiveData(I2C1);
	I2C_GenerateSTOP(I2C1,ENABLE);
  I2C_AcknowledgeConfig(I2C1,DISABLE);
	printf("data: 0x%x\n",month);
	Delay_ms(1000);
}

void I2C_SendData_Normal(void){
		I2C_SendData(I2C_USED,0x67);
		Delay_ms(10);
		data1 = I2C_ReceiveData(I2C_USED);
		Delay_ms(10);
		printf("data: 0x%x\n", data1);
		Delay_ms(500);
}

void I2C_SendData_DS1307(void){
		I2Cx_WriteByte(I2C_USED,DS1307_ADDR+0,0x22);
		Delay_ms(2);
}