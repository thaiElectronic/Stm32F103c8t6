#include "ILI9341_Driver.h"
#include "delay_sys.h"
#include "ILI9341_Define.h"
#include "ILI9341_Gui.h"

ILI9341_dev ili_dev;
u16 POINT_COLOR = 0x0000,BACK_COLOR = 0xFFFF;  
u16 DeviceCode;
void ILI9341_Init(void){
	ILI9341_SPI_Display_Init();

	/* Reset The Screen */
	ILI9341_Reset();
	ILI9341_Send_Command(0xCF);  
	ILI9341_Send_Data(0x00); 
	ILI9341_Send_Data(0xD9); //C1 
	ILI9341_Send_Data(0X30); 
	ILI9341_Send_Command(0xED);  
	ILI9341_Send_Data(0x64); 
	ILI9341_Send_Data(0x03); 
	ILI9341_Send_Data(0X12); 
	ILI9341_Send_Data(0X81); 
	ILI9341_Send_Command(0xE8);  
	ILI9341_Send_Data(0x85); 
	ILI9341_Send_Data(0x10); 
	ILI9341_Send_Data(0x7A); 
	ILI9341_Send_Command(0xCB);  
	ILI9341_Send_Data(0x39); 
	ILI9341_Send_Data(0x2C); 
	ILI9341_Send_Data(0x00); 
	ILI9341_Send_Data(0x34); 
	ILI9341_Send_Data(0x02); 
	ILI9341_Send_Command(0xF7);  
	ILI9341_Send_Data(0x20); 
	ILI9341_Send_Command(0xEA);  
	ILI9341_Send_Data(0x00); 
	ILI9341_Send_Data(0x00); 
	ILI9341_Send_Command(0xC0);    //Power control 
	ILI9341_Send_Data(0x1B);   //VRH[5:0] 
	ILI9341_Send_Command(0xC1);    //Power control 
	ILI9341_Send_Data(0x12);   //SAP[2:0];BT[3:0] //0x01
	ILI9341_Send_Command(0xC5);    //VCM control 
	ILI9341_Send_Data(0x26); 	 //3F
	ILI9341_Send_Data(0x26); 	 //3C
	ILI9341_Send_Command(0xC7);    //VCM control2 
	ILI9341_Send_Data(0XB0); 
	ILI9341_Send_Command(0x36);    // Memory Access Control 
	ILI9341_Send_Data(0x08); 
	ILI9341_Send_Command(0x3A);   
	ILI9341_Send_Data(0x55); 
	ILI9341_Send_Command(0xB1);   
	ILI9341_Send_Data(0x00);   
	ILI9341_Send_Data(0x1A); 
	ILI9341_Send_Command(0xB6);    // Display Function Control 
	ILI9341_Send_Data(0x0A); 
	ILI9341_Send_Data(0xA2); 
	ILI9341_Send_Command(0xF2);    // 3Gamma Function Disable 
	ILI9341_Send_Data(0x00); 
	ILI9341_Send_Command(0x26);    //Gamma curve selected 
	ILI9341_Send_Data(0x01); 
	ILI9341_Send_Command(0xE0); //Set Gamma
	ILI9341_Send_Data(0x1F);
	ILI9341_Send_Data(0x24);
	ILI9341_Send_Data(0x24);
	ILI9341_Send_Data(0x0D);
	ILI9341_Send_Data(0x12);
	ILI9341_Send_Data(0x09);
	ILI9341_Send_Data(0x52);
	ILI9341_Send_Data(0xB7);
	ILI9341_Send_Data(0x3F);
	ILI9341_Send_Data(0x0C);
	ILI9341_Send_Data(0x15);
	ILI9341_Send_Data(0x06);
	ILI9341_Send_Data(0x0E);
	ILI9341_Send_Data(0x08);
	ILI9341_Send_Data(0x00);
	ILI9341_Send_Command(0XE1); //Set Gamma
	ILI9341_Send_Data(0x00);
	ILI9341_Send_Data(0x1B);
	ILI9341_Send_Data(0x1B);
	ILI9341_Send_Data(0x02);
	ILI9341_Send_Data(0x0E);
	ILI9341_Send_Data(0x06);
	ILI9341_Send_Data(0x2E);
	ILI9341_Send_Data(0x48);
	ILI9341_Send_Data(0x3F);
	ILI9341_Send_Data(0x03);
	ILI9341_Send_Data(0x0A);
	ILI9341_Send_Data(0x09);
	ILI9341_Send_Data(0x31);
	ILI9341_Send_Data(0x37);
	ILI9341_Send_Data(0x1F);

	ILI9341_Send_Command(0x2B); 
	ILI9341_Send_Data(0x00);
	ILI9341_Send_Data(0x00);
	ILI9341_Send_Data(0x01);
	ILI9341_Send_Data(0x3f);
	ILI9341_Send_Command(0x2A); 
	ILI9341_Send_Data(0x00);
	ILI9341_Send_Data(0x00);
	ILI9341_Send_Data(0x00);
	ILI9341_Send_Data(0xef);	 
	ILI9341_Send_Command(0x11); //Exit Sleep
	Delay_ms(120);
	ILI9341_Send_Command(0x29); //display on	
	ILI9341_Send_Data(0x2C);
	ILI9341_Gui_Direction(1);
}

