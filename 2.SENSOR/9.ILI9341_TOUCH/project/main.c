#include "delay.h"
#include "sys.h"
#include "lcd.h"
#include "touch.h"
#include "gui.h"
#include "test.h"
#include "string.h"
#include "font7s.h"
#include "mcu-usart.h"
#include "stdio.h"
#include "Touchscreen.h"
//#include "font.h"


/*
ham Text_Center: su dung de viet can le giua trong pham vi chi dinh.
*/
void Text_Center(u16 x1, u16 y1, u16 x2, u16 y2, u16 fc, u16 bc, u8 *str, u8 size,u8 mode){
	int Width_x = x2-x1;
	int length_text = strlen((const char *)str);
	int Width_text = length_text*8;
	int X_text = (Width_x - Width_text)/2;
	int Y_text = ((y2-y1)-13)/2;
	Show_Str(X_text+x1,Y_text+y1,fc, bc, str, size, mode);
}



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

int main(void){	
	char counter_buff[30];
	SystemInit();
	delay_init(72);	   
	LCD_Init();	
//  touchInit();  
//	ILI9341_Draw_Text("Touchscreen", 10, 10, BLACK, 2, WHITE);
//	ILI9341_Draw_Text("Touch to draw", 10, 30, BLACK, 2, WHITE);

	while(1){
//		if(TP_Touchpad_Pressed()){				
//			uint16_t x_pos = 0;
//			uint16_t y_pos = 0;				
//			uint16_t position_array[2];					
//			
//			if(TP_Read_Coordinates(position_array) == TOUCHPAD_DATA_OK)
//			{
//			x_pos = position_array[0];
//			y_pos = position_array[1];										
//			sprintf(counter_buff, "POS X: %.3d", x_pos);						
//			ILI9341_Draw_Text(counter_buff, 10, 80, BLACK, 2, WHITE);					
//			sprintf(counter_buff, "POS Y: %.3d", y_pos);						
//			ILI9341_Draw_Text(counter_buff, 10, 120, BLACK, 2, WHITE);
//			delay_ms(1);
//			LCD_Clear(WHITE);
//			}
//		}		

	}
}

