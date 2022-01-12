#include "mcu-i2c.h"
#include "sensor_pcf8574.h"

static uint8_t u8LCD_Buff[8];//bo nho dem luu lai toan bo
static uint8_t u8LcdTmp;

uint8_t backlightState = 1;


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

void PCF_Init(void){
	/* Set 4-bits interface */
	PCF_SendCommand(0x33);		 
	Delay_ms(10);
	PCF_SendCommand(0x32);
	Delay_us(50);
	/* Start to set LCD function */
	PCF_SendCommand(0x28);
		Delay_us(50);	
	/* clear LCD */
	PCF_SendCommand(0x01);
	/* wait 60ms */
		Delay_ms(2);
	/* set entry mode */
	PCF_SendCommand(0x06);	Delay_us(50);;
	/* set display to on */	
	PCF_SendCommand(0x0C);	Delay_us(50);;
	/* move cursor to home and set data address to 0 */
	PCF_SendCommand(0x02);	Delay_us(50);
}

void PCF_Goto(uint8_t row, uint8_t col) {
	switch (row){
		case 1:
			PCF_SendCommand(0x80 + col);
			Delay_us(50);
			break;
		case 2:
			PCF_SendCommand(0x80 + col + 0x40);
			Delay_us(50);
			break;
		case 3:
			PCF_SendCommand(0x80 + col + 0x14);
			Delay_us(50);
			break;
		case 4:
			PCF_SendCommand(0x80 + col + 0x54);
			Delay_us(50);
			break;
	}
}

void PCF_Backlight(uint8_t state) {
	backlightState = (state & 0x01) << LCD_BL;
	I2Cx_WriteByte(I2C_USED,PCF8574_ADDR,backlightState);
}

void PCF_SendData(char data){
	char data_u, data_l;
	uint8_t data_t[4],i=0;
	data_u = data&0xf0;
	data_l = (data<<4)&0xf0;
	data_t[0] = data_u|0x0d;  //en=1, rs=1, rw = 0 
	data_t[1] = data_u|0x09;  //en=0, rs=1,	rw = 0 
	data_t[2] = data_l|0x0d;  //en=1, rs=1, rw = 0 
	data_t[3] = data_l|0x09;  //en=0, rs=1, rw = 0 
	for(i = 0;i<4;i++){
		I2Cx_WriteByte(I2C_USED,PCF8574_ADDR,data_t[i]);
	}
}

void PCF_SendCommand(char data){
  char data_u, data_l;
	uint8_t data_t[4],i=0;
	data_u = data&0xf0;
	data_l = (data<<4)&0xf0;
	data_t[0] = data_u|0x04;  //en=1, rs=0, 
	data_t[1] = data_u;  			//en=0, rs=0,
	data_t[2] = data_l|0x04;  //en=1, rs=0,
	data_t[3] = data_l|0x08;  //en=0, rs=0,
	for(i = 0;i<4;i++){
		I2Cx_WriteByte(I2C_USED,PCF8574_ADDR,data_t[i]);
	}
}

void PCF_Print(char *str){
	while (*str) PCF_SendData(*str++);
}
void PCF_Clear(void){
	PCF_SendCommand(0x01);
	Delay_ms(2);
}








