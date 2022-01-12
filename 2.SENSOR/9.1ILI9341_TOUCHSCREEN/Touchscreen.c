#include "Touchscreen.h"


void touchInit(void){
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

//Internal Touchpad command, do not call directly
uint16_t TP_Read(void)
{
    uint8_t i = 16;
    uint16_t value = 0;

    while(i > 0x00)
    {
        value <<= 1;

				GPIO_WriteBit(TP_CLK_PORT, TP_CLK_PIN, Bit_SET);
				GPIO_WriteBit(TP_CLK_PORT, TP_CLK_PIN, Bit_RESET);
			
        if(GPIO_ReadInputDataBit(TP_MISO_PORT, TP_MISO_PIN) != 0)
        {
            value++;
        }

        i--;
    };

    return value;
}

//Internal Touchpad command, do not call directly
void TP_Write(uint8_t value)
{
    uint8_t i = 0x08;

		GPIO_WriteBit(TP_CLK_PORT, TP_CLK_PIN, Bit_RESET);	
	
    while(i > 0)
    {
        if((value & 0x80) != 0x00)
        {
						GPIO_WriteBit(TP_MOSI_PORT, TP_MOSI_PIN, Bit_SET);
        }
        else
        {
						GPIO_WriteBit(TP_MOSI_PORT, TP_MOSI_PIN, Bit_RESET);
        }

        value <<= 1;
				GPIO_WriteBit(TP_CLK_PORT, TP_CLK_PIN, Bit_SET);
				GPIO_WriteBit(TP_CLK_PORT, TP_CLK_PIN, Bit_RESET);        
        i--;
    };
}



//Read coordinates of touchscreen press. Position[0] = X, Position[1] = Y
uint8_t TP_Read_Coordinates(uint16_t Coordinates[2])
{
    uint32_t avg_x, avg_y = 0;		
		uint16_t rawx, rawy = 0;	
		uint32_t calculating_x, calculating_y = 0;
	
    uint32_t samples = NO_OF_POSITION_SAMPLES;
    uint32_t counted_samples = 0;	
	
		GPIO_WriteBit(TP_CLK_PORT, TP_CLK_PIN, Bit_SET);		
		GPIO_WriteBit(TP_MOSI_PORT, TP_MOSI_PIN, Bit_SET);		
		GPIO_WriteBit(TP_CS_PORT, TP_CS_PIN, Bit_SET);		
		GPIO_WriteBit(TP_CS_PORT, TP_CS_PIN, Bit_RESET);

	
    while((samples > 0)&&(GPIO_ReadInputDataBit(TP_IRQ_PORT, TP_IRQ_PIN) == 0))
    {			
        TP_Write(CMD_RDY);

				rawy = TP_Read();	
				avg_y += rawy;
				calculating_y += rawy;

				
        TP_Write(CMD_RDX);
        rawx = TP_Read();
				avg_x += rawx;
				calculating_x += rawx;
        samples--;
				counted_samples++;
    };
		
		GPIO_WriteBit(TP_CS_PORT, TP_CS_PIN, Bit_SET);

		
		if((counted_samples == NO_OF_POSITION_SAMPLES)&&(GPIO_ReadInputDataBit(TP_IRQ_PORT, TP_IRQ_PIN) == 0))
		{
		
		calculating_x /= counted_samples;
		calculating_y /= counted_samples;
		
		rawx = calculating_x;
		rawy = calculating_y;		
		
		rawx *= -1;
		rawy *= -1;
		
		//CONVERTING 16bit Value to Screen coordinates
    // 65535/273 = 240!
		// 65535/204 = 320!
    Coordinates[0] = ((240 - (rawx/X_TRANSLATION)) - X_OFFSET)*X_MAGNITUDE;
		Coordinates[1] = ((rawy/Y_TRANSLATION)- Y_OFFSET)*Y_MAGNITUDE;
		
		return TOUCHPAD_DATA_OK;			
		}
		else
		{
			Coordinates[0] = 0;
			Coordinates[1] = 0;
			return TOUCHPAD_DATA_NOISY;
		}
}

//Check if Touchpad was pressed. Returns TOUCHPAD_PRESSED (1) or TOUCHPAD_NOT_PRESSED (0)
uint8_t TP_Touchpad_Pressed(void)
{
	if(GPIO_ReadInputDataBit(TP_IRQ_PORT, TP_IRQ_PIN) == 0)
	{
		return TOUCHPAD_PRESSED;
	}
	else
	{
		return TOUCHPAD_NOT_PRESSED;
	}
}








