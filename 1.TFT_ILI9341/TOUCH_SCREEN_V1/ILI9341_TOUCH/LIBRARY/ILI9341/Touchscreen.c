#include "Touchscreen.h"
TS_TypeInput BT_IRQ_Pin;

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
  GPIO_Init(GPIOA, &GPIO_InitStruct);
	
}

void Fn_INPUT_ReadInput(unsigned char _vruc_Input, TS_TypeInput *_vrts_DataInput){
  _vrts_DataInput->vruc_DataOld = _vruc_Input;
  if(!_vruc_Input){
    if(_vrts_DataInput->vruc_DataOld == _vruc_Input){
      if(_vrts_DataInput->vruc_CountAccess <= 20){ // thoi gian nhan nut < 500ms -> nhan nha; nguoc lai la nhan giu
        _vrts_DataInput->vruc_CountAccess++;
        if(_vrts_DataInput->vruc_CountAccess == 20){ // nhan nha
          _vrts_DataInput->vruc_FlagChange = 1;
          _vrts_DataInput->vruc_hold = 0;
        }
      }
      else// nhan giu
      {
				_vrts_DataInput->vruc_FlagChange = 0;
        _vrts_DataInput->vruc_hold = 1;
      }
    }
    else{
      _vrts_DataInput->vruc_CountAccess = 0;
    }
  }
  else{
    _vrts_DataInput->vruc_CountAccess = 0;
  }
}
void TP_IRQ_Pin_Run(void){
  Fn_INPUT_ReadInput (GPIO_ReadInputDataBit(TP_IRQ_PORT,T_IRQ_Pin), (TS_TypeInput*) (&BT_IRQ_Pin));
}
//Internal Touchpad command, do not call directly
uint16_t TP_Read(void){
	uint8_t i = 16;
	uint16_t value = 0;

	while(i > 0x00){
		value <<= 1;

		GPIO_WriteBit(TP_CLK_PORT, TP_CLK_PIN, Bit_SET);
		GPIO_WriteBit(TP_CLK_PORT, TP_CLK_PIN, Bit_RESET);
	
		if(GPIO_ReadInputDataBit(TP_MISO_PORT, TP_MISO_PIN) != 0){
			value++;
		}
		i--;
	}

	return value;
}

//Internal Touchpad command, do not call directly
void TP_Write(uint8_t value){
	uint8_t i = 0x08;
	GPIO_WriteBit(TP_CLK_PORT, TP_CLK_PIN, Bit_RESET);	
	while(i > 0){
		if((value & 0x80) != 0x00){
			GPIO_WriteBit(TP_MOSI_PORT, TP_MOSI_PIN, Bit_SET);
		}
		else{
			GPIO_WriteBit(TP_MOSI_PORT, TP_MOSI_PIN, Bit_RESET);
		}
		value <<= 1;
		GPIO_WriteBit(TP_CLK_PORT, TP_CLK_PIN, Bit_SET);
		GPIO_WriteBit(TP_CLK_PORT, TP_CLK_PIN, Bit_RESET);        
		i--;
	}
}

//Read coordinates of touchscreen press. Position[0] = X, Position[1] = Y
uint8_t TP_Read_Coordinates(uint16_t Coordinates[2]){
	uint32_t avg_x, avg_y = 0;		
	uint16_t rawx, rawy = 0;	
	uint32_t calculating_x, calculating_y = 0;

	uint32_t samples = NO_OF_POSITION_SAMPLES;
	uint32_t counted_samples = 0;	

	GPIO_WriteBit(TP_CLK_PORT, TP_CLK_PIN, Bit_SET);		
	GPIO_WriteBit(TP_MOSI_PORT, TP_MOSI_PIN, Bit_SET);		
	GPIO_WriteBit(TP_CS_PORT, TP_CS_PIN, Bit_SET);		
	GPIO_WriteBit(TP_CS_PORT, TP_CS_PIN, Bit_RESET);
	TP_IRQ_Pin_Run();
	while((samples > 0)&&(BT_IRQ_Pin.vruc_FlagChange == 0)){			
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
	}	
	GPIO_WriteBit(TP_CS_PORT, TP_CS_PIN, Bit_SET);
	if((counted_samples == NO_OF_POSITION_SAMPLES)&&(BT_IRQ_Pin.vruc_FlagChange == 0)){
	
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
	else{
		Coordinates[0] = 0;
		Coordinates[1] = 0;
		return TOUCHPAD_DATA_NOISY;
	}
}

//Check if Touchpad was pressed. Returns TOUCHPAD_PRESSED (1) or TOUCHPAD_NOT_PRESSED (0)
uint8_t TP_Touchpad_Pressed(void){
	TP_IRQ_Pin_Run();
	if(BT_IRQ_Pin.vruc_FlagChange == 0){
		return TOUCHPAD_PRESSED;
	}
	else{
		return TOUCHPAD_NOT_PRESSED;
	}
}








