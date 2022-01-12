#include "system.h"

extern unsigned char gImage_keyboard[];

int main(){
	
	SystemInit();
	delay_init(72);	 
	LCD_Init();	
	LCD_Fill(0,0,320,60,WHITE);
	Gui_DrawbmpUser(0,60,320,240,gImage_keyboard);
	while(1){
		
	}
}
