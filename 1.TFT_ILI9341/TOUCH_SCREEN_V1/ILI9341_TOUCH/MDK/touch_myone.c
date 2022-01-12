#include "touch_myone.h"

void Touch_SPI(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.GPIO_Pin = T_IRQ_Pin|T_MISO_Pin;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;

  GPIO_Init(T_IRQ_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PEPin PEPin PEPin */
  GPIO_InitStruct.GPIO_Pin = T_CLK_Pin|T_MOSI_Pin|T_CS_Pin;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOE, &GPIO_InitStruct);
}



