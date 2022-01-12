#include "stm32f10x.h" 
#include "onewire.h"
#include "delay.h"
void GPIO_SetState(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin, GPIOMode_TypeDef GPIO_Mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin;	         		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOx, &GPIO_InitStructure);
}
void OneWire_Reset()
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    GPIO_SetState(GPIOB,GPIO_Pin_9,GPIO_Mode_Out_OD);
		//Thiet lap dau ra
		GPIO_ResetBits(GPIOB,GPIO_Pin_9);
		delay_us(500);
		GPIO_SetState(GPIOB,GPIO_Pin_9,GPIO_Mode_IN_FLOATING);//Thiet lap dau vao
		delay_us(500); 
		GPIO_SetState(GPIOB,GPIO_Pin_9,GPIO_Mode_IN_FLOATING);//Thiet lap dau vao
}
void OneWire_Write(uint8_t data)
{
 uint8_t count;
 for (count=0; count<8; ++count)
 {
  GPIO_SetState(GPIOB,GPIO_Pin_9,GPIO_Mode_Out_OD);//Thiet lap dau ra
  GPIO_ResetBits(GPIOB,GPIO_Pin_9);
  delay_us(2); 
  if(data&0x01)GPIO_SetBits(GPIOB,GPIO_Pin_9);
  else GPIO_ResetBits(GPIOB,GPIO_Pin_9);
  data>>=1;
  delay_us(60); 
  GPIO_SetState(GPIOB,GPIO_Pin_9,GPIO_Mode_IN_FLOATING);//Thiet lap dau vao
  delay_us(2);
 }
}
uint8_t OneWire_Read(void){
 uint8_t count, data=0;
 for (count=0; count<8; ++count)
 {
  GPIO_SetState(GPIOB,GPIO_Pin_9,GPIO_Mode_Out_OD);//Thiet lap dau ra
  GPIO_ResetBits(GPIOB,GPIO_Pin_9);
  delay_us(2);                      
  GPIO_SetState(GPIOB,GPIO_Pin_9,GPIO_Mode_IN_FLOATING);//Thiet lap dau vao         
  delay_us( 8 );                
  if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9))
  data|=0x01<<count;
  delay_us( 120 ); 
 }
 return( data );
}