void ILI9341_Reset(void){
	ILI9341_PIN_RST_RESET;
	Delay_ms(50);
	ILI9341_PIN_RST_SET;
	Delay_ms(50);
//	ILI9341_Send_Command(0x01);
}

u8 SPI_SendByte(u8 Byte){
	while((ILI9341_SPI_DISPLAY->SR&SPI_I2S_FLAG_TXE)==RESET);			  
	ILI9341_SPI_DISPLAY->DR=Byte;	 
	while((ILI9341_SPI_DISPLAY->SR&SPI_I2S_FLAG_RXNE)==RESET);  
	return ILI9341_SPI_DISPLAY->DR;          	     	
} 

static void ILI9341_Send_Command(unsigned char command){
	ILI9341_PIN_CS_RESET;
	ILI9341_PIN_DC_RESET;	
	SPI_SendByte(command);
	ILI9341_PIN_CS_SET;
}

static void ILI9341_Send_Data(unsigned char data){
	ILI9341_PIN_CS_RESET;
	ILI9341_PIN_DC_SET;
	SPI_SendByte(data);
	ILI9341_PIN_CS_SET;
}

/*****************************************************************************
 * @name       :void LCD_WriteRAM_Prepare(void)
 * @date       :2018-08-09 
 * @function   :Write GRAM
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	 
void ILI9341_WriteRAM_Prepare(void){
	ILI9341_Send_Command(ili_dev.wramcmd);
}	  

/*****************************************************************************
 * @name       :void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue)
 * @date       :2018-08-09 
 * @function   :Write data into registers
 * @parameters :LCD_Reg:Register address
                LCD_RegValue:Data to be written
 * @retvalue   :None
******************************************************************************/
void ILI9341_WriteReg(u8 LCD_Reg, u16 LCD_RegValue){	
	ILI9341_Send_Command(LCD_Reg);  
	ILI9341_Send_Data(LCD_RegValue);	    		 
}	

void ILI9341_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd){	
	ILI9341_Send_Command(ili_dev.setxcmd);	
	ILI9341_Send_Data(xStar>>8);
	ILI9341_Send_Data(0x00FF&xStar);		
	ILI9341_Send_Data(xEnd>>8);
	ILI9341_Send_Data(0x00FF&xEnd);

	ILI9341_Send_Command(ili_dev.setycmd);	
	ILI9341_Send_Data(yStar>>8);
	ILI9341_Send_Data(0x00FF&yStar);		
	ILI9341_Send_Data(yEnd>>8);
	ILI9341_Send_Data(0x00FF&yEnd);

	ILI9341_WriteRAM_Prepare();	//¿ªÊ¼Ð´ÈëGRAM			
} 

void ILI9341_Send_Data_16Bit(u16 Data){	
	ILI9341_PIN_CS_RESET;
	ILI9341_PIN_DC_SET;  
	SPI_SendByte(Data>>8);
	SPI_SendByte(Data);
	ILI9341_PIN_CS_SET;
}