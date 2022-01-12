#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "stm32f10x_i2c.h"              // Keil::Device:StdPeriph Drivers:I2C
#include "mcu-i2c.h"
#include "sensor_pcf8574.h"
#include "usart.h"
uint8_t data[5]={0x01,0x02,0x03,0x04,0x05};
u8 data1 = 0;

void I2C_SendData_Normal(void);
void I2C_SendData_PCF8574(void);

int main(){
	I2Cx_Init(I2C_USED, I2C1_B67, I2C_CLOCK_STANDARD);
	PCF_Init();
	PCF_Backlight(0);
	Delay_ms(2000);
	PCF_Backlight(1);
	PCF_Print("Vu Thi Thu Ha");
	PCF_Goto(2,0);
	PCF_Print("Do Van Thai");
	while(1){

	}
}

void I2C_SendData_Normal(void){
		I2C_SendData(I2C_USED,0x67);
		Delay_ms(10);
		data1 = I2C_ReceiveData(I2C_USED);
		Delay_ms(10);
		printf("data: 0x%x\n", data1);
		Delay_ms(500);
}

void I2C_SendData_PCF8574(void){
		I2Cx_WriteByte(I2C_USED,PCF8574_ADDR+0,0x22);
		Delay_ms(2);
